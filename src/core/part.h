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
	Part (const Part* orig);
	~Part ();

	void setPartRef (const string& );
	void setPartLabel (const string& );
	void setPartType (const string& );
	void setPartCtg (const string& );
	void setIsBinded (const bool& );

	void setPart (
			const string&, 
			const string&, 
			const string&, 
			const string&, 
			const string& = false
			);

	string getPartRef () const;
	string getPartLabel () const;
	string getPartType () const;
	string getPartCtg () const;
	bool getIsBinded () const;

  private:
	
	//
	//	four listed attribute in database
	//
	string partRef, partLabel, partType, partCtg;

	//
	//	bool flag to indicate whether this part is in binded state
	//
	bool isBinded;
};
#endif
