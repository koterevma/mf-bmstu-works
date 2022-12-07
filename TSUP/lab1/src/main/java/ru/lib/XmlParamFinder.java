package ru.lib;

import java.util.HashMap;

public class XmlParamFinder {
    public static String find(int number, HashMap<Integer, String> parameters)
    {
        if (parameters == null) {
            return "";
        }

        return parameters.getOrDefault(number, "");
    }
}
