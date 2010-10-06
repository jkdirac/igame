#include "mysbmldoc.h"

MySBMLDocument::MySBMLDocument ():
	SBMLDocument (2,4)
{}

MySBMLDocument::~MySBMLDocument ()
{
	for (int i=0; i < listOfMySpecies.size (); i++)
		delete listOfMySpecies[i];
	for (int i=0; i < listOfMyCompartments.size (); i++)
		delete listOfMyCompartments[i];
	for (int i=0; i < listOfMyReactions.size (); i++)
		delete listOfMyReactions[i];
}

//	make sure species added has never existed before
void MySBMLDocument::addMySpecies (MySpecies* s) 
{
	listOfMySpecies.push_back (s);
	MyCompartment* c = getMyCompartment (
			s->getCompartment ()
			);
	if (c == NULL) throw StrCacuException (
			"No compartment existed in compartment list"
			" for given species!"
			);
	else c->addMySpeciesIn (s);
}

void MySBMLDocument::addMyCompartment (MyCompartment* c) 
{
	listOfMyCompartments.push_back (c);
}

void MySBMLDocument::addMyCompartmentChildren ()
{
	for (int i=0; i < listOfMyCompartments.size (); i++)
	{
		MyCompartment* child = listOfMyCompartments[i];
		if (child->getOutside () != "ROOT")
		{
			MyCompartment* parent = getMyCompartment (child->getOutside ());
			if (parent != NULL) parent->addMyCompartmentIn (child);
			else throw StrCacuException (
					"No compartment existed in compartment list"
					" for given compartment!"
					);
		}
	}
}

void MySBMLDocument::addMyReaction (MyReaction* r) {
	listOfMyReactions.push_back (r);
}

MySpecies* MySBMLDocument::createMySpecies ()
{
	MySpecies* s = new MySpecies;

	ostringstream oss;
	oss << "sPecIes" << listOfMySpecies.size ();
	s->setId (oss.str ());

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

	int operation;
	ostringstream oss;
	oss << "rEactIon" << listOfMyReactions.size ();

	r->setId (oss.str ());
	if (operation == LIBSBML_INVALID_ATTRIBUTE_VALUE)
		throw StrCacuException (
				"Invalid Attribute Value: Reaction id!"
				);

	listOfMyReactions.push_back (r);
	return r;
}

MyCompartment* MySBMLDocument::getMyCompartment (const string& ref)
{
	for (int i=0; i < listOfMyCompartments.size (); i++)
	{
		MyCompartment* comp = listOfMyCompartments[i];
		if (comp->getId () == ref) return comp;
	}
	return NULL;
}

const MyCompartment* MySBMLDocument::getMyCompartment (const string& ref) const
{
	for (int i=0; i < listOfMyCompartments.size (); i++)
	{
		MyCompartment* comp = listOfMyCompartments[i];
		if (comp->getId () == ref) return comp;
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

MySpecies* MySBMLDocument::getMySpecies (const string& ref) 
{
	for (int i=0; i < listOfMySpecies.size (); i++) 
	{
		MySpecies* s = listOfMySpecies[i];
		if (s->getId () == ref) return s;
	}
	return NULL;
}

const MySpecies* MySBMLDocument::getMySpecies (const string& ref) const
{
	for (int i=0; i < listOfMySpecies.size (); i++) 
	{
		MySpecies* s = listOfMySpecies[i];
		if (s->getId () == ref) return s;
	}
	return NULL;
}

MySpecies* MySBMLDocument::getMySpecies (const MySpecies* s)
{
	MySpecies* found = NULL;
	for (int i=0; i<listOfMyCompartments.size (); i++)
	{
		MyCompartment* c = listOfMyCompartments[i];
		found  = c->isMySpeciesIn (s);
		if (found != NULL) break;
	}
	return found;
}

const MySpecies* MySBMLDocument::getMySpecies (const MySpecies* s) const
{
	MySpecies* found = NULL;
	for (int i=0; i<listOfMyCompartments.size (); i++)
	{
		MyCompartment* c = listOfMyCompartments[i];
		found  = c->isMySpeciesIn (s);
		if (found != NULL) break;
	}
	return found;
}

void MySBMLDocument::run (readDataBase& dbreader)
{
	//
	//  listOfMySpecies size may be updated while 
	//  developing biological system network
	//
	int numOfSpecies = listOfMySpecies.size ();

	//  for each species in listOfMySpecies
	for (int i= 0; i < numOfSpecies; i++)
	{
		if (i == 1) break;

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
					"/MoDeL/part/" + p->getPartCtg () + 
					"/listOfReferencedSpecies/"
					"referencedSpecies";
				string doc_1 = p->getPartRef ();

				int numOfSpeciesLinks = 
					dbreader.get_node_element_num (
							PART, &doc_1, &speciesLinkPath
							);

				for (int t=1; t <= numOfSpeciesLinks; t++)
				{
					cout << "\nHandling the First Referenced Species...";

					string speciesReference, partType;
					dbreader.readSpeciesLink (
							PART, p->getPartRef (),speciesLinkPath, 
							t, speciesReference, partType
							);

					//	if partType is not empty, it has to check
					//	part type matching
					if (!partType.empty () && 
							p->getPartType () != partType)
						continue;

					//	check if this species has been searched
					if (speciesUsed.count (speciesReference)) continue;
					else speciesUsed.insert (speciesReference);

					//
					//	read searched species
					//

					cout << "\nReading Species...";

					MySpecies* sLink = new MySpecies;
					sLink->setDB_ref (speciesReference);  
					dbreader.read_cnModel (
							sLink, 
							SPECIES, 
							speciesReference, 
							"/MoDeL/species", 
							true
							);
					//                    cout << "\nspeciesReference = " <<
					//                        speciesReference << endl;

					cout << "\n=============Species Referred...=================\n";
					sLink->Output ();

					//
					//  is this species template match?
					//
					cMatchsArray trym;
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

					int numOfReactionLinks = 
						dbreader.get_node_element_num (
							SPECIES, 
							&speciesReference, 
							&reactionLinkPath
							);

					for (int r=1; r <= numOfReactionLinks; r++)
					{
						string reactionReference, speciesRole;
						dbreader.readReactionLink (
								SPECIES, 
								speciesReference, 
								reactionLinkPath, 
								r, 
								reactionReference, 
								speciesRole
								);
						handleReactionTemplate (
								dbreader, 
								reactionReference, 
								speciesReference,
								speciesRole, 
								i
								);
					}
				}
			}
		}

		numOfSpecies = listOfMySpecies.size ();
	}

	//	update
	write ();
}

void MySBMLDocument::handleReactionTemplate (
		readDataBase& dbreader,
		const string& doc,
		const string& role,
		const string& dbref,
		const int& index
		)
{
	//  reaction direction
	bool direction = true;
	if (role == "product") direction = false;

	//	create a reaction template object
	reactionTemplate* tmpR = new reactionTemplate;
	dbreader.readReactionTemplate (tmpR, doc, direction); 

	//	handle constraints
	for (int i=0; i < tmpR->listOfConstraints.size (); i++)
	{
		vector<string> vars = tmpR->listOfConstraints[i].first;
		string formula = tmpR->listOfConstraints[i].second;

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
			para = tmpR->getParameter (varid);
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
			delete tmpR;
			return;
		}
	}

	/**
	 * ================================================
	 * find species and compartment configuration that
	 * matching patterns described in reaction template
	 * ================================================
	 */

	reactionArrayMatch result;
	tmpR->findSpeciesMatch (
			dbref, 
			index, 
			listOfMySpecies, 
			listOfMyCompartments, 
			result
			);

	/**
	 * create reactions from each matching result
	 */
	for (int i=0; i < result.size (); i++)
	{
		/**
		 * only set id, name, fast, reversible,
		 * other elements such as math, listOfParameters 
		 * will be initialized in myreaction::init function
		 */
		MyReaction* myreaction = createMyReaction ();

		/**
		 * generate products (main body) by
		 * replacing substituent-type parts in products
		 * based on results of matching
		 * *
		 */
		vector<MySpecies*> products;
		tmpR->createProductsFromTemplate (
				listOfMySpecies, 
				listOfMyCompartments, 
				result[i], 
				products
				);

		/**
		 * init species of new reaction 
		 */
		myreaction->init (
				products,
				listOfMySpecies, 
				result[i].first, 
				tmpR
				);

		//
		//	generate real product
		//
		myreaction->createReactionsFromTemplate (
				dbreader, 
				listOfMySpecies, 
				listOfMyCompartments, 
				result[i].first.first,
				tmpR	
				);
	}

	delete tmpR;
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

	string db_comp = getMyCompartment (s->getCompartment ())->getDB_ref ();
	dbreader.readConditionalParameter (
			PART, p->getPartCtg (), p->getPartRef (),
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
						db_comp = getMyCompartment (s->getCompartment ())->getDB_ref ();
						dbreader.readConditionalParameter (
								PART, p->getPartCtg (), p->getPartRef (),
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

					MySpecies* mrna = new MySpecies (listOfMySpecies.size ());
					mrna->setName ("mrna");
					mrna->setCompartment (s->getCompartment ());
					mrna->setInitialAmount (0.0);

					assert (k+1 <= ci-1);
					Chain* mrna_chain = mrna->createChain (mrna->getId (), 0);

					for (int j=k+1; j < ci; j++)
					{
						Part* tm = c->getPart (j);
						Part* mrna_part = mrna_chain->createPart (tm);

						//	partLabel and partCategory are keeped not changed

						//	partType
						if (tm->getPartType () == "ForwardDNA")
							mrna_part->setPartType ("ForwardRNA");
						else if (tm->getPartType () == "ReverseDNA")
							mrna_part->setPartType ("ReverseRNA");
						else throw StrCacuException (
								"Invalid Transcriptional Unit!"
								);

						//	isbinded and partRef
						if (tm->getIsBinded ())
						{
							vector<string> tmp;
							const string doc = tm->getPartRef ();
							string path ("/MoDeL/part/");
							path += tm->getPartCtg () + "/@originalConformation";
							dbreader.get_node_attr (PART, &doc, &path, tmp);
							if (!tmp.empty ()) mrna_part->setPartRef (tmp[0]);
							mrna_part->setIsBinded (false);
						}
					}
					mrna->rearrange ();

					//	check existance of myspecies
					if (getMySpecies (mrna) ==NULL) addMySpecies (mrna); 

					//	record a reaction
					MyReaction* transcription = createMyReaction ();
					transcription->setName ("transcription");
					transcription->setReversible (false);
					transcription->addSpecialReaction (s, mrna, "k_tc", name, k_tc, units);

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
	db_comp = getMyCompartment (s->getCompartment ())->getDB_ref ();
	dbreader.readConditionalParameter (
			PART, p->getPartCtg (), p->getPartRef (),
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
						db_comp = getMyCompartment (s->getCompartment ())->getDB_ref ();
						dbreader.readConditionalParameter (
								PART, p->getPartCtg (), p->getPartRef (),
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

					MySpecies* mrna = new MySpecies (listOfMySpecies.size());
					mrna->setName ("mrna");
					mrna->setCompartment (s->getCompartment ());
					mrna->setInitialAmount (0.0);

					Chain* mrna_chain = mrna->createChain (mrna->getId (), 0);
					assert (k-1 >= ci+1);

					for (int j=k-1; j > ci; j--)
					{
						Part* tm = c->getPart (j);
						Part* mrna_part = mrna_chain->createPart (tm);

						//	partType
						if (tm->getPartType () == "ForwardDNA")
							mrna_part->setPartType ("ReverseRNA");
						else if (tm->getPartType () == "ReverseDNA")
							mrna_part->setPartType ("ForwardRNA");
						else throw StrCacuException (
								"Invalid Transcriptional Unit!"
								);

						//	isbinded and partRef
						if (tm->getIsBinded ())
						{
							vector<string> tmp;
							const string doc = tm->getPartRef ();
							string path ("/MoDeL/part/");
							path += tm->getPartCtg () + "/@originalConformation";
							dbreader.get_node_attr (PART, &doc, &path, tmp);
							if (!tmp.empty ()) mrna_part->setPartRef (tmp[0]);
							mrna_part->setIsBinded (false);
						}
					}
					mrna->rearrange ();

					//	check existance of myspecies
					if (getMySpecies (mrna) ==NULL) addMySpecies (mrna); 

					//	record a reaction
					MyReaction* transcription = createMyReaction ();
					transcription->setName ("transcription");
					transcription->setReversible (false);
					transcription->addSpecialReaction (s, mrna, "k_tc", name, k_tc, units);

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
	string db_comp = getMyCompartment (s->getCompartment ())->getDB_ref ();
	dbreader.readConditionalParameter (
			PART, p->getPartCtg (), p->getPartRef (),
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
			db_comp = getMyCompartment (s->getCompartment ())->getDB_ref ();
			dbreader.readConditionalParameter (
					PART, p->getPartCtg (), p->getPartRef (),
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
							db_comp = getMyCompartment (s->getCompartment ())->getDB_ref ();
							dbreader.readConditionalParameter (
									PART, p->getPartCtg (), p->getPartRef (),
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
						if (ci == k+1 && !isvalidseq)  break;

						//	the biobrick next to rbs is not a valid sequence
						MySpecies* prot = new MySpecies (listOfMySpecies.size ());
						prot->setName ("prot");
						prot->setCompartment (s->getCompartment ());
						prot->setInitialAmount (0.0);

						Chain* prot_chain = prot->createChain (prot->getId (), 0);
						assert (k+1 <= ci);

						int newci = ci;
						if (!isvalidseq) newci = ci-1; 
						for (int j=k+1; j <= newci; j++)
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

							//	isbinded and partRef
							if (tm->getIsBinded ())
							{
								vector<string> tmp;
								const string doc = tm->getPartRef ();
								string path ("/MoDeL/part/");
								path += tm->getPartCtg () + "/@originalConformation";
								dbreader.get_node_attr (PART, &doc, &path, tmp);
								if (!tmp.empty ()) prot_part->setPartRef (tmp[0]);
								prot_part->setIsBinded (false);
							}
						}
						prot->rearrange ();

						//	check existance of myspecies
						if (getMySpecies (prot) ==NULL) addMySpecies (prot); 

						//	record a reaction
						MyReaction* translation = createMyReaction ();
						translation->setName ("translation");
						translation->setReversible (false);
						translation->addSpecialReaction (s, prot, "k_tl", name, value, units);

						break;
					}

					ci++;
				}	while (1);
			}
		}
	}

	return;
}

void MySBMLDocument::write ()
{
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

	cout << "\nREAL RULEs Number: " 
		 << m->getNumRules () 
		 << endl;

	cout << "\nREAL FUNCTIONDEFINITIONs Number: " 
		 << m->getNumFunctionDefinitions () 
		 << endl;

	cout << "\nREAL PARAMETERs Number: " 
		 << m->getNumParameters () 
		 << endl;

	cout << "\nREAL UNITs Number: " 
		 << m->getNumUnitDefinitions () 
		 << endl;

	cout << "\nREAL SPECIES Number: " 
		 << m->getNumSpecies () 
		 << endl;

	cout << "\nREAL COMPARTMENTs Number: " 
		 << m->getNumCompartments () 
		 << endl;

	cout << "\nREAL REACTIONs Number: " 
		 << m->getNumReactions () 
		 << endl;

	cout << "\nDONE!..." << endl;
}
