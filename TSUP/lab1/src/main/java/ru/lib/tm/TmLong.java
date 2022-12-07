package ru.lib.tm;

public class TmLong extends TmDat {

	public TmLong(String paramName, int time, String razm, int attr, int value) {
		super(paramName, time, razm, attr);
        this.value = value;
	}

    @Override
    public String toString() {
        String result = super.toString();
        return result + "\t" + Integer.toString(this.value);
    }

    private int value;

}
