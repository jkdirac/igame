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
  //  constant variables 
  //
  const string MODEL = "iGAMEsbml";
  const string DOC = "input";
  const string PREFIX = "/sbpmodel/input/";

  //
  //  create model object in mysbmldoc
  //
  Model* m = mysbmldoc->createModel ();
  m->setId (MODEL);

  //
  //  read input file and config environment
  //

  //  (0) load files predefined in PREDEF

  //
  //  (0.1) load unitDefinitions
  //
  const string pathU1 = "/sbpmodel/predef/"
	"listOfUnitDefinitions/unitDefinition";
  const string unitDoc = "listOfUnitDefinitions";
  const int numOfUnitDefs = get_node_element_num (PREDEF, &unitDoc, &pathU1);

  for (int i=1; i <= numOfUnitDefs; i++)
  {
	string id, name;
	nodeQuery (PREDEF, unitDoc, pathU1, i, "id", id); 
	nodeQuery (PREDEF, unitDoc, pathU1, i, "id", name); 

	UnitDefinition* unitdef = m->createUnitDefinition ();
	setUnit (unitdef, id, name); 
	
	ostringstream oss;
	oss << pathU1 << "[" << i << "]/unit";
	const string& pathU2 (oss.str ());

	int numOfUnits = get_node_element_num (PREDEF, &unitDoc, &pathU2);
	for (int j =1; j <= numOfUnits; j++)
	{
	  Unit* unit = unitdef->createUnit ();

	  string kind;
	  double exponent, multiplier;
	  int scale;

	  readUnit (PREDEF, unitDoc, pathU2, j, kind, exponent, scale, multiplier);

	  UnitKind_t unitKind = mysbmldoc->getUnitKind_t (kind);
	  setUnit (unit, unitKind, exponent, scale, multiplier);
	}
  }

  //
  //  (0.2) load functionDefinitions
  //
  const string pathFunc = "/sbpmodel/predef/"
	"listOfFunctionDefinitions/functionDefinition";
  const string funcDoc = "listOfFunctionDefinitions";
  const int numOfFuncDefs = get_node_element_num (PREDEF, &funcDoc, &pathFunc);

  for (int i =1; i < numOfFuncDefs; i++)
  {
	string id, name, math;
	readFunctionDef (PREDEF, funcDoc, pathFunc, i, id, name, math);

	FunctionDefinition* fdef = m->createFunctionDefinition ();
	setFunction (fdef, id, name, math);
  }

  //
  //  (1) read listOfConditions 
  //  parameter listed must be previously defined in
  //  PREDEF container in database. This would not be
  //  validated since program which outputs the input
  //  file should take this responsibility.
  //
  const string path1 = PREFIX + "listOfParameters/parameter";
  const int numOfParas =  get_node_element_num (PREDEF, &DOC, &path1);

  for (int i=1; i <= numOfParas; i++)
  {
	string id, name, units;
	double value;
	bool constant;

	readParameter (PREDEF, DOC, path1, i, id, 
		name, value, units, constant);
	
	Parameter* para = m->createParameter ();
	setParameter (para, id, name, value, units, constant);
  }

  //
  //  (2) read listOfRules
  //  functions in listOfRules must be build-in MathML ones
  //  or previously defined in PREDEF container
  //
  const string path3 = PREFIX + "listOfRules";

  //  2.1 read algebraic rules
  const string path4 = path3 + "/algebraicrule";
  const int numOfAlgebraicRules = 
	get_node_element_num (PREDEF, &DOC, &path4);

  for (int i=1; i <= numOfAlgebraicRules; i++)
  {
	string variable, math;
	readRule (PREDEF, DOC, path3, 
		"algebraicrule", i, variable, math);
	
	AlgebraicRule* alger = m->createAlgebraicRule ();
	setAlgebraicRule (alger, variable, math);
  }

  //  2.2 read assignment rule
  const string path5 = path3 + "/assignmentule";
  const int numOfAssignmentRules = 
	get_node_element_num (PREDEF, &DOC, &path5);

  for (int i=1; i <= numOfAssignmentRules; i++)
  {
	string variable, math;
	readRule (PREDEF, DOC, path3, 
		"assignmentrule", i, variable, math);
	
	AssignmentRule* assr = m->createAssignmentRule ();
	setAssignmentRule (assr, variable, math);
  }

  //  2.3 read rate rule
  const string path6 = path3 + "/raterule";
  const int numOfRateRules = 
	get_node_element_num (PREDEF, &DOC, &path6);

  for (int i=1; i <= numOfRateRules; i++)
  {
	string variable, math;
	readRule (PREDEF, DOC, path3, 
		"raterule", i, variable, math);
	
	RateRule* rater = m->createRateRule ();
	setRateRule (rater, variable, math);
  }

  //
  //  (3) read listOfCompartments
  //
  const string path7 = PREFIX + "listOfCompartments/compartment";
  const int numOfComps =  get_node_element_num (PREDEF, &DOC, &path7);

  for (int i=1; i <= numOfComps; i++)
  {
	//outside must be name of its parent compartment
	string id, name, units, outside;
	int spatialDimensions;
	double size;
	bool constant; 

	readCompartment (PREDEF, DOC, path7, i, id, 
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

	//
	//	read self-contained contents
	//
	const string ddoc = id;
	const string path8 ("/sbpmodel/compartment/listOfContents/content");
	const int numOfContents = get_node_element_num (COMPARTMENT, &ddoc, &path8);

	for (int j=1; j <= numOfContents; j++)
	{
	  string id, name, compartment, substanceUnits;
	  double initialAmount, initialConcentration;
	  bool hasOnlySubstanceUnits, boundaryCondition, constant;
	  int charge;

	  readSpecies (COMPARTMENT, ddoc, path8, j, id, name,
		  compartment, initialAmount, initialConcentration,
		  substanceUnits, hasOnlySubstanceUnits, 
		  boundaryCondition, charge, constant);
	  
	  MySpecies* s = mysbmldoc->createMySpecies ();  
	  
	  //  name should be unique sbmlid, which should be reset
	  name = mysbmldoc->genSbmlId ();

	  setSpecies (s, id, name, compartment, initialAmount, 
		  initialConcentration, substanceUnits, hasOnlySubstanceUnits, 
		  boundaryCondition, charge, constant);

	  readSpecies_db (s);
	  mysbmldoc->validateBackSpecies ();
	  s->rearrange ();
	}

	//
	//	3.1 read listOfContents
	//
	const string path9 = path7 + "/listOfContents";

	//	3.1.1 read listOfSpecies
	const string path10 = path9 + "/listOfSpecies/species";
	const int numOfSpecies =  get_node_element_num (PREDEF, &DOC, &path10);

	for (int j=1; j <= numOfSpecies; j++)
	{
	  string id, name, compartment, substanceUnits;
	  double initialAmount, initialConcentration;
	  bool hasOnlySubstanceUnits, boundaryCondition, constant;
	  int charge;

	  readSpecies (PREDEF, DOC, path10, j, id, name,
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
	const int numOfPlasmids = get_node_element_num (PREDEF, &DOC, &path12);

	for (int j =1; j <= numOfPlasmids; j++)
	{
	  MySpecies* s = mysbmldoc->createMySpecies ();
	  Chain* c = s->createChain ();

	  ostringstream oss;
	  oss << path12 << "[" << j << "]/biobrick";
	  const string path13 (oss.str ());

	  const int numOfParts = get_node_element_num (PREDEF, &DOC, &path13);
	  for (int k =0; k <numOfParts; k++)
	  {
		string pR, pL, pT, pC;
		readPart (PREDEF, DOC, path13, k, pR, pL, pT, pC);
		
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



