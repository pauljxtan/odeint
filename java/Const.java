/**
 * The constants in the equation of motions.
 */
public class Const {
    //---- Brusselator
    public static final double BRUSS_A = 1.0;
    public static final double BRUSS_B = 3.0;
    //----

    //---- Chen system
    public static final double CHEN_A = 40.0;
    public static final double CHEN_B = 3.0; 
    public static final double CHEN_C = 28.0;
    //----

    //----Damped spring
    // Spring constant
    public static final double DAMPSPR_K = 1.0;
    // Damping coefficient
    public static final double DAMPSPR_C = -0.005;
    //----

    //---- Double pendulum
    // Mass
    public static final double DOUPEND_M = 1.0;
    // Gravitational acceleration
    public static final double DOUPEND_G = 1.0;
    // Length
    public static final double DOUPEND_L = 1.0;
    //----

    //---- Duffing system
    // Damping
    public static final double DUFFING_DELTA = 0.2;
    // Stiffness
    public static final double DUFFING_ALPHA = 2.75;
    // Amount of non-linearity in restoring force
    public static final double DUFFING_BETA = 0.2;
    // Amplitude of driving force
    public static final double DUFFING_GAMMA = 0.3;
    // Frequency of driving force
    public static final double DUFFING_OMEGA = 1.0;
    //----

    //---- Lorenz system
    public static final double LORENZ_RHO = 28.0;
    public static final double LORENZ_SIGMA = 10.0;
    public static final double LORENZ_BETA = 8.0 / 3.0;
    //----

    //---- Lotka-Volterra equations
    public static final double LOTKA_ALPHA = 1.5;
    public static final double LOTKA_BETA = 1.0;
    public static final double LOTKA_GAMMA = 2.0;
    public static final double LOTKA_DELTA = 1.0;
    //----
    
    //---- Rossler system
    public static final double ROSSLER_A = 0.2;
    public static final double ROSSLER_B = 0.2;
    public static final double ROSSLER_C = 5.7;
    //----
    
    //---- Symmetric top
    // Mass
    public static final double SYMTOP_M = 1.0;
    // Gravitational acceleration
    public static final double SYMTOP_G = 1.0;
    // Length
    public static final double SYMTOP_L = 1.0;
    // Radius
    public static final double SYMTOP_R = 1.0;

    // Moments of inertia
    public static final double SYMTOP_I_1 = 3.0 / 20 * SYMTOP_M
                                            * (Math.pow(SYMTOP_R, 2)
                                            + (Math.pow(SYMTOP_L, 2) / 4));
    public static final double SYMTOP_I_3 = 3 / (SYMTOP_M
                                            * Math.pow(SYMTOP_R, 2));
    //----

    //---- Van der Pol oscillator
    // Nonlinearity and strength of damping
    public static final double VANDERPOL_MU = 4.0;
    //----
}
