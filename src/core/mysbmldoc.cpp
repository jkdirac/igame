#include "mysbmldoc.h"

MySBMLDocument::MySBMLDocument ():
  SBMLDocument (2,4)
{
  //complete unit map
  unitMap["ampere"] = UNIT_KIND_AMPERE;
  unitMap["becquerel"] = UNIT_KIND_BECQUEREL;
  unitMap["candela"] = UNIT_KIND_CANDELA;
  unitMap["coulomb"] = UNIT_KIND_COULOMB;
  unitMap["dimensionless"] = UNIT_KIND_DIMENSIONLESS;
  unitMap["farad"] = UNIT_KIND_FARAD;
  unitMap["gram"] = UNIT_KIND_GRAM;
  unitMap["gray"] = UNIT_KIND_GRAY;
  unitMap["henry"] = UNIT_KIND_HENRY;
  unitMap["hertz"] = UNIT_KIND_HERTZ;
  unitMap["item"] = UNIT_KIND_ITEM;
  unitMap["joule"] = UNIT_KIND_JOULE;
  unitMap["katal"] = UNIT_KIND_KATAL;
  unitMap["kelvin"] = UNIT_KIND_KELVIN;
  unitMap["kilogram"] = UNIT_KIND_KILOGRAM;
  unitMap["litre"] = UNIT_KIND_LITRE;
  unitMap["lumen"] = UNIT_KIND_LUMEN;
  unitMap["lux"] = UNIT_KIND_LUX;
  unitMap["metre"] = UNIT_KIND_METRE;
  unitMap["mole"] = UNIT_KIND_MOLE;
  unitMap["newton"] = UNIT_KIND_NEWTON;
  unitMap["ohm"] = UNIT_KIND_OHM;
  unitMap["pascal"] = UNIT_KIND_PASCAL;
  unitMap["radian"] = UNIT_KIND_RADIAN;
  unitMap["second"] = UNIT_KIND_SECOND;
  unitMap["siemens"] = UNIT_KIND_SIEMENS;
  unitMap["sievert"] = UNIT_KIND_SIEVERT;
  unitMap["steradian"] = UNIT_KIND_STERADIAN;
  unitMap["tesla"] = UNIT_KIND_TESLA;
  unitMap["volt"] = UNIT_KIND_VOLT;
  unitMap["watt"] = UNIT_KIND_WATT;
  unitMap["weber"] = UNIT_KIND_WEBER;
  unitMap["invalid"] = UNIT_KIND_INVALID;
}

MySBMLDocument::~MySBMLDocument ()
{
  for (int i=0; i < listOfMySpecies.size (); i++)
	delete listOfMySpecies[i];
  for (int i=0; i < listOfMyCompartments.size (); i++)
	delete listOfMyCompartments[i];
  for (int i=0; i < listOfMyReactions.size (); i++)
	delete listOfMyReactions[i];
}

MySpecies* MySBMLDocument::createMySpecies ()
{
  MySpecies* s = new MySpecies;
  listOfMySpecies.push_back (s);
  return s;
}

MyCompartment* MySBMLDocument::createMyCompartment ()
{
  MyCompartment* c = new MyCompartment;
  listOfMyCompartments.push_back (c);
  return c;
}

MyReaction* MySBMLDocument::createMyReaction ()
{
  MyReaction* r = new MyReaction;
  listOfMyReactions.push_back (r);
  return r;
}

MyCompartment* MySBMLDocument::getMyCompartment (
	const string& label
	)
{
  for (int i=0; i < listOfMyCompartments.size (); i++)
  {
	MyCompartment* comp = listOfMyCompartments[i];
	if (comp->getId () == label) return comp;
  }
  return NULL;
}

const MyCompartment* MySBMLDocument::getMyCompartment (
	const string& label
	) const
{
  for (int i=0; i < listOfMyCompartments.size (); i++)
  {
	MyCompartment* comp = listOfMyCompartments[i];
	if (comp->getId () == label) return comp;
  }
  return NULL;
}

int MySBMLDocument::getNumOfMyCompartments () const
{
  return listOfMyCompartments.size ();
}

int MySBMLDocument::getNumOfMySpecies () const
{
  return listOfMySpecies.size ();
}

MySpecies* MySBMLDocument::validateBackSpecies ()
{
  MySpecies* sEx = listOfMySpecies.back ();
  string compId = sEx->getCompartment ();

  for (int i=0; i < listOfMySpecies.size ()-1; i++)
  {
	MySpecies* s = listOfMySpecies[i];
	if (s->getCompartment () != compId) continue;
	else if (s->equal (sEx)) 
	{
	  listOfMySpecies.pop_back ();
	  delete sEx;
	  return s;
	}
  }
  return NULL;
}

string MySBMLDocument::genSbmlId () const
{
  ostringstream oss;
  oss << "sPecIes" << listOfMySpecies.size ();
  return string (oss.str ());
}

UnitKind_t MySBMLDocument::getUnitKind_t (
	const string& unit
	) const
{
  if (unitMap.count (unit))
	return unitMap.find (unit)->second;
  else return unitMap.find ("invalid")->second;
}

void MySBMLDocument::run (
	readDataBase& dbreader
	)
{
  //
  //  listOfMySpecies size may be updated while 
  //  developing biological system network
  //
  int numOfSpecies = listOfMySpecies.size ();

  //  for each species in listOfMySpecies
  for (int i= 0; i < numOfSpecies; i++)
  {
	//for each species
	MySpecies* s = listOfMySpecies[i];

	//a set to store species id that has been used
	set<string> speciesUsed;

	for (int j =0; j < s->getNumOfChains (); j++)
	{
	  Chain* c = s->getChain (j);
	  for (int k=0; k < c->getNumOfParts (); k++)
	  {
		Part* p = c->getPart (k);

		//read species link
		string speciesLinkPath =
		  "/sbpmodel/part/" +
		  p->getPartCategory () + 
		  "/listOfSpeciesLinks/"
		  "speciesLink";
		string doc_1 = p->getDbId ();

		int numOfSpeciesLinks = 
		  dbreader.get_node_element_num (PART, &doc_1, &speciesLinkPath);

		for (int t=1; t <= numOfSpeciesLinks; t++)
		{
		  string speciesReference, partType;
		  dbreader.readSpeciesLink (
			  PART, p->getDbId (),speciesLinkPath, 
			  t, speciesReference, partType
			  );

		  //
		  //  constraints
		  //
		  if (speciesReference.empty ())
		  {
			string errno ("Reading Part...Empty "
				"speciesReference attribute!");
			throw errno;
		  }

		  if (speciesUsed.count (speciesReference)) continue;
		  else speciesUsed.insert (speciesReference);

		  if (!partType.empty () && 
			  partType != p->getPartType ()) continue;

		  //
		  //  handle species read
		  //
		  
		  MySpecies* sLink = new MySpecies;
		  sLink->setDbId (speciesReference);  
		  dbreader.readSpecies_db (sLink);

		  //
		  //  is this species template match?
		  //
		  vector<MySpecies::cMatchsType2> trym;
		  if (!s->match (sLink, trym)) continue;

		  //
		  //  read reaction Links
		  //
		  string reactionLinkPath =
			"/sbpmodel/species/"  
			"/listOfReactionLinks/"
			"reactionLink";

		  int numOfReactionLinks = dbreader.get_node_element_num (
			  SPECIES, &speciesReference, &reactionLinkPath
			  );

		  for (int r=1; r <= numOfReactionLinks; r++)
		  {
			string reactionReference, speciesRole;
			dbreader.readSpeciesLink (
				SPECIES, speciesReference, reactionLinkPath, 
				r, reactionReference, speciesRole
				);

			if (reactionReference.empty ())
			{
			  string errno ("Reading SPECIES...Empty "
				  "reactionReference attribute!");
			  throw errno;
			}
			
			bool validRole = 
			  (speciesRole == "reactant")
			  || (speciesRole == "product") 
			  || (speciesRole == "modifier");

			if (!validRole)
			{
			  string errno ("Reading SPECIES...Invalid "
				  "speciesRole value!");
			  throw errno;
			}

			handleReactionTemplate (
				dbreader, reactionReference, speciesRole, i
				);
		  }
		}
	  }
	}

	//
	//	update!
	//
	numOfSpecies = listOfMySpecies.size ();
  }

  //  add species, compartment and reaction to SBML file

  Model* m = getModel ();

  for (int i=0; i < listOfMySpecies.size (); i++)
	m->addSpecies (listOfMySpecies[i]);

  for (int i=0; i < listOfMyCompartments.size (); i++)
	m->addCompartment (listOfMyCompartments[i]);

  for (int i=0; i < listOfMyReactions.size (); i++)
	m->addReaction (listOfMyReactions[i]);
}

void MySBMLDocument::handleReactionTemplate (
	readDataBase& dbreader,
	const string& doc,
	const string& role,
	const int& speciesIndex
	)
{
  //  reaction direction
  bool direction = true;
  if (role == "product") direction = false;

  //create a reaction template object
  reactionTemplate* RT = new reactionTemplate;
  dbreader.readReactionTemplate (RT, doc, direction); 
 
  //
  //  find species and compartment configuration that
  //  matching patterns described in reaction template
  //
  reactionTemplate::reactionArrayMatch result;
  RT->findSpeciesMatch (
	  listOfMyCompartments, listOfMySpecies, 
	  speciesIndex, role, result
	  );

  //
  //  create reaction objects
  //
  for (int i=0; i < result.size (); i++)
  {
	ostringstream oss;
	oss << "rEactIon" << listOfMyReactions.size ();

	//	new reaction
	MyReaction* myreaction = createMyReaction ();

	//	set attributes
	myreaction->setId (oss.str ());
	myreaction->setName (RT->getName ());
	myreaction->setFast (RT->getFast ());
	myreaction->setReversible (false);

	//
	//	generate product body
	//
	vector<MySpecies*> newGenProducts;
	RT->genProductBody (
		result[i].first, result[i].second, 
		listOfMySpecies, newGenProducts
		);
	
	//
	//	generate real product
	//
	myreaction->completeReaction (
		listOfMyCompartments, listOfMySpecies, newGenProducts, 
		result[i].first, result[i].second, RT
		);

	for (int i=0; i < newGenProducts.size (); i++)
	  delete newGenProducts[i];
  }

  delete RT;
}

