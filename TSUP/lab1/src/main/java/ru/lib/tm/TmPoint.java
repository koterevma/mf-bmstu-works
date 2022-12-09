package ru.lib.tm;

import java.util.HexFormat;

public class TmPoint extends TmDat {

	public TmPoint(String paramName, int time, String razm, int type, short elementSize, byte[] code) {
		super(paramName, time, razm, type);
        this.elementSize = elementSize;
        this.code = code;
	}

    @Override
    public String toString() {
        String result = super.toString();
        HexFormat hexFormat = HexFormat.of();
        return result + "\t" + Short.toString(this.elementSize) + " - " + hexFormat.formatHex(this.code);
    }


	private short elementSize;
	private byte[] code;

}
