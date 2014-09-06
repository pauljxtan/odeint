/* bulsto: a Bulirsch-Stoer integrator
 * (add more description here)
 * The vector X fully specifies the state of the system at time t. */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "bulsto.h"

bulsto * bulsto_new(int n_vars, double dt, double t0, double X0[],
                    double * (* F)(double, double []), double delta,
                    int verbose, int write, FILE * poutfile) {

    bulsto * pbulsto = malloc(sizeof(bulsto));

    /* Load integration parameters */
    pbulsto->n_vars = n_vars;
    pbulsto->dt = dt;
    pbulsto->F = F;
    pbulsto->delta = delta;
    pbulsto->verbose = verbose;
    pbulsto->write = write;
    pbulsto->poutfile = poutfile;
    
    /* Load initial conditions */
    pbulsto->t = t0;
    pbulsto->X = malloc(n_vars * sizeof(double));
    pbulsto->X = X0;

    /* Print and/or write initial state if necessary */
    if (verbose) bulsto_print_state(pbulsto);
    if (write) bulsto_write_state(pbulsto);

    /* These arrays store intermediate data of constant size, so making them
     * struct members (instead of reallocating with each iteration) to reduce
     * memory allocation overhead */
    pbulsto->epsilon = malloc(pbulsto->n_vars * sizeof(double));
    pbulsto->X1 = malloc(pbulsto->n_vars * sizeof(double));
    pbulsto->X2 = malloc(pbulsto->n_vars * sizeof(double));
    pbulsto->X_inc = malloc(pbulsto->n_vars * sizeof(double));
    pbulsto->X_step = malloc(pbulsto->n_vars * sizeof(double));

    return pbulsto;
}

void bulsto_step(bulsto * pbulsto) {
    int i, j;
    /* Number of small step-sizes */
    int n;
    /* Size of small step-size */
    double ddt;
    /* Estimate of local error */
    double error;
    /* Rows of Richardson extrapolation table */
    double * E1 = NULL;
    double * E2 = NULL;

    /* First midpoint step of size dt */
    n = 1;
    pbulsto->X_inc = pbulsto->F(pbulsto->t, pbulsto->X);
    for (i = 0; i < pbulsto->n_vars; i++)
        pbulsto->X1[i] = pbulsto->X[i] + (pbulsto->dt / 2) * pbulsto->X_inc[i];
    pbulsto->X_inc = pbulsto->F(pbulsto->t, pbulsto->X1);
    for (i = 0; i < pbulsto->n_vars; i++)
        pbulsto->X2[i] = pbulsto->X[i] + pbulsto->dt * pbulsto->X_inc[i];

    /* Get first row of extrapolation table (single modified midpoint step) */
    E1 = malloc(pbulsto->n_vars * sizeof(double));
    
    pbulsto->X_inc = pbulsto->F(pbulsto->t, pbulsto->X2);
    for (i = 0; i < pbulsto->n_vars; i++)
        E1[i] = (pbulsto->X1[i] + pbulsto->X2[i]
                 + pbulsto->X_inc[i] * pbulsto->dt / 2) / 2;

    /* Extrapolate increasing number of rows until target accuracy achieved */
    error = 2 * pbulsto->dt * pbulsto->delta;
    while (error > pbulsto->dt * pbulsto->delta) {
        n++;
        ddt = pbulsto->dt / n;

        /* First midpoint step of size ddt */
        pbulsto->X_inc = pbulsto->F(pbulsto->t, pbulsto->X);
        for (i = 0; i < pbulsto->n_vars; i++)
            pbulsto->X1[i] = pbulsto->X[i] + (ddt / 2) * pbulsto->X_inc[i];
        pbulsto->X_inc = pbulsto->F(pbulsto->t, pbulsto->X1);
        for (i = 0; i < pbulsto->n_vars; i++)
            pbulsto->X2[i] = pbulsto->X[i] + ddt * pbulsto->X_inc[i];
        for (i = 0; i < n - 1; i++) {
            pbulsto->X_inc = pbulsto->F(pbulsto->t, pbulsto->X2);
            for (j = 0; j < pbulsto->n_vars; j++)
                pbulsto->X1[j] += ddt * pbulsto->X_inc[j];
            pbulsto->X_inc = pbulsto->F(pbulsto->t, pbulsto->X1);
            for (j = 0; j < pbulsto->n_vars; j++)
                pbulsto->X2[j] += ddt * pbulsto->X_inc[j];
        }

        /* E2 records the previous E1; used for error calculation later */
        E2 = realloc(E2, (n - 1) * pbulsto->n_vars * sizeof(double));
        for (i = 0; i < (n - 1) * pbulsto->n_vars; i++)
            E2[i] = E1[i];

        /* E1 becomes an n-dimensional array here */
        E1 = realloc(E1, n * pbulsto->n_vars * sizeof(double));
        pbulsto->X_inc = pbulsto->F(pbulsto->t, pbulsto->X2);
        for (i = 0; i < pbulsto->n_vars; i++)
            E1[i] = (pbulsto->X1[i] + pbulsto->X2[i]
                     + (ddt / 2) * pbulsto->X_inc[i]) / 2;
        
        /* Get remaining rows of extrapolation table */
        for (i = 1; i < n; i++) {
            for (j = 0; j < pbulsto->n_vars; j++) {
                pbulsto->epsilon[j] = E1[(i-1)*pbulsto->n_vars + j]
                                      - E2[(i-1)*pbulsto->n_vars + j];
                pbulsto->epsilon[j] /= pow(((double) n / (n - 1)), 2 * i) - 1;
            }
            for (j = 0; j < pbulsto->n_vars; j++)
                E1[i * pbulsto->n_vars + j] = E1[(i - 1) * pbulsto->n_vars
                                                   + j] + pbulsto->epsilon[j];
        }
        error = fabs(pbulsto->epsilon[0]);
    }
    
    /* Get results for this step */
    pbulsto->t_step = pbulsto->t + pbulsto->dt;
    for (i = 0; i < pbulsto->n_vars; i++)
        /* Take the most accurate estimate */
        pbulsto->X_step[i] = E1[(n - 1) * pbulsto->n_vars + i];

    /* Update state */
    pbulsto->t = pbulsto->t_step;
    pbulsto->X = pbulsto->X_step;
    pbulsto->n_steps++;

    /* Print and/or write state if necessary */
    if (pbulsto->verbose) bulsto_print_state(pbulsto);
    if (pbulsto->write) bulsto_write_state(pbulsto);
}

void bulsto_print_state(bulsto * pbulsto) {
    int i;

    printf("%f ", pbulsto->t);
    for (i = 0; i < pbulsto->n_vars - 1; i++)
        printf("%f ", pbulsto->X[i]);
    printf("%f\n", pbulsto->X[pbulsto->n_vars - 1]);
}

void bulsto_write_state(bulsto * pbulsto) {
    int i;

    fprintf(pbulsto->poutfile, "%f ", pbulsto->t);
    for (i = 0; i < pbulsto->n_vars - 1; i++)
        fprintf(pbulsto->poutfile, "%f ", pbulsto->X[i]);
    fprintf(pbulsto->poutfile, "%f\n", pbulsto->X[pbulsto->n_vars - 1]);
}

void bulsto_integrate(bulsto * pbulsto, int total_steps) {
    while (total_steps--)
        bulsto_step(pbulsto);
}
