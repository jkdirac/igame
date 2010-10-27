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
#include "GlobalSetting.h"
#include "DebugOut.h"

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

bdbXMLInterface::bdbXMLInterface()
{
	env_flags = DB_CREATE 
		| DB_INIT_LOG
		| DB_INIT_MPOOL
		| DB_INIT_LOCK;

	int dberr = 0;
	bool b_succ = false;

	sys_home_path = QDir::homePath();

	db_env_home = "dbs";
	igame_home_path = get_igame_home_dir();

	QDir dir(igame_home_path);
	if (!dir.exists(db_env_home))
	{
		b_succ = dir.mkdir(db_env_home);

		if (!b_succ)
		{
			debugOut() << dir.path().toLatin1().constData() << endl;
			throw XmlException(XmlException::NULL_POINTER, "db env create dbs dir error", __FILE__, __LINE__);
		}
	}
	db_env_home = dir.path() + "/" + db_env_home;
	debugOut() << db_env_home.toLatin1().constData() << endl;

	try 
	{
		dberr = db_env_create(&db_env, 0);
		if (dberr != 0)
		{
			throw XmlException(XmlException::NULL_POINTER, "db env create error", __FILE__, __LINE__);
		}

		db_env->open(db_env, db_env_home.toLatin1().constData(), env_flags, 0);
		m_manager = new XmlManager(db_env, DBXML_ADOPT_DBENV);

		if (!m_manager)
		{
			throw XmlException(XmlException::NULL_POINTER, "m_manager", __FILE__, __LINE__);
		}

		container_names.resize(CONT_IDX_NUM);
		container_names[SPECIES] = "Species";
		container_names[REACTION] = "Reaction";
		container_names[SYSTEM] = "System";
		container_names[DBINTERFACE] = "dbInterface";
		container_names[PART] = "Part";
		container_names[NEW] = "New";
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
		debugOut() << "xml exception: " << xe.what() << endl;
		throw xe;
	}

	//create newdoc.xml
}

/** 
 * @breif  
 * 		Put a file to dbxml database, if there already
 * 		had the file in db, check the time stamp to decide if
 * 		update needed.
 * 
 * @Param pathname
 * 		the path of the file
 * @Param docname
 * 		The doc name in the dbxml database
 * 
 * @Returns   
 * 	return no_error for success
 * 	otherwise an XmlException was throwed
 */
BdRetVal bdbXMLInterface::add_files(const string& pathname, const string& docname)
{
	XmlContainer* container = NULL;
	if (m_manager == NULL)
	{
		throw XmlException(XmlException::NULL_POINTER, "n_manager NULL", __FILE__, __LINE__);
	}

	QString q_pathname(pathname.c_str());
	for (int i = 0; i < CONT_IDX_NUM; i ++)
	{
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
	}

	XmlUpdateContext the_context = m_manager->createUpdateContext();
	try{
		XmlDocument the_doc = container->getDocument(docname);

		//
		container->deleteDocument(the_doc, the_context);

	}
	catch (XmlException &e)
	{
//                debugOut() << "open document xml exception: " << e.what() << " file name: " << docname << endl;
		if (e.getExceptionCode() != XmlException::DOCUMENT_NOT_FOUND)
		{
				throw e;
		}
	}

	debugOut() << "putting file: " << pathname << " to container " << container->getName() <<
			" as doc " << docname << endl;
	try
	{
			XmlInputStream *the_stream =
					m_manager->createLocalFileInputStream(pathname);
			container->putDocument(docname,
							the_stream,
							the_context,
							0);
	}
	catch (XmlException &e)
	{
			debugOut() << "xml exception: " << e.what() << endl;
			throw e;
	}

	return no_error;
}

/** 
 * @breif  
 * 	get the element of a node
 * 
 * @Param container_type
 * 	should be value defined in container_index enum
 * @Param doc
 * 	the document name of xml file
 * @Param node_path
 * 	the xpath path of node to be search
 * @Param res
 * 	output parameter, return the values of element,
 * 	For there might be serveral node have the same name,
 * 	so the result may be a vector of string. 
 *
 * @Returns   
 * 	return no_error for success
 * 	otherwise an XmlException was throwed
 */
BdRetVal bdbXMLInterface::get_node_element (container_index container_type, 
		const string *doc, 
		const string *node_path, 
		vector<string> &res)
{
	string query_string;

	if (m_manager == NULL)
	{
		throw XmlException(XmlException::NULL_POINTER, "m_manager", __FILE__, __LINE__);
	}


	if (container_type >= CONT_IDX_NUM)
	{
		throw XmlException(XmlException::INVALID_VALUE, "contianer_type", __FILE__, __LINE__);
	}

	if (doc == NULL)
	{
		query_string += "collection('"
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
		debugOut() <<"get node element: " << query_string << endl;
		debugOut() << "get_node_element in prepare xml exception: " << xe.what() << endl;
		throw xe;
	}

	res.clear();
	XmlValue value;
	while (results.next(value))
	{
	    string stripped_str = strip_char(value.getFirstChild().getNodeValue());
		res.push_back(stripped_str);
	}

	return no_error;
}

/** 
 * @breif  
 * 	get the attribute value of a node
 * 
 * @Param container_type
 * 	should be value defined in container_index enum
 * @Param doc
 * 	the document name of xml file
 * @Param node_path
 * 	the xpath path of node to be search
 * @Param res
 * 	output parameter, return the values of attribute,
 * 	For there might be serveral node have the same name,
 * 	so the result may be a vector of string. 
 *
 * @Returns   
 * 	return no_error for success
 * 	otherwise an XmlException was throwed
 */
BdRetVal bdbXMLInterface::get_node_attr(container_index container_type, 
		const string *doc, 
		const string *node_path, 
		vector<string> &res)
{
	string query_string;

	if (m_manager == NULL)
	{
		throw XmlException(XmlException::NULL_POINTER, "m_manager", __FILE__, __LINE__);
	}


	if (container_type >= CONT_IDX_NUM)
	{
		throw XmlException(XmlException::INVALID_VALUE, "contianer_type", __FILE__, __LINE__);
	}

	if (doc == NULL)
	{
		query_string += "collection('"
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
		debugOut() << "get node attr: " << query_string << endl;
		debugOut() << "get_node_attr in prepare xml exception: " << xe.what() << endl;
		throw xe;
	}

	res.clear();
	XmlValue value;
	while (results.next(value))
	{
	    string stripped_str = strip_char(value.getNodeValue());

		if (stripped_str.empty())
			continue;

		res.push_back(stripped_str);
	}

	return no_error;
}

/** 
 * @breif  
 * 	get the node content of a document as a string
 * 
 * @Param container_type
 * 	should be value defined in container_index enum
 * @Param doc
 * 	the document name of xml file
 * @Param node_path
 * 	the xpath path of node to be search
 * @Param res
 * 	output parameter, return the string value of results
 *
 * @Returns   
 * 	return no_error for success
 * 	otherwise an XmlException was throwed
 */
BdRetVal bdbXMLInterface::get_node(container_index container_type, 
		const string *doc, 
		const string *node_path, 
		string &res)
{
	string query_string;

	if (m_manager == NULL)
	{
		throw XmlException(XmlException::NULL_POINTER, "m_manager null", __FILE__, __LINE__);
	}


	if (container_type >= CONT_IDX_NUM)
	{
		throw XmlException(XmlException::INVALID_VALUE, "contianer_type", __FILE__, __LINE__);
	}

	if (doc == NULL)
	{
		query_string += "collection('"
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
		debugOut() << "get node query string: " << query_string << endl;
		debugOut() << "get_node in prepare xml exception: " << xe.what() << endl;
		throw xe;
	}

	res.clear();
	XmlValue value;
	while (results.next(value))
	{
		res = value.asString();
	}

	return no_error;
}

//BdRetVal bdbXMLInterface::get_math(container_index container_type, 
//                const string *doc, 
//                const string *node_path, 
//                string &res)
//{

//}

/** 
 * @breif  
 * 		Add all files in a directory to dbxml database
 * 
 * @Param directory
 * 		The path of drectory
 * 
 * @Returns   
 * 	return no_error for success
 * 	otherwise an XmlException was throwed
 */
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
			debugOut() << "add files exception" << cur_pathname.toStdString() << endl;
			throw se;
		}

		//add to directory
	}
}

/** 
 * @breif  
 * 		Get the number of nodes in a xml file
 * 
 * @Param container_type
 * 	should be value defined in container_index enum
 * @Param doc
 * 	the document name of xml file
 * @Param node_path
 * 	the xpath path of node to be search
 *
 * @Returns   
 * 		the node number
 */
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
		query_string += "count(collection('"
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
		debugOut() << "get_node_element_num: " << query_string << endl;
		debugOut() << "get_node_element_num exception: " << xe.what() << endl;
		throw xe;
	}

	XmlValue value;
	results.next(value);
	if (value.isNumber())
		res = (int)value.asNumber();
	else
		res = 0;

	return res;
}

/** 
 * @breif 
 * 	strip the space, return and tab chars 
 * 	exist in the head and tail positions of string 
 * 
 * @Param instring
 * 	The string need be strip
 * 
 * @Returns   
 * 	The result string of stripped param instring
 */
string bdbXMLInterface::strip_char(string instring)
{
		int pos_head = 0;
		int pos_tail = instring.size() - 1;

		while (pos_head < instring.size())
		{
				if ((instring[pos_head] == ' ')
								|| (instring[pos_head] == '\t')
								|| (instring[pos_head] == '\n'))
				{
						pos_head ++;
				}
				else
				{
						break;
				}
		}

		while (pos_tail > 0)
		{
				if ((instring[pos_tail] == ' ')
								|| (instring[pos_tail] == '\t')
								|| (instring[pos_tail] == '\n'))
				{
						pos_tail --;
				}
				else
				{
						break;
				}
		}

		return string (instring, pos_head, pos_tail-pos_head+1);
}

BdRetVal bdbXMLInterface::get_ids_byNodePath(container_index container_type, const char* node_path, vector<string> &res)
{
	if (node_path == NULL)
		return para_error;

		string path = node_path;

		res.clear();
		//may throw exception
		get_node_attr(container_type, NULL, &path, res);

		return no_error;
}

/** 
 * @breif 
 * 	This is a function for ui interface.
 * 	Provide id strings of all db files in the container
 * 
 * @Param container_type
 * 	should be value defined in container_index enum
 * @Param res
 * 	output parameter, return the ids
 * 
 * @Returns   
 */
BdRetVal bdbXMLInterface::get_ids_bycontainer(container_index container_type, vector<string> &res)
{
		string path_biobrick = "//@id";
//        string path_biobrick = "//biobrick/@id";
//        string path_compartment= "//compartment/@id";

		return get_ids_byNodePath(container_type, path_biobrick.c_str(), res);
}

BdRetVal bdbXMLInterface::insert_new_node(container_index container_type, const string& docname, const string &node_path,
		const string &node_name, vector<string>* attr_list, const string& element)
{
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
	string query_string = "insert nodes ";

	query_string += "\n<" + node_name;
	if (attr_list != NULL)
	{
		for (int i=0; i < attr_list->size(); i++)
		{
			query_string += "\n"; 
			query_string += (*attr_list)[i];
		}
	}

	query_string += ">\n" + element;
	query_string += "\n</" + node_name + ">\n";

	query_string += " into "; 

	query_string += "doc(\"dbxml:/" 
		+ container_names[container_type] 
		+ ".dbxml/" 
		+ docname
		+ "\")" + node_path;

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
		debugOut() << "insert operation: " << query_string << endl;
		debugOut() << "insert exception: " << xe.what() << endl;
		throw xe;
	}

	return no_error;
}

BdRetVal bdbXMLInterface::create_doc(container_index container_type, 
		const string &doc_name, 
		const string &root,
		vector<string>* attr_list,
		int flag)
{
	if (m_manager == NULL)
	{
		throw XmlException(XmlException::NULL_POINTER, "m_manager", __FILE__, __LINE__);
	}

	XmlContainer* container = NULL;
	container = &m_containers[container_type];
	XmlUpdateContext the_context = m_manager->createUpdateContext();

	try
	{
		XmlDocument the_doc = container->getDocument(doc_name);
		if ((flag & DELET_EXIST) != DELET_EXIST)
		{
			throw XmlException(XmlException::NULL_POINTER, "xml document exists", __FILE__, __LINE__);
			return xml_exception;
		}
		else
		{
			container->deleteDocument(the_doc, the_context);
		}
	}
	catch (XmlException &e)
	{
		if (e.getExceptionCode() != XmlException::DOCUMENT_NOT_FOUND)
		{
			debugOut() << "xml excepiton" << e.what() << endl;
			throw XmlException(XmlException::NULL_POINTER, "xml document get error", __FILE__, __LINE__);
		}
	}

	//创建一个新的document
	string content = "<?xml version=\"1.0\"?>";
	content += "\n<" + root + ">"; 
	if (attr_list != NULL)
	{
		for (int i=0; i < attr_list->size(); i++)
		{
			content += "\n";
			content += (*attr_list)[i];
		}
	}

	content += "\n</" + root + ">";
	try
	{
		container->putDocument(doc_name, content, the_context, 0);
	}
	catch (XmlException &e)
	{
		debugOut() << "xml exception: " << e.what() << endl;
		throw XmlException(XmlException::NULL_POINTER, "xml document put content error", __FILE__, __LINE__);
	}
}

BdRetVal bdbXMLInterface::delete_doc(container_index container_type, const string &doc_name)
{
	XmlContainer* container = NULL;
	if (m_manager == NULL)
	{
		throw XmlException(XmlException::NULL_POINTER, "n_manager NULL", __FILE__, __LINE__);
	}

	container = &m_containers[container_type];

	if (container == NULL)
	{
		throw XmlException(XmlException::NULL_POINTER, "container NULL", __FILE__, __LINE__);
	}

	XmlUpdateContext the_context = m_manager->createUpdateContext();
	try{
		XmlDocument the_doc = container->getDocument(doc_name);

		container->deleteDocument(the_doc, the_context);
	}
	catch (XmlException &xe)
	{
		throw xe;
	}

	return no_error;
}
