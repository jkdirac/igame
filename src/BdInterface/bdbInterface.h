#ifndef _BD_INTERFACE_H_
#define _BD_INTERFACE_H_

#include "dbxml/DbXml.hpp"
#include "dbxml/XmlException.hpp"
#include "db.h"
#include <vector>

using namespace std;
using namespace DbXml;

enum BdRetVal {
	no_error,
	para_error,
	xml_exception,
	no_container
};

enum container_index
{
	SPECIES=0,
	REACTION,
	SYSTEM,
	PART,
	COMPARTMENT,
	DBINTERFACE,
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
		const string db_env_home; 
		const string db_container_name;

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
//        BdRetVal get_node(container_index container_type, 
//                const string *doc, 
//                const string *node_path, 
//                string &res,
//                const string &prefix,
//                const string &uri);
		BdRetVal get_ids_bycontainer(container_index container_type, vector<string> &res);
};

#endif
