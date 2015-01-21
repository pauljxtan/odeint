/**
 * The equations of motion.
 */
public class Eoms {
    /**
     * The Brusselator.
     */
    public static double[] brusselator(double t, double[] X) {
        double x = X[0], y = X[1];
        
        double x_dot = 1.0 - (Const.BRUSS_B + 1.0) * x
                       + Const.BRUSS_A * Math.pow(x, 2) * y;
        double y_dot = Const.BRUSS_B * x - Const.BRUSS_A * Math.pow(x, 2) * y;

        return new double[] {x_dot, y_dot};
    }

    /**
     * The Chen system.
     */
    public static double[] chen(double t, double[] X) {
        double x = X[0], y = X[1], z = X[2];

        double x_dot = Const.CHEN_A * (y - x);
        double y_dot = (Const.CHEN_C - Const.CHEN_A) * x - x * z
                       + Const.CHEN_C * y;
        double z_dot = x * y - Const.CHEN_B * z;

        return new double[] {x_dot, y_dot, z_dot};
    }

    /**
     * The damped spring.
     */
    public static double[] dampedSpring(double t, double[] X) {
        double x = X[0], v = X[1];

        double x_dot = v;
        double v_dot = -Const.DAMPSPR_K * x - Const.DAMPSPR_C * v;

        return new double[] {x_dot, v_dot};
    }

    /**
     * The double pendulum.
     */
    public static double[] doublePendulum(double t, double[] X) {
        double theta_1 = X[0], theta_2 = X[1], p_1 = X[2], p_2 = X[3];


        double theta_dot_1 = 6.0 / Const.DOUPEND_M
                             / Math.pow(Const.DOUPEND_L, 2)
                             * (2 * p_1 - 3 * Math.cos(theta_1 - theta_2)
                             * p_2) / (16 - 9 * Math.pow(Math.cos(theta_1
                             - theta_2), 2));
        double theta_dot_2 = 6.0 / Const.DOUPEND_M
                             / Math.pow(Const.DOUPEND_L, 2) * (8 * p_2 - 3
                             * Math.cos(theta_1 - theta_2) * p_1) / (16 - 9
                             * Math.pow(Math.cos(theta_1 - theta_2), 2));
        double p_dot_1 = - 1.0 / 2 * Const.DOUPEND_M
                         * Math.pow(Const.DOUPEND_L, 2) * (theta_dot_1
                         * theta_dot_2 * Math.sin(theta_1 - theta_2) + 3
                         * Const.DOUPEND_G / Const.DOUPEND_L
                         * Math.sin(theta_1));
        double p_dot_2 = - 1.0 / 2 * Const.DOUPEND_M
                         * Math.pow(Const.DOUPEND_L, 2) * (- theta_dot_1
                         * theta_dot_2 * Math.sin(theta_1 - theta_2)
                         + Const.DOUPEND_G / Const.DOUPEND_L
                         * Math.sin(theta_2));

        return new double[] {theta_dot_1, theta_dot_2, p_dot_1, p_dot_2};
    }

    /**
     * The Duffing equation.
     */
    public static double[] duffing(double t, double[] X) {
        double x = X[0], v = X[1];

        double x_dot = v;
        double v_dot = Const.DUFFING_GAMMA * Math.cos(Const.DUFFING_OMEGA * t)
                       - Const.DUFFING_DELTA * v - Const.DUFFING_ALPHA * x
                       - Const.DUFFING_BETA * Math.pow(x, 3);

        return new double[] {x_dot, v_dot};
    }

    /**
     * The Lorenz system.
     */
    public static double[] lorenz(double t, double[] X) {
        double x = X[0], y = X[1], z = X[2];

        double x_dot = Const.LORENZ_SIGMA * (y - x);
        double y_dot = x * (Const.LORENZ_RHO - z) - y;
        double z_dot = x * y - Const.LORENZ_BETA * z;

        return new double[] {x_dot, y_dot, z_dot};
    }

    /**
     * The Lotka-Volterra equations.
     */
    public static double[] lotka(double t, double[] X) {
        double x = X[0], y = X[1];

        double x_dot = x * (Const.LOTKA_ALPHA - Const.LOTKA_BETA * y);
        double y_dot = - y * (Const.LOTKA_GAMMA - Const.LOTKA_DELTA * x);

        return new double[] {x_dot, y_dot};
    }

    /**
     * The Parrot system.
     */
    public static double[] parrot(double t, double[] X) {
        double x = X[0], y = X[1];

        double x_dot = y + Math.pow(y, 2);
        double y_dot = - x + 0.2 * y - x * y + 1.2 * Math.pow(y, 2);

        return new double[] {x_dot, y_dot};
    }

    /**
     * The Rossler system.
     */
    public static double[] rossler(double t, double[] X) {
        double x = X[0], y = X[1], z = X[2];
    
        double x_dot = - y - z;
        double y_dot = x + Const.ROSSLER_A * y;
        double z_dot = Const.ROSSLER_B + z * (x - Const.ROSSLER_C);

        return new double[] {x_dot, y_dot, z_dot};
    }

    /**
     * The symmetric top.
     */
    public static double[] symmetricTop(double t, double[] X) {
        double theta = X[0], phi = X[1], psi = X[2];
        double theta_dot = X[3], phi_dot = X[4], psi_dot = X[5];

        //double theta_dot = theta_dot;
        //double phi_dot = phi_dot;
        //double psi_dot = psi_dot;
        double theta_ddot = (Math.pow(phi_dot, 2) * Math.sin(theta)
                            * Math.cos(theta) * (Const.SYMTOP_I_1
                            - Const.SYMTOP_I_3) - Const.SYMTOP_I_3 * phi_dot
                            * psi_dot * Math.sin(theta) + Const.SYMTOP_M
                            * Const.SYMTOP_G * Const.SYMTOP_L
                            * Math.sin(theta)) / Const.SYMTOP_I_1;
        double phi_ddot = (2 * (Const.SYMTOP_I_3 - Const.SYMTOP_I_1) * phi_dot
                          * theta_dot * Math.sin(theta) * Math.cos(theta)
                          - Const.SYMTOP_I_3 * phi_dot * theta_dot
                          * Math.sin(theta) * Math.cos(theta)
                          + Const.SYMTOP_I_3 * psi_dot * theta_dot
                          * Math.sin(theta) ) / ( Const.SYMTOP_I_1
                          * Math.pow(Math.sin(theta), 2));
        double psi_ddot = (Math.cos(theta) * ((Const.SYMTOP_I_1
                          * Math.pow(Math.sin(theta), 2) + Const.SYMTOP_I_3
                          * Math.pow(Math.cos(theta), 2)) * phi_dot
                          * theta_dot * Math.sin(theta) / Math.cos(theta)
                          - 2 * (Const.SYMTOP_I_3 - Const.SYMTOP_I_1)
                          * phi_dot * theta_dot * Math.sin(theta)
                          * Math.cos(theta) - Const.SYMTOP_I_3 * psi_dot
                          * theta_dot * Math.sin(theta))) / (Const.SYMTOP_I_1
                          * Math.pow(Math.sin(theta), 2));

        return new double[] {theta_dot, phi_dot, psi_dot,
                             theta_ddot, phi_ddot, psi_ddot};
    }

    /**
     * The Van der Pol oscillator.
     */
    public static double[] vanderpol(double t, double[] X) {
        double x = X[0], v = X[1];

        double x_dot = v;
        double v_dot = Const.VANDERPOL_MU * (1 - Math.pow(x, 2)) * v - x;

        return new double[] {x_dot, v_dot};
    }

    /**
     * The 2D Van der Pol oscillator.
     */
    public static double[] vanderpol2d(double t, double[] X) {
        double x = X[0], y = X[1];

        double x_dot = Const.VANDERPOL_MU * (x - 1.0 / 3 * Math.pow(x, 3) - y);
        double y_dot = 1.0 / Const.VANDERPOL_MU * x;

        return new double[] {x_dot, y_dot};
    }
}
