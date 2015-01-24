/**
 * A generic integrator base class.
 */
public class OdeInt {
    public Eom system;
    public double dt;
    public double t;
    public double[] X;
    public double[] C;

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
}
