// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/elementaryFluxModes/CEFMTask.h,v $
//   $Revision: 1.6 $
//   $Name: Build-31 $
//   $Author: shoops $
//   $Date: 2009/10/01 19:58:29 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CEFMTask class.
 *  This class is used to describe a task in COPASI. This class is
 *  intended to be used as the parent class for all tasks whithin COPASI.
 *
 *  Created for Copasi by Stefan Hoops 2003
 */

#ifndef COPASI_CEFMTask
#define COPASI_CEFMTask

#include <string>

#include "utilities/CCopasiTask.h"

class CFluxMode;
class CMetab;

class CEFMTask : public CCopasiTask
{
public:
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

  /**
   * default constructor
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CEFMTask(const CCopasiContainer * pParent = NULL);

  /**
   * Copy constructor
   * @param const COptTask & src
   */
  //-COptTask(const CEFMTask & src);
  CEFMTask(const CEFMTask & src, const CCopasiContainer * pParent = NULL);

  /**
   * Destructor
   */
  virtual ~CEFMTask();

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

  /**
   * Retrieve the Flux Modes
   * @return const std::vector< CFluxMode > &
   */
  const std::vector< CFluxMode > & getFluxModes() const;

  /**
   * Retrieve the description of the flux mode
   * @param const CFluxMode & fluxMode
   * @return std::string fluxModeDescription
   */
  std::string getFluxModeDescription(const CFluxMode & fluxMode) const;

  /**
   * Retrieve the reaction equation of the part of the flux mode pointed at by itReaction
   * @param const std::map< size_t, C_FLOAT64 >::const_iterator & itReaction
   * @return std::string reactionEquation
   */
  std::string getReactionEquation(const std::map< size_t, C_FLOAT64 >::const_iterator & itReaction) const;

  /**
   * Retrieve the species changes for the given flux mode and species
   * @param const CFluxMode & fluxMode
   * @param const CMetab & pMetab
   * @return std::pair< C_FLOAT64, C_FLOAT64 > changes
   */
  std::pair< C_FLOAT64, C_FLOAT64 > getSpeciesChanges(const CFluxMode & fluxMode,
      const CMetab & metab) const;

  /**
   * Retrieve the net reaction for the given flux mode.
   * @param const CFluxMode & fluxMode
   * @return std::string netReaction
   */
  std::string getNetReaction(const CFluxMode & fluxMode) const;

  /**
   * Retrieve the internal species for the given flux mode.
   * @param const CFluxMode & fluxMode
   * @return std::string species
   */
  std::string getInternalSpecies(const CFluxMode & fluxMode) const;

private:
  /**
   * Retrieve the net reaction data for the given flux mode.
   * @param const CFluxMode & fluxMode
   * @return std::map< const CMetab *, C_FLOAT64 >g netReactionData
   */
  std::map< const CMetab *, C_FLOAT64 > getNetReactionData(const CFluxMode & fluxMode) const;

#ifdef COPASI_SSA
  std::string getReactionEquationForward(unsigned C_INT32 index1,
                                         unsigned C_INT32 index2) const;
  std::string getReactionEquationBackward(unsigned C_INT32 index1,
                                          unsigned C_INT32 index2) const;
#endif // COPASI_SSA
};

#endif // COPASI_CEFMTask
