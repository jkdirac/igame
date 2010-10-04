#include "mycompartment.h"

	MyCompartment::MyCompartment ()
:Compartment (2,4)
{}

MyCompartment::~MyCompartment ()
{}

void MyCompartment::setDbId (
		const string& dbid
		)
{
	dbId = dbid;
}

string MyCompartment::getDbId () const
{
	return dbId;
}

void MyCompartment::addMySpeciesIn (
		MySpecies* s
		)
{
	listOfMySpeciesIn.push_back (s);
}

void MyCompartment::addMyCompartmentIn (
		MyCompartment* comp
		)
{
	listOfMyCompartmentsIn.push_back (comp);
}

MySpecies* MyCompartment::isMySpeciesIn (
		const string& sbmlid
		)
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

MySpecies* MyCompartment::isMySpeciesIn (
		const MySpecies* s
		)
{

	for (int i=0; i < listOfMySpeciesIn.size (); i++)
	{
		MySpecies* species = listOfMySpeciesIn[i];
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
