/*************************************************************************************
*
*            Author: liaochen- liaochen@mail.ustc.edu.cn
*
*            Last modified:	2010-09-25 22:02
*
*            Filename:		mysbmldoc.h
*
*            Description: .
*
************************************************************************************/
#ifndef MYSBML_DOCUMENT_H
#define MYSBML_DOCUMENT_H

#include "myspecies.h"
#include "mycompartment.h"
#include "myreaction.h"
#include "reactionTemplate.h"
#include "readDataBase.h"

#define TINY 1E-5

class MySBMLDocument:
	public SBMLDocument
{
	public:

		friend class Driver;

	public:

		MySBMLDocument ();
		~MySBMLDocument ();

		MyCompartment* createMyCompartment ();

		MySpecies* createMySpecies ();

		MyReaction* createMyReaction ();

		MyCompartment* getMyCompartment (
				const string& label
				);

		const MyCompartment* getMyCompartment (
				const string& label
				) const;
 

		//
		//	switch (t)
		//	t=0 --> species
		//	t=1 --> reaction
		//
		string genSbmlId (
				const int& t
				) const;

		UnitKind_t getUnitKind_t (
				const string& unit
				) const;

		int getNumOfMyCompartments () const;
		int getNumOfMySpecies () const;

		//
		//	return species pointer 
		//
		MySpecies* validateBackSpecies ();

		//
		//	core programe
		//
		void run (
				readDataBase& dbreader
				);

	private:

		void handleReactionTemplate (
				readDataBase& dbreader,
				const string& doc,
				const string& role,
				const int& speciesIndex
				);

		void searchTranscriptionReactions (
				const int& i,
				const int& j,
				const int& k,
				readDataBase& dbreader
				);

		void searchTranslationReactions (
				const int& i,
				const int& j,
				const int& k,
				readDataBase& dbreader
				);
	private:

		vector<MyCompartment*> listOfMyCompartments;

		vector<MySpecies*> listOfMySpecies;

		vector<MyReaction*> listOfMyReactions;

		//
		//	map string to UnitKind_t
		//
		map <string, UnitKind_t> unitMap;
};
#endif
