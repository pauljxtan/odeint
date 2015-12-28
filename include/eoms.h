#ifndef EOMS_H
#define EOMS_H

/*! @file */

/* SET YOUR CONSTANTS HERE */

static const double BRUSS_A = 1.0; /*!< Brusselator: constant A */
static const double BRUSS_B = 3.0; /*!< Bruseelator: constant B */

static const double CHEN_A = 40.0; /*!< Chen system: constant a */
static const double CHEN_B = 3.0;  /*!< Chen system: constant b */
static const double CHEN_C = 28.0; /*!< Chen system: constant c */

static const double DAMPSPR_K = 1.0;    /*!< Damped spring: spring constant */
static const double DAMPSPR_C = -0.005; /*!< Damped spring: damping coefficient */

static const double DOUPEND_M = 1.0; /*!< Double pendulum: mass */
static const double DOUPEND_G = 1.0; /*!< Double pendulum: gravitational acceleration */
static const double DOUPEND_L = 1.0; /*!< Double pendulum: length */

static const double DUFFING_DELTA = 0.2;  /*!< Duffing equation: damping */
static const double DUFFING_ALPHA = 2.75; /*!< Duffing equation: stiffness */
static const double DUFFING_BETA = 0.2;   /*!< Duffing equation: amount of non-linearity in restoring force */
static const double DUFFING_GAMMA = 0.3; /*!< Duffing equation: amplitude of driving force */
static const double DUFFING_OMEGA = 1.0; /*!< Duffing equation: frequency of driving force */

static const double LORENZ_RHO = 28.0;       /*!< Lorenz system: constant rho */
static const double LORENZ_SIGMA = 10.0;     /*!< Lorenz system: constant sigma */
static const double LORENZ_BETA = 8.0 / 3.0; /*!< Lorenz system: constant beta */

static const double LOTKA_ALPHA = 1.5; /*!< Lotka-Volterra equations: constant alpha */
static const double LOTKA_BETA = 1.0;  /*!< Lotka-Volterra equations: constant beta */
static const double LOTKA_GAMMA = 2.0; /*!< Lotka-Volterra equations: constant gamma */
static const double LOTKA_DELTA = 1.0; /*!< Lotka-Volterra equations: constant delta */

static const double ROSSLER_A = 0.2; /*!< Rossler system: constant a */
static const double ROSSLER_B = 0.2; /*!< Rossler system: constant b */
static const double ROSSLER_C = 5.7; /*!< Rossler system: constant c */

static const double SYMTOP_M = 1.0; /*!< Symmetric top: mass */
static const double SYMTOP_G = 1.0; /*!< Symmetric top: gravitational acceleration */
static const double SYMTOP_L = 1.0; /*!< Symmetric top: length */
static const double SYMTOP_R = 1.0; /*!< Symmetric top: radius */

static const double VANDERPOL_MU = 4.0; /*!< Van der Pol oscillator: nonlinearity & strength of damping */

/*! The Brusselator */
double * brusselator(double, double []);
/*! The Chen system */
double * chen(double, double []);
/*! The damped spring */
double * damped_spring(double, double []);
/*! The double pendulum */
double * double_pendulum(double, double []);
/*! The Duffing equation */
double * duffing(double, double []);
/*! The Lorenz system */
double * lorenz(double, double []);
/*! The Lotka-Volterra equations */
double * lotka(double, double []);
/*! The parrot system */
double * parrot(double, double []);
/*! The Rossler system (Borelli & Coleman 1987) */
double * rossler(double, double []);
/*! The symmetric top */
double * symmetric_top(double, double []);
/*! The van der Pol oscillator */
double * vanderpol(double, double []);
/*! The 2-D van der Pol oscillator */
double * vanderpol2d(double, double []);

/*! Pointer type for ODE functions */
typedef double * (* func_ptr)(double, double[]);

/*! Stores system properties for easy access */
typedef struct function_table {
    char * name; /*!< Name of system */
    int n_vars;  /*!< Number of dimensions */
    func_ptr F;  /*!< Pointer to ODE function */
} function_table;

extern function_table func_table[]; /*!< Function table */

extern char * system_list; /*!< List of systems and their corresponding parameters */

#endif /* EOMS.H */
