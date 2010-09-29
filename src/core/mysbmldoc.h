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

	string genSbmlId () const;

	UnitKind_t getUnitKind_t (
		const string& unit
		) const;

	int getNumOfMyCompartments () const;
	int getNumOfMySpecies () const;

	//
	//	return NULL indicates the back species is new
	//	in the compartment
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
