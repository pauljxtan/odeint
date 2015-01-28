/**
 * The Lorenz system. The equations are:
 *
 * dx/dt = sigma * (y - x)
 * dy/dt = x * (rho - z) - y
 * dz/dt = x * y - beta * z
 */
public class Lorenz implements Eom {
    /** The number of dimensions in this system. */
    public final int N_DIMS = 3;

    /** The number of constants in the system of ODEs. */
    public final int N_CONSTS = 3;

    /** The constant sigma. */
    private final double SIGMA;

    /** The constant rho. */
    private final double RHO;

    /** The constant beta. */
    private final double BETA;

    /** A constructor for using default constants. */
    public Lorenz() {
        SIGMA = 10.0;
        RHO = 28.0;
        BETA = 8.0 / 3.0;
    }
    
    /** A constructor for using specified constants. */
    public Lorenz(double[] C) {
        SIGMA = C[0];
        RHO = C[1];
        BETA = C[2];
    }

    @Override
    public double[] evaluate(double t, double[] X) {
        double x = X[0], y = X[1], z = X[2];

        double x_dot = SIGMA * (y - x);
        double y_dot = x * (RHO - z) - y;
        double z_dot = x * y - BETA * z;

        return new double[] {x_dot, y_dot, z_dot};
    }
}
