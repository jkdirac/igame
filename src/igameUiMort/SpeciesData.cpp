#include "SpeciesData.h"

SpeciesData::SpeciesData()
{
}

SpeciesData::SpeciesData(SPECIESTYPE type, const QString& id, SPECIESTYPE parentType, const QString& parent)
{
	m_type = type;
	m_id = id;
	m_compartment = parent;
	m_parentType = parentType;
}

SpeciesData::SpeciesData(const SpeciesData &other)
{
	m_type = other.type();
	m_id = other.id();
	m_compartment = other.parent();
	m_parentType = other.parentType();
}

SpeciesData& SpeciesData::operator = (const SpeciesData &other)
{
	m_type = other.type();
	m_id = other.id();
	m_compartment = other.parent();
	m_parentType = other.parentType();

	return *this;
}

QString SpeciesData::generateCompartmentXmlString()
{
//    <compartment db="Chemostat">
//        <id>Chemostat</id>
//        <size>0.10</size>
//        <outside>ROOT</outside>
//        <constant>true</constant>
//        </compartment>
	QString res;
	res += "<compartment db=\""; res += m_id; res += "\">\n";
	res += "<id>"; res += m_id; res+="</id>\n";
	res += "<size>"; res += "0.10";  res += "</size>\n";
	res += "<outside>"; res += m_compartment; res += "</outside>\n";
	res += "<constant>"; res += "true"; res += "</constant>\n";
	res += "</compartment>\n";

	return res;
}

QString SpeciesData::generatePartsXmlString()
{
	QString res;
	res.clear();

	QString typeString;
	//        <part>
	//            <partReference>TE_X_100</partReference>
	//            <partLabel>TE_X_100_4</partLabel>
	//            <partType>ForwardDNA</partType>
	//            <partCategory>biobrick</partCategory>
	//            </part>

	//ignore the part/comparement types
	//because the ui forbid add compartment to plasmids
	if (m_type == SPEC_BIOBRICK)
		typeString = "biobrick";
	else if (m_type == SPEC_COMPOUNDS)
		typeString = "compound";
	else
		typeString = "comparement";

	res += "<part>\n";
	res += "<partReference>"; res+=m_id; res += "</partReference>\n";
	res += "<partLabel>"; res+=m_id; res += "</partLabel>\n";
	res += "<partType>"; res+="ForwardDNA"; res += "</partType>\n";
	res += "<partLabel>"; res+=typeString; res += "</partLabel>\n";
	res += "</part>\n";

	return res;
}
