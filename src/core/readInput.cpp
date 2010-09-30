#include "readInput.h"

readInput::readInput ()
{}

readInput::~readInput ()
{}

void readInput::config (
		MySBMLDocument* mysbmldoc
		) 
{
	//
	//  create model object in mysbmldoc
	//
	Model* m = mysbmldoc->createModel ();
	m->setId ("iGameModel");

	//===================================
	//  (0.1) load unitDefinitions
	//===================================
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
		if (id.empty ()) 
		{
			string errno (
					"UNIT: empty attribute @id in "
					);
			errno += unitDoc + ".xml!"
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

	//	================================
	//  (0.2) load functionDefinitions
	//	================================
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

	//	===================================================
	//			READ INPUT FILE
	//	===================================================
	const string DOC ("input");

	//	===================================================
	//  (1) read listOfParameters 
	//  parameter listed must be previously defined in
	//  SYSTEM container in database. This would not be
	//  validated since program which outputs the input
	//  file should take this responsibility.
	//  ===================================================
	const string pathPara = 
		"/MoDeL/system/"
		"listOfParameters/"
		"parameter";
	const int numOfParas = 
		get_node_element_num (SYSTEM, &DOC, &pathPara);

	for (int i=1; i <= numOfParas; i++)
	{
		string id, name, units;
		double value;
		bool constant;

		readParameter (SYSTEM, DOC, pathPara, i, id, 
				name, value, units, constant);

		Parameter* para = m->createParameter ();
		setParameter (para, id, name, value, units, constant);
	}

	//	======================================================
	//  (2) read listOfRules
	//  functions in listOfRules must be build-in MathML ones
	//  or previously defined in SYSTEM container
	//	======================================================
	const string pathRule = 
		"/MoDeL/input/"
		"listOfRules";

	//  2.1 read algebraic rules
	const string pathAlge (pathRule + "/algebraicrule");
	const int numOfAlgebraicRules = 
		get_node_element_num (SYSTEM, &DOC, &pathAlge);

	for (int i=1; i <= numOfAlgebraicRules; i++)
	{
		string variable, math;
		readRule (SYSTEM, DOC, pathAlge, 
				"algebraicrule", i, variable, math);

		AlgebraicRule* alger = m->createAlgebraicRule ();
		setAlgebraicRule (alger, variable, math);
	}

	//  2.2 read assignment rule
	const string pathAssr (pathRule + "/assignmentule");
	const int numOfAssignmentRules = 
		get_node_element_num (SYSTEM, &DOC, &pathAssr);

	for (int i=1; i <= numOfAssignmentRules; i++)
	{
		string variable, math;
		readRule (SYSTEM, DOC, pathAssr, 
				"assignmentrule", i, variable, math);

		AssignmentRule* assr = m->createAssignmentRule ();
		setAssignmentRule (assr, variable, math);
	}

	//  2.3 read rate rule
	const string pathRate (pathRule + "/raterule");
	const int numOfRateRules = 
		get_node_element_num (SYSTEM, &DOC, &pathRate);

	for (int i=1; i <= numOfRateRules; i++)
	{
		string variable, math;
		readRule (SYSTEM, DOC, pathRate, 
				"raterule", i, variable, math);

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
		get_node_element_num (SYSTEM, &DOC, &pathComp);

	for (int i=1; i <= numOfComps; i++)
	{
		//outside must be name of its parent compartment
		string id, name, units, outside;
		int spatialDimensions;
		double size;
		bool constant; 

		readCompartment (SYSTEM, DOC, path7, i, id, 
				name, spatialDimensions, size, units, outside, constant);
		MyCompartment* comp = mysbmldoc->createMyCompartment ();
		setCompartment (comp, id, name, spatialDimensions, 
				size, units, outside, constant);

		//
		//	add comp* to its outside compartment
		//
		if (outside != "ROOT")
		{
			MyCompartment* outComp = 
				mysbmldoc->getMyCompartment (outside);
			if (outComp != NULL) outComp->addMyCompartmentIn (comp);
			else throw string (
					"Unrecognized Compartment Label (outside)!"
					);
		}
	}

		//
		//	3.1 read listOfContents
		//
		const string path9 = path7 + "/listOfContents";

		//	3.1.1 read listOfSpecies
		const string path10 = path9 + "/listOfSpecies/species";
		const int numOfSpecies =  get_node_element_num (SYSTEM, &DOC, &path10);

		for (int j=1; j <= numOfSpecies; j++)
		{
			string id, name, compartment, substanceUnits;
			double initialAmount, initialConcentration;
			bool hasOnlySubstanceUnits, boundaryCondition, constant;
			int charge;

			readSpecies (SYSTEM, DOC, path10, j, id, name,
					compartment, initialAmount, initialConcentration,
					substanceUnits, hasOnlySubstanceUnits, 
					boundaryCondition, charge, constant);

			MySpecies* s = mysbmldoc->createMySpecies ();  
			setSpecies (s, id, name, compartment, initialAmount, 
					initialConcentration, substanceUnits, hasOnlySubstanceUnits, 
					boundaryCondition, charge, constant);

			readSpecies_db (s);
			s->rearrange ();
			mysbmldoc->validateBackSpecies ();
		}

		//	
		//	3.1.2 read listOfPlasmids
		//	
		const string path12 = path7 + "/listOfPlasmids/plasmid";
		const int numOfPlasmids = get_node_element_num (SYSTEM, &DOC, &path12);

		for (int j =1; j <= numOfPlasmids; j++)
		{
			MySpecies* s = mysbmldoc->createMySpecies ();
			Chain* c = s->createChain ();

			ostringstream oss;
			oss << path12 << "[" << j << "]/biobrick";
			const string path13 (oss.str ());

			const int numOfParts = get_node_element_num (SYSTEM, &DOC, &path13);
			for (int k =0; k <numOfParts; k++)
			{
				string pR, pL, pT, pC;
				readPart (SYSTEM, DOC, path13, k, pR, pL, pT, pC);

				Part* p = c->createPart ();
				p->setDbId (pR);
				p->setPartLabel (pL);
				p->setPartType (pT);
				p->setPartCategory (pC);
				p->setIsBinded (s->countBindedNode (pL));
			}

			s->rearrange ();
			mysbmldoc->validateBackSpecies ();
		}

	}//! read listOfMyCompartments
}



