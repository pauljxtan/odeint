#ifndef FWEULER_H
#define FWEULER_H

/*! @file */

//! A forward-Euler integrator.
typedef struct fweuler {
    //! Number of spatial variables
    int n_vars;
    //! Length of timestep
    double dt;
    //! Elapsed time
    double t;
    //! Current state (at time t)
    double * X;
    //! ODE vector function
    double * (*F)(double, double []);
    //! Verbose flag
    int verbose;
    //! Write flag
    int write;
    //! Output file pointer
    FILE * poutfile;
    //! Number of steps so far
    int n_steps;
    //! Array for storing intermediate data
    double t_inc;
    //! Array for storing intermediate data
    double * X_inc;
    //! Array for storing intermediate data
    double t_step;
    //! Array for storing intermediate data
    double * X_step;
    //! Array for storing intermediate data
} fweuler;

//! "Constructor" for forward-Euler integrator
fweuler * fweuler_new(int, double, double, double [],
                      double * (*)(double, double[]), int, int, FILE *);

//! Prints state at time t
void fweuler_print_state(fweuler *);

//! Writes state at time t to file
void fweuler_write_state(fweuler *);

//! Integrates system over one timestep
void fweuler_step(fweuler *);

//! Integrates system over multiple timesteps
void fweuler_integrate(fweuler *, int);

#endif /* FWEULER.H */
