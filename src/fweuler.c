/* fweuler: a forward-Euler integrator
 * (add more description soon...)
 * The vector X fully specifies the state of the system at time t. */

#include <stdio.h>
#include <stdlib.h>
#include "fweuler.h"

fweuler * fweuler_new(int n_vars, double dt, double t0, double X0[],
                      double * (* F)(double, double []), int verbose,
                      int write, FILE * poutfile) {
    
    fweuler * pfweuler = malloc(sizeof(fweuler));

    /* Load integration parameters */
    pfweuler->n_vars = n_vars;
    pfweuler->dt = dt;
    pfweuler->F = F;
    pfweuler->verbose = verbose;
    pfweuler->write = write;
    pfweuler->poutfile = poutfile;
    
    /* Load initial conditions */
    pfweuler->t = t0;
    pfweuler->X = malloc(n_vars * sizeof(double));
    pfweuler->X = X0;

    /* Print and/or write initial state if necessary */
    if (verbose) fweuler_print_state(pfweuler);
    if (write) fweuler_write_state(pfweuler);
   
    /* These arrays store intermediate data of constant size, so making them
     * struct members (instead of reallocating with each iteration) to reduce
     * memory allocation overhead */
    pfweuler->X_inc = malloc(pfweuler->n_vars * sizeof(double));
    pfweuler->X_step = malloc(pfweuler->n_vars * sizeof(double));

    return pfweuler;
}

void fweuler_step(fweuler * pfweuler) {
    int i;

    /* Increment */
    pfweuler->X_inc = pfweuler->F(pfweuler->t, pfweuler->X);
    
    /* Get results for this step */
    pfweuler->t_step = pfweuler->t + pfweuler->dt;
    for (i = 0; i < pfweuler->n_vars; i++)
        pfweuler->X_step[i] = pfweuler->X[i]
                              + pfweuler->dt * pfweuler->X_inc[i];

    /* Update state */
    pfweuler->t = pfweuler->t_step;
    pfweuler->X = pfweuler->X_step;
    pfweuler->n_steps++;

    /* Print and/or write state if necessary */
    if (pfweuler->verbose) fweuler_print_state(pfweuler);
    if (pfweuler->write) fweuler_write_state(pfweuler);
}

void fweuler_print_state(fweuler * pfweuler) {
    int i;

    printf("%f ", pfweuler->t);
    for (i = 0; i < pfweuler->n_vars - 1; i++)
        printf("%f ", pfweuler->X[i]);
    printf("%f\n", pfweuler->X[pfweuler->n_vars - 1]);
}

void fweuler_write_state(fweuler * pfweuler) {
    int i;
    
    fprintf(pfweuler->poutfile, "%f ", pfweuler->t);
    for (i = 0; i < pfweuler->n_vars - 1; i++)
        fprintf(pfweuler->poutfile, "%f ", pfweuler->X[i]);
    fprintf(pfweuler->poutfile, "%f\n", pfweuler->X[pfweuler->n_vars - 1]);
}

void fweuler_integrate(fweuler * pfweuler, int total_steps) {
    while (total_steps--)
        fweuler_step(pfweuler);
}
