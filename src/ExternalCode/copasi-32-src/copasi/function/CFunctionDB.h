// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/function/CFunctionDB.h,v $
//   $Revision: 1.54 $
//   $Name: Build-31 $
//   $Author: aekamal $
//   $Date: 2009/06/12 19:58:24 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CFunctionDB
 *
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2001
 */

#ifndef COPASI_CFunctionDB
#define COPASI_CFunctionDB

#include "function/CEvaluationTree.h"

#include "report/CCopasiContainer.h"
#include "report/CCopasiRootContainer.h"
#include "utilities/CReadConfig.h"
#include "utilities/CCopasiVector.h"

class CFunction;
class CModel;

/** @dia:pos 106.082,17.0878 */
class CFunctionDB : public CCopasiContainer
{
  // Attributes
private:
  /**
   *  Filename which contains the function database
   */
  std::string mFilename;

  /**
   *  Vector of the currently loaded functions
   */
  CCopasiVectorN < CEvaluationTree > mLoadedFunctions;

  // Operations

public:
  /**
   * Default constructor
   * @param const std::string & name (default: "NoName")
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  //CFunctionDB(const std::string & name = "FunctionDB",
  //            const CCopasiContainer * pParent = NULL);
  CFunctionDB(const std::string & name,
              const CCopasiContainer * pParent);

  /**
   * Destructor
   */
  ~CFunctionDB();

  /**
   *
   */
  void cleanup();

  void initObjects();

  bool load();

  /**
   *  Loads an object with data coming from a CReadConfig object.
   *  (CReadConfig object reads an input stream)
   *  @param pconfigbuffer reference to a CReadConfig object.
   *  @return mFail
   */
  C_INT32 load(CReadConfig & configbuffer);

  /**
   *
   */
  void setFilename(const std::string & filename);

  /**
   *
   */
  std::string getFilename() const;

#ifdef FFFF
  /**
   *  Load the function functionName from the database
   *  @param "const string" &functionName
   *  @return CEvaluationTree * function (NULL if function can not be loaded)
   */
  CEvaluationTree * dBLoad(const std::string & functionName);
#endif // FFFF

  /**
   * Add the function to the database
   * @param CEvaluationTree * pFunction
   * @param const bool & adopt (default = false)
   * @return bool success
   */
  bool add(CEvaluationTree * pFunction, const bool & adopt);

  /**
   * Add the function to the database, if necessary adapt the name so it
   * is unique.
   */
  void addAndAdaptName(CEvaluationTree * pFunction);

#ifdef FFFF
  /**
   *  Add the function to the database
   *  @param const std::string & name
   *  @param const CEvaluationTree::Type & type (Default: CEvaluationTree::Base)
   *  @return bool success
   */
  CEvaluationTree* createFunction(const std::string &name, const CEvaluationTree::Type & type = CEvaluationTree::Function);
#endif // FFFF

  bool removeFunction(unsigned C_INT32 index);

  bool removeFunction(const std::string &key);

  /**
   *  Delete the function functionName from the database
   *  @param "const string" &functionName
   *  @return C_INT32 Fail
   */
  //void dBDelete(const std::string & functionName);

  /**
   *  Search for a function among the loaded functions. If no
   *  function is found NULL is returned
   *  @param "const string" &functionName
   *  @return CEvaluationTree *
   */
  CEvaluationTree * findFunction(const std::string & functionName);

  /**
   *  Search for a function among the loaded functions. If no
   *  function is found the database is searched and the apropriate
   *  function is loaded.
   *  @param "const string" &functionName
   *  @return CEvaluationTree * function (NULL if function is not found)
   */
  CEvaluationTree * findLoadFunction(const std::string & functionName);

  /**
   *  Retrieves the vector of loaded functions.
   *  @return "CCopasiVectorNS < CKinFunction > &" loadedFunctions
   */
  CCopasiVectorN < CEvaluationTree > & loadedFunctions();

  /**
   *  Retrieves the vector of functions that are suitable for a
   *  number of substrates, products and reversibility status.
   *  Note: The returns CCopasiVector has to be deleted after use!
   *  @param "const unsigned C_INT32" noSubstrates the number of substrates
   *  @param "const unsigned C_INT32" noProducts the number of products
   *  @param "const TriLogic" reversible the reversibility status
   *  @return "std::vector<CFunction*> " suitableFunctions
   */
  std::vector<CFunction*>
  suitableFunctions(const unsigned C_INT32 noSubstrates,
                    const unsigned C_INT32 noProducts,
                    const TriLogic reversibility);

  /**
   * Appends pointers to function, which are dependent on any of the candidates
   * to the list dependentFunctions.
   * @param std::set< const CCopasiObject * > candidates
   * @param std::set< const CCopasiObject * > & dependentFunctions
   * @return bool functionsAppended
   */
  bool appendDependentFunctions(std::set< const CCopasiObject * > candidates,
                                std::set< const CCopasiObject * > & dependentFunctions) const;

  /**
   * Retrieve a list of evaluation trees depending on the tree with the
   * given name.
   * @param const std::string & name
   * @return std::set<std::string> list
   */
  std::set<std::string> listDependentTrees(const std::string & name) const;

  /**
   * Retrieves a list of all functions used in the model
   * @return std::vector< CEvaluationTree * > usedFunctions
   */
  std::vector< CEvaluationTree * > getUsedFunctions(const CModel* pModel) const;
};

#endif // COPASI_CFunctionDB
