package ru.main;

import ru.lib.BinaryReader;
import ru.lib.DimensionReader;
import ru.lib.XmlReader;
import ru.lib.tm.TmDat;
import ru.lib.tm.TmWriter;

import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import java.io.*;
import java.util.HashMap;
import java.util.TreeSet;

public class Main {
    public static void main(String[] args) throws IOException, SAXException, ParserConfigurationException {
        if (args.length != 4)
            throw new RuntimeException("Usage: java <data_file> <data_bin_knp> <dimensions> <output>");

        String dataFile = args[0];
        String dataBinKMP = args[1];
        String dimensionsFile = args[2];
        String outputFile = args[3];

        HashMap<Integer, String> data = XmlReader.getData(dataFile);

        HashMap<Integer, String> dimensions = DimensionReader.readFrom(dimensionsFile);

        BinaryReader binaryReader = new BinaryReader(dataBinKMP, data, dimensions);
        TreeSet<TmDat> fields = new TreeSet<TmDat>();
        binaryReader.ParseKnpTo(fields);

        Writer outputFileWriter = new BufferedWriter(new FileWriter(outputFile));
        TmWriter.writeTo(outputFileWriter, fields);

        binaryReader.printStatistics();
    }
}
