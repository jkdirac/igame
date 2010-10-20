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

#include "../BdInterface/bdbInterface.h"

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

class IsLess_no
{
	public:

		IsLess_no () {}

		inline bool operator () (
				const Chain* x,
				const Chain* y
				) const
		{
			return x->chainNum < y->chainNum;
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

		MySpecies ();
		MySpecies (const int&);
		MySpecies (const MySpecies*);
		~MySpecies ();

		void rearrange (const bool&);
		bool equal (const MySpecies*);
		void split (bdbXMLInterface&, vector<MySpecies*>&);
		void addPrefix (const string&);

		Chain* createChain ();
		Chain* createChain (const Chain* c); 

		Tree* createTree ();
		Tree* createTree (const Tree* t);

		int getNumOfChains () const;
		int getNumOfTrees () const;

		Chain* getChain (const int&);
		const Chain* getChain (const int&) const;

		Tree* getTree (const int&);
		const Tree* getTree (const int&) const;

		Part* getPart (const string&);
		const Part* getPart (const string&) const;

		void setDB_ref (const string&);
		void setDB_Label (const string&);
		void setCompTypeId (const string&);

		string getDB_ref () const;
		string getDB_Label () const;
		string getCompTypeId () const;

		Node* findBindedNode (const string&);
		const Node* findBindedNode (const string&) const;

		bool isCompartment () const;
		bool match (const MySpecies*, cMatchsArray& res) const;

		void display_name (const int&);
		void Output () const;

	private:

		string reference_db; //id in database for template species 
		string comp_type_id; //non-empty if it is a compartment-type species 
		string speciesLabel_db; //used in reaction templates

		string minW;
		vector< set<int> > equiv; // each set is an equivalent class

		//	chain list and tree list
		vector<Chain*> listOfChains;
		vector<Tree*> listOfTrees;

	private:

		void findEquiv (vector<markType>&) const;
		void trim (bdbXMLInterface* dbreader = NULL);
		void perm (const int&, const vector<markType>&, const permType&, vector<int>&);
};
#endif
