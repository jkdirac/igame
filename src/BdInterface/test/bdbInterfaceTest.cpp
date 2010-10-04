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

		BdRetVal bsucc = db_interface.add_files(cur_pathname.toStdString(), cur_filename.toStdString());
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
		cout << "test: [" << i << "]" << endl;
		res = test_inter.get_node_element_num(SPECIES, &docs[i], &paths[i]);
		cout << "test_get_module_num num:" << res << endl;
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

	cout << "-------- test get nodes element start---------" << endl;
	for (int i=0; i<docs.size(); i++)
	{
		try
		{
			res_str.clear();
			cout << "test: [" << i << "]" << endl;
			test_inter.get_node_element(types[i], &docs[i], &paths[i], res_str);
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
	vector<container_index> types;

	types.push_back(DBINTERFACE); docs.push_back("input"); paths.push_back("/MoDeL/math");
	types.push_back(SYSTEM); docs.push_back("rules"); paths.push_back("/MoDeL/system/listOfRules/assignmentRule/math");
	string res_str;

	cout << "-------- test get nodes start---------" << endl;
	for (int i=0; i<docs.size(); i++)
	{
		try
		{
			cout << "test: [" << i << "]" << endl;
			res_str.clear();
			test_inter.get_node(types[i], &docs[i], &paths[i], res_str);
			cout << "node: " << res_str << endl;
		}
		catch (XmlException &se)
		{
			cout << "test get node error" << se.what() << endl;
		}
	}
	cout << "-------- test get nodes end---------" << endl;
}

void test_get_node_attr()
{
	vector<string> docs;
	vector<string> paths;
	vector<container_index> types;

	types.push_back(SYSTEM); docs.push_back("rules"); paths.push_back("/MoDeL/system/listOfRules/assignmentRule/math/csymbol/@encoding");
	vector<string> res_str;

	cout << "-------- test get nodes attr start---------" << endl;
	for (int i=0; i<docs.size(); i++)
	{
		try
		{
			res_str.clear();
			cout << "test: [" << i << "]" << endl;
			test_inter.get_node_attr(types[i], &docs[i], &paths[i], res_str);
			for (int j=0; j<res_str.size(); j++)
			{
				cout << "==attr: " << j << " " << res_str[j] << endl;
			}
		}
		catch (XmlException &se)
		{
			cout << "test get attr error" << se.what() << endl;
		}
	}
	cout << "-------- test get nodes element end---------" << endl;
}

int main()
{
	try
	{
		test_inter.add_directory(XML_FILE_HOME);

		cout << endl;
		test_get_node();
		cout << endl;
		test_get_node_element();
		cout << endl;
		test_get_node_attr();
		cout << endl;
		test_get_module_num();
		cout << endl;
	} 
	catch (XmlException &se)
	{
		cout << "[Exception code] " << se.getExceptionCode() << " [description]: " << se.what() << endl;
	}

}
