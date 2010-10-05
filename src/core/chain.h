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
  friend class MySpecies;

  public:

	Chain ();
	Chain (const Chain*);
	~Chain ();

	string getLabel () const;
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

	void Output (ostream&) const; 

  private:

	bool substituent_m (const int&, const int&, const int&, const int&, const Chain*, cMatchsType& res) const; 

  private:

	string unicode;
	string chainLabel;

	vector<Part*> listOfParts;

  private:

	map<string, int> keywords;
};

#endif
