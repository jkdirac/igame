#include "mysbmldoc.h"

MySBMLDocument::MySBMLDocument ():
	SBMLDocument (2,4)
{}

MySBMLDocument::~MySBMLDocument ()
{
	for (int i=0; i < listOfMySpecies.size (); i++) {
		delete listOfMySpecies[i];
	}
	for (int i=0; i < listOfMyCompartments.size (); i++) {
		delete listOfMyCompartments[i];
	}
	for (int i=0; i < listOfMyReactions.size (); i++) {
	   	delete listOfMyReactions[i];
	}
}

//	make sure species added has never existed before
void MySBMLDocument::addMySpecies (MySpecies* s) 
{
	listOfMySpecies.push_back (s);
	MyCompartment* c = getMyCompartment (s->getCompartment ());
	
	//	add species to compartment
	assert (c != NULL);
	c->addMySpeciesIn (s);

	//	set counterpart of compartment
	if (!s->getCompTypeId ().empty ())
	{
		MyCompartment* itself = getMyCompartment (s->getCompTypeId ());
		if (itself == NULL) throw CoreException (
				"No corresponding compartment for species with non-empty comp_type_id!"
				);
		else itself->setCounterPart (s->getId ());
	}
}

void MySBMLDocument::addMyCompartment (MyCompartment* c) 
{
	listOfMyCompartments.push_back (c);
}

void MySBMLDocument::setRelationOfCompartments ()
{
	for (int i=0; i < listOfMyCompartments.size (); i++)
	{
		MyCompartment* child = listOfMyCompartments[i];
		if (child->getOutside () != "ROOT")
		{
			MyCompartment* parent = getMyCompartment (child->getOutside ());
			if (parent == NULL) throw CoreException (
					"No compartment existed in compartment list for given compartment!"
					);
			else 
			{
				child->addParentCompartment (parent);
				parent->addMyCompartmentIn (child);
			}
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

	ostringstream oss;
	oss << "rEactIon" << listOfMyReactions.size ();

	r->setId (oss.str ());

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

MyCompartment* MySBMLDocument::getMyCompartment (const int& i)
{
	if (i < 0 || i >= listOfMyCompartments.size ()) return NULL;
	else return listOfMyCompartments[i];
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

const MyCompartment* MySBMLDocument::getMyCompartment (const int& i) const
{
	if (i < 0 || i >= listOfMyCompartments.size ()) return NULL;
	else return listOfMyCompartments[i];
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
		//for each species
		MySpecies* s = listOfMySpecies[i];

		cout << "\n===========		SPECIES " << i << "		=============" << endl;
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
				string speciesLinkPath = "/MoDeL/part/" + p->getPartCtg () + 
					"/listOfReferencedSpecies/referencedSpecies";
				string doc_1 = p->getPartRef ();

				int numOfSpeciesLinks = dbreader.get_node_element_num (
							PART, &doc_1, &speciesLinkPath
							);


				for (int t=1; t <= numOfSpeciesLinks; t++)
				{
					string speciesReference, partType;
					dbreader.readSpeciesLink (
							PART, p->getPartRef (),speciesLinkPath, 
							t, speciesReference, partType
							);

					//	if partType is not empty, it has to check
					//	part type matching
					if (!partType.empty () && p->getPartType () != partType) continue;

					//	check if this species has been searched
					if (speciesUsed.count (speciesReference)) continue;
					else speciesUsed.insert (speciesReference);

					//	read searched species
					MySpecies* sLink = new MySpecies;
					sLink->setDB_ref (speciesReference);  
					dbreader.read_cnModel (sLink, SPECIES, speciesReference, "/MoDeL/species", true);

					cout << "\n------------	TEMPLATES " << t << "	------------\n";
					sLink->Output ();

					//  Does this template match this species?
					cMatchsArray trym;
					if (!s->match (sLink, trym)) continue;

					//
					//  read reaction Links
					string reactionLinkPath = "/MoDeL/species/"
						"listOfReferencedReactions/referencedReaction";

					const int numOfReactionLinks = dbreader.get_node_element_num (
							SPECIES, &speciesReference, &reactionLinkPath
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

						cout << "\nHandling Referenced Reaction	" 
							<< "	...		DOC	:	" 
							<< reactionReference << "	TYPE :	"
							<< speciesRole << endl;

						handleReactionTemplate (
								dbreader, 
								reactionReference, 
								speciesRole, 
								speciesReference,
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
		const string& type, 
		const string& dbref,
		const int& index
		)
{
	/**
	 * =================================
	 * create a reaction template object
	 * =================================
	 */
	reactionTemplate* tmpR = new reactionTemplate;
	dbreader.readReaction (doc, dbref, type, tmpR);

	cout << "\n<--  READ Reaction Template	  "
		 << "---	...	---	DONE! " << endl;

	/**
	 * ===============================
	 * HANDLE CONSTRAINTS OF PARAMTERS
	 * ===============================
	 */
	const ListOfParameters* listOfMyParameters 
		= getModel ()->getListOfParameters ();
	bool expr = tmpR->handle_constraints (listOfMyParameters);
	if (!expr) {delete tmpR; return;}

	cout << "\n<--  Caculate Reaction Constraints " 
		 << "---	...	---	DONE! " << endl;

	/**
	 * ================================================
	 * find species and compartment configuration that
	 * matching patterns described in reaction template
	 * ================================================
	 */

	reactionArrayMatch result;
	bool found = tmpR->findSpeciesMatch (
			dbref, 
			index, 
			listOfMySpecies, 
			listOfMyCompartments, 
			result
			);

#ifndef NDEBUG
	cout << "\n################		MATCHING...	 DONE	#################\n";
	cout << "\n^_^	Combinations	=	" << result.size () << endl;
#endif

	/**
	 * create reactions from each matching result
	 */
	for (int i=0; i < result.size (); i++)
	{
		cout << "\n======	new reaction	i=	" 
			 << i << "	=========" <<	endl;
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

	if (value <0) throw CoreException (
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
						if (termeff <0 || termeff > 1) throw CoreException (
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
					mrna->setHasOnlySubstanceUnits (false);
					mrna->setConstant (false);
					mrna->setBoundaryCondition (false);

					assert (k+1 <= ci-1);
					Chain* mrna_chain = mrna->createChain ();

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
						else throw CoreException (
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
					mrna->rearrange (false);

					//	check existance of myspecies
					MySpecies* found = getMySpecies (mrna);
					if (found == NULL) {found = mrna; addMySpecies (mrna);} 
					else delete mrna;

					//	record a reaction
					MyReaction* transcription = createMyReaction ();
					transcription->setName ("transcription");
					transcription->setReversible (false);
					transcription->addSpecialReaction (
							s, found, "k_tc", name, k_tc, units
							);

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
	if (value <0) throw CoreException (
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
						if (termeff <0 || termeff > 1) throw CoreException (
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
					mrna->setHasOnlySubstanceUnits (false);
					mrna->setConstant (false);
					mrna->setBoundaryCondition (false);

					Chain* mrna_chain = mrna->createChain ();
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
						else throw CoreException (
								"Invalid Transcriptional Unit!"
								);

//                        cout << "\npartRef = " << mrna_part->getPartRef ()
//                             << " partType == " << mrna_part->getPartType ();

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
					mrna->rearrange (false);

//                    cout << "\nspecies test = " << endl;
//                    mrna->Output ();

					//	check existance of myspecies
					MySpecies* found = getMySpecies (mrna);
					if (found == NULL) {found = mrna; addMySpecies (mrna);} 
					else delete mrna;

					//	record a reaction
					MyReaction* transcription = createMyReaction ();
					transcription->setName ("transcription");
					transcription->setReversible (false);
					transcription->addSpecialReaction (s, found, "k_tc", name, k_tc, units);

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

	if (value <0) throw CoreException (
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
			if (codonEff <0 || codonEff > 1) throw CoreException (
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
							if (codonEff <0 || codonEff > 1) throw CoreException (
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
						prot->setHasOnlySubstanceUnits (false);
						prot->setConstant (false);
//                        prot->setCharge (0);
						prot->setBoundaryCondition (false);

						Chain* prot_chain = prot->createChain ();
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
							else throw CoreException (
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
						prot->rearrange (false);

						//	check existance of myspecies
						MySpecies* found = getMySpecies (prot);
						if (found == NULL) {found = prot; addMySpecies (prot);} 
						else delete prot;

						//	record a reaction
						MyReaction* translation = createMyReaction ();
						translation->setName ("translation");
						translation->setReversible (false);
						translation->addSpecialReaction (s, found, "k_tl", name, value, units);

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
	Model* m = getModel ();

	int operation = 0;

	for (int i=0; i < listOfMySpecies.size (); i++)
	{
		m->addSpecies (listOfMySpecies[i]);
		
		cout << "\n------------ OUTPUT SPECIES " << i << "\n";
		listOfMySpecies[i]->Output ();
		
		
	}

	for (int i=0; i < listOfMyCompartments.size (); i++)
	{
		MyCompartment* comp = listOfMyCompartments[i];
		if (comp->getOutside () == "ROOT") 
		{
			comp->unsetOutside ();
		}
		m->addCompartment (comp);
	}

	for (int i=0; i < listOfMyReactions.size (); i++)
	{
		m->addReaction (listOfMyReactions[i]);
	}
}

void MySBMLDocument::output ()
{
	cout << setiosflags (ios::right);

	//version and level
	unsigned int level = getLevel();
	unsigned int version = getVersion();

	cout << endl;
	cout << "  level: " << level << "  	version: " << version << endl;
	cout << endl;

	//getmodel
	Model* model = getModel ();

	/*****************************************************************
	  COMPARTMENTS
	 ******************************************************************/
	unsigned int NumCompartments = model->getNumCompartments();

	cout << endl;
	cout << "  NumberOfCompartments: " << NumCompartments << endl;
	cout << endl;

	for (int i = 0; i < NumCompartments; i++)
	{
		Compartment* comp;
		comp = model->getCompartment (i);

		cout << endl;
		cout << setw(10) << "  id: " << comp->getId () << setw(10) 
			<< "  		name: " << comp->getName () << setw(10)
			<< "  		size: " << comp->getSize () << setw(10)
			<< "  		units: " << comp->getUnits () << endl;
	}

	/*****************************************************************
	  SPIECES
	 ******************************************************************/
	unsigned int NumSpecies = model->getNumSpecies ();

	cout << endl;
	cout << "  NumberOfSpecies: " << NumSpecies << endl;
	cout << endl;

	for (int i = 0; i < NumSpecies; i++)
	{
		Species* sp;
		sp = model->getSpecies (i);

		cout << endl;
		cout << setw(10) << "  id: " << sp->getId () << setw(10)
			<< "  name: " << sp->getName () << setw(10)
			<< "  type: " << sp->getSpeciesType () << setw(10)
			<< "  InitialAmount: " << sp->getInitialAmount () << setw(10)
			<< "  unit: " << sp->getSubstanceUnits () << setw(10)
			<< "  compartment: " << sp->getCompartment () <<  endl;
	}

	/******************************************************************
	 * 					    REACTIONS
	 *****************************************************************/

	unsigned int NumReactions = model->getNumReactions ();

	cout << endl;
	cout << "  NumOfReactions: " << NumReactions << endl;
	cout << endl;

	Reaction* re;
	KineticLaw* kl;
	SpeciesReference* SpRef;

	for (int i = 0; i < NumReactions; i++)
	{
		re = model->getReaction (i);

		cout << endl;

		unsigned int NumReactants = re->getNumReactants ();
		unsigned int NumProducts = re->getNumProducts ();

		//		cout << "\nNumR = " << NumReactants << " NumP = " << NumProducts << endl;
		cout << setw(40) << re->getName () << ": ";
		cout.setf(ios::right, ios::adjustfield);

		for (int ir = 0; ir < NumReactants; ir++)
		{
			if (ir > 0) cout << " + " ;

			SpRef = re->getReactant (ir);
			cout << "  " << SpRef->getSpecies ();
		}

		cout << " --> ";

		for (int ip = 0; ip < NumProducts; ip++)
		{
			if (ip > 0) cout << " + " ;

			SpRef = re->getProduct (ip);
			cout << "  " << SpRef->getSpecies ();
		}

		//kinetic law
		cout << "\t";
		kl = re->getKineticLaw ();
		cout << kl->getFormula ();

		cout << endl;

	}

	/******************************************************************
	 * 					    PARAMETERS
	 *****************************************************************/
	unsigned int NumParameters = model->getNumParameters ();

	cout << endl;
	cout << "  NumOfParameters: " << NumParameters << endl;
	cout << endl;

	Parameter * pm;

	for (int i = 0; i < NumParameters; i++)
	{
		pm = model->getParameter (i);

		cout << endl << setw(10);
		cout << "  id: " << pm->getId () << setw(10)
			<< "  name: " << pm->getName () << setw(10)
			<< "  unit: " << pm->getUnits () << setw(10)
			<< "  value: " << pm->getValue () << setw(10) 
			<< "  constant: " << pm->getConstant () << endl;
	}

	/******************************************************************
	 * 					    RULES
	 ******************************************************************/
	unsigned int NumRules = model->getNumRules ();

	cout << endl;
	cout << "  NumOfRules: " << NumRules << endl;
	cout << endl;

	Rule * rl;

	for (int i =0; i < NumRules; i++)
	{
		rl = model->getRule (i);

		cout << endl << setw(10);
		cout << "  variable: " << rl->getVariable () << setw(10)
			<< "  unit: " << rl->getUnits () << setw(10)
			<< "  Formula: " << rl->getFormula () << endl;
	}

	cout << endl << endl << endl;
}
