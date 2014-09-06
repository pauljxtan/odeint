#ifndef BULSTO_H
#define BULSTO_H

/* bulsto: A Bulirsch-Stoer integrator */
typedef struct bulsto {
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
    /* Target accuracy */
    double delta;
    /* Verbose flag */
    int verbose;
    /* Write flag */
    int write;
    /* Output file pointer */
    FILE * poutfile;
    /* Number of steps so far */
    int n_steps;
    /* Arrays for storing intermediate data */
    double * epsilon;
    double * X1;
    double * X2;
    double * X_inc;
    double t_step;
    double * X_step;
} bulsto;

/* bulsto_new: "Constructor" for Bulirsch-Stoer integrator */
bulsto * bulsto_new(int, double, double, double [],
                    double * (*)(double, double[]), double, int, int, FILE *);

/* bulsto_print_state: Print state at time t */
void bulsto_print_state(bulsto *);

/* bulsto_write_state: Write state at time t to file */
void bulsto_write_state(bulsto *);

/* bulsto_step: Integrate over one timestep */
void bulsto_step(bulsto *);

/* bulsto_integrate: Integrate over multiple timesteps */
void bulsto_integrate(bulsto *, int);

#endif /* BULSTO_H */
