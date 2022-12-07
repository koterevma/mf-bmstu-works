package ru.lib.tm;

import java.io.IOException;
import java.io.Writer;
import java.util.TreeSet;

public class TmWriter {
    public static void writeTo(Writer writer, TreeSet<TmDat> fields) {
        System.out.println("I am writing " + fields.size() + " fields!");
        for (TmDat field: fields) {
            try {
                writer.write(field.toString() + '\n');
            } catch (IOException e) {
                System.out.println("While writing to file: " + e);
            }
        }

        try {
            writer.flush();
        } catch (IOException e) {
            System.out.println("Ну " + e + ", и " + e);
        }
    }
}
