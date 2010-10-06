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

		MySpecies* createMySpecies ();
		MyCompartment* createMyCompartment ();
		MyReaction* createMyReaction ();

		void addMySpecies (MySpecies*);
		void addMyCompartment (MyCompartment*);
		void addMyReaction (MyReaction*);
		void addMyCompartmentChildren ();

		MySpecies* getMySpecies (const string&);
		const MySpecies* getMySpecies (const string&) const;
		MySpecies* getMySpecies (const MySpecies*);
		const MySpecies* getMySpecies (const MySpecies*) const;
		
		MyCompartment* getMyCompartment (const string&);
		const MyCompartment* getMyCompartment (const string&) const;

		int getNumOfMyCompartments () const;
		int getNumOfMySpecies () const;

	public:
		
		void run (readDataBase&);

	private:

		void handleReactionTemplate (
				readDataBase&,
				const string&,
				const string&,
				const string&,
				const int&
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
		
		void write ();

	private:

		vector<MyCompartment*> listOfMyCompartments;
		vector<MySpecies*> listOfMySpecies;
		vector<MyReaction*> listOfMyReactions;
};
#endif
