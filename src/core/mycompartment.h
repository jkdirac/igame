/*************************************************************************************
*
*            Author: liaochen- liaochen@mail.ustc.edu.cn
*
*            Last modified:	2010-09-25 10:50
*
*            Filename:		mycompartment.h
*
*            Description: .
*
************************************************************************************/
#ifndef MY_COMPARTMENT_H
#define MY_COMPARTMENT_H

#include "myspecies.h"

class MyCompartment:
  public Compartment
{
  public:

	MyCompartment ();
	~MyCompartment ();

	void addMySpeciesIn (MySpecies*);
	void addMyCompartmentIn (MyCompartment*);
	void addParentCompartment (MyCompartment*);

	MyCompartment* getParentCompartment ();
	const MyCompartment* getParentCompartment () const;

	MySpecies* isMySpeciesIn (const string&);
	const MySpecies* isMySpeciesIn (const string&) const;
	MySpecies* isMySpeciesIn (const MySpecies*);
	const MySpecies* isMySpeciesIn (const MySpecies*) const;

	MyCompartment* isMyCompartmentIn (const string&);
	const MyCompartment* isMyCompartmentIn (const string&) const;

	void setDB_ref (const string&);
	string getDB_ref () const;
	
	void setCounterPart (const string&);
	string getCounterPart () const;

  private:

	string reference_db;
	string counterpart;

	vector<MySpecies*> listOfMySpeciesIn;

	MyCompartment* parent;
	vector<MyCompartment*> listOfMyCompartmentsIn;

};
#endif
