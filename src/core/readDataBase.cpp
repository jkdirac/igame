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
		const bool& direction
		)
{
	string head ("/MoDeL/reaction");

	if (doc.empty ())
		throw StrCacuException (
				"Reading Reaction...No ID Specified!"
				);

	vector<string> temp;

	//	read attribute Id
	string id;
	const string pathId = head + "/@id";
	get_node_attr (REACTION, &doc, &pathId, temp);
	if (temp.empty ())
	{
		string errno = string (
				"REACTION: empty attribute id in "
				) + doc + ".xml!";
		throw StrCacuException (errno);
	}
	else id = temp[0];

	if (id != doc)
		throw StrCacuException (
				"Reading Reaction...Inconsistent ID!"
				);

	RT->setId (id);

	//	read attribute name
	string name;
	const string pathName = head + "/@name";
	get_node_attr (REACTION, &doc, &pathName, temp);
	if (!temp.empty ()) name = temp[0];
	RT->setName (name);

	//	read attribute Reversible
	bool reversible;
	const string pathRev = head + "/@reversible";
	get_node_attr (REACTION, &doc, &pathRev, temp);
	if (!temp.empty ()) reversible = (temp[0] == "true");
	else reversible = true;

	if (!direction && !reversible) 
		throw StrCacuException (
				"Reactions shuold not be linked"
				" to Products in Irreversible cases!"
				);
	RT->setReversible (reversible);

	//	read attribute fast
	bool fast;
	const string pathFast = head + "/@fast";
	get_node_attr (REACTION, &doc, &pathFast, temp);
	if (!temp.empty ()) fast = (temp[0] == "true");
	else fast = false;
	RT->setFast (fast);

	//readReactionCompartments
	const string pathComp = head + "/listOfCompartments/compartment";
	int numOfComps = get_node_element_num (REACTION, &doc, &pathComp);
	for (int cnt =1; cnt <= numOfComps; cnt++)
	{
		string compartmentRef, currComp, parComp;
		readCompartment (REACTION, doc, pathComp, cnt, compartmentRef, currComp, parComp);
		RT->addCompartment (compartmentRef, currComp, parComp);
	}

	//readReactionSpecies
	//(1) read reactants
	
	string pathReactants = head;
	if (direction)  pathReactants += "/listOfReactants/reactant";
	else pathReactants += "/listOfProducts/product";
	int numOfReactants = get_node_element_num (
			REACTION, &doc, &pathReactants
			);

	for (int cnt =1; cnt <= numOfReactants; cnt++)
	{
		string speciesReference, speciesLabel, compartmentLabel;
		int relation;
		readSpecies (
				REACTION, doc, pathReactants, cnt,
				speciesReference, speciesLabel, 
				compartmentLabel, relation
				);

		const string path_cnModel = "/MoDeL/species";
		MySpecies* s = new MySpecies;
		s->setDbId (speciesReference);
		s->setLabel (speciesLabel);
		if (relation == 1) s->setCCid (compartmentLabel);
		read_cnModel (s, SPECIES, speciesReference, path_cnModel, true); 

		if (direction) RT->addReactant (s, compartmentLabel);
		else RT->addProduct (s, compartmentLabel);
	}

	//(2) read products
	string pathProducts (head);
	if (direction) pathProducts += "/listOfProducts/product";
	else pathProducts += "/listOfReactants/reactant";
	int numOfProducts = get_node_element_num (REACTION, &doc, &pathProducts);

	for (int cnt =1; cnt <= numOfProducts; cnt++)
	{
		string speciesReference, speciesLabel, compartmentLabel;
		int relation;

		readSpecies (
				REACTION, doc, pathProducts, cnt,
				speciesReference, speciesLabel, 
				compartmentLabel, relation
				);

		const string path_cnModel = "/MoDeL/species";
		MySpecies* s = new MySpecies;
		s->setDbId (speciesReference);
		s->setLabel (speciesLabel);
		if (relation == 1) s->setCCid (compartmentLabel);
		read_cnModel (s, SPECIES, speciesReference, path_cnModel, true); 

		if (direction) RT->addProduct (s, compartmentLabel);
		else RT->addReactant (s, compartmentLabel);
	}

	//(3) read Modifier
	const string pathModifier = head + "/listOfModifiers/modifier";
	int numOfModifiers = get_node_element_num (REACTION, &doc, &pathModifier);

	for (int cnt =1; cnt <= numOfModifiers; cnt++)
	{
		string speciesReference, speciesLabel, compartmentLabel;
		int relation;
		readSpecies (
				REACTION, doc, pathModifier, cnt,
				speciesReference, speciesLabel, 
				compartmentLabel, relation
				);

		const string path_cnModel = "/MoDeL/species";
		MySpecies* s = new MySpecies;
		s->setDbId (speciesReference);
		s->setLabel (speciesLabel);
		if (relation == 1) s->setCCid (compartmentLabel);
		read_cnModel (s, SPECIES, speciesReference, path_cnModel, true); 
		RT->addModifier (s, compartmentLabel);
	}

	//read substituent transfer table
	vector< pair<string,string> > source;
	vector< pair<string,string> > destin;
	const string pathTransfer = head + 
		"/listOfSubstituentTransfers/substituentTransfer";
	int numOfTrans = get_node_element_num (REACTION, &doc, &pathTransfer);

	for (int cnt= 1; cnt <= numOfTrans; cnt++)
	{
		pair<string,string> from, to;
		readTransfer (REACTION, doc, pathTransfer, cnt, from, to);
		RT->addSubstituentTransfer (from, to);
	}

	//	read KineticLaw
	string pathKineticLaw;
	if (direction) pathKineticLaw = head + "/forwardKineticLaw";
	else pathKineticLaw = head + "/reverseKineticLaw";

	//	read math
	string math;

	const string pathMath = pathKineticLaw + "/math";
	get_node (REACTION, &doc, &pathMath, math); 

	if (math.empty ())
		throw StrCacuException (
				"Reading Reaction...No Math Specified!"
				);

	RT->setMath (math);

	//	read local parameters
	const string pathLocalPara = 
		pathKineticLaw + "/listOfLocalParameters/localParameter";
	const int numOfLocalParas = get_node_element_num (
			REACTION, &doc, &pathLocalPara
			);

	for (int i=1; i <= numOfLocalParas; i++)
	{
		string db, id, name, units;
		double value;
		bool constant;

		readParameter (REACTION, doc, pathLocalPara, i, db, id,
			   name, value, units, constant);

		Parameter* para = new Parameter (2,4);
		setParameter (para, id, name, value, units, constant);
		RT->addParameter (para);
	}

	//	read referenced parameters
	const string pathExtRef = 
		pathKineticLaw + "/listOfReferencedParameters/referencedParameter";
	const int numOfRefParas = get_node_element_num (
			REACTION, &doc, &pathExtRef
			);

	for (int i=1; i <= numOfRefParas; i++)
	{
		string id, partLabel, speciesLabel, parameterLabel, formula;
		readExternalRef (
				REACTION, doc, pathExtRef, i, id, 
				speciesLabel, partLabel, parameterLabel
				);

		//	find species 
		const MySpecies* s = RT->getSpecies (speciesLabel);
		if (s == NULL)
			throw StrCacuException (
					string ("REACTION: No species existed with label ")
					+ speciesLabel + "!"
					);
		string compartmentLabel = s->getCompartment ();

		string units, name;
		double value;

		const Part* p = s->getPart (partLabel);
		readConditionalParameter (
				PART, p->getPartCategory (),
				p->getPartLabel (), parameterLabel,
			    compartmentLabel, value, units, name
				);

		Parameter* para = new Parameter (2,4);
		setParameter (para, id, name, value, units, true);
		RT->addParameter (para);
	}
	
	//	read listOfConstraints
	const string pathConstraint = 
		pathKineticLaw + "/listOfConstraints/constraint";
	const int numOfConstraints = get_node_element_num (
			REACTION, &doc, &pathConstraint
			);

	for (int i=1; i <= numOfConstraints; i++)
	{
		vector<string> variables;
		string formula;
		readConstraint (REACTION, doc, pathConstraint,
				i, variables, formula);
		RT->addConstraint (variables, formula);
	}

	return;
}
