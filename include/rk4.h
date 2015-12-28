#ifndef RK4_H
#define RK4_H

/*! @file */

/*! A classical (4th-order) Runge-Kutta integrator */
typedef struct rk4 {
    int n_vars;      /*! Number of spatial variables */
    double dt;       /*! Length of timestep */
    double t;        /*! Elapsed time */
    double * X;      /*! Current state (at time t) */
    double * (*F)(double, double []); /*! ODE vector function */
    int verbose;     /*! Verbose flag */
    int write;       /*! Write flag */
    FILE * poutfile; /*! Output file pointer */
    int n_steps;     /*! Number of steps so far */
    double * K1;     /*! Array for storing intermediate data */
    double * K2;     /*! Array for storing intermediate data */
    double * K3;     /*! Array for storing intermediate data */
    double * K4;     /*! Array for storing intermediate data */
    double t_inc;    /*! Array for storing intermediate data */
    double * X_inc;  /*! Array for storing intermediate data */
    double t_step;   /*! Array for storing intermediate data */
    double * X_step; /*! Array for storing intermediate data */
} rk4;

/*! Initializes a RK4 integrator */
rk4 * rk4_new(int, double, double, double [], double * (*)(double, double[]),
              int, int, FILE *);

/*! Prints state at time t */
void rk4_print_state(rk4 *);

/*! Writes state at time t to file */
void rk4_write_state(rk4 *);

/*! Integrates system over one timestep */
void rk4_step(rk4 *);

/*! Integrates system over multiple timesteps */
void rk4_integrate(rk4 *, int);

#endif /* RK4_H */
