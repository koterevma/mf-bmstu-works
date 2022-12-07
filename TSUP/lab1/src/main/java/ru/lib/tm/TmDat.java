package ru.lib.tm;


public class TmDat implements Comparable<TmDat> {
    public TmDat(String paramName, int time, String razm, int attr) {
        this.name = paramName;
        this.time = time;
        this.razm = razm;
        this.attr = attr;
    }

    @Override
    public int compareTo(TmDat other) {
        if(this.name.compareTo(other.name) == 0)
            return 1;
        return name.compareTo(other.name);
    }

    private short paramNum;
    private int time;
    private String name;
    private String razm;
    private int attr;
    private int type;

    @Override
    public String toString() {
        String res = String.join(
                "\t",
                name,
                Integer.toString(time),
                razm,
                Integer.toHexString(attr)
            );
        return res;
    }

	public short getParamNum() {
		return paramNum;
	}

	public int getTime() {
		return time;
	}

	public String getName() {
		return name;
	}

	public String getRazm() {
		return razm;
	}

	public int getAttr() {
		return attr;
	}

	public int getType() {
		return type;
	}
}

