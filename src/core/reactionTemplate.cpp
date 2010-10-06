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
		if (s->getDB_Label () == speciesLabel) 
			return s->getCompartment ();
	}

	for (int i=0; i<listOfMyModifiers.size (); i++)
	{
		MySpecies* s = listOfMyModifiers[i];
		if (s->getDB_Label () == speciesLabel) 
			return s->getCompartment ();
	}

	for (int i=0; i<listOfMyProducts.size (); i++)
	{
		MySpecies* s = listOfMyProducts[i];
		if (s->getDB_Label () == speciesLabel) 
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
		if (s->getDB_Label () == speciesLabel) return s;
	}

	for (int i=0; i<listOfMyModifiers.size (); i++)
	{
		MySpecies* s = listOfMyModifiers[i];
		cout << "\nlabel = " << s->getDB_Label () << endl;
		if (s->getDB_Label () == speciesLabel) return s;
	}

	for (int i=0; i<listOfMyProducts.size (); i++)
	{
		MySpecies* s = listOfMyProducts[i];
		if (s->getDB_Label () == speciesLabel) return s; 
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
	/**
	 * Generate a set of compartment configurations
	 * *
	 * Each configuration requires correction of  
	 * (1) compartment database identifiers
	 * (2) relations between compartments
	 * *
	 * Results are stored in a vector<map<string,int>> 
	 * map<string,int> maps the compartment db label to the index in reality
	 */

	int permALL_DB = 1;
	int n = mapComps.size ();

	vector<string> compLabels;
	vector< vector<int> > options;
	
	map<string,string>::const_iterator first = mapComps.begin ();
	for (int i=0; first != mapComps.end (); i++, first ++)
	{
		string comp_id_db = first->second;
		compLabels.push_back (first->first);
		
		vector<int> __opt;
		for (int j=0; j<listOfMyCompartments.size (); j++)
		{
			MyCompartment* mycomp = listOfMyCompartments[j];
			if (mycomp->getDB_ref () == comp_id_db) __opt.push_back (j);
		}

		if (__opt.size () == 0) return false;
		else 
		{
			options.push_back (__opt); 
			permALL_DB *= __opt.size ();
		}
	}
	
	vector< map<string, int> > compConfig;	//	important

	for (int i=0; i < permALL_DB; i++)
	{
		map<string,int> conf;
		int divide = i;

		for (int j=0; j < n; j++)
		{
			string __comp_label = compLabels[j];
			int __comp_index = options[j][divide % options[j].size ()];
			
			if (conf.count (__comp_label)) throw StrCacuException (
					"Compartments in Reaction Definition should have different LABELs!"
					);
			else conf.insert (make_pair (__comp_label, __comp_index));
			divide /= kind[j].size ();
		}

		//	validate relations between compartments
		bool fail = false;
		for (int j=0; j < n; j++)
		{
			string __prent = compLabels[j];
			string __parent_index = conf[__parent];
			MyCompartment* parentComp = listOfMyCompartments[__parent_index];

			int entries = mapComps.count (__parent);
			multimap<string,string>::iterator iter = 
				mapComps.find (__parent);

			for (int cnt=0; cnt != entries; cnt++, iter++)
			{
				string __child = iter->second;
				if (conf.count (__child))
				{
					int __child_index = conf[__child];
					
					/**
					 * check if compartment __child_index is the child
					 * of compartment __parent_index in biological system
					 */
					MyCompartment* childComp = listOfMyCompartments[__child_index];
					MyCompartment* found = parentComp->isMyCompartmentIn (childComp->getId ());
					if (found == NULL) {
						fail = true; break;
					}
				}
			}

			if (fail) break;
		}

		if (fail) continue;
		else compConfig.push_back (conf);
	}

	if (compConfig.empty ()) return false;

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
	
	int permAll1 = 1;	//	all permutations of reactants

	/**
	 *	map between species index and its matching details
	 */

	if (role == "reactant")
	{
		bool fail1 = false; 
		for (int i=0; i < listOfMyReactants.size (); i++)
		{
			//
			//	special handle for current species 
			//
			MySpecies* tmReactant = listOfMyReactants[i];
			if (i == currSpeIndex)
			{
				MySpecies* currSpe = listOfMySpecies[currSpeIndex];

				cMatchsArray trym;
				if (currSpe->match (tmReactant, trym))
				{
					/**
					 * pair relation between species index and its matching info.
					 */
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
	}

	//
	//	find species matching for modifiers
	//
	int permAll2 = 1;

	if (role == "modifier")
	{
		bool fail2 = false; 
		for (int i=0; i < listOfMyModifiers.size (); i++)
		{
			MySpecies* tmModifier = listOfMyModifiers[i];
			if (i == currSpeIndex)
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
	}

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

	/**
	 * *************************************************
	 * all reactants/modifiers matching are obtained, in
	 * possibleReactantMatch and possibleModifierMatch,
	 * we need to check the compartment constraints
	 * *************************************************
	 * record possible compartment configuration 
	 * survived in compartment configuration validation
	 * *************************************************
	 */
	

	for (int i =0; i < possibleReactantMatch.size (); i++)
		for (int j =0; j < possibleModifierMatch.size (); j++)
		{
			//	find all possible compartment configuration
			set<int> possible;

			//	reactant constraints
			assert (possibleReactantMatch[i].size () == listOfMyReactants.size ());
			for (int n1 = 0; n1 < n; n1++)
			{
				bool fail = false;
				for (int n2=0; n2 < possibleReactantMatch[i].size (); n2++)
				{
					//	parameter about template spcies
					string __compLabel_tm = listOfMyReactants[n2]->getCompartment ();
					string __compid_tm;
					if (compConfig[n1].count (__compLabel_tm))
					{
						MyCompartment* c= listOfMyCompartments[compConfig[n1][__compLabel_tm]];
						__compid_tm = c->getId ();
					}
					else throw StrCacuException (
							"No compartment read for species in reaction template!"
							);

					//	parameter about real species
					int __species_index = possibleReactantMatch[i][n2].first;
					string __compid = listOfMySpecies[__species_index]->getCompartment ();

					if (__compid_tm != __compid) {fail = true;break;}
				}
				if (!fail) possible.insert (n1);
			}
			if (possible.empty ()) continue;

			//	modifier constraints
			assert (possibleModifierMatch[j].size () == listOfMyModifiers.size ());
			for (int n1 = 0; n1 < n; n1++)
			{
				if (!possible.count (n1)) continue;

				bool fail = false;
				for (int n2=0; n2 < possibleModifierMatch[j].size (); n2++)
				{
					//	parameter about template spcies
					string __compLabel_tm = listOfMyModifiers[n2]->getCompartment ();
					string __compid_tm;
					if (compConfig[n1].count (__compLabel_tm))
					{
						MyCompartment* c= listOfMyCompartments[compConfig[n1][__compLabel_tm]];
						__compid_tm = c->getId ();
					}
					else throw StrCacuException (
							"No compartment read for species in reaction template!"
							);

					//	parameter about real species
					int __species_index = possibleModifierMatch[j][n2].first;
					string __compid = listOfMySpecies[__species_index]->getCompartment ();

					if (__compid_tm != __compid) {fail = true;break;}
				}
				if (fail) possible.erase (n1);
			}
			if (possible.empty ()) continue;

			//	compartment-type species constraints
			for (int n1=0; n1 < n; n1++)
			{
				if (!possible.count (n1)) continue;
				
				map<string, string> itself;
				for (int n2 =0; n2 < possibleReactantMatch[i].size (); n2++)
				{
					string __species_itself = listOfMyReactants[n2]->getCompTypeId ();
					if (!__species_itself.empty ())
					{
						int __species_index = possibleReactantMatch[i][n2].first;
						string __species_id = listOfMySpecies[__species_index]->getId ();
						if (!itself.count (__species_itself)) 
							itself[__species_itself] = __species_id;
						else if (itself[__species_itself] != __species_id) {
							possible.erase (n1);
							break;
						}
					}
				}
			}
			if (possible.empty ()) continue;

			if (notfail) result.push_back (
				make_pair (possibleReactantMatch[i], possibleModifierMatch[j])
				);
		}
	}

	return result.size () > 0;
}

//
//	Based on products templates and pattern matchings of
//	reactants and modifiers, new products by replacing 
//	substituent parts are generated and stored in productCandidates
//
void reactionTemplate::createProductsFromTemplate (
		const speciesArrayMatch& reactantCandidates,
		const speciesArrayMatch& modifierCandidates,
		const vector<MySpecies*>& listOfMySpecies,
		vector<MySpecies*>& productCandidates
		)
{
	for (int i=0; i < listOfMyProducts.size (); i++)
	{
		MySpecies* origproduct = listOfMyProducts[i];
		string productLabel = origproduct->getDB_Label ();

		MySpecies* newproduct = new MySpecies;
		newproduct->setDB_Label (productLabel);

		for (int j=0; j< origproduct->getNumOfChains(); j++)
		{
			Chain* origchain = origproduct->getChain (j);
			Chain* newchain = newproduct->createChain ();

			for (int k=0; k < origchain->getNumOfParts (); k++)
			{
				Part* origpart = origchain->getPart (k);
				if (origpart->getPartCtg () == "substituent")
				{
					string subLabel = origpart->getPartLabel ();
					pair<string,string> destine = make_pair (
							productLabel, subLabel
							);
					if (!transferTable.count (destine))
						throw StrCacuException (
								"Lack Info. for Substituent Transfer!"
								);
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

						if (tmps == NULL) throw StrCacuException (
								"Fail in search  species with label "
								);
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
		if (s->getDB_Label () == speciesLabel) return cnt;
		else {first++;cnt++;}
	}

	return -1;	
}
