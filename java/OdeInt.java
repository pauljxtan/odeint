/**
 * A generic integrator base class.
 */
public class OdeInt {
    protected Eom system;
    protected double dt;
    protected double t;
    protected double[] X;
    protected double[] C;

    /**
     * A constructor for using default constants.
     * (Note: zero initial conditions cause some systems to get stuck at the
     * origin, so it's required to set them.)
     */
    public OdeInt(String system, double dt, double t0, double X0[]) {
        this.dt = dt;
        this.t = t0;
        this.X = X0;

        //========== Add new mappings here ==========
        if (system.equals("lorenz")) this.system = new Lorenz();
        //===========================================
    }

    /**
     * Returns the elapsed time.
     */
    public double getTime() {
        return t;
    }

    /**
     * Returns the system state.
     */
    public double[] getState() {
        return X;
    }

    /**
     * Returns the string-formatted time and system state.
     */
    public String getTimeStateStr() {
        String str = String.format("%.6f ", t);
        for (int i = 0; i < X.length - 1; i++)
            str += String.format("%.6f ", X[i]);
        str += String.format("%.6f ", X[X.length - 1]);
        return str;
    }
}