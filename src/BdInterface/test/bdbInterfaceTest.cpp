/********************************************************************
*
*            Author: jkdirac- jiangkun1@gmail.com
*
*
*
*            Last modified: 2010-08-10 16:11
*
*            Filename: bdbInterfaceTest.cpp
*
*            Description: .
*
*******************************************************************/
#include "bdbInterface.h"
#include "bdbInterfaceTest.h"
#include <string>
#include <vector>

#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QDirIterator>
#include <QVector>
//#include "debugOutput.h"

using namespace std;

bdbXMLInterface test_inter;
const string XML_FILE_HOME = "../../database";

void test_init()
{
	QString path_name(XML_FILE_HOME.c_str());
	QDirIterator dir_itr(path_name, QDir::Files, QDirIterator::Subdirectories);
	bdbXMLInterface db_interface;
	while (dir_itr.hasNext())
	{
		QString cur_pathname = dir_itr.next();

		QFileInfo cur_file(cur_pathname);
		if (!cur_file.isFile())
			continue;

		QString cur_filename = cur_file.fileName();

		//file name is ended with .xml?
		QString xml_ext(".xml");
		if (!cur_filename.endsWith(xml_ext, Qt::CaseInsensitive))
		{
			continue;
		}
		else 
		{
			int str_len = cur_filename.size();
			cur_filename.remove(str_len - 4, 4);
		}

		BdRetVal bsucc = db_interface.add_files(cur_pathname.toStdString(), cur_filename.toStdString());
		//add to directory
	}
}

void test_get_speice_link()
{
	vector<string> result;
	string res;
	
//        test_inter.get_species_link("cIlam156_dimer" , result);
//        test_inter.get_species_module_id("cIlam156_dimer" , result);
	string doc = "cIlam156_dimer"; 
	string node_path = "/species/link/index";
	test_inter.get_node_element(SPECIES, &doc, &node_path, result);

	doc = "cIlam156_dimer"; 
	node_path = "/species/structure/listOfChains/chain/module/@id";
	test_inter.get_node_attr(SPECIES, &doc, &node_path, result);

	doc = "cIlam156_dimer"; 
	node_path = "/species/structure/listOfChains/chain/module";
	test_inter.get_node(SPECIES, &doc, &node_path, res);

}

void test_get_module_num()
{
	int res;
	vector<string> docs;
	vector<string> paths;

	docs.push_back("placI185_dna"); paths.push_back("/species/structure/listOfChains/chain");

	for (int i=0; i<docs.size(); i++)
	{
		res = test_inter.get_node_element_num(SPECIES, &docs[i], &paths[i]);
		cout << "test_get_module_num num:" << res << endl;
	}
}

void test_get_node_element()
{
	vector<string> docs;
	vector<string> paths;

	docs.push_back("listOfFunctionDefinitions"); paths.push_back("/sbpmodel/predef/listOfFunctionDefinitions/functionDefinition[1]");
	docs.push_back("listOfFunctionDefinitions"); paths.push_back("/sbpmodel/predef/listOfFunctionDefinitions/functionDefinition[1]/math");
	docs.push_back("listOfFunctionDefinitions"); paths.push_back("/sbpmodel/predef/listOfFunctionDefinitions/functionDefinition[1]/math/lambda");
	docs.push_back("listOfFunctionDefinitions"); paths.push_back("/sbpmodel/predef/listOfFunctionDefinitions/functionDefinition[1]/id");
	docs.push_back("listOfFunctionDefinitions"); paths.push_back("/sbpmodel/predef/listOfFunctionDefinitions/functionDefinition[1]/name");
	vector<string> res_str;

	cout << "-------- test get nodes element start---------" << endl;
	for (int i=0; i<docs.size(); i++)
	{
		try
		{
			cout << "test get node element: " << i << endl;
			test_inter.get_node_element(PREDEF, &docs[i], &paths[i], res_str);
			for (int j=0; j<res_str.size(); j++)
			{
				cout << "==element: " << j << " " << res_str[j] << endl;
			}
		}
		catch (XmlException &se)
		{
			cout << "test get node error" << endl;
		}
	}
	cout << "-------- test get nodes element end---------" << endl;
}

void test_get_node()
{
	vector<string> docs;
	vector<string> paths;

	docs.push_back("listOfFunctionDefinitions"); paths.push_back("//math");
	string res_str;

	cout << "-------- test get nodes start---------" << endl;
	for (int i=0; i<docs.size(); i++)
	{
		try
		{
			string prefix="";
			string uri = "http://www.w3.org/1998/Math/MathML";
//                        test_inter.get_node(PREDEF, &docs[i], &paths[i], res_str);
//                        cout << "test get node: " << i << " " << res_str << endl;
			res_str.clear();
			test_inter.get_node(PREDEF, &docs[i], &paths[i], res_str, "", uri);
			cout << "test get node with namespace: " << i << " " << res_str << endl;
		}
		catch (XmlException &se)
		{
			cout << "test get node error" << endl;
		}
	}
	cout << "-------- test get nodes end---------" << endl;
}

int main()
{
	try
	{
//                test_init();
		test_inter.add_directory(XML_FILE_HOME);
		test_get_node();
		test_get_node_element();
		test_get_speice_link();
		test_get_module_num();
	} 
	catch (XmlException &se)
	{
		cout << "[Exception code] " << se.getExceptionCode() << " [description]: " << se.what() << endl;
	}

}
