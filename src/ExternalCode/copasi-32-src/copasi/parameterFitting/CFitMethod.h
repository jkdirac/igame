/* Begin CVS Header
   $Source: /fs/turing/cvs/copasi_dev/copasi/parameterFitting/CFitMethod.h,v $
   $Revision: 1.2 $
   $Name: Build-31 $
   $Author: shoops $
   $Date: 2006/04/27 01:30:29 $
   End CVS Header */

// Copyright � 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CFitMethod
#define COPASI_CFitMethod

#include <string>

#include "optimization/COptMethod.h"

class CFitProblem;
class CFitTask;

/**
 * The CFitMehod class contains optimization methods which can utilize
 * special properties of the objective function for fitting.
 */
class CFitMethod : public COptMethod
  {
  public:
    static const std::string TypeName[];

    // Operations
  private:
    /**
     * Default constructor.
     */
    CFitMethod();

  protected:
    /**
     *
     * @param CCopasiMethod::SubType subType
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CFitMethod(CCopasiMethod::SubType subType,
               const CCopasiContainer * pParent = NULL);

  public:
    /**
     * Create a fitting method.
     * Note: the returned object has to be released after use with delete
     */
    static COptMethod * createMethod(CCopasiMethod::SubType subType = CCopasiMethod::EvolutionaryProgram);

    /**
     * Copy constructor
     * @param const CFitMethod & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CFitMethod(const CFitMethod & src,
               const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~CFitMethod();

    /**
     * Initialize arrays and pointer.
     * @return bool success
     */
    virtual bool initialize();

    /**
     * Check if the method is suitable for this problem
     * @return bool suitability of the method
     */
    virtual bool isValidProblem(const CCopasiProblem * pProblem);

    // Attributes
  protected:
    CFitProblem * mpFitProblem;

    CFitTask * mpFitTask;
  };

// Include implemented methods below

#endif  // COPASI_CFitMethod
