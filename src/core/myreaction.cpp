#include "myreaction.h"

MyReaction::MyReaction ():
	Reaction (2, 4)
{}

MyReaction::~MyReaction () 
{}

void MyReaction::createReactionsFromTemplate (
		bdbXMLInterface& dbreader,
		const speciesArrayMatch& __reactants_m,
		const speciesArrayMatch& __modifiers_m,
		vector<MySpecies*>& __products_body,
		vector<MySpecies*>& listOfMySpecies,
		vector<MyCompartment*>& listOfMyCompartments,
		const reactionTemplate* tmpR
		)
{
	/**
	 * replace table: used to map reactants/modifiers/products 
	 * label to that of matched species already in the system
	 */
	map <string, string> replaceTable;

	/**
	 * copy reactants/modifiers/products/ to local lists
	 */
	for (int i=0; i < __reactants_m.size (); i++)
	{
		MySpecies* sr = listOfMySpecies[__reactants_m[i].first];
		listOfMyReactants.push_back (sr);
		
		string __tm_label = tmpR->listOfMyReactants[i]->getDB_Label ();
		if (!replaceTable.count (__tm_label)) 
			replaceTable[__tm_label] = sr->getId ();
		else throw StrCacuException (
				"Labels of species within one reactions should be different!"
				);
	}

	for (int i=0; i < __modifiers_m.size (); i++)
	{
		MySpecies* mr = listOfMySpecies[__modifiers_m[i].first];
		listOfMyModifiers.push_back (mr);
		
		string __tm_label = tmpR->listOfMyModifiers[i]->getDB_Label ();
		if (!replaceTable.count (__tm_label)) 
			replaceTable[__tm_label] = mr->getId ();
		else throw StrCacuException (
				"Labels of species within one reactions should be different!"
				);
	}

	for (int i=0; i < __products_body.size (); i++)
	{
		MySpecies* prodBody = __products_body[i];
		
		//  compartment of prodBody must have been set previously
		assert (!prodBody->getCompartment ().empty ());

		//	generate unique label for each chain of __products_body
		prodBody->genUniqueLabel (i);

		//	push product body into products list
		listOfMyProducts.push_back (prodBody);	
	}


	/**
	 * mix species:
	 * algo: only chains of reactants (does not contain those 
	 * defined in the template) and products (only contains 
	 * those defined in the template) will be mixed
	 * *
	 * some extra work needs to be done:
	 * 1. chain-label should be reset: we use species db label +
	 * [cHaIn + num] to set the chain label
	 * 2. species mixed should be trimmed before splitting
	 * 3. splits should be rearranged and generated new labels
	 * *
	 */
	MySpecies* mixture  = new MySpecies;

	//  (1.1) mix reactants
	for (int i=0; i < __reactants_m.size (); i++)
	{
		MySpecies* sr = listOfMySpecies[__reactants_m[i].first];

		/**
		 *	template chains are not allowed to be mixed into the mixture
		 */
		set<int> chainUsed;
		cMatchsType2 speciesM = __reactants_m[i].second;
		for (int j=0; j < speciesM.size ();j++) 
			chainUsed.insert (speciesM[j].second);

		//	copy chains that contributes to matching
		for (int j=0; j < sr->getNumOfChains (); j++)
		{
			if (!chainUsed.count (j)) 
				mixture->createChain (sr->getChain (j));
		}

		//	copy all trees
		for (int j=0; j < sr->getNumOfTrees (); j++)
			mixture->createTree (sr->getTree (j));
	}

	//  (1.2) mix products
	for (int i=0; i < __products_body.size () ; i++)
	{
		MySpecies* prodBody = __products_body[i];
		//	copy chains
		for (int j=0; j< prodBody->getNumOfChains (); j++)
			mixture->createChain (prodBody->getChain (j));
		//	copy trees
		for (int j=0; j< prodBody->getNumOfTrees (); j++)
			mixture->createTree (prodBody->getTree (j));
	}

	//	mixed species
	cout << "\nMixture Before Splitting:" << endl;
	mixture->Output ();

	/**
	 * split mixed species and store results in splits
	 */
	vector<MySpecies*> splits; 
	mixture->split (dbreader, splits);

	/**
	 * check splits
	 */
	cout << "\nChecking Species Spliting ...";
	for (int i=0; i < splits.size (); i++) splits[i]->Output ();

	// 	splits are only partial copies of mixture 
	delete mixture;

	//  add products
	vector< vector<int> > degenerate;

	for (int i=0; i< splits.size (); i++)
	{
		MySpecies* split = splits[i];

		set<string> __CU_splits;
		for (int j =0; j < split->getNumOfChains (); j++)
			__CU_splits.insert (split->getChain (j)->getLabel ());

		vector<int> __deg;
		for (int j =0; j < listOfMyProducts.size (); j++)
		{
			MySpecies* __prod = listOfMyProducts[i];
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

	for (int i=0; i < splits.size (); i++)
	{
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
			 * 2. comp_type_id should be set previously if it is empty
			 */
			MySpecies* __product (splitted);
			MySpecies* __product_tm = listOfMyProducts[degenerate[i][j]];

			ostringstream oss;

			//	set Id
			oss << "sPecIes" << listOfMySpecies.size ();
			__product->setId (oss.str ());

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
					break;
				}
			}	
			if (!found) 
			{
				listOfMySpecies.push_back (__product);
				listOfMyCompartments[compIndex]->addMySpeciesIn (__product);
			}

			//
			//  add replacement
			//
			string oldLabel = __product_tm->getDB_Label ();
			assert (!replaceTable.count (oldLabel));
			replaceTable[oldLabel] = __product->getId ();

			//  delete old species and replaced with new one
			delete __product_tm;
		   	__product_tm = __product;	
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
	map<string,string>::const_iterator itMath = replaceTable.begin ();
	while (itMath != replaceTable.end ())
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
		throw StrCacuException ("Invalid MathML string convetmpRed!");
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

