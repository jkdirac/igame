// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/moieties/CMoietiesTask.h,v $
//   $Revision: 1.3 $
//   $Name: Build-31 $
//   $Author: gauges $
//   $Date: 2009/02/18 20:54:45 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CMoietiesTask
#define COPASI_CMoietiesTask

#include "copasi/utilities/CCopasiTask.h"

class CProcessReport;

class CMoietiesTask : public CCopasiTask
  {
    //Attributes

  public:
    /**
     * The methods which can be selected for preforming this task.
     */
    static unsigned C_INT32 ValidMethods[];

    /**
     * default constructor
     * @param const CCopasiTask::Type & type (default: moieties)
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CMoietiesTask(const CCopasiTask::Type & type = CCopasiTask::moieties,
                  const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param const CMoietiesTask & src
     */
    //-CMoietiesTask(const CMoietiesTask & src);
    CMoietiesTask(const CMoietiesTask & src, const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    ~CMoietiesTask();

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
     * Set the method type applied to solve the task
     * @param const CCopasiMethod::SubType & type
     * @return bool success
     */
    virtual bool setMethodType(const int & type);
  };
#endif // COPASI_CMoietiesTask
