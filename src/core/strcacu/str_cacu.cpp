#include <map>
#include <string>
#include <iostream>

#include "cacuyac.h"
//#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>

#include "str_cacu.h"
#include "StrCacuException.h"

using namespace std;

int err_no;
char err_msg[MSG_BUFF];
//#ifdef __cplusplus 
//extern "C" {
//#endif
//extern int cacu_string_exp(const char *par, const char *expr);

//#ifdef __cplusplus
//}
//#endif

map<string, double> symbo_table;

void init_symbol_table()
{
	symbo_table.clear();
}

void add_symbol(char *name, double value)
{
	if (name == NULL)
		return;

	string str(name);
	symbo_table.insert(pair<string, double> (str, value));
}

double get_symbol_value(char *name)
{
	if (name == NULL)
	{
		return STRCACU_SYMBOL_NOT_FOUND;
	}

	string str(name);

	map<string, double>::iterator itr_map;
	itr_map = symbo_table.find(str);

	if (itr_map == symbo_table.end())
	{
		return STRCACU_SYMBOL_NOT_FOUND;
	}

	return itr_map->second;
}

const char *get_err_msg()
{
	return err_msg;
}

int cacu_str_exp(const char *par, const char *expr)
{
	int res = cacu_string_exp(par, expr);

	if (expr == NULL)
	{
		throw StrCacuException("input null pointer");
	}
	
	if (err_no == STRCACU_SUCCESS)
		return res;
	else if (err_no == STRCACU_NULL_POINTER)
	{
		throw StrCacuException("null pointer");
	}
	else if (err_no == STRCACU_SYNTAX_ERROR)
	{
		throw StrCacuException("input error, expression have synatx error");
	}
	else if (err_no == STRCACU_SYMBOL_NOT_FOUND)
	{
		throw StrCacuException("input error, every variable in expression should be assigned a value");
	}
}
