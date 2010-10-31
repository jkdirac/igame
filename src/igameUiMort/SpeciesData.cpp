#include "SpeciesData.h"
#include <QDebug>

void SpeciesData::init()
{
	//compartment
	m_compartSize = "0.10"; // 0.10

	m_InitConcentration = "4.15135E-24"; //"4.15135E-24"

	if (m_type == SPEC_COMPARTMENT)
		m_constant = "true"; // true
	if (m_type == SPEC_BACKBONE)
		m_constant = "false";
	//part
	m_partType = "ForwardDNA"; // "ForwardDNA"
}

SpeciesData::SpeciesData()
{
	m_parentType = SPEC_COMPARTMENT;
	m_parent = "ROOT";
	init();
}

SpeciesData::SpeciesData(SPECIESTYPE type, const QString& id, SPECIESTYPE parentType, const QString& parent)
{
	m_type = type;
	m_dbId = id;
	m_parent = parent;
	m_parentType = parentType;
	init();
}

SpeciesData::SpeciesData(const SpeciesData &other)
{
	m_type = other.type();
	m_dbId = other.id();
	m_parent = other.parent();
	m_parentType = other.parentType();
}

SpeciesData& SpeciesData::operator = (const SpeciesData &other)
{
	m_type = other.type();
	m_dbId = other.id();
	m_parent = other.parent();
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

	qDebug() << "SpeciesData generate compartment xml string";

	res += "<compartment db=\""; res += m_dbId; res += "\">\n";
	res += "\t<id>"; res += m_dbId; res+="</id>\n";
	res += "\t<size>"; res += m_compartSize;  res += "</size>\n";
	res += "\t<outside>"; res += m_parent; res += "</outside>\n";
	res += "\t<constant>"; res += m_constant; res += "</constant>\n";
	res += "</compartment>\n";

	return res;
}

QString SpeciesData::generateSpeciesXmlString()
{
	QString res;
	res.clear();

	qDebug() << "SpeciesData generate species xml string";
	//no dbid
	res += "<species db="; res += m_dbId; res += ">\n";
	res += "\t<id>"; res += m_dbId; res += "</id>\n";
	res += "\t<compartment>"; res += m_parent; res += "</compartment>\n";
	res += "\t<initialConcentration>"; res += m_InitConcentration; res += "</initialConcentration>\n";
	res += "</species>\n";

	return res;
}

QString SpeciesData::generatePartsXmlString()
{
	QString res;
	res.clear();

	qDebug() << "SpeciesData generate parts xml string";
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
	res += "\t<partReference>"; res+=m_dbId; res += "</partReference>\n";
	res += "\t<partLabel>"; res+=m_dbId; res += "</partLabel>\n";
	res += "\t<partType>"; res+="ForwardDNA"; res += "</partType>\n";
	res += "\t<partLabel>"; res+=typeString; res += "</partLabel>\n";
	res += "\t</part>\n";

	return res;
}
