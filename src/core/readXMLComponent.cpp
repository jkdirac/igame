#include "readXMLComponent.h"

readXMLComponent::readXMLComponent ()
{}

readXMLComponent::~readXMLComponent ()
{}

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
		string& db,
		string& id,
		string& name,
		double& value,
		string& units,
		bool& constant
		)
{
	ostringstream oss;
	oss << qpath << "[" << i <<"]/";
	string prefix (oss.str ());

	vector<string> temp;

	//
	//	read attribute db
	//
	const string part_db = prefix + "@db";
	get_node_attr (cind, &doc, &part_db, temp);
	if (!temp.empty ()) db = temp[0];

	//
	//  read node id
	//
	const string path_id = prefix + "id";
	get_node_element (cind, &doc, &path_id, temp); 
	if (temp.empty ())
	{
		string errno (
				string ("PARAMETER: empty attribute @id in "
					) + doc + ".xml!"
				);
		throw StrCacuException (errno);
	}
	else id = temp[0];

	//
	//  read node name
	//
	const string path_name = prefix + "name";
	get_node_element (cind, &doc, &path_name, temp); 
	if (!temp.empty ()) name = temp[0];

	//
	//  read node value 
	//
	const string path_value = prefix + "value";
	get_node_element (cind, &doc, &path_value, temp);
	if (!temp.empty ()) 
		value = atof (temp[0].c_str ());
	else value = 0.0;

	//
	//  read node units
	//
	const string path_units = prefix + "units";
	get_node_element (cind, &doc, &path_units, temp);
	if (!temp.empty ()) units = temp[0];

	//
	//  read node constant
	//
	const string path_const = prefix + "constant";
	get_node_element (cind, &doc, &path_const, temp);
	if (!temp.empty ()) 
		constant = (temp[0] == "true"); 
	else constant = true;
}

void readXMLComponent::readCompartment (
		const container_index& cind,
		const string& doc, 
		const string& qpath, 
		const int& i, 
		string& db,
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
	oss << qpath << "[" << i <<"]/";
	string prefix (oss.str ());

	vector<string> temp;

	//	read attribute db
	const string path_db = prefix + "@db";
	get_node_attr (cind, &doc, &path_db, temp);
	if (temp.empty ())
	{
		string errno = string (
				"COMPARTMENT: empty attribute @db in "
				) + doc + ".xml!";
		throw StrCacuException (errno);
	}
	else db = temp[0];

	//
	//  read node id
	//
	const string path_id = prefix + "id";
	get_node_element (cind, &doc, &path_id, temp); 
	if (temp.empty ())
	{
		string errno = string (
				"COMPARTMENT: empty node @id in "
				) + doc + ".xml!";
		throw StrCacuException (errno);
	}
	else id = temp[0];

	//
	//  read node name
	//
	const string path_name = prefix + "name";
	get_node_element (cind, &doc, &path_name, temp); 
	if (!temp.empty ()) name = temp[0];

	//
	//  read node spatialDimensions
	//
	const string path_dim = prefix + "spatialDimensions";
	get_node_element (cind, &doc, &path_dim, temp);
	if (!temp.empty ())
		spatialDimensions = atoi (temp[0].c_str ());
	else spatialDimensions = 3;

	//
	//  read node size
	//
	const string path_size = prefix + "size";
	get_node_element (cind, &doc, &path_size, temp);
	if (temp.empty ()) size = -1.0;
	else size = atof (temp[0].c_str ());

	//
	//  read node units
	//
	const string path_units = prefix + "units";
	get_node_element (cind, &doc, &path_units, temp);
	if (!temp.empty ()) units = temp[0];

	//
	//  read node outside
	//
	const string path_out = prefix + "outside";
	get_node_element (cind, &doc, &path_out, temp); 
	if (temp.empty ())
	{
		string errno = string (
				"COMPARTMENT: empty node @outside in "
				) + doc + ".xml!";
		throw StrCacuException (errno);
	}
	else outside = temp[0];

	//
	//  read node constant
	//
	const string path_const = prefix + "constant";
	get_node_element (cind, &doc, &path_const, temp);
	if (!temp.empty ()) 
		constant = (temp[0] == "true"); 
	else constant = true;
}

void readXMLComponent::readSpecies (
		const container_index& cind, 
		const string& doc,
		const string& qpath,
		const int& i,
		string& db,
		string& ccid,
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
	oss << qpath  << "[" << i <<"]/";
	string prefix (oss.str ());

	vector<string> temp;

	//
	//	read attribute db
	//
	const string path_db = prefix + "@db";
	get_node_attr (cind, &doc, &path_db, temp);
	if (!temp.empty ()) db = temp[0];

	//
	//	read attribute ccid
	//
	const string path_ccid = prefix + "@ccid";
	get_node_attr (cind, &doc, &path_db, temp);
	if (temp.empty ())
	{
		string errno = string (
				"SPECIES: empty attribute @ccid in "
				) + doc + ".xml!";
	}
	else ccid = temp[0];

	//
	//  read node id
	//
	const string path_id = prefix + "id";
	get_node_element (cind, &doc, &path_id, temp); 
	if (temp.empty ())
	{
		string errno = string (
				"SPECIES: empty node id in "
				) + doc + ".xml!";
		throw StrCacuException (errno);
	}
	else id = temp[0];

	//
	//  read node name
	//
	const string path_name = prefix + "name";
	get_node_element (cind, &doc, &path_name, temp); 
	if (!temp.empty ()) name = temp[0];

	//
	//  read node compartment 
	//
	const string path_comp = prefix + "compartment";
	get_node_element (cind, &doc, &path_comp, temp); 
	if (temp.empty ())
	{
		string errno = string (
				"SPECIES: empty node compartment in "
				) + doc + ".xml!";
		throw StrCacuException (errno);
	}
	else compartment = temp[0];

	//
	//  read node initialAmount
	//
	const string path_initA = prefix + "initialAmount";
	get_node_element (cind, &doc, &path_initA, temp); 
	if (temp.empty ()) initialAmount = -1;
	else initialAmount = atof (temp[0].c_str ());

	//
	//  read node initialConcentration
	//
	const string path_initC = prefix + "initialConcentrationt";
	get_node_element (cind, &doc, &path_initC, temp); 
	if (temp.empty ()) initialConcentration = -1;
	else initialConcentration = atof (temp[0].c_str ());

	if (initialAmount >= 0.0 && 
			initialConcentration >= 0.0)
	{
		string errno = string (
				"SPECIES: only one of initialAmount/initialConcentration"
				" could be set to indicate species' initial quantity!"
				) + doc + ".xml!";
		throw StrCacuException (errno);
	}

	//
	//  read node substanceUnits
	//
	const string path_subunit = prefix + "substanceUnits";
	get_node_element (cind, &doc, &path_subunit, temp); 
	if (!temp.empty ()) substanceUnits = temp[0];

	//
	//  read node hasOnlySubstanceUnits
	//
	const string path_hos = prefix + "hasOnlySubstanceUnits";
	get_node_element (cind, &doc, &path_hos, temp); 
	if (temp.empty ()) hasOnlySubstanceUnits = false;
	else hasOnlySubstanceUnits = (temp[0] == "true");

	//
	//  read node constant
	//
	const string path_const = prefix + "constant";
	get_node_element (cind, &doc, &path_const, temp); 
	if (temp.empty ()) constant = true;
	else constant = (temp[0] == "true");

	//
	//  read node charge
	//
	const string path_charge = prefix + "charge";
	get_node_element (cind, &doc, &path_charge, temp); 
	if (temp.empty ()) charge = 0;
	else charge = atoi (temp[0].c_str ());

	//
	//  read node boundaryCondition
	//
	const string path_bc = prefix + "boundaryCondition";
	get_node_element (cind, &doc, &path_bc, temp); 
	if (temp.empty ()) boundaryCondition = false;
	else boundaryCondition = (temp[0] == "true");
}

void readXMLComponent::readRule (
		const container_index& cind, 
		const string& doc,
		const string& qpath,
		const int& i,
		string& variable,
		string& math,
		const bool& text
		)
{
	ostringstream oss;
	oss << "[" << i <<"]/";
	string prefix = qpath + string(oss.str ());

	vector<string> temp;
	string temp1;

	//
	//  read attribute variable
	//
	const string path_var = prefix + "variable";
	get_node_element (cind, &doc, &path_var, temp); 
	if (temp.empty ())
	{
		string errno = string (
				"RULE: empty node variable in "
				) + doc + ".xml!";
		throw StrCacuException (errno);
	}
	else variable = temp[0];

	//
	//  read attribute math
	//
	const string path_math = prefix + "math";
	if (text)
		get_node_element (cind, &doc, &path_math, temp);
	else get_node (cind, &doc, &path_math, temp1);
	if ((temp.empty () && text)
			|| (temp1.empty () && !text))
	{
		string errno = string (
				"RULE: empty node math in "
				) + doc + ".xml!";
		throw StrCacuException (errno);
	}
	else math = temp[0];
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
	oss << qpath << "[" << i <<"]/@";
	string prefix (oss.str ());

	string np;
	vector<string> temp;

	//
	//  read attribute kind 
	//
	np = prefix + "kind";
	get_node_attr (cind, &doc, &np, temp);
	if (temp.empty ())
	{
		string errno = string (
				"UNIT: empty attribute @kind in "
				) + doc + ".xml!";
		throw StrCacuException (errno);
	}
	else kind = temp[0];

	//
	//  read attribute exponent
	//
	np = prefix + "exponent";
	get_node_attr (cind, &doc, &np, temp);
	if (!temp.empty ()) exponent = atof (temp[0].c_str ()); 
	else exponent = 1.0;

	//
	//  read attribute scale
	//
	np = prefix + "scale";
	get_node_attr (cind, &doc, &np, temp);
	if (!temp.empty ()) scale = atoi (temp[0].c_str ()); 
	else scale = 0;

	//
	//  read attribute double
	//
	np = prefix + "multiplier";
	get_node_attr (cind, &doc, &np, temp);
	if (!temp.empty ()) multiplier = atof (temp[0].c_str ()); 
	else multiplier = 1.0;
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

	//	node path
	oss << qpath << "[" << i <<"]/";
	const string prefix1 (oss.str ());

	//	attribute path
	oss << "@";
	const string prefix2 (oss.str ());

	string np;
	vector<string> temp;

	//
	//  read attribute kind 
	//
	np = prefix2 + "id";
	get_node_attr (cind, &doc, &np, temp);
	if (temp.empty ())
	{
		string errno = string (
				"FUNCTION: empty attribute @id in "
				) + doc + ".xml!";
		throw StrCacuException (errno);
	}
	else id = temp[0];
	
	//
	//  read attribute name
	//
	np = prefix2 + "name";
	get_node_attr (cind, &doc, &np, temp);
	if (!temp.empty ()) name = temp[0];

	//
	//  read attribute math
	//
	np = prefix1 + "math";
	get_node (cind, &doc, &np, math);
	if (math.empty ())
	{
		string errno = string (
				"FUNCTION: empty node math in "
				) + doc + ".xml!";
		throw StrCacuException (errno);
	}
}
