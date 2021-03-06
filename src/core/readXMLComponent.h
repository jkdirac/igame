/*************************************************************************************
 *
 *            Author: liaochen- liaochen@mail.ustc.edu.cn
 *
 *            Last modified: 2010-09-24 00:15
 *
 *            Filename: readXMLComponent.h
 *
 *            Description: .
 *
 ************************************************************************************/
#ifndef READ_XML_COMPONENT_H
#define READ_XML_COMPONENT_H

#include "bdbInterface.h"
#include "g_i.h"

class readXMLComponent :
	public bdbXMLInterface

{ 
	public:

		readXMLComponent ();
		~readXMLComponent ();

	protected:

		set<string> partCtg_set;
		set<string> partType_set;
		set<string> speciesType_set;
		set<string> substituentType_set;

	public:

		void readPart (
				const container_index& cind,
				const string& doc,
				const string& qpath,
				const int& i,
				string& __ref, 
				string& __label,
				string& __type,
				string& __ctg 
				);

		void readNode (
				const container_index& cind,
				const string& doc,
				const string& qpath,
				const int& i,
				string& nCL, 
				string& nPL 
				);

		void readSpecies (
				const container_index& cind,
				const string& doc,
				const string& qpath,
				const int& i,
				string& speciesReference,
				string& speciesLabel,
				string& compartmentLabel,
				string& ccid
				);

		void readCompartment (
				const container_index& cind,
				const string& doc,
				const string& qpath,
				const int& i,
				string& compartmentReference,
				string& currentCompartmentLabel,
				string& parentCompartmentLabel
				);

		void readTransfer (
				const container_index& cind,
				const string& doc,
				const string& qpath,
				const int& i,
				pair<string,string>& from,
				pair<string,string>& to
				);

		void readParameter (
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
				);

		void readCompartment (
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
				);

		void readSpecies (
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
				);

		void readRule (
				const container_index& cind, 
				const string& doc,
				const string& qpath,
				const int& i,
				string& variable,
				string& math,
				const bool& text
				);

		void readSpeciesLink (
				const container_index& cind, 
				const string& doc,
				const string& qpath,
				const int& i,
				string& speciesReference,
				string& partType
				);

		void readReactionLink (
				const container_index& cind, 
				const string& doc,
				const string& qpath,
				const int& i,
				string& reactionReference,
				string& speciesRole 
				); 

		void readUnit (
				const container_index& cind,
				const string& doc,
				const string& qpath,
				const int& i,
				string& kind,
				double& exponent,
				int& scale,
				double& multiplier
				);

		void readFunctionDef (
				const container_index& cind,
				const string& doc,
				const string& qpath,
				const int& i,
				string& id,
				string& name,
				string& math
				);

		void readExternalRef (
				const container_index& cind,
				const string& doc,
				const string& qpath,
				const int& i,
				string& id,
				string& speciesLabel,
				string& partLabel,
				string& parameterLabel
				);

		void readConditionalParameter (
				const container_index& cind,
				const string& dir,
				const string& doc,
				const string& para,
				const string& comp,
				double& value,
				string& units,
				string& name
				);

		void readConstraint (
				const container_index& cind,
				const string& doc,
				const string& qpath,
				const int& i,
				vector<string>& vars,
				string& formula
				);
};
#endif 


