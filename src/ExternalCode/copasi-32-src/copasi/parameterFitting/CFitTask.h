// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/parameterFitting/CFitTask.h,v $
//   $Revision: 1.7 $
//   $Name: Build-31 $
//   $Author: gauges $
//   $Date: 2009/02/18 20:54:46 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CFitTask class.
 *
 * This class implements a parameter estimation task which is comprised of a
 * of a problem and a method.
 *
 */

#ifndef COPASI_CFitTask
#define COPASI_CFitTask

#include "optimization/COptTask.h"

class CFitTask : public COptTask
  {
    //Attributes

  public:
    /**
     * default constructor
     * @param const CCopasiTask::Type & type (default: parameterFitting)
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CFitTask(const CCopasiTask::Type & type = CCopasiTask::parameterFitting,
             const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param const CFitTask & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CFitTask(const CFitTask & src, const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    ~CFitTask();

    /**
     * cleanup()
     */
    void cleanup();

    /**
     * Set the call back of the task
     * @param CProcessReport * pCallBack
     * @result bool succes
     */
    virtual bool setCallBack(CProcessReport * pCallBack);

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
     * Set the method type applied to solve the task
     * @param const CCopasiMethod::SubType & type
     * @return bool success
     */
    virtual bool setMethodType(const int & type);
  };
#endif // COPASI_CFitTask
