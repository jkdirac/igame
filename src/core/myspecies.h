/*************************************************************************************
*
*            Author: liaochen- liaochen@mail.ustc.edu.cn
*
*            Last modified:	2010-09-25 12:16
*
*            Filename:		myspecies.h
*
*            Description: .
*
************************************************************************************/
#ifndef MY_SPECIES_H
#define MY_SPECIES_H

#include "chain.h"
#include "tree.h"
#include "imath.h"

class IsLess_c
{
  public:

	IsLess_c () {}

	inline bool operator () (
		const Chain* x, 
		const Chain* y
		) const
	{
	  return x->unicode < y->unicode;
	}
};

class IsLess_t
{
  public:

	IsLess_t () {}

	inline bool operator () (
		const Tree* x, 
		const Tree* y
		) const
	{
	  pair<int,int> xw = 
		x->mapNodes.find ("ROOT")
		->second->getNodeWeight ();
	  pair<int,int> yw = 
		y->mapNodes.find ("ROOT")
		->second->getNodeWeight ();
	  return xw < yw;
	}
};

class MySpecies:
  public Species
{
  public:
	
	typedef vector<int> vi;
	typedef vector<vi> dvi;
	typedef vector<dvi> tvi;
	typedef tvi permType;

	typedef pair<int,int> markType;
	typedef list<markType> cMatchType;
	typedef vector<cMatchType> cMatchsType;
	typedef pair<cMatchType, int> cMatchType2;
	typedef vector<cMatchType2> cMatchsType2;

  public:

	MySpecies ();

	MySpecies (
		const MySpecies* orig
		);

	~MySpecies ();

	void DeleteAndSave (
		const set<int>& chainSaved,
		const set<string>& nodeSaved
		);

	void split (
		vector<MySpecies*>& pieces
		);

	void rearrange ();

	bool equal (
		const MySpecies* rhs
		);

	Chain* createChain ();

	Chain* createChain (
		const Chain* c
		);

	Tree* createTree ();

	Tree* createTree (
		const Tree* t
		);

	int getNumOfChains () const;

	int getNumOfTrees () const;

	Chain* getChain (
		const int& n
		);

	const Chain* getChain (
		const int& n
		) const;

	Tree* getTree (
		const int& n
		);

	const Tree* getTree (
		const int& n
		) const;

	void setDbId (
		const string& dbid
		);

	void setLabel (
		const string& _label
		);

	string getDbId () const;
	string getLabel () const;

	bool countBindedNode (
		const string& label
		) const;

	Node* findBindedNode (
		const string& label
		);

	bool match (
		const MySpecies* s,
		vector<cMatchsType2>& trym
		) const;

	void Output () const;

  private:

	string dbId;
	string label; //used in reaction templates

	bool isRearranged;

	vector<Chain*> listOfChains;
	vector<Tree*> listOfTrees;

	vector< pair<int,int> > equiv;

	void findEquiv ();

	void perm (
		const int& i, 
		const permType& permAll
		);
};
#endif
