/*************************************************************************************
 *
 *            Author: liaochen- liaochen@mail.ustc.edu.cn
 *
 *            Last modified:	2010-09-26 10:24
 *
 *            Filename:		readDataBase.h
 *
 *            Description: class to read database: Predef (include input file),
 *						  Compartment, Parts, Species, Reactions.
 *
 ************************************************************************************/
#ifndef READ_DB_H
#define READ_DB_H

#include "readXMLComponent.h"
#include "reactionTemplate.h"
#include "myspecies.h"
#include "mycompartment.h"

class readDataBase:
	public readXMLComponent
{
	private:

		//	type conversion between string to UnitKind_t
		map <string, UnitKind_t> unitMap;

	protected:

		UnitKind_t getUnitKind_t (const string&) const;

	public:

		readDataBase () {}
		~readDataBase () {}

		/**
		 * read cnModel of Species 
		 */
		void read_cnModel (
				MySpecies* s,
				const container_index& cind,
				const string& doc,
				const string& qp,
				const bool& isTemplate
				);

		/**
		 * read reaction template
		 */
		void readReactionTemplate (
				reactionTemplate* RT,
				const string& doc,
				const bool& redir
				);

	protected:

		void setParameter (
				Parameter* para,
				const string& id,
				const string& name,
				const double& value,
				const string& units,
				const bool& constant
				) const;

		void setAlgebraicRule (
				AlgebraicRule* alger,
				const string& variable,
				const string& math
				) const;

		void setAssignmentRule (
				AssignmentRule* assr,
				const string& variable,
				const string& math
				) const ;

		void setRateRule (
				RateRule* rater,
				const string& variable,
				const string& math
				) const;

		void setCompartment (
				MyCompartment* comp,
				const string& db,
				const string& id,
				const string& name,
				const int& spatialDimensions,
				const double& size,
				const string& units,
				const string& outside,
				const bool& constant
				) const;

		void setSpecies (
				MySpecies* s,
				const string& db,
				const string& ccid,
				const string& id,
				const string& name,
				const string& compartment,
				const double& initialAmount,
				const double& initialConcentration,
				const string& substanceUnits,
				const bool& hasOnlySubstanceUnits,
				const bool& boundaryCondition,
				const int& charge,
				const bool& constant
				) const;

		void setUnit (
				UnitDefinition* unitdef,
				const string& id,
				const string& name
				) const;

		void setUnit (
				Unit* unit,
				const UnitKind_t& kind, 
				const double& exponent,
				const int& scale, 
				const double& multiplier
				) const;

		void setFunction (
				FunctionDefinition* fdef,
				const string& id,
				const string& name,
				const string& math
				) const;
};

#endif
