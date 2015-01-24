/**
 * A (non-adaptive) 4th-order Runge-Kutta integrator.
 */
public class RK4 extends OdeInt {
    public RK4(String system, double dt, double t0, double X0[]) {
        super(system, dt, t0, X0);
    }

    public void step() {
        int i;
        double[] XInc = new double[X.length];
        double[] XStep = new double[X.length];

        // First increment
        double[] K1 = system.evaluate(t, X);
        for (i = 0; i < K1.length; i++)
            K1[i] *= dt;

        // Second increment
        for (i = 0; i < XInc.length; i++)
            XInc[i] = X[i] + K1[i] / 2.0;
        double[] K2 = system.evaluate(t + dt / 2.0, XInc);
        for (i = 0; i < K2.length; i++)
            K2[i] *= dt;

        // Third increment
        for (i = 0; i < XInc.length; i++)
            XInc[i] = X[i] + K2[i] / 2.0;
        double[] K3 = system.evaluate(t + dt / 2.0, XInc);
        for (i = 0; i < K3.length; i++)
            K3[i] *= dt;

        // Fourth increment
        for (i = 0; i < XInc.length; i++)
            XInc[i] = X[i] + K3[i];
        double[] K4 = system.evaluate(t + dt, XInc);
        for (i = 0; i < K4.length; i++)
            K4[i] *= dt;

        // Weighted average of increments
        for (i = 0; i < XStep.length; i++)
            X[i] += (K1[i] + 2.0 * K2[i] + 2.0 * K3[i] + K4[i]) / 6.0;

        t += dt;
    }
}
