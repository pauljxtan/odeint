#ifndef BULSTO_H
#define BULSTO_H

/*! @file */

//! A Bulirsch-Stoer integrator
typedef struct bulsto {
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
    //! Target accuracy
    double delta;
    //! Verbose flag
    int verbose;
    //! Write flag
    int write;
    //! Output file pointer
    FILE * poutfile;
    //! Number of steps so far
    int n_steps;
    //! Array for storing intermediate data
    double * epsilon;
    //! Array for storing intermediate data
    double * X1;
    //! Array for storing intermediate data
    double * X2;
    //! Array for storing intermediate data
    double * X_inc;
    //! Array for storing intermediate data
    double t_step;
    //! Array for storing intermediate data
    double * X_step;
} bulsto;

//! "Constructor" for Bulirsch-Stoer integrator
bulsto * bulsto_new(int, double, double, double [],
                    double * (*)(double, double[]), double, int, int, FILE *);

//! Prints state at time t
void bulsto_print_state(bulsto *);

//! Writes state at time t to file
void bulsto_write_state(bulsto *);

//! Integrates system over one time step
void bulsto_step(bulsto *);

//! Integrates system over multiple timesteps
void bulsto_integrate(bulsto *, int);

#endif /* BULSTO_H */
