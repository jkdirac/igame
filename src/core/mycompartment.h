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

	MySpecies* isMySpeciesIn (const string&);
	const MySpecies* isMySpeciesIn (const string&) const;
	MySpecies* isMySpeciesIn (const MySpecies*);
	const MySpecies* isMySpeciesIn (const MySpecies*) const;

	MyCompartment* isMyCompartmentIn (const string&);
	const MyCompartment* isMyCompartmentIn (const string&) const;

	void setDB_ref (const string&);
	string getDB_ref () const;

  private:

	string reference_db;

	vector<MySpecies*> listOfMySpeciesIn;
	vector<MyCompartment*> listOfMyCompartmentsIn;

};
#endif
