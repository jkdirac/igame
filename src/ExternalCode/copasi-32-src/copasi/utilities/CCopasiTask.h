// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/utilities/CCopasiTask.h,v $
//   $Revision: 1.49 $
//   $Name: Build-31 $
//   $Author: shoops $
//   $Date: 2010/02/03 21:15:17 $
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
 *  CCopasiTask class.
 *  This class is used to describe a task in COPASI. This class is
 *  intended to be used as the parent class for all tasks whithin COPASI.
 *
 *  Created for Copasi by Stefan Hoops 2003
 */

#ifndef COPASI_CCopasiTask
#define COPASI_CCopasiTask

#include <string>

#include "utilities/COutputHandler.h"

#include "report/CCopasiContainer.h"
#include "report/CReport.h"

class CCopasiProblem;
class CCopasiMethod;
class CCopasiParameterGroup;
class CProcessReport;
class CState;

class CCopasiTask : public CCopasiContainer
{
public:
  /**
   * Enumeration of the types of tasks known to COPASI.
   */
  enum Type
  {
    steadyState = 0,
    timeCourse,
    scan,
    fluxMode,
    optimization,
    parameterFitting,
    mca,
    lyap,
    tssAnalysis,
#ifdef COPASI_TSS
    tss,
#endif // COPASI_TSS
    sens,
    moieties,
    unset
  };

  /**
   * String literals for the GUI to display type names of tasks known
   * to COPASI.
   */
  static const std::string TypeName[];

  /**
   * XML type names of tasks known to COPASI.
   */
  static const char* XMLType[];

  /**
   * The methods which can be selected for performing this task.
   */
  static const unsigned C_INT32 ValidMethods[];

  /**
   * Check whether the given method is in the list of valid methods
   * This list must end with CCopasiMethod::unset
   * @param const unsigned C_INT32 & method
   * @param const unsigned C_INT32 * validMethods
   * @return bool isValid
   */
  static bool isValidMethod(const unsigned C_INT32 & method,
                            const unsigned C_INT32 * validMethods);

  enum eOutputFlagBase
  {
    INITIALIZE = 0x01,
    STREAM = 0x02,
    FINISH = 0x04,
    REPORT = 0x10,
    PLOT = 0x20,
    TIME_SERIES = 0x40
  };

  enum OutputFlag
  {
    //do no output
    NO_OUTPUT = 0,
    //do output, but do not initialize/finish
    OUTPUT = REPORT | PLOT | TIME_SERIES | STREAM,
    //do output, including initialization and closing
    OUTPUT_COMPLETE = REPORT | PLOT | TIME_SERIES | INITIALIZE | STREAM | FINISH,
    // only do time series
    ONLY_TIME_SERIES = TIME_SERIES | INITIALIZE | STREAM | FINISH
  };

  class CDescription: public CCopasiObject
  {
  public:
    /**
     * Default constructor
     */
    CDescription(const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param const CDescription & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CDescription(const CDescription & src,
                 const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~CDescription();

    /**
     * This is the output method for any object. The default implementation
     * provided with CCopasiObject uses the ostream operator<< of the object
     * to print the object.To overide this default behaviour one needs to
     * reimplement the virtual print function.
     * @param std::ostream * ostream
     */
    virtual void print(std::ostream * ostream) const;

    /**
     * Output stream operator
     * @param ostream & os
     * @param const CDescription & A
     * @return ostream & os
     */
    friend std::ostream &operator<<(std::ostream &os, const CDescription & o);
  };

  class CResult: public CCopasiObject
  {
  public:
    /**
     * Default constructor
     */
    CResult(const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param const CResult & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CResult(const CResult & src,
            const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~CResult();

    /**
     * This is the output method for any object. The default implementation
     * provided with CCopasiObject uses the ostream operator<< of the object
     * to print the object.To overide this default behaviour one needs to
     * reimplement the virtual print function.
     * @param std::ostream * ostream
     */
    virtual void print(std::ostream * ostream) const;

    /**
     * Output stream operator
     * @param ostream & os
     * @param const CResult & A
     * @return ostream & os
     */
    friend std::ostream &operator<<(std::ostream &os, const CResult & o);
  };

  // Attributes
protected:
  /**
   * The type of the task
   */
  Type mType;

  /**
   * The key of the task
   */
  std::string mKey;

  /**
   * The description of the task.
   */
  CDescription mDescription;

  /**
   * The result of the task.
   */
  CResult mResult;

  /**
   * Tells whether the task is scheduled for execution
   */
  bool mScheduled;

  /**
   * Tells whether the task shall update the model with the result.
   * The restore method must act accordingly.
   */
  bool mUpdateModel;

  /**
   * The state of the model before execution of the task. If mUpdateModel
   * is false this state is restored.
   */
  CState * mpInitialState;

  /**
   * The problem of the task
   */
  CCopasiProblem * mpProblem;

  /**
   * The method used to solve the problem.
   */
  CCopasiMethod * mpMethod;

  /**
   * The report that belongs to this specific task
   */
  CReport mReport;

  /**
   * progress bar handler
   */
  CProcessReport * mpCallBack;

  /**
   * Pointer to group of sliders associated with the task.
   */
  CCopasiParameterGroup * mpSliders;

public:
  /**
   * Default constructor
   */
  CCopasiTask(const std::string & name = "NoName",
              const CCopasiContainer * pParent = NULL,
              const std::string & type = "Task");

  /**
   * Specific constructor
   * @param const Type & taskType
   * @param const CCopasiContainer * pParent (default: NULL)
   * @param const std::string & type (default: "Task")
   */
  CCopasiTask(const Type & taskType,
              const CCopasiContainer * pParent = NULL,
              const std::string & type = "Task");

  /**
   * Copy constructor
   * @param const CCopasiTask & src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CCopasiTask(const CCopasiTask & src,
              const CCopasiContainer * pParent = NULL);

  /**
   * Destructor
   */
  virtual ~CCopasiTask();

  /**
   * Retrieve the type of the task
   * @return CCopasiTask::Type type
   */
  Type getType() const;

  /**
   * Set the type of the task
   * @param CCopasiTask::Type & type
   */
  void setType(const Type & type);

  /**
   * Retrieve the key for the task.
   * @return std::string key
   */
  virtual const std::string & getKey() const;

  /**
   * Set whether the task is scheduled
   * @param const bool & scheduled
   */
  void setScheduled(const bool & scheduled);

  /**
   * Check whether the task is scheduled
   * @return const bool & scheduled
   */
  const bool & isScheduled() const;

  /**
   * Set whether the task must update the model
   * @param const bool & updateModel
   */
  void setUpdateModel(const bool & updateModel);

  /**
   * Check whether the task must update the modle
   * @return const bool & updateModel
   */
  const bool & isUpdateModel() const;

  /**
   * Set the call back of the task
   * @param CProcessReport * pCallBack
   * @result bool succes
   */
  virtual bool setCallBack(CProcessReport * pCallBack);

  CProcessReport * getCallBack() const;

  /**
   * Resizes result matrices and updates array annotations for a specific task.
   * For now this will be hardcoded in the respective derived classes.
   * We may introduce a more generic mechanism for this in the future.
   * This is used when we need to know about the data structures of a task result
   * without actually performing the task, e.g. when selecting objects for output.
   * For now we assume that this functionality is also performed when
   * initialize() is called.
   */
  virtual bool updateMatrices() {return true;};

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
   * Retrieve the problem
   */
  CCopasiProblem * getProblem();

  /**
   * Retrieve the problem
   */
  const CCopasiProblem * getProblem() const;

  /**
   * Set the method type applied to solve the task
   * @param const CCopasiMethod::SubType & type
   * @return bool success
   */
  virtual bool setMethodType(const int & type);

  /**
   * Retrieve the method
   */
  CCopasiMethod * getMethod();

  /**
   * Retrieve the method
   */
  const CCopasiMethod * getMethod() const;

  /**
   * Retrieve the report
   */
  CReport & getReport();

  /**
   * Retrieve the description
   */
  const CDescription & getDescription() const;

  /**
   * Retrieve the result
   */
  const CResult & getResult() const;

  /**
   * Cleanup function
   **/
  void cleanup();

  /**
   * Retrieve a pointer to the group of sliders.
   * @return CCopasiParameterGroup * pSliders
   */
  CCopasiParameterGroup * getSliders();

  //the following methods are wrappers for doing output. They are intended
  //to hide the fact that output is done using different mechanisms, e.g. reports and plots

  /**
   * Perform an output event for the current activity
   * @param const Activity & activity
   */
  virtual void output(const COutputInterface::Activity & activity);

  /**
   * Introduce an additional seperator into the ouput
   * @param const Activity & activity
   */
  virtual void separate(const COutputInterface::Activity & activity);

  inline const OutputFlag & getOutputMode() const
  {return mDoOutput;};

protected:
  OutputFlag mDoOutput;
  COutputHandler * mpOutputHandler;
  unsigned C_INT32 mOutputCounter;

private:
  void initObjects();
};

#endif // COPASI_CCopasiTask
