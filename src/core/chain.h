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
	
	typedef pair<int,int> markType;
	typedef list<markType> cMatchType;

  public:

	Chain ();

	Chain (
		const Chain* orig
		);

	~Chain ();

	void genChainLabel (
		const string& slabel,
		const int& num
		);

	bool equal (
		const Chain* rhs
		) const;

	bool match ( 
		const Chain* c, 
		vector<cMatchType>& xyz
		) const; 

	Part* createPart ();

	Part* createPart (
		const Part* p
		);

	void genUnicode ();

	string genUnicode (
		const Part* ps,
		const Part* pe
		) const;

	//
	//	return pointer of Part object, if 
	//	not found, return NULL
	//	

	Part* getPart (
		const int& n
		);

	const Part* getPart (
		const int& n
		) const;

	Part* getPart (
		const string& label
		);

	const Part* getPart (
		const string& label
		) const;

	int getNumOfParts () const;

	//
	//	return index of part with given label, if
	//	not found, return -1
	//
	int getPartIndex (
		const string& label
		) const;

	string getUnicode () const;
	string getChainLabel () const;

	void Output (
		ostream& os
		) const; 

  private:

	bool substituent_m (
		const int& l1,
		const int& u1,
		const int& l2,
		const int& u2,
		const Chain* c,
		vector<cMatchType>& pm
		) const;

  private:

	vector<Part*> listOfParts;

	string unicode;

	string chainLabel;

};

#endif
