#ifndef FWEULER_H
#define FWEULER_H

/*! @file */

/*! A forward-Euler integrator. Simple but inaccurate.*/
typedef struct fweuler {
    int n_vars;      /*! Number of spatial variables */
    double dt;       /*! Length of timestep */
    double t;        /*! Elapsed time */
    double * X;      /*! Current state (at time t) */
    double * (*F)(double, double []); /*! ODE vector function */
    int verbose;     /*! Verbose flag */
    int write;       /*! Write flag */
    FILE * poutfile; /*! Output file pointer */
    int n_steps;     /*! Number of steps so far */
    double t_inc;    /*! Array for storing intermediate data */
    double * X_inc;  /*! Array for storing intermediate data */
    double t_step;   /*! Array for storing intermediate data */
    double * X_step; /*! Array for storing intermediate data */
} fweuler;

/*! Initializes a forward-Euler integrator */
fweuler * fweuler_new(int, double, double, double [],
                      double * (*)(double, double[]), int, int, FILE *);

/*! Prints state at time t */
void fweuler_print_state(fweuler *);

/*! Writes state at time t to file */
void fweuler_write_state(fweuler *);

/*! Integrates system over one timestep */
void fweuler_step(fweuler *);

/*! Integrates system over multiple timesteps */
void fweuler_integrate(fweuler *, int);

#endif /* FWEULER.H */
