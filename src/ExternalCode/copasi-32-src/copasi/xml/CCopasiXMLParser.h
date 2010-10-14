// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/xml/CCopasiXMLParser.h,v $
//   $Revision: 1.70.2.2 $
//   $Name: Build-31 $
//   $Author: shoops $
//   $Date: 2010/05/31 18:43:06 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CCopasiXMLParser class.
 * This class is the parses a Copasi XML file.
 *
 * Created for Copasi by Stefan Hoops 2003
 * Copyright Stefan Hoops
 */

#ifndef COPASI_CCopasiXMLParser
#define COPASI_CCopasiXMLParser

#include <stack>
#include <map>
#include <string>
#include <sstream>

#include "xml/CExpat.h"
#include "xml/CXMLHandler.h"
#include "utilities/CCopasiVector.h"
#include "report/CKeyFactory.h"

class CCompartment;
class CMetab;
class CModel;
class CModelEntity;
class CModelValue;
class CEvent;
class CEventAssignment;
class CReaction;
class CEvaluationTree;
class CFunctionParameter;
class CCopasiXMLParser;
class CReportDefinitionVector;
class COutputDefinitionVector;
class CPlotSpecification;
class CPlotItem;
class CPlotDataChannelSpec;
class CCopasiParameter;
class CCopasiParameterGroup;
class CVersion;
class CSlider;
class SCopasiXMLGUI;
class CReportDefinition;
class CCopasiTask;
class CListOfLayouts;
class CLayout;
class CLCompartmentGlyph;
class CLMetabGlyph;
class CLReactionGlyph;
class CLTextGlyph;
class CLGraphicalObject;
class CLCurve;
class CLLineSegment;
class CLMetabReferenceGlyph;
class CCopasiDataModel;

class SCopasiXMLParserCommon
{
public:
  // Operations
  /**
   * Default Constructor
   */
  SCopasiXMLParserCommon();

  // Attributes
  /**
   * The version of the parsed file
   */
  CVersion * pVersion;

  /**
   * The model which is build during parsing.
   */
  CModel * pModel;

  /**
   * Storage for a comment.
   */
  std::string CharacterData;

  /**
   * Storage for assignments.
   */
  std::vector<std::pair<std::string, std::string> > mAssignments;

  /**
   * Pointer to a vector of functions which has been loaded or is to be saved.
   * The ownership is handed to the user.
   */
  CCopasiVectorN< CEvaluationTree > * pFunctionList;

  /**
   * Pointer to the currently processed function.
   */
  CEvaluationTree * pFunction;

  /**
   * Pointer to the currently processed function.
   */
  CFunctionParameter * pFunctionVariable;

  /**
   * The description of the function.
   */
  std::string FunctionDescription;

  /**
   * Indicates whether the current function was already in the list;
   */
  bool mExistingFunction;

  /**
   * Pointer to the currently processed reaction.
   */
  CReaction * pReaction;

  /**
   * Pointer to the currently processed event
   */
  CEvent * pEvent;

  /**
   * Pointer to the currently processed event assignment
   */
  CEventAssignment * pEventAssignment;

  /**
   * The keys of the source parameters for a call parameter.
   */
  std::map< std::string, std::vector< std::string > > SourceParameterKeys;

  /**
   * A map relating CopasiXML function keys with internal keys
   */
  //    std::map< std::string, std::string > KeyMap;
  CKeyFactory KeyMap;

  /**
   * A map relating StateVariables to model entities.
   */
  std::vector< CModelEntity * > StateVariableList;

  /**
   * Pointer to a vector of tasks which has been loaded or is to be saved.
   * The ownership is handed to the user.
   */
  CCopasiVectorN< CCopasiTask > * pTaskList;

  /**
   * Pointer to a vector of reports which has been loaded or is to be saved.
   * The ownership is handed to the user.
   */
  CReportDefinitionVector * pReportList;

  /**
   * Pointer to a vector of plots which has been loaded or is to be saved.
   * The ownership is handed to the user.
   */
  COutputDefinitionVector * pPlotList;

  /**
   * Pointer to the currently processed report
   */
  CReportDefinition * pReport;

  /**
   * Pointer to the currently processed task
   */
  CCopasiTask* pCurrentTask;

  /**
   * Pointer to the currently processed parameter
   */
  CCopasiParameter* pCurrentParameter;

  /**
   * Stack of parameter groups which is needed since nesting
   * of groups is possible.
   */
  std::stack< CCopasiParameterGroup * > ParameterGroupStack;
  //    CCopasiParameterGroup* pCurrentParameterGroup;

  /**
   * Pointer to the currently processed plot
   */
  CPlotSpecification* pCurrentPlot;

  /**
   * Pointer to the currently processed plot item.
   */
  CPlotItem* pCurrentPlotItem;

  /**
   * Pointer to the currently processed channel.
   */
  CPlotDataChannelSpec* pCurrentChannelSpec;

  /**
   * Vector of parameters of type key which could not be updated due to missing target objects
   * at time of read.
   */
  std::vector< std::string > UnmappedKeyParameters;

  /**
   * Pointer to a list of Layouts which has been loaded or is to be saved.
   * The ownership is handed to the user.
   */
  CListOfLayouts * pLayoutList;

  /**
   * Pointer to the currently processed layout
   */
  CLayout * pCurrentLayout;

  CLCompartmentGlyph * pCompartmentGlyph;
  CLMetabGlyph * pMetaboliteGlyph;
  CLReactionGlyph * pReactionGlyph;
  CLTextGlyph * pTextGlyph;
  CLGraphicalObject * pAdditionalGO;
  CLCurve *pCurve;
  CLLineSegment *pLineSegment;
  CLMetabReferenceGlyph* pMetaboliteReferenceGlyph;

  /**
   * Nesting level of the currently processed parameter group
   */
  int mParameterGroupLevel;

  /**
   * A map that stores a vector of tasks that reference a certain key
   * together with the key to the reference.
   */
  std::map<std::string , std::vector < CCopasiTask* > > taskReferenceMap;

  /**
   * A map that stores a vector of pairs of header,body or footer addresses
   *  with the index together with the key to the reference.
   */
  std::map<std::string , std::vector < std::pair < std::vector <CRegisteredObjectName >*, unsigned C_INT32 > > > reportReferenceMap;

  SCopasiXMLGUI * pGUI;

  /**
   * A pointer to the datamodel.
   */
  CCopasiDataModel* pDataModel;
};

class CCopasiXMLParser : public CExpat
{
  // Attributes
private:
  /**
   * Attributes accessible through the whole parser.
   */
  SCopasiXMLParserCommon mCommon;

  /**
   * The character data.
   */
  std::string mCharacterData;

  /**
   * The element handler stack
   */
  std::stack< CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon > * > mElementHandlerStack;

#ifdef  COPASI_TEMPLATE
  class TEMPLATEElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      TEMPLATE = 0,
      etc
    };

    // Operations
  public:
    /**
     * Constructor
     */
    TEMPLATEElement(CCopasiXMLParser & parser,
                    SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~TEMPLATEElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);

  private:
    /**
     * A pointer to the etcElement handler
     */
    etcElement * mpetcElement;
  };

#endif // COPASI_TEMPLATE

  class UnknownElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      Unknown = 0
    };

    /**
     * The line number the unknown element was encountered.
     */
    unsigned C_INT32 mLineNumber;

    // Operations
  public:
    /**
     * Constructor
     */
    UnknownElement(CCopasiXMLParser & parser,
                   SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~UnknownElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

public:
  /**
   * The unknown element handler
   */
  UnknownElement mUnknownElement;

private:

  class CharacterDataElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Text
     */
    enum Element
    {
      CharacterData = 0
    };

    // Operations
  public:
    /**
     * Constructor
     */
    CharacterDataElement(CCopasiXMLParser & parser,
                         SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~CharacterDataElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);

  private:
    std::string mCurrentElementName;
  };

public:
  /**
   * The character data element handler
   */
  CharacterDataElement mCharacterDataElement;

private:

  class InitialStateElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      InitialState = 0,
      etc
    };

    // Operations
  public:
    /**
     * Constructor
     */
    InitialStateElement(CCopasiXMLParser & parser,
                        SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~InitialStateElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class StateTemplateVariableElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      StateTemplateVariable = 0
    };

    // Operations
  public:
    /**
     * Constructor
     */
    StateTemplateVariableElement(CCopasiXMLParser & parser,
                                 SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~StateTemplateVariableElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class StateTemplateElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      StateTemplate = 0,
      StateTemplateVariable
    };

    // Operations
  public:
    /**
     * Constructor
     */
    StateTemplateElement(CCopasiXMLParser & parser,
                         SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~StateTemplateElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class SourceParameterElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      SourceParameter = 0
    };

    // Operations
  public:
    /**
     * Constructor
     */
    SourceParameterElement(CCopasiXMLParser & parser,
                           SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~SourceParameterElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class CallParameterElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      CallParameter = 0,
      SourceParameter
    };

    // Operations
  public:
    /**
     * Constructor
     */
    CallParameterElement(CCopasiXMLParser & parser,
                         SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~CallParameterElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class ListOfCallParametersElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      ListOfCallParameters = 0,
      CallParameter
    };

    // Operations
  public:
    /**
     * Constructor
     */
    ListOfCallParametersElement(CCopasiXMLParser & parser,
                                SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~ListOfCallParametersElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class KineticLawElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      KineticLaw = 0,
      ListOfCallParameters
    };

    // Operations
  public:
    /**
     * Constructor
     */
    KineticLawElement(CCopasiXMLParser & parser,
                      SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~KineticLawElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class ConstantElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      Constant = 0
    };

    // Operations
  public:
    /**
     * Constructor
     */
    ConstantElement(CCopasiXMLParser & parser,
                    SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~ConstantElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class ListOfConstantsElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      ListOfConstants = 0,
      Constant
    };

    // Operations
  public:
    /**
     * Constructor
     */
    ListOfConstantsElement(CCopasiXMLParser & parser,
                           SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~ListOfConstantsElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class ModifierElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      Modifier = 0
    };

    // Operations
  public:
    /**
     * Constructor
     */
    ModifierElement(CCopasiXMLParser & parser,
                    SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~ModifierElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class ListOfModifiersElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      ListOfModifiers = 0,
      Modifier
    };

    // Operations
  public:
    /**
     * Constructor
     */
    ListOfModifiersElement(CCopasiXMLParser & parser,
                           SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~ListOfModifiersElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class ProductElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      Product = 0
    };

    // Operations
  public:
    /**
     * Constructor
     */
    ProductElement(CCopasiXMLParser & parser,
                   SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~ProductElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class ListOfProductsElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      ListOfProducts = 0,
      Product
    };

    // Operations
  public:
    /**
     * Constructor
     */
    ListOfProductsElement(CCopasiXMLParser & parser,
                          SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~ListOfProductsElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class SubstrateElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      Substrate = 0
    };

    // Operations
  public:
    /**
     * Constructor
     */
    SubstrateElement(CCopasiXMLParser & parser,
                     SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~SubstrateElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class ListOfSubstratesElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      ListOfSubstrates = 0,
      Substrate
    };

    // Operations
  public:
    /**
     * Constructor
     */
    ListOfSubstratesElement(CCopasiXMLParser & parser,
                            SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~ListOfSubstratesElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class ReactionElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      Reaction = 0,
      MiriamAnnotation,
      ListOfSubstrates,
      ListOfProducts,
      ListOfModifiers,
      ListOfConstants,
      KineticLaw
    };

    /**
     * Pointer to ListOfSubstratesElement element handler.
     */
    ListOfSubstratesElement * mpListOfSubstratesElement;

    /**
     * Pointer to ListOfProductsElement element handler.
     */
    ListOfProductsElement * mpListOfProductsElement;

    /**
     * Pointer to ListOfModifiersElement element handler.
     */
    ListOfModifiersElement * mpListOfModifiersElement;

    /**
     * Pointer to ListOfConstantsElement element handler.
     */
    ListOfConstantsElement * mpListOfConstantsElement;

    /**
     * Pointer to ListOfConstantsElement element handler.
     */
    KineticLawElement * mpKineticLawElement;

    /**
     * The key in the CopasiML gile
     */
    std::string mKey;

    // Operations
  public:
    /**
     * Constructor
     */
    ReactionElement(CCopasiXMLParser & parser,
                    SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~ReactionElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class ListOfReactionsElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      ListOfReactions = 0,
      Reaction
    };

    // Operations
  public:
    /**
     * Constructor
     */
    ListOfReactionsElement(CCopasiXMLParser & parser,
                           SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~ListOfReactionsElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class MetaboliteElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      Metabolite = 0,
      MiriamAnnotation,
      Expression,
      InitialExpression
    };

    // Operations
  public:
    /**
     * Constructor
     */
    MetaboliteElement(CCopasiXMLParser & parser,
                      SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~MetaboliteElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);

  private:
    /**
     * A pointer to the current metabolite.
     */
    CMetab * mpMetabolite;

    /**
     * The key in the CopasiML file
     */
    std::string mKey;
  };

  class ListOfMetabolitesElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      ListOfMetabolites = 0,
      Metabolite
    };

    // Operations
  public:
    /**
     * Constructor
     */
    ListOfMetabolitesElement(CCopasiXMLParser & parser,
                             SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~ListOfMetabolitesElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class CompartmentElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      Compartment = 0,
      MiriamAnnotation,
      Expression,
      InitialExpression
    };

    // Operations
  public:
    /**
     * Constructor
     */
    CompartmentElement(CCopasiXMLParser & parser,
                       SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~CompartmentElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);

  private:
    /**
     * A pointer to the current compartment
     */
    CCompartment * mpCompartment;

    /**
     * The key in the CopasiML file
     */
    std::string mKey;
  };

  class ListOfCompartmentsElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      ListOfCompartments = 0,
      Compartment
    };

    // Operations
  public:
    /**
     * Constructor
     */
    ListOfCompartmentsElement(CCopasiXMLParser & parser,
                              SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~ListOfCompartmentsElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class MathMLElement;

  class ModelValueElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      ModelValue = 0,
      MiriamAnnotation,
      Expression,
      InitialExpression,
      MathML
    };

    CModelValue * mpMV;
    MathMLElement * mpMathMLElement;

    /**
     * The key in the CopasiML file
     */
    std::string mKey;

    // Operations
  public:
    /**
     * Constructor
     */
    ModelValueElement(CCopasiXMLParser & parser,
                      SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~ModelValueElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class ListOfModelValuesElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      ListOfModelValues = 0,
      ModelValue
    };

    // Operations
  public:
    /**
     * Constructor
     */
    ListOfModelValuesElement(CCopasiXMLParser & parser,
                             SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~ListOfModelValuesElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class EventElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      Event = 0,
      MiriamAnnotation,
      TriggerExpression,
      DelayExpression,
      ListOfAssignments
    };

    /**
     * The key in the CopasiML file
     */
    std::string mKey;

    // Operations
  public:
    /**
     * Constructor
     */
    EventElement(CCopasiXMLParser & parser,
                 SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~EventElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class ListOfEventsElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      ListOfEvents = 0,
      Event
    };

    /**
     * A set of event orders used to enforce uniqueness
     */
    std::set< unsigned C_INT32 > mEventOrders;

    // Operations
  public:
    /**
     * Constructor
     */
    ListOfEventsElement(CCopasiXMLParser & parser,
                        SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~ListOfEventsElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class AssignmentElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      Assignment = 0,
      Expression
    };

    /**
     * The key in the CopasiML file
     */
    std::string mKey;

    std::pair<std::string, std::string> mAssignmentPair;
    // Operations
  public:
    /**
     * Constructor
     */
    AssignmentElement(CCopasiXMLParser & parser,
                      SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~AssignmentElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class ListOfAssignmentsElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      ListOfAssignments = 0,
      Assignment
    };

    // Operations
  public:
    /**
     * Constructor
     */
    ListOfAssignmentsElement(CCopasiXMLParser & parser,
                             SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~ListOfAssignmentsElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);

    //        std::vector<std::pair<std::string, std::string> > mAssignments;
  };

  class CommentElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      Comment = 0,
      xhtml
    };

    /**
     * String stream to handle xhtml comments
     */
    std::ostringstream mXhtml;

    /**
     * The level of nested xhtml elements.
     */
    unsigned C_INT32 mLevel;

    /**
     * Information whether an element is empty
     */
    std::stack< bool > mElementEmpty;

    // Operations
  public:
    /**
     * Constructor
     */
    CommentElement(CCopasiXMLParser & parser,
                   SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~CommentElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

public:
  /**
   * The comment element handler
   */
  CommentElement mCommentElement;

private:

  class ModelElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      Model = 0,
      MiriamAnnotation,
      InitialExpression,
      Comment,
      ListOfCompartments,
      ListOfMetabolites,
      ListOfModelValues,
      ListOfReactions,
      ListOfEvents,
      StateTemplate,
      InitialState
    };

    /**
     * The key in the CopasiML file
     */
    std::string mKey;

    // Operations
  public:
    /**
     * Constructor
     */
    ModelElement(CCopasiXMLParser & parser,
                 SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~ModelElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class ChannelSpecElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     *
     */
    enum Element
    {
      ChannelSpec = 0
    };

    // Operations
  public:
    /**
     * Constructor
     */
    ChannelSpecElement(CCopasiXMLParser & parser,
                       SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~ChannelSpecElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class PlotItemElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     *
     */
    enum Element
    {
      PlotItem = 0,
      Parameter,
      ParameterGroup,
      ListOfChannels
    };

    /**
     * Pointer to the Parameter Element Handler
     */
    CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon > * mpParameterElement;

    /**
     * Pointer to the Parameter Group Element Handler
     */
    CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon > * mpParameterGroupElement;

    /**
     * Pointer to the List Of Channels Element Handler
     */
    CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon > * mpListOfChannelsElement;

    /**
     * The line number the unknown parameter was encountered.
     */
    unsigned C_INT32 mLineNumber;

    // Operations
  public:
    /**
     * Constructor
     */
    PlotItemElement(CCopasiXMLParser & parser,
                    SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~PlotItemElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class ListOfChannelsElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     *
     */
    enum Element
    {
      ListOfChannels = 0,
      ChannelSpec
    };

    // Operations
  public:
    /**
     * Constructor
     */
    ListOfChannelsElement(CCopasiXMLParser & parser,
                          SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~ListOfChannelsElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class ListOfPlotItemsElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     *
     */
    enum Element
    {
      ListOfPlotItems = 0,
      PlotItem
    };

    // Operations
  public:
    /**
     * Constructor
     */
    ListOfPlotItemsElement(CCopasiXMLParser & parser,
                           SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~ListOfPlotItemsElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class PlotSpecificationElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     *
     */
    enum Element
    {
      PlotSpecification = 0,
      Parameter,
      ParameterGroup,
      ListOfChannels,
      ListOfPlotItems
    };

    /**
     * The line number the unknown parameter was encountered.
     */
    unsigned C_INT32 mLineNumber;

    // Operations
  public:
    /**
     * Constructor
     */
    PlotSpecificationElement(CCopasiXMLParser & parser,
                             SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~PlotSpecificationElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class ListOfPlotsElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     *
     */
    enum Element
    {
      ListOfPlots = 0,
      PlotSpecification
    };

    // Operations
  public:
    /**
     * Constructor
     */
    ListOfPlotsElement(CCopasiXMLParser & parser,
                       SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~ListOfPlotsElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class ListOfTasksElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     *
     */
    enum Element
    {
      ListOfTasks = 0,
      Task
    };

    // Operations
  public:
    /**
     * Constructor
     */
    ListOfTasksElement(CCopasiXMLParser & parser,
                       SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~ListOfTasksElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class ReportInstanceElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      Report = 0
    };

    // Operations
  public:
    /**
     * Constructor
     */
    ReportInstanceElement(CCopasiXMLParser & parser,
                          SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~ReportInstanceElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class ParameterElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      Parameter = 0
    };

    // Operations
  public:
    /**
     * Constructor
     */
    ParameterElement(CCopasiXMLParser & parser,
                     SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~ParameterElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class ParameterTextElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      ParameterText = 0
    };

    // Operations
  public:
    /**
     * Constructor
     */
    ParameterTextElement(CCopasiXMLParser & parser,
                         SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~ParameterTextElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class ParameterGroupElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      ParameterGroup = 0,
      Content
    };

    ParameterElement* mpParameterHandler;
    ParameterTextElement* mpParameterTextHandler;
    ParameterGroupElement* mpParameterGroupHandler;

    bool mDerivedElement;

    // Operations
  public:
    /**
     * Constructor
     */
    ParameterGroupElement(CCopasiXMLParser & parser,
                          SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~ParameterGroupElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);

    /**
     * Set the derived element for which the handler is called such as methods and problems
     * @param CCopasiParameterGroup * pDerivedElement
     */
    void setDerivedElement(CCopasiParameterGroup * pDerivedElement);
  };

  class MethodElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      Method = 0,
      Content
    };

    ParameterGroupElement* mpContentHandler;

    /**
     * The line number the unknown parameter was encountered.
     */
    unsigned C_INT32 mLineNumber;

    // Operations
  public:
    /**
     * Constructor
     */
    MethodElement(CCopasiXMLParser & parser,
                  SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~MethodElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class TaskElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      Task = 0,
      Report,
      Problem,
      Method
    };

    ReportInstanceElement* mpReportElement;
    ParameterGroupElement* mpProblemElement;
    MethodElement* mpMethodElement;

    // Operations
  public:
    /**
     * Constructor
     */
    TaskElement(CCopasiXMLParser & parser,
                SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~TaskElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class ListOfReportsElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     *
     */
    enum Element
    {
      ListOfReports = 0,
      Report
    };

    // Operations
  public:
    /**
     * Constructor
     */
    ListOfReportsElement(CCopasiXMLParser & parser,
                         SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~ListOfReportsElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class ObjectElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Object
     */
    enum Element
    {
      Object = 0
    };

    // Operations
  public:
    /**
     * Constructor
     */
    ObjectElement(CCopasiXMLParser & parser,
                  SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~ObjectElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class ComplexElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Complex
     */
    enum Element
    {
      Complex = 0,
      Object,
      Text
      //Report
    };

    // Operations
  public:
    /**
     * Constructor
     */
    ComplexElement(CCopasiXMLParser & parser,
                   SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~ComplexElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class HeaderElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Header
     */
    enum Element
    {
      Header = 0,
      Object,
      Text,
      Report
    };

    // Operations
  public:
    /**
     * Constructor
     */
    HeaderElement(CCopasiXMLParser & parser,
                  SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~HeaderElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);

    // Attributes
  private:
    ObjectElement * mpObjectElement;
  };

  class BodyElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Body
     */
    enum Element
    {
      Body = 0,
      Object,
      Text,
      Report
    };

    // Operations
  public:
    /**
     * Constructor
     */
    BodyElement(CCopasiXMLParser & parser,
                SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~BodyElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);

    // Attributes
  private:
    ObjectElement * mpObjectElement;
  };

  class FooterElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     *  Footer
     */
    enum Element
    {
      Footer = 0,
      Object,
      Text,
      Report
    };

    // Operations
  public:
    /**
     * Constructor
     */
    FooterElement(CCopasiXMLParser & parser,
                  SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~FooterElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);

    // Attributes
  private:
    ObjectElement * mpObjectElement;
  };

  class TableElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      Table = 0,
      Object
    };

    // Operations
  public:
    /**
     * Constructor
     */
    TableElement(CCopasiXMLParser & parser,
                 SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~TableElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class ReportElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Report
     */
    enum Element
    {
      Report = 0,
      Comment,
      Header,
      Body,
      Footer,
      Table
    };

    HeaderElement * mpHeaderElement;
    BodyElement * mpBodyElement;
    FooterElement * mpFooterElement;
    TableElement* mpTableElement;

    bool tableFound;
    bool otherFound;

    // Operations
  public:
    /**
     * Constructor
     */
    ReportElement(CCopasiXMLParser & parser,
                  SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~ReportElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  /**
      *
      */
  class COPASIElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     *
     */
    enum Element
    {
      COPASI = 0,
      ListOfFunctions,
      Model,
      ListOfTasks,
      ListOfReports,
      ListOfPlots,
      GUI,
      ListOfLayouts,
      SBMLReference
    };

    // Operations
  public:
    /**
     * Constructor
     */
    COPASIElement(CCopasiXMLParser & parser,
                  SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~COPASIElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class ListOfFunctionsElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     *
     */
    enum Element
    {
      ListOfFunctions = 0,
      Function
    };

    // Operations
  public:
    /**
     * Constructor
     */
    ListOfFunctionsElement(CCopasiXMLParser & parser,
                           SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~ListOfFunctionsElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class MathMLElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Text
     */
    enum Element
    {
      MathML = 0,
      Text
    };

    // Operations
  public:
    /**
     * Constructor
     */
    MathMLElement(CCopasiXMLParser & parser,
                  SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~MathMLElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class ParameterDescriptionElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     *
     */
    enum Element
    {
      ParameterDescription = 0
    };

    /**
     * Order
     */
    unsigned C_INT32 mOrder;

    // Operations
  public:
    /**
     * Constructor
     */
    ParameterDescriptionElement(CCopasiXMLParser & parser,
                                SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~ParameterDescriptionElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);

    /**
     * Reset the element handler to start values.
     */
    virtual void reset();
  };

  class ListOfParameterDescriptionsElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     *
     */
    enum Element
    {
      ListOfParameterDescriptions = 0,
      ParameterDescription
    };

    // Operations
  public:
    /**
     * Constructor
     */
    ListOfParameterDescriptionsElement(CCopasiXMLParser & parser,
                                       SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~ListOfParameterDescriptionsElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class FunctionElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     *
     */
    enum Element
    {
      Function = 0,
      MiriamAnnotation,
      Expression,
      ListOfParameterDescriptions,
      MathML
    };

    /**
     *
     */
    MathMLElement * mpMathMLElement;

    /**
     *
     */
    ListOfParameterDescriptionsElement * mpListOfParameterDescriptionsElement;

    /**
     * The key in the CopasiML file
     */
    std::string mKey;

    // Operations
  public:
    /**
     * Constructor
     */
    FunctionElement(CCopasiXMLParser & parser,
                    SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~FunctionElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class MiriamAnnotationElement: public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      MiriamAnnotation = 0,
      RDF
    };

    /**
     * String stream to handle RDF contents
     */
    std::ostringstream mRDF;

    /**
     * The level of nested xhtml elements.
     */
    unsigned C_INT32 mLevel;

    /**
     * Information whether an element is empty
     */
    std::stack< bool > mElementEmpty;

    // Operations
  public:
    /**
     * Constructor
     */
    MiriamAnnotationElement(CCopasiXMLParser & parser,
                            SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~MiriamAnnotationElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

public:
  /**
   * The Miriam Annotation Element handler
   */
  MiriamAnnotationElement mMiriamAnnotationElement;

private:

  class GUIElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      GUI = 0,
      ListOfSliders
    };

    // Operations
  public:
    /**
     * Constructor
     */
    GUIElement(CCopasiXMLParser & parser,
               SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~GUIElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class ListOfSlidersElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      ListOfSliders = 0,
      Slider
    };

    // Operations
  public:
    /**
     * Constructor
     */
    ListOfSlidersElement(CCopasiXMLParser & parser,
                         SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~ListOfSlidersElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class SliderElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      Slider = 0
    };

    // Operations
  public:
    /**
     * Constructor
     */
    SliderElement(CCopasiXMLParser & parser,
                  SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~SliderElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class CurveElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
  private:
    enum Element
    {
      Curve = 0,
      ListOfCurveSegments,
      CurveSegment,
      Start,
      End,
      BasePoint1,
      BasePoint2
    };

    unsigned C_INT32 mLineNumber;

  public:
    CurveElement(CCopasiXMLParser & parser,
                 SCopasiXMLParserCommon & common);

    virtual ~CurveElement();

    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    virtual void end(const XML_Char *pszName);
  };

  class CompartmentGlyphElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
  private:
    enum Element
    {
      CompartmentGlyph = 0,
      BoundingBox,
      Position,
      Dimensions
    };

    unsigned C_INT32 mLineNumber;

  public:
    CompartmentGlyphElement(CCopasiXMLParser & parser,
                            SCopasiXMLParserCommon & common);

    virtual ~CompartmentGlyphElement();

    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    virtual void end(const XML_Char *pszName);
  };

  class ListOfCompartmentGlyphsElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
  private:
    enum Element
    {
      ListOfCompartmentGlyphs = 0,
      CompartmentGlyph
    };

  public:
    ListOfCompartmentGlyphsElement(CCopasiXMLParser & parser,
                                   SCopasiXMLParserCommon & common);

    virtual ~ListOfCompartmentGlyphsElement();

    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    virtual void end(const XML_Char *pszName);
  };

  class MetaboliteGlyphElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
  private:
    enum Element
    {
      MetaboliteGlyph = 0,
      BoundingBox,
      Position,
      Dimensions
    };

    unsigned C_INT32 mLineNumber;

  public:
    MetaboliteGlyphElement(CCopasiXMLParser & parser,
                           SCopasiXMLParserCommon & common);

    virtual ~MetaboliteGlyphElement();

    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    virtual void end(const XML_Char *pszName);
  };

  class ListOfMetabGlyphsElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
  private:
    enum Element
    {
      ListOfMetabGlyphs = 0,
      MetaboliteGlyph
    };

  public:
    ListOfMetabGlyphsElement(CCopasiXMLParser & parser,
                             SCopasiXMLParserCommon & common);

    virtual ~ListOfMetabGlyphsElement();

    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    virtual void end(const XML_Char *pszName);
  };

  class MetaboliteReferenceGlyphElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
  private:
    enum Element
    {
      MetaboliteReferenceGlyph = 0,
      BoundingBox,
      Position,
      Dimensions,
      Curve
    };

    unsigned C_INT32 mLineNumber;

  public:
    MetaboliteReferenceGlyphElement(CCopasiXMLParser & parser,
                                    SCopasiXMLParserCommon & common);

    virtual ~MetaboliteReferenceGlyphElement();

    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    virtual void end(const XML_Char *pszName);
  };

  class ListOfMetaboliteReferenceGlyphsElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
  private:
    enum Element
    {
      ListOfMetaboliteReferenceGlyphs = 0,
      MetaboliteReferenceGlyph
    };

  public:
    ListOfMetaboliteReferenceGlyphsElement(CCopasiXMLParser & parser,
                                           SCopasiXMLParserCommon & common);

    virtual ~ListOfMetaboliteReferenceGlyphsElement();

    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    virtual void end(const XML_Char *pszName);
  };

  class ReactionGlyphElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
  private:
    enum Element
    {
      ReactionGlyph = 0,
      BoundingBox,
      Position,
      Dimensions,
      Curve,
      ListOfMetaboliteReferenceGlyphs
    };

    unsigned C_INT32 mLineNumber;

  public:
    ReactionGlyphElement(CCopasiXMLParser & parser,
                         SCopasiXMLParserCommon & common);

    virtual ~ReactionGlyphElement();

    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    virtual void end(const XML_Char *pszName);
  };

  class ListOfReactionGlyphsElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
  private:
    enum Element
    {
      ListOfReactionGlyphs = 0,
      ReactionGlyph
    };

  public:
    ListOfReactionGlyphsElement(CCopasiXMLParser & parser,
                                SCopasiXMLParserCommon & common);

    virtual ~ListOfReactionGlyphsElement();

    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    virtual void end(const XML_Char *pszName);
  };

  class TextGlyphElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
  private:
    enum Element
    {
      TextGlyph = 0,
      BoundingBox,
      Position,
      Dimensions
    };

    unsigned C_INT32 mLineNumber;

  public:
    TextGlyphElement(CCopasiXMLParser & parser,
                     SCopasiXMLParserCommon & common);

    virtual ~TextGlyphElement();

    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    virtual void end(const XML_Char *pszName);
  };

  class ListOfTextGlyphsElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
  private:
    enum Element
    {
      ListOfTextGlyphs = 0,
      TextGlyph
    };

  public:
    ListOfTextGlyphsElement(CCopasiXMLParser & parser,
                            SCopasiXMLParserCommon & common);

    virtual ~ListOfTextGlyphsElement();

    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    virtual void end(const XML_Char *pszName);
  };

  class AdditionalGOElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
  private:
    enum Element
    {
      AdditionalGO = 0,
      BoundingBox,
      Position,
      Dimensions
    };

    unsigned C_INT32 mLineNumber;

  public:
    AdditionalGOElement(CCopasiXMLParser & parser,
                        SCopasiXMLParserCommon & common);

    virtual ~AdditionalGOElement();

    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    virtual void end(const XML_Char *pszName);
  };

  class ListOfAdditionalGOsElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
  private:
    enum Element
    {
      ListOfAdditionalGOs = 0,
      AdditionalGO
    };

  public:
    ListOfAdditionalGOsElement(CCopasiXMLParser & parser,
                               SCopasiXMLParserCommon & common);

    virtual ~ListOfAdditionalGOsElement();

    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    virtual void end(const XML_Char *pszName);
  };

  class LayoutElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
  private:
    enum Element
    {
      Layout = 0,
      Dimensions,
      ListOfCompartmentGlyphs,
      ListOfMetabGlyphs,
      ListOfReactionGlyphs,
      ListOfTextGlyphs,
      ListOfAdditionalGOs
    };

    unsigned C_INT32 mLineNumber;

  public:
    LayoutElement(CCopasiXMLParser & parser,
                  SCopasiXMLParserCommon & common);

    virtual ~LayoutElement();

    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    virtual void end(const XML_Char *pszName);
  };

  class ListOfLayoutsElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     *
     */
    enum Element
    {
      ListOfLayouts = 0,
      Layout
    };

    // Operations
  public:
    /**
     * Constructor
     */
    ListOfLayoutsElement(CCopasiXMLParser & parser,
                         SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~ListOfLayoutsElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class SBMLReferenceElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      SBMLReference = 0,
      SBMLMap
    };

    // Operations
  public:
    /**
     * Constructor
     */
    SBMLReferenceElement(CCopasiXMLParser & parser,
                         SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~SBMLReferenceElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };

  class SBMLMapElement:
      public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
  {
    // Attributes
  private:
    /**
     * Enum of invoked parsers
     */
    enum Element
    {
      SBMLMap = 0
    };

    // Operations
  public:
    /**
     * Constructor
     */
    SBMLMapElement(CCopasiXMLParser & parser,
                   SCopasiXMLParserCommon & common);

    /**
     * Destructor
     */
    virtual ~SBMLMapElement();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);
  };
  // Operations
private:
  /**
   * Constructor
   */
  CCopasiXMLParser();

public:
  /**
   * Public constructor
   * @param CVersion & version
   */
  CCopasiXMLParser(CVersion & version);

  /**
   * Destructor
   */
  ~CCopasiXMLParser();

  /**
   * Start element handler
   * @param const XML_Char *pszName
   * @param const XML_Char **papszAttrs
   */
  virtual void onStartElement(const XML_Char *pszName,
                              const XML_Char **papszAttrs);

  /**
   * End element handler
   * @param const XML_Char *pszName
   */
  virtual void onEndElement(const XML_Char *pszName);

  /**
   * Set the datamodel.
   * @param CCopasiDataModel* pDataModel
   */
  void setDatamodel(CCopasiDataModel* pDataModel);

  /**
   * Set the list of loaded functions
   * @param CCopasiVectorN< CEvaluationTree > * pFunctionList
   */
  void setFunctionList(CCopasiVectorN< CEvaluationTree > * pFunctionList);

#ifdef XXXX
  /**
   * Start CDATA section handler
   */
  virtual void onStartCdataSection();

  /**
   * End CDATA section handler
   */
  virtual void onEndCdataSection();
#endif // XXXX

  /**
   * Enable/Disable the character data handler
   * @param bool fEnable (Default: true)
   */
  void enableCharacterDataHandler(bool fEnable = true);

  /**
   * Character data handler
   * @param const XML_Char *pszData
   * @param int nLength
   */
  virtual void onCharacterData(const XML_Char *pszData,
                               int nLength);
  /**
   * Retrieve the data.
   * Any sequence of toBeStripped characters is replaced by a single
   * join character. The default is no stripping.
   * @param const std::string & toBeStripped (default: "")
   * @param const std::string & join (default: " ")
   * @return std::string data
   */
  std::string getCharacterData(const std::string & toBeStripped = "",
                               const std::string & join = " ");

  /**
   * Push the element handler on the stack.
   * @param CXMLHandler< CCopasiXMLParser > elementHandler
   */
  void pushElementHandler(CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon > * elementHandler);

  /**
   * Pop the element handler form the stack.
   */
  void popElementHandler();

  /**
   * Retrieve the loaded model functions
   * @return CModel * pModel
   */
  CModel * getModel() const;

  /**
   * Retrieve the list of loaded reports
   * @return CReportDefinitionVector * pReportList
   */
  CReportDefinitionVector * getReportList() const;

  /**
   * Retrieve the list of loaded functions
   * @return CCopasiVectorN< CTask > * pTaskList
   */
  CCopasiVectorN< CCopasiTask > * getTaskList() const;

  /**
   * Retrieve the list of loaded functions
   * @return COutputDefinitionVector * pPlotList
   */
  COutputDefinitionVector * getPlotList() const;

  /**
   * Set the GUI information to be saved
   * @param SCopasiXMLGUI * pGUI
   */
  void setGUI(SCopasiXMLGUI * pGUI);

  /**
   * Set the list of loaded layouts
   * @param CListOfLayouts * pLayoutList
   */
  void setLayoutList(CListOfLayouts * pLayoutList);

  /**
   * Retrieve the list of loaded layouts
   * @return CListOfLayouts * pLayoutList
   */
  CListOfLayouts * getLayoutList() const;

  /**
   * Retrieve a pointer to the current group if available
   * @return const CCopasiParameterGroup * currentGroup
   */
  const CCopasiParameterGroup * getCurrentGroup() const;

  /**
   * Retrieve an object by its CN within the context of the parser
   * @param const std::string & cn
   * @return const CCopasiObject * pObject
   */
  const CCopasiObject * getObjectFromName(const std::string & cn) const;
};

#endif // COPASI_CCopasiXMLParser
