package com.example.brainstormstudiosgameengine;

import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.List;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

import org.jbox2d.dynamics.BodyType;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.InputSource;

import android.content.Context;
import android.content.res.AssetManager;
import android.os.Environment;

public class XMLReader
{
	
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
								overWriteSDFile("errorLog.txt", errorMessage);
								
								newNode.nodeValue = ((Node) secNodeList.item(0)).getNodeValue();
								newNode.nodeName = listOfNodes.get(k);
								
	
								errorMessage += "12";
								overWriteSDFile("errorLog.txt", errorMessage);
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
	
	public static void writeTheReadedXML(BSXmlStruct headNode)
	{
//		int nr = headNode.listOfTheSecondNodes.size();
//		String message = String.valueOf(nr) + '\n';
		for(int i = 0 ; i < headNode.listOfTheSecondNodes.size(); i++)
		{
//			message += headNode.listOfTheSecondNodes.get(i).nodeName + ": " + 
//					headNode.listOfTheSecondNodes.get(i).nodeValue + '\n';
			float xCord = 0, yCord = 0, width = 0, height = 0;
			String userName = "";
			for(int j = 0 ; j < headNode.listOfTheSecondNodes.get(i).listOfTheOtherNodes.size(); j++)
			{
				if(headNode.listOfTheSecondNodes.get(i).listOfTheOtherNodes.get(j).nodeName.equals("xCoordinate"))
				{
					xCord = Float.parseFloat(headNode.listOfTheSecondNodes.get(i).listOfTheOtherNodes.get(j).nodeValue);
				}

				if(headNode.listOfTheSecondNodes.get(i).listOfTheOtherNodes.get(j).nodeName.equals("yCoordinate"))
				{
					yCord = Float.parseFloat(headNode.listOfTheSecondNodes.get(i).listOfTheOtherNodes.get(j).nodeValue);
				}

				if(headNode.listOfTheSecondNodes.get(i).listOfTheOtherNodes.get(j).nodeName.equals("width"))
				{
					width = Float.parseFloat(headNode.listOfTheSecondNodes.get(i).listOfTheOtherNodes.get(j).nodeValue);
				}

				if(headNode.listOfTheSecondNodes.get(i).listOfTheOtherNodes.get(j).nodeName.equals("height"))
				{
					height = Float.parseFloat(headNode.listOfTheSecondNodes.get(i).listOfTheOtherNodes.get(j).nodeValue);
				}

				if(headNode.listOfTheSecondNodes.get(i).listOfTheOtherNodes.get(j).nodeName.equals("userName"))
				{
					userName = headNode.listOfTheSecondNodes.get(i).listOfTheOtherNodes.get(j).nodeValue;
				}
//				message += "		" + headNode.listOfTheSecondNodes.get(i).listOfTheOtherNodes.get(j).nodeName + ": " + 
//						headNode.listOfTheSecondNodes.get(i).listOfTheOtherNodes.get(j).nodeValue + '\n';
			}
			BSTheSquareBodies ground = new BSTheSquareBodies();
			Values.obstacles.add(ground);
			ActionStuff.createSquareBody(Values.obstacles.get(Values.obstacles.size() - 1), BodyType.STATIC, -xCord, -yCord, width, height, 1, 0, 0, userName, Values.world, R.raw.texture);
			
		}
		
//		overWriteSDFile("finalXml.txt", message);
	}

	public static void readTheXML(Context context) 
	{
		String message = "";
		try {
			DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
			DocumentBuilder db = dbf.newDocumentBuilder();
			String theXML = getXml("xmlfile.xml", context);
			Document doc = db.parse(new InputSource(new ByteArrayInputStream(theXML.getBytes("utf-8"))));
			doc.getDocumentElement().normalize();

			NodeList nodeList = doc.getElementsByTagName("obstacle");

			for (int i = 0; i < nodeList.getLength(); i++) 
			{
				Node node = nodeList.item(i);

				Element fstElmnt = (Element) node;

				NodeList websiteList = fstElmnt.getElementsByTagName("userName");
				Element websiteElement = (Element) websiteList.item(0);
				websiteList = websiteElement.getChildNodes();
				
				message += ((Node) websiteList.item(0)).getNodeName() + "; " + 
				((Node) websiteList.item(0)).getNodeValue()  + ";; ";
				

				websiteList = fstElmnt.getElementsByTagName("Animation_name");
				websiteElement = (Element) websiteList.item(0);
				websiteList = websiteElement.getChildNodes();
				
				message += ((Node) websiteList.item(0)).getNodeName() + "; " + 
				((Node) websiteList.item(0)).getNodeValue()  + '\n';
			}
		} catch (Exception e) {
			System.out.println("XML Pasing Excpetion = " + e);
			message = "XML Pasing Excpetion = " + e;
		}
		overWriteSDFile("testxml.txt", message);
	}
	
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
	
	

	public static void overWriteSDFile(String name, String message)
	{
    	//This will get the SD Card directory and create a folder named MyFiles in it.
    	File sdCard = Environment.getExternalStorageDirectory();
    	File directory = new File (sdCard.getAbsolutePath() + "/Bs Studios Files");
    	directory.mkdirs();

    	//Now create the file in the above directory and write the contents into it
    	File file = new File(directory, name);
    	FileOutputStream fOut = null;
		try 
		{
			fOut = new FileOutputStream(file);
		} 
		catch (FileNotFoundException e) 
		{
			e.printStackTrace();
		}
    	OutputStreamWriter osw = new OutputStreamWriter(fOut);
    	try 
    	{
			osw.write(message);
			
	    	osw.flush();
	    	osw.close();
		} 
    	catch (IOException e) 
    	{
			e.printStackTrace();
		}
	}
	
}
