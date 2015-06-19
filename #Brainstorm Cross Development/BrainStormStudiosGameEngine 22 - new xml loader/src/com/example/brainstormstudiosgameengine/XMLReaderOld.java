package com.example.brainstormstudiosgameengine;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.InputSource;


import android.content.Context;
import android.content.res.AssetManager;

public class XMLReaderOld {

	public static String getXml(String path, Context context)
	{
	    String xmlString = null;
	    AssetManager am = context.getAssets();
	    try 
	    {
	        InputStream is = am.open(path);
	        int length = is.available();
	        byte[] data = new byte[length];
	        is.read(data);
	        xmlString = new String(data);
	    } 
	    catch (IOException e1) 
	    {
	        e1.printStackTrace();
	    }

	    return xmlString;
	}
	

	public static BSXmlStruct readAnyXML(Context context, String path, 
			List<String> listOfNodes, List<String> listOfAttributes,
			String headNode, String secondNode)
	{
		BSXmlStruct theReturnedHeadNode = new BSXmlStruct();
		
		try
		{
			DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
			DocumentBuilder db = dbf.newDocumentBuilder();
			String theXML = getXml(path, context);
			Document doc = db.parse(new InputSource(new ByteArrayInputStream(theXML.getBytes("utf-8"))));
			doc.getDocumentElement().normalize();

			NodeList nodeListHeadNode = doc.getElementsByTagName(headNode);
			///Create a list with the second nodes
			List<BSXmlStruct> listOfSecondNodes = new ArrayList<BSXmlStruct>();
			
			String errorMessage = "";

			for (int i = 0; i < nodeListHeadNode.getLength(); i++) 
			{
				Node theHeadNode = nodeListHeadNode.item(i);

				Element headNodeElement = (Element) theHeadNode;

				NodeList headNodeList = headNodeElement.getElementsByTagName(headNode);
				Element elementsOfHeadNode = (Element) headNodeList.item(0);
				headNodeList = elementsOfHeadNode.getChildNodes();
				
				List<BSAttribute> listOfHeadNodeAttributes = new ArrayList<BSAttribute>();;
				
				///Get the attributes of the headNode
				for(int k = 0 ; k < listOfAttributes.size(); k++)
				{
					BSAttribute newAtr = new BSAttribute();
					newAtr.attributeName = listOfAttributes.get(k);
					newAtr.attributeValue = elementsOfHeadNode.getAttribute(newAtr.attributeName);
					listOfHeadNodeAttributes.add(newAtr);
				}
				theReturnedHeadNode.headNodeAttributes = listOfHeadNodeAttributes;
				theReturnedHeadNode.headNodeName = headNode;
				
				
				NodeList nodeListSecondNode = doc.getElementsByTagName(secondNode);
				
				///parcurg toate nodurile secundare
				for(int j = 0 ; j < nodeListSecondNode.getLength(); j++)
				{
					BSXmlStruct newSecondNode = new BSXmlStruct();
					newSecondNode.nodeName = secondNode;
					
					Node theSecNode = nodeListSecondNode.item(j);
					
					Element secNodeElement = (Element) theSecNode;

					
					///parcurg toate nodurile din nodurile secundare daca exista
					if(listOfNodes.size() != 0)
					{
						List<BSXmlStruct> listOfNodesOthers = new ArrayList<BSXmlStruct>();

						errorMessage = "5 " + j + '\n';
						///parcurg toate nodurile din nodurile secundare
						for(int k = 0; k < listOfNodes.size(); k++)
						{
							try
							{
								NodeList secNodeList = secNodeElement.getElementsByTagName(listOfNodes.get(k));
								Element elementsOfSecNode = (Element) secNodeList.item(0);
								secNodeList = elementsOfSecNode.getChildNodes();
	
								BSXmlStruct newNode = new BSXmlStruct();
								
//								Node nodeOfTheSecond = secNodeList.item(k);
	
//								Element fstElmnt = (Element) secNodeList;
	
//								NodeList websiteList = fstElmnt.getElementsByTagName(listOfNodes.get(k));
//								Element websiteElement = (Element) websiteList.item(0);
//								websiteList = websiteElement.getChildNodes();
								errorMessage += "11 " + listOfNodes.get(0);
								
								newNode.nodeValue = ((Node) secNodeList.item(0)).getNodeValue();
								newNode.nodeName = listOfNodes.get(k);
								
	
								errorMessage += "12";
								List<BSAttribute> listOfAttributesOthers = new ArrayList<BSAttribute>();
								
								///parcurg toate atributele
								for(int u = 0 ; u < listOfAttributes.size(); u++)
								{
									BSAttribute newAtr = new BSAttribute();
									newAtr.attributeValue = elementsOfSecNode.getAttribute(listOfAttributes.get(u));
									newAtr.attributeName = listOfAttributes.get(u);
									listOfAttributesOthers.add(newAtr);
								}
								newNode.attributes = listOfAttributesOthers;
								listOfNodesOthers.add(newNode);
							}
							catch(Exception ex)
							{
								///nu a gasit nodul scris de mine in fisierul xml, probabil a fost scris gresit de mine
							}
						}
						newSecondNode.listOfTheOtherNodes = listOfNodesOthers;
						listOfSecondNodes.add(newSecondNode);
					}
					///daca nu exista alte noduri in cele secundare, ii iau valoarea
					///si attributes
					else
						if(listOfNodes.size() == 0)
						{
							newSecondNode.nodeValue = ((Node) secNodeElement).getNodeValue();
							
							List<BSAttribute> listOfSecondAttributes = new ArrayList<BSAttribute>();
							
							for(int u = 0 ; u < listOfAttributes.size(); u++)
							{
								BSAttribute newAtr = new BSAttribute();
								newAtr.attributeValue = secNodeElement.getAttribute(listOfAttributes.get(u));
								newAtr.attributeName = listOfAttributes.get(u);
								listOfSecondAttributes.add(newAtr);
							}
							newSecondNode.attributes = listOfSecondAttributes;
							listOfSecondNodes.add(newSecondNode);
						}
				}
			}
			theReturnedHeadNode.listOfTheSecondNodes = listOfSecondNodes;
//			writeTheReadedXML(theReturnedHeadNode);
		}
		catch (Exception e)
		{
			System.out.println("XML Pasing Excpetion = " + e);
		}

		return theReturnedHeadNode;
	}
	
}
