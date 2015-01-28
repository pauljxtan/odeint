package odeint;

public final class EomTable {
    public static final EomInfo[] TABLE = {
        new EomInfo("lorenz", 3, 3, new String[] {"sigma", "rho", "beta"}),
        new EomInfo("FAKE", 3, 3, new String[] {"A", "B", "C"})
    };

    public static String[] getStrs() {
        String[] strs = new String[TABLE.length];
        for (int i = 0; i < TABLE.length; i++)
            strs[i] = TABLE[i].toString();
        return strs;
    }

    static class EomInfo {
        private String name;
        private int nDims;
        private int nConsts;
        private String[] constNames;

        EomInfo(String name, int nDims, int nConsts, String[] constNames) {
            this.name = name;
            this.nDims = nDims;
            this.nConsts = nConsts;
            this.constNames = constNames;
        }

        public String toString() {
            String str = "" + name + ", " + nDims + ", " + nConsts + ", {";
            for (int i = 0; i < constNames.length - 1; i++)
                str += constNames[i] + ", ";
            str += constNames[constNames.length - 1] + "}";
            return str;
        }
    }
}
