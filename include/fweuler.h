#ifndef FWEULER_H
#define FWEULER_H

typedef struct fweuler {
    /* Number of spatial variables */
    int n_vars;
    /* Length of timestep */
    double dt;
    /* Elapsed time */
    double t;
    /* Current state (at time t) */
    double * X;
    /* ODE vector function */
    double * (*F)(double, double []);
    /* Verbose flag */
    int verbose;
    /* Write flag */
    int write;
    /* Output file pointer */
    FILE * poutfile;
    /* Number of steps so far */
    int n_steps;
    /* Arrays for storing intermediate data */
    double t_inc;
    double * X_inc;
    double t_step;
    double * X_step;
} fweuler;

/* fweuler_new: "Constructor" for forward Euler integrator */
fweuler * fweuler_new(int, double, double, double [],
                      double * (*)(double, double[]), int, int, FILE *);

/* fweuler_print_state: Print the state at time t */
void fweuler_print_state(fweuler *);

/* fweuler_write_state: Write the state at time t */
void fweuler_write_state(fweuler *);

/* fweuler_step: Integrate over one timestep */
void fweuler_step(fweuler *);

/* fweuler_integrate: Integrate over multiple timesteps */
void fweuler_integrate(fweuler *, int);

#endif /* FWEULER.H */
