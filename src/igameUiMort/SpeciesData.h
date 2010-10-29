#ifndef _SPECIES_H_
#define _SPECIES_H_

#include <QString>

class MItem;

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

		MItem* m_item;

	public:
		SpeciesData();
		SpeciesData(SPECIESTYPE type, const QString& id, SPECIESTYPE parentType=SPEC_COMPARTMENT, const QString& parent="ROOT");
		SpeciesData(const SpeciesData &other);
		SpeciesData& operator = (const SpeciesData &other);

		SPECIESTYPE type() const { return m_type; }
		void setType(SPECIESTYPE type) { m_type = type; };

		const QString& id() const { return m_id; }
		const QString& parent() const { return m_compartment; } 
		SPECIESTYPE parentType() const { return m_parentType; }

		void setParent(const QString& id, SPECIESTYPE type) 
		{ m_compartment = id; m_parentType = type; };

		QString generatePartsXmlString();
		QString generateCompartmentXmlString();
		QString generateSpeciesXmlString();

		void setId(QString id) { m_id = id; };
};
#endif
