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
		const string& __math
		)
{
	/**
	 * validate math formula
	 * no products labels are allowed to appear
	 */
	for (int i=0; i < listOfMyProducts.size (); i++)
	{
		string label = listOfMyProducts[i]->getDB_Label ();

		if (__math.find (label) != string::npos) 
			throw StrCacuException (
					"Products labels are not allowed "
				    "to be used in math expression!  "
					);
	}
	math = __math;
}

bool reactionTemplate::findSpeciesMatch (
		const string& dbref, 
		const int& index,
		const vector<MySpecies*>& listOfMySpecies,
		const vector<MyCompartment*>& listOfMyCompartments,
		reactionArrayMatch& result	
		) 
{

	cout << "\n^_^		FIND SPECIES MATCH		^_^\n";

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
			
//            cout << "\nparent = " << __parent 
//                 << "  j = " << j 
//                 << "  entries = " << entries << endl;

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

	/**
	 *	find species matching for reactants 
	 */

	int perm_reactants = 1;	//	all permutations of reactants
	int perm_modifiers = 1;   //  all permutations of products
	speciesArrayMatch* reactant_sam = NULL;
    speciesArrayMatch* modifier_sam = NULL;

	//	find reactants match
	if (listOfMyReactants.size () > 0)
	{
		bool fail2match = false; 
		reactant_sam = new speciesArrayMatch [listOfMyReactants.size ()]; 

		for (int i=0; i < listOfMyReactants.size (); i++)
		{
			MySpecies* tmReactant = listOfMyReactants[i];
			if (tmReactant->getDB_ref () == dbref)
			{
				MySpecies* currSpe = listOfMySpecies[index];
				bool same = isSameType (
						currSpe->getCompTypeId (), 
						tmReactant->getCompTypeId ()
						);

				cMatchsArray trym;
				if (same && currSpe->match (tmReactant, trym))
				{
					for (int k=0; k < trym.size (); k++)
						reactant_sam[i].push_back (make_pair (index, trym[k]));
					perm_reactants *= reactant_sam[i].size ();
				}
				else {fail2match = true; break;}
			}
			else
			{
				for (int j=0; j <= index; j++)
				{
					MySpecies* prevSpe = listOfMySpecies[j];
					bool same = isSameType (
							prevSpe->getCompTypeId (), 
							tmReactant->getCompTypeId ()
							);

					cMatchsArray trym;
					if (same && prevSpe->match (tmReactant, trym))
					{
						for (int k=0; k < trym.size (); k++)
							reactant_sam[i].push_back (make_pair (j, trym[k]));
					}
				}

				if (reactant_sam[i].empty ()) {fail2match = true; break;}
				else perm_reactants *= reactant_sam[i].size ();
			}
		}

		//	no reactant match
		if (fail2match) return false;
		else cout << "\nNumber of Matchings of Reactant TEMPLATEs = " << perm_reactants << endl;
	}

	//	find modifiers match
	if (listOfMyModifiers.size () > 0)
	{
		bool fail2match = false; 
		modifier_sam = new speciesArrayMatch [listOfMyModifiers.size ()]; 
	
		for (int i=0; i < listOfMyModifiers.size (); i++)
		{
			MySpecies* tmModifier = listOfMyModifiers[i];
			if (tmModifier->getDB_ref () == dbref)
			{
				MySpecies* currSpe = listOfMySpecies[index];
				bool same = isSameType (
						currSpe->getCompTypeId (), 
						tmModifier->getCompTypeId ()
						);

				cMatchsArray trym;
				if (same && currSpe->match (tmModifier, trym)) 
				{
					for (int k=0; k < trym.size (); k++)
						modifier_sam[i].push_back (make_pair (index, trym[k]));
					perm_modifiers *= modifier_sam[i].size ();
				}
				else {fail2match = true; break;} 
			}
			else
			{
				for (int j=0; j <= index; j++)
				{
					MySpecies* prevSpe = listOfMySpecies[j];
					bool same = isSameType (
							prevSpe->getCompTypeId (), 
							tmModifier->getCompTypeId ()
							);

					cMatchsArray trym;
					if (same && prevSpe->match (tmModifier, trym))
					{
						for (int k=0; k < trym.size (); k++)
							modifier_sam[i].push_back (make_pair (j, trym[k]));
					}
				}

				if (modifier_sam[i].empty ()) {fail2match = true; break;}
				else perm_modifiers *= modifier_sam[i].size ();
			}
		}

		if (fail2match) return false;
		else cout << "\nNumber of Matchings of Reactant TEMPLATEs = " << perm_modifiers << endl;
	}

	/**
	 * permutation to find all possible combinations
	 */

	vector<speciesArrayMatch> possibleReactantMatch; 
	vector<speciesArrayMatch> possibleModifierMatch;

	for (int i =0; i < perm_reactants; i++)
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

	for (int i =0; i < perm_modifiers; i++)
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

	//	free memory
	if (reactant_sam != NULL) delete [] reactant_sam;
	if (modifier_sam != NULL) delete [] modifier_sam;

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
			/**
			 * COMPARTMENT CONSTRAINTS
			 */

			//	find all possible compartment configuration
			set<int> possible;

			//	reactant constraints
			if (listOfMyReactants.size () > 0)
			{
				for (int n1 = 0; n1 < compConfig.size (); n1++)
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
			}

			//	modifier constraints
			if (listOfMyModifiers.size () > 0)
			{
				for (int n1 = 0; n1 < compConfig.size (); n1++)
				{
					if (!possible.count (n1)) continue;

					bool fail = false;
					for (int n2=0; n2 < possibleModifierMatch[j].size (); n2++)
					{
						//	parameter about template spcies
						string __compLabel_tm = listOfMyModifiers[n2]->getCompartment ();
						string __compid_tm;

						//	LIAOCHEN MARK ... TAKE CARE!
						assert (n1 < compConfig.size ());
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
			}

			//	compartment-type species constraints
			for (int n1=0; n1 < compConfig.size (); n1++)
			{
				if (!possible.count (n1)) continue;

				map<string, int> itself;

				//	for reactants
				if (listOfMyReactants.size () > 0)
				{
					for (int n2 =0; n2 < possibleReactantMatch[i].size (); n2++)
					{
						string __species_itself = listOfMyReactants[n2]->getCompTypeId ();
						if (!__species_itself.empty ())
						{
							int __species_index = possibleReactantMatch[i][n2].first;
							if (!itself.count (__species_itself)) 
								itself[__species_itself] = __species_index;
							else if (itself[__species_itself] != __species_index) {
								possible.erase (n1); break;
							}
						}
					}
				}

				//	for modifiers
				if (listOfMyModifiers.size () > 0)
				{
					for (int n2 =0; n2 < possibleModifierMatch[i].size (); n2++)
					{
						string __species_itself = listOfMyModifiers[n2]->getCompTypeId ();
						if (!__species_itself.empty ())
						{
							int __species_index = possibleModifierMatch[i][n2].first;
							if (!itself.count (__species_itself)) 
								itself[__species_itself] = __species_index;
							else if (itself[__species_itself] != __species_index) {
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

			for (int n1=0; n1 < compConfig.size (); n1++)
			{
				if (possible.count (n1))
				{
					reactionMatch tmp = make_pair (
							possibleReactantMatch[i], 
							possibleModifierMatch[j]
							);
					map<string, int>& conf = compConfig[n1];
					result.push_back (make_pair(tmp, conf));

					/**
					 * it is important to check tmp
					 */
					cout << "\n^_^		REACTANTS	:	^_^\n";
					if (listOfMyReactants.size () > 0)
					{
						cout << "\nspeciesArrayMatch: reactant num = " 
							<< possibleReactantMatch[i].size () << endl;
						for (int cnt = 0; cnt < possibleReactantMatch[i].size (); cnt++)
						{
							cout << "\nreactant : " << cnt;
							cout << "\nspecies matched in the system : " 
								<< possibleReactantMatch[i][cnt].first;
							cMatchsType2& details = possibleReactantMatch[i][cnt].second;
							cout << "\nchains of reactant = " << details.size ();
							for (int cnt2 = 0; cnt2 < details.size (); cnt2++)
							{
								cout << "\nmatched chain of species in reality: " << 
									details[cnt2].second;
								cout << "\n<--	details	-->";
								cMatchType& __match = details[cnt2].first;

								cout << "\nnumber of parts to be matched:	" 
									<< __match.size () << endl;
								cMatchType::iterator first = __match.begin ();
								for (; first != __match.end (); first++)
								{
									cout << "(" << first->first << ", " << first->second << ") " << endl; 
								}	
							}
						}	
					}

					cout << "\n^_^		MODIFIERS	:	^_^\n";
					if (listOfMyModifiers.size () > 0)
					{
						cout << "\nspeciesArrayMatch: modifier num = " 
							<< possibleModifierMatch[j].size () << endl;
						for (int cnt = 0; cnt < possibleModifierMatch[j].size (); cnt++)
						{
							cout << "\nmodifier : " << cnt;
							listOfMyModifiers[cnt]->Output ();

							cout << "\nspecies matched in the system : " 
								<< possibleModifierMatch[j][cnt].first;
							listOfMySpecies[possibleModifierMatch[j][cnt].first]->Output ();

							cMatchsType2& details = possibleModifierMatch[j][cnt].second;
							cout << "\nchains of modifier = " << details.size () 
								<< " should be : " << listOfMyModifiers[cnt]->getNumOfChains () << endl;
							for (int cnt2 = 0; cnt2 < details.size (); cnt2++)
							{
								cout << "\nmatched chain of species in reality: " << 
									details[cnt2].second;
								cout << "\n\n<-------			details			-------->";
								cMatchType& __match = details[cnt2].first;

								cout << "\nnumber of parts to be matched:	" 
									<< __match.size () << endl;
								cMatchType::iterator first = __match.begin ();
								for (; first != __match.end (); first++)
								{
									cout << "(" << first->first << ", " << first->second << ") "; 
								}	
							}
						}	
					}

					//	check over
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
	cout << "\n<--	create products from template	--	..	-->" << endl;

	//	configure 
	const map<string, int>& config = table.second;
	const speciesArrayMatch& __cand_reactants =  table.first.first;
	const speciesArrayMatch& __cand_modifiers =  table.first.second;

	if (__cand_reactants.size () != listOfMyReactants.size ()) 
		throw StrCacuException ("Empty reactant candidates to generate products!");

	if (__cand_modifiers.size () != listOfMyModifiers.size ()) 
		throw StrCacuException ("Empty modifier candidates to generate products!");

	/**
	 * core programme to generate products
	 */
	for (int i=0; i < listOfMyProducts.size (); i++)
	{
		cout << "\nproducts template i = " << i;

		MySpecies* __orig_p = listOfMyProducts[i];	//	template product
		MySpecies* __spe_new_p = new MySpecies;	//	product new body

		__orig_p->Output ();
		
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

		//	set compTypeId
		string __comp_tid = __orig_p->getCompTypeId ();
		if (!__comp_tid.empty ())
		{
			if (!config.count (__comp_tid)) throw StrCacuException (
					"No map for compartment DB Label!"
					);
			else 
			{
				const MyCompartment* mycomp = 
					listOfMyCompartments[config.find (__comp_tid)->second];
				__spe_new_p->setCompTypeId (mycomp->getId ());
			}
		}

		/**
		 * copy chains
		 */	
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
					//	transferTabel [to] = from
					if (!transferTable.count (destine))
					{
						cout << "\ndestine	:	(" 
							 << destine.first 
							 << ", " 
							 << destine.second 
							 << ")" 
							 << endl;
						throw StrCacuException (
								"Lack Info. for Substituent Transfer!"
								);
					}

//                    cout << "\nj = " << j << "k = " << k << endl;
					subsp source = transferTable[destine];
					

					//	ATTENTION!
					//
					//	source.first --> speciesLabel of reactant/modifier
					//	source.second --> corresponded partLabel in reactant/modifier
					//	
					//
					//	we need to posit the chain number and part number 
					//	of source.second in source.first

					MySpecies* found = NULL;
					bool isr = false;

					int index_s, index_c, index_p;
					index_s = index_c = index_p = -1;

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

							index_s = i;
							for (int j=0; j < species->getNumOfChains (); j++)
							{
								Chain* c = species->getChain (j);
								index_p = c->getPartIndex (source.second);
								if (index_p >= 0) {index_c = j; break;}
							}

							assert (index_c >=0); assert (index_p >= 0);

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

								index_s = i;
								for (int j=0; j < species->getNumOfChains (); j++)
								{
									Chain* c = species->getChain (j);
									index_p = c->getPartIndex (source.second);
									if (index_p >= 0) {index_c = j; break;}
								}

								assert (index_c >=0); assert (index_p >= 0);

								break;
							}
						}
					}

					if (found == NULL) throw StrCacuException ("species Label NOT found!");

					/*
					cout << "\nsource.first = " << source.first
					     << "  source.second = " << source.second 
					     << "\nindex_s = " << index_s 
						 << "  index_c = " << index_c
						 << "  index_p = " << index_p << endl;
					*/

					/**
					 * replace substituent-part 
					 */
					int chain_lst = -1;
//                    cout << "\ncand size = " << __cand_reactants.size () << endl;
//                    if (isr) cout << "\nchain size = " << __cand_reactants[index_s].second.size ();

					//	chain_lst is the matching of chain number of species found for chain j
					if (isr) chain_lst = __cand_reactants[index_s].second[index_c].second;
					else chain_lst = __cand_modifiers[index_s].second[index_c].second;

//                    cout << "\nchain_lst = " << chain_lst << endl;

					cMatchType cmt;
					Chain* ck = found->getChain (chain_lst);
					assert (ck != NULL);

					if (isr) cmt = __cand_reactants[index_s].second[index_c].first;
					else cmt = __cand_modifiers[index_s].second[index_c].first;

					cMatchType::const_iterator cmtf = cmt.begin ();
					for (int cnt =0; cnt != index_p; cnt++) {
						cmtf ++; assert (cmtf != cmt.end ());
					}

					for (int t = cmtf->first; t <= cmtf->second; t++)
					{
						Part* pk = ck->getPart (t);
						assert (pk != NULL);

						Part* __new_p = __new_c->createPart (pk);

						//	change its part label
						string prefix;
						if (isr) string prefix = "__MoDeL_REACTANT_CXX";
						else string prefix = "__MoDeL_MODIFIER_CXX";

						ostringstream oss;
						oss << prefix << index_s << "::" 
							<< __new_p->getPartLabel ();
						__new_p->setPartLabel (oss.str ());
					}
				}
				else
				{
					__new_c->createPart (__orig_part);
					cout << "\n__new_c->createPart = " 
						 << __orig_part->getPartRef () << " "
						 << __orig_part->getIsBinded ()
						 << endl;
				}
			}
		}

		for (int j=0; j < __orig_p->getNumOfTrees (); j++)
			__spe_new_p->createTree (__orig_p->getTree (j));

		products.push_back (__spe_new_p);
	}
}

void reactionTemplate::addProductPrefix (const string& prefix) {
	for (int i=0; i<listOfMyProducts.size (); i++) listOfMyProducts[i]->addPrefix (prefix);
}

bool isSameType (const string& lhs, const string& rhs)
{
	if (lhs.empty () && !rhs.empty ()) return false;
	if (!lhs.empty () && rhs.empty ()) return false;
	else return true;
}

bool reactionTemplate::handle_constraints (
		const ListOfParameters* globalpara
		)
{
	vector<constraintType>::iterator 
		begin = listOfConstraints.begin ();

	for (int i=0; i < listOfConstraints.size (); i++)
	{
		vector<string>& vars = listOfConstraints[i].first;
		string formula = listOfConstraints[i].second;

		// temp vars	
		string expression;

		//	drop this constraint if quantities are not constant
		//	however, unrecognized vars would cause programme to terminate
		bool drop = false;	

		//	find values of vars
		for (int j=0; j < vars.size (); j++)
		{
			const string& varid = vars[j];
			
			const Parameter* para1 = globalpara->get (varid);
			if (para1 != NULL)
			{
				if (para1->getConstant ())
				{
					ostringstream oss;
					oss << varid 
						<< "=" 
						<< para1->getValue () 
						<< ",";
					expression += oss.str ();
					continue;
				}
				else {drop = true; break;}
			}

			const Parameter* para2 = getParameter (varid);
			if (para2 != NULL)
			{
				ostringstream oss;
				oss << varid 
					<< "=" 
					<< para2->getValue () 
					<< ",";
				expression += oss.str ();
				continue;
			}

			drop = true; break;
		}

		if (!drop && !expression.empty ()) 
		{
			expression.substr (0, expression.size ()-1);
			if (cacu_string_exp (expression.c_str (), formula.c_str ()) == 0) return false;
		}
	}

	return true;
}

void reactionTemplate::OutputProducts ()
{
	cout << "\nTESTING...	...	..." << endl;
	for (int i=0; i < listOfMyProducts.size (); i++)
		listOfMyProducts[i]->Output ();
}
