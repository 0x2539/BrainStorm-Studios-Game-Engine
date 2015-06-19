#ifndef XMLFILES_H_INCLUDED
#define XMLFILES_H_INCLUDED

#include <iostream>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/xmlwriter.h>
#include "BSValues.h"

class BSXmlFiles
{
public:

	void parseStory (xmlDocPtr doc, xmlNodePtr cur);
	void writeXML();
	void parseDoc(char *docname);





	void readAnyXML(std::string docnameString, std::string headNodeString, std::string secondNodeString,
					ListaDeCaractere *theNodeValues[], char theNodes[][100],
					char theProperties[][100], ListaDeCaractere *headAttributesValues[],
					int nrOfNodes, int NrOfProperties);

	void parseAnyStory(xmlDocPtr doc, xmlNodePtr cur,
						ListaDeCaractere *theNodeValues[], char theNodes[][100], int nrOfNodes, int currentLine);
	void parseAnyStoryAttributes(xmlDocPtr doc, xmlNodePtr cur, ListaDeCaractere* theNodeValues[], char attributesOfNode[][100],
								int NrOfProperties, int currentLine);



	void writeAnyXML(char docName[], std::string headNodeString, std::string secondNodeString,
							char theNodes[][100], ListaDeCaractere *theNodeValues[],
							char headAttributesNames[][100], char headAttributesValues[][100],
							int nrOfNodes, int nrOfLines, int nrOfAttributes, int nrOfHeadAttributes);
};

#endif // XMLFILES_H_INCLUDED
