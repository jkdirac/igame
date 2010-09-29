#ifndef _LIBSBML_401_WRAPPER_H_
#define _LIBSBML_401_WRAPPER_H_

#include <sbml/SBMLTypes.h>

#ifdef __cplusplus
#  define CLASS_OR_STRUCT class
#else
#  define CLASS_OR_STRUCT struct
#endif  /* __cplusplus */

typedef CLASS_OR_STRUCT ParseMessage ParseMessage_t;
typedef CLASS_OR_STRUCT RateRule RateRule_t;
typedef CLASS_OR_STRUCT AssignmentRule AssignmentRule_t;
typedef CLASS_OR_STRUCT AlgebraicRule AlgebraicRule_t;
typedef CLASS_OR_STRUCT ModifierSpeciesReference  ModifierSpeciesReference_t;

//#define SBML_LEVEL 2
//#define SBML_VERSION 4

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Used by an SBMLReader to indicate the level of XML Schema validation.
 * Schema violations (for both BASIC and FULL) are reported in the
 * SBMLDocument's list of ParseMessages.  The levels are:
 *
 *   NONE (0) turns schema validation off.
 *
 *   BASIC (1) validates an XML instance document against an XML Schema.
 *   Those who wish to perform schema checking on SBML documents should use
 *   this option.
 *
 *   FULL (2) validates both the instance document itself *and* the XML
 *   Schema document.  The XML Schema document is checked for violation of
 *   particle unique attribution constraints and particle derivation
 *   restrictions, which is both time-consuming and memory intensive.
 */
typedef enum
{
    XML_SCHEMA_VALIDATION_NONE
  , XML_SCHEMA_VALIDATION_BASIC
  , XML_SCHEMA_VALIDATION_FULL
} XMLSchemaValidation_t;

Compartment_t * Compartment_createWith ( const char *sid, double size,
		const char *units, const char *outside );
Parameter_t *
Parameter_createWith (const char *sid, double value, const char *units);

Species_t *
Species_createWith( const char *sid,
                    const char *compartment,
                    double      initialAmount,
                    const char *substanceUnits,
                    int         boundaryCondition,
                    int         charge );

int RateRule_isSetVariable (const RateRule_t *rr);

RateRule_t * RateRule_create (void);

void RateRule_setVariable (RateRule_t *rr, const char *sid);
const char* RateRule_getVariable (const RateRule_t *rr);
const char * AssignmentRule_getVariable (const AssignmentRule_t *ar);
unsigned int SBMLDocument_getNumWarnings (const SBMLDocument_t *d);
unsigned int ParseMessage_getId (const ParseMessage_t *pm);
ParseMessage_t * SBMLDocument_getWarning (SBMLDocument_t *d, unsigned int n);
void SBMLReader_setSchemaFilenameL2v1 (SBMLReader_t *sr, const char *filename);
unsigned int ListOf_getNumItems (const ListOf_t *lo);
const char * ParseMessage_getMessage (const ParseMessage_t *pm);
void SBMLReader_setSchemaFilenameL1v2 (SBMLReader_t *sr, const char *filename);
void SBMLReader_setSchemaFilenameL1v1 (SBMLReader_t *sr, const char *filename);
unsigned int SBMLDocument_getNumFatals (const SBMLDocument_t *d);
ParseMessage_t * SBMLDocument_getFatal (SBMLDocument_t *d, unsigned int n);
void SBMLReader_setSchemaValidationLevel ( SBMLReader_t *sr, XMLSchemaValidation_t level );
AssignmentRule_t * AssignmentRule_create (void);
const char * ModifierSpeciesReference_getSpecies (const ModifierSpeciesReference_t *msr);

void SBMLDocument_setVersion (SBMLDocument_t *d, unsigned int version);
void SBMLDocument_setLevel (SBMLDocument_t *d, unsigned int level);
AlgebraicRule_t * AlgebraicRule_create (void);
int AssignmentRule_isSetVariable (const AssignmentRule_t *ar);
void AssignmentRule_setVariable (AssignmentRule_t *ar, const char *sid);
int RateRule_isSetVariable (const RateRule_t *rr);

char* SBMLDocument_tosbml (SBMLDocument_t *dd);
#ifdef __cplusplus
	}
#endif

#endif
