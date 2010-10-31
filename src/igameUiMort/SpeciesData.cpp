#include "SpeciesData.h"
#include "MScene.h"
#include "MItem.h"
#include "InputGen.h"
#include <QDebug>

void SpeciesData::init()
{
	//compartment
	m_compartSize = "0.10"; // 0.10
	m_constant = "true";
	m_InitConcentration = "4.15135E-24"; //"4.15135E-24"

	//part
	m_partType = "ForwardDNA"; // "ForwardDNA"
}

SpeciesData::SpeciesData()
{
	m_item = NULL;
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

	if ((m_item == NULL)
			|| (type() != SPEC_COMPARTMENT))
	{
		return "";
	}

	MScene* sce = m_item->getScene();
	if ((sce == NULL)
			|| (!sce->itemInCompartment(m_item)))
	{
		return "";
	}

	res += "  <compartment db=\""; res += m_dbId; res += "\">\n";
	res += "    <id>"; res += fileId(); res+="</id>\n";
	res += "    <size>"; res += m_compartSize;  res += "</size>\n";
	res += "    <outside>"; res += m_parent; res += "</outside>\n";
	res += "    <constant>"; res += constant(); res += "</constant>\n";
	res += "  </compartment>\n";

	return res;
}

QString SpeciesData::generateSpeciesXmlString()
{
	QString res;
	res.clear();

	qDebug() << "SpeciesData generate species xml string";
	//no dbid
//    res += "<species>\n";
	QString specId = "sPecIes";
	specId += QString::number(InputGen::getSpecNo());
	InputGen::incSpecNo();
	res += "  <id>"; res += specId; res += "</id>\n";
	res += "  <compartment>"; res += parent(); res += "</compartment>\n";

	if ((type() == SPEC_COMPARTMENT) || (type() == SPEC_COMPOUNDS))
	{
		res += "  <initialConcentration>"; res += initConcentration(); res += "</initialConcentration>\n";
	}

	res += "  <constant>"; res += constant(); res += "</constant>\n";
//    res += "<cnModel>\n";
//    res += "<listOfChains>\n";
//    res += "<chain>\n";
//    res += "<listOfParts>\n";
//    res += generatePartsXmlString();
//    res += "</listOfParts>\n";
//    res += "</chain>\n";
//    res += "</listOfChains>\n";
//    res += "</cnModel>\n";
//    res += "</species>\n";

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

	res += "          <part>\n";
	res += "            <partReference>"; res+=id(); res += "</partReference>\n";
	if ((type() == SPEC_BIOBRICK)
			|| (type() == SPEC_BACKBONE))
	{
		res += "            <partLabel>"; res+=fileId(); res += "</partLabel>\n";
	}
	res += "            <partType>"; res+=partType(); res += "</partType>\n";
	res += "            <partCategory>"; res+=partCategory(); res += "</partCategory>\n";
	res += "          </part>\n";

	return res;
}

void SpeciesData::setInputNo(int nm)
{
	m_fileId += "_i";

	m_fileId += QString::number(nm);
}

void SpeciesData::setType(SPECIESTYPE type) 
{ 
	m_type = type; 

	if (m_type == SPEC_COMPARTMENT)
	{
		m_constant = "true";
		m_partType = "Compartment";
		m_partCatgory = "compartment";
	}
	if (m_type == SPEC_BACKBONE)
	{
		m_constant = "false";
		m_partType = "ForwardDNA";
		m_partCatgory = "biobrick";
	}
	if (m_type == SPEC_COMPOUNDS)
	{
		m_partType = "Compound";
		m_partCatgory = "compound";
	}
	if (m_type == SPEC_BIOBRICK)
	{
		m_partCatgory = "biobrick";
	}
};
