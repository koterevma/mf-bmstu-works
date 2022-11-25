package ru.lib;

import java.io.*;
import ru.lib.tm.*;

public class BinaryReader {
    // номер параметра служебного сообщения
    protected final int SYSTEM_MESSAGE_PARAM = 0xFFFF;

    protected BufferedInputStream inputStream;
    protected BufferedWriter outputWriter;
    protected XmlParamElement[] xmlParamElements;

    protected int currentByte = 0;
    protected String currentByteHex = "";

    protected int codeLength = 0;
    protected int valueType = 0;
    protected int messageType = 0;
    protected long milliseconds = 0;
    protected int paramNumber = 0;
    protected int position = -1;
    protected String tmpString = "";

    protected Statistics statistics;

    public BinaryReader(String inputFilePath, String outputFilePath, XmlParamElement[] xmlParamElements) throws IOException {
        this.inputStream = new BufferedInputStream(new FileInputStream(inputFilePath));
        this.outputWriter = new BufferedWriter(new FileWriter(outputFilePath));
        this.xmlParamElements = xmlParamElements;
        this.statistics = new Statistics();
    }

    public void readAndWrite() throws IOException {
        while ((this.currentByte = this.inputStream.read()) != -1) {
            this.currentByteHex = String.format("%02x", currentByte);

            this.statistics.bytesNum++; this.position++;

            switch (this.position) {
                case 0, 1 -> this.getParamNumber();
                case 2, 3, 4, 5 -> this.getMilliseconds();
                case 6 -> this.getMessageType();
                case 7 -> this.getValueType();
                default -> this.getMessageValue();
            }
        }

        System.out.println("File size: " + this.statistics.bytesNum + " bytes");
        System.out.println("TM fields: " + this.statistics.usefulFieldsNum);
        System.out.println("System fields: " + this.statistics.systemFieldsNum);
        this.outputWriter.close();
    }

    protected void getParamNumber() throws IOException {
        if (this.position == 0) {
            this.tmpString = this.currentByteHex;
        } else {
            this.tmpString = this.tmpString + this.currentByteHex;
            this.paramNumber = Integer.parseInt(this.tmpString, 16);

            if (!this.isSystemMessage()) {
                String paramName = XmlParamFinder.find(this.paramNumber, this.xmlParamElements);
                this.outputWriter.write(paramName + ' ');
                this.outputWriter.write(Integer.toString(this.paramNumber) + ' ');
                this.statistics.usefulFieldsNum++;
            } else {
                this.statistics.systemFieldsNum++;
            }
        }
    }

    protected void getMilliseconds() throws IOException {
        if (this.position == 2) {
            this.tmpString = this.currentByteHex;
        } else {
            this.tmpString = this.tmpString + this.currentByteHex;
            if (this.position == 5) {
                this.milliseconds = Long.parseLong(this.tmpString, 16);

                long seconds = this.milliseconds / 1000;
                long hours = seconds / 3600;
                long minutes = (seconds % 3600) / 60;
                seconds %= 60;

                if (!this.isSystemMessage())
                    this.outputWriter.write(String.format("%02d:%02d:%02d", hours, minutes, seconds) + ',' + this.milliseconds + ' ');
            }
        }
    }

    protected void getMessageType() {
        this.messageType = this.currentByte;
    }

    protected void getValueType() {
        if (this.paramNumber == 65535) {
            this.valueType = this.currentByte;
        } else {
            this.valueType = this.currentByte & 0xF; // 15 -> 00001111 bit mask
        }
    }

    protected void getMessageValue() throws IOException {
        if (this.position == 8) {
            this.tmpString = "";
        }

        switch (this.valueType) {
            // Long
            case 0 -> this.getValueTypeLong();
            // Double
            case 1 -> this.getValueTypeDouble();
            // Code
            case 2 -> this.getValueTypeCode();
            // Point
            case 3 -> this.getValueTypePoint();
        }
    }

    protected void getValueTypeLong() throws IOException {
        // 8-11 байт не используется
        if (this.position >= 8 && this.position <= 11) return;

        this.tmpString = this.tmpString + this.currentByteHex;
        if (this.position == 15) {

            if (!this.isSystemMessage()) {
                this.outputWriter.write(Long.toString(Long.parseLong(this.tmpString, 16)));
                this.outputWriter.write('\n');
            }
            this.position = -1;
        }
    }

    protected void getValueTypeDouble() throws IOException {
        this.tmpString = this.tmpString + this.currentByteHex;

        if (this.position == 15) {
            if (!this.isSystemMessage()) {
                try {
                    this.outputWriter.write(Double.toString(Double.longBitsToDouble(Long.parseLong(this.tmpString, 16))));
                } catch (NumberFormatException e) {
                    this.outputWriter.write(" ERROR");
                }
                this.outputWriter.write('\n');
            }
            this.position = -1;
        }
    }

    protected void getValueTypeCode() throws IOException {
        // 8-11 байт не используется
        if (this.position == 8 || this.position == 9) return;

        // считаем длину кода
        if (this.position == 10 || this.position == 11) {
            this.tmpString = this.tmpString + this.currentByteHex;
            if (this.position == 11) {
                this.codeLength = Integer.parseInt(this.tmpString, 16);
                if (!this.isSystemMessage())
                    this.outputWriter.write("len:" + this.codeLength + ' ');
            }
        } else {
            if (this.position == 12) {
                this.tmpString = "";
            }

            // переводим байт в бинарное представление
            this.tmpString = this.tmpString + (String.format("%8s", Integer.toBinaryString(this.currentByte)).replace(' ', '0'));
            if (this.position == 15) {
                if (!this.isSystemMessage()) {
                    this.outputWriter.write(this.tmpString.substring(this.tmpString.length() - this.codeLength));
                    this.outputWriter.write('\n');
                }
                this.position = -1;
            }
        }
    }

    protected void getValueTypePoint() throws IOException {
        // 8-11 байт не используется
        if (this.position == 8 || this.position == 9) return;

        if (this.position == 10 || this.position == 11) {
            this.tmpString = this.tmpString + this.currentByteHex;
            if (this.position == 11) {
                this.codeLength = Integer.parseInt(this.tmpString, 16);
                if (!this.isSystemMessage())
                    this.outputWriter.write("len:" + this.codeLength + ' ');
            }
        } else {
            if (--this.codeLength == 0) {
                if (!this.isSystemMessage()) {
                    this.outputWriter.write("point\n");
                }
                this.position = -1;
            }
        }
    }

    protected boolean isSystemMessage() {
        return this.paramNumber == this.SYSTEM_MESSAGE_PARAM;
    }
    
    private class Statistics {
        long usefulFieldsNum = 0l;
        long systemFieldsNum = 0l;
        long bytesNum = 0l;
    }
}
