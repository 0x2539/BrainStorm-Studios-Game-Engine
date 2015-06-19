package com.example.brainstormstudiosgameengine;
import java.util.List;


public class BSXmlStruct {
	public  String nodeName, nodeValue, headNodeName;
	public  List<BSAttribute> attributes, headNodeAttributes = null;
	public  List<BSXmlStruct> listOfTheSecondNodes = null, listOfTheOtherNodes = null;
}

class BSAttribute
{
	public  String attributeName, attributeValue;
}
