package ru.lib.tm;

import java.text.SimpleDateFormat;
import java.time.LocalTime;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeFormatterBuilder;
import java.time.format.FormatStyle;

public class TmDat implements Comparable<TmDat> {
    public TmDat(String paramName, int time, String razm, int type) {
        this.name = paramName;
        this.time = time;
        this.razm = razm;
        this.type = type;
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
        DateTimeFormatter timeFormatter = DateTimeFormatter.ISO_TIME;
        LocalTime localTime = LocalTime.ofSecondOfDay(time / 1000);
        String res = String.join(
                "\t",
                name,
                localTime.format(timeFormatter) + "," + time % 1000,
                razm,
                Integer.toHexString(type)
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

