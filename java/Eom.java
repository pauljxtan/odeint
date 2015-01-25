/**
 * Describes any class containing equations of motion (i.e. a system of ODEs)
 * as input for the integrator.
 */
public interface Eom {
    /**
     * Evaluates the system of ODEs.
     */
    double[] evaluate(double t, double[] X);
}
