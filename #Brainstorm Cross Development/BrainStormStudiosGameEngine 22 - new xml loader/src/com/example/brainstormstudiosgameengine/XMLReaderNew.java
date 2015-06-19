package com.example.brainstormstudiosgameengine;

import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.StringReader;
import java.util.ArrayList;
import java.util.List;

import org.jdom2.Document;
import org.jdom2.Element;
import org.jdom2.input.SAXBuilder;
import org.xml.sax.InputSource;

import android.content.Context;
import android.content.res.AssetManager;
import android.util.Log;

public class XMLReaderNew {

	public static BSXmlStruct readAnyXML(Context context, String path, List<String> listOfNodes, List<String> listOfAttributes,
										 String headNode, String secondNode)
	{
		BSXmlStruct theReturnedHeadNode = new BSXmlStruct();

		try
		{
			SAXBuilder builder = new SAXBuilder();
			String theXML = getXml(path, context);
//			Document doc = db.parse(new InputSource(new ByteArrayInputStream(theXML.getBytes("utf-8"))));
//			doc.getDocumentElement().normalize();
			
			File xmlFile = new File(path);
			
			StringReader xmlReader = new StringReader(theXML);
			
			Document document = (Document) builder.build(new InputSource(new ByteArrayInputStream(theXML.getBytes("utf-8"))));
			Element rootNode = document.getRootElement();
			List nodeListHeadNode = rootNode.getChildren(secondNode);

			///Create a list with the second nodes
			List<BSXmlStruct> listOfSecondNodes = new ArrayList<BSXmlStruct>();

			List<BSAttribute> listOfHeadNodeAttributes = new ArrayList<BSAttribute>();;

//			System.out.println(rootNode.getName());

			///Get the attributes of the headNode
			try
			{
				for(int k = 0 ; k < listOfAttributes.size(); k++)
				{
					BSAttribute newAtr = new BSAttribute();
					newAtr.attributeName = listOfAttributes.get(k);
					newAtr.attributeValue = rootNode.getAttributeValue(newAtr.attributeName);
					// elementsOfHeadNode.getAttribute(newAtr.attributeName);
					listOfHeadNodeAttributes.add(newAtr);
//					System.err.println("	" + newAtr.attributeName + ": " + newAtr.attributeValue);
				}

				theReturnedHeadNode.headNodeAttributes = listOfHeadNodeAttributes;
				theReturnedHeadNode.headNodeName = headNode;
			}
			catch(Exception ex)
			{
			}

			System.out.println();

			for (int i = 0; i < nodeListHeadNode.size(); i++)
			{
				BSXmlStruct newSecondNode = new BSXmlStruct();
				newSecondNode.nodeName = secondNode;
				Element secNodeElement = (Element) nodeListHeadNode.get(i);

//				System.out.println(secondNode);


				///parcurg toate nodurile din nodurile secundare daca exista
				if(listOfNodes.size() != 0)
				{
					List<BSXmlStruct> listOfNodesOthers = new ArrayList<BSXmlStruct>();

					///parcurg toate nodurile din nodurile secundare
					for(int k = 0; k < listOfNodes.size(); k++)
					{
						try
						{
							BSXmlStruct newNode = new BSXmlStruct();


							newNode.nodeName = listOfNodes.get(k);
							Element elementsOfSecNode = secNodeElement.getChild(newNode.nodeName);
							newNode.nodeValue = elementsOfSecNode.getValue();
//							System.out.println("	" + newNode.nodeName + ": " + newNode.nodeValue);


							///parcurg toate atributele daca exista
							if(elementsOfSecNode.hasAttributes() == true)
							{
								List<BSAttribute> listOfAttributesOthers = new ArrayList<BSAttribute>();

								for(int u = 0 ; u < listOfAttributes.size(); u++)
								{
									BSAttribute newAtr = new BSAttribute();
									newAtr.attributeName = listOfAttributes.get(u);
									newAtr.attributeValue = elementsOfSecNode.getAttributeValue(newAtr.attributeName);
									listOfAttributesOthers.add(newAtr);
//									System.err.println("		" + newAtr.attributeName + ": " + newAtr.attributeValue);
								}

								newNode.attributes = listOfAttributesOthers;
							}
							listOfNodesOthers.add(newNode);
						}
						catch
							(Exception ex)
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
						newSecondNode.nodeValue = secNodeElement.getValue();

						List<BSAttribute> listOfSecondAttributes = new ArrayList<BSAttribute>();

						for(int u = 0 ; u < listOfAttributes.size(); u++)
						{
							BSAttribute newAtr = new BSAttribute();
							newAtr.attributeName = listOfAttributes.get(u);
							newAtr.attributeValue = secNodeElement.getAttributeValue(newAtr.attributeName);
							listOfSecondAttributes.add(newAtr);
						}

						newSecondNode.attributes = listOfSecondAttributes;
						listOfSecondNodes.add(newSecondNode);
					}
			}

			theReturnedHeadNode.listOfTheSecondNodes = listOfSecondNodes;
		}
		catch
			(Exception e)
		{
			System.out.println("XML Pasing Excpetion = " + e);
		}

		
		return theReturnedHeadNode;
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

	public static InputStream getXml2(String path, Context context)
	{
	    InputStream is = null;
	    AssetManager am = context.getAssets();
	    try 
	    {
	        is = am.open(path);
	        int length = is.available();
	        byte[] data = new byte[length];
	        is.read(data);
	    } 
	    catch (IOException e1) 
	    {
	        e1.printStackTrace();
	    }

	    return is;
	}
	
}
