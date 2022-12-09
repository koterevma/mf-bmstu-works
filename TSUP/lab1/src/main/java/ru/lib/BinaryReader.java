package ru.lib;

import java.io.*;
import java.nio.MappedByteBuffer;
import java.nio.channels.FileChannel;
import java.util.HashMap;
import java.util.TreeSet;

import ru.lib.tm.*;

public class BinaryReader {

	public BinaryReader(String inputFilePath, HashMap<Integer, String>  xmlParamElements, HashMap<Integer, String> dimensions) throws IOException {
        RandomAccessFile file = new RandomAccessFile(new File(inputFilePath), "r");
        FileChannel channel = file.getChannel();
        this.buffer = channel.map(FileChannel.MapMode.READ_ONLY, 0, channel.size());

        this.dimensions = dimensions;
        this.xmlParamElements = xmlParamElements;
        this.statistics = new Statistics();
    }

    public void ParseKnpTo(TreeSet<TmDat> tmSet) {
        while (true) {
            try {
                int paramNum = this.buffer.getShort() & 0xFFFF;
                // if (paramNum < 0)
                int time = this.buffer.getInt();

                if (isSystemMessage(paramNum)) {
                    parseSystemMessage();
                    this.statistics.systemFieldsNum++;
                    continue;
                }
                if (paramNum > 8480) {
                    System.out.println("ERROR wrong paramNum");
                }

                int dimension = this.buffer.get() & 0xFF;
                String dimensionStr = DimensionFinder.find(this.dimensions, dimension);
                int attributeAndValueType = this.buffer.get() & 0xFF;

                int valueType = attributeAndValueType & 0xF;

                TmDat field;
                switch (valueType) {
                    case 0:  // Long
                        this.buffer.getInt(); // Skip
                        int longValue = this.buffer.getInt();
                        field = new TmLong(
                                XmlParamFinder.find(paramNum, this.xmlParamElements),
                                time, 
                                dimensionStr,
                                0xFFFF,
                                longValue);
                        break;
                    case 1:  // Double
                        double doubleValue = this.buffer.getDouble();
                        field = new TmDouble(
                                XmlParamFinder.find(paramNum, this.xmlParamElements),
                                time,
                                dimensionStr,
                                valueType,
                                doubleValue);
                        break;
                    case 2:  // Code
                        this.buffer.getShort(); // Skip
                        short codeLength = this.buffer.getShort();
                        int code = this.buffer.getInt();
                        field = new TmCode(
                                XmlParamFinder.find(paramNum, this.xmlParamElements),
                                time,
                                dimensionStr,
                                valueType,
                                codeLength,
                                code);
                        break;
                    case 3: // Point
                        short elemSize = this.buffer.getShort();
                        int bytesLength = this.buffer.getShort() & 0xFFFF;
                        byte[] point = new byte[bytesLength];
                        for (int i = 0; i < bytesLength; i++)
                            point[i] = this.buffer.get();
                        field = new TmPoint(
                                XmlParamFinder.find(paramNum, this.xmlParamElements),
                                time,
                                dimensionStr,
                                valueType,
                                elemSize,
                                point);
                        break;
                    default:
                        System.out.println("PARSING ERROR: valueType=" + valueType);
                        field = new TmDat(
                                XmlParamFinder.find(paramNum, this.xmlParamElements),
                                time,
                                dimensionStr,
                                valueType);

                }
                tmSet.add(field);
                // if (tmSet.size() > 100)
                //     break;

            } catch (Exception e) {
                System.err.println("Ну " + e + ", и " + e);
                break; // For some reason we return in while loop
            }
            this.statistics.bytesNum = this.buffer.position();
            this.statistics.usefulFieldsNum = tmSet.size();
        }
    }

    public void printStatistics() {
        System.out.println("usefulFieldsNum: " + statistics.usefulFieldsNum);
        System.out.println("systemFieldsNum: " + statistics.systemFieldsNum);
        System.out.println("bytesNum: " + statistics.bytesNum);
    }

    private void parseSystemMessage() {
        int messageType = this.buffer.get() & 0xF;
        this.buffer.get(); // valueType
        switch (messageType) {
            case 1:
                this.buffer.getShort();
                int messageLength = this.buffer.getShort() & 0xFFFF;
                for (int i = 0; i < messageLength; i++)
                    this.buffer.get();
                break;
            default:
                this.buffer.getLong();
        }
    }

    static protected boolean isSystemMessage(int paramNum) {
        return paramNum == SYSTEM_MESSAGE_PARAM;
    }
    
    private class Statistics {
        long usefulFieldsNum = 0l;
        long systemFieldsNum = 0l;
        long bytesNum = 0l;
    }
    // номер параметра служебного сообщения
    protected static final int SYSTEM_MESSAGE_PARAM = 0xFFFF;

    protected HashMap<Integer, String> xmlParamElements;


    // New iteration
    protected MappedByteBuffer buffer;
    protected HashMap<Integer, String> dimensions;

    protected short offset = 0;

    protected Statistics statistics;

}
