/********************************************************************
*
*            Author: jkdirac- jiangkun1@gmail.com
*
*
*
*            Last modified:	2010-09-04 15:08
*
*            Filename:		bdbInterface.cpp
*
*            Description: .
*
*******************************************************************/
#include "bdbInterface.h"
#include <string>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QDirIterator>

using namespace std;
using namespace DbXml;


bdbXMLInterface::~bdbXMLInterface() 
{
	if (m_manager)
	{
		delete m_manager;
		m_manager = NULL;
	}
	
	if (db_env)
	{
//                db_env->close(db_env, DB_FORCE);
	}
}

bdbXMLInterface::bdbXMLInterface():db_env_home("dbs"),
	db_container_name("ustc.dbxml")
{
	env_flags = DB_CREATE 
		| DB_INIT_LOG
		| DB_INIT_MPOOL
		| DB_INIT_LOCK;

	int dberr = 0;

	try 
	{
		dberr = db_env_create(&db_env, 0);
		if (dberr != 0)
		{
			throw XmlException(XmlException::NULL_POINTER, "db env create error", __FILE__, __LINE__);
//                        cout << "db env create error" << endl;
//                        return;
		}

//                db_env->set_data_dir(db_env, db_env_home.c_str());
		db_env->open(db_env, db_env_home.c_str(), env_flags, 0);
		m_manager = new XmlManager(db_env, DBXML_ADOPT_DBENV);

		if (!m_manager)
		{
			throw XmlException(XmlException::NULL_POINTER, "m_manager", __FILE__, __LINE__);
//                        return;
		}

		container_names.resize(CONT_IDX_NUM);
		container_names[SPECIES] = "Species";
		container_names[REACTION] = "Reaction";
		container_names[SYSTEM] = "System";
		container_names[DBINTERFACE] = "dbInterface";
		container_names[PART] = "Part";
		container_names[COMPARTMENT] = "Compartment";

		for (int i=0; i < container_names.size(); i++)
		{
			if (m_manager->existsContainer(container_names[i]+".dbxml") != 0)
			{
				m_containers[i] = m_manager->openContainer(container_names[i]+".dbxml");
			}
			else
			{
				m_containers[i] = m_manager->createContainer(container_names[i]+".dbxml");
			}
		}
	}
	catch (XmlException &xe)
	{
		cout << "xml exception: " << xe.what() << endl;
		throw xe;
	}
}

BdRetVal bdbXMLInterface::add_files(const string& pathname, const string& docname)
{
	XmlContainer* container = NULL;
	if (m_manager == NULL)
	{
		throw XmlException(XmlException::NULL_POINTER, "n_manager NULL", __FILE__, __LINE__);
//                return xml_exception;
	}

	QString q_pathname(pathname.c_str());
	for (int i = 0; i < CONT_IDX_NUM; i ++)
	{
		//这个有点随便了
		QString q_cont_name("database/");
		q_cont_name += (container_names[i].c_str());
		q_cont_name += "/";
		if (q_pathname.contains(q_cont_name, Qt::CaseInsensitive))
		{
			container = &m_containers[i];
		}
	}

	if (container == NULL)
	{
		throw XmlException(XmlException::NULL_POINTER, "container NULL", __FILE__, __LINE__);
//                return no_container;
	}

	try{
		XmlDocument the_doc = container->getDocument(docname);
	}
	catch (XmlException &e)
	{
//                cout << "open document xml exception: " << e.what() << " file name: " << docname << endl;
		if (e.getExceptionCode() == XmlException::DOCUMENT_NOT_FOUND)
		{
			XmlUpdateContext the_context = m_manager->createUpdateContext();
			try {
				cout << "putting file: " << pathname << " to container " << container->getName() <<
					" as doc " << docname << endl;
				XmlInputStream *the_stream =
					m_manager->createLocalFileInputStream(pathname);
				container->putDocument(docname,
						the_stream,
						the_context,
						0);
			}
			catch (XmlException &e)
			{
				cout << "xml exception: " << e.what() << endl;
				throw e;
//                                return xml_exception;
			}
		}
	}

	return no_error;
}

BdRetVal bdbXMLInterface::get_node_element (container_index container_type, 
		const string *doc, 
		const string *node_path, 
		vector<string> &res)
{
	string query_string;

	if (m_manager == NULL)
	{
		throw XmlException(XmlException::NULL_POINTER, "m_manager", __FILE__, __LINE__);
//                return xml_exception;
	}


	if (container_type >= CONT_IDX_NUM)
	{
		throw XmlException(XmlException::INVALID_VALUE, "contianer_type", __FILE__, __LINE__);
//                return para_error;
	}

	if (doc == NULL)
	{
		query_string += "collections('"
			+ container_names[container_type]
			+ ".dbxml')";
	}
	else
	{
		query_string += "doc(\"dbxml:/" 
			+ container_names[container_type] 
			+ ".dbxml/" 
			+ *doc 
			+ "\")";
	}

	if (node_path != NULL)
		query_string += *node_path;

	XmlQueryContext context = m_manager->createQueryContext();


	XmlQueryExpression qe;
	XmlResults results;
	try
	{
		qe = m_manager->prepare(query_string, context);
		results = qe.execute(context);
	}
	catch (XmlException &xe)
	{
		cout << query_string << endl;
		cout << "get_node_element in prepare xml exception: " << xe.what() << endl;
		throw xe;
//                return xml_exception;
	}

	res.clear();
	XmlValue value;
	while (results.next(value))
	{
		res.push_back(value.getFirstChild().getNodeValue());
//                cout << "Node name: " << value.getNodeName() << " value: " 
//                        << value.getFirstChild().getNodeValue() << endl;
	}

	return no_error;
}

BdRetVal bdbXMLInterface::get_node_attr(container_index container_type, 
		const string *doc, 
		const string *node_path, 
		vector<string> &res)
{
	string query_string;

	if (m_manager == NULL)
	{
		throw XmlException(XmlException::NULL_POINTER, "m_manager", __FILE__, __LINE__);
//                return xml_exception;
	}


	if (container_type >= CONT_IDX_NUM)
	{
		throw XmlException(XmlException::INVALID_VALUE, "contianer_type", __FILE__, __LINE__);
//                return para_error;
	}

	if (doc == NULL)
	{
		query_string += "collections('"
			+ container_names[container_type]
			+ ".dbxml')";
	}
	else
	{
		query_string += "doc(\"dbxml:/" 
			+ container_names[container_type] 
			+ ".dbxml/" 
			+ *doc 
			+ "\")";
	}

	if (node_path != NULL)
		query_string += *node_path;

	XmlQueryContext context = m_manager->createQueryContext();


	XmlQueryExpression qe;
	XmlResults results;
	try
	{
		qe = m_manager->prepare(query_string, context);
		results = qe.execute(context);
	}
	catch (XmlException &xe)
	{
		cout << query_string << endl;
		cout << "get_node_attr in prepare xml exception: " << xe.what() << endl;
		throw xe;
//                return xml_exception;
	}

	res.clear();
	XmlValue value;
	while (results.next(value))
	{
		res.push_back(value.getNodeValue());
//                cout << " attr: " << value.getNodeValue() << endl;
	}

	return no_error;
}

BdRetVal bdbXMLInterface::get_node(container_index container_type, 
		const string *doc, 
		const string *node_path, 
		string &res)
{
	string query_string;

	if (m_manager == NULL)
	{
		throw XmlException(XmlException::NULL_POINTER, "m_manager null", __FILE__, __LINE__);
//                return xml_exception;
	}


	if (container_type >= CONT_IDX_NUM)
	{
		throw XmlException(XmlException::INVALID_VALUE, "contianer_type", __FILE__, __LINE__);
//                return para_error;
	}

	if (doc == NULL)
	{
		query_string += "collections('"
			+ container_names[container_type]
			+ ".dbxml')";
	}
	else
	{
		query_string += "doc(\"dbxml:/" 
			+ container_names[container_type] 
			+ ".dbxml/" 
			+ *doc 
			+ "\")";
	}

	if (node_path != NULL)
		query_string += *node_path;

	XmlQueryContext context = m_manager->createQueryContext();


	XmlQueryExpression qe;
	XmlResults results;
	try
	{
		qe = m_manager->prepare(query_string, context);
		results = qe.execute(context);
	}
	catch (XmlException &xe)
	{
		cout << query_string << endl;
		cout << "get_node in prepare xml exception: " << xe.what() << endl;
		throw xe;
//                return xml_exception;
	}

	res.clear();
	XmlValue value;
	while (results.next(value))
	{
		res = value.asString();
//                cout <<  " attr: " << res << endl;
	}

	return no_error;
}

BdRetVal bdbXMLInterface::get_node(container_index container_type, 
		const string *doc, 
		const string *node_path, 
		string &res,
		const string &prefix,
		const string &uri)
{
	string query_string;

	if (m_manager == NULL)
	{
		throw XmlException(XmlException::NULL_POINTER, "m_manager null", __FILE__, __LINE__);
//                return xml_exception;
	}


	if (container_type >= CONT_IDX_NUM)
	{
		throw XmlException(XmlException::INVALID_VALUE, "contianer_type", __FILE__, __LINE__);
//                return para_error;
	}

	if (prefix == "")
	{
		query_string += "'declare default element namespace \"";
		query_string += uri;
		query_string += "\";";
	}

	if (doc == NULL)
	{
		query_string += "collections('"
			+ container_names[container_type]
			+ ".dbxml')";
	}
	else
	{
		query_string += "doc(\"dbxml:/" 
			+ container_names[container_type] 
			+ ".dbxml/" 
			+ *doc 
			+ "\")";
	}

	if (node_path != NULL)
		query_string += *node_path;

	XmlQueryContext context = m_manager->createQueryContext();

	if (prefix != "")
	{
		context.setNamespace(prefix, uri);
	}

	if (prefix == "")
	{
		query_string += "'";
	}

	XmlQueryExpression qe;
	XmlResults results;
	try
	{
		
		qe = m_manager->prepare(query_string, context);
		results = qe.execute(context);
	}
	catch (XmlException &xe)
	{
		cout << query_string << endl;
		cout << "get_node in prepare xml exception: " << xe.what() << endl;
		throw xe;
//                return xml_exception;
	}

	res.clear();
	XmlValue value;
	while (results.next(value))
	{
		res = value.asString();
//                cout <<  " attr: " << res << endl;
	}

	return no_error;
}

//BdRetVal bdbXMLInterface::get_math(container_index container_type, 
//                const string *doc, 
//                const string *node_path, 
//                string &res)
//{

//}

BdRetVal bdbXMLInterface::add_directory(const string &directory)
{
	if (directory.empty())
	{
		throw XmlException(XmlException::INVALID_VALUE, "directory", __FILE__, __LINE__);
//                return para_error;
	}

	QString path_name(directory.c_str());
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

		try
		{
			BdRetVal bsucc = db_interface.add_files(cur_pathname.toStdString(), cur_filename.toStdString());
		}
		catch (XmlException &se)
		{
			cout << "cannot get right container for file " << cur_pathname.toStdString() << endl;
		}

		//add to directory
	}
}

int bdbXMLInterface::get_node_element_num (container_index container_type, 
		const string *doc, 
		const string *node_path)
{
	string query_string;
	int res = 0;

	if (m_manager == NULL)
	{
		throw XmlException(XmlException::NULL_POINTER, "m_manager", __FILE__, __LINE__);
//                return xml_exception;
	}


	if (container_type >= CONT_IDX_NUM)
	{
		throw XmlException(XmlException::INVALID_VALUE, "contianer_type", __FILE__, __LINE__);
//                return para_error;
	}

	if (doc == NULL)
	{
		query_string += "count(collections('"
			+ container_names[container_type]
			+ ".dbxml')";
	}
	else
	{
		query_string += "count(doc(\"dbxml:/" 
			+ container_names[container_type] 
			+ ".dbxml/" 
			+ *doc 
			+ "\")";
	}

	if (node_path != NULL)
		query_string += *node_path;

	query_string += ")";
	XmlQueryContext context = m_manager->createQueryContext();

	XmlQueryExpression qe;
	XmlResults results;
	try
	{
		qe = m_manager->prepare(query_string, context);
		results = qe.execute(context);
	}
	catch (XmlException &xe)
	{
		cout << query_string << endl;
		cout << "get_node_attr_num exception: " << xe.what() << endl;
		throw xe;
//                return xml_exception;
	}

	XmlValue value;
	results.next(value);
	if (value.isNumber())
		res = (int)value.asNumber();
	else
		res = 0;

	return res;
}
