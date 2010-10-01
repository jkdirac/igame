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

class reactionTemplate
{
	public:

		friend class MyReaction;
		friend class MySBMLDocument;

	public:

		typedef pair <int,int> markType;
		typedef list<markType> cMatchType;
		typedef pair<cMatchType, int> cMatchType2;
		typedef vector<cMatchType2> cMatchsType2; //chain match assemble (CMA)
		typedef vector<cMatchsType2> cMatchsArray; //all possible CMAs
		typedef pair<int, cMatchsType2> speciesMatch; // all CMAs matched to one species
		typedef vector<speciesMatch> speciesArrayMatch; // an array match of all reactants or modifiers
		typedef pair<speciesArrayMatch, speciesArrayMatch> reactionMatch;
		typedef vector<reactionMatch> reactionArrayMatch;

		typedef pair<string,string> subsp;

	public:

		reactionTemplate ();
		~reactionTemplate ();

		void setId (
				const string& _id
				);

		void setName (
				const string& _name
				);

		void setReversible (
				const bool& _rev
				);

		void setFast (
				const bool& _fast
				);

		string getId () const;

		string getName () const;

		bool getFast () const;

		bool getReversible () const;

		string getMath () const;

		string getCompartment (
				const string& speciesLabel
				) const;

		const MySpecies* getSpecies (
				const string& speciesLabel
				) const;

		Parameter* getParameter (
				const string& sid
				);

		void addCompartment (
				const string& _compRef,
				const string& _currComp,
				const string& _parComp
				);

		void addParameter (
				Parameter* para
				);

		void addConstraint (
				const vector<string>& vars,
				const string& formula
				);

		void addReactant (
				MySpecies* s,
				const string& compLabel
				);

		void addProduct (
				MySpecies* s,
				const string& compLabel
				);

		void addModifier (
				MySpecies* s,
				const string& compLabel
				);

		void addSubstituentTransfer (
				const pair<string,string>& from,
				const pair<string,string>& to
				);

		void setMath (
				const string& math
				);

		bool findSpeciesMatch (
				const vector<MyCompartment*>& listOfMyCompartments,
				const vector<MySpecies*>& listOfMySpecies,
				const int& currSpeIndex,
				const string& role,
				reactionArrayMatch& result
				);

		void genProductBody (
				const speciesArrayMatch& reactantCandidates,
				const speciesArrayMatch& modifierCandidates,
				const vector<MySpecies*>& listOfMySpecies,
				vector<MySpecies*>& productCandidates
				);

	private:

		bool compartmentConstraints (
				const string& searchComp,
				const string& parentComp,
				set<string>& compUsed,
				const vector<MyCompartment*>& listOfMyCompartments,
				const vector<MySpecies*>& listOfMySpecies,
				const speciesArrayMatch& reactantCandidates,
				const speciesArrayMatch& modifierCandidates
				);

	private:

		//
		//	return -1 if not found
		//
		int searchSpecies (
				const char& role,
				const string& speciesLabel
				);

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
		//	map compartment labels to its database id
		//
		map <string, string> mapComps;

		//
		//	map	compartment labels to its children 
		//	compartment labels
		multimap <string,string> mmapComps;

		//
		//	map compartment label to reactants/modifier index
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
		vector< pair<vector<string>, string> > listOfConstraints;
};


#endif



