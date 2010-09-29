#include "libsbml-401-wrapper.h"

int sbml_level = 2;
int sbml_version = 4;
Compartment_t * Compartment_createWith ( const char *sid, double size,
		const char *units, const char *outside )
{
	Compartment* c = new(std::nothrow) Compartment(sbml_level, sbml_version);

	if (c != 0)
	{
		c->setId     ( sid     ? sid     : "" );
		c->setUnits  ( units   ? units   : "" );
		c->setOutside( outside ? outside : "" );
		c->setSize(size);
	}

	return c;
}

/**
 * Creates a new Parameter with the given id, value and units and returns a
 * pointer to it.  This convenience function is functionally equivalent to:
 *
 *   Parameter_t *p = Parameter_create();
 *   Parameter_setName(p, id); Parameter_setValue(p, value); ... ;
 */
Parameter_t *
Parameter_createWith (const char *sid, double value, const char *units)
{
	Parameter_t *pPara = new(std::nothrow) Parameter(sbml_level, sbml_version);
	pPara->setId(sid ? sid : ""); 
	pPara->setValue(value); 
	pPara->setUnits(units ? units : "");
	return pPara;
}

Species_t *
Species_createWith( const char *sid,
                    const char *compartment,
                    double      initialAmount,
                    const char *substanceUnits,
                    int         boundaryCondition,
                    int         charge )
{
	Species* s = new(std::nothrow) Species(sbml_level, sbml_version);

	if (s != 0)
	{
		s->setId                ( sid            ? sid            : "" );
		s->setCompartment       ( compartment    ? compartment    : "" );
		s->setSubstanceUnits    ( substanceUnits ? substanceUnits : "" );
		s->setInitialAmount     ( initialAmount );
		s->setBoundaryCondition ( (bool) boundaryCondition  );
		s->setCharge            ( charge );
	}

	return s;
	return NULL;
}

/**
 * Creates a new RateRule and returns a pointer to it.
 */
RateRule_t * RateRule_create (void)
{
	return new(std::nothrow) RateRule(sbml_level, sbml_version);
}

/**
 * Sets the variable of this RateRule to a copy of sid.
 */
void
RateRule_setVariable (RateRule_t *rr, const char *sid)
{
	static_cast<RateRule*>(rr)->setVariable(sid ? sid : "");
}

/**
 * @return the variable for this RateRule.
 */
const char *
RateRule_getVariable (const RateRule_t *rr)
{
	const RateRule* x = static_cast<const RateRule*>(rr);
	return x->isSetVariable() ? x->getVariable().c_str() : NULL;
}

/**
 * @return the variable for this AssignmentRule.
 */
const char *
AssignmentRule_getVariable (const AssignmentRule_t *ar)
{
	const AssignmentRule* x = static_cast<const AssignmentRule*>(ar);
	return x->isSetVariable() ? x->getVariable().c_str() : NULL;
}

/**
 * @return the number of warnings encountered during the parse of this
 * SBMLDocument.
 */
unsigned int SBMLDocument_getNumWarnings (const SBMLDocument_t *d)
{
	return static_cast<const SBMLDocument*>(d)->getNumErrors();
}

/**
 * @return the id of this ParseMessage.
 */
unsigned int ParseMessage_getId (const ParseMessage_t *pm)
{
	return 0;
}

/**
 * @return the nth warning encountered during the parse of this
 * SBMLDocument or NULL if n > getNumWarnings() - 1.
 */
ParseMessage_t * SBMLDocument_getWarning (SBMLDocument_t *d, unsigned int n)
{
//        return static_cast<SBMLDocument*>(d)->getError(n);
	return NULL;
}

/**
 * Sets the schema filename used by this SBMLReader to validate SBML Level
 * 2 version 1 documents.
 *
 * The filename should be either i) an absolute path or ii) relative to the
 * directory contain the SBML file(s) to be read.
 */
LIBSBML_EXTERN
void
SBMLReader_setSchemaFilenameL2v1 (SBMLReader_t *sr, const char *filename)
{
}

/**
 * @return the number of items in this List.
 */
unsigned int ListOf_getNumItems (const ListOf_t *lo)
{
  return static_cast<const ListOf*>(lo)->size();
}

/**
 * @return the message text of this ParseMessage.
 */
const char * ParseMessage_getMessage (const ParseMessage_t *pm)
{
	return NULL;
}

/**
 * Sets the schema filename used by this SBMLReader to validate SBML Level
 * 1 version 2 documents.
 *
 * The filename should be either i) an absolute path or ii) relative to the
 * directory contain the SBML file(s) to be read.
 */
void SBMLReader_setSchemaFilenameL1v2 (SBMLReader_t *sr, const char *filename)
{
}

/**
 * Sets the schema filename used by this SBMLReader to validate SBML Level
 * 1 version 1 documents.
 *
 * The filename should be either i) an absolute path or ii) relative to the
 * directory contain the SBML file(s) to be read.
 */
LIBSBML_EXTERN
void
SBMLReader_setSchemaFilenameL1v1 (SBMLReader_t *sr, const char *filename)
{
}

/**
 * @return the number of fatal errors encountered during the parse of this
 * SBMLDocument.
 */
LIBSBML_EXTERN
unsigned int
SBMLDocument_getNumFatals (const SBMLDocument_t *d)
{
  return static_cast<const SBMLDocument*>(d)->getNumErrors();
}

/**
 * @return the nth fatal error encountered during the parse of this
 * SBMLDocument or NULL if n > getNumFatals() - 1.
 */
LIBSBML_EXTERN
ParseMessage_t *
SBMLDocument_getFatal (SBMLDocument_t *d, unsigned int n)
{
  return NULL;
}


/**
 * Sets the version of this SBMLDocument to the given version number.
 * Valid versions are currently 1 and 2 for SBML L1 and 1 for SBML L2.
 */
LIBSBML_EXTERN
void
SBMLDocument_setVersion (SBMLDocument_t *d, unsigned int version)
{
	return;
}

/**
 * Sets the schema validation level used by this SBMLReader.
 *
 * The levels are:
 *
 *   XML_SCHEMA_VALIDATION_NONE (0) turns schema validation off.
 *
 *   XML_SCHEMA_VALIDATION_BASIC (1) validates an XML instance document
 *   against an XML Schema.  Those who wish to perform schema checking on
 *   SBML documents should use this option.
 *
 *   XML_SCHEMA_VALIDATION_FULL (2) validates both the instance document
 *   itself *and* the XML Schema document.  The XML Schema document is
 *   checked for violation of particle unique attribution constraints and
 *   particle derivation restrictions, which is both time-consuming and
 *   memory intensive.
 */
void SBMLReader_setSchemaValidationLevel ( SBMLReader_t *sr,
                                      XMLSchemaValidation_t level )
{
}

/**
 * Creates a new AssignmentRule and returns a pointer to it.
 *
 * In L1 AssignmentRule is an abstract class.  It exists soley to provide
 * fields to its subclasess: CompartmentVolumeRule, ParameterRule and
 * SpeciesConcentrationRule.
 *
 * In L2 the three subclasses are gone and AssigmentRule is concrete;
 * i.e. it may be created, used and destroyed directly.
 */
AssignmentRule_t * AssignmentRule_create (void)
{
	return new(std::nothrow) AssignmentRule(sbml_level, sbml_version);
}

/**
 * @return the species for this ModifierSpeciesReference.
 */
const char * ModifierSpeciesReference_getSpecies (const ModifierSpeciesReference_t *msr)
{
	const ModifierSpeciesReference* x =
		static_cast<const ModifierSpeciesReference*>(msr);

	return x->isSetSpecies() ? x->getSpecies().c_str() : NULL;
}

/**
 * Sets the level of this SBMLDocument to the given level number.  Valid
 * levels are currently 1 and 2.
 */
LIBSBML_EXTERN
void
SBMLDocument_setLevel (SBMLDocument_t *d, unsigned int level)
{
	return;
}

/**
 * Creates a new AlgebraicRule and returns a pointer to it.
 */
LIBSBML_EXTERN
AlgebraicRule_t *
AlgebraicRule_create (void)
{
	return new(std::nothrow) AlgebraicRule(sbml_level, sbml_version);
}

/**
 * @return 1 if the variable of this AssignmentRule has been set, 0
 * otherwise.
 */
int AssignmentRule_isSetVariable (const AssignmentRule_t *ar)
{
	return (int) static_cast<const AssignmentRule*>(ar)->isSetVariable();
}

/**
 * Sets the variable of this AssignmentRule to a copy of sid.
 */
LIBSBML_EXTERN
void
AssignmentRule_setVariable (AssignmentRule_t *ar, const char *sid)
{
	static_cast<AssignmentRule*>(ar)->setVariable(sid ? sid : "");
}

/**
 * @return 1 if the variable of this RateRule has been set, 0 otherwise.
 */
int RateRule_isSetVariable (const RateRule_t *rr)
{
	return (int) static_cast<const RateRule*>(rr)->isSetVariable();
}

char* SBMLDocument_tosbml (SBMLDocument_t *dd)
{
	return (char*) static_cast<SBMLDocument*>(dd)->toSBML();
}
