package ru.main;

import ru.lib.BinaryReader;
import ru.lib.XmlParamElement;
import ru.lib.XmlReader;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException, SAXException, ParserConfigurationException {
        if (args.length > 3 || args.length < 2)
            throw new RuntimeException("Usage: java <data_file> <data_bin_knp> [output]");

        String dataFile = args[0];
        XmlParamElement[] data = XmlReader.getData(dataFile);
        System.out.println("DATA LENGTH: " + data.length);

        String dataBinKMP = args[1];
        String output = args[2];
        BinaryReader binaryReader = new BinaryReader(dataBinKMP, output, data);
        binaryReader.readAndWrite();
    }
}
