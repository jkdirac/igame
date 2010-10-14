// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/steadystate/CMCATask.h,v $
//   $Revision: 1.11 $
//   $Name: Build-31 $
//   $Author: gauges $
//   $Date: 2009/02/18 20:55:34 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CMCATask class.
 *
 * This class implements a metabolic control analysis task which is comprised of a
 * of a problem and a method. Additionally calls to the reporting
 * methods are done when initialized.
 *
 * Created for Copasi by Ralph Gauges 2004
 */

#ifndef COPASI_CMCATask_H__
#define COPASI_CMCATask_H__

#include <iostream>

#include "utilities/CCopasiTask.h"
#include "utilities/CMatrix.h"
#include "utilities/CReadConfig.h"
#include "steadystate/CSteadyStateMethod.h"

class CMCAProblem;
class CState;

class CMCATask : public CCopasiTask
  {
    //Attributes
  private:
    /**
     * A pointer to the found elasticities
     */

    /**
     * A pointer to the found flux control coefficients.
     */

    /**
     * A pointer to the found concentration control coefficients.
     */

    //Operations
  public:

    /**
     * Default constructor
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CMCATask(const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param const CMCATask & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CMCATask(const CMCATask & src,
             const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~CMCATask();

    /**
     * Resizes result matrices and updates array annotations for a specific task.
     * This is used when we need to know about the data structures of a task result
     * without actually performing the task, e.g. when selecting objects for output.
     * For now we assume that this functionality is also performed when
     * initialize() is called.
     */
    virtual bool updateMatrices();

    /**
     * Initialize the task. If an ostream is given this ostream is used
     * instead of the target specified in the report. This allows nested
     * tasks to share the same output device.
     * @param const OutputFlag & of
     * @param COutputHandler * pOutputHandler
     * @param std::ostream * pOstream (default: NULL)
     * @return bool success
     */
    virtual bool initialize(const OutputFlag & of,
                            COutputHandler * pOutputHandler,
                            std::ostream * pOstream);

    /**
     * Process the task with or without initializing to the initial state.
     * @param const bool & useInitialValues
     * @return bool success
     */
    virtual bool process(const bool & useInitialValues);

    /**
     * Perform neccessary cleaup procedures
     */
    virtual bool restore();

    /**
     * Loads parameters for this solver with data coming from a
     * CReadConfig object. (CReadConfig object reads an input stream)
     * @param configbuffer reference to a CReadConfig object.
     */
    void load(CReadConfig & configBuffer);

    // Friend functions
    friend std::ostream &operator<<(std::ostream &os,
                                    const CMCATask &A);

    /**
     * This functionality is expected from the problem but has to be implemented
     * here for the moment. This is called from the corresponding method of the problem
     */
    void printResult(std::ostream * ostream) const;

  private:
    /**
     * cleanup()
     */
    void cleanup();
  };

#endif // COPASI_CMCATask_H__
