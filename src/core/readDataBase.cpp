#include "readDataBase.h"

void readDataBase::read_cnModel (
		MySpecies* s,
		const container_index& cind,
		const string& doc,
		const string& qp,
		const bool& isTemplate
		)
{
	//read tree map
	string qpt = qp + "/cnModel/listOfTrees/tree";
//    cout << qpt << endl;
	int numOfTrees = get_node_element_num (cind, &doc, &qpt);

	for (int itree = 1; itree <= numOfTrees; itree++)
	{
		//create an empty tree
		Tree* t = s->createTree ();

		//read nodes 
		ostringstream oss;
		oss << qpt << "[" << itree << "]/listOfNodes/node";
		string qpn (oss.str ());
		int numOfNodes = get_node_element_num (cind, &doc, &qpn);

		for (int inode = 1; inode <= numOfNodes; inode++)
		{
			string nCL, nPL;
			readNode (cind, doc, qpn, inode, nCL, nPL);

			//create an empty node
			Node* n = t->createNode (nCL, nPL);
			t->addNodeMap (n);
		}

		//add Children of each node
		t->addNodeChildren ();	
	}

	//read chains
	string qpc = qp + "/cnModel/listOfChains/chain";
	int numOfChains = get_node_element_num (cind, &doc, &qpc);
//    cout << "\nnumOfChains = " << numOfChains << endl;

	for (int ichain = 1; ichain <= numOfChains; ichain++)
	{
		//create an empty chain
		Chain* c = s->createChain ();

		//read parts 
		ostringstream oss;
		oss << qpc << "[" << ichain << "]/listOfParts/part";
		string qpp (oss.str ());
		int numOfParts = get_node_element_num (cind, &doc, &qpp);
//        cout << "\nnumOfParts = " << numOfParts << endl;

		for (int ipart = 1; ipart <= numOfParts; ipart++)
		{
			string pR, pL, pT, pC;
			readPart (cind, doc, qpp, ipart, pR, pL, pT, pC); 
			if (pT == "substituent" && !isTemplate)
				throw StrCacuException (
						"Reading Block cnModel..."
						"Non-Template species is required!"
						);
			else
			{
				bool isBinded = s->countBindedNode (pL);
				c->createPart (pR, pL, pT, pC, isBinded);
			}
		}
	}
	return;
}

void readDataBase::setParameter (
		Parameter* para,
		const string& id,
		const string& name,
		const double& value,
		const string& units,
		const bool& constant
		) const
{
	int operation = LIBSBML_OPERATION_SUCCESS;

	//
	//  setId
	//
	operation = para->setId (id); 
	if (operation == LIBSBML_INVALID_ATTRIBUTE_VALUE)
		throw StrCacuException (
				"Reading Block Parameter..."
				"Invalid Attribute Value: id!"
				);

	//
	//  setName
	//
	if (!name.empty ())
	{
		operation = para->setName (name);
		if (operation == LIBSBML_INVALID_ATTRIBUTE_VALUE)
			throw StrCacuException (
					"Reading Block Parameter..."
					"Invalid Attribute Value: name!"
					);
	}

	//
	//  setValue
	//
	operation = para->setValue (value);

	//
	//  setUnits
	//  
	if (!units.empty ())
	{
		operation = para->setUnits (units);
		if (operation == LIBSBML_INVALID_ATTRIBUTE_VALUE)
			throw StrCacuException (
					"Reading Block Parameter..."
					"Invalid Attribute Value: units!"
					);
	}

	//
	//  setConstant
	//
	operation = para->setConstant (constant);
	if (operation == LIBSBML_UNEXPECTED_ATTRIBUTE)
		throw StrCacuException (
				"Reading Block Parameter..."
				"Unexpected Attribute: constant!"
				);

	return;
}

void readDataBase::setAlgebraicRule (
		AlgebraicRule* alger,
		const string& variable,
		const string& math
		) const
{
	int operation = LIBSBML_OPERATION_SUCCESS;

	//
	//  setVariable
	//
	operation = alger->setVariable (variable); 
	if (operation == LIBSBML_INVALID_ATTRIBUTE_VALUE)
		throw StrCacuException (
				"Reading Block AlgebraicRule..."
				"Invalid Attribute Value: variable!"
				);
	if (operation == LIBSBML_UNEXPECTED_ATTRIBUTE)
		throw StrCacuException (
				"Reading Block AlgebraicRule..."
				"Unexpected Attribute Value: variable!"
				);

	//
	//  setFormula
	//
	operation = alger->setFormula (math);
	if (operation == LIBSBML_INVALID_OBJECT)
		throw StrCacuException (
				"Reading Block AlgebraicRule..."
				"Invalid Object: math!"
				);

	return;
}

void readDataBase::setAssignmentRule (
		AssignmentRule* assr,
		const string& variable,
		const string& math
		) const
{
	int operation = LIBSBML_OPERATION_SUCCESS;

	//
	//  setVariable
	//
	operation = assr->setVariable (variable); 
	if (operation == LIBSBML_INVALID_ATTRIBUTE_VALUE)
		throw StrCacuException (
				"Reading Block AssignmentRule..."
				"Invalid Attribute Value: variable!"
				);
	if (operation == LIBSBML_UNEXPECTED_ATTRIBUTE)
		throw StrCacuException (
				"Reading Block AssignmentRule..."
				"Unexpected Attribute Value: variable!"
				);

	//
	//  setFormula
	//
	operation = assr->setFormula (math);
	if (operation == LIBSBML_INVALID_OBJECT)
		throw StrCacuException (
				"Reading Block AssignmentRule..."
				"Invalid Object: math!"
				);

	return;
}

void readDataBase::setRateRule (
		RateRule* rater,
		const string& variable,
		const string& math
		) const
{
	int operation = LIBSBML_OPERATION_SUCCESS;

	//
	//  setVariable
	//
	operation = rater->setVariable (variable); 
	if (operation == LIBSBML_INVALID_ATTRIBUTE_VALUE)
		throw StrCacuException (
				"Reading Block RateRule..."
				"Invalid Attribute Value: variable!"
				);
	if (operation == LIBSBML_UNEXPECTED_ATTRIBUTE)
		throw StrCacuException (
				"Reading Block RateRule..."
				"Unexpected Attribute Value: variable!"
				);

	//
	//  setFormula
	//
	operation = rater->setFormula (math);
	if (operation == LIBSBML_INVALID_OBJECT)
		throw StrCacuException (
				"Reading Block RateRule..."
				"Invalid Object: math!"
				);

	return;
}

void readDataBase::setCompartment (
		MyCompartment* comp,
		const string& db,
		const string& id,
		const string& name,
		const int& spatialDimensions,
		const double& size,
		const string& units,
		const string& outside,
		const bool& constant
		) const
{
	int operation = LIBSBML_OPERATION_SUCCESS;

	//
	//  setDbId 
	//
	comp->setDbId (db); 

	//
	//  setId 
	//
	operation = comp->setId (id);
	if (operation == LIBSBML_INVALID_ATTRIBUTE_VALUE)
		throw StrCacuException (
				"Reading Block Compartment..."
				"Invalid Attribute Value: id!"
				);

	//
	//	setName
	//
	if (!name.empty ())
	{
		operation = comp->setName (name);
		if (operation == LIBSBML_INVALID_ATTRIBUTE_VALUE)
			throw StrCacuException (
					"Reading Block Compartment..."
					"Invalid Attribute Value: name!"
					);
	}

	//
	//  setSpatialDimensions
	//
	operation = comp->setSpatialDimensions (spatialDimensions);
	if (operation == LIBSBML_INVALID_ATTRIBUTE_VALUE)
		throw StrCacuException (
				"Reading Block Compartment..."
				"Invalid Attribute Value: "
				"spatialDimensions!"
				);
	if (operation == LIBSBML_UNEXPECTED_ATTRIBUTE)
		throw StrCacuException (
				"Reading Block Compartment..."
				"Unexpected Attribute Value: "
				"spatialDimensions!"
				);

	//
	//  setSize
	//
	if (size >= 0.0) comp->setSize (size);

	//
	//  setUnits
	//
	if (!units.empty ())
	{
		operation = comp->setUnits (units);
		if (operation == LIBSBML_INVALID_ATTRIBUTE_VALUE)
			throw StrCacuException (
					"Reading Block Compartment..."
					"Invalid Attribute Value: units!"
					);
	}

	//
	//  setOutside
	//
	operation = comp->setOutside (outside);	
	if (operation == LIBSBML_INVALID_ATTRIBUTE_VALUE)
			throw StrCacuException (
					"Reading Block Compartment..."
					"Invalid Attribute Value: units!"
					);

	//
	//  setConstant
	//
	operation = comp->setConstant (constant);
	if (operation == LIBSBML_UNEXPECTED_ATTRIBUTE)
			throw StrCacuException (
					"Reading Block Compartment..."
					"Invalid Attribute Value: constant!"
					);

	return;
}

void readDataBase::setSpecies (
		MySpecies* s,
		const string& db,
		const string& ccid,
		const string& id,
		const string& name,
		const string& compartment,
		const double& initialAmount,
		const double& initialConcentration,
		const string& substanceUnits,
		const bool& hasOnlySubstanceUnits,
		const bool& boundaryCondition,
		const int& charge,
		const bool& constant
		) const
{
	int operation = LIBSBML_OPERATION_SUCCESS;

	//
	//  setDbId 
	//
	s->setDbId (db); 

	//
	//	setCCid
	//
	s->setCCid (ccid);

	//
	//  setId 
	//
	operation = s->setId (id);
	if (operation == LIBSBML_INVALID_ATTRIBUTE_VALUE)
		throw StrCacuException (
				"Reading Block Species..."
				"Invalid Attribute Value: id!"
				);

	//
	//  setName 
	//
	if (!name.empty ())
	{
		operation = s->setName (name);
		if (operation == LIBSBML_INVALID_ATTRIBUTE_VALUE)
			throw StrCacuException (
					"Reading Block Species..."
					"Invalid Attribute Value: name!"
					);
	}

	//
	//  setCompartment
	//
	operation = s->setCompartment (compartment);
	if (operation == LIBSBML_INVALID_ATTRIBUTE_VALUE)
		throw StrCacuException (
				"Reading Block Species..."
				"Invalid Attribute Value: compartment!"
				);

	//
	//  setInitialAmount
	//
	if (initialAmount >= 0.0) 
		operation = s->setInitialAmount (initialAmount);

	//
	//  setInitialConcentration
	//
	if (initialConcentration >= 0.0) 
	{
		operation = s->setInitialConcentration (initialAmount);
		if (operation == LIBSBML_UNEXPECTED_ATTRIBUTE)
			throw StrCacuException (
					"Reading Block Species..."
					"Unexpected Attribute: initialConcentration!"
					);
	}

	//
	//  setSubstanceUnits
	//
	if (!substanceUnits.empty ())
	{
		operation = s->setSubstanceUnits (substanceUnits);
		if (operation == LIBSBML_INVALID_ATTRIBUTE_VALUE)
			throw StrCacuException (
					"Reading Block Species..."
					"Invalid Attribute Value: substanceUnits!"
					);
	}

	//
	//  setHasOnlySubstanceUnits
	//
	operation = s->setHasOnlySubstanceUnits (hasOnlySubstanceUnits);
	if (operation == LIBSBML_UNEXPECTED_ATTRIBUTE)
		if (operation == LIBSBML_UNEXPECTED_ATTRIBUTE)
			throw StrCacuException (
					"Reading Block Species..."
					"Unexpected Attribute: hasOnlySubstanceUnits!"
					);

	//
	//  setBoundaryCondition
	//
	s->setBoundaryCondition (boundaryCondition);

	//
	//  setCharge
	//
	if (charge != 0)
	{
		operation = s->setCharge (charge);
		if (operation == LIBSBML_UNEXPECTED_ATTRIBUTE)
			throw StrCacuException (
					"Reading Block Species..."
					"Unexpected Attribute: charge!"
					);
	}

	//
	//  setConstant
	//
	operation = s->setConstant (constant);
	if (operation == LIBSBML_UNEXPECTED_ATTRIBUTE)
		if (operation == LIBSBML_UNEXPECTED_ATTRIBUTE)
			throw StrCacuException (
					"Reading Block Species..."
					"Unexpected Attribute: constant!"
					);

	return;
}

void readDataBase::setUnit (
		UnitDefinition* unitdef,
		const string& id,
		const string& name
		) const
{
	int operation = LIBSBML_OPERATION_SUCCESS;

	//
	//  setId
	//
	operation = unitdef->setId (id);
	if (operation == LIBSBML_INVALID_ATTRIBUTE_VALUE)
		throw StrCacuException (
				"Reading Block UnitDefinition..."
				"Invalid Attribute Value: id!"
				);

	//
	//  setName
	//
	if (!name.empty ())
	{
		operation = unitdef->setName (name);
		if (operation == LIBSBML_INVALID_ATTRIBUTE_VALUE)
			throw StrCacuException (
					"Reading Block UnitDefinition..."
					"Invalid Attribute Value: name!"
					);
	}
}

void readDataBase::setUnit (
		Unit* unit,
		const UnitKind_t& kind, 
		const double& exponent,
		const int& scale, 
		const double& multiplier
		) const
{
	int operation = LIBSBML_OPERATION_SUCCESS;

	//
	//  setKind
	//
	operation = unit->setKind (kind);
	if (operation == LIBSBML_INVALID_ATTRIBUTE_VALUE)
		throw StrCacuException (
				"Reading Block Unit..."
				"Invalid Attribute Value: kind!"
				);

	//
	//  setExponent
	//
	unit->setExponent (exponent);

	//
	//  setScale
	//
	unit->setScale (scale);

	//
	//  setMultiplier
	//
	operation = unit->setMultiplier (multiplier);
	if (operation == LIBSBML_UNEXPECTED_ATTRIBUTE)
		throw StrCacuException (
				"Reading Block Unit..."
				"Unexpected Attribute: multiplier!"
				);
}

void readDataBase::setFunction (
		FunctionDefinition* fdef,
		const string& id,
		const string& name,
		const string& math
		) const
{
	int operation = LIBSBML_OPERATION_SUCCESS;
	string errno = "Reading Block FunctionDefinition...";

	//
	//  setId
	//
	operation = fdef->setId (id);
	if (operation == LIBSBML_INVALID_ATTRIBUTE_VALUE)
		throw StrCacuException (
				"Reading Block FunctionDefinition..."
				"Invalid Attribute Value: id!"
				);

	//
	//  setName
	//
	if (!name.empty ())
	{
		operation = fdef->setName (name);
		if (operation == LIBSBML_INVALID_ATTRIBUTE_VALUE)
			throw StrCacuException (
					"Reading Block FunctionDefinition..."
					"Invalid Attribute Value: name!"
					);
	}

	//
	//  setMath
	//
	ASTNode* astMath = readMathMLFromString(math.c_str());
	if (astMath == NULL) 
		throw StrCacuException (
				"Reading Block FunctionDefinition..."
				"Null or Invalid Attribute Value: math!"
				);

	operation = fdef->setMath(astMath);
	if (operation == LIBSBML_INVALID_OBJECT)
		throw StrCacuException (
				"Reading Block FunctionDefinition..."
				"Invalid Object: astMath!"
				);
	delete astMath;
}

void readDataBase::readReactionTemplate (
		reactionTemplate* RT,
		const string& doc,
		const bool& redir
		)
{
	if (doc.empty ())
	{
		string errno ("Reading Reaction...No ID Specified!");
		throw errno;
	}

	string qp ("/sbpmodel/reaction");
	string qpath;

	//read element Id
	string id;
//    nodeQuery (REACTION, doc, qpath, 0, "id", id);
	RT->setId (id);

	//read element Name
	string name;
//	nodeQuery (REACTION, doc, qpath, 0, "name", name);
	RT->setName (name);

	//read element Reversible
	string reversible;
//    nodeQuery (REACTION, doc, qpath, 0, "reversible", reversible);
	bool rev = (reversible == "true");
	RT->setReversible (rev);
	if (!redir && !rev) 
	{
		string errno ("Reactions shuold not be linked"
				" to Products in Irreversible cases!");
		throw errno;
	}

	//read element fast
	string fast;
//    nodeQuery (REACTION, doc, qpath, 0, "fast", fast);
	RT->setFast (fast == "true");

	//readReactionCompartments
	qpath = qp + "/listOfCompartments/compartment";
	int numOfComps = get_node_element_num (REACTION, &doc, &qpath);
	for (int cnt =1; cnt <= numOfComps; cnt++)
	{
		string compartmentRef, currComp, parComp;
		readCompartment (REACTION, doc, qpath, cnt, compartmentRef, currComp, parComp);
		RT->addCompartment (compartmentRef, currComp, parComp);
	}

	//readReactionSpecies
	//(1) read reactants
	if (redir) qpath = qp + "/listOfReactants/reactant";
	else qpath = qp + "/listOfProducts/product";
	int numOfRs = get_node_element_num (REACTION, &doc, &qpath);

	for (int cnt =1; cnt <= numOfRs; cnt++)
	{
		string speciesReference, speciesLabel, compartmentLabel;
		readSpecies (REACTION, doc, qpath, cnt,
				speciesReference, speciesLabel, compartmentLabel);

		MySpecies* s = new MySpecies;
		s->setDbId (speciesReference);
		s->setLabel (speciesLabel);

//        readSpecies_db (s);

		if (redir) RT->addReactant (s, compartmentLabel);
		else RT->addProduct (s, compartmentLabel);
	}

	//(1) read Compartments

	//(2) read products
	if (redir) qpath = qp + "/listOfProducts/product";
	else qpath = qp + "/listOfReactants/reactant";
	int numOfPs = get_node_element_num (REACTION, &doc, &qpath);

	for (int cnt =1; cnt < numOfPs; cnt++)
	{
		string speciesReference, speciesLabel, compartmentLabel;
		readSpecies (REACTION, doc, qpath, cnt,
				speciesReference, speciesLabel, compartmentLabel);

		MySpecies* s = new MySpecies;
		s->setDbId (speciesReference);
		s->setLabel (speciesLabel);

//        readSpecies_db (s);

		if (redir) RT->addProduct (s, compartmentLabel);
		else RT->addReactant (s, compartmentLabel);
	}

	//(3) read Modifier
	qpath = qp + "/listOfModifiers/modifier";
	int numOfMs = get_node_element_num (REACTION, &doc, &qpath);

	for (int cnt =1; cnt < numOfMs; cnt++)
	{
		qpath += "/modifier";
		string speciesReference, speciesLabel, compartmentLabel;
		readSpecies (REACTION, doc, qpath, cnt,
				speciesReference, speciesLabel, compartmentLabel);

		MySpecies* s = new MySpecies;
		s->setDbId (speciesReference);
		s->setLabel (speciesLabel);

//        readSpecies_db (s);
		RT->addModifier (s, compartmentLabel);
	}

	//read substituent transfer table
	vector< pair<string,string> > source;
	vector< pair<string,string> > destin;
	qpath = qp + "/listOfSubstituentTransfers/substituentTransfer";
	int numOfTrans = get_node_element_num (REACTION, &doc, &qpath);

	for (int cnt=0; cnt < numOfTrans; cnt++)
	{
		pair<string,string> from, to;
		readTransfer (REACTION, doc, qpath, cnt, from, to);
		RT->addSubstituentTransfer (from, to);
	}

	//read KineticLaw
	if (redir) qpath = qp + "/forwardKineticLaw";
	else qpath = qp + "/reverseKineticLaw";

	//read math
	string math;

	string nodepath = qpath + "/math";
	get_node (REACTION, &doc, &nodepath, math); 

	if (math.empty ())
	{
		string errno ("Reading Reaction...No Math Specified!");
		throw errno;
	}

	RT->setMath (math);
}
