#include <stdio.h>
#include <string.h>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>

#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

#define MY_ENCODING "ISO-8859-1"
const string startString = "string";
const string endString = "string";

class node
{ 
	node() {};
	virtual ~node() {};
};

class moduleNode : public node
{
	public:
		enum MODULE_STRING
		{
			modetype = 0,
			id, 
			name,
			class_name,
			regid,            
			part_url,          
			part_short_desc,
			fw_prom_eff,
			rev_prom_eff,
			fw_term_eff,
			rev_term_eff,
			fw_rbs_eff,
			rev_rbs_eff,
			fw_start_codon,
			rev_start_codon,
			fw_stop_codon,
			rev_stop_codon,
			listOfSpeciesLinks,
			size,
			unit,
			ph,
			temperature,
			light,
			constant,
			copies,
			origin,
			chassis,
			resistence,
			constant,
			can_be_empty,
			MODULE_STRING_NUM
		};

		vector<string> module_strings;
		MODULE_STRING lookup_idx(string input)
		{
			map<string, MODULE_STRING>::iterator itr;
			itr = string_maps.find(input);
			if (itr != string_maps.end())
				return itr->second;
			else
				return -1;
		};

		moduleNode():node() 
		{
			module_strings.clear();
			module_strings.resize(MODULE_STRING_NUM);

			string_maps.insert(pair<string, MODULE_STRING>("type",module_type));
			string_maps.insert(pair<string, MODULE_STRING>("id",id));
			string_maps.insert(pair<string, MODULE_STRING>("name",name));
			string_maps.insert(pair<string, MODULE_STRING>("class",class_name));
			string_maps.insert(pair<string, MODULE_STRING>("regid",regid));
			string_maps.insert(pair<string, MODULE_STRING>("part_url",part_url));
			string_maps.insert(pair<string, MODULE_STRING>("part_short_desc",part_short_desc));
			string_maps.insert(pair<string, MODULE_STRING>("fw_prom_eff",fw_prom_eff));
			string_maps.insert(pair<string, MODULE_STRING>("rev_prom_eff",rev_prom_eff));
			string_maps.insert(pair<string, MODULE_STRING>("fw_term_eff",fw_term_eff));
			string_maps.insert(pair<string, MODULE_STRING>("rev_term_eff",rev_term_eff));
			string_maps.insert(pair<string, MODULE_STRING>("fw_rbs_eff",fw_rbs_eff));
			string_maps.insert(pair<string, MODULE_STRING>("rev_rbs_eff",rev_rbs_eff));
			string_maps.insert(pair<string, MODULE_STRING>("fw_start_codon",fw_start_codon));
			string_maps.insert(pair<string, MODULE_STRING>("rev_start_codon",rev_start_codon));
			string_maps.insert(pair<string, MODULE_STRING>("fw_stop_codon",fw_stop_codon));
			string_maps.insert(pair<string, MODULE_STRING>("rev_stop_codon",rev_stop_codon));
			string_maps.insert(pair<string, MODULE_STRING>("listOfSpeciesLinks",listOfSpeciesLinks));
			string_maps.insert(pair<string, MODULE_STRING>("size",size));
			string_maps.insert(pair<string, MODULE_STRING>("unit",unit));
			string_maps.insert(pair<string, MODULE_STRING>("ph",ph));
			string_maps.insert(pair<string, MODULE_STRING>("temperature",temperature));
			string_maps.insert(pair<string, MODULE_STRING>("light",light));
			string_maps.insert(pair<string, MODULE_STRING>("constant",constant));
			string_maps.insert(pair<string, MODULE_STRING>("copies",copies));
			string_maps.insert(pair<string, MODULE_STRING>("origin",origin));
			string_maps.insert(pair<string, MODULE_STRING>("chassis",chassis));
			string_maps.insert(pair<string, MODULE_STRING>("resistence",resistence));
			string_maps.insert(pair<string, MODULE_STRING>("constant",constant));
			string_maps.insert(pair<string, MODULE_STRING>("can_be_empty",can_be_empty));
			string_maps.insert(pair<string, MODULE_STRING>("MODULE_STRING_NUM",MODULE_STRING_NUM  ));
		};

		~moduleNode() {}

	private:
		map<string, MODULE_STRING> string_maps;
};

class speciesNode
{
};

void testXmlwriterFilename(const char *uri);
xmlChar *ConvertInput(const char *in, const char *encoding);
void parserFile(char *file_name);
void generateSpecFile();
void generateReacFile();
void generateModlueFile(moduleNode *pnode);

int main(int argc, char** argv)
{
	if (argc <= 1)	
		return 0;

	for (int i=1; i < argc; i++)
	{
		parserFile(argv[i]);
	}
	return 0;
}

//start type
//key value
//end
void parserFile(char *file_name)
{
	ifstream scrip_file(file_name, ios::in);

	if (!scrip_file)
		return;

	string parse_string;
	while (!scrip_file.eof())
	{
		scrip_file >> parse_string;

		if (parse_string == startString)
		{
			scrip_file >> parse_string;
//                        if (scrip_file == ";")
//                        {
//                                scrip_file >> parse_string;
//                        }
//                        else
//                        {
//                                cout >> "line no : after start";
//                                break;
//                        }

			scrip_file >> parse_string;
			if (parse_string == "module")
			{
				moduleNode* p_node = new moduleNode();
				while (parse_string != endString)
				{
					scrip_file >> parse_string;
					MODULE_STRING idx = p_node->lookup_idx(parse_string);
					scrip_file >> parse_string;
					p_node->module_strings[idx] = parse_string;
				}

				generateModlueFile(p_node);
			}
			else if (parse_string == "species")
			{
			}
		}
		else
			continue;
	}
}

void generateSpecFile()
{
}

void generateReacFile()
{
}

void generateModlueFile(moduleNode *pnode)
{
}

void testXmlwriterFilename(const char *uri)
{
    int rc;
    xmlTextWriterPtr writer;
    xmlChar *tmp;

    /* Create a new XmlWriter for uri, with no compression. */
    writer = xmlNewTextWriterFilename(uri, 0);
    if (writer == NULL) {
        printf("testXmlwriterFilename: Error creating the xml writer\n");
        return;
    }

    /* Start the document with the xml default for the version,
     * encoding ISO 8859-1 and the default for the standalone
     * declaration. */
    rc = xmlTextWriterStartDocument(writer, NULL, MY_ENCODING, NULL);
    if (rc < 0) {
        printf
            ("testXmlwriterFilename: Error at xmlTextWriterStartDocument\n");
        return;
    }

    /* Start an element named "EXAMPLE". Since thist is the first
     * element, this will be the root element of the document. */
    rc = xmlTextWriterStartElement(writer, BAD_CAST "EXAMPLE");
    if (rc < 0) {
        printf
            ("testXmlwriterFilename: Error at xmlTextWriterStartElement\n");
        return;
    }

    /* Write a comment as child of EXAMPLE.
     * Please observe, that the input to the xmlTextWriter functions
     * HAS to be in UTF-8, even if the output XML is encoded
     * in iso-8859-1 */
    tmp = ConvertInput("This is a comment with special chars: <漩�>",
                       MY_ENCODING);
    rc = xmlTextWriterWriteComment(writer, tmp);
    if (rc < 0) {
        printf
            ("testXmlwriterFilename: Error at xmlTextWriterWriteComment\n");
        return;
    }
    if (tmp != NULL) xmlFree(tmp);

    /* Start an element named "ORDER" as child of EXAMPLE. */
    rc = xmlTextWriterStartElement(writer, BAD_CAST "ORDER");
    if (rc < 0) {
        printf
            ("testXmlwriterFilename: Error at xmlTextWriterStartElement\n");
        return;
    }

    /* Add an attribute with name "version" and value "1.0" to ORDER. */
    rc = xmlTextWriterWriteAttribute(writer, BAD_CAST "version",
                                     BAD_CAST "1.0");
    if (rc < 0) {
        printf
            ("testXmlwriterFilename: Error at xmlTextWriterWriteAttribute\n");
        return;
    }

    /* Add an attribute with name "xml:lang" and value "de" to ORDER. */
    rc = xmlTextWriterWriteAttribute(writer, BAD_CAST "xml:lang",
                                     BAD_CAST "de");
    if (rc < 0) {
        printf
            ("testXmlwriterFilename: Error at xmlTextWriterWriteAttribute\n");
        return;
    }

    /* Write a comment as child of ORDER */
    tmp = ConvertInput("<漩�>", MY_ENCODING);
    rc = xmlTextWriterWriteFormatComment(writer,
		     "This is another comment with special chars: %s",
		     tmp);
    if (rc < 0) {
        printf
            ("testXmlwriterFilename: Error at xmlTextWriterWriteFormatComment\n");
        return;
    }
    if (tmp != NULL) xmlFree(tmp);

    /* Start an element named "HEADER" as child of ORDER. */
    rc = xmlTextWriterStartElement(writer, BAD_CAST "HEADER");
    if (rc < 0) {
        printf
            ("testXmlwriterFilename: Error at xmlTextWriterStartElement\n");
        return;
    }

    /* Write an element named "X_ORDER_ID" as child of HEADER. */
    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "X_ORDER_ID",
                                         "%010d", 53535L);
    if (rc < 0) {
        printf
            ("testXmlwriterFilename: Error at xmlTextWriterWriteFormatElement\n");
        return;
    }

    /* Write an element named "CUSTOMER_ID" as child of HEADER. */
    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "CUSTOMER_ID",
                                         "%d", 1010);
    if (rc < 0) {
        printf
            ("testXmlwriterFilename: Error at xmlTextWriterWriteFormatElement\n");
        return;
    }

    /* Write an element named "NAME_1" as child of HEADER. */
    tmp = ConvertInput("M黮ler", MY_ENCODING);
    rc = xmlTextWriterWriteElement(writer, BAD_CAST "NAME_1", tmp);
    if (rc < 0) {
        printf
            ("testXmlwriterFilename: Error at xmlTextWriterWriteElement\n");
        return;
    }
    if (tmp != NULL) xmlFree(tmp);

    /* Write an element named "NAME_2" as child of HEADER. */
    tmp = ConvertInput("J鰎g", MY_ENCODING);
    rc = xmlTextWriterWriteElement(writer, BAD_CAST "NAME_2", tmp);
    if (rc < 0) {
        printf
            ("testXmlwriterFilename: Error at xmlTextWriterWriteElement\n");
        return;
    }
    if (tmp != NULL) xmlFree(tmp);

    /* Close the element named HEADER. */
    rc = xmlTextWriterEndElement(writer);
    if (rc < 0) {
        printf
            ("testXmlwriterFilename: Error at xmlTextWriterEndElement\n");
        return;
    }

    /* Start an element named "ENTRIES" as child of ORDER. */
    rc = xmlTextWriterStartElement(writer, BAD_CAST "ENTRIES");
    if (rc < 0) {
        printf
            ("testXmlwriterFilename: Error at xmlTextWriterStartElement\n");
        return;
    }

    /* Start an element named "ENTRY" as child of ENTRIES. */
    rc = xmlTextWriterStartElement(writer, BAD_CAST "ENTRY");
    if (rc < 0) {
        printf
            ("testXmlwriterFilename: Error at xmlTextWriterStartElement\n");
        return;
    }

    /* Write an element named "ARTICLE" as child of ENTRY. */
    rc = xmlTextWriterWriteElement(writer, BAD_CAST "ARTICLE",
                                   BAD_CAST "<Test>");
    if (rc < 0) {
        printf
            ("testXmlwriterFilename: Error at xmlTextWriterWriteElement\n");
        return;
    }

    /* Write an element named "ENTRY_NO" as child of ENTRY. */
    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "ENTRY_NO", "%d",
                                         10);
    if (rc < 0) {
        printf
            ("testXmlwriterFilename: Error at xmlTextWriterWriteFormatElement\n");
        return;
    }

    /* Close the element named ENTRY. */
    rc = xmlTextWriterEndElement(writer);
    if (rc < 0) {
        printf
            ("testXmlwriterFilename: Error at xmlTextWriterEndElement\n");
        return;
    }

    /* Start an element named "ENTRY" as child of ENTRIES. */
    rc = xmlTextWriterStartElement(writer, BAD_CAST "ENTRY");
    if (rc < 0) {
        printf
            ("testXmlwriterFilename: Error at xmlTextWriterStartElement\n");
        return;
    }

    /* Write an element named "ARTICLE" as child of ENTRY. */
    rc = xmlTextWriterWriteElement(writer, BAD_CAST "ARTICLE",
                                   BAD_CAST "<Test 2>");
    if (rc < 0) {
        printf
            ("testXmlwriterFilename: Error at xmlTextWriterWriteElement\n");
        return;
    }

    /* Write an element named "ENTRY_NO" as child of ENTRY. */
    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "ENTRY_NO", "%d",
                                         20);
    if (rc < 0) {
        printf
            ("testXmlwriterFilename: Error at xmlTextWriterWriteFormatElement\n");
        return;
    }

    /* Close the element named ENTRY. */
    rc = xmlTextWriterEndElement(writer);
    if (rc < 0) {
        printf
            ("testXmlwriterFilename: Error at xmlTextWriterEndElement\n");
        return;
    }

    /* Close the element named ENTRIES. */
    rc = xmlTextWriterEndElement(writer);
    if (rc < 0) {
        printf
            ("testXmlwriterFilename: Error at xmlTextWriterEndElement\n");
        return;
    }

    /* Start an element named "FOOTER" as child of ORDER. */
    rc = xmlTextWriterStartElement(writer, BAD_CAST "FOOTER");
    if (rc < 0) {
        printf
            ("testXmlwriterFilename: Error at xmlTextWriterStartElement\n");
        return;
    }

    /* Write an element named "TEXT" as child of FOOTER. */
    rc = xmlTextWriterWriteElement(writer, BAD_CAST "TEXT",
                                   BAD_CAST "This is a text.");
    if (rc < 0) {
        printf
            ("testXmlwriterFilename: Error at xmlTextWriterWriteElement\n");
        return;
    }

    /* Close the element named FOOTER. */
    rc = xmlTextWriterEndElement(writer);
    if (rc < 0) {
        printf
            ("testXmlwriterFilename: Error at xmlTextWriterEndElement\n");
        return;
    }

    /* Here we could close the elements ORDER and EXAMPLE using the
     * function xmlTextWriterEndElement, but since we do not want to
     * write any other elements, we simply call xmlTextWriterEndDocument,
     * which will do all the work. */
    rc = xmlTextWriterEndDocument(writer);
    if (rc < 0) {
        printf
            ("testXmlwriterFilename: Error at xmlTextWriterEndDocument\n");
        return;
    }

    xmlFreeTextWriter(writer);
}

xmlChar *ConvertInput(const char *in, const char *encoding)
{
	xmlChar *out;
	int ret;
	int size;
	int out_size;
	int temp;
	xmlCharEncodingHandlerPtr handler;

	if (in == 0)
		return 0;

	handler = xmlFindCharEncodingHandler(encoding);

	if (!handler) {
		printf("ConvertInput: no encoding handler found for '%s'\n",
				encoding ? encoding : "");
		return 0;
	}

	size = (int) strlen(in) + 1;
	out_size = size * 2 - 1;
	out = (unsigned char *) xmlMalloc((size_t) out_size);

	if (out != 0) {
		temp = size - 1;
		ret = handler->input(out, &out_size, (const xmlChar *) in, &temp);
		if ((ret < 0) || (temp - size + 1)) {
			if (ret < 0) {
				printf("ConvertInput: conversion wasn't successful.\n");
			} else {
				printf
					("ConvertInput: conversion wasn't successful. converted: %i octets.\n",
					 temp);
			}

			xmlFree(out);
			out = 0;
		} else {
			out = (unsigned char *) xmlRealloc(out, out_size + 1);
			out[out_size] = 0;  /*null terminating out */
		}
	} else {
		printf("ConvertInput: no mem\n");
	}

	return out;
}
