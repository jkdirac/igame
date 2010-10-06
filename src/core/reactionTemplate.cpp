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
		const string& dbref, 
		const int& index,
		const vector<MySpecies*>& listOfMySpecies,
		const vector<MyCompartment*>& listOfMyCompartments,
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
			divide /= options[j].size ();

			cout << "\n__comp_label = " << __comp_label 
				 << "; __comp_index = " << __comp_index << endl;
		}

		//	validate relations between compartments
		bool fail = false;
		for (int j=0; j < n; j++)
		{
			string __parent = compLabels[j];
			int __parent_index = conf[__parent];
			MyCompartment* parentComp = listOfMyCompartments[__parent_index];

			int entries = mmapComps.count (__parent);
			multimap<string,string>::iterator iter = 
				mmapComps.find (__parent);
			
			cout << "\nparent = " << __parent 
				 << "  j = " << j 
				 << "  entries = " << entries << endl;

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
					if (found == NULL) {fail = true; break;}
				}
			}

			if (fail) break;
		}

		if (fail) continue;
		else compConfig.push_back (conf);
	}

	if (compConfig.empty ()) return false;
	else 
	{
		cout << "\nNumber of Compartment Configurations = " 
			 << compConfig.size () << endl;
	}

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

	bool fail1 = false; 
	for (int i=0; i < listOfMyReactants.size (); i++)
	{
		//
		//	special handle for current species 
		//
		MySpecies* tmReactant = listOfMyReactants[i];

		if (tmReactant->getDB_ref () == dbref)
		{
			MySpecies* currSpe = listOfMySpecies[index];

			cMatchsArray trym;

			//	is two species both/both not of compartment-type 
			bool same = isSameType (
					currSpe->getCompTypeId (), tmReactant->getCompTypeId ()
					);
						
			if (same && currSpe->match (tmReactant, trym))
			{
				/**
				 * pair relation between species index and its matching info.
				 */
				for (int k=0; k < trym.size (); k++)
					reactant_sam[i].push_back (make_pair (index, trym[k]));
			}
			else 
			{
				fail1 = true;
				break;
			}
		}
		else
		{
			for (int j=0; j <= index; j++)
			{
				MySpecies* prevSpe = listOfMySpecies[j];

				cMatchsArray trym;

				//	is two species both/both not of compartment-type 
				bool same = isSameType (
					prevSpe->getCompTypeId (), tmReactant->getCompTypeId ()
					);

				if (same && prevSpe->match (tmReactant, trym))
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

	//	no reactant match
	if (fail1) return false;
	else cout << "\npermALL1 = " << permAll1 << endl;

	
	//
	//	find species matching for modifiers
	//
	int permAll2 = 1;

	bool fail2 = false; 
	for (int i=0; i < listOfMyModifiers.size (); i++)
	{
		MySpecies* tmModifier = listOfMyModifiers[i];
		
		cout << "\ngetDB_ref = " << tmModifier->getDB_ref () 
			 << "  dbref =  "<< dbref << endl;

		if (tmModifier->getDB_ref () == dbref)
		{
			MySpecies* currSpe = listOfMySpecies[index];

			cMatchsArray trym;

			//	is two species both/both not of compartment-type 
			bool same = isSameType (
					currSpe->getCompTypeId (), tmModifier->getCompTypeId ()
					);
			bool mok = currSpe->match (tmModifier, trym);

			//	TEST
			cout << "\ncurrSpe = " << endl;
			currSpe->Output ();
			cout << "\ntmModifier = " << endl;
			tmModifier->Output ();
			cout << "\nmok = " << mok << endl;
			//	TEST OVER

			if (same && mok) 
			{
				for (int k=0; k < trym.size (); k++)
					modifier_sam[i].push_back (make_pair (index, trym[k]));
			}
			else 
			{
				fail2 = true;
				break;
			}
		}
		else
		{
			for (int j=0; j <= index; j++)
			{
				MySpecies* prevSpe = listOfMySpecies[j];

				cMatchsArray trym;

				//	is two species both/both not of compartment-type 
				bool same = isSameType (
						prevSpe->getCompTypeId (), tmModifier->getCompTypeId ()
						);

				if (same && prevSpe->match (tmModifier, trym))
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
	else cout << "\npermALL2 = " << permAll2 << endl;

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
	{
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

					//	LIAOCHEN MARK ... TAKE CARE!
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

				//	for reactants
				for (int n2 =0; n2 < possibleReactantMatch[i].size (); n2++)
				{
					string __species_itself = listOfMyReactants[n2]->getCompTypeId ();
					if (!__species_itself.empty ())
					{
						int __species_index = possibleReactantMatch[i][n2].first;
						string __comp_id = listOfMySpecies[__species_index]->getCompTypeId ();
						assert (!__comp_id.empty ());

						if (!itself.count (__species_itself)) 
							itself[__species_itself] = __comp_id;
						else if (itself[__species_itself] != __comp_id) {
							possible.erase (n1); break;
						}
					}
				}

				//	for modifiers
				for (int n2 =0; n2 < possibleModifierMatch[i].size (); n2++)
				{
					string __species_itself = listOfMyModifiers[n2]->getCompTypeId ();
					if (!__species_itself.empty ())
					{
						int __species_index = possibleModifierMatch[i][n2].first;
						string __comp_id = listOfMySpecies[__species_index]->getCompTypeId ();
						assert (!__comp_id.empty ());

						if (!itself.count (__species_itself)) 
							itself[__species_itself] = __comp_id;
						else if (itself[__species_itself] != __comp_id) {
							possible.erase (n1); break;
						}
					}
				}

				//	for products
				for (int n2= 0; n2 < listOfMyProducts.size (); n2++)
				{
					string __species_itself = listOfMyProducts[n2]->getCompTypeId ();
					if (!__species_itself.empty ())
					{
						string compLabel = listOfMyProducts[n2]->getCompartment ();
						if (!compConfig[n1].count(compLabel)) throw StrCacuException (
								"No compartment Label found!"
								);
						else 
						{
							int compIndex = compConfig[n1][compLabel];
							string __comp_id = listOfMyCompartments[compIndex]->getId ();
							assert (!__comp_id.empty ());

							if (!itself.count (__species_itself)) 
								itself[__species_itself] = __comp_id;
							else if (itself[__species_itself] != __comp_id) {
								possible.erase (n1); break;
							}
						}
					}
				}
			}

			if (possible.empty ()) continue;

			/**
			 * output result, it includes two components:
			 * (1) matching result of modifiers and reactants 
			 * (2) associated product compartment attribution
			 */

			for (int i=0; i < compConfig.size (); i++)
			{
				if (possible.count (i))
				{
					reactionMatch tmp = make_pair (
							possibleReactantMatch[i], 
							possibleModifierMatch[j]
							);
					map<string, int>& conf = compConfig[i];
					result.push_back (make_pair(tmp, conf));
				}
			}

			//	go to next pair of reactants and modifiers
		}
	}
	
	return result.size () > 0;
}

/**
 * Based on products templates and pattern matchings of
 * reactants and modifiers, new products by replacing 
 * substituent parts are generated and stored in productCandidates
 */

void reactionTemplate::createProductsFromTemplate (
		const vector<MySpecies*>& listOfMySpecies,
		const vector<MyCompartment*>& listOfMyCompartments,
		const reactionPairMatch& table,
		vector<MySpecies*>& products
		)
{

	//	configure 
	const map<string, int>& config = table.second;
	const speciesArrayMatch& __cand_reactants =  table.first.first;
	const speciesArrayMatch& __cand_modifiers =  table.first.second;

	/**
	 * core programme to generate products
	 */
	for (int i=0; i < listOfMyProducts.size (); i++)
	{
		MySpecies* __orig_p = listOfMyProducts[i];
		MySpecies* __spe_new_p = new MySpecies;
		
		//	set DB Label
		string __label_p = __orig_p->getDB_Label ();
		__spe_new_p->setDB_Label (__label_p);
		
		//	set compartment
		string __comp_p = __orig_p->getCompartment ();
		if (!config.count (__comp_p)) throw StrCacuException (
				"No map for compartment DB Label!"
				);
		else 
		{
			const MyCompartment* mycomp = 
				listOfMyCompartments[config.find (__comp_p)->second];
			__spe_new_p->setCompartment (mycomp->getId ());
		}

		for (int j=0; j< __orig_p->getNumOfChains(); j++)
		{
			Chain* __orig_c = __orig_p->getChain (j);
			Chain* __new_c = __spe_new_p->createChain ();

			for (int k=0; k < __orig_c->getNumOfParts (); k++)
			{
				Part* __orig_part = __orig_c->getPart (k);
				if (__orig_part->getPartCtg () == "substituent")
				{
					string subLabel = __orig_part->getPartLabel ();
					subsp destine = make_pair (__label_p, subLabel);

					//	read chain transfer table
					if (!transferTable.count (destine))
						throw StrCacuException ("Lack Info. for Substituent Transfer!");
					else
					{
						subsp source = transferTable[destine];

						MySpecies* found = NULL;
						bool isr = false;
						int localindex = -1;
						
						/**
						 * find species with Label source.first
						 * it must be a reactant or a modifier
						 */
						for (int i=0; i < listOfMyReactants.size (); i++)
						{
							MySpecies* species = listOfMyReactants[i];
							if (species->getDB_Label () == source.first) 
							{
								int index = __cand_reactants[i].first;
								found = listOfMySpecies[index];
								isr = true;
								localindex = i;
								break;
							}
						}

						if (!isr)
						{
							for (int i=0; i < listOfMyModifiers.size (); i++)
							{
								MySpecies* species = listOfMyModifiers[i];
								if (species->getDB_Label () == source.first)
								{
									int index = __cand_modifiers[i].first;
									found = listOfMySpecies[index];
									isr = false;
									localindex = i;
									break;
								}
							}
						}
						
						if (found == NULL) throw StrCacuException (
								"species Label NOT found!"
								);

						/**
						 * replace substituent-part 
						 */
						int chain_lst = -1;
						if (isr) chain_lst = __cand_reactants[localindex].second[j].second;
						else chain_lst = __cand_modifiers[localindex].second[j].second;

						cMatchType cmt;
						Chain* ck = found->getChain (chain_lst);
						if (isr) cmt = __cand_reactants[localindex].second[j].first;
						else cmt = __cand_modifiers[localindex].second[j].first;

						cMatchType::const_iterator cmtf = cmt.begin ();
						for (int cnt =0; cnt != k; cnt++) cmtf ++;

						for (int t = cmtf->first; t <= cmtf->second; t++)
						{
							Part* pk = ck->getPart (t);
							__new_c->createPart (pk);
						}
					}
				}
				else __new_c->createPart (__orig_part);
			}
		}

		for (int j=0; j < __orig_p->getNumOfTrees (); j++)
			__spe_new_p->createTree (__orig_p->getTree (j));

		products.push_back (__spe_new_p);
	}
}

bool isSameType (const string& lhs, const string& rhs)
{
	if (lhs.empty () && !rhs.empty ()) return false;
	if (!lhs.empty () && rhs.empty ()) return false;
	else return true;
}
