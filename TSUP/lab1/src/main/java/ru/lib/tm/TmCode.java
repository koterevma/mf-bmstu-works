package ru.lib.tm;

public class TmCode extends TmDat {

	public TmCode(String paramName, int time, String razm, byte attr, short codeLength, int code) {
		super(paramName, time, razm, attr);
        this.codeLength = codeLength;
        this.code = code;
	}

    @Override
    public String toString() {
        String result = super.toString();
        return result + "\t" + Short.toString(this.codeLength) + " - " + Integer.toString(code);
    }


	private short codeLength;
	private int code;

}
