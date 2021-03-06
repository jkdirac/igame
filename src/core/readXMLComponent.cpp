#include "readXMLComponent.h"
#include "DebugOut.h"

readXMLComponent::readXMLComponent ()
{
	//	set partCtg
	partCtg_set.insert ("biobrick");
	partCtg_set.insert ("plasmidBackbone");
	partCtg_set.insert ("compound");
	partCtg_set.insert ("substituent");
	partCtg_set.insert ("compartment");	

	//	set partType
	partType_set.insert ("DNA");
	partType_set.insert ("RNA");
	partType_set.insert ("Protein");
	partType_set.insert ("ForwardDNA");
	partType_set.insert ("ForwardRNA");
	partType_set.insert ("ForwardProtein");
	partType_set.insert ("ReverseDNA");
	partType_set.insert ("ReverseRNA");
	partType_set.insert ("ReverseProtein");
	partType_set.insert ("Compound");
	partType_set.insert ("Compartment");
	
	//	set speciesType
	speciesType_set.insert ("reactant");
	speciesType_set.insert ("modifier");
	speciesType_set.insert ("product");

	//	set substituentType 
	substituentType_set.insert ("ANY");
	substituentType_set.insert ("ANYUB");
	substituentType_set.insert ("NZ");
	substituentType_set.insert ("NZUB");
	substituentType_set.insert ("ONE");
	substituentType_set.insert ("ONEUB");
}

readXMLComponent::~readXMLComponent ()
{}

void readXMLComponent::readPart (
		const container_index& cind,
		const string& doc,
		const string& qpath,
		const int& i,
		string& __ref, 
		string& __label,
		string& __type,
		string& __ctg 
		)
{
	ostringstream oss;
	oss << qpath << "[" << i <<"]/";
	string prefix (oss.str ());

	vector<string> temp;

	//  read node partReference (mandatory)
	const string path_pr = prefix + "partReference";
	get_node_element (cind, &doc, &path_pr, temp); 
	if (temp.empty ())
	{
		string errno = string (
				"PART: empty node partReference in "
				) + doc + ".xml!";
		throw CoreException (errno);
	}
	else __ref = temp[0];

	//  read node partLabel (optional)
	const string path_pl = prefix + "partLabel";
	get_node_element (cind, &doc, &path_pl, temp); 
	if (!temp.empty ()) __label = temp[0];

	//  read node partCategory
	const string path_pc = prefix + "partCategory";
	get_node_element (cind, &doc, &path_pc, temp); 
	if (temp.empty ())
	{
		string errno = string (
				"PART: empty node partCategory in "
				) + doc + ".xml!";
		throw CoreException (errno);
	}
	else __ctg = temp[0];

	if (__ctg == "substituent" && !substituentType_set.count (__ref))
		throw CoreException (
				"PART: invalid substituent-type part Reference!"
				);

	//	check if it is invalid
	if (!temp.empty () && !partCtg_set.count (__ctg))
	{
		string errno = string (
				"PART: Invalid partCategory value in "
				) + doc + ".xml!";
		throw CoreException (errno);
	}

	//
	//  read node partType (optional)
	//
	const string path_pt = prefix + "partType";
	get_node_element (cind, &doc, &path_pt, temp); 
	if (!temp.empty ()) __type = temp[0];
	else if (__ctg != "substituent") 
	{
		string errno = string (
				"PART: empty node partType for"
			    " non-substituent type part in "
				) + doc + ".xml!";
		throw CoreException (errno);
	}

	//	check if it is invalid
	if (!temp.empty () && !partType_set.count (__type))
	{
		string errno = string (
				"PART: Invalid partType value in "
				) + doc + ".xml!";
		throw CoreException (errno);
	}
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
	oss << qpath << "[" << i <<"]/";
	string prefix (oss.str ());

	vector<string> temp;

	//  read node currentNodeLabel
	const string path_cnl = prefix + "currentNodeLabel";
	get_node_element (cind, &doc, &path_cnl, temp); 
	if (temp.empty ())
	{
		string errno = string (
				"NODE: empty node currentNodeLabel in "
				) + doc + ".xml!";
		throw CoreException (errno);
	}
	else nCL = temp[0];

	//  read node parentNodeLabel
	const string path_pnl = prefix + "parentNodeLabel";
	get_node_element (cind, &doc, &path_pnl, temp); 
	if (temp.empty ())
	{
		string errno = string (
				"NODE: empty node parentNodeLabel in "
				) + doc + ".xml!";
		throw CoreException (errno);
	}
	else nPL = temp[0];
}

void readXMLComponent::readSpecies (
		const container_index& cind,
		const string& doc,
		const string& qpath,
		const int& i,
		string& speciesReference,
		string& speciesLabel,
		string& compartmentLabel,
		string& ccid
		)
{
	ostringstream oss;
	oss << qpath << "[" << i << "]/";
	string prefix (oss.str ());

	vector<string> temp;

	//
	//  read node speciesReference
	//
	const string path_srf = prefix + "speciesReference";
	get_node_element (cind, &doc, &path_srf, temp); 
	if (temp.empty ())
	{
		string errno = string (
				"SPECIES: empty node speciesReference in "
				) + doc + ".xml!";
		throw CoreException (errno);
	}
	else speciesReference = temp[0];

	//
	//  read node speciesLabel
	//
	const string path_sl = prefix + "speciesLabel";
	get_node_element (cind, &doc, &path_sl, temp); 
	if (temp.empty ())
	{
		string errno = string (
				"SPECIES: empty node speciesLabel in "
				) + doc + ".xml!";
		throw CoreException (errno);
	}
	else speciesLabel = temp[0];

	//
	//  read node compartmentLabel
	//
	const string path_cl = prefix + "compartmentLabel";
	get_node_element (cind, &doc, &path_cl, temp); 
	if (temp.empty ())
	{
		string errno = string (
				"SPECIES: empty node compartmentLabel in "
				) + doc + ".xml!";
		throw CoreException (errno);
	}
	else compartmentLabel = temp[0];

	//	read attribute itself
	const string path_rel = prefix + "compartmentLabel/@itself";
	get_node_attr (cind, &doc, &path_rel, temp);
	if (!temp.empty ()) ccid = temp[0];
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
	oss << qpath << "[" << i <<"]/";
	string prefix (oss.str ());

	vector<string> temp; 

	//  read node compartmentLabel
	const string path_compref = prefix + "compartmentReference";
	get_node_element (cind, &doc, &path_compref, temp); 
	if (temp.empty ())
	{
		string errno = string (
				"COMPARTMENT: empty node compartmentReference in "
				) + doc + ".xml!";
		throw CoreException (errno);
	}
	else compartmentReference = temp[0];

	//  read node currentCompartmentLabel
	const string path_curr = prefix + "currentCompartmentLabel";
	get_node_element (cind, &doc, &path_curr, temp); 
	if (temp.empty ())
	{
		string errno = string (
				"COMPARTMENT: empty node currentCompartmentLabel in "
				) + doc + ".xml!";
		throw CoreException (errno);
	}
	else currentCompartmentLabel = temp[0];

	//
	//  read node parentCompartmentLabel
	//
	const string path_par = prefix + "parentCompartmentLabel";
	get_node_element (cind, &doc, &path_par, temp); 
	if (temp.empty ())
	{
		string errno = string (
				"COMPARTMENT: empty node parentCompartmentLabel in "
				) + doc + ".xml!";
		throw CoreException (errno);
	}
	else parentCompartmentLabel = temp[0];
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
	oss << qpath << "[" << i << "]/";
	string prefix (oss.str ());

	vector<string> temp; 

	//
	//  read component from
	//
	const string path_from = prefix + "from";
	
	//
	//	read attribute speciesLabel
	const string path_from_sl = path_from + "/@speciesLabel";
	get_node_attr (cind, &doc, &path_from_sl, temp); 
	if (temp.empty ())
	{
		string errno = string (
				"TRANSFER: empty attribute speciesLabel in "
				) + doc + ".xml!";
		throw CoreException (errno);
	}
	else from.first = temp[0];

	//
	//  read node from
	//
	get_node_element (cind, &doc, &path_from, temp); 
	if (temp.empty ())
	{
		debugOut() << "\nnodepath = " 
			 << path_from 
			 << endl;

		string errno = string (
				"TRANSFER: empty node from in "
				) + doc + ".xml!";
		throw CoreException (errno);
	}
	else from.second = temp[0];

	//
	//  read component to
	//
	const string path_to = prefix + "to";
	
	//
	//	read attribute speciesLabel
	//
	const string path_to_sl = path_to + "/@speciesLabel";
	get_node_attr (cind, &doc, &path_to_sl, temp); 
	if (temp.empty ())
	{
		string errno = string (
				"TRANSFER: empty attribute speciesLabel in "
				) + doc + ".xml!";
		throw CoreException (errno);
	}
	else to.first = temp[0];

	//
	//  read node to
	//
	get_node_element (cind, &doc, &path_to, temp); 
	if (temp.empty ())
	{
		debugOut() << "\nnodepath = " 
			 << path_to 
			 << endl;

		string errno = string (
				"TRANSFER: empty node to in "
				) + doc + ".xml!";
		throw CoreException (errno);
	}
	else to.second = temp[0];

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
		throw CoreException (errno);
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
		throw CoreException (errno);
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
		throw CoreException (errno);
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
		throw CoreException (errno);
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
	const string path_ccid = 
		prefix + "compartment/@itself";
	get_node_attr (cind, &doc, &path_ccid, temp);
	if (!temp.empty ()) ccid = temp[0];

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
		throw CoreException (errno);
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
		throw CoreException (errno);
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
	const string path_initC = prefix + "initialConcentration";
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
		throw CoreException (errno);
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
	if (temp.empty ()) constant = false;
	else constant = (temp[0] == "true");

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
		throw CoreException (errno);
	}
	else variable = temp[0];

	//
	//  read attribute math
	//
	const string path_math = prefix + "math";
	if (text)
	{
		get_node_element (cind, &doc, &path_math, temp);
		if (temp.empty ())
		{
			string errno = string (
					"RULE: empty node math in "
					) + doc + ".xml!";
			throw CoreException (errno);
		}
		else math = temp[0];
	}
	else
	{
		string res;
		get_node (cind, &doc, &path_math, res);
		if (res.empty ())
		{
			string errno = string (
					"RULE: empty node math in "
					) + doc + ".xml!";
			throw CoreException (errno);
		}
		else math = res;
	}
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
	oss << qpath << "[" << i <<"]";
	string prefix (oss.str ());

	vector<string> temp;

	//
	//  read node referencedSpecies
	//
	get_node_element (cind, &doc, &prefix, temp);
	if (temp.empty ())
	{
		string errno = string (
				"\nReferencedSpecies:"
			   	" empty node referencedSpcies in "
				) + doc + ".xml!";
		throw CoreException (errno);
	}
	else speciesReference = temp[0];

	//
	//  read attribute partType
	//
	const string path_ptype = prefix + "/@partType";
	get_node_attr (cind, &doc, &path_ptype, temp);
	if (!temp.empty ()) partType = temp[0];
}

void readXMLComponent::readReactionLink (
		const container_index& cind, 
		const string& doc,
		const string& qpath,
		const int& i,
		string& reactionReference,
		string& speciesType 
		) 
{
	ostringstream oss;
	oss << qpath << "[" << i <<"]";
	string prefix (oss.str ());

	vector<string> temp;

	//
	//  read node referencedReaction
	//
	get_node_element (cind, &doc, &prefix, temp);
	if (temp.empty ())
	{
		string errno = string (
				"ReferencedReaction: empty node referencedReaction in "
				) + doc + ".xml!";
		throw CoreException (errno);
	}
	else reactionReference = temp[0];

	//
	//  read attribute speciesType
	//
	const string path_stype = prefix + "/@speciesType";
	get_node_attr (cind, &doc, &path_stype, temp);
	if (temp.empty ())
	{
		string errno = string (
				"\nReferencedReaction: empty attribute @speciesType in "
				) + doc + ".xml!";
		throw CoreException (errno);
	}
	else 
	{
		set<string> validSpeciesType;

		validSpeciesType.insert ("reactant");
		validSpeciesType.insert ("modifier");
		validSpeciesType.insert ("product");

		if (!validSpeciesType.count (temp[0]))
		{
			string errno = string (
					"\nReferencedReaction: invalid speciesType value in "
					) + doc + ".xml";
			throw CoreException (errno);
		}
		else speciesType = temp[0];
	}
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
		throw CoreException (errno);
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
		throw CoreException (errno);
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
		throw CoreException (errno);
	}
}

void readXMLComponent::readExternalRef (
		const container_index& cind,
		const string& doc,
		const string& qpath,
		const int& i,
		string& id,
		string& speciesLabel,
		string& partLabel,
		string& parameterLabel
		)
{
	ostringstream oss;

	//	node path
	oss << qpath << "[" << i <<"]/";
	const string prefix (oss.str ());

	vector<string> temp;

	//
	//  read node id 
	//
	const string path_id = prefix + "id";
	get_node_element (cind, &doc, &path_id, temp);
	if (temp.empty ())
	{
		string errno = string (
				"REACTION: empty node id (extRef) in "
				) + doc + ".xml!";
		throw CoreException (errno);
	}
	else id = temp[0];

	//
	//	read node extRefSource
	//

	const string path_ext = prefix + "extRefSource";
	get_node_element (cind, &doc, &path_ext, temp);
	if (temp.empty ())
	{
		string errno = string (
				"REACTION: empty node extRefSource in "
				) + doc + ".xml!";
		throw CoreException (errno);
	}
	else parameterLabel = temp[0];

	//	
	//	read attribute speciesLabel
	//
	
	const string path_sl = path_ext + "/@speciesLabel";
	get_node_attr (cind, &doc, &path_sl, temp);
	if (temp.empty ())
	{
		string errno = string (
				"REACTION: empty attribute speciesLabel (extRef) in "
				) + doc + ".xml!";
		throw CoreException (errno);
	}
	else speciesLabel = temp[0];

	//
	//	read attribute partLabel
	//
	
	const string path_pl = path_ext + "/@partLabel";
	get_node_attr (cind, &doc, &path_pl, temp);
	if (temp.empty ())
	{
		string errno = string (
				"REACTION: empty attribute partLabel (extRef) in "
				) + doc + ".xml!";
		throw CoreException (errno);
	}
	else partLabel = temp[0];
}	

void readXMLComponent::readConditionalParameter (
		const container_index& cind,
		const string& dir,
		const string& doc,
		const string& para,
		const string& comp,
		double& value,
		string& units,
		string& name
		)
{
//    debugOut() << "\ndir = " << dir << " doc = " << doc << 
//        " para = " << para << " comp = " << comp << endl;

	//	search conditional parameter value
	string nodepath;
	nodepath = string ("/MoDeL/part/") + dir +
		"/listOfConditionalParameters/"
		"conditionalParameter[@id=\""
		+ para + "\"]/parameterValue[@compartment=\""
		+ comp + "\"]";

	vector<string> temp;

	get_node_element (cind, &doc, &nodepath, temp);
	if (temp.empty ())
	{
		nodepath = string ("/MoDeL/part/") + dir +
			"/listOfConditionalParameters/"
			"conditionalParameter[@id=\""
			+ para + "\"]/@commonValue";

		get_node_attr (cind, &doc, &nodepath, temp);
		if (temp.empty ())
		{
			//	read default
			const string doc1 ("defaults");
			string defaultpath;
			defaultpath = string ("/MoDeL/part/") + 
				"listOfValueDefaults/"
				"valueDefault[@id=\""
				+ para + "\"]";
			get_node_element (cind, &doc1, &defaultpath, temp);
			if (temp.empty ())
			{
				string errno = string (
						"DEFAULT: no default value: "
						) + para + " , in " + doc1 + ".xml!";
				throw CoreException (errno);
			}
			else value = atof (temp[0].c_str ());
		}
		else value = atof (temp[0].c_str ());
	}
	else value = atof (temp[0].c_str ());

	//	
	//	read units
	//
	nodepath = string ("/MoDeL/part/") + dir +
		"/listOfConditionalParameters/"
		"conditionalParameter[@id=\""
		+ para + "\"]/@units";

//    debugOut() << "\nnodepath = " << nodepath << endl;
	get_node_attr (cind, &doc, &nodepath, temp);
	if (!temp.empty ()) units = temp[0];

	//	
	//	read name
	//
	nodepath = string ("/MoDeL/part/") + dir +
		"/listOfConditionalParameters/"
		"conditionalParameter[@id=\""
		+ para + "\"]/@name";

	get_node_attr (cind, &doc, &nodepath, temp);
	if (!temp.empty ()) name = temp[0];
}

void readXMLComponent::readConstraint (
		const container_index& cind,
		const string& doc,
		const string& qpath,
		const int& i,
		vector<string>& vars,
		string& formula
		)
{
	ostringstream oss;

	//	node path
	oss << qpath << "[" << i <<"]/";
	const string prefix (oss.str ());

	vector<string> temp;

	//
	//  read variables 
	//
	const string path_vars (
			prefix + "listOfVariables/variable"
			);
	const int numOfVars = get_node_element_num (cind, &doc, &path_vars);
	if (numOfVars == 0)
	{
		string errno = string (
				"REACTION: no variables defined in "
				) + doc + ".xml!";
		throw CoreException (errno);
	}
	else
	{
		for (int i=1; i <= numOfVars; i++)
		{
			oss.str ("");
			oss << path_vars << "[" << i << "]";
			const string pathVar_text (oss.str ());
			get_node_element (cind, &doc, &pathVar_text, temp);
			if (!temp.empty ()) vars.push_back (temp[0]);
		}
	}

	//
	//	read formula
	//
	const string path_formula (
			prefix + "formula"
			);
	get_node_element (cind, &doc, &path_formula, temp);
	if (temp.empty ())
	{
		string errno = string (
				"REACTION: no formula defined in "
				) + doc + ".xml!";
		throw CoreException (errno);
	}
	else formula = temp[0];
}
