#ifndef _BD_INTERFACE_H_
#define _BD_INTERFACE_H_

#include "dbxml/DbXml.hpp"
#include "dbxml/XmlException.hpp"
#include "db.h"
#include <vector>
#include <QString>
#include <QDir>

using namespace std;
using namespace DbXml;

#define DEFAULT_FLAG 0x0
#define DELET_EXIST 0x1

enum BdRetVal {
	no_error,
	para_error,
	xml_exception,
	no_container,
};

enum container_index
{
	SPECIES=0,
	REACTION,
	SYSTEM,
	PART,
	COMPARTMENT,
	DBINTERFACE,
	NEW,
	CONT_IDX_NUM
};

class bdbXMLInterface
{
	private:
		XmlManager* m_manager;
		XmlContainer m_container;
		XmlContainer m_containers[CONT_IDX_NUM];
		DB_ENV *db_env;
		u_int32_t env_flags;
		QString sys_home_path;
		QString igame_home_path;
		QString db_env_home; 

		vector<string> container_names;
		string strip_char(string instring);

	public:
		bdbXMLInterface();
		~bdbXMLInterface();
		BdRetVal add_directory(const string &directory);
		BdRetVal add_files(const string &pathname, const string& filename);
		int get_node_element_num (container_index container_type, 
				const string *doc, 
				const string *node_path);

		BdRetVal get_node_element (container_index container_type, 
				const string *doc, 
				const string *node_path, 
				vector<string> &res);
		BdRetVal get_node_attr(container_index container_type, 
				const string *doc, 
				const string *node_path, 
				vector<string> &res);
		BdRetVal get_node(container_index container_type, 
				const string *doc, 
				const string *node_path, 
				string &res);
		BdRetVal insert_new_node(container_index container_type, const string& docname, const string &node_path,
				const string &node_name, vector<string>* attr_list, const string& element);
		BdRetVal delete_doc(container_index container_type, const string &doc_name);
		BdRetVal create_doc(container_index container_type, 
				const string &doc_name, 
				const string &root,
				vector<string>* attr_list,
				int flag);
//        BdRetVal get_node(container_index container_type, 
//                const string *doc, 
//                const string *node_path, 
//                string &res,
//                const string &prefix,
//                const string &uri);
		BdRetVal get_ids_bycontainer(container_index container_type, vector<string> &res);
		BdRetVal get_ids_byNodePath(container_index container_type, const char* node_path, vector<string> &res);
		BdRetVal put_stringtodoc(container_index container_type, const char* content, const string& doc_name);
};

#endif
