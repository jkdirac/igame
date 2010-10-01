#include "readInput.h"

readInput::readInput ()
{}

readInput::~readInput ()
{}

void readInput::config (
		MySBMLDocument* mysbmldoc
		) 
{

	cout << "\n=================	CONFIGURING...	===================\n";

	//
	//  create model object in mysbmldoc
	//
	Model* m = mysbmldoc->createModel ();
	m->setId ("iGameModel");

	//===================================================
	//	PART1:	LOADING UNITDEFS AND FUNCTIONDEFS FROM DB
	//===================================================
	

	//  (1.1) load unitDefinitions
	const string unitPath = 
		"/MoDeL/system/"
		"listOfUnitDefinitions/"
		"unitDefinition";
	const string unitDoc = "units";
	const int numOfUnitDefs = 
		get_node_element_num (SYSTEM, &unitDoc, &unitPath);

	for (int i=1; i <= numOfUnitDefs; i++)
	{
		ostringstream oss;
		vector<string> _id, _name;
		string id, name;

		//	attribute path for id
		oss << unitPath << "[" << i << "]/@id";
		const string attrPath_id (oss.str ());
		get_node_attr (SYSTEM, &unitDoc, &attrPath_id, _id); 
		if (_id.empty ()) 
		{
			string errno (
					"UNIT: empty attribute @id in "
					);
			errno += unitDoc + ".xml!";
			throw StrCacuException (errno);
		}
		else id = _id[0];

		//	attribute path for name 
		oss.str ("");
		oss << unitPath << "[" << i << "]/@name";
		const string attrPath_name (oss.str ());
		get_node_attr (SYSTEM, &unitDoc, &attrPath_name, _name); 
		if (!_name.empty ()) name = _name[0];

		UnitDefinition* unitdef = m->createUnitDefinition ();
		setUnit (unitdef, id, name); 

		//	read unit
		oss.str ("");
		oss << unitPath << "[" << i << "]/listOfUnits/unit";
		const string unitPath2 (oss.str ());
		int numOfUnits = get_node_element_num (SYSTEM, &unitDoc, &unitPath2);

		for (int j =1; j <= numOfUnits; j++)
		{
			Unit* unit = unitdef->createUnit ();

			string kind;
			double exponent, multiplier;
			int scale;

			readUnit (SYSTEM, unitDoc, unitPath2, j, kind, exponent, scale, multiplier);

			UnitKind_t unitKind = mysbmldoc->getUnitKind_t (kind);
			setUnit (unit, unitKind, exponent, scale, multiplier);
		}
	}

	//  (1.2) load functionDefinitions
	const string pathFunc = 
		"/MoDeL/system/"
		"listOfFunctionDefinitions/"
		"functionDefinition";
	const string funcDoc ("functions");
	const int numOfFuncDefs = 
		get_node_element_num (SYSTEM, &funcDoc, &pathFunc);

	for (int i =1; i <= numOfFuncDefs; i++)
	{
		string id, name, math;
		readFunctionDef (SYSTEM, funcDoc, pathFunc, i, id, name, math);

		FunctionDefinition* fdef = m->createFunctionDefinition ();
		setFunction (fdef, id, name, math);
	}

	cout << "\nPART1...DONE." << endl;

	//	===================================================
	//		PART2:	READ INPUT FILE
	//	===================================================
	const string DOC ("input");

	//	===================================================
	//  (1) read listOfParameters 
	//  parameter listed must be previously defined in
	//  SYSTEM container in database. This would not be
	//  validated since program which outputs the input
	//  file should take this responsibility.
	//  ===================================================
	set<string> paraUsed;

	const string pathPara = 
		"/MoDeL/dbinterface/input/"
		"listOfParameters/"
		"parameter";
	const int numOfParas = 
		get_node_element_num (DBINTERFACE, &DOC, &pathPara);

	for (int i=1; i <= numOfParas; i++)
	{
		string db, id, name, units;
		double value;
		bool constant;

		readParameter (DBINTERFACE, DOC, pathPara, i, db, id, 
				name, value, units, constant);

		//	db must be the same with id
		if (!db.empty () && db != id)
			throw StrCacuException (
					"Attribute db and id must be same"
					" in Parameter Definition"
					);

		if (paraUsed.count (id))
			throw StrCacuException (
					string ("Redefinition of Parameter ")
					+ db + "!"
					);
		else paraUsed.insert (id);

		Parameter* para = m->createParameter ();
		setParameter (para, id, name, value, units, constant);
	}

	//	======================================================
	//  (2) read listOfRules
	//  functions in listOfRules must be build-in MathML ones
	//  or previously defined in SYSTEM container
	// ======================================================
	set<string> variableUsed;

	const string pathRule = 
		"/MoDeL/dbinterface/input/"
		"listOfRules";

	//  2.1 read algebraic rules
	const string pathAlge (pathRule + "/algebraicrule");
	const int numOfAlgebraicRules = 
		get_node_element_num (DBINTERFACE, &DOC, &pathAlge);

	for (int i=1; i <= numOfAlgebraicRules; i++)
	{
		string variable, math;
		readRule (DBINTERFACE, DOC, pathAlge, i, variable, math, true);

		if (variableUsed.count (variable))
			throw StrCacuException (
					string ("Redefinition of Variable ")
					+ variable + "!"
					);
		else variableUsed.insert (variable);

		AlgebraicRule* alger = m->createAlgebraicRule ();
		setAlgebraicRule (alger, variable, math);
	}

	//  2.2 read assignment rule
	const string pathAssr (pathRule + "/assignmentrule");
	const int numOfAssignmentRules = 
		get_node_element_num (DBINTERFACE, &DOC, &pathAssr);

	for (int i=1; i <= numOfAssignmentRules; i++)
	{
		string variable, math;
		readRule (DBINTERFACE, DOC, pathAssr, i, variable, math, true);

		if (variableUsed.count (variable))
			throw StrCacuException (
					string ("Redefinition of Variable ")
					+ variable + "!"
					);
		else variableUsed.insert (variable);

		AssignmentRule* assr = m->createAssignmentRule ();
		setAssignmentRule (assr, variable, math);
	}

	//  2.3 read rate rule
	const string pathRate (pathRule + "/raterule");
	const int numOfRateRules = 
		get_node_element_num (DBINTERFACE, &DOC, &pathRate);

	for (int i=1; i <= numOfRateRules; i++)
	{
		string variable, math;
		readRule (DBINTERFACE, DOC, pathRate, i, variable, math, true);

		if (variableUsed.count (variable))
			throw StrCacuException (
					string ("Redefinition of Variable ")
					+ variable + "!"
					);
		else variableUsed.insert (variable);

		RateRule* rater = m->createRateRule ();
		setRateRule (rater, variable, math);
	}


	//	==================================
	//  (3) read listOfCompartments
	//	==================================
	const string pathComp = 
		"/MoDeL/dbInterface/input/"
		"listOfCompartments/"
		"compartment";
	const int numOfComps = 
		get_node_element_num (DBINTERFACE, &DOC, &pathComp);

	for (int i=1; i <= numOfComps; i++)
	{
		//outside must be name of its parent compartment
		string id, db, name, units, outside;
		int spatialDimensions;
		double size;
		bool constant; 


		readCompartment (DBINTERFACE, DOC, pathComp, i, db, id, 
				name, spatialDimensions, size, units, outside, constant);
		MyCompartment* comp = mysbmldoc->createMyCompartment ();
		setCompartment (comp, db, id, name, spatialDimensions, 
				size, units, outside, constant);

		//
		//	add comp* to its outside compartment
		//
		if (outside != "ROOT")
		{
			MyCompartment* outComp = 
				mysbmldoc->getMyCompartment (outside);
			if (outComp != NULL) outComp->addMyCompartmentIn (comp);
			else throw StrCacuException (
					"Unrecognized Compartment Label (outside)!"
					);
		}
	}

	//	=========================================
	//			READ listOfSpecies
	//	=========================================
	const string pathSpe =
		"/MoDeL/dbinterface/input"
		"/listOfSpecies/species";

	const int numOfSpecies =  
		get_node_element_num (DBINTERFACE, &DOC, &pathSpe);

	for (int i=1; i <= numOfSpecies; i++)
	{
		string db, ccid, id, name, compartment, substanceUnits;
		double initialAmount, initialConcentration;
		bool hasOnlySubstanceUnits, boundaryCondition, constant;
		int charge;

		readSpecies (DBINTERFACE, DOC, pathSpe, i, db, ccid, id, name,
				compartment, initialAmount, initialConcentration,
				substanceUnits, hasOnlySubstanceUnits, 
				boundaryCondition, charge, constant);

		MySpecies* s = mysbmldoc->createMySpecies ();  
		setSpecies (s, db, ccid, id, name, compartment, initialAmount, 
				initialConcentration, substanceUnits, hasOnlySubstanceUnits, 
				boundaryCondition, charge, constant);

		//
		//	read species container if db attr has been specified
		//	or read chain-node model component to complete its structure
		//
		ostringstream oss;
		if (db.empty ())
		{
			//	read structure
			oss << pathSpe << "[" << i << "]";
			read_cnModel (s, DBINTERFACE, DOC, oss.str (), false);
		}
		else
		{
			//	read structure
//            cout << "\ndb = " << db << endl;
			read_cnModel (s, SPECIES, db, "/MoDeL/species", false);
		}

//        cout << "\ni = " << i << endl;

		//	sort chain-node model
		s->rearrange ();

		//	add species in compartment
		mysbmldoc->validateBackSpecies (); //check if this species has been existed before
	}

	cout << "\nPART2...DONE." << endl;

	//	=========================================
	//	PART3: LOADING PARAMETERS AND RULES IN DB
	//	=========================================
	
	//	(3.1) read global parameter
	//	parameter definition in input file will shade that in db
	const string pathPara_db = 
		"/MoDeL/system/"
		"listOfGlobalParameters/"
		"globalParameter";
	string DOCdb = "parameters";
	const int numOfParas_db = 
		get_node_element_num (SYSTEM, &DOCdb, &pathPara_db);

	for (int i=1; i <= numOfParas; i++)
	{
		string db, id, name, units;
		double value;
		bool constant;

		readParameter (SYSTEM, DOCdb, pathPara_db, i, db, id, 
				name, value, units, constant);

		if (paraUsed.count (id)) continue;
		else
		{
			Parameter* para = m->createParameter ();
			setParameter (para, id, name, value, units, constant);
		}
	}

	//  (3.2) read listOfRules
	//	rule definition in input file will shade that in db

	const string pathRule_db = 
		"/MoDeL/system/listOfRules";
	DOCdb = "rules";

	//  2.1 read algebraic rules
	const string pathAlge_db (pathRule_db + "/algebraicrule");
	const int numOfAlgebraicRules_db = 
		get_node_element_num (SYSTEM, &DOCdb, &pathAlge_db);

	for (int i=1; i <= numOfAlgebraicRules_db; i++)
	{
		string variable, math;
		readRule (SYSTEM, DOCdb, pathAlge_db, i, variable, math, false);

		if (variableUsed.count (variable)) continue;
		else
		{
			AlgebraicRule* alger = m->createAlgebraicRule ();
			setAlgebraicRule (alger, variable, math);
		}
	}

	//  2.2 read assignment rule
	const string pathAssr_db (pathRule_db + "/assignmentule");
	const int numOfAssignmentRules_db = 
		get_node_element_num (SYSTEM, &DOCdb, &pathAssr_db);

	for (int i=1; i <= numOfAssignmentRules_db; i++)
	{
		string variable, math;
		readRule (SYSTEM, DOCdb, pathAssr_db, i, variable, math, false);

		if (variableUsed.count (variable)) continue;
		else
		{
			AssignmentRule* assr = m->createAssignmentRule ();
			setAssignmentRule (assr, variable, math);
		}
	}

	//  2.3 read rate rule
	const string pathRate_db (pathRule_db + "/raterule");
	const int numOfRateRules_db = 
		get_node_element_num (SYSTEM, &DOCdb, &pathRate_db);

	for (int i=1; i <= numOfRateRules_db; i++)
	{
		string variable, math;
		readRule (SYSTEM, DOCdb, pathRate_db, i, variable, math, false);

		if (variableUsed.count (variable)) continue;
		else
		{
			RateRule* rater = m->createRateRule ();
			setRateRule (rater, variable, math);
		}
	}
	
	cout << "\nPART3...DONE." << endl;

	cout << "\n=================	CONFIGURING...Done	===================\n";
	return;
}



