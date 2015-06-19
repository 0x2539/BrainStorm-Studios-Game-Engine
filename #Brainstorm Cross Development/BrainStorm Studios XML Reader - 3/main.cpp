#include <iostream>
#include <fstream>
#include <vector>

struct BSAttribute
{
    std::string name, value;
};

struct BSNodeXml
{
    ///std::vector<BSAttribute> attributes;
    std::string name;///, value;
    bool checked;
};


struct ListaDeCaractere
{
	std::string theCharArray1D;
	std::vector<std::string> theCharArray2D;
	std::vector<std::string> theCharArray2DAttributes;
};

void getTheFileAsString(std::string fileName, std::string &theString)
{
    std::ifstream fin(fileName.c_str());
    theString = "";
    std::string readingLine;

    while(getline(fin, readingLine))
    {
        theString += readingLine;
    }
}


bool checkElementNames(std::string el1, std::string el2)
{
    if(el1 != el2)
    {
        return false;
    }
    return true;
}


bool checkIfNodeIsWanted(std::string node, std::vector<std::string> theNodes)
{
    for(int i = 0; i < theNodes.size(); i++)
    {
        if(node == theNodes[i])
        {
            return true;
        }
    }
    return false;
}



bool readTheXmlFile(std::string fileName, std::string headNode, std::string secondNode, std::vector<std::string> theNodes, std::vector<std::string> theAttributes, std::vector<ListaDeCaractere*> &theNodeValues, std::vector<std::string> &headAttributesValues)
{
    std::string moFoLongString;
    getTheFileAsString(fileName, moFoLongString);

    bool encoding = false;
    std::string sEncoding = "";
    int lastPosition = 0;

    for(int i = 0; i < moFoLongString.size(); i++)
    {
        lastPosition = i + 1;
        sEncoding += moFoLongString[i];
        if(moFoLongString[i] == '>')
        {
            encoding  = true;
            break;
        }
    }
    if(sEncoding != "<?xml version=\"1.0\" encoding=\"UTF-8\"?>")
    {
        std::cout<<"The encoding is not good buddy!!"<<'\n'<<"It should be: "<<"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"<<'\n';
        return false;
    }
//    std::cout<<sEncoding<<'\n';

    std::vector<BSNodeXml> listOfActualNodes;

    std::string elementName1 =  "", elementName2 =  "", elementValue =  "", attributeName =  "", attributeValue =  "";
    bool readsAnElementName1 = false, readsAnElementName2 = false, readsAnElementValue = false, readsAnAttributeName = false, readsAnAttributeValue = false;

    for(int i = lastPosition; i < moFoLongString.size(); i++)
    {
        if(moFoLongString[i] == '<')
        {
            readsAnElementName1 = true; readsAnElementValue = false; readsAnAttributeName = false; readsAnAttributeValue = false;
            if(moFoLongString[i + 1] == '/')
            {
                readsAnElementName1 = false; readsAnElementName2 = true;
                i++;
            }
            else
            {
                BSNodeXml newNode;
                listOfActualNodes.push_back(newNode);
            }
            continue;
        }
        else
            if(moFoLongString[i] == ' ' && !readsAnAttributeValue)
            {
                if(attributeValue != "" && attributeName != "")
                {
                    BSAttribute atribut;
                    atribut.name = attributeName;
                    atribut.value = attributeValue;


                    headAttributesValues.push_back(attributeValue);
                    ///theNodeValues.back()->theCharArray2DAttributes.push_back(attributeValue);
                    ///listOfActualNodes.back().attributes.push_back(atribut);
                }
                attributeName = ""; attributeValue = "";

                readsAnElementName1 = false; readsAnElementName2 = false; readsAnElementValue = false; readsAnAttributeName = true; readsAnAttributeValue = false;
                continue;
            }
            else
                if(moFoLongString[i] == '=' && moFoLongString[i + 1] == '"' && !readsAnElementValue)
                {
                    readsAnElementName1 = false; readsAnElementName2 = false; readsAnElementValue = false; readsAnAttributeName = false; readsAnAttributeValue = true;
                    i++;
                    continue;
                }
                else
                    if(moFoLongString[i] == '"' && !readsAnElementValue)
                    {
                        if(attributeValue != "" && attributeName != "")
                        {
                            BSAttribute atribut;
                            atribut.name = attributeName;
                            atribut.value = attributeValue;

                            headAttributesValues.push_back(attributeValue);
                            ///theNodeValues.back()->theCharArray2DAttributes.push_back(attributeValue);
                            ///listOfActualNodes.back().attributes.push_back(atribut);
                        }
                        attributeName = ""; attributeValue = "";

                        readsAnElementName1 = false; readsAnElementName2 = false; readsAnElementValue = false; readsAnAttributeName = false; readsAnAttributeValue = false;
                        continue;
                    }
                    else
                        if(moFoLongString[i] == '>')
                        {
                            readsAnElementValue = true;
                            if(readsAnElementName2)
                            {
                                int index = 0;
                                for(int j = listOfActualNodes.size() - 1; j >= 0; j--)
                                {
                                    if(listOfActualNodes[j].checked != true)
                                    {
                                        index = j;
                                        break;
                                    }
                                }
                                readsAnElementValue = false;
                                if(!checkElementNames(listOfActualNodes[index].name, elementName2))
                                {
                                    std::cout<<"The element names do not match: "<<listOfActualNodes.back().name<<' '<<elementName2<<". Position: "<<i<<'\n';
                                    return false;
                                }
                                else
                                {
                                    if(elementName2 == secondNode)
                                    {
//                                        std::cout<<"    "<<elementName2<<'\n'<<'\n';
                                    }
                                    else
                                        if(elementName2 == headNode)
                                        {
//                                            std::cout<<elementName2<<'\n';
                                        }
                                        else
                                        {
                                            if(checkIfNodeIsWanted(elementName2, theNodes))
                                            {
                                                theNodeValues.back()->theCharArray2D.push_back(elementValue);
                                            }

//                                            std::cout<<"        "<<elementName2<<' '<<elementValue<<'\n';
                                        }
                                }
                                listOfActualNodes[index].checked = true;
                                elementName1 = ""; elementName2 = ""; elementValue = ""; attributeName = ""; attributeValue = "";
                            }
                            else
                            {
                                if(elementName1 == secondNode)
                                {
                                    ListaDeCaractere *newNode = new ListaDeCaractere;
                                    theNodeValues.push_back(newNode);

//                                    std::cout<<"    "<<elementName1<<'\n';
                                }
                                else
                                    if(elementName1 == headNode)
                                    {
//                                        std::cout<<elementName1<<'\n';
                                    }
                                listOfActualNodes.back().name = elementName1;
                                elementName1 = "";
                            }

                            readsAnElementName1 = false; readsAnElementName2 = false; readsAnAttributeName = false; readsAnAttributeValue = false;

                            //for(int k = 0; k < listOfActualNodes.back().attributes.size(); k++)
                            {
//                                std::cout<<listOfActualNodes.back().listOfMoFoAttributes[k].key<<' '<<listOfActualNodes.back().listOfMoFoAttributes[k].value<<'\n';
                            }
                            continue;
                        }

        ///write the name, attribute or the value of an element
        if(readsAnElementName1)
        {
            elementName1 += moFoLongString[i];
        }
        else
            if(readsAnElementName2)
            {
                elementName2 += moFoLongString[i];
            }
            else
                if(readsAnAttributeName)
                {
                    attributeName += moFoLongString[i];
                }
                else
                    if(readsAnAttributeValue)
                    {
                        attributeValue += moFoLongString[i];
                    }
                    else
                        if(readsAnElementValue)
                        {
                            elementValue += moFoLongString[i];
                        }
    }
    return true;
}

int main()
{
    std::vector<ListaDeCaractere*> theNodeValues;
    std::vector<std::string> headAttributesValues;

    std::vector<std::string> listOfNodesNames;
    listOfNodesNames.push_back("Body_Type"); listOfNodesNames.push_back("Texture_path"); listOfNodesNames.push_back("Kill_or_Next_Level");
    listOfNodesNames.push_back("xCoordinate"); listOfNodesNames.push_back("yCoordinate"); listOfNodesNames.push_back("width"); listOfNodesNames.push_back("height");
    listOfNodesNames.push_back("userName"); listOfNodesNames.push_back("Animation_name"); listOfNodesNames.push_back("Index");

    std::vector<std::string> listOfAttributesNames;
    listOfAttributesNames.push_back("name"); listOfAttributesNames.push_back("boundary_Left");
    listOfAttributesNames.push_back("boundary_Down"); listOfAttributesNames.push_back("boundary_Up");
    listOfAttributesNames.push_back("boundary_Right"); listOfAttributesNames.push_back("script");


    if(!readTheXmlFile("level1.xml", "Level", "obstacle", listOfNodesNames, listOfAttributesNames, theNodeValues, headAttributesValues))
    {
        std::cout<<"Something is screwed up with your xml file. Come back later, after you fix it. Comprende amigo?";
        return 0;
    }

//    for(int i = 0; i < theNodeValues.size(); i++)
//    {
//        std::cout<<"obstacle"<<'\n';
//        for(int j = 0; j < theNodeValues[i]->theCharArray2D.size(); j++)
//        {
//            std::cout<<"    "<<theNodeValues[i]->theCharArray2D[j]<<'\n';
//        }
//        std::cout<<"/obstacle"<<'\n'<<'\n';
//    }
    return 0;
}
