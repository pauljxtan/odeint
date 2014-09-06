/* RK4: a classical (4th-order) Runge-Kutta integrator
 * 
 * The integrator handles systems of any number of coupled ODEs, represented
 * as a single vector function.
 *
 * The initial value problem is specified by
 *     X_dot = f(t, X); X(t_0) = X_0
 *
 * For a step size dt > 0, we define
 *     t[i+1] = t[i] + dt
 *     X[i+1] = X[i] + (1/6)(k_1 + 2k_2 + 2k_3 + k_4)
 * for i = 0, 1, 2, ..., where
 *     k_1 = dt * f(t[i], X[i])
 *     k_2 = dt * f(t[i] + dt/2, X[i] + (1/2)k_1)
 *     k_3 = dt * f(t[i] + dt/2, X[i] + (1/2)k_2)
 *     k_4 = dt * f(t[i] + dt, X[i] + k_3).
 *
 * The vector X fully specifies the state of the system at time t. */

#include <stdio.h>
#include <stdlib.h>
#include "rk4.h"

rk4 * rk4_new(int n_vars, double dt, double t0, double X0[],
              double * (* F)(double, double []), int verbose, int write,
              FILE * poutfile) {

    rk4 * prk4 = malloc(sizeof(rk4));

    /* Load integration parameters */
    prk4->n_vars = n_vars;
    prk4->dt = dt;
    prk4->F = F;
    prk4->verbose = verbose;
    prk4->write = write;
    prk4->poutfile = poutfile;
    
    /* Load initial conditions */
    prk4->t = t0;
    prk4->X = malloc(n_vars * sizeof(double));
    prk4->X = X0;

    /* Print and/or write initial state if necessary */
    if (verbose) rk4_print_state(prk4);
    if (write) rk4_write_state(prk4);

    /* These arrays store intermediate data of constant size, so making them
     * struct members (instead of reallocating with each iteration) to reduce
     * memory allocation overhead */
    prk4->K1 = malloc(prk4->n_vars * sizeof(double));
    prk4->K2 = malloc(prk4->n_vars * sizeof(double));
    prk4->K3 = malloc(prk4->n_vars * sizeof(double));
    prk4->K4 = malloc(prk4->n_vars * sizeof(double));
    prk4->X_inc = malloc(prk4->n_vars * sizeof(double));
    prk4->X_step = malloc(prk4->n_vars * sizeof(double));

    return prk4;
}

void rk4_step(rk4 * prk4) {
    int i;

    /* First increment */
    prk4->K1 = prk4->F(prk4->t, prk4->X);
    for (i = 0; i < prk4->n_vars; i++)
        prk4->K1[i] *= prk4->dt;

    /* Second increment */
    prk4->t_inc = prk4->t + prk4->dt / 2;
    for (i = 0; i < prk4->n_vars; i++)
        prk4->X_inc[i] = prk4->X[i] + prk4->K1[i] / 2;
    prk4->K2 = prk4->F(prk4->t_inc, prk4->X_inc);
    for (i = 0; i < prk4->n_vars; i++)
        prk4->K2[i] *= prk4->dt;

    /* Third increment */
    prk4->t_inc = prk4->t + prk4->dt / 2;
    for (i = 0; i < prk4->n_vars; i++)
        prk4->X_inc[i] = prk4->X[i] + prk4->K2[i] / 2;
    prk4->K3 = prk4->F(prk4->t_inc, prk4->X_inc);
    for (i = 0; i < prk4->n_vars; i++)
        prk4->K3[i] *= prk4->dt;

    /* Fourth increment */
    prk4->t_inc = prk4->t + prk4->dt;
    for (i = 0; i < prk4->n_vars; i++)
        prk4->X_inc[i] = prk4->X[i] + prk4->K3[i];
    prk4->K4 = prk4->F(prk4->t_inc, prk4->X_inc);
    for (i = 0; i < prk4->n_vars; i++)
        prk4->K4[i] *= prk4->dt;

    /* Get results for this step */
    prk4->t_step = prk4->t + prk4->dt;
    for (i = 0; i < prk4->n_vars; i++)
        /* Take weighted average of increments */
        prk4->X_step[i] = prk4->X[i] + (prk4->K1[i] + 2 * prk4->K2[i]
                                        + 2 * prk4->K3[i] + prk4->K4[i]) / 6;
    /* Update state */
    prk4->t = prk4->t_step;
    prk4->X = prk4->X_step;
    prk4->n_steps++;

    /* Print and/or write state if necessary */
    if (prk4->verbose) rk4_print_state(prk4);
    if (prk4->write) rk4_write_state(prk4);
}

void rk4_print_state(rk4 * prk4) {
    int i;

    printf("%f ", prk4->t);
    for (i = 0; i < prk4->n_vars - 1; i++)
        printf("%f ", prk4->X[i]);
    printf("%f\n", prk4->X[prk4->n_vars - 1]);
}

void rk4_write_state(rk4 * prk4) {
    int i;

    fprintf(prk4->poutfile, "%f ", prk4->t);
    for (i = 0; i < prk4->n_vars - 1; i++)
        fprintf(prk4->poutfile, "%f ", prk4->X[i]);
    fprintf(prk4->poutfile, "%f\n", prk4->X[prk4->n_vars - 1]);
}

void rk4_integrate(rk4 * prk4, int total_steps) {
    while (total_steps--)
        rk4_step(prk4);
}
