/* Begin CVS Header
   $Source: /fs/turing/cvs/copasi_dev/copasi/elementaryFluxModes/CEFMMethod.h,v $
   $Revision: 1.5 $
   $Name: Build-31 $
   $Author: shoops $
   $Date: 2010/02/03 17:18:42 $
   End CVS Header */

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CEFMMethod
#define COPASI_CEFMMethod

#include <string>

#include "elementaryFluxModes/CFluxMode.h"

#include "utilities/CCopasiMethod.h"
#include "utilities/CVector.h"

class CEFMMethod : public CCopasiMethod
{
  // Operations
private:
  /**
   * Default constructor.
   */
  CEFMMethod();

protected:
  /**
   * Specific constructor
   * @param const CCopasiTask::Type & type
   * @param const CCopasiMethod::SubType & subType
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CEFMMethod(const CCopasiTask::Type & taskType,
             const SubType & subType,
             const CCopasiContainer * pParent = NULL);

public:
  /**
   * Create a EFM method.
   * Note: the returned object has to be released after use with delete
   */
  static CEFMMethod * createMethod(CCopasiMethod::SubType subType
                                   = CCopasiMethod::RandomSearch);

  /**
   * Copy constructor
   * @param const CEFMMethod & src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CEFMMethod(const CEFMMethod & src,
             const CCopasiContainer * pParent = NULL);

  /**
   * Destructor
   */
  virtual ~CEFMMethod();

  /**
   * Execute the optimization algorithm calling simulation routine
   * when needed. It is noted that this procedure can give feedback
   * of its progress by the callback function set with SetCallback.
   * @ return success;
   */
  virtual bool calculate();

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
  /**
   * The resulting elementary flux modes
   */
  std::vector< CFluxMode > *mpFluxModes;

  /**
   * Reactions in the order used in the analysis
   */
  std::vector< const CReaction * > *mpReorderedReactions;
};

#endif  // COPASI_CEFMMethod
