// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/steadystate/CSteadyStateMethod.h,v $
//   $Revision: 1.21 $
//   $Name: Build-31 $
//   $Author: shoops $
//   $Date: 2007/12/05 15:13:21 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CSteadyStateMethod class.
 *  This class describes the interface to all steady state methods.
 *  The variaous method like Netwon have to be derived from
 *  this class.
 *
 *  Created for Copasi by Stefan Hoops 2002
 */

#ifndef COPASI_CSteadyStateMethod
#define COPASI_CSteadyStateMethod

#include <string>
#include <sstream>

#include "utilities/CCopasiMethod.h"
#include "utilities/CMatrix.h"

class CSteadyStateProblem;
class CSteadyStateTask;
class CState;
class CEigen;
class CProcessReport;
class CModel;

class CSteadyStateMethod : public CCopasiMethod
  {
  public:
    enum ReturnCode
    {
      notFound = 0,
      found,
      foundEquilibrium,
      foundNegative
    };

  protected:
    /**
     *  A pointer to the  problem.
     */
    const CSteadyStateProblem * mpProblem;

    /**
     *  A pointer to the model.
     */
    CModel * mpModel;

    /**
     *  A pointer to the task.
     */
    CSteadyStateTask * mpParentTask;

    /**
     * A pointer to the steady state
     */
    CState * mpSteadyState;

    /**
     * The jacobian of the steadystate
     */
    CMatrix< C_FLOAT64 > * mpJacobianX;

    /**
     * A pointer to the progress bar handler
     */
    CProcessReport * mpProgressHandler;

    /**
     * The concentration rate that is considered zero
     */
    C_FLOAT64* mpSSResolution;

    /**
     * The factor for numerical derivation
     */
    C_FLOAT64* mpDerivationFactor;

    /**
     * The resolution of the variable of numerical derivation
     */
    C_FLOAT64* mpDerivationResolution;

    std::ostringstream mMethodLog;

    // Operations
  private:
    /**
     * Default constructor.
     */
    CSteadyStateMethod();

  protected:
    /**
     * Specific constructor.
     * @param CCopasiMethod::SubType subType
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CSteadyStateMethod(CCopasiMethod::SubType subType,
                       const CCopasiContainer * pParent = NULL);

    /**
     * initialize parameters and handle parameters of old copasi files
     */
    void initializeParameter();

  public:
    /**
     * Create a trajectory method.
     * Note: the returned object has to be released after use with delete
     */
    static CSteadyStateMethod *
    createSteadyStateMethod(CCopasiMethod::SubType subType
                            = CCopasiMethod::Newton);

    /**
     * Copy constructor.
     * @param "const CSteadyStateMethod &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CSteadyStateMethod(const CSteadyStateMethod & src,
                       const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    ~CSteadyStateMethod();

    bool elevateChildren();

    /**
     * This instructs the method to calculate a the steady state
     * starting with the initialState given.
     * The steady state is returned in the object pointed to by steadyState.
     * @param CState * steadyState
     * @param CMatrix< C_FLOAT64 > & jacobianX
     * @param CProcessReport * handler
     * @return CSteadyStateMethod::ReturnCode returnCode
     */
    CSteadyStateMethod::ReturnCode process(CState * pState,
                                           CMatrix< C_FLOAT64 > & jacobianX,
                                           CProcessReport * handler);

    /**
     * Check if the method is suitable for this problem
     * @return bool suitability of the method
     */
    virtual bool isValidProblem(const CCopasiProblem * pProblem);

    /**
     * Initialize the method must be called before process
     * @param const CSteadyStateProblem * pProblem
     * @return bool success
     */
    virtual bool initialize(const CSteadyStateProblem * pProblem);

    /**
     * calls the CModel methods to calculate the jacobians (at the steady state).
     * This trivial method is implemented in the method
     * because it may need to know about some method parameters
     */
    void doJacobian(CMatrix< C_FLOAT64 > & jacobian,
                    CMatrix< C_FLOAT64 > & jacobianX);

    /**
     * returns the resolution for stability analysis
     */
    C_FLOAT64 getStabilityResolution();

    std::string getMethodLog() const;

  protected:

    /**
     * This instructs the method to calculate a the steady state
     * starting with the initialState given.
     * The steady state is returned in the object pointed to by steadyState.
     * @return CSteadyStateMethod::ReturnCode returnCode
     */
    virtual CSteadyStateMethod::ReturnCode
    processInternal();

    /**
     * This function has to be called at the return of any implementation
     * of the protected function process()
     * @return CSteadyStateMethod::ReturnCode returnCode
     */
    virtual CSteadyStateMethod::ReturnCode
    returnProcess(bool steadyStateFound);

    /**
     * Check whether the steady state is chemical equilibrium
     * @param const C_FLOAT64 & resolution
     * @retrun bool isEquilibrium
     */
    bool isEquilibrium(const C_FLOAT64 & resolution) const;

  protected:
    /**
     * Check whether all values make physically sence, i.e.,
     * volumes and particle number are positive
     * @return bool allPositive
     */
    bool allPositive();

    void calculateJacobianX(const C_FLOAT64 & oldMaxRate);
  };

#include "CNewtonMethod.h"

#endif // COPASI_CSteadyStateMethod
