#ifndef RK4_H
#define RK4_H

/*! @file */

//! A classical (4th-order) Runge-Kutta integrator
typedef struct rk4 {
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
    double * K1;
    //! Array for storing intermediate data
    double * K2;
    //! Array for storing intermediate data
    double * K3;
    //! Array for storing intermediate data
    double * K4;
    //! Array for storing intermediate data
    double t_inc;
    //! Array for storing intermediate data
    double * X_inc;
    //! Array for storing intermediate data
    double t_step;
    //! Array for storing intermediate data
    double * X_step;
} rk4;

//! "Constructor" for RK4 integrator
rk4 * rk4_new(int, double, double, double [], double * (*)(double, double[]),
              int, int, FILE *);

//! Prints state at time t
void rk4_print_state(rk4 *);

//! Writes state at time t to file
void rk4_write_state(rk4 *);

//! Integrates system over one timestep
void rk4_step(rk4 *);

//! Integrates system over multiple timesteps
void rk4_integrate(rk4 *, int);

#endif /* RK4_H */
