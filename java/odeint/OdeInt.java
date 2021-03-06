package odeint;

/**
 * A generic ODE integrator base class.
 */
class OdeInt {
    /** The system to integrate. */
    Eom system;

    /** The length of each integration step. */
    double dt;

    /** The time elapsed in the simulation.
     *  (Bit of a misnomer, since we don't necessarily integrate over time)
     */
    double t;

    /** The system state vector. */
    double[] X;

    /** The constants in the equations of motion. */
    double[] C;

    /**
     * A constructor for using default constants.
     * (Note: zero initial conditions can cause some systems to get stuck at
     * the origin, so it's required to set them.)
     */
    OdeInt(String system, double dt, double t0, double[] X0) {
        this.dt = dt;
        this.t = t0;
        this.X = X0;

        //========== Add new mappings here ==========
        if (system.equals("lorenz")) this.system = new Lorenz();
        //===========================================
    }

    /**
     * A constructor for using specified constants.
     * (Note: zero initial conditions can cause some systems to get stuck at
     * the origin, so it's required to set them.)
     */
    OdeInt(String system, double dt, double t0, double[] X0, double[] C) {
        this.dt = dt;
        this.t = t0;
        this.X = X0;
        this.C = C;

        //========== Add new mappings here ==========
        if (system.equals("lorenz")) this.system = new Lorenz(C);
        //===========================================
    }
    
    /** Returns the elapsed time. */
    double getTime() {
        return t;
    }

    /** Returns the system state. */
    double[] getState() {
        return X;
    }

    /** Returns the string-formatted time and system state. */
    public String getTimeStateStr() {
        String str = String.format("%.6f ", t);
        for (int i = 0; i < X.length - 1; i++)
            str += String.format("%.6f ", X[i]);
        str += String.format("%.6f ", X[X.length - 1]);
        return str;
    }
}
