package ru.lib;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import java.io.File;
import java.io.IOException;
import java.util.HashMap;

public class XmlReader {
    public static HashMap<Integer, String> getData(String filePath) throws ParserConfigurationException, IOException, SAXException {
        // открываем файл
        File inputFile = new File(filePath);

        DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
        DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
        Document doc = dBuilder.parse(inputFile);
        doc.getDocumentElement().normalize();

        // ищем все теги Param
        NodeList nList = doc.getElementsByTagName("Param");

        // подготавливаем данные
        HashMap<Integer, String> tmp = new HashMap<Integer, String>();

        // проходимся по всем элементам
        for (int i = 0; i < nList.getLength(); i++) {
            Node nNode = nList.item(i);
            if (nNode.getNodeType() == Node.ELEMENT_NODE) {
                Element eElement = (Element) nNode;
                tmp.put(
                    Integer.parseInt(eElement.getAttribute("number")),
                    eElement.getAttribute("name")
                );
            }
        }

        return tmp;
    }
}
