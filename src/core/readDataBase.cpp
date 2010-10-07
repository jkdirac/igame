#include "readDataBase.h"

readDataBase::readDataBase ()
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

readDataBase::~readDataBase () {}

UnitKind_t readDataBase::getUnitKind_t (
		const string& unit
		) const
{
	if (unitMap.count (unit)) 
		return unitMap.find (unit)->second;
	else return unitMap.find ("invalid")->second;
}

void readDataBase::read_cnModel (
		MySpecies* s,
		const container_index& cind,
		const string& doc,
		const string& nodepath,
		const bool& isTemplate
		)
{
	//	============
	//	read chains
	//	============
	
	string pathChain = nodepath + "/cnModel/listOfChains/chain";
	int numOfChains = get_node_element_num (cind, &doc, &pathChain);

	//
	//	some examinations is needed
	//	(1) partLabel on chains should be unique
	//	(2) nodeLabel of leaf nodes shuold be defined previously 
	//
	set<string> __label_set;

	for (int ichain = 1; ichain <= numOfChains; ichain++)
	{
		/**
		 * create an empty chain
		 * !no need to generate chain label here
		 */
		Chain* c = s->createChain ();

		//read parts 
		ostringstream oss;
		oss << pathChain << "[" << ichain << "]/listOfParts/part";
		string pathPart (oss.str ());
		int numOfParts = get_node_element_num (cind, &doc, &pathPart);

		for (int ipart = 1; ipart <= numOfParts; ipart++)
		{
			string __ref, __label, __type, __ctg;
			readPart (cind, doc, pathPart, ipart, 
					__ref, __label, __type, __ctg); 

			//
			//	TIPS:
			//
			//	1. if __label is empty, program will automatically 
			//	generate one. 
			//	2. __type is mandatory if it is not a substituent-type part
			//

			if (__label_set.count (__label))
				throw StrCacuException (
						"Species: partLabel should be unique within"
						"one species cnModel definition!"
						);
			else if (__label == "ROOT") throw StrCacuException (
					"partLabel could not be \"ROOT\""
					);
			else __label_set.insert (__label);

			//	it is not allow species with substituent-type part
			//	if it is not a template species
			if (__ctg == "substituent" && !isTemplate)
				throw StrCacuException (
						"Reading Block cnModel..."
						"Non-Template species is required!"
						);
			else
			{
				//	attribute isBinded will be set after tree nodes have been read in
				Part* p = c->createPart ();
				p->setPart (__ref, __label, __type, __ctg);
			}
		}
	}

	//read tree map
	string pathTree = nodepath + "/cnModel/listOfTrees/tree";
	int numOfTrees = get_node_element_num (cind, &doc, &pathTree);

	//	all parent nodes at least have two children
	set<string> __leaf;
	set<string> __all;	// "ROOT" node would not be added

	for (int itree = 1; itree <= numOfTrees; itree++)
	{
		//	create an empty tree
		Tree* t = s->createTree ();

		//	read nodes 
		ostringstream oss;
		oss << pathTree << "[" << itree << "]/listOfNodes/node";
		string pathNode (oss.str ());
		int numOfNodes = get_node_element_num (cind, &doc, &pathNode);

		//	Node labels of the tree should never be the same to nodes in
		//	other trees
		set<string> __prev (__all);
		map<string, int> __parent;

		for (int inode = 1; inode <= numOfNodes; inode++)
		{
			string child, parent;
			readNode (cind, doc, pathNode, inode, child, parent);

			//	ROOT could not be child
			if (child == "ROOT") throw StrCacuException (
					"\"ROOT\" could not be a child!"
					);

			if (!__label_set.count (child))
			{
				string errno ("No corresponded part found for Node: ");
				errno += child + "with same Label!";
				throw StrCacuException (errno);
			}

			if (__label_set.count (parent))
			{
				string errno ("Invalid Parent Node; ");
				errno += parent + ", conflict with partLabel!";
				throw StrCacuException (errno);
			}

			//create an empty node
			if (__all.count (child))
			{
				string errno ("\nNode Label: ");
				errno += child + " has been defined already!";
				throw StrCacuException (errno);
			}
			else if (__prev.count (parent))
			{
				string errno ("\nNode Label: ");
				errno += parent + " has been defined already!";
				throw StrCacuException (errno);
			}
			else
			{
				//	insert child
				__leaf.insert (child);
				__all.insert (child);

				//	insert parent (ROOT will not be added)
				if (parent != "ROOT")
				{
					if (__parent.count (parent)) __parent[parent]++;
					else {__parent[parent] = 1;	__all.insert (parent);}
				}

				//	create Node
				t->createNode (child, parent);
			}
		}

		//	check if all parents have more than one children (except "ROOT")
		map<string, int>::iterator first= __parent.begin ();
		while (first != __parent.end ())
		{
			if (first->second == 1) 
			{
				string errno ("Invalid Parent Node: ");
				errno += first->first + ". At least 2 children are required!";
				throw StrCacuException (errno);
			}
			first ++;
		}

		//add Children of each node
		t->addNodeChildren ();	

		//	check if the tree is itself as a whole 
		t->checkIntegrated ();
	}

	//	find binded part
	for (int ichain=0; ichain < s->getNumOfChains (); ichain++)
	{
		bool alone = false;

		Chain* c = s->getChain (ichain);
		for (int ipart = 0; ipart < c->getNumOfParts (); ipart++)
		{
			Part* p = c->getPart (ipart);
			string __part_label = p->getPartLabel ();
			if (__leaf.count (__part_label)) p->setIsBinded (true);
			else p->setIsBinded (false);
		}

		//	any chain must be 
		if (!alone && s->getNumOfChains () >1) 
			throw StrCacuException ("Not a species ALONE!");
	}

	//	ok, fine strcuture
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
		const string& math,
		const bool& text
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
	if (text)
	{
		operation = alger->setFormula (math);
		if (operation == LIBSBML_INVALID_OBJECT)
			throw StrCacuException (
					"Reading Block AlgebraicRule..."
					"Invalid Object: math!"
					);
	}
	else 
	{
		ASTNode* astMath = readMathMLFromString(math.c_str());
		if (astMath == NULL) 
			throw StrCacuException ("Invalid MathML string converted!");
		operation = alger->setMath (astMath);
		if (operation == LIBSBML_INVALID_OBJECT)
			throw StrCacuException (
					"Writing Block Reaction...Invalid object: astMath!"
					);
	}

	return;
}

void readDataBase::setAssignmentRule (
		AssignmentRule* assr,
		const string& variable,
		const string& math,
		const bool& text
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
	if (text)
	{
		operation = assr->setFormula (math);
		if (operation == LIBSBML_INVALID_OBJECT)
			throw StrCacuException (
					"Reading Block AssignmentRule..."
					"Invalid Object: math!"
					);
	}
	else 
	{
		ASTNode* astMath = readMathMLFromString(math.c_str());
		if (astMath == NULL) 
			throw StrCacuException ("Invalid MathML string converted!");
		operation = assr->setMath (astMath);
		if (operation == LIBSBML_INVALID_OBJECT)
			throw StrCacuException (
					"Writing Block Reaction...Invalid object: astMath!"
					);
	}

	return;
}

void readDataBase::setRateRule (
		RateRule* rater,
		const string& variable,
		const string& math,
		const bool& text
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
	if (text)
	{
		operation = rater->setFormula (math);
		if (operation == LIBSBML_INVALID_OBJECT)
			throw StrCacuException (
					"Reading Block RateRule..."
					"Invalid Object: math!"
					);
	}
	else 
	{
		ASTNode* astMath = readMathMLFromString(math.c_str());
		if (astMath == NULL) 
			throw StrCacuException ("Invalid MathML string converted!");
		operation = rater->setMath (astMath);
		if (operation == LIBSBML_INVALID_OBJECT)
			throw StrCacuException (
					"Writing Block Reaction...Invalid object: astMath!"
					);
	}

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
	//  setDB_ref
	//
	comp->setDB_ref (db); 

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
	//  set database reference 
	//
	if (!db.empty ()) s->setDB_ref (db); 

	//
	//	set id of compartment-type species
	//
	if (!ccid.empty ()) s->setCompTypeId (ccid);

	//
	//  setId 
	//
	operation = s->setId (id);
	if (operation == LIBSBML_INVALID_ATTRIBUTE_VALUE)
	{
		cout << "\nid = " << id << endl;
		throw StrCacuException (
				"Reading Block Species..."
				"Invalid Attribute Value: id!"
				);
	}

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
	{
		cout << "\nmath = " << math << endl;
		throw StrCacuException (
				"Reading Block FunctionDefinition..."
				"Null or Invalid Attribute Value: math!"
				);
	}

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
	cout << "\nreading reaction	...\n" << doc << endl;

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
		string speciesReference, speciesLabel, compartmentLabel, ccid;
		readSpecies (
				REACTION, doc, pathReactants, cnt,
				speciesReference, speciesLabel, 
				compartmentLabel, ccid
				);

		const string path_cnModel = "/MoDeL/species";
		MySpecies* s = new MySpecies;
		s->setDB_ref (speciesReference);
		s->setDB_Label (speciesLabel);
		s->setCompartment (compartmentLabel);
		if (!ccid.empty ()) s->setCompTypeId (ccid);
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
		string speciesReference, speciesLabel, compartmentLabel, ccid;

		readSpecies (
				REACTION, doc, pathProducts, cnt,
				speciesReference, speciesLabel, 
				compartmentLabel, ccid
				);

		const string path_cnModel = "/MoDeL/species";
		MySpecies* s = new MySpecies;
		s->setDB_ref (speciesReference);
		s->setDB_Label (speciesLabel);
		s->setCompartment (compartmentLabel);
		if (!ccid.empty ()) s->setCompTypeId (ccid);
		read_cnModel (s, SPECIES, speciesReference, path_cnModel, true); 

		if (direction) RT->addProduct (s, compartmentLabel);
		else RT->addReactant (s, compartmentLabel);
	}

	//(3) read Modifier
	const string pathModifier = head + "/listOfModifiers/modifier";
	int numOfModifiers = get_node_element_num (REACTION, &doc, &pathModifier);

	for (int cnt =1; cnt <= numOfModifiers; cnt++)
	{
		string speciesReference, speciesLabel, compartmentLabel, ccid;
		readSpecies (
				REACTION, doc, pathModifier, cnt,
				speciesReference, speciesLabel, 
				compartmentLabel, ccid
				);

		const string path_cnModel = "/MoDeL/species";
		MySpecies* s = new MySpecies;
		s->setDB_ref (speciesReference);
		s->setDB_Label (speciesLabel);
		s->setCompartment (compartmentLabel);
		if (!ccid.empty ()) s->setCompTypeId (ccid);
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
	if (direction) pathKineticLaw = head + "/kineticLaw/forwardKineticLaw";
	else pathKineticLaw = head + "/kineticLaw/reverseKineticLaw";

	//	read math
	string math;

	const string pathMath = pathKineticLaw + "/math";
	get_node (REACTION, &doc, &pathMath, math); 

	if (math.empty ())
	{
		cout << "\npath = " << pathMath << endl;
		throw StrCacuException (
				"Reading Reaction...No Math Specified!"
				);
	}
	else RT->setMath (math);

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
				PART, p->getPartCtg (),
				p->getPartRef (), parameterLabel,
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
