package odeint;

/**
 * The Lorenz system. The equations are:
 *
 * dx/dt = sigma * (y - x)
 * dy/dt = x * (rho - z) - y
 * dz/dt = x * y - beta * z
 */
class Lorenz implements Eom {
    /** The number of dimensions in this system. */
    private static final int N_DIMS = 3;

    /** The number of constants in the system of ODEs. */
    private static final int N_CONSTS = 3;

    /** The default value for the constant sigma. */
    private static final double SIGMA_DEFAULT = 10.0;
    
    /** The default value for the constant rho. */
    private static final double RHO_DEFAULT = 28.0;
    
    /** The default value for the constant sigma. */
    private static final double BETA_DEFAULT = 8.0 / 3.0;

    /** The constant sigma. */
    private final double SIGMA;

    /** The constant rho. */
    private final double RHO;

    /** The constant beta. */
    private final double BETA;

    /** A constructor for using default constants. */
    Lorenz() {
        SIGMA = SIGMA_DEFAULT;
        RHO = RHO_DEFAULT;
        BETA = BETA_DEFAULT;
    }
    
    /** A constructor for using specified constants. */
    Lorenz(double[] C) {
        SIGMA = C[0];
        RHO = C[1];
        BETA = C[2];
    }

    public int getNDims() {
        return N_DIMS;
    }

    public int getNConsts() {
        return N_CONSTS;
    }

    public double[] evaluate(double t, double[] X) {
        double x = X[0], y = X[1], z = X[2];

        double x_dot = SIGMA * (y - x);
        double y_dot = x * (RHO - z) - y;
        double z_dot = x * y - BETA * z;

        return new double[] {x_dot, y_dot, z_dot};
    }
}
