#include "reactionTemplate.h"

reactionTemplate::reactionTemplate ()
{}

reactionTemplate::~reactionTemplate ()
{
  for (int i=0; i<listOfMyReactants.size (); i++)
	delete listOfMyReactants[i];
  for (int i=0; i<listOfMyModifiers.size (); i++)
	delete listOfMyModifiers[i];
  for (int i=0; i<listOfMyProducts.size (); i++)
	delete listOfMyProducts[i];
  for (int i=0; i<listOfParameters.size (); i++)
	delete listOfParameters[i];
}

void reactionTemplate::setId (
	const string& _id
	)
{
  id = _id;
}

void reactionTemplate::setName (
	const string& _name
	)
{
  name = _name;
}

void reactionTemplate::setReversible (
	const bool& _rev
	)
{
  reversible = _rev;
}

void reactionTemplate::setFast (
	const bool& _fast
	)
{
  fast = _fast;
}

string reactionTemplate::getId () const
{
  return id;
}

string reactionTemplate::getName () const
{
  return name;
}

bool reactionTemplate::getFast () const
{ 
  return fast;
}

bool reactionTemplate::getReversible () const
{
  return reversible;
}

string reactionTemplate::getMath () const
{
  return math;
}

Parameter* reactionTemplate::getParameter (
		const string& sid
		)
{
	for (int i=0; i<listOfParameters.size (); i++)
	{
		Parameter* para = listOfParameters[i];
		if (para->getId () == sid) return para;
	}
	return NULL;
}

string reactionTemplate::getCompartment (
		const string& speciesLabel
		) const
{
	for (int i=0; i<listOfMyReactants.size (); i++)
	{
		MySpecies* s = listOfMyReactants[i];
		if (s->getLabel () == speciesLabel) 
			return s->getCompartment ();
	}

	for (int i=0; i<listOfMyModifiers.size (); i++)
	{
		MySpecies* s = listOfMyModifiers[i];
		if (s->getLabel () == speciesLabel) 
			return s->getCompartment ();
	}

	for (int i=0; i<listOfMyProducts.size (); i++)
	{
		MySpecies* s = listOfMyProducts[i];
		if (s->getLabel () == speciesLabel) 
			return s->getCompartment ();
	}

	return string ();
}
const MySpecies* reactionTemplate::getSpecies (
		const string& speciesLabel
		) const
{
	for (int i=0; i<listOfMyReactants.size (); i++)
	{
		MySpecies* s = listOfMyReactants[i];
		if (s->getLabel () == speciesLabel) return s;
	}

	for (int i=0; i<listOfMyModifiers.size (); i++)
	{
		MySpecies* s = listOfMyModifiers[i];
		cout << "\nlabel = " << s->getLabel () << endl;
		if (s->getLabel () == speciesLabel) return s;
	}

	for (int i=0; i<listOfMyProducts.size (); i++)
	{
		MySpecies* s = listOfMyProducts[i];
		if (s->getLabel () == speciesLabel) return s; 
	}

	return NULL;
}

void reactionTemplate::addCompartment (
	const string& _compRef,
	const string& _currComp,
	const string& _parComp
	)
{
  if (mapComps.count (_currComp))
	throw StrCacuException (
			"Two Many Compartments of the same label!"
			);
  else
  {
	mapComps[_currComp] = _compRef;
	mmapComps.insert (make_pair (_parComp, _currComp));
  }
}

void reactionTemplate::addParameter (
		Parameter* para
		)
{
	listOfParameters.push_back (para);
}

void reactionTemplate::addConstraint (
		const vector<string>& vars,
		const string& formula
		)
{
	listOfConstraints.push_back (
			make_pair (vars, formula)
			);
}

void reactionTemplate::addReactant (
	MySpecies* s,
	const string& compLabel
	)
{
  mmapIndexReactants.insert (
	  make_pair (compLabel, listOfMyReactants.size ())
		);
  listOfMyReactants.push_back (s);
}

void reactionTemplate::addProduct (
	MySpecies* s,
	const string& compLabel
	)
{
  mmapIndexProducts.insert (
	  make_pair (compLabel, listOfMyProducts.size ())
		);
  listOfMyProducts.push_back (s);
}

void reactionTemplate::addModifier (
	MySpecies* s,
	const string& compLabel
	)
{
  mmapIndexModifiers.insert (
	  make_pair (compLabel, listOfMyModifiers.size ())
		);
  listOfMyModifiers.push_back (s);
}

void reactionTemplate::addSubstituentTransfer (
	const pair<string,string>& from,
	const pair<string,string>& to
	)
{
  transferTable.insert (make_pair (to, from));
}

void reactionTemplate::setMath (
	const string& _math
	)
{
  math = _math;
}

bool reactionTemplate::findSpeciesMatch (
	const vector<MyCompartment*>& listOfMyCompartments,
	const vector<MySpecies*>& listOfMySpecies,
	const int& currSpeIndex,
	const string& role,
	reactionArrayMatch& result	
	) 
{
  //
  //  temporary variables
  //
  speciesArrayMatch* reactant_sam = 
	new speciesArrayMatch [listOfMyReactants.size ()]; 
  speciesArrayMatch* modifier_sam = 
	new speciesArrayMatch [listOfMyModifiers.size ()]; 

  //
  //	find species matching for reactants 
  //
  bool fail1 = false; 
  int permAll1 = 1;

  for (int i=0; i < listOfMyReactants.size (); i++)
  {
	//
	//	special handle for current species 
	//
	MySpecies* tmReactant = listOfMyReactants[i];
	if (role == "reactant" && i == currSpeIndex)
	{
	  MySpecies* currSpe = listOfMySpecies[currSpeIndex];

	  cMatchsArray trym;
	  if (currSpe->match (tmReactant, trym))
	  {
		for (int k=0; k < trym.size (); k++)
		  reactant_sam[i].push_back (make_pair (currSpeIndex, trym[k]));
	  }
	  else 
	  {
		fail1 = true;
		break;
	  }
	}
	else
	{
	  for (int j=0; j <= currSpeIndex; j++)
	  {
		MySpecies* prevSpe = listOfMySpecies[j];

		cMatchsArray trym;
		if (prevSpe->match (tmReactant, trym))
		{
		  for (int k=0; k < trym.size (); k++)
			reactant_sam[i].push_back (make_pair (j, trym[k]));
		}
	  }
	  if (reactant_sam[i].empty ()) 
	  {
		fail1 = true;
		break;
	  }
	  else permAll1 *= reactant_sam[i].size ();
	}
  }

  if (fail1) return false;

  //
  //	find species matching for modifiers
  //
  bool fail2 = false; 
  int permAll2 = 1;

  for (int i=0; i < listOfMyModifiers.size (); i++)
  {
	MySpecies* tmModifier = listOfMyModifiers[i];
	if (role == "modifier" && i == currSpeIndex)
	{
	  MySpecies* currSpe = listOfMySpecies[currSpeIndex];

	  cMatchsArray trym;
	  if (currSpe->match (tmModifier, trym))
	  {
		for (int k=0; k < trym.size (); k++)
		{
		  modifier_sam[i].push_back (make_pair (currSpeIndex, trym[k]));
		}
	  }
	  else 
	  {
		fail2 = true;
		break;
	  }
	}
	else
	{
	  for (int j=0; j <= currSpeIndex; j++)
	  {
		MySpecies* prevSpe = listOfMySpecies[j];

		cMatchsArray trym;
		if (prevSpe->match (tmModifier, trym))
		{
		  for (int k=0; k < trym.size (); k++)
			modifier_sam[i].push_back (make_pair (j, trym[k]));
		}
	  }
	  if (modifier_sam[i].empty ()) 
	  {
		fail2 = true;
		break;
	  }
	  else permAll2 *= modifier_sam[i].size ();
	}
  }

  if (fail2) return false;

  //
  //	permutation to find all possible combinations
  //	reactant_sam and modifier_sam are both of type speciesArrayMatch*
  //

  vector<speciesArrayMatch> possibleReactantMatch;

  for (int i =0; i < permAll1; i++)
  {
	speciesArrayMatch tryMS; 

	int divide = i;
	for (int j =0; j < listOfMyReactants.size (); j++)
	{
	  int indperm = divide % reactant_sam[j].size ();
	  tryMS.push_back (reactant_sam[j][indperm]);
	  divide /= reactant_sam[j].size ();
	}

	possibleReactantMatch.push_back (tryMS);
  }
  delete [] reactant_sam;

  vector<speciesArrayMatch> possibleModifierMatch;

  for (int i =0; i < permAll2; i++)
  {
	speciesArrayMatch tryMS; 

	int divide = i;
	for (int j =0; j < listOfMyModifiers.size (); j++)
	{
	  int indperm = divide % modifier_sam[j].size ();
	  tryMS.push_back (modifier_sam[j][indperm]);
	  divide /= modifier_sam[j].size ();
	}

	possibleModifierMatch.push_back (tryMS);
  }
  delete [] modifier_sam;

  //
  //	find possible combinations of reactants and modifiers
  //	under constraints of compartment configuration and parameters
  //

  for (int i =0; i < possibleReactantMatch.size (); i++)
  {
	for (int j =0; j < possibleModifierMatch.size (); j++)
	{
	  //
	  //  compartment constraints
	  //
	  set<string> compUsed;
	  bool ok1 = compartmentConstraints (
		  "ROOT", "", compUsed, listOfMyCompartments, listOfMySpecies,
		  possibleReactantMatch[i], possibleModifierMatch[j]
		  );

	  if (ok1) 
		result.push_back (make_pair (
			  possibleReactantMatch[i],
			  possibleModifierMatch[j]
			  )
			);
	}
  }

  return result.size () > 0;
}

bool reactionTemplate::compartmentConstraints (
	const string& searchComp, //Rlabel 
	const string& parentComp, //sbml id of parent compartment
	set<string>& compUsed,
	const vector<MyCompartment*>& listOfMyCompartments,
	const vector<MySpecies*>& listOfMySpecies,
	const speciesArrayMatch& reactantCandidates,
	const speciesArrayMatch& modifierCandidates
	) 
{ 
  string searchCompDbId;  //db id of Rlabel
  if (mapComps.count (searchComp))
	searchCompDbId = mapComps.find (searchComp)->second; 

  //
  //	FOR REACTANTS
  //
  int entries = mmapIndexReactants.count (searchComp);
  multimap<string,int>::iterator iter = 
	mmapIndexReactants.find (searchComp);

  MyCompartment* fixedComp = NULL;

  for (int cnt=0; cnt != entries; cnt++, iter++)
  {
	int speciesIndex = reactantCandidates[iter->second].first; //index in listOfMySpecies
	string speciesLabel = listOfMySpecies[speciesIndex]->getId ();

	//
	//	find compartment where it locates in
	//
	MyCompartment* currComp = NULL;
	cout << "\nsize = " << listOfMyCompartments.size () << endl;
	for (int icomp =0; icomp < listOfMyCompartments.size (); icomp++)
	{
	  MyCompartment* mycomp = listOfMyCompartments[icomp];
	  cout << "\nmycomp == " << mycomp->getId () << "\n speicesLabel = " << speciesLabel << endl;
	  if (mycomp->isMySpeciesIn (speciesLabel) != NULL) currComp = mycomp;
	}

	//	check
	if (currComp == NULL) 
	{
		string errno (
			  "\nNo Compartment Found for Species with Label "
			  );
		errno += speciesLabel;
		throw StrCacuException (errno);
	}

	if (cnt == 0) 
	{
	  fixedComp = currComp;

	  if (compUsed.count (fixedComp->getId ())) return false;
	  else compUsed.insert (fixedComp->getId ());

	  string parent = fixedComp->getOutside ();
	  if (parentComp != "ROOT" && parent != parentComp) return false;
	  if (fixedComp->getDbId () != searchCompDbId) return false;
	}
	else if (currComp->getId () != fixedComp->getId ()) return false;
  }

  //
  //	FOR MODIFIERS
  //
  entries = mmapIndexModifiers.count (searchComp);
  iter = mmapIndexModifiers.find (searchComp);

  for (int cnt=0; cnt != entries; cnt++, iter++)
  {
	int speciesIndex = modifierCandidates[iter->second].first;
	string speciesLabel = listOfMySpecies[speciesIndex]->getId ();

	//
	//	find compartment where it locates in
	//
	MyCompartment* currComp = NULL;
	cout << "\nsize = " << listOfMyCompartments.size () << endl;
	for (int icomp =0; icomp < listOfMyCompartments.size (); icomp++)
	{
	  MyCompartment* mycomp = listOfMyCompartments[icomp];
	  cout << "\nmycomp == " << mycomp->getId () << "\n speicesLabel = " << speciesLabel << endl;
	  if (mycomp->isMySpeciesIn (speciesLabel) != NULL) currComp = mycomp; 
	}
	
	//	check
	if (currComp == NULL) 
	{
		string errno (
			  "\nNo Compartment Found for Species with Label "
			  );
		errno += speciesLabel;
		throw StrCacuException (errno);
	}

	if (fixedComp != NULL)
	{
	  if (currComp->getId () != fixedComp->getId ()) return false;
	}
	else 
	{
	  fixedComp = currComp;

	  if (compUsed.count (fixedComp->getId ())) return false;
	  else compUsed.insert (fixedComp->getId ());

	  string parent = fixedComp->getOutside ();
	  if (parentComp != "ROOT" && parent != parentComp) return false;
	  if (fixedComp->getDbId () != searchCompDbId) return false;
	}
  }

  //
  //	CHECK CHILDREN COMPARTMENTS RECURSIVELY
  //
  entries = mmapComps.count (searchComp);
  multimap<string,string>::iterator iter_c = mmapComps.find (searchComp);

  string corresComp;
  if (fixedComp == NULL) corresComp = "ROOT";
  else corresComp = fixedComp->getId ();

  for (int cnt=0; cnt != entries; cnt++, iter_c++)
  {
	string child = iter_c->second;
	bool ism = compartmentConstraints (
		child, corresComp, compUsed, listOfMyCompartments, listOfMySpecies, 
		reactantCandidates, modifierCandidates
		);
	if (!ism) return false;
  }
  return true;
}

//
//	Based on products templates and pattern matchings of
//	reactants and modifiers, new products by replacing 
//	substituent parts are generated and stored in productCandidates
//
void reactionTemplate::genProductBody (
	const speciesArrayMatch& reactantCandidates,
	const speciesArrayMatch& modifierCandidates,
	const vector<MySpecies*>& listOfMySpecies,
	vector<MySpecies*>& productCandidates
	)
{
  for (int i=0; i < listOfMyProducts.size (); i++)
  {
	MySpecies* origproduct = listOfMyProducts[i];
	string productLabel = origproduct->getLabel ();

	MySpecies* newproduct = new MySpecies;

	for (int j=0; j< origproduct->getNumOfChains(); j++)
	{
	  Chain* origchain = origproduct->getChain (j);
	  Chain* newchain = newproduct->createChain ();

	  for (int k=0; k < origchain->getNumOfParts (); k++)
	  {
		Part* origpart = origchain->getPart (k);
		if (origpart->getPartCategory () == "substituent")
		{
		  string subLabel = origpart->getPartLabel ();
		  pair<string,string> destine = make_pair (
			  productLabel, subLabel
			  );
		  if (!transferTable.count (destine))
		  {
			string errno ("Lack Info. for Substituent Transfer!");
			throw errno;
		  }
		  else
		  {
			pair<string,string> source = transferTable[destine];

			//reactant or modifier?
			MySpecies* tmps = NULL;

			int ridx = searchSpecies ('r', source.first);
			if (ridx >= 0)
			{
			  tmps = listOfMySpecies[reactantCandidates[ridx].first];
			  int chain_lst = reactantCandidates[ridx].second[j].second;
			  Chain* ck = tmps->getChain (chain_lst);

			  cMatchType cmt = reactantCandidates[ridx].second[j].first;
			  list< pair<int,int> >::const_iterator cmtf = cmt.begin ();
			  
			  int cnt = 0;
			  while (cnt++ == k) cmtf++;

			  int start, end;
			  start = cmtf->first; 
			  end = cmtf->second;

			  for (int t = start; t <= end; t++)
			  {
				Part* pk = ck->getPart (t);
				newchain->createPart (pk);
			  }
			}

			int midx = searchSpecies ('m', source.first);
			if (midx >= 0)
			{
			  tmps = listOfMySpecies[modifierCandidates[midx].first];
			  int chain_lst = modifierCandidates[midx].second[j].second;
			  Chain* ck = tmps->getChain (chain_lst);

			  cMatchType cmt = modifierCandidates[midx].second[j].first;
			  list< pair<int,int> >::const_iterator cmtf = cmt.begin ();
			  
			  int cnt = 0;
			  while (cnt++ == k) cmtf++;

			  int start, end;
			  start = cmtf->first; 
			  end = cmtf->second;

			  for (int t = start; t <= end; t++)
			  {
				Part* pk = ck->getPart (t);
				newchain->createPart (pk);
			  }
			}

			if (tmps == NULL) 
			{
			  string errno ("Fail in search  species with label ");
			  errno += source.first;
			  throw errno;
			}
		  }
		}
		else newchain->createPart (origpart);
	  }
	}

	for (int j=0; j < origproduct->getNumOfTrees (); j++)
	  newproduct->createTree (origproduct->getTree (j));

	productCandidates.push_back (newproduct);
  }
}

int reactionTemplate::searchSpecies (
	const char& role,
	const string& speciesLabel
	)
{
  vector<MySpecies*>::const_iterator first, last;
  switch (role)
  {
	case 'r': 
	  {
		first = listOfMyReactants.begin ();
		last = listOfMyReactants.end ();
		break;
	  }
	case 'm': 
	  {
		first = listOfMyModifiers.begin ();
		last = listOfMyModifiers.end ();
		break;
	  }
	case 'p': 
	  {
		first = listOfMyProducts.begin ();
		last = listOfMyProducts.end ();
		break;
	  }
	default: return -1;
  }
  
  int cnt =0;
  while (first != last)
  {
	MySpecies* s = *first;
	if (s->getLabel () == speciesLabel) return cnt;
	else {first++;cnt++;}
  }
  
  return -1;	
}
