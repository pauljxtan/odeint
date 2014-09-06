#ifndef RK4_H
#define RK4_H

/* rk4: A classical (4th-order) Runge-Kutta integrator */
typedef struct rk4 {
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
    double * K1;
    double * K2;
    double * K3;
    double * K4;
    double t_inc;
    double * X_inc;
    double t_step;
    double * X_step;
} rk4;

/* rk4_new: "Constructor" for RK4 integrator */
rk4 * rk4_new(int, double, double, double [], double * (*)(double, double[]),
              int, int, FILE *);

/* rk4_print_state: Print the state at time t */
void rk4_print_state(rk4 *);

/* rk4_write_state: Write the state at time t to file */
void rk4_write_state(rk4 *);

/* rk4_step: Integrate over one timestep */
void rk4_step(rk4 *);

/* rk4_integrate: Integrate over multiple timesteps */
void rk4_integrate(rk4 *, int);

#endif /* RK4_H */
