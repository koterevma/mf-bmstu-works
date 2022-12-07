package ru.lib;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.stream.Stream;

public class DimensionReader {
    static public HashMap<Integer, String> readFrom(String filename) throws IOException {
        HashMap<Integer, String> result = new HashMap<Integer, String>();
        BufferedReader inputFile = new BufferedReader(new FileReader(filename));
        var wrapper = new Object() { int key = 1; };

        try (Stream<String> lines = inputFile.lines()) {
            lines.forEach(line->{if (!line.isEmpty()) result.put(wrapper.key, line); wrapper.key++; });
        }

        inputFile.close();

        return result;
    }
}
