/*************************************************************************************
*
*            Author: liaochen- liaochen@mail.ustc.edu.cn
*
*            Last modified:	2010-09-25 15:15
*
*            Filename:		chain.h
*
*            Description: .
*
************************************************************************************/
#ifndef CHAIN_H
#define CHAIN_H

#include "part.h"

class Chain
{
  friend class IsLess_c;
  friend class IsLess_no;
  friend class MySpecies;

  public:

	Chain ();
	Chain (const Chain*);
	~Chain ();

	string getLabel () const;
	void setLabel (const string&);

	bool equal (const Chain*) const;
	bool match (const Chain*, cMatchsType&) const; 

	Part* createPart ();
	Part* createPart (const Part*);
	Part* createPart (const string&, const string&, const string&, const string&, const bool& =false);

	void genUnicode ();
	string genUnicode (const int&, const int&) const;
	string getUnicode () const;

	int getNumOfParts () const;
	Part* getPart (const int&);
	const Part* getPart (const int&) const;
	Part* getPart (const string&);
	const Part* getPart (const string&) const;
	int getPartIndex (const string&) const;

	void __add_chain_prefix (const string&);
	void Output (ostream&) const; 

  private:

	int getKeywords (const string&) const;
	bool substituent_m (const int&, const int&, const int&, const int&, const Chain*, cMatchsType& res) const; 

  private:

	string unicode;

	//	only used when generating products by splitting the spcies mixure
	string chainLabel;

	//	chain number will be used to recover original order after perm
	int chainNum;

	vector<Part*> listOfParts;
};

#endif
