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
	friend class SpeciesDataManager;
	private:
		MItem* m_item;

		QString m_dbId;
		QString m_inputId;
		SPECIESTYPE m_type;
		QString m_parent;
		SPECIESTYPE m_parentType;

		//compartment
		QString m_compartSize; // 0.10
		QString m_InitConcentration; //"4.15135E-24"
		QString m_constant; // true
		//part
		QString m_partType; // "ForwardDNA"

		void init();

		SpeciesData();
		SpeciesData(SPECIESTYPE type, const QString& id, SPECIESTYPE parentType=SPEC_COMPARTMENT, const QString& parent="ROOT");
		SpeciesData(const SpeciesData &other);
		SpeciesData& operator = (const SpeciesData &other);

	public:

		const MItem* item() { return m_item; }
		const SPECIESTYPE type() const { return m_type; }
		const SPECIESTYPE parentType() const { return m_parentType; }
		const QString& id() const { return m_dbId; }
		const QString& parent() const { return m_parent; } 
		const QString& size() const { return m_compartSize; }
		const QString& initConcentration() const { return m_InitConcentration; }
		const QString& partType() const { return m_partType; }
		const QString inputId() const { return m_dbId + m_inputId; }
		const QString& constant() const { return m_constant; }

		inline void setItem(MItem *item) { m_item = item; }
		inline void setParentType(SPECIESTYPE type) { m_parentType = type; }
		inline void setId(const QString id) { m_dbId = id; };
		inline void setParent(const QString& id, SPECIESTYPE type) { m_parent = id; m_parentType = type; };
		inline void setSize(const QString& size) { m_compartSize = size; }
		inline void setConstant(const QString& constant) { m_constant = constant; }
		inline void setInitConcentration(QString& con) { m_InitConcentration = con; }
		inline void setPartType(QString &type) { m_partType = type; }
		inline void setInputId(QString input) { m_inputId = input; }
		void setType(SPECIESTYPE type);

		void setInputNo(int nm);

		QString generatePartsXmlString();
		QString generateCompartmentXmlString();
		QString generateSpeciesXmlString();

};
#endif
