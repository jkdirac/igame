#include "myreaction.h"
#include "DebugOut.h"

MyReaction::MyReaction ():
	Reaction (2, 4)
{}

MyReaction::~MyReaction () 
{}

void MyReaction::init (
		vector<MySpecies*>& products, 
		const vector<MySpecies*>& listOfMySpecies,
		const reactionMatch& __reaction_match,
		const reactionTemplate* tmpR
		)	
{

	/**
	 * since id has been set when the reaction generates,
	 * we need only check if it is not empty
	 */
	if (getId ().empty ()) 
		throw CoreException ("Empty Id in MyReaction Object!");
	if (!tmpR->name.empty ()) setName (tmpR->name);
	setFast (tmpR->fast);
	setReversible (false);

	/**
	 * set listOfMyReactants/listOfMyModifiers/listOfMyProducts
	 */
	const speciesArrayMatch& __reactants = __reaction_match.first;
	const speciesArrayMatch& __modifiers = __reaction_match.second;

	for (int i=0; i < __reactants.size (); i++)
	{
		MySpecies* sr = listOfMySpecies[__reactants[i].first];
		listOfMyReactants.push_back (sr);
	}
	for (int i=0; i < __modifiers.size (); i++)
	{
		MySpecies* mr = listOfMySpecies[__modifiers[i].first];
		listOfMyModifiers.push_back (mr);
	}
	for (int i=0; i < products.size (); i++)
	{
		listOfMyProducts.push_back (products[i]);
	}
}

void MyReaction::createReactionsFromTemplate (
		bdbXMLInterface& dbreader,
		vector<MySpecies*>& listOfMySpecies,
		vector<MyCompartment*>& listOfMyCompartments,
		const speciesArrayMatch& __reactants_m,
		const map<string, int>& config,
		const reactionTemplate* tmpR
		)
{
	/**
	 * replacement: used to map reactants/modifiers/products 
	 * label to that of matched species already in the system
	 */
	map <string, string> replacement;
	for (int i=0; i < listOfMyReactants.size (); i++)
	{
		string __old = tmpR->listOfMyReactants[i]->getDB_Label ();
		string __new = listOfMyReactants[i]->getId ();

		if (!replacement.count (__old)) replacement[__old] = __new;
		else 
		{
			string errno ("Two different species should not have same label ( ");
			errno += __old + ")!"; throw CoreException (errno);
		}
	}

	for (int i=0; i < listOfMyModifiers.size (); i++)
	{
		string __old = tmpR->listOfMyModifiers[i]->getDB_Label ();
		string __new = listOfMyModifiers[i]->getId ();

		if (!replacement.count (__old)) replacement[__old] = __new;
		else 
		{
			string errno ("Two different species should not have same label ( ");
			errno += __old + ")!"; throw CoreException (errno);
		}
	}

	map<string,string>::const_iterator first = tmpR->mapComps.begin ();
	for (int i=0; first != tmpR->mapComps.end (); i++, first ++)
	{
		assert (config.count (first->first));
		int compIndex = config.find (first->first)->second;

		string compartment = listOfMyCompartments[compIndex]->getId ();
		replacement[first->first] = compartment;
	}

	/**
	 * mix species:
	 * algo: only chains of reactants (does not contain those 
	 * defined in the template) and products (only contains 
	 * those defined in the template) will be mixed
	 * *
	 * some extra work needs to be done:
	 * 1. chain-label should be set.
	 * 2. species mixed should be trimmed before splitting
	 * 3. splits should be rearranged and generated new labels
	 * *
	 */
	MySpecies* mixture  = new MySpecies;

	//  (1.1) mix reactants
	for (int i=0; i < listOfMyReactants.size (); i++)
	{
		MySpecies* sr = listOfMySpecies[__reactants_m[i].first];

		//	prefix to be added for part labels and node labels
		ostringstream oss;
		string prefix = "__MoDeL_REACTANT_CXX";
		oss << prefix << i << "::"; 

		//	find chains that are defined in reactant template
		set<int> chainUsed;
		cMatchsType2 speciesM = __reactants_m[i].second;
		for (int j=0; j < speciesM.size ();j++) chainUsed.insert (speciesM[j].second);

		//	copy chains that contributes to matching
		for (int j=0; j < sr->getNumOfChains (); j++)
		{
			if (!chainUsed.count (j)) 
			{
				Chain* c = mixture->createChain (sr->getChain (j));
				c->__add_chain_prefix (oss.str ());
			}
		}

		//	copy all trees
		for (int j=0; j < sr->getNumOfTrees (); j++)
		{
			Tree* t = mixture->createTree (sr->getTree (j));
			t->__add_tree_prefix (oss.str ());
		}
	}

	//  (1.2) mix products
	for (int i=0; i < listOfMyProducts.size () ; i++)
	{
		MySpecies* s = listOfMyProducts[i];

		for (int j=0; j< s->getNumOfChains (); j++) 
		{
			Chain* c = mixture->createChain (s->getChain (j));
			
			//	generate chain label
			ostringstream oss;
			oss << "__MoDeL_CHAIN_CXX_" << i << "_" << j;
			c->setLabel (oss.str ());
			s->getChain (j)->setLabel (oss.str ());
		}

		for (int j=0; j< s->getNumOfTrees (); j++) 
			mixture->createTree (s->getTree (j));
	}

	//	DEBUG
	debugOut() << "\nMixture:" << endl;
	mixture->Output ();
	debugOut () << "\nEnd Mixture!" << endl;
	//	END

	/**
	 * split mixed species and store results in splits
	 */
	vector<MySpecies*> splits; 
	mixture->split (dbreader, splits);

	//	DEBUG
	debugOut() << "\nSplits:" << endl;
	for (int i=0; i < splits.size (); i++) splits[i]->Output ();
	debugOut () << "\nEnd Splits!" << endl;
	//	END
	
	delete mixture;

	//  add products
	set<int> remove;
	vector< vector<int> > degenerate;

	for (int i=0; i< splits.size (); i++)
	{
		MySpecies* split = splits[i];

		//	gather chainLabels of split
		set<string> __CU_splits;
		for (int j =0; j < split->getNumOfChains (); j++)
		{
			Chain* c = split->getChain (j);
			if (!c->getLabel ().empty ()) __CU_splits.insert (c->getLabel ());
		}

		vector<int> __deg;
		for (int j =0; j < listOfMyProducts.size (); j++)
		{
			MySpecies* __prod = listOfMyProducts[j];
			for (int k =0; k < __prod->getNumOfChains (); k++)
			{
				Chain* c = __prod->getChain (k);
				if (__CU_splits.count (c->getLabel ())) {
					__deg.push_back (j); break;
				}
			}
		}

		/**
		 * not all splits are generated from products
		 * However, in present version, undefined species (unknown compartment)
		 * will be omitted!
		 */
		if (__deg.empty ()) remove.insert (i);
		else degenerate.push_back (__deg);
	}

	//	set stoichiometry
	double* stoiMath = NULL;
	if (listOfMyProducts.size () > 0)
	{
		stoiMath = new double[listOfMyProducts.size ()];
		for (int i=0; i< degenerate.size (); i++) 
			for (int j=0; j < degenerate[i].size (); j++)
				stoiMath[degenerate[i][j]] = 
					1.0 / degenerate[i].size ();
	}

	/**
	 * create products for each product template
	 */

	cout << "\ncreate products for each product template!" << endl;
	for (int i=0; i < splits.size (); i++)
	{
		if (remove.count (i)) continue;
		MySpecies* splitted = splits[i];

		//	for each species in listOfMyProducts
		for (int j=0; j < degenerate[i].size (); j++)
		{
			/**
			 * new species 
			 * create and set its id and compartment, and initialAmount
			 * *
			 * Attention!
			 * 1. name is omitted
			 * 2. comp_type_id should be set previously if it is not empty
			 */
			MySpecies* __product = new MySpecies (splitted);
			MySpecies* __product_tm = listOfMyProducts[degenerate[i][j]];

			__product->rearrange (false);

			ostringstream oss;
			oss << "sPecIes" << listOfMySpecies.size ();
			__product->setId (oss.str ());
			__product->display_name (listOfMySpecies.size ());
			__product->setCompTypeId (__product_tm->getCompTypeId ());
			__product->setCompartment (__product_tm->getCompartment ());
			__product->setInitialAmount (0.0);

			//  add to speciesList
			bool found = false;
			int compIndex = -1;	//	compartment index of __product
			for (int k=0; k <listOfMyCompartments.size (); k++)
			{
				MyCompartment* mycomp = listOfMyCompartments[k];
				if (__product->getCompartment () == mycomp->getId ()) 
				{
					compIndex = k;
					MySpecies* prev = mycomp->isMySpeciesIn (__product);
					if (prev != NULL) {
						found = true; delete __product; __product = prev;
					}
					break;
				}
			}	
			if (!found) 
			{
				if (compIndex == -1) 
				{
					string errno ("No compartment with label ");
					errno += __product->getCompartment () + " found in compartment list!";
					throw CoreException (errno);
				}
				else
				{
					listOfMySpecies.push_back (__product);
					listOfMyCompartments[compIndex]->addMySpeciesIn (__product);
				}
			}

			//  delete old species and replaced with new one
			listOfMyProducts[degenerate[i][j]] = __product;

			//	it is need to make it clear about chain labels
			for (int k=0; k < __product->getNumOfChains (); k++) __product->getChain (k)->setLabel ("");
			__product_tm->Output ();
			delete __product_tm;
		}
	}

	cout << "DONE" << endl;

	for (int i=0; i < splits.size (); i++) delete splits[i];

	//  complete components of Reaction object needed for SBML
	//  speciesReference and ModifierReference
	for (int i=0; i<listOfMyReactants.size (); i++)
	{
		SpeciesReference* spr = createReactant ();
		spr->setSpecies (listOfMyReactants[i]->getId ());
	}

	for (int i=0; i<listOfMyProducts.size (); i++)
	{
		SpeciesReference* spr = createProduct ();
		spr->setSpecies (listOfMyProducts[i]->getId ());
		spr->setStoichiometry (stoiMath[i]);
	}

	for (int i=0; i<listOfMyModifiers.size (); i++)
	{
		ModifierSpeciesReference* smr = createModifier ();
		 smr->setSpecies (listOfMyModifiers[i]->getId ());
	}

	//  setKineticLaw
	KineticLaw* kl = createKineticLaw ();

	//  setLocalParameter
	for (int i=0; i < tmpR->listOfParameters.size (); i++)
		kl->addParameter (tmpR->listOfParameters[i]);

	//  setMath
	string mathXMLString = tmpR->math;
	map<string,string>::const_iterator itMath = replacement.begin ();

	cout << "\nmath = " << mathXMLString << endl;
	while (itMath != replacement.end ())
	{
		string __old = itMath->first;
		string __new = itMath->second;

		cout << "\nold = " << __old << " new = " << __new << endl;

		if (__old == __new) {itMath++; continue;}

		string::size_type pos = 0;
		//	each trip reset pos to the next instance in name
//        int i = 0;
		while ((pos = mathXMLString.find (__old, pos)) != string::npos)	
		{
//            if (i ==5) terminate ();
//            cout << "pos1 = " << pos ;
			mathXMLString.replace (pos, __old.size (), __new);
			pos += __new.size ();
//            cout << "\nmath = " << mathXMLString << endl;
//            cout << " pos2 =  " << pos << endl;
//            i++;
		}
		itMath ++;
	}
	cout << "\nmath = " << endl;

	ASTNode* astMath = readMathMLFromString(mathXMLString.c_str());
	if (astMath == NULL) throw CoreException ("Invalid MathML string converted!");
	else kl->setMath (astMath);

	if (astMath != NULL) delete astMath;
	if (astMath != NULL) delete stoiMath;

	cout << "\nDone of this reaction!" << endl;
}

void MyReaction::addSpecialReaction (
		MySpecies* modifier,
		MySpecies* product,
		const string& paraId,
		const string& paraName,
		const double& paraValue,
		const string& paraUnits
		)
{
	listOfMyModifiers.push_back (modifier);
	listOfMyProducts.push_back (product);

	//	set Modifier
	ModifierSpeciesReference* mpr = createModifier ();
	mpr->setSpecies (modifier->getId ());

	//	set Produtct
	SpeciesReference* spr = createProduct ();
	spr->setSpecies (product->getId ());

	//  setKineticLaw
	KineticLaw* kl = createKineticLaw ();

	//  setLocalParameter
	Parameter* para = kl->createParameter ();

	para->setId (paraId);
	para->setValue (paraValue);
	para->setConstant (true);

	if (!paraName.empty ()) para->setName (paraName);
	if (!paraUnits.empty ()) para->setUnits (paraUnits);

	string formula = paraId + "*" 
		+ modifier->getId () + "*"
		+ modifier->getCompartment ();

	ASTNode_t* astMath = SBML_parseFormula (formula.c_str ());
	if (astMath == NULL) 
		throw CoreException ("Invalid MathML string converted!");
	kl->setMath (astMath);
	delete astMath;
}

