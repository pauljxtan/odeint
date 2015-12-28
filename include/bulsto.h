#ifndef BULSTO_H
#define BULSTO_H

/*! @file */

/*! A Bulirsch-Stoer integrator */
typedef struct bulsto {
    int n_vars;       /*! Number of spatial variables */
    double dt;        /*! Length of timestep */
    double t;         /*! Elapsed time */
    double * X;       /*! Current state (at time t) */
    double * (*F)(double, double []); /*! ODE vector function */
    double delta;     /*! Target accuracy */
    int verbose;      /*! Verbose flag */
    int write;        /*! Write flag */
    FILE * poutfile;  /*! Output file pointer */
    int n_steps;      /*! Number of steps so far */
    double * epsilon; /*! Array for storing intermediate data */
    double * X1;      /*! Array for storing intermediate data */
    double * X2;      /*! Array for storing intermediate data */
    double * X_inc;   /*! Array for storing intermediate data */
    double t_step;    /*! Array for storing intermediate data */
    double * X_step;  /*! Array for storing intermediate data */
} bulsto;

/*! Initializes a Bulirsch-Stoer integrator */
bulsto * bulsto_new(int, double, double, double [],
                    double * (*)(double, double[]), double, int, int, FILE *);

/*! Prints state at time t */
void bulsto_print_state(bulsto *);

/*! Writes state at time t to file */
void bulsto_write_state(bulsto *);

/*! Integrates system over one time step */
void bulsto_step(bulsto *);

/*! Integrates system over multiple timesteps */
void bulsto_integrate(bulsto *, int);

#endif /* BULSTO_H */
