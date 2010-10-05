#include "myreaction.h"

MyReaction::MyReaction ():
	Reaction (2, 4)
{}

MyReaction::~MyReaction () 
{
	/*
	   for (int i=0; i<listOfMyReactants.size (); i++)
	   listOfMyReactants[i]->~Species ();
	   for (int i=0; i<listOfMyModifiers.size (); i++)
	   listOfMyModifiers[i]->~Species ();
	   for (int i=0; i<listOfMyProducts.size (); i++)
	   listOfMyProducts[i]->~Species ();
	   */
}

void MyReaction::completeReaction (
		bdbXMLInterface& dbreader,
		vector<MyCompartment*>& listOfMyCompartments,
		vector<MySpecies*>& listOfMySpecies,
		vector<MySpecies*>& productsBody,
		const speciesArrayMatch& reactantsM,
		const speciesArrayMatch& modifiersM,
		const reactionTemplate* RT
		)
{
	//(1) mix species 
	MySpecies* speciesMixing = new MySpecies;
	map<string,string> replaceTable;

	//  (1.1) copy modifiers
	//  cout << "\nmodifiers = " << modifiersM.size () << endl;
	for (int i=0; i < modifiersM.size (); i++)
	{
		int sind = modifiersM[i].first;
		MySpecies* mr = listOfMySpecies[sind];
		listOfMyModifiers.push_back (mr);

		string Label = RT->listOfMyModifiers[i]->getDB_Label ();
		replaceTable[Label] = mr->getId ();
	}

	//  (1.2) copy and mix reactants
	//  cout << "\nreactants = " << reactantsM.size () << endl;
	for (int i=0; i < reactantsM.size (); i++)
	{
		int sind = reactantsM[i].first;
		cMatchsType2 speciesM = reactantsM[i].second;

		MySpecies* sr = listOfMySpecies[sind];
		listOfMyReactants.push_back (sr);

		//	complete chainUsed
		set<int> chainUsed;
		for (int j=0; j < speciesM.size ();j++)
			chainUsed.insert (speciesM[j].second);

		//	copy chains that contributes to matching
		for (int j=0; j < sr->getNumOfChains (); j++)
		{
			if (!chainUsed.count (j)) 
				speciesMixing->createChain (sr->getChain (j));
		}

		//	copy all trees
		for (int j=0; j < sr->getNumOfTrees (); j++)
			speciesMixing->createTree (sr->getTree (j));

		string Label = RT->listOfMyReactants[i]->getDB_Label ();
		replaceTable[Label] = sr->getId ();
	}

	//  (1.3) copy and mix products
	int numProd = listOfMyProducts.size ();
	//  cout << "\nproducts = " << productsBody.size () << endl;
	for (int i=0; i < productsBody.size () ; i++)
	{
		MySpecies* prodBody = productsBody[i];

		/*
		 * generate unique label for each chain of productsBody
		 */
		prodBody->genUniqueLabel (i);

		//    cout << "\nproductsBody: " << i;
		listOfMyProducts.push_back (prodBody);	//push product body into products list

		//    cout << "\nchain number = " << sp->getNumOfChains () << endl;
		for (int j=0; j< prodBody->getNumOfChains (); j++)
			speciesMixing->createChain (prodBody->getChain (j));

		//    cout << "\ntree number = " << sp->getNumOfTrees () << endl;
		for (int j=0; j< prodBody->getNumOfTrees (); j++)
			speciesMixing->createTree (prodBody->getTree (j));
	}

	//	mixed species
	speciesMixing->Output ();

	/**
	 * split mixed species and store results in realProducts
	 */
	vector<MySpecies*> realProducts; 
	speciesMixing->split (dbreader, realProducts);

	//	check realProducts
	cout << "\nCheck products after mixing...";
	for (int i=0; i < realProducts.size (); i++)
		realProducts[i]->Output ();
	cout << "Done!" << endl;

	//  readProducts are just copies
	delete speciesMixing;

	//  add products
	vector<int>* dGp = new vector<int> [realProducts.size ()];

	for (int i=0; i< realProducts.size (); i++)
	{
		MySpecies* s = realProducts[i];

		set<string> chainLabel;
		for (int j =0; j < s->getNumOfChains (); j++)
			chainLabel.insert (s->getChain (j)->getLabel ());

		vector<int> degenerate;
		for (int j =0; j < listOfMyProducts.size (); j++)
		{
			MySpecies* templateProduct = listOfMyProducts[i];
			for (int k=0; k < templateProduct->getNumOfChains (); k++)
			{
				string label = templateProduct->getChain (k)->getLabel ();
				if (chainLabel.count (label))
				{
					degenerate.push_back (j);
					break;
				}
			}
		}

		assert (degenerate.size () >= 1);
		dGp[i] = degenerate;
	}

	cout << "\ndGp[0]= " << dGp[0][0] << endl;

	double* stoiMath = new double[listOfMyProducts.size ()];

	for (int i=0; i < realProducts.size (); i++)
	{
		MySpecies* s = realProducts[i];
		double stoi = 1.0/dGp[i].size ();

		//	for each species in listOfMyProducts
		for (int j=0; j < dGp[i].size (); j++)
		{
			/**
			 * new species 
			 */
			MySpecies* newsp (s);

			/**
			 * dGp[i] store index of products templateProduct included in real product i
			 */
			int sindex = dGp[i][j];
			MySpecies* templateProduct = listOfMyProducts[sindex];
			stoiMath[sindex] = stoi;

			/**
			 * set compartment
			 */
			string compId_tm = templateProduct->getCompartment ();
			if (RT->mmapIndexReactants.count (compId_tm))
			{
				/**
				 * take care!
				 * since all reactants have the same compartment,
				 * so we just choose one to find its compartment identifier in reality
				 */
				int index = RT->mmapIndexReactants.find(compId_tm)->second;
				string compId = listOfMyReactants[index]->getCompartment ();
				newsp->setCompartment (compId);
			}
			else if (RT->mmapIndexProducts.count (compId_tm))
			{
				/**
				 * take care!
				 * since all products have the same compartment,
				 * so we just choose one to find its compartment identifier in reality
				 */
				int index = RT->mmapIndexModifiers.find(compId_tm)->second;
				string compId = listOfMyModifiers[index]->getCompartment ();
				newsp->setCompartment (compId);
			}
			else throw StrCacuException (
					"Generating Products: No Compartment found for Products!"
					);

			//  add to speciesList
			for (int k=0; k < listOfMyCompartments.size (); k++)
			{
				MyCompartment* mycomp = listOfMyCompartments[k];
				if (mycomp->getId () == newsp->getCompartment ()) 
				{
					MySpecies* sEx = mycomp->isMySpeciesIn (newsp);
					if (sEx == NULL)
					{
						newsp->rearrange ();
						listOfMySpecies.push_back (newsp);
						mycomp->addMySpeciesIn (newsp);
					}
					else
					{
						delete newsp;
						newsp = sEx;
					}
					break;
				}
			}

			//
			//  add replacement
			//
			replaceTable[templateProduct->getDB_Label ()] = newsp->getId ();


			//  delete old species and replaced with new one
			delete templateProduct;
			templateProduct = newsp;
		}

		delete s;
	}

	delete [] dGp;

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
	for (int i=0; i < RT->listOfParameters.size (); i++)
	{
		kl->addParameter (RT->listOfParameters[i]);
	}

	//  setMath
	string mathXMLString = RT->math;

	map<string,string>::const_iterator itMath = replaceTable.begin ();
	while (itMath != replaceTable.end ())
	{
		string::size_type posP = mathXMLString.find (itMath->first);
		if (posP != string::npos)
			mathXMLString.replace (
					posP, itMath->first.size (), itMath->second
					);
		itMath ++;
	}

	ASTNode* astMath = readMathMLFromString(mathXMLString.c_str());
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

