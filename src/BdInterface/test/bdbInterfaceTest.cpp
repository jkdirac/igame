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

#include "DebugOut.h"
//#include "debugOutput.h"

using namespace std;

bdbXMLInterface test_inter;
const string XML_FILE_HOME = "../../../database";

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

		BdRetVal bsucc = db_interface.add_files(
				cur_pathname.toStdString(), 
				cur_filename.toStdString()
				);
		//add to directory
	}
}


void test_get_module_num()
{
	int res;
	vector<string> docs;
	vector<string> paths;

	for (int i=0; i<docs.size(); i++)
	{
		debugOut() << "test: [" << i << "]" << endl;
		res = test_inter.get_node_element_num(SPECIES, &docs[i], &paths[i]);
		debugOut() << "test_get_module_num num:" << res << endl;
	}
}

void test_get_node_element()
{
	vector<string> docs;
	vector<string> paths;
	vector<container_index> types;

	types.push_back(DBINTERFACE); docs.push_back("input"); paths.push_back("/MoDeL/math/csymbol");
	types.push_back(SYSTEM); docs.push_back("rules"); paths.push_back("/MoDeL/system/listOfRules/assignmentRule/math/csymbol");
	vector<string> res_str;

	debugOut() << "-------- test get nodes element start---------" << endl;
	for (int i=0; i<docs.size(); i++)
	{
		try
		{
			res_str.clear();
			debugOut() << "test: [" << i << "]" << endl;
			test_inter.get_node_element(types[i], &docs[i], &paths[i], res_str);
			for (int j=0; j<res_str.size(); j++)
			{
				debugOut() << "==element: " << j << " " << res_str[j] << endl;
			}
		}
		catch (XmlException &se)
		{
			debugOut() << "test get node error" << endl;
		}
	}
	debugOut() << "-------- test get nodes element end---------" << endl;
}

void test_get_node()
{
	vector<string> docs;
	vector<string> paths;
	vector<container_index> types;

	types.push_back(DBINTERFACE); docs.push_back("input"); paths.push_back("/MoDeL/math");
	types.push_back(SYSTEM); docs.push_back("rules"); paths.push_back("/MoDeL/system/listOfRules/assignmentRule");
	types.push_back(SYSTEM); docs.push_back("rules"); paths.push_back("/MoDeL/system/listOfRules/assignmentRule[1]/math");
	
	string res_str;

	debugOut() << "-------- test get nodes start---------" << endl;
	for (int i=0; i<docs.size(); i++)
	{
		try
		{
			debugOut() << "test: [" << i << "]" << endl;
			res_str.clear();
			test_inter.get_node(types[i], &docs[i], &paths[i], res_str);
			debugOut() << "node: " << res_str << endl;
		}
		catch (XmlException &se)
		{
			debugOut() << "test get node error" << se.what() << endl;
		}
	}
	debugOut() << "-------- test get nodes end---------" << endl;
}

void test_get_node_attr()
{
	vector<string> docs;
	vector<string> paths;
	vector<container_index> types;

	types.push_back(SYSTEM); docs.push_back("rules"); paths.push_back("/MoDeL/system/listOfRules/assignmentRule/math/csymbol/@encoding");
	vector<string> res_str;

	debugOut() << "-------- test get nodes attr start---------" << endl;
	for (int i=0; i<docs.size(); i++)
	{
		try
		{
			res_str.clear();
			debugOut() << "test: [" << i << "]" << endl;
			test_inter.get_node_attr(types[i], &docs[i], &paths[i], res_str);
			for (int j=0; j<res_str.size(); j++)
			{
				debugOut() << "==attr: " << j << " " << res_str[j] << endl;
			}
		}
		catch (XmlException &se)
		{
			debugOut() << "test get attr error" << se.what() << endl;
		}
	}
	debugOut() << "-------- test get nodes element end---------" << endl;
}

void test_get_ids()
{
	vector<container_index> types;

	types.push_back(PART); 
	types.push_back(COMPARTMENT); 
	vector<string> res_str;

	debugOut() << "-------- test get ids start---------" << endl;
	for (int i=0; i<types.size(); i++)
	{
		try
		{
			res_str.clear();
			debugOut() << "test: [" << i << "]" << endl;
			test_inter.get_ids_bycontainer(types[i], res_str);
			for (int j=0; j<res_str.size(); j++)
			{
				debugOut() << "==id: " << j << " " << res_str[j] << endl;
			}
		}
		catch (XmlException &se)
		{
			debugOut() << "test get ids error" << se.what() << endl;
		}
	}
	debugOut() << "-------- test get ids end---------" << endl;
}

int main()
{
	try
	{
		test_inter.add_directory(XML_FILE_HOME);

		debugOut() << endl;
		test_get_node();
		debugOut() << endl;
		test_get_node_element();
		debugOut() << endl;
		test_get_node_attr();
		debugOut() << endl;
		test_get_module_num();
		debugOut() << endl;
		test_get_ids();
		debugOut() << endl;
	} 
	catch (XmlException &se)
	{
		debugOut() << "[Exception code] " << se.getExceptionCode() << " [description]: " << se.what() << endl;
	}

}
