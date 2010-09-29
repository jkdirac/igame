/*************************************************************************************
*
*            Author: liaochen- liaochen@mail.ustc.edu.cn
*
*            Last modified:	2010-09-25 16:01
*
*            Filename:		part.h
*
*            Description: .
*
************************************************************************************/
#ifndef PART_H
#define PART_H

#include "g_i.h"

class Part
{
  friend class Chain;

  public:

	Part ();

	Part (
		const Part* orig
		);

	~Part ();

	void setDbId (
		const string& dbid
		);

	void setPartLabel (
		const string& label
		);

	void setPartType (
		const string& type
		);

	void setPartCategory (
		const string& category
		);

	void setIsBinded (
		const bool& isb
		);

	string getDbId () const;

	string getPartLabel () const;

	string getPartType () const;

	string getPartCategory () const;

	bool getIsBinded () const;

  private:
	
	string dbId;

	string partLabel;

	string partType;

	string partCategory;

	bool isBinded;
};
#endif
