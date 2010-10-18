#include "mycompartment.h"

MyCompartment::MyCompartment ():
	Compartment (2,4), parent (NULL)
{}

MyCompartment::~MyCompartment ()
{}

void MyCompartment::setCounterPart (const string& _counterp) {
	counterpart = _counterp;
}

string MyCompartment::getCounterPart () const {
	return counterpart;
}

void MyCompartment::setDB_ref (const string& ref) {
	reference_db = ref;
}

string MyCompartment::getDB_ref () const {
	return reference_db;
}

void MyCompartment::addMySpeciesIn (MySpecies* s) {
	listOfMySpeciesIn.push_back (s);
}

void MyCompartment::addMyCompartmentIn (MyCompartment* comp) {
	listOfMyCompartmentsIn.push_back (comp);
}

void MyCompartment::addParentCompartment (MyCompartment* comp) {
	parent = comp;
}

MyCompartment* MyCompartment::getParentCompartment () {return parent;}
const MyCompartment* MyCompartment::getParentCompartment () const {return parent;}

MySpecies* MyCompartment::isMySpeciesIn (const string& ref) 
{
	for (int i=0; i < listOfMySpeciesIn.size (); i++)
	{
		MySpecies* s = listOfMySpeciesIn[i];
		if (s->getId () == ref) return s;
	}
	return NULL;
}

const MySpecies* MyCompartment::isMySpeciesIn (const string& ref) const 
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
		string compLHS = lhs->getCompartment ();
		string compTypeIdLHS = lhs->getCompTypeId ();
		
		//	is compartment same?
		string compRHS = rhs->getCompartment(); 
		if (compLHS != compRHS) continue; 

		//	if same cnModel Strucutrue
		if (!lhs->equal (rhs)) continue;

		//	compare their corresonded compartment
		string compTypeIdRHS = rhs->getCompTypeId ();
		if (compTypeIdLHS.empty () && 
				compTypeIdRHS.empty()) return lhs;
		else if (compTypeIdLHS == compTypeIdRHS) return lhs;
		else continue;
	}
	return NULL;
}

const MySpecies* MyCompartment::isMySpeciesIn (
		const MySpecies* rhs
		) const
{

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
		string compLHS = lhs->getCompartment ();
		string compTypeIdLHS = lhs->getCompTypeId ();
		
		//	is compartment same?
		string compRHS = rhs->getCompartment(); 
		if (compLHS != compRHS) continue; 

		//	if same cnModel Strucutrue
		if (!lhs->equal (rhs)) continue;

		//	compare their corresonded compartment
		string compTypeIdRHS = rhs->getCompTypeId ();
		if (compTypeIdLHS.empty () && 
				compTypeIdRHS.empty()) return lhs;
		else if (compTypeIdLHS == compTypeIdRHS) return lhs;
		else continue;
	}
	return NULL;
}

MyCompartment* MyCompartment::isMyCompartmentIn (
		const string& ref
		)
{
	for (int i =0; i < listOfMyCompartmentsIn.size (); i++)
	{
		MyCompartment* comp = listOfMyCompartmentsIn[i];
		if (comp->getId () == ref) return comp;
	}
	return NULL;
}

const MyCompartment* MyCompartment::isMyCompartmentIn (
		const string& ref
		) const
{
	for (int i =0; i < listOfMyCompartmentsIn.size (); i++)
	{
		MyCompartment* comp = listOfMyCompartmentsIn[i];
		if (comp->getId () == ref) return comp;
	}
	return NULL;
}
