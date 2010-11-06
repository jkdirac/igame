#include "SpeciesData.h"
#include "MScene.h"
#include "MItem.h"
#include "InputGen.h"
#include "bdbInterface.h"

#include <QDebug>
#include <vector>
#include <string>

using namespace std;

void SpeciesData::init()
{
	//compartment
	/*
	m_compartSize = "7E-16"; // 0.10
	m_InitConcentration = "2.37E-9"; //"4.15135E-24"
	*/
	m_speciesId = "";
	//part
	m_constant = "false";
	m_partType = "ForwardDNA"; // "ForwardDNA"
	m_InitConcentration = "2.37E-9"; //"4.15135E-24"
}

void SpeciesData::initFromDb(SPECIESTYPE type)
{
	bdbXMLInterface interface;

	if (type == SPEC_COMPARTMENT)
	{
		string doc = id().toLatin1().constData();
		string path = "/MoDeL/compartment/@size";
		vector<string> res; 

		try
		{
			interface.get_node_attr(COMPARTMENT, &doc, &path, res);
			qDebug() << "succss get init size";
			m_compartSize = res[0].c_str();
		}
		catch (XmlException &se)
		{
			m_compartSize = "0.10";
		}
	}
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

QString SpeciesData::generateRuleFuncXmlString()
{
//    <assignmentRule>
//        <variable>sPecIes1</variable>
//        <math>square_wave (t, ts, te, s)</math>
//        </assignmentRule>
	QString res;
	res.clear();

	qDebug() << "SpeciesData generate species rule function xml string";
	QString specId = "sPecIes";
	specId += speciesId();
	for (int i=0; i<ruleNum(); i++)
	{
		res+="    <assignmentRule>\n";
		res+="        <variable>" + specId + "</variable>\n";
		res+="        <math>" + getRuleList()[i]->rule() + "</math>\n";
		res+="    </assignmentRule>\n";
	}

	return res;
}

QString SpeciesData::generateParameterXmlString()
{
	QString res;
	res.clear();

	qDebug() << "SpeciesData generate species rule function xml string";
	QString specId = "sPecIes";
	specId += speciesId();
	for (int i=0; i<ruleNum(); i++)
	{
			RuleData* ruleData = getRuleList()[i];
			for (int k=0; k<ruleData->parameters().size(); k++)
			{
				ParameterData* data = (ruleData->parameters())[k];
				res += "  <parameter>\n";
				res += "    <id>" + data->id() + "</id>\n";
				res += "    <value>" + data->value() + "</value>\n";
				res += "    <units>" + data->units() + "</units>\n";
				res += "    <constant>" + data->constant() + "</constant>\n";
				res += "  </parameter>\n";
			}
	}

	return res;
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
	res += "    <id>"; res += fileComId(); res+="</id>\n";
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
	specId += speciesId();
	res += "  <id>"; res += specId; res += "</id>\n";
	if (type() == SPEC_COMPARTMENT)
	{
		res += "  <compartment itself=\""; res += fileComId(); res += "\">"; res += parent(); res += "</compartment>\n";
	}
	else
	{
		res += "  <compartment>"; res += parent(); res += "</compartment>\n";
	}

	if ((type() == SPEC_COMPARTMENT) || (type() == SPEC_COMPOUNDS)
			|| (type() == SPEC_BACKBONE))
	{
		res += "  <initialConcentration>"; res += initConcentration(); res += "</initialConcentration>\n";
	}

	res += "  <constant>"; res += constant(); res += "</constant>\n";

	if (ruleNum() != 0)
	{
		res += "  <boundaryCondition> true </boundaryCondition>\n";
	}
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
	res += "            <partLabel>"; res+=filePartId(); res += "</partLabel>\n";
	res += "            <partType>"; res+=partType(); res += "</partType>\n";
	res += "            <partCategory>"; res+=partCategory(); res += "</partCategory>\n";
	res += "          </part>\n";

	return res;
}

void SpeciesData::setInputNo(int nm)
{
	m_fileComId += "_i";
	m_filePartId += "_i";

	m_fileComId += QString::number(nm);
	m_filePartId += QString::number(nm+1);
}

void SpeciesData::setType(SPECIESTYPE type) 
{ 
	m_type = type; 

	if (m_type == SPEC_COMPARTMENT)
	{
//        m_constant = "false";
		m_partType = "Compartment";
		m_partCatgory = "compartment";
	}
	if (m_type == SPEC_BACKBONE)
	{
//        m_constant = "false";
		m_partType = "ForwardDNA";
		m_partCatgory = "biobrick";
	}
	if (m_type == SPEC_COMPOUNDS)
	{
//        m_constant = "false";
		m_partType = "Compound";
		m_partCatgory = "compound";
	}
	if (m_type == SPEC_BIOBRICK)
	{
		m_partCatgory = "biobrick";
	}
	initFromDb(m_type);
};

QString SpeciesData::speciesId()
{
	if (m_speciesId != "")
		return m_speciesId;

	m_speciesId = QString::number(InputGen::getSpecNo());
	InputGen::incSpecNo();
	return m_speciesId;
}
