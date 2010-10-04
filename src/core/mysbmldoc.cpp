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
	//
	//	algorithm:
	//	for two compartment-type species, in addition
	//	to its species strucutre, we also need to compare
	//	their corresponded compartment
	//
	MySpecies* myspe = listOfMySpecies.back ();
	string compid = myspe->getCompartment ();
	string ccid = myspe->getCCid ();

	for (int i=0; i < listOfMySpecies.size ()-1; i++)
	{
		MySpecies* myspe1 = listOfMySpecies[i];
		string compid1 = myspe1->getCompartment ();
		string ccid1 = myspe1->getCCid ();

		if (!myspe1->equal (myspe)) continue;
		else if (compid != compid1) continue; 
		else if (ccid != ccid1) continue;
		else
		{
			listOfMySpecies.pop_back ();
			delete myspe;
			return myspe1;
		}
	}
	return myspe;
}

string MySBMLDocument::genSbmlId (
		const int& t
		) const
{
	ostringstream oss;
	switch (t)
	{
		case 0: oss << "sPecIes" << listOfMySpecies.size ();
				break;
		case 1: oss << "rEactIon" << listOfMyReactions.size ();
				break;
	}
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

		cout << "\n************* SPECIES	" << i << "	****************\n";
		s->Output ();	

		//a set to store species id that has been used
		set<string> speciesUsed;

		for (int j =0; j < s->getNumOfChains (); j++)
		{
			Chain* c = s->getChain (j);
			for (int k=0; k < c->getNumOfParts (); k++)
			{
				Part* p = c->getPart (k);

				//	search transcription reactions
				searchTranscriptionReactions (i, j, k, dbreader);

				//	search translation reactions
				searchTranslationReactions (i, j, k, dbreader);

				//	read species containing this part 
				string speciesLinkPath =
					"/MoDeL/part/" +
					p->getPartCategory () + 
					"/listOfReferencedSpecies/"
					"referencedSpecies";
				string doc_1 = p->getDbId ();

				int numOfSpeciesLinks = 
					dbreader.get_node_element_num (
							PART, &doc_1, &speciesLinkPath
							);

				for (int t=1; t <= numOfSpeciesLinks; t++)
				{
					cout << "\nHandling the First Referenced Species...";

					string speciesReference, partType;
					
					cout << "\ndb = " << p->getDbId () << endl;

					dbreader.readSpeciesLink (
							PART, p->getDbId (),speciesLinkPath, 
							t, speciesReference, partType
							);

					//	check if this species has been searched
					if (speciesUsed.count (speciesReference)) continue;
					else speciesUsed.insert (speciesReference);

					//	partType must be consistant
					if (!partType.empty () && 
							partType != p->getPartType ()) continue;

					//
					//	read searched species
					//

					cout << "\nReading Species...";

					MySpecies* sLink = new MySpecies;
					sLink->setDbId (speciesReference);  
					dbreader.read_cnModel (
							sLink, SPECIES, speciesReference,
							"/MoDeL/species", true
							);
//                    cout << "\nspeciesReference = " <<
//                        speciesReference << endl;

					cout << "\n=============Species Referred...=================\n";
					sLink->Output ();

					//
					//  is this species template match?
					//
					vector<MySpecies::cMatchsType2> trym;
					if (!s->match (sLink, trym)) 
					{
						cout << "\nDoes not MATCH! Continue to NEXT...";
						terminate ();
						continue;
					}
					else cout << "\nMATCH! Continue...";


					//
					//  read reaction Links
					//
					string reactionLinkPath =
						"/MoDeL/species/"  
						"listOfReferencedReactions/"
						"referencedReaction";

					int numOfReactionLinks = dbreader.get_node_element_num (
							SPECIES, &speciesReference, &reactionLinkPath
							);

					for (int r=1; r <= numOfReactionLinks; r++)
					{
						string reactionReference, speciesRole;
						dbreader.readReactionLink (
								SPECIES, speciesReference, reactionLinkPath, 
								r, reactionReference, speciesRole
								);
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

	cout << "\n=========================================================";
	cout << "\n	 COPY MYOBJECTS TO SBML COMPONENTS... 		";
	cout << "\n=========================================================";
	cout <<	endl;

	Model* m = getModel ();

	for (int i=0; i < listOfMySpecies.size (); i++)
	{
		int operation = m->addSpecies (listOfMySpecies[i]);
		if (operation == LIBSBML_LEVEL_MISMATCH)
			throw StrCacuException (
					"Add Species to Model: Level Mismatch!"
					);
		if (operation == LIBSBML_VERSION_MISMATCH)
			throw StrCacuException (
					"Add Species to Model: Version Mismatch!"
					);
		if (operation == LIBSBML_DUPLICATE_OBJECT_ID)
			throw StrCacuException (
					"Add Species to Model: Duplicate Object Id!"
					);
		if (operation == LIBSBML_OPERATION_FAILED)
			throw StrCacuException (
					"Add Species to Model: Failed!"
					);
	}

	for (int i=0; i < listOfMyCompartments.size (); i++)
	{
		MyCompartment* comp = listOfMyCompartments[i];
		if (comp->getOutside () == "ROOT") 
		{
			int operation = comp->unsetOutside ();
			if (operation == LIBSBML_OPERATION_FAILED)
				throw StrCacuException (
						"Operation Failed: Unable to unset Outside"
						" attribute of compartment!"
						);
		}
		int operation = m->addCompartment (comp);
		if (operation == LIBSBML_LEVEL_MISMATCH)
			throw StrCacuException (
					"Add Compartment to Model: Level Mismatch!"
					);
		if (operation == LIBSBML_VERSION_MISMATCH)
			throw StrCacuException (
					"Add Compartment to Model: Version Mismatch!"
					);
		if (operation == LIBSBML_DUPLICATE_OBJECT_ID)
			throw StrCacuException (
					"Add Compartment to Model: Duplicate Object Id!"
					);
		if (operation == LIBSBML_OPERATION_FAILED)
			throw StrCacuException (
					"Add Compartment to Model: Failed!"
					);
	}

	for (int i=0; i < listOfMyReactions.size (); i++)
	{
		int operation = m->addReaction (listOfMyReactions[i]);

		if (operation == LIBSBML_LEVEL_MISMATCH)
			throw StrCacuException (
					"Add Reaction to Model: Level Mismatch!"
					);
		if (operation == LIBSBML_VERSION_MISMATCH)
			throw StrCacuException (
					"Add Reaction to Model: Version Mismatch!"
					);
		if (operation == LIBSBML_DUPLICATE_OBJECT_ID)
			throw StrCacuException (
					"Add Reaction to Model: Duplicate Object Id!"
					);
		if (operation == LIBSBML_OPERATION_FAILED)
			throw StrCacuException (
					"Add Reaction to Model: Failed!"
					);
	}

	cout << "\nREAL RULEs Number: " << m->getNumRules () << endl;
	cout << "\nREAL FUNCTIONDEFINITIONs Number: " << m->getNumFunctionDefinitions () << endl;
	cout << "\nREAL PARAMETERs Number: " << m->getNumParameters () << endl;
	cout << "\nREAL UNITs Number: " << m->getNumUnitDefinitions () << endl;
	cout << "\nREAL SPECIES Number: " << m->getNumSpecies () << endl;
	cout << "\nREAL COMPARTMENTs Number: " << m->getNumCompartments () << endl;
	cout << "\nREAL REACTIONs Number: " << m->getNumReactions () << endl;
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

	//	create a reaction template object
	reactionTemplate* RT = new reactionTemplate;
	dbreader.readReactionTemplate (RT, doc, direction); 

	//	handle constraints
	for (int i=0; i < RT->listOfConstraints.size (); i++)
	{
		vector<string> vars = RT->listOfConstraints[i].first;
		string formula = RT->listOfConstraints[i].second;

		string conditions;
		Model* m = getModel ();

		//	find values of vars
		for (int j=0; j < vars.size (); j++)
		{
			string varid = vars[j];

			//	(1) search global parameters
			Parameter* para = m->getParameter (varid);		
			if (para != NULL)
			{
				if (!para->getConstant ())
					throw StrCacuException (
							"Constant parameter is needed in" 
							"calculation of constraint expression!"
							);
				else 
				{
					ostringstream oss;
					oss << varid << "=" << para->getValue () << ",";
					conditions += oss.str ();
					continue;
				}
			}

			//	(2) search local parameters
			para = RT->getParameter (varid);
			if (para != NULL)
			{
				ostringstream oss;
				oss << varid << "=" << para->getValue () << ",";
				conditions += oss.str ();
				continue;
			}

			//	not found
			throw StrCacuException (
					string ("Unrecognized parameter id: ")
					+ varid + "!"
					);
		}
		conditions.substr (0, conditions.size ()-1);

		if (cacu_string_exp (conditions.c_str (), formula.c_str ()) == 0)
		{
			delete RT;
			return;
		}
	}
	

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
		//	new reaction
		MyReaction* myreaction = new MyReaction;
		myreaction->setId (genSbmlId (1));
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

void MySBMLDocument::searchTranscriptionReactions (
		const int& i,
		const int& j,
		const int& k,
		readDataBase& dbreader
		)
{
	MySpecies* s = listOfMySpecies[i];
	Chain* c = s->getChain (j);
	Part* p = c->getPart (k);
	string ptype = p->getPartType ();
	bool isvalidseq = ((ptype == "ForwardDNA") || (ptype == "ReverseDNA"));
	if (!isvalidseq) return;

	//	check if p is a promoter
	string units, name;
	double value;

	//	if p is a forward element, query its forward attribute
	//	if p is a reverse element, query its reverse attribute
	
	//	===============================
	//	forward transcription reaction
	//	===============================
	string PE_fw ("forwardPromoterEfficiency");
	if (ptype == "ReverseDNA") PE_fw = "reversePromoterEfficiency";
	
	string db_comp = getMyCompartment (s->getCompartment ())->getDbId ();
	dbreader.readConditionalParameter (
			PART, p->getPartCategory (), p->getDbId (),
			PE_fw, db_comp, value, units, name
			);

	if (value <0) throw StrCacuException (
			"Invalid parameter value: forward/reverse PromoterEfficiency!"
			);

	if (value > TINY)
	{
		int numofparts = c->getNumOfParts ();
		if (k < numofparts-1)
		{
			string termUnits, termName;
			double termeff;

			int ci = k;
			double k_tc = value;	//k_tc

			do
			{
				if (++ci != numofparts)
				{
					p = c->getPart (ci);
					ptype = p->getPartType ();
					isvalidseq = (ptype == "ForwardDNA" || ptype == "ReverseDNA");
					if (isvalidseq)
					{
						string TE_fw ("forwardTerminatorEfficiency");
						if (ptype == "ReverseDNA") TE_fw = "reverseTerminatorEfficiency";
						db_comp = getMyCompartment (s->getCompartment ())->getDbId ();
						dbreader.readConditionalParameter (
								PART, p->getPartCategory (), p->getDbId (),
								TE_fw, db_comp, termeff, termUnits, termName
								);
						if (termeff <0 || termeff > 1) throw StrCacuException (
								"Invalid parameter value: forward/reverse TerminatorEfficiency!"
								);
					}
				}
				else termeff = 1;

				if (termeff > TINY || !isvalidseq)
				{
					//	the biobrick next to promoter is not a valid sequence
					if (!isvalidseq && ci == k + 1) break;	

					MySpecies* mrna = new MySpecies;

					if (mrna->setId (genSbmlId (0)) 
							== LIBSBML_INVALID_ATTRIBUTE_VALUE)
						throw StrCacuException (
								"Transcription: Invalid Attribute Value: id!"
								);
					mrna->setName ("mrna");
					mrna->setCompartment (s->getCompartment ());
					mrna->setInitialAmount (0.0);

					Chain* mrna_chain = mrna->createChain ();
					assert (k+1 <= ci-1);

					for (int j=k+1; j < ci; j++)
					{
						Part* tm = c->getPart (j);
						Part* mrna_part = mrna_chain->createPart (tm);

						if (tm->getPartType () == "ForwardDNA")
							mrna_part->setPartType ("ForwardRNA");
						else if (tm->getPartType () == "ReverseDNA")
							mrna_part->setPartType ("ReverseRNA");
						else throw StrCacuException (
								"Invalid Transcriptional Unit!"
								);
					}
					mrna->rearrange ();

					//	check existance of myspecies
					listOfMySpecies.push_back (mrna);
					mrna = validateBackSpecies ();
//                    cout << "\nmrna = ";
//                    mrna->Output ();

					//	record a reaction
					MyReaction* transcription = new MyReaction;
					transcription->setId (genSbmlId (1));
					transcription->setName ("transcription");
					transcription->setReversible (false);

					transcription->addSpecialReaction (s, mrna, "k_tc", name, k_tc, units);
					listOfMyReactions.push_back (transcription);

					if (!isvalidseq) break;
					if (fabs (1-termeff) < TINY) break;
					else k_tc *= 1-termeff;
				}

			}	while (1);
		}
	}

	//	==============================
	//	reverse transcription reaction
	//	==============================
	
	if (!units.empty ()) units.clear ();
	if (!name.empty ()) name.clear ();

	string PE_rev ("reversePromoterEfficiency");
	if (ptype == "ReverseDNA") PE_rev = "forwardPromoterEfficiency";
	db_comp = getMyCompartment (s->getCompartment ())->getDbId ();
	dbreader.readConditionalParameter (
			PART, p->getPartCategory (), p->getDbId (),
			PE_rev, db_comp, value, units, name
			);
	if (value <0) throw StrCacuException (
			"Invalid parameter value: reverse/forward PromoterEfficiency!"
			);

	if (value > TINY)
	{
		int numofparts = c->getNumOfParts ();
		if (k > 0)
		{
			string termUnits, termName;
			double termeff;

			int ci = k;
			double k_tc = value;	//k_tc

			do
			{
				if (--ci != 0)
				{
					p = c->getPart (ci);
					ptype = p->getPartType ();
					isvalidseq = (ptype == "ForwardDNA" || ptype == "ReverseDNA");
					if (isvalidseq)
					{
						string TE_rev ("reverseTerminatorEfficiency");
						if (ptype == "ReverseDNA") TE_rev = "forwardTerminatorEfficiency";
						db_comp = getMyCompartment (s->getCompartment ())->getDbId ();
						dbreader.readConditionalParameter (
								PART, p->getPartCategory (), p->getDbId (),
								TE_rev, db_comp, termeff, termUnits, termName
								);
						if (termeff <0 || termeff > 1) throw StrCacuException (
								"Invalid parameter value: reverse/forward TerminatorEfficiency!"
								);
					}
				}
				else termeff = 1;

				if (termeff > TINY || !isvalidseq)
				{
					//	the biobrick next to promoter is not a valid sequence
					if (!isvalidseq && ci == k-1) break;	

					MySpecies* mrna = new MySpecies;

					if (mrna->setId (genSbmlId (0)) 
							== LIBSBML_INVALID_ATTRIBUTE_VALUE)
						throw StrCacuException (
								"Transcription: Invalid Attribute Value: id!"
								);
					mrna->setName ("mrna");
					mrna->setCompartment (s->getCompartment ());
					mrna->setInitialAmount (0.0);

					Chain* mrna_chain = mrna->createChain ();
					assert (k-1 >= ci+1);

					for (int j=k-1; j > ci; j--)
					{
						Part* tm = c->getPart (j);
						Part* mrna_part = mrna_chain->createPart (tm);

						if (tm->getPartType () == "ForwardDNA")
							mrna_part->setPartType ("ReverseRNA");
						else if (tm->getPartType () == "ReverseDNA")
							mrna_part->setPartType ("ForwardRNA");
						else throw StrCacuException (
								"Invalid Transcriptional Unit!"
								);
					}
					mrna->rearrange ();

					//	check existance of myspecies
					listOfMySpecies.push_back (mrna);
					mrna = validateBackSpecies ();

					//	record a reaction
					MyReaction* transcription = new MyReaction;
					transcription->setId (genSbmlId (1));
					transcription->setName ("transcription");
					transcription->setReversible (false);

					transcription->addSpecialReaction (s, mrna, "k_tc", name, k_tc, units);
					listOfMyReactions.push_back (transcription);

					if (!isvalidseq) break;
					if (fabs (1-termeff) < TINY) break;
					else k_tc *= 1-termeff;
				}

			}	while(1);

		} //!k>0
	}

	return;
}

void MySBMLDocument::searchTranslationReactions (
		const int& i,
		const int& j,
		const int& k,
		readDataBase& dbreader
		)
{
	MySpecies* s = listOfMySpecies[i];
	Chain* c = s->getChain (j);
	Part* p = c->getPart (k);
	string ptype = p->getPartType ();
	bool isvalidseq = (ptype == "ForwardRNA" || ptype == "ReverseRNA");
	if (!isvalidseq) return;

	//	check if p is a promoter
	string units, name;
	double value;

	//	forward transcription reaction
	string RE_fw ("forwardRbsEfficiency");
	if (ptype == "ReverseRNA") RE_fw = "reverseRbsEfficiency";
	string db_comp = getMyCompartment (s->getCompartment ())->getDbId ();
	dbreader.readConditionalParameter (
			PART, p->getPartCategory (), p->getDbId (),
			RE_fw, db_comp, value, units, name
			);

	if (value <0) throw StrCacuException (
			"Invalid parameter value: forward/reverse RbsEfficiency!"
			);

	if (value > TINY)
	{
		int numofparts = c->getNumOfParts ();
		if (k < numofparts-1)
		{
			string codonUnits, codonName;
			double codonEff;

			int ci = k+1;
			p = c->getPart (ci);
			string ptype = p->getPartType ();
			bool isvalidseq = (ptype == "ForwardRNA" || ptype == "ReverseRNA");
			if (!isvalidseq) return;

			string StartC_fw ("forwardStartCodonEfficiency");
			if (ptype == "ReverseRNA") 
				StartC_fw = "reverseStartCodonEfficiency";
			db_comp = getMyCompartment (s->getCompartment ())->getDbId ();
			dbreader.readConditionalParameter (
					PART, p->getPartCategory (), p->getDbId (),
					StartC_fw, db_comp, codonEff, codonUnits, codonName
					);
			if (codonEff <0 || codonEff > 1) throw StrCacuException (
					"Invalid parameter value: forward/reverse StartCodonEfficiency!"
					);

			if (fabs (1.0-codonEff) > TINY) return;
			else
			{
				do
				{
					if (ci != numofparts)
					{
						p = c->getPart (ci);
						ptype = p->getPartType ();
						isvalidseq = (ptype == "ForwardRNA" || ptype == "ReverseRNA");
						if (isvalidseq)
						{
							string StopC_fw ("forwardStopCodonEfficiency");
							if (ptype == "ReverseRNA") StopC_fw = "reverseStopCodonEfficiency";
							db_comp = getMyCompartment (s->getCompartment ())->getDbId ();
							dbreader.readConditionalParameter (
									PART, p->getPartCategory (), p->getDbId (),
									StopC_fw, db_comp, codonEff, codonUnits, codonName
									);
							if (codonEff <0 || codonEff > 1) throw StrCacuException (
									"Invalid parameter value: forward/reverse StopCodonEfficiency!"
									);
						}
					}
					else codonEff = 1;

					if (codonEff > TINY || !isvalidseq)
					{
						//	the biobrick next to rbs is not a valid sequence
						MySpecies* prot = new MySpecies;

						if (prot->setId (genSbmlId (0)) 
								== LIBSBML_INVALID_ATTRIBUTE_VALUE)
							throw StrCacuException (
									"Translation: Invalid Attribute Value: id!"
									);
						prot->setName ("prot");
						prot->setCompartment (s->getCompartment ());
						prot->setInitialAmount (0.0);

						Chain* prot_chain = prot->createChain ();
						assert (k+1 <= ci);

						for (int j=k+1; j <= ci; j++)
						{
							Part* tm = c->getPart (j);
							Part* prot_part = prot_chain->createPart (tm);

							if (tm->getPartType () == "ForwardRNA")
								prot_part->setPartType ("ForwardProtein");
							else if (tm->getPartType () == "ReverseRNA")
								prot_part->setPartType ("ReverseProtein");
							else throw StrCacuException (
									"Invalid Translation Unit!"
									);
						}
						prot->rearrange ();

						//	check existance of myspecies
						listOfMySpecies.push_back (prot);
						prot = validateBackSpecies ();

						//	record a reaction
						MyReaction* translation = new MyReaction;
						translation->setId (genSbmlId (1));
						translation->setName ("translation");
						translation->setReversible (false);

						translation->addSpecialReaction (s, prot, "k_tl", name, value, units);
						listOfMyReactions.push_back (translation);

						break;
					}

					ci++;
				}	while (1);
			}
		}
	}

	return;
}
