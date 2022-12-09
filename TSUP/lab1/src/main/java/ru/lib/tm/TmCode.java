package ru.lib.tm;

public class TmCode extends TmDat {

	public TmCode(String paramName, int time, String razm, int type, short codeLength, int code) {
		super(paramName, time, razm, type);
        this.codeLength = codeLength;
        this.code = code;
	}

    @Override
    public String toString() {
        String result = super.toString();
        return result + "\t" + Short.toString(this.codeLength) + " - " +String.format("%8s", Integer.toBinaryString(code)).replace(' ', '0');
    }


	private short codeLength;
	private int code;

}
