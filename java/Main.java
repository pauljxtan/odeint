//import javax.swing.JFrame;
//import javax.swing.JPanel;

import odeint.EomTable;
import odeint.RK4;

public class Main {
    public static void main(String[] args) {
        if (args.length < 1)
            printUsage();

        else if (args[0].equalsIgnoreCase("list")) {
            String[] rows = EomTable.getStrs();
            for (String row : rows)
                System.out.println(row);
        }

        // TEMPORARY
        else if (args[0].equalsIgnoreCase("test")) {
            RK4 rk4 = new RK4("lorenz", 0.01, 0.0, new double[] {0.01, 0.01, 0.01});
            rk4.integrate(10000, true);
        }

        /*
        JFrame frame = new JFrame("ODE integrator");
        frame.setSize(640, 640);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
        */
    }

    static void printUsage() {
        // TODO
    }
}
