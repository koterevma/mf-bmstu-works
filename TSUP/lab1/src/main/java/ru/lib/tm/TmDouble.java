package ru.lib.tm;

public class TmDouble extends TmDat {

	public TmDouble(String paramName, int time, String razm, byte attr, double value) {
		super(paramName, time, razm, attr);
        this.value = value;
	}

    @Override
    public String toString() {
        String result = super.toString();
        return result + "\t" + Double.toString(this.value);
    }


    private double value;
}
