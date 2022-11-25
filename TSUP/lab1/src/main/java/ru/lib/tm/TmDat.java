package ru.lib.tm;

public class TmDat implements Comparable<TmDat> {

    @Override
    public int compareTo(TmDat other) {
        if(this.name.compareTo(other.name) == 0)
            return 1;
        return name.compareTo(other.name);
    }

    int num;
    String name;
    long time;
    String razm;
    int attr;
    int type;

    @Override
    public String toString() {
        return "";
    }
}

