#include "myreaction.h"

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
	int operation;

	/**
	 * since id has been set when the reaction generates,
	 * we need only check if it is not empty
	 */
	if (getId ().empty ()) throw StrCacuException (
			"Empty Id in MyReaction Object!"
			);

	//	set name
	if (!tmpR->name.empty ())
	{
		operation = setName (tmpR->name);
		if (operation == LIBSBML_INVALID_ATTRIBUTE_VALUE)
			throw StrCacuException (
					"Invalid Attribute Value: Reaction name!"
					);
	}

	setFast (tmpR->fast);
	setReversible (tmpR->reversible);

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
		else throw StrCacuException (
				"Labels of species within one "
			    "reactions should be different!"
				);
	}

	for (int i=0; i < listOfMyModifiers.size (); i++)
	{
		string __old = tmpR->listOfMyModifiers[i]->getDB_Label ();
		string __new = listOfMyModifiers[i]->getId ();

		if (!replacement.count (__old)) replacement[__old] = __new;
		else throw StrCacuException (
				"Labels of species within one "
			    "reactions should be different!"
				);
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
	assert (__reactants_m.size () == listOfMyReactants.size ());

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
		for (int j=0; j < speciesM.size ();j++) 
			chainUsed.insert (speciesM[j].second);

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

	//	mixed species
//    cout << "\nMixture Before Splitting:" << endl;
//    mixture->Output ();

	/**
	 * split mixed species and store results in splits
	 */
	vector<MySpecies*> splits; 
	mixture->split (dbreader, splits);

	/**
	 * check splits
	 */
//    cout << "\nChecking Species Spliting ...";
//    for (int i=0; i < splits.size (); i++) splits[i]->Output ();

	// 	splits are only partial copies of mixture 
	delete mixture;

	//  add products
	vector< vector<int> > degenerate;

	for (int i=0; i< splits.size (); i++)
	{
		MySpecies* split = splits[i];

		//	gather chainLabels of split
		set<string> __CU_splits;
		for (int j =0; j < split->getNumOfChains (); j++)
		{
			Chain* c = split->getChain (j);
			if (!c->getLabel ().empty ())
			{
//                cout << "\nc->getLabel = " << c->getLabel () << endl;
				__CU_splits.insert (c->getLabel ());
			}
		}

		vector<int> __deg;
		for (int j =0; j < listOfMyProducts.size (); j++)
		{
			MySpecies* __prod = listOfMyProducts[i];
			__prod->Output ();
			
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
		if (__deg.empty ())
		{
			vector<MySpecies*>::iterator pos = splits.begin () + i;
			splits.erase (pos); delete split;
		}
		else degenerate.push_back (__deg);
	}

	assert (splits.size () == degenerate.size ());

	//	set stoichiometry
	double* stoiMath = new double[listOfMyProducts.size ()];
	for (int i=0; i< degenerate.size (); i++) 
		for (int j=0; j < degenerate[i].size (); j++)
			stoiMath[degenerate[i][j]] = 1.0 / degenerate[i].size ();

	/**
	 * create products for each product template
	 */

//    cout << "\nsplits_size = " << splits.size ();
	for (int i=0; i < splits.size (); i++)
	{
		MySpecies* splitted = splits[i];

		//	for each species in listOfMyProducts
		for (int j=0; j < degenerate[i].size (); j++)
		{
//            cout << "\nj = " << j << " deg = " << degenerate[i].size () << endl;
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

			ostringstream oss;

			//	set Id
			oss << "sPecIes" << listOfMySpecies.size ();
			__product->setId (oss.str ());

			//	set compTypeId
			__product->setCompTypeId (__product_tm->getCompTypeId ());

			//	set Compartment	
			__product->setCompartment (__product_tm->getCompartment ());

			//	set InitialAmount 
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
//                    cout << "\nfound = " << found << endl;
					break;
				}
			}	
			if (!found) 
			{
				if (compIndex == -1) throw StrCacuException (
						"No compartment found in listOfMyCompartments!"
						);
				else
				{
					listOfMySpecies.push_back (__product);
					listOfMyCompartments[compIndex]->addMySpeciesIn (__product);
				}
			}

			//  delete old species and replaced with new one
			listOfMyProducts[degenerate[i][j]] = __product;
			delete __product_tm;
		}

		delete splitted;
	}

	//
	//  complete components of Reaction object needed for SBML
	//
	int operation;

	//  speciesReference and ModifierReference
	for (int i=0; i<listOfMyReactants.size (); i++)
	{
		SpeciesReference* spr = createReactant ();
		operation = spr->setSpecies (listOfMyReactants[i]->getId ());
		if (operation == LIBSBML_INVALID_ATTRIBUTE_VALUE)
			throw StrCacuException (
					"Writing Block Reaction..."
					"Invalid attribute value: speciesReference!"
					);
	}

	for (int i=0; i<listOfMyProducts.size (); i++)
	{
		SpeciesReference* spr = createProduct ();

//        cout << "\nid = " << listOfMyProducts[i]->getId ();

		operation = spr->setSpecies (listOfMyProducts[i]->getId ());
		if (operation == LIBSBML_INVALID_ATTRIBUTE_VALUE)
			throw StrCacuException (
					"Writing Block Reaction..."
					"Invalid attribute value: speciesReference!"
					);
		spr->setStoichiometry (stoiMath[i]);
	}

	for (int i=0; i<listOfMyModifiers.size (); i++)
	{
		ModifierSpeciesReference* smr = createModifier ();
		operation = smr->setSpecies (listOfMyModifiers[i]->getId ());
		if (operation == LIBSBML_INVALID_ATTRIBUTE_VALUE)
			throw StrCacuException (
					"Writing Block Reaction..."
					"Invalid attribute value: modifierSpeciesReference!"
					);
	}

	//  setKineticLaw
	KineticLaw* kl = createKineticLaw ();

	//  setLocalParameter
	for (int i=0; i < tmpR->listOfParameters.size (); i++)
		kl->addParameter (tmpR->listOfParameters[i]);

	//  setMath
	
	string mathXMLString = tmpR->math;
	map<string,string>::const_iterator itMath = replacement.begin ();
	while (itMath != replacement.end ())
	{
		string __old = itMath->first;
		string __new = itMath->second;

		string::size_type pos = 0;
		//	each trip reset pos to the next instance in name
		while ((pos = mathXMLString.find (__old, pos)) != string::npos)	
			mathXMLString.replace (pos, __old.size (), __new);
		itMath ++;
	}

	ASTNode* astMath = readMathMLFromString(mathXMLString.c_str());
	if (astMath == NULL) 
		throw StrCacuException ("Invalid MathML string converted!");
	operation = kl->setMath (astMath);
	if (operation == LIBSBML_INVALID_OBJECT)
		throw StrCacuException (
				"Writing Block Reaction...Invalid object: astMath!"
				);

	delete astMath;
	delete stoiMath;
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

	int operation;

	//	set Modifier
	ModifierSpeciesReference* mpr = createModifier ();
	operation = mpr->setSpecies (modifier->getId ());
	if (operation == LIBSBML_INVALID_ATTRIBUTE_VALUE)
		throw StrCacuException (
				"Writing Block Reaction..."
				"Invalid attribute value: modifierSpeciesReference!"
				);

	//	set Produtct
	SpeciesReference* spr = createProduct ();
	operation = spr->setSpecies (product->getId ());
	if (operation == LIBSBML_INVALID_ATTRIBUTE_VALUE)
		throw StrCacuException (
				"Writing Block Reaction..."
				"Invalid attribute value: speciesReference!"
				);

	//  setKineticLaw
	KineticLaw* kl = createKineticLaw ();

	//  setLocalParameter
	Parameter* para = kl->createParameter ();

	operation = para->setId (paraId);
	if (operation == LIBSBML_INVALID_ATTRIBUTE_VALUE)
		throw StrCacuException (
				"Writing Block Parameter..."
				"Invalid Attribute Value: id!"
				);
	if (!paraName.empty ())
	{
		para->setName (paraName);
		if (operation == LIBSBML_INVALID_ATTRIBUTE_VALUE)
			throw StrCacuException (
					"Writing Block Parameter..."
					"Invalid Attribute Value: name!"
					);
	}

	para->setValue (paraValue);

	if (!paraUnits.empty ())
	{
		operation = para->setUnits (paraUnits);
		if (operation == LIBSBML_INVALID_ATTRIBUTE_VALUE)
			throw StrCacuException (
					"Writing Block Parameter..."
					"Invalid Attribute Value: units!"
					);
	}

	para->setConstant (true);

	//  setMath
	string formula = paraId + "*" 
		+ modifier->getId () + "*"
		+ modifier->getCompartment ();

	//    cout << "\nformula = " << formula << endl;

	ASTNode_t* astMath = SBML_parseFormula (formula.c_str ());
	if (astMath == NULL) throw StrCacuException (
			"Invalid MathML string converted!"
			);

	operation = kl->setMath (astMath);
	if (operation == LIBSBML_INVALID_OBJECT)
		throw StrCacuException (
				"Writing Block Reaction..."
				"Invalid object: astMath!"
				);
	delete astMath;
}

