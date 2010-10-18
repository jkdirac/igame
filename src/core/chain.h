/*************************************************************************************
*
*            Author: liaochen- liaochen@mail.ustc.edu.cn
*
*            Last modified:	2010-10-18 03:15
*
*            Filename:		chain.h
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

	void setIsDNA ();

	bool equal (const Chain*) const;
	bool match (const Chain*, cMatchsType&) const; 

	Part* createPart ();
	Part* createPart (const Part*);
	Part* createPart (const string&, const string&, const string&, const string&, const bool& =false);

	void genUnicode ();
	string getUnicode () const;
	string genUnicode (const int&, const int&, const bool&) const;

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
	bool isCsymm ();
	void turnover ();

  private:

	int chainNum;
	bool isDNA;

	string unicode;
	string chainLabel;
	vector<Part*> listOfParts;
};

#endif
