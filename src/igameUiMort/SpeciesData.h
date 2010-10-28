#ifndef _SPECIES_H_
#define _SPECIES_H_

#include <QString>

typedef enum
{
	SPEC_COMPARTMENT,
	SPEC_BACKBONE,
	SPEC_BIOBRICK,
	SPEC_COMPOUNDS
} SPECIESTYPE;

class SpeciesData
{
	private:
		QString m_id;
		SPECIESTYPE m_type;
		QString m_compartment;
		SPECIESTYPE m_parentType;

	public:
		SpeciesData();
		SpeciesData(SPECIESTYPE type, QString id, SPECIESTYPE parentType, QString parent);
		SpeciesData(SpeciesData &other);
		SpeciesData& operator = (SpeciesData &other);

		SPECIESTYPE type() { return m_type; }
		QString id() { return m_id; }
		QString parent() { return m_compartment; }
		SPECIESTYPE parentType() { return m_parentType; }
};
#endif
