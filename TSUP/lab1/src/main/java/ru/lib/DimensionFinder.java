package ru.lib;

import java.util.HashMap;

public class DimensionFinder {

    public static String find(HashMap<Integer, String> dimensions, int key) {
        if (dimensions == null)
            return "";

        String res = dimensions.get(key);
        if (res == null)
            return "";
        
        return res;

    }

}
