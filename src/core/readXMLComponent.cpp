#include "readXMLComponent.h"

readXMLComponent::readXMLComponent ()
{}

readXMLComponent::~readXMLComponent ()
{}

void readXMLComponent::nodeQuery (
	const container_index& cind,
	const string& doc,
	const string& qpath,
	const int& i, 
	const string& node,
	string& value
	)
{
  string np (qpath);
  if (i == 0) np += "/" + node;
  else 
  {
	ostringstream oss;
	oss << np << "[" << i << "]/" << node;
	np = string (oss.str ());
  }

  vector<string> res;
  
  int operation = get_node_element (cind, &doc, &np, res);
  //errorHandle (operation);

  if (!res.empty ()) value = res[0];
}

void readXMLComponent::readPart (
	const container_index& cind,
	const string& doc,
	const string& qpath,
	const int& i,
	string& pR, 
	string& pL,
	string& pT,
	string& pC 
	)
{
  ostringstream oss;
  oss << "[" << i <<"]/";
  string prefix = qpath + string(oss.str ());

  string np;
  vector<string> _pR, _pL, _pT, _pC;

  //
  //  read attribute partReference
  //
  np = prefix + "partReference";
  get_node_element (cind, &doc, &np, _pR); 
  if (_pR.empty ())
  {
	string error = string (
		"PART: empty attribute @partReference in "
		) + doc + ".xml!";
	throw error;
  }
  else pR = _pR[0];

  //
  //  read attribute partLabel
  //
  np = prefix + "partLabel";
  get_node_element (cind, &doc, &np, _pL); 
  if (_pL.empty ())
  {
	string error = string (
		"PART: empty attribute @partLabel in "
		) + doc + ".xml!";
	throw error;
  }
  else pL = _pL[0];

  //
  //  read attribute partType
  //
  np = prefix + "partType";
  get_node_element (cind, &doc, &np, _pT); 
  if (_pT.empty ())
  {
	string error = string (
		"PART: empty attribute @partType in "
		) + doc + ".xml!";
	throw error;
  }
  else pT = _pT[0];

  //
  //  read attribute partCategory
  //
  np = prefix + "partCategory";
  get_node_element (cind, &doc, &np, _pC); 
  if (_pC.empty ())
  {
	string error = string (
		"PART: empty attribute @partCategory in "
		) + doc + ".xml!";
	throw error;
  }
  else pC = _pC[0];
}

void readXMLComponent::readNode (
	const container_index& cind,
	const string& doc,
	const string& qpath,
	const int& i,
	string& nCL, 
	string& nPL 
	)
{
  ostringstream oss;
  oss << "[" << i <<"]/";
  string prefix = qpath + string(oss.str ());

  string np;
  vector<string> _nCL, _nPL;

  //
  //  read attribute currentNodeLabel
  //
  np = prefix + "currentNodeLabel";
  get_node_element (cind, &doc, &np, _nCL); 
  if (_nCL.empty ())
  {
	string error = string (
		"NODE: empty attribute @currentNodeLabel in "
		) + doc + ".xml!";
	throw error;
  }
  else nCL = _nCL[0];

  //
  //  read attribute parentNodeLabel
  //
  np = prefix + "parentNodeLabel";
  get_node_element (cind, &doc, &np, _nPL); 
  if (_nPL.empty ())
  {
	string error = string (
		"NODE: empty attribute @parentNodeLabel in "
		) + doc + ".xml!";
	throw error;
  }
  else nPL = _nPL[0];
}

void readXMLComponent::readSpecies (
	const container_index& cind,
	const string& doc,
	const string& qpath,
	const int& i,
	string& speciesReference,
	string& speciesLabel,
	string& compartmentLabel
	)
{
  ostringstream oss;
  oss << "[" << i << "]/";
  string prefix = qpath + string (oss.str ());

  string np;
  vector<string> _ref, _sl, _cl;
  
  //
  //  read attribute speciesReference
  //
  np = prefix + "speciesReference";
  get_node_element (cind, &doc, &np, _ref); 
  if (_ref.empty ())
  {
	string error = string (
		"SPECIES: empty attribute @speciesReference in "
		) + doc + ".xml!";
	throw error;
  }
  else speciesReference = _ref[0];

  //
  //  read attribute speciesLabel
  //
  np = prefix + "speciesLabel";
  get_node_element (cind, &doc, &np, _sl); 
  if (_sl.empty ())
  {
	string error = string (
		"SPECIES: empty attribute @speciesLabel in "
		) + doc + ".xml!";
	throw error;
  }
  else speciesLabel = _sl[0];

  //
  //  read attribute compartmentLabel
  //
  np = prefix + "compartmentLabel";
  get_node_element (cind, &doc, &np, _cl); 
  if (_cl.empty ())
  {
	string error = string (
		"SPECIES: empty attribute @compartmentLabel in "
		) + doc + ".xml!";
	throw error;
  }
  else compartmentLabel = _cl[0];
}

void readXMLComponent::readCompartment (
	const container_index& cind,
	const string& doc,
	const string& qpath,
	const int& i,
	string& compartmentReference,
	string& currentCompartmentLabel,
	string& parentCompartmentLabel
	)
{
  ostringstream oss;
  oss << "[" << i <<"]/";
  string prefix = qpath + string(oss.str ());

  string np;
  vector<string> cref, curr, par; 

  //
  //  read attribute compartmentLabel
  //
  np = prefix + "compartmentReference";
  get_node_element (cind, &doc, &np, cref); 
  if (cref.empty ())
  {
	string error = string (
		"COMPARTMENT: empty attribute @compartmentReference in "
		) + doc + ".xml!";
	throw error;
  }
  else compartmentReference = cref[0];

  //
  //  read attribute currentCompartmentLabel
  //
  np = prefix + "currentCompartmentLabel";
  get_node_element (cind, &doc, &np, curr); 
  if (curr.empty ())
  {
	string error = string (
		"COMPARTMENT: empty attribute @currentCompartmentLabel in "
		) + doc + ".xml!";
	throw error;
  }
  else currentCompartmentLabel = curr[0];

  //
  //  read attribute parentCompartmentLabel
  //
  np = prefix + "parentCompartmentLabel";
  get_node_element (cind, &doc, &np, par); 
  if (par.empty ())
  {
	string error = string (
		"COMPARTMENT: empty attribute @parentCompartmentLabel in "
		) + doc + ".xml!";
	throw error;
  }
  else parentCompartmentLabel = par[0];
}


void readXMLComponent::readTransfer (
	const container_index& cind,
	const string& doc,
	const string& qpath,
	const int& i,
	pair<string,string>& from,
	pair<string,string>& to
	)
{
  ostringstream oss;
  oss << "/[" << i << "]/";
  string prefix = qpath + string (oss.str ());

  string np;
  vector<string> tmp; 

  //
  //  read component from
  //
  
  //
  //  read attribute partLabel
  //
  np = prefix + "From/partLabel";
  get_node_element (cind, &doc, &np, tmp); 
  if (tmp.empty ())
  {
	string error = string (
		"TRANSFER: empty attribute From/@partLabel in "
		) + doc + ".xml!";
	throw error;
  }
  else from.first = tmp[0];
  tmp.clear ();

  //
  //  read attribute speciesLabel
  //
  np = prefix + "From/speciesLabel";
  get_node_element (cind, &doc, &np, tmp); 
  if (tmp.empty ())
  {
	string error = string (
		"TRANSFER: empty attribute From/@speciesLabel in "
		) + doc + ".xml!";
	throw error;
  }
  else from.second = tmp[0];
  tmp.clear ();

  //
  //  read component to 
  //
  
  //
  //  read attribute partLabel
  //
  np = prefix + "To/partLabel";
  get_node_element (cind, &doc, &np, tmp); 
  if (tmp.empty ())
  {
	string error = string (
		"TRANSFER: empty attribute To/@partLabel in "
		) + doc + ".xml!";
	throw error;
  }
  else to.first = tmp[0];
  tmp.clear ();

  //
  //  read attribute speciesLabel
  //
  np = prefix + "To/speciesLabel";
  get_node_element (cind, &doc, &np, tmp); 
  if (tmp.empty ())
  {
	string error = string (
		"TRANSFER: empty attribute To/@speciesLabel in "
		) + doc + ".xml!";
	throw error;
  }
  else to.second = tmp[0];
  tmp.clear ();
}

void readXMLComponent::readParameter (
	const container_index& cind,
	const string& doc, 
	const string& qpath, 
	const int& i, 
	string& id,
	string& name,
	double& value,
	string& units,
	bool& constant
	)
{
  ostringstream oss;
  oss << "[" << i <<"]/";
  string prefix = qpath + string(oss.str ());

  string np; 
  vector<string> _id, _name, _value, _units, _const;

  //
  //  read attribute id
  //
  np = prefix + "id";
  get_node_element (cind, &doc, &np, _id); 
  if (_id.empty ())
  {
	string error = string (
		"PARAMETER: empty attribute @id in "
		) + doc + ".xml!";
	throw error;
  }
  else id = _id[0];

  //
  //  read attribute name
  //
  np = prefix + "name";
  get_node_element (cind, &doc, &np, _name); 
  if (!_name.empty ()) name = _name[0];

  //
  //  read attribute value 
  //
  np = prefix + "value";
  get_node_element (cind, &doc, &np, _value);
  if (!_value.empty ()) 
	value = atof (_value[0].c_str ());
  else value = 0.0;

  //
  //  read attribute units
  //
  np = prefix + "units";
  get_node_element (cind, &doc, &np, _units);
  if (!_units.empty ()) units = _units[0];

  //
  //  read attribute constant
  //
  np = prefix + "constant";
  get_node_element (cind, &doc, &np, _const);
  if (!_const.empty ()) 
	constant = (_const[0] == "true"); 
  else constant = true;
}

void readXMLComponent::readCompartment (
	const container_index& cind,
	const string& doc, 
	const string& qpath, 
	const int& i, 
	string& id,
	string& name,
	int& spatialDimensions,
	double& size,
	string& units,
	string& outside,
	bool& constant
	)
{
  ostringstream oss;
  oss << "[" << i <<"]/";
  string prefix = qpath + string(oss.str ());

  string np; 
  vector<string> _id, _name, _dim, _size, _units, _outside, _const;

  //
  //  read attribute id
  //
  np = prefix + "id";
  get_node_element (cind, &doc, &np, _id); 
  if (_id.empty ())
  {
	string error = string (
		"COMPARTMENT: empty attribute @id in "
		) + doc + ".xml!";
	throw error;
  }
  else id = _id[0];

  //
  //  read attribute name
  //
  np = prefix + "name";
  get_node_element (cind, &doc, &np, _name); 
  if (!_name.empty ()) name = _name[0];

  //
  //  read attribute spatialDimensions
  //
  np = prefix + "spatialDimensions";
  get_node_element (cind, &doc, &np, _dim);
  if (!_dim.empty ())
	spatialDimensions = atoi (_dim[0].c_str ());
  else spatialDimensions = 3;

  //
  //  read attribute size
  //
  np = prefix + "size";
  get_node_element (cind, &doc, &np, _size);
  if (_size.empty ()) size = -1.0;
  else size = atof (_size[0].c_str ());

  //
  //  read attribute units
  //
  np = prefix + "units";
  get_node_element (cind, &doc, &np, _units);
  if (!_units.empty ()) units = _units[0];

  //
  //  read attribute outside
  //
  np = prefix + "outside";
  get_node_element (cind, &doc, &np, _outside); 
  if (_outside.empty ())
  {
	string error = string (
		"COMPARTMENT: empty attribute @outside in "
		) + doc + ".xml!";
	throw error;
  }
  else outside = _outside[0];

  //
  //  read attribute constant
  //
  np = prefix + "constant";
  get_node_element (cind, &doc, &np, _const);
  if (!_const.empty ()) 
	constant = (_const[0] == "true"); 
  else constant = true;
}

void readXMLComponent::readSpecies (
	const container_index& cind, 
	const string& doc,
	const string& qpath,
	const int& i,
	string& id,
	string& name,
	string& compartment,
	double& initialAmount,
	double& initialConcentration,
	string& substanceUnits,
	bool& hasOnlySubstanceUnits,
	bool& boundaryCondition,
	int& charge,
	bool& constant
	)
{
  ostringstream oss;
  oss << "/[" << i <<"]/";
  string prefix = qpath + string(oss.str ());

  string np; 
  vector<string> temp;

  //
  //  read attribute id
  //
  np = prefix + "id";
  get_node_element (cind, &doc, &np, temp); 
  if (temp.empty ())
  {
	string error = string (
		"SPECIES: empty attribute @id in "
		) + doc + ".xml!";
	throw error;
  }
  else id = temp[0];

  //
  //  read attribute name
  //
  np = prefix + "name";
  get_node_element (cind, &doc, &np, temp); 
  if (temp.empty ())
  {
	string error = string (
		"SPECIES: empty attribute @name in "
		) + doc + ".xml!";
	throw error;
  }
  else name = temp[0];

  //
  //  read attribute compartment 
  //
  np = prefix + "compartment";
  get_node_element (cind, &doc, &np, temp); 
  if (temp.empty ())
  {
	string error = string (
		"SPECIES: empty attribute @compartment in "
		) + doc + ".xml!";
	throw error;
  }
  else compartment = temp[0];

  //
  //  read attribute initialAmount
  //
  np = prefix + "initialAmount";
  get_node_element (cind, &doc, &np, temp); 
  if (temp.empty ()) initialAmount = -1;
  else initialAmount = atof (temp[0].c_str ());

  //
  //  read attribute initialConcentration
  //
  np = prefix + "initialConcentrationt";
  get_node_element (cind, &doc, &np, temp); 
  if (temp.empty ()) initialConcentration = -1;
  else initialConcentration = atof (temp[0].c_str ());

  if (initialAmount >= 0.0 && 
	  initialConcentration >= 0.0)
  {
	string error = string (
		"SPECIES: only one of initialAmount/initialConcentration"
		" could be set to indicate species' initial quantity!"
		) + doc + ".xml!";
	throw error;
  }

  //
  //  read attribute substanceUnits
  //
  np = prefix + "substanceUnits";
  get_node_element (cind, &doc, &np, temp); 
  if (!temp.empty ()) substanceUnits = temp[0];

  //
  //  read attribute hasOnlySubstanceUnits
  //
  np = prefix + "hasOnlySubstanceUnits";
  get_node_element (cind, &doc, &np, temp); 
  if (temp.empty ()) hasOnlySubstanceUnits = false;
  else hasOnlySubstanceUnits = (temp[0] == "true");

  //
  //  read attribute constant
  //
  np = prefix + "constant";
  get_node_element (cind, &doc, &np, temp); 
  if (temp.empty ()) constant = true;
  else constant = (temp[0] == "true");

  //
  //  read attribute charge
  //
  np = prefix + "charge";
  get_node_element (cind, &doc, &np, temp); 
  if (temp.empty ()) charge = 0;
  else charge = atoi (temp[0].c_str ());

  //
  //  read attribute boundaryCondition
  //
  np = prefix + "boundaryCondition";
  get_node_element (cind, &doc, &np, temp); 
  if (temp.empty ()) boundaryCondition = false;
  else boundaryCondition = (temp[0] == "true");
}

void readXMLComponent::readRule (
	const container_index& cind, 
	const string& doc,
	const string& qpath,
	const string& rule_t,
	const int& i,
	string& variable,
	string& math
	)
{
  ostringstream oss;
  oss << "/" << rule_t << "[" << i <<"]/";
  string prefix = qpath + string(oss.str ());

  string np; 
  vector<string> _var, _math;

  //
  //  read attribute variable
  //
  np = prefix + "variable";
  get_node_element (cind, &doc, &np, _var); 
  if (_var.empty ())
  {
	string error = string (
		"RULE: empty attribute @variable in "
		) + doc + ".xml!";
	throw error;
  }
  else variable = _var[0];

  //
  //  read attribute math
  //
  np = prefix + "math";
  get_node_element (cind, &doc, &np, _math);
  if (_math.empty ())
  {
	string error = string (
		"RULE: empty attribute @math in "
		) + doc + ".xml!";
	throw error;
  }
  else math = _math[0];
}

void readXMLComponent::readSpeciesLink (
	const container_index& cind, 
	const string& doc,
	const string& qpath,
	const int& i,
	string& speciesReference,
	string& partType
	) 
{
  ostringstream oss;
  oss << "[" << i <<"]/";
  string prefix = qpath + string(oss.str ());

  string np;
  vector<string> _ref, _role;

  //
  //  read attribute speciesReference 
  //
  np = prefix + "speciesReference";
  get_node_element (cind, &doc, &np, _ref);
  if (_ref.empty ())
  {
	string error = string (
		"SPECIESLINK: empty attribute @speciesReference in "
		) + doc + ".xml!";
	throw error;
  }
  else speciesReference = _ref[0];

  //
  //  read attribute partType
  //
  np = prefix + "partType";
  get_node_element (cind, &doc, &np, _role);
  if (_role.empty ())
  {
	string error = string (
		"SPECIESLINK: empty attribute @partType in "
		) + doc + ".xml!";
	throw error;
  }
  else partType = _role[0];
}

void readXMLComponent::readReactionLink (
	const container_index& cind, 
	const string& doc,
	const string& qpath,
	const int& i,
	string& reactionReference,
	string& speciesRole 
	) 
{
  ostringstream oss;
  oss << "[" << i <<"]/";
  string prefix = qpath + string(oss.str ());

  string np;
  vector<string> _ref, _role;

  //
  //  read attribute reactionReference 
  //
  np = prefix + "reactionReference";
  get_node_element (cind, &doc, &np, _ref);
  if (_ref.empty ())
  {
	string error = string (
		"REACTIONLINK: empty attribute @reactionReference in "
		) + doc + ".xml!";
	throw error;
  }
  else reactionReference = _ref[0];

  //
  //  read attribute speciesRole
  //
  np = prefix + "speciesRole";
  get_node_element (cind, &doc, &np, _role);
  if (_role.empty ())
  {
	string error = string (
		"REACTIONLINK: empty attribute @speciesRole in "
		) + doc + ".xml!";
	throw error;
  }
  else speciesRole = _role[0];
}

void readXMLComponent::readUnit (
	const container_index& cind,
	const string& doc,
	const string& qpath,
	const int& i,
	string& kind,
	double& exponent,
	int& scale,
	double& multiplier
	)
{
  ostringstream oss;
  oss << "[" << i <<"]/";
  string prefix = qpath + string(oss.str ());

  string np;
  vector<string> temp;

  //
  //  read attribute kind 
  //
  np = prefix + "kind";
  get_node_element (cind, &doc, &np, temp);
  if (temp.empty ())
  {
	string error = string (
		"UNIT: empty attribute @kind in "
		) + doc + ".xml!";
	throw error;
  }
  else kind = temp[0];

  //
  //  read attribute exponent
  //
  np = prefix + "exponent";
  get_node_element (cind, &doc, &np, temp);
  if (!temp.empty ()) exponent = atoi (temp[0].c_str ()); 
  else exponent = 1;

  //
  //  read attribute scale
  //
  np = prefix + "scale";
  get_node_element (cind, &doc, &np, temp);
  if (!temp.empty ()) scale = atoi (temp[0].c_str ()); 
  else scale = 0;

  //
  //  read attribute double
  //
  np = prefix + "multiplier";
  get_node_element (cind, &doc, &np, temp);
  if (!temp.empty ()) multiplier = atof (temp[0].c_str ()); 
  else multiplier = 1;
}

void readXMLComponent::readFunctionDef (
	const container_index& cind,
	const string& doc,
	const string& qpath,
	const int& i,
	string& id,
	string& name,
	string& math
	)
{
  ostringstream oss;
  oss << "[" << i <<"]/";
  string prefix = qpath + string(oss.str ());

  string np;
  vector<string> temp;

  //
  //  read attribute kind 
  //
  np = prefix + "id";
  get_node_element (cind, &doc, &np, temp);
  if (temp.empty ())
  {
	string error = string (
		"FUNCTION: empty attribute @id in "
		) + doc + ".xml!";
	throw error;
  }
  else id = temp[0];

  //
  //  read attribute name
  //
  np = prefix + "name";
  get_node_element (cind, &doc, &np, temp);
  if (!temp.empty ()) name = temp[0];

  //
  //  read attribute math
  //
  np = prefix + "math";
  get_node (cind, &doc, &np, math);
}
