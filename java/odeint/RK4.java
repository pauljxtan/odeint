package odeint;

/**
 * A (non-adaptive) 4th-order Runge-Kutta integrator.
 */
public class RK4 extends OdeInt {
    public RK4(String system, double dt, double t0, double X0[]) {
        super(system, dt, t0, X0);
    }

    /** Performs a single integration step. */
    private void step(boolean verbose) {
        int i;
        double[] tmp = new double[X.length];

        // First increment
        double[] K1 = system.evaluate(t, X);
        for (i = 0; i < system.getNDims(); i++)
            K1[i] *= dt;

        // Second increment
        for (i = 0; i < system.getNDims(); i++)
            tmp[i] = X[i] + K1[i] / 2.0;
        double[] K2 = system.evaluate(t + dt / 2.0, tmp);
        for (i = 0; i < system.getNDims(); i++)
            K2[i] *= dt;

        // Third increment
        for (i = 0; i < system.getNDims(); i++)
            tmp[i] = X[i] + K2[i] / 2.0;
        double[] K3 = system.evaluate(t + dt / 2.0, tmp);
        for (i = 0; i < system.getNDims(); i++)
            K3[i] *= dt;

        // Fourth increment
        for (i = 0; i < system.getNDims(); i++)
            tmp[i] = X[i] + K3[i];
        double[] K4 = system.evaluate(t + dt, tmp);
        for (i = 0; i < system.getNDims(); i++)
            K4[i] *= dt;

        // Weighted average of increments
        for (i = 0; i < X.length; i++)
            X[i] += (K1[i] + 2.0 * K2[i] + 2.0 * K3[i] + K4[i]) / 6.0;

        t += dt;

        if (verbose)
            System.out.println(getTimeStateStr());
    }

    /** Performs multiple integration steps. */
    public void integrate(int nSteps, boolean verbose) {
        while (nSteps-- > 0)
            step(verbose);
    }
}
