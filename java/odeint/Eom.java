package odeint;

/**
 * Describes any class containing equations of motion (i.e. a system of ODEs)
 * as input for the integrator.
 */
interface Eom {
    /** Returns the number of dimensions in the system. */
    int getNDims();

    /** Returns the number of constants in the system. */
    int getNConsts();

    /** Evaluates the system of ODEs. */
    double[] evaluate(double t, double[] X);
}
