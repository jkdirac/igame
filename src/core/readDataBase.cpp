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

	for (int itree = 1; itree <= numOfTrees; itree++)
	{
		//	create an empty tree
		Tree* t = s->createTree ();

		//	read nodes 
		ostringstream oss;
		oss << pathTree << "[" << itree << "]/listOfNodes/node";
		string pathNode (oss.str ());
		int numOfNodes = get_node_element_num (cind, &doc, &pathNode);

		for (int inode = 1; inode <= numOfNodes; inode++)
		{
			string child, parent;
			readNode (cind, doc, pathNode, inode, child, parent);
			t->createNode (child, parent);
		}

		//add Children of each node
		t->addNodeChildren ();	
	}

	//	find binded part
	for (int ichain=0; ichain < s->getNumOfChains (); ichain++)
	{
		Chain* c = s->getChain (ichain);
		for (int ipart = 0; ipart < c->getNumOfParts (); ipart++)
		{
			Part* p = c->getPart (ipart);
			Node* n = s->findBindedNode (p->getPartLabel ());
		    if (n != NULL) p->setIsBinded (true);
			else p->setIsBinded (false);
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

	//  set database reference 
	if (!db.empty ()) s->setDB_ref (db); 

	//	set id of compartment-type species
	if (!ccid.empty ()) s->setCompTypeId (ccid);

	//  setId 
	operation = s->setId (id);
	if (operation == LIBSBML_INVALID_ATTRIBUTE_VALUE)
	{
		cout << "\nid = " << id << endl;
		throw StrCacuException (
				"Reading Block Species..."
				"Invalid Attribute Value: id!"
				);
	}

	//  setName 
	if (!name.empty ())
	{
		operation = s->setName (name);
		if (operation == LIBSBML_INVALID_ATTRIBUTE_VALUE)
			throw StrCacuException (
					"Reading Block Species..."
					"Invalid Attribute Value: name!"
					);
	}

	//  setCompartment
	operation = s->setCompartment (compartment);
	if (operation == LIBSBML_INVALID_ATTRIBUTE_VALUE)
		throw StrCacuException (
				"Reading Block Species..."
				"Invalid Attribute Value: compartment!"
				);

	//  setInitialAmount
	if (initialAmount >= 0.0) 
		operation = s->setInitialAmount (initialAmount);

	//  setInitialConcentration
	if (initialConcentration >= 0.0) 
	{
		operation = s->setInitialConcentration (initialConcentration);
		if (operation == LIBSBML_UNEXPECTED_ATTRIBUTE)
			throw StrCacuException (
					"Reading Block Species..."
					"Unexpected Attribute: initialConcentration!"
					);
	}

	//  setSubstanceUnits
	if (!substanceUnits.empty ())
	{
		operation = s->setSubstanceUnits (substanceUnits);
		if (operation == LIBSBML_INVALID_ATTRIBUTE_VALUE)
			throw StrCacuException (
					"Reading Block Species..."
					"Invalid Attribute Value: substanceUnits!"
					);
	}


	//	setConstant
	if (constant == true) s->setConstant (true);

	//  setHasOnlySubstanceUnits
	if (hasOnlySubstanceUnits == true) s->setHasOnlySubstanceUnits (true);

	//	setBoundaryCondition
	if (boundaryCondition == true) s->setBoundaryCondition (true);
	
	//	setCharge
	if (charge != 0) 
	{
		operation = s->setCharge (charge);
		if (operation == LIBSBML_UNEXPECTED_ATTRIBUTE)
			throw StrCacuException (
					"Reading Block Species..."
					"Unexpected Attribute: charge!"
					);
	}
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

/**
 * only necessary examination will be executed
 */
void readDataBase::readReaction (
		const string& doc,	//	reaction document file
		const string& sid,	// 	species identifier
		const string& type, //  reactant/modifier/product
		reactionTemplate* tmpR
		)
{
	cout << "\n##############	READING REACTION TEMPLATE:	" 
		 << doc << "	..." << endl;

	string head ("/MoDeL/reaction");

	if (doc.empty ()) throw StrCacuException (
			"Reading Reaction...No ID Specified!"
			);

	vector<string> temp;

	/**
	 * before everything, we first need to find
	 * the species type of sid in the reaction if type is empty
	 */
	int speciesType = -1;	//0, 1, 2	

	if (type == "reactant") speciesType = 0;
	else if (type == "modifier") speciesType = 1;
	else if (type == "product") speciesType = 2;
	else
	{
		if (speciesType == -1)
		{
			//	read reactant species reference
			string pathReactants = head + "/listOfReactants/reactant";
			int numOfReactants = get_node_element_num (REACTION, &doc, &pathReactants);
			for (int cnt =1; cnt <= numOfReactants; cnt++)
			{
				ostringstream oss;
				oss << pathReactants << "[" << cnt << "]/speciesReference";
				const string nodepath (oss.str ());
				get_node_element (REACTION, &doc, &nodepath, temp); 
				if (temp.empty ())
				{
					string errno = string (
							"SPECIES: empty node speciesReference in "
							) + doc + ".xml!";
					throw StrCacuException (errno);
				}
				else if (temp[0] == sid) {speciesType = 0; break;}
			}
		}

		if (speciesType == -1)
		{
			//	read modifier species reference
			string pathModifiers = head + "/listOfModifiers/modifier";
			int numOfModifiers = get_node_element_num (REACTION, &doc, &pathModifiers);
			for (int cnt =1; cnt <= numOfModifiers; cnt++)
			{
				ostringstream oss;
				oss << pathModifiers << "[" << cnt << "]/speciesReference";
				const string nodepath (oss.str ());
				get_node_element (REACTION, &doc, &nodepath, temp); 
				if (temp.empty ())
				{
					string errno = string (
							"SPECIES: empty node speciesReference in "
							) + doc + ".xml!";
					throw StrCacuException (errno);
				}
				else if (temp[0] == sid) {speciesType = 1; break;}
			}
		}

		if (speciesType == -1)
		{
			//	read reactant species reference
			string pathProducts = head + "/listOfProducts/product";
			int numOfProducts = get_node_element_num (REACTION, &doc, &pathProducts);
			for (int cnt =1; cnt <= numOfProducts; cnt++)
			{
				ostringstream oss;
				oss << pathProducts << "[" << cnt << "]/speciesReference";
				const string nodepath (oss.str ());
				get_node_element (REACTION, &doc, &nodepath, temp); 
				if (temp.empty ())
				{
					string errno = string (
							"SPECIES: empty node speciesReference in "
							) + doc + ".xml!";
					throw StrCacuException (errno);
				}
				else if (temp[0] == sid) {speciesType = 2; break;}
			}
		}

		if (speciesType == -1) throw StrCacuException (
				"Wrong link from species to reaction!"
				);
	}

	/**
	 *	read attribute Id
	 */
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

	if (id != doc) throw StrCacuException (
			"Reading Reaction...Inconsistent ID!"
			);
	else tmpR->setId (id);

	/**
	 *	read attribute name
	 */
	string name;
	const string pathName = head + "/@name";
	get_node_attr (REACTION, &doc, &pathName, temp);
	if (!temp.empty ()) name = temp[0];
	tmpR->setName (name);

	/**
	 * 	read attribute Reversible
	 */
	bool reversible;
	const string pathRev = head + "/@reversible";
	get_node_attr (REACTION, &doc, &pathRev, temp);
	if (!temp.empty ()) reversible = (temp[0] == "true");
	else reversible = true;
	tmpR->setReversible (reversible);

	//	species type could not be "product" in an irreversible reaction
	if (reversible == false && speciesType == 2) return;

	/**
	 *	read attribute fast
	 */
	bool fast;
	const string pathFast = head + "/@fast";
	get_node_attr (REACTION, &doc, &pathFast, temp);
	if (!temp.empty ()) fast = (temp[0] == "true");
	else fast = false;
	tmpR->setFast (fast);

	/**
	 * read Block Compartments
	 * *
	 * validate: 
	 */
	const string pathComp = head + "/listOfCompartments/compartment";
	int numOfComps = get_node_element_num (REACTION, &doc, &pathComp);

	set<string> __read_in_comps;
	for (int cnt =1; cnt <= numOfComps; cnt++)
	{
		string compartmentRef, currComp, parComp;
		readCompartment (REACTION, doc, pathComp, cnt, compartmentRef, currComp, parComp);

		if (currComp == "ROOT") throw StrCacuException (
				"ROOT could not be regarded as child!"
				);

		if (__read_in_comps.count (currComp)) throw StrCacuException (
				"REACTION: Different compartments should have different labels!"
				);
		else 
		{
			__read_in_comps.insert (currComp);
			tmpR->addCompartment (compartmentRef, currComp, parComp);
		}
	}

	/**
	 * readReactionSpecies
	 */
	bool direction = (speciesType != 2);
	
	//(1) read reactants
	
	string pathReactants = head;
	if (direction) pathReactants += "/listOfReactants/reactant";
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

		if (direction) tmpR->addReactant (s, compartmentLabel);
		else tmpR->addProduct (s, compartmentLabel);
	}

	//(2) read products
	map <string, int> prodIndex;

	//	begin
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

		if (direction) tmpR->addProduct (s, compartmentLabel);
		else tmpR->addReactant (s, compartmentLabel);

		prodIndex[speciesLabel] = cnt-1;
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

		tmpR->addModifier (s, compartmentLabel);
	}

	/**
	 * add prefix to products
	 */
	ostringstream oss;
	string prefix = "__MoDeL_PRODUCT_CXX_";
	for (int i=0; i < numOfProducts; i++) 
	{
		oss.str (""); oss << prefix << i << "::";
        tmpR->addProductPrefix (oss.str ());
	}

	//read substituent transfer table
	vector< pair<string,string> > source;
	vector< pair<string,string> > destin;
	const string pathTransfer = head + 
		"/listOfSubstituentTransfers"
		"/substituentTransfer";
	int numOfTrans = get_node_element_num (REACTION, &doc, &pathTransfer);

	for (int cnt= 1; cnt <= numOfTrans; cnt++)
	{
		//	need validation here
		//	from must be part of reactants/modifiers
		//	to must be part of products
		//	for reverse reaction, roles of from/to will be exchanged
		//	BIG PROBLEM!

		pair<string,string> from, to;
		readTransfer (REACTION, doc, pathTransfer, cnt, from, to);

//        cout << "\nto.first = " <<to.first << "to.second = " << to.second << endl;

		//	reset partLabel of "to" element
		oss.str (""); 
		oss << prefix << prodIndex[to.first] << "::";
		to.second = oss.str () + to.second;
//        cout << "\nto.second = " << to.second << endl;

		tmpR->addSubstituentTransfer (from, to);
	}

//    cout << "\nbegin read kineticlaw " << endl;

	/**
	 *	read KineticLaw
	 */
	string pathKineticLaw;
	if (direction) pathKineticLaw = 
		head + "/kineticLaw/forwardKineticLaw";
	else pathKineticLaw = 
		head + "/kineticLaw/reverseKineticLaw";

	//	read math
	string math;

	const string pathMath = pathKineticLaw + "/math";
	get_node (REACTION, &doc, &pathMath, math); 

	if (math.empty ())
	{
		cout << "\ndoc = " << doc 
			 << "	path = " << pathMath 
			 << endl;

		throw StrCacuException (
				"Reading Reaction...No Math Specified!"
				);
	}
	else tmpR->setMath (math);

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
		tmpR->addParameter (para);
	}

	//	read referenced parameters
	const string pathExtRef = pathKineticLaw + 
		"/listOfReferencedParameters/referencedParameter";
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
		const MySpecies* s = tmpR->getSpecies (speciesLabel);
		if (s == NULL)
		{
			string errno ("REACTION: species with label ");
			errno += speciesLabel + " does not exist in"
			   " reactant/modifier/product definition!";
			throw StrCacuException (errno);
		}
		string compartmentLabel = s->getCompartment ();

		string units, name;
		double value;

		const Part* p = s->getPart (partLabel);
		if (p == NULL)
		{
			string errno ("REACTION: no part with label ");
			errno += partLabel + 
					" could be found in species " 
					+ speciesLabel + "!"; 
			throw StrCacuException (errno);
		}
		readConditionalParameter (
				PART, p->getPartCtg (),
				p->getPartRef (), parameterLabel,
			    compartmentLabel, value, units, name
				);

		Parameter* para = new Parameter (2,4);
		setParameter (para, id, name, value, units, true);
		tmpR->addParameter (para);
	}
	
	/**
	 * read listOfConstraints
	 */
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
		tmpR->addConstraint (variables, formula);
	}

	return;
}
