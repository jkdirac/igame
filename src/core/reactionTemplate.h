/*************************************************************************************
 *
 *            Author: liaochen- liaochen@mail.ustc.edu.cn
 *
 *            Last modified:	2010-09-27 09:31
 *
 *            Filename:		reactionTemplate.h
 *
 *            Description: .
 *
 ************************************************************************************/
#ifndef REACTION_TEMPLATE_H
#define REACTION_TEMPLATE_H

#include "myspecies.h"
#include "mycompartment.h"

bool isSameType (const string&, const string&);

class reactionTemplate
{
	public:

		friend class MyReaction;
		friend class MySBMLDocument;

	public:

		reactionTemplate ();
		~reactionTemplate ();

		void setId (const string&);
		void setName (const string&);
		void setReversible (const bool&);
		void setFast (const bool&);
		void setMath (const string&);

		string getId () const;
		string getName () const;
		bool getFast () const;
		bool getReversible () const;
		string getMath () const;

		string getCompartment (const string&) const;
		const MySpecies* getSpecies (const string&) const;
		Parameter* getParameter (const string&);

		void addParameter (Parameter*);
		void addReactant (MySpecies*, const string&);
		void addProduct (MySpecies*, const string&);
		void addModifier (MySpecies*, const string&);

		void addCompartment (const string&, const string&, const string&);
		void addConstraint (const vector<string>&, const string&);
		void addSubstituentTransfer (const subsp&, const subsp&);	//attention! it maps subsp to --> subsp from
		void addProductPrefix (const string&);

		bool findSpeciesMatch (
				const string&, 
				const int&, 
				const vector<MySpecies*>&, 
				const vector<MyCompartment*>&, 
				reactionArrayMatch&	
				); 

		void createProductsFromTemplate (
				const vector<MySpecies*>&,
				const vector<MyCompartment*>&, 
				const reactionPairMatch&,
				vector<MySpecies*>&
				);

		bool handle_constraints (const ListOfParameters*);


		void OutputProducts ();

	private:

		//
		//	id and name
		//
		string id;
		string name;

		//
		//	reversible and fast
		//
		bool reversible;
		bool fast;

		//
		//	map compartment labels to its database id (ignores Node "ROOT")
		//
		map <string, string> mapComps;

		//
		//	map	compartment labels to its children 
		//	compartment labels
		//	//
		//	say, if Flask is the outside compartment of E_coli,
		//	it has mmapComps[Flask] = E_coli
		//	//
		//	contains Node "ROOT"
		//
		multimap <string,string> mmapComps;

		//
		//	map compartment label to reactants/modifier/product index
		//
		multimap <string, int> mmapIndexReactants;
		multimap <string, int> mmapIndexModifiers;
		multimap <string, int> mmapIndexProducts;

		//	
		//	map component "to" to component "from"
		//	
		map<subsp, subsp> transferTable;

		//
		//	species in following vectors are only
		//	species templates without any modification
		//
		vector<MySpecies*> listOfMyReactants;
		vector<MySpecies*> listOfMyModifiers;
		vector<MySpecies*> listOfMyProducts;

		string math;

		//	
		//	local parameters
		//
		vector<Parameter*> listOfParameters;

		//
		//	constraints
		//
		vector<constraintType> listOfConstraints;
};


#endif



