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

	void addMySpeciesIn (
		MySpecies* s
		);

	void addMyCompartmentIn (
		MyCompartment* comp
		);

	void setDbId (
		const string& dbid
		);

	MySpecies* isMySpeciesIn (
		const string& sbmlid
		);

	MySpecies* isMySpeciesIn (
		const MySpecies* s
		);

	const MySpecies* isMySpeciesIn (
		const string& sbmlid
		) const;

	MyCompartment* isMyCompartmentIn (
		const string& sbmlid
		);

	const MyCompartment* isMyCompartmentIn (
		const string& sbmlid
		) const;

	string getDbId () const;

  private:

	string dbId;

	vector<MySpecies*> listOfMySpeciesIn;
	vector<MyCompartment*> listOfMyCompartmentsIn;

};
#endif
