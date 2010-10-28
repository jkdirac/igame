#include "SpeciesData.h"

SpeciesData::SpeciesData()
{
}

SpeciesData::SpeciesData(SPECIESTYPE type, QString id, SPECIESTYPE parentType, QString parent)
{
	m_type = type;
	m_id = id;
	m_compartment = parent;
	m_parentType = parentType;
}

SpeciesData::SpeciesData(SpeciesData &other)
{
	m_type = other.type();
	m_id = other.id();
	m_compartment = other.parent();
	m_parentType = other.parentType();
}

SpeciesData& SpeciesData::operator = (SpeciesData &other)
{
	m_type = other.type();
	m_id = other.id();
	m_compartment = other.parent();
	m_parentType = other.parentType();

	return *this;
}
