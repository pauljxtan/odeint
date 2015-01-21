/* Equations of motion for various systems, expressed as vector functions. */

#include <stdlib.h>
#include <math.h>
#include "eoms.h"

function_table func_table[] = {
    {"brusselator", 2, brusselator},
    {"chen", 3, chen},
    {"damped_spring", 2, damped_spring},
    {"double_pendulum", 4, double_pendulum},
    {"duffing", 2, duffing},
    {"lorenz", 3, lorenz},
    {"lotka", 2, lotka},
    {"rossler", 3, rossler},
    {"parrot", 2, parrot},
    {"symmetric_top", 6, symmetric_top},
    {"vanderpol", 2, vanderpol},
    {"vanderpol2d", 2, vanderpol2d}
};

char * system_list = 
"\n"
"o Brusselator [brusselator]\n"
"----> 2 params: x, y\n"
"o Chen system [chen]\n"
"----> 3 params: x, y, z\n"
"o Damped spring [damped_spring]\n"
"----> 2 params: x, v\n"
"o Double pendulum [double_pendulum]\n"
"----> 4 params: theta_1, theta_2, p_1, p_2\n"
"o Duffing equation [duffing]\n"
"----> 2 params: x, v\n"
"o Lorenz system [lorenz]\n"
"----> 3 params: x, y, z\n"
"o Lotka-Volterra equations [lotka]\n"
"----> 2 params: x, y\n"
"o Parrot system [parrot]\n"
"----> 2 params: x, y\n"
"o Rossler system [rossler]\n"
"----> 3 params: x, y, z\n"
"o Symmetric top [symmetric_top]\n"
"----> 6 params: theta, phi, psi, theta_dot, phi_dot, psi_dot\n"
"o Van der Pol oscillator [vanderpol]\n"
"----> 2 params: x, v\n"
"o 2-D Van der Pol oscillator [vanderpol2d]\n"
"----> 2 params: x, y\n"
"\n";

/* brusselator: the Brusselator */
double * brusselator(double t, double X[]) {
    double x = X[0], y = X[1];
    double x_dot, y_dot;
    double * X_dot = malloc(2 * sizeof(double));

    x_dot = 1.0 - (BRUSS_B + 1.0) * x + BRUSS_A * pow(x, 2) * y;
    y_dot = BRUSS_B * x - BRUSS_A * pow(x, 2) * y;

    X_dot[0] = x_dot;
    X_dot[1] = y_dot;

    return X_dot;
}

/* chen: the Chen system */
double * chen(double t, double X[]) {
    double x = X[0], y = X[1], z = X[2];
    double x_dot, y_dot, z_dot;
    double * X_dot = malloc(3 * sizeof(double));
    
    x_dot = CHEN_A * (y - x);
    y_dot = (CHEN_C - CHEN_A) * x - x * z + CHEN_C * y;
    z_dot = x * y - CHEN_B * z;

    X_dot[0] = x_dot;
    X_dot[1] = y_dot;
    X_dot[2] = z_dot;

    return X_dot;
}

/* damped_spring: the damped spring */
double * damped_spring(double t, double X[]) {
    double x = X[0], v = X[1];
    double x_dot, v_dot;
    double * X_dot = malloc(2 * sizeof(double));

    x_dot = v;
    v_dot = -DAMPSPR_K * x - DAMPSPR_C * v;

    X_dot[0] = x_dot;
    X_dot[1] = v_dot;
    
    return X_dot;
}

/* TODO: these X_dots may need to be modified to separate m1, m2 */
/* double_pendulum: the double pendulum */
double * double_pendulum(double t, double X[]) {
    double theta_1 = X[0], theta_2 = X[1], p_1 = X[2], p_2 = X[3];
    double theta_dot_1, theta_dot_2, p_dot_1, p_dot_2;
    double * X_dot = malloc(4 * sizeof(double));

    theta_dot_1 = 6.0 / DOUPEND_M / pow(DOUPEND_L, 2)
                  * (2 * p_1 - 3 * cos(theta_1 - theta_2) * p_2)
                  / (16 - 9 * pow(cos(theta_1 - theta_2), 2));
    theta_dot_2 = 6.0 / DOUPEND_M / pow(DOUPEND_L, 2)
                  * (8 * p_2 - 3 * cos(theta_1 - theta_2) * p_1)
                  / (16 - 9 * pow(cos(theta_1 - theta_2), 2));
    p_dot_1 = - 1.0 / 2 * DOUPEND_M * pow(DOUPEND_L, 2)
              * (theta_dot_1 * theta_dot_2 * sin(theta_1 - theta_2)
                 + 3 * DOUPEND_G / DOUPEND_L * sin(theta_1));
    p_dot_2 = - 1.0 / 2 * DOUPEND_M * pow(DOUPEND_L, 2)
              * (- theta_dot_1 * theta_dot_2 * sin(theta_1 - theta_2)
                 + DOUPEND_G / DOUPEND_L * sin(theta_2));

    X_dot[0] = theta_dot_1;
    X_dot[1] = theta_dot_2;
    X_dot[2] = p_dot_1;
    X_dot[3] = p_dot_2;

    return X_dot;
}

/* duffing: the Duffing equation */
double * duffing(double t, double X[]) {
    double x = X[0], v = X[1];
    double x_dot, v_dot;
    double * X_dot = malloc(2 * sizeof(double));

    x_dot = v;
    v_dot = DUFFING_GAMMA * cos(DUFFING_OMEGA * t) - DUFFING_DELTA * v
             - DUFFING_ALPHA * x - DUFFING_BETA * pow(x, 3);

    X_dot[0] = x_dot;
    X_dot[1] = v_dot;

    return X_dot;
}

/* lorenz: the Lorenz system */
double * lorenz(double t, double X[]) {
    double x = X[0], y = X[1], z = X[2];
    double x_dot, y_dot, z_dot;
    double * X_dot = malloc(3 * sizeof(double));
    
    x_dot = LORENZ_SIGMA * (y - x);
    y_dot = x * (LORENZ_RHO - z) - y;
    z_dot = x * y - LORENZ_BETA * z;

    X_dot[0] = x_dot;
    X_dot[1] = y_dot;
    X_dot[2] = z_dot;

    return X_dot;
}

/* lotka: the Lotka-Volterra equations */
double * lotka(double t, double X[]) {
    double x = X[0], y = X[1];
    double x_dot, y_dot;
    double * X_dot = malloc(2 * sizeof(double));

    x_dot = x * (LOTKA_ALPHA - LOTKA_BETA * y);
    y_dot = - y * (LOTKA_GAMMA - LOTKA_DELTA * x);

    X_dot[0] = x_dot;
    X_dot[1] = y_dot;

    return X_dot;
}

/* parrot: the Parrot system */
double * parrot(double t, double X[]) {
    double x = X[0], y = X[1];
    double x_dot, y_dot;
    double * X_dot = malloc(2 * sizeof(double));

    x_dot = y + pow(y, 2);
    y_dot = - x + 0.2 * y - x * y + 1.2 * pow(y, 2);

    X_dot[0] = x_dot;
    X_dot[1] = y_dot;

    return X_dot;
}

/* rossler: the Rossler system */
double * rossler(double t, double X[]) {
    double x = X[0], y = X[1], z = X[2];
    double x_dot, y_dot, z_dot;
    double * X_dot = malloc(3 * sizeof(double));
    
    x_dot = - y - z;
    y_dot = x + ROSSLER_A * y;
    z_dot = ROSSLER_B + z * (x - ROSSLER_C);

    X_dot[0] = x_dot;
    X_dot[1] = y_dot;
    X_dot[2] = z_dot;

    return X_dot;
}
// symmetric_top: the spinning symmetric top
double * symmetric_top(double t, double X[]) {
    double theta = X[0];//, phi = X[1], psi = X[2],
    double theta_dot = X[3], phi_dot = X[4], psi_dot = X[5];
    double theta_ddot, phi_ddot, psi_ddot;
    double * X_dot = malloc(6 * sizeof(double));

    // Moments of inertia
    const double I_1 = 3.0 / 20 * SYMTOP_M * (pow(SYMTOP_R, 2) + (pow(SYMTOP_L, 2) / 4));
    const double I_3 = 3 / (SYMTOP_M * pow(SYMTOP_R, 2));

    //theta_dot = theta_dot;
    //phi_dot = phi_dot;
    //psi_dot = psi_dot;
    theta_ddot = (pow(phi_dot, 2) * sin(theta) * cos(theta) * (I_1 - I_3)
                  - I_3 * phi_dot * psi_dot * sin(theta)
                  + SYMTOP_M * SYMTOP_G * SYMTOP_L * sin(theta))
                 / I_1;
    phi_ddot = (2 * (I_3 - I_1) * phi_dot * theta_dot * sin(theta) * cos(theta)
                - I_3 * phi_dot * theta_dot * sin(theta) * cos(theta)
                + I_3 * psi_dot * theta_dot * sin(theta) )
               / ( I_1 * pow(sin(theta), 2));
    psi_ddot = (cos(theta)
                * ((I_1 * pow(sin(theta), 2) + I_3 * pow(cos(theta), 2))
                   * phi_dot * theta_dot * sin(theta)
                   / cos(theta)
                   - 2 * (I_3 - I_1) * phi_dot * theta_dot * sin(theta)
                       * cos(theta)
                   - I_3 * psi_dot * theta_dot * sin(theta)))
                / (I_1 * pow(sin(theta), 2));

    X_dot[0] = theta_dot;
    X_dot[1] = phi_dot;
    X_dot[2] = psi_dot;
    X_dot[3] = theta_ddot;
    X_dot[4] = phi_ddot;
    X_dot[5] = psi_ddot;
    
    return X_dot;
}

// vanderpol: the Van der Pol oscillator
double * vanderpol(double t, double X[]) {
    double x = X[0], v = X[1];
    double x_dot, v_dot;
    double * X_dot = malloc(2 * sizeof(double));
    
    x_dot = v;
    v_dot = VANDERPOL_MU * (1 - pow(x, 2)) * v - x;
    
    X_dot[0] = x_dot;
    X_dot[1] = v_dot;
    
    return X_dot;
}

// vanderpol2d: the Van der Pol oscillator (two-dimensional form)
double * vanderpol2d(double t, double X[]) {
    double x = X[0], y = X[1];
    double x_dot, y_dot;
    double * X_dot = malloc(2 *sizeof(double));
    
    x_dot = VANDERPOL_MU * (x - 1.0 / 3 * pow(x, 3) - y);
    y_dot = 1.0 / VANDERPOL_MU * x;
    
    X_dot[0] = x_dot;
    X_dot[1] = y_dot;
    
    return X_dot;
}
