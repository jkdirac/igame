#include "mycompartment.h"

MyCompartment::MyCompartment ():
	Compartment (2,4)
{}

MyCompartment::~MyCompartment ()
{}

void MyCompartment::setDB_ref (const string& ref) {
	reference_db = ref;
}

string MyCompartment::setDB_ref () const {
	return reference_db;
}

void MyCompartment::addMySpeciesIn (MySpecies* s) {
	listOfMySpeciesIn.push_back (s);
}

void MyCompartment::addMyCompartmentIn (MyCompartment* comp) {
	listOfMyCompartmentsIn.push_back (comp);
}

MySpecies* MyCompartment::isMySpeciesIn (
		const string& ref) 
{
	for (int i=0; i < listOfMySpeciesIn.size (); i++)
	{
		MySpecies* s = listOfMySpeciesIn[i];
		if (s->getId () == ref) return s;
	}
	return NULL;
}

MySpecies* MyCompartment::isMySpeciesIn (
		const MySpecies* rhs
		)
{

	//
	//	TIPS
	//
	//	(1) same cnModel Structure
	//	(2) in the same compartment
	//	(3) if they are two compartment-type species,
	//	compare their species_of_compartment_type
	//
	for (int i=0; i < listOfMySpeciesIn.size (); i++)
	{
		MySpecies* lhs = listOfMySpeciesIn[i];
		string compLHS = lhs->getOutside ();
		
		//	is compartment same?
		compRHS = rhs->getOutside (); 
		if (species->equal (s)) return species;
	}
	return NULL;
}

const MySpecies* MyCompartment::isMySpeciesIn (
		const string& sbmlid
		) const
{
	cout << "\nmyspecies in = " << listOfMySpeciesIn.size ();
	int numOfSpecies = listOfMySpeciesIn.size ();
	for (int i=0; i < numOfSpecies; i++)
	{
		MySpecies* s = listOfMySpeciesIn[i];
		cout << "\nspecies = " << s->getId ();
		if (s->getId () == sbmlid) return s;
	}
	return NULL;
}

MyCompartment* MyCompartment::isMyCompartmentIn (
		const string& sbmlid
		)
{
	int numOfComps = listOfMyCompartmentsIn.size ();
	for (int i =0; i < numOfComps; i++)
	{
		MyCompartment* comp = listOfMyCompartmentsIn[i];
		if (comp->getId () == sbmlid) return comp;
	}
	return NULL;
}

const MyCompartment* MyCompartment::isMyCompartmentIn (
		const string& sbmlid
		) const
{
	int numOfComps = listOfMyCompartmentsIn.size ();
	for (int i =0; i < numOfComps; i++)
	{
		MyCompartment* comp = listOfMyCompartmentsIn[i];
		if (comp->getId () == sbmlid) return comp;
	}
	return NULL;
}
