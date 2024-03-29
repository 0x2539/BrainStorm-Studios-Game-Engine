#include "BSXmlFiles.h"

void BSXmlFiles::parseStory (xmlDocPtr doc, xmlNodePtr cur)
{
	xmlChar *key;
	cur = cur->xmlChildrenNode;
    
	while (cur != NULL)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"capsOn")))
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			printf("capsOn: %s\n", key);
            
			char asd[100] = "";
			std::string theString = BStoString(key);
			strcpy(asd, theString.c_str());
			//xmlFree(key);
		}
        
		cur = cur->next;
	}
    
	return;
}


void BSXmlFiles::writeXML()
{
	xmlTextWriterPtr writer;
	writer = xmlNewTextWriterFilename("Animations/Font/test.xml", 0);
	xmlTextWriterStartDocument(writer, NULL, (const char*) "UTF-8", NULL);
	xmlTextWriterStartElement(writer, (const xmlChar*)"theLetters");
    
	xmlTextWriterWriteElement(writer, (const xmlChar*)"capsOn", (const xmlChar*)"A");// xmlTextWriterEndElement(writer);
    
	xmlTextWriterWriteElement(writer, (const xmlChar*)"capsOff", (const xmlChar*)"a");
    
	xmlTextWriterEndElement(writer);
    
	xmlTextWriterEndElement(writer);
	xmlTextWriterEndDocument(writer);
	xmlFreeTextWriter(writer);
}

void BSXmlFiles::parseDoc(char *docname)
{
	std::cout<<"opened the XML"<<'\n';
	xmlDocPtr doc;
	xmlNodePtr cur;
	doc = xmlParseFile(docname);
    
	if (doc == NULL )
	{
		fprintf(stderr,"Document not parsed successfully. \n");
		return;
	}
    
	cur = xmlDocGetRootElement(doc);
    
	if (cur == NULL)
	{
		fprintf(stderr,"empty document\n");
		xmlFreeDoc(doc);
		return;
	}
    
	if (xmlStrcmp(cur->name, (const xmlChar *) "FontLetters"))
	{
		fprintf(stderr,"document of the wrong type, root node != FontLetters");
		std::cout<<" should be "<<cur->name<<'\n';
		xmlFreeDoc(doc);
		return;
	}
    
	cur = cur->xmlChildrenNode;
    
	while (cur != NULL)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"letter")))
		{
			parseStory (doc, cur);
		}
        
		cur = cur->next;
	}
    
	std::cout<<"closed the XML"<<'\n';
	xmlFreeDoc(doc);
	writeXML();
	return;
}



void BSXmlFiles::readAnyXML(std::string docnameString, std::string headNodeString, std::string secondNodeString,
							ListaDeCaractere *theNodeValues[], char theNodes[][100],
							char theProperties[][100], ListaDeCaractere *headAttributesValues[],
							int nrOfNodes, int NrOfProperties)
{
	
	bool isTxt =false, isXML = false;
	if(docnameString[docnameString.size() - 1] == 't')//.txt
	{
		isTxt = true;
	}
	else
		if(docnameString[docnameString.size() - 1] == 'l')//.xml
		{
			isXML = true;
		}
	std::string newPath = "", copyOfPath = docnameString;
	
	for(int i = 0 ; i < docnameString.size() - 4; i++)
	{
		newPath += docnameString[i];
	}
	
	docnameString = newPath;
	//std::cout<<"path: "<<path<<'\n';
	
	NSString *fileName = [NSString stringWithCString:docnameString.c_str()
											encoding:[NSString defaultCStringEncoding]];
	//std::cout<<"pula1"<<'\n';
	NSString *path;
	if(isTxt)
	{
		path = [[NSBundle mainBundle] pathForResource:fileName ofType:@"txt"];
	}
	else
		if(isXML)
		{
			path = [[NSBundle mainBundle] pathForResource:fileName ofType:@"xml"];
		}

	//NSString *path = [[NSBundle mainBundle] pathForResource:@"some" ofType:@"xml"];
	NSString *fileText = [NSString stringWithContentsOfFile:path];
	
	NSString *xml = fileText; // string containing XML
	xmlDocPtr doc = xmlParseMemory([xml UTF8String], [xml lengthOfBytesUsingEncoding:NSUTF8StringEncoding]);
	xmlNodePtr root = xmlDocGetRootElement(doc);
	xmlNodePtr node = root->children;
	xmlNodePtr cur_node;
	
	
	xmlAttr *attrHead = root->properties;
	
	if(headAttributesValues != NULL)
	{
		headAttributesValues[0] = new ListaDeCaractere;
		while(attrHead && attrHead->name && attrHead->children)
		{
			//std::cout<<attrHead->name<<' '<<docnameString<<'\n';
			for(int i = 0 ; i < NrOfProperties; i++)
			{
				NSString *fileName = [NSString stringWithCString:theProperties[i]
														encoding:[NSString defaultCStringEncoding]];
				
				if (strcmp((char *)attrHead->name, [fileName cStringUsingEncoding:NSUTF8StringEncoding])==0)
				{
					xmlChar *ret = xmlNodeListGetString(doc, attrHead->children, 1);
					strcpy(headAttributesValues[0]->theCharArray2DAttributes[i], (char*)ret);
					//std::cout<<attrHead->name<<' '<<ret<<'\n';
					break;
				}
			}
			attrHead = attrHead->next;
		}
	}
	
	int nodeNR = 0;
	
	for (cur_node = node; cur_node; cur_node = cur_node->next)
	{
		//std::cout<<""<<"Obstacle"<<'\n';
		//if(BStoString(cur_node) == secondNodeString)
		//{
		if ((!xmlStrcmp(cur_node->name, (const xmlChar *)secondNodeString.c_str())))
		{
			theNodeValues[nodeNR] = new ListaDeCaractere;
			//NSString *nameToSearchFor = @"obstacle";
			//std::cout<<"	"<<secondNodeString<<'\n';
			xmlNode *child = NULL;
			for (child = cur_node->children; child; child = child->next)
			{
				for(int i = 0 ; i < nrOfNodes; i++)
				{
					NSString *fileName = [NSString stringWithCString:theNodes[i]
															encoding:[NSString defaultCStringEncoding]];
					
					if (strcmp((char *)child->name, [fileName cStringUsingEncoding:NSUTF8StringEncoding])==0)
					{
						xmlChar *ret = xmlNodeListGetString(doc, child->children, 1);
						
						strcpy(theNodeValues[nodeNR]->theCharArray2D[i], (char*)ret);
					}
				}
				if(NrOfProperties != 0)
				{
					xmlAttr *attr = child->properties;
					//std::cout<<attr<<'\n';
					while(attr)// && attr->name && attr->children)
					{
						for(int i = 0 ; i < NrOfProperties; i++)
						{
							NSString *fileName = [NSString stringWithCString:theProperties[i]
																	encoding:[NSString defaultCStringEncoding]];
							
							if (strcmp((char *)attr->name, [fileName cStringUsingEncoding:NSUTF8StringEncoding])==0)
							{
								xmlChar *ret = xmlNodeListGetString(doc, attr->children, 1);
								strcpy(theNodeValues[nodeNR]->theCharArray2DAttributes[i], (char*)ret);
								//std::cout<<"ret: "<<ret<<'\n';
								break;
							}
						}
						//std::cout<<"ret:: "<<attr->name<<'\n';
						attr = attr->next;
					}
				}
			}
			if(nrOfNodes == 0)
			{
				xmlAttr *attr = cur_node->properties;
				//std::cout<<attr<<'\n';
				while(attr)// && attr->name && attr->children)
				{
					for(int i = 0 ; i < NrOfProperties; i++)
					{
						NSString *fileName = [NSString stringWithCString:theProperties[i]
																encoding:[NSString defaultCStringEncoding]];
						
						if (strcmp((char *)attr->name, [fileName cStringUsingEncoding:NSUTF8StringEncoding])==0)
						{
							xmlChar *ret = xmlNodeListGetString(doc, attr->children, 1);
							strcpy(theNodeValues[nodeNR]->theCharArray2DAttributes[i], (char*)ret);
							//std::cout<<"ret: "<<theNodeValues[nodeNR]->theCharArray2DAttributes[i]<<'\n';
							break;
						}
					}
					//std::cout<<"ret:: "<<attr->name<<'\n';
					attr = attr->next;
				}
			}
			nodeNR++;
		}
	}
	theNodeValues[nodeNR] = NULL;
	//std::cout<<"nodenr: "<<nodeNR<<'\n';
	
}
	/*const char* docname = docnameString.c_str();
	char headNode[100] = "";
	strcpy(headNode, headNodeString.c_str());
    
	char secondNode[100] = "";
	strcpy(secondNode, secondNodeString.c_str());
    
    
	xmlDocPtr doc;
	xmlNodePtr cur;
	doc = xmlParseFile(docname);
    
	if (doc == NULL )
	{
		fprintf(stderr,"Document not parsed successfully. \n");
		return;
	}
    
	cur = xmlDocGetRootElement(doc);
    
	if (cur == NULL)
	{
		fprintf(stderr,"empty document\n");
		xmlFreeDoc(doc);
		return;
	}
    
	if (xmlStrcmp(cur->name, (const xmlChar *) headNode))
	{
		std::cout<<"document of the wrong type, root node != " + BStoString(headNode)<<" should be "<<cur->name<<'\n';
		xmlFreeDoc(doc);
		return;
	}
    
    ///Check the head node properties
    if(theProperties && headAttributesValues)
    {
        headAttributesValues[0] = NULL;
        if ((!xmlStrcmp(cur->name, (const xmlChar *)headNode)))
        {
            if(theProperties)
            {
                parseAnyStoryAttributes(doc, cur, headAttributesValues, theProperties, NrOfProperties, 0);
            }
        }
    }
    
	cur = cur->xmlChildrenNode;
    
	///Current line
	int i = 0, j = 0;
    
	while (cur != NULL)
	{
		///check for the nodes from body
		if ((!xmlStrcmp(cur->name, (const xmlChar *)secondNode)))
		{
			theNodeValues[j] = NULL;
			if(theNodes)
			{
				parseAnyStory(doc, cur, theNodeValues, theNodes, nrOfNodes, j);
			}
			if(theProperties)
			{
				parseAnyStoryAttributes(doc, cur, theNodeValues, theProperties, NrOfProperties, j);
			}
			j++;
		}
		i++;
		cur = cur->next;
	}
    
	theNodeValues[j] = NULL;
    
	xmlFreeDoc(doc);
	writeXML();
	return;*/

void BSXmlFiles::parseAnyStory (xmlDocPtr doc, xmlNodePtr cur, ListaDeCaractere *theNodeValues[],
								char theNodes[][100], int nrOfNodes, int currentLine)
{
	xmlChar *key;
	cur = cur->xmlChildrenNode;
    
    theNodeValues[currentLine] = new ListaDeCaractere;
	while (cur != NULL)
	{
		int i = 0;
        
		while(i < nrOfNodes)
		{
			if ((!xmlStrcmp(cur->name, (const xmlChar *)theNodes[i])))
			{
				key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
				std::string theString = BStoString(key);
				theNodeValues[currentLine]->theCharArray2D[i][0] = NULL;
				strcpy(theNodeValues[currentLine]->theCharArray2D[i], theString.c_str());
				//xmlFree(key);
				break;
			}
			i++;
		}
        
		cur = cur->next;
	}
	return;
}

void BSXmlFiles::parseAnyStoryAttributes(xmlDocPtr doc, xmlNodePtr cur,
                                         ListaDeCaractere* theNodeValues[], char nameAttributesOfNode[][100],
                                         int NrOfProperties, int currentLine)
{
	xmlAttr* attributeOfTheNode = cur->properties;
	if(!theNodeValues[currentLine])
	{
		theNodeValues[currentLine] = new ListaDeCaractere;
	}
	int i = 0;
	while(attributeOfTheNode && attributeOfTheNode->name && attributeOfTheNode->children)
	{
		int j = 0;
		while(j < NrOfProperties)
		{
			if ((!xmlStrcmp(attributeOfTheNode->name, (const xmlChar *)nameAttributesOfNode[j])))
			{
				xmlChar* value = xmlNodeListGetString(cur->doc, attributeOfTheNode->children, 1);
				std::string theValueOfAttr = BStoString(value);
				theNodeValues[currentLine]->theCharArray2DAttributes[j][0] = NULL;
				strcpy(theNodeValues[currentLine]->theCharArray2DAttributes[j], theValueOfAttr.c_str());
				break;
			}
			j++;
		}
        
		i++;
		attributeOfTheNode = attributeOfTheNode->next;
	}
}



void BSXmlFiles::writeAnyXML(char docName[], std::string headNodeString, std::string secondNodeString,
                             char theNodes[][100], ListaDeCaractere *theNodeValues[],
                             char headAttributesNames[][100], char headAttributesValues[][100],
                             int nrOfNodes, int nrOfLines, int nrOfAttributes, int nrOfHeadAttributes)
{
	char headNode[100] = "";
	strcpy(headNode, headNodeString.c_str());
	char secondNode[100] = "";
	strcpy(secondNode, secondNodeString.c_str());
    
	xmlTextWriterPtr writer;
	writer = xmlNewTextWriterFilename(docName, 0);
    
    
	xmlTextWriterStartDocument(writer, NULL, (const char*) "UTF-8", NULL);
	xmlTextWriterStartElement(writer, (const xmlChar*)headNode);
    
	int k = 0;//retine primul attribute care va fi dat in continut
    
	for(int i = 0 ; i < nrOfHeadAttributes; i++)
	{
		xmlTextWriterWriteAttribute(writer, (const xmlChar*)headAttributesNames[i], (const xmlChar*)headAttributesValues[i]);
		k = i;
	}
    
	int i = 0;
	while(i < nrOfLines)
	{
		xmlTextWriterStartElement(writer, (const xmlChar*)secondNode);
        
		if(nrOfAttributes != nrOfHeadAttributes)
		{
			for(int w = k + 1; w < nrOfAttributes ; w++)
			{
				xmlTextWriterWriteAttribute(writer, (const xmlChar*)headAttributesNames[w], (const xmlChar*)headAttributesValues[w]);
			}
		}
        
		int j = 0;
		while(j < nrOfNodes)
		{
			xmlTextWriterWriteElement(writer, (const xmlChar*)theNodes[j], (const xmlChar*)theNodeValues[i]->theCharArray2D[j]);
			j++;
		}
        
		xmlTextWriterEndElement(writer);
		i++;
	}
    
	xmlTextWriterEndElement(writer);
	xmlTextWriterEndDocument(writer);
	xmlFreeTextWriter(writer);
}




