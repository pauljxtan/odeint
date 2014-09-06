#ifndef EOMS_H
#define EOMS_H

/* define your constants here */

/* Brusselator */
static const double BRUSS_A = 1.0;
static const double BRUSS_B = 3.0;

/* Chen system */
static const double CHEN_A = 40.0;
static const double CHEN_B = 3.0;
static const double CHEN_C = 28.0;

/* damped spring */
static const double DAMPSPR_K = 1.0;  /* spring constant */
static const double DAMPSPR_C = -0.005; /* damping coefficient */

/* double pendulum */
static const double DOUPEND_M = 1.0; /* mass */
static const double DOUPEND_G = 1.0; /* gravitational acceleration */
static const double DOUPEND_L = 1.0; /* length */

/* Duffing equation */
static const double DUFFING_DELTA = 0.2; /* damping */
static const double DUFFING_ALPHA = 2.75; /* stiffness */
static const double DUFFING_BETA = 0.2;  /* amount of non-linearity
                                            in restoring force */
static const double DUFFING_GAMMA = 0.3; /* amplitude of driving force */
static const double DUFFING_OMEGA = 1.0; /* frequency of driving force */

/* Lorenz system */
static const double LORENZ_RHO = 28.0;
static const double LORENZ_SIGMA = 10.0;
static const double LORENZ_BETA = 8.0 / 3.0;

/* Lotka-Volterra equations */
static const double LOTKA_ALPHA = 1.5;
static const double LOTKA_BETA = 1.0;
static const double LOTKA_GAMMA = 2.0;
static const double LOTKA_DELTA = 1.0;

/* Rossler system */
static const double ROSSLER_A = 0.2;
static const double ROSSLER_B = 0.2;
static const double ROSSLER_C = 5.7;

/* Symmetric top */
static const double SYMTOP_M = 1.0; /* mass */
static const double SYMTOP_G = 1.0; /* gravitational acceleration */
static const double SYMTOP_L = 1.0; /* length */
static const double SYMTOP_R = 1.0; /* radius */

/* Van der Pol oscillator */
static const double VANDERPOL_MU = 4.0; /* nonlinearity & strength of damping */

double * brusselator(double, double []);
double * chen(double, double []);
double * damped_spring(double, double []);
double * double_pendulum(double, double []);
double * duffing(double, double []);
double * lorenz(double, double []);
double * lotka(double, double []);
double * parrot(double, double []);
double * rossler(double, double []);
double * symmetric_top(double, double []);
double * vanderpol(double, double []);
double * vanderpol2d(double, double []);

typedef double * (* func_ptr)(double, double[]);

typedef struct function_table {
    char * name;
    int n_vars;
    func_ptr F;
} function_table;

extern function_table func_table[];

extern char * system_list;

#endif /* EOMS.H */
