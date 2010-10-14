// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/optimization/COptItem.h,v $
//   $Revision: 1.22.2.1 $
//   $Name: Build-31 $
//   $Author: shoops $
//   $Date: 2010/02/26 16:01:20 $
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

#ifndef COPASI_COptItem
#define COPASI_COptItem

#include <vector>

#include "report/CCopasiObject.h"
#include "report/CCopasiContainer.h"
#include "utilities/CCopasiParameterGroup.h"

class CCopasiObjectName;
class COptProblem;
class CRandom;
class CCopasiDataModel;

class COptItem: public CCopasiParameterGroup
{
  //Operations
protected:
  /**
   * Default constructor
   */
  COptItem();

public:
  /**
   * Specific constructor
   * @param const CCopasiContainer * pParent
   * @param const std::string & name (default: OptimizationItem)
   */
  COptItem(const CCopasiContainer * pParent,
           const std::string & name = "OptimizationItem");

  /**
   * Copy constructor
   * @param const COptItem & src
   * @param const CCopasiContainer * pParent (default: src data model)
   */
  COptItem(const COptItem & src,
           const CCopasiContainer * pParent = NULL);

  /**
   * Specific constructor used for reading COPASI files
   * @param const CCopasiParameterGroup & group
   * @param const CCopasiContainer * pParent (default: group data model)
   */
  COptItem(const CCopasiParameterGroup & group,
           const CCopasiContainer * pParent = NULL);

  /**
   * Destructor
   */
  virtual ~COptItem();

  /**
   * Set the object of the optimization item.
   * @param const CCopasiObjectName & objectCN
   * @return bool success
   */
  bool setObjectCN(const CCopasiObjectName & objectCN);

  /**
   * Retrieve the object of the optimization item.
   * @return const CCopasiObjectName objectCN
   */
  const CCopasiObjectName getObjectCN() const;

  /**
   * Retrieve the item object. This may only be called after compile
   * @return const CCopasiObject *
   */
  const CCopasiObject * getObject() const;

  /**
   * Retrieve the display name of the optimization item.
   * @return std::string displayName
   */
  std::string getObjectDisplayName() const;

  /**
   * Set the lower bound.
   * @param const CCopasiObjectName & lowerBound
   * @return bool success
   */
  bool setLowerBound(const CCopasiObjectName & lowerBound);

  /**
   * Retrieve the lower bound.
   * @return const std::string lowerBound
   */
  const std::string getLowerBound() const;

  /**
   * Set the upper bound.
   * @param const CCopasiObjectName & upperBound
   * @return bool success
   */
  bool setUpperBound(const CCopasiObjectName & upperBound);

  /**
   * Retrieve the upper bound.
   * @return const std::string upperBound
   */
  const std::string getUpperBound() const;

  /**
   * Retrieve the update method
   * @return UpdateMethod * pUpdateMethod
   */
  virtual UpdateMethod * getUpdateMethod() const;

  /**
   * Check the validity of the optimization item.
   */
  virtual bool isValid() const;

  /**
   * Check whether the group describes a valid optimization item.
   * @return bool isValid
   */
  static bool isValid(CCopasiParameterGroup & group);

  /**
   * Compile the optimization item. This function must be called
   * before any of the check functions are called.
   * @param const std::vector< CCopasiContainer * > listOfContainer
   * @return bool success
   */
  virtual bool compile(const std::vector< CCopasiContainer * > listOfContainer =
                         CCopasiContainer::EmptyList);

  /**
   * This functions check whether the current value is within the limits
   * of the optimization item.
   * @return C_INT32 result (-1: to small, 0: within boundaries, 1 to large)
   */
  virtual C_INT32 checkConstraint() const;

  /**
   * Retrieve the magnitude of the constraint violation
   * This is always a positive number
   * @return C_FLOAT64 constraintViolation;
   */
  virtual C_FLOAT64 getConstraintViolation() const;

  /**
   * This functions check whether the value is within the limits
   * of the optimization item.
   * @param const C_FLOAT64 & value
   * @return C_INT32 result (-1: to small, 0: within boundaries, 1 to large)
   */
  C_INT32 checkConstraint(const C_FLOAT64 & value) const;

  /**
   * Checks whether the value fulfills the lower bound constraint.
   * @param const C_FLOAT64 & value
   * @return bool fulfills
   */
  bool checkLowerBound(const C_FLOAT64 & value) const;

  /**
   * Checks whether the value fulfills the upper bound constraint.
   * @param const C_FLOAT64 & value
   * @return bool fulfills
   */
  bool checkUpperBound(const C_FLOAT64 & value) const;

  /**
   * Retrieve the value of the optimization object.
   * @return const C_FLOAT64 * objectValue
   */
  virtual const C_FLOAT64 * getObjectValue() const;

  /**
   * Retrieve the value of the lower bound.
   * @return const C_FLOAT64 * lowerBoundValue
   */
  inline const C_FLOAT64 * getLowerBoundValue() const
  {return mpLowerBound;}

  /**
   * Retrieve the value of the upper bound.
   * @return const C_FLOAT64 * upperBoundValue
   */
  inline const C_FLOAT64 * getUpperBoundValue() const
  {return mpUpperBound;}

  /**
   * Set the value start value.
   * @param const C_FLOAT64 & startValue
   * @return bool succes
   */
  bool setStartValue(const C_FLOAT64 & value);

  /**
   * Retrieve the sart value of the optimization object.
   * @return const C_FLOAT64 & startValue
   */
  const C_FLOAT64 & getStartValue() const;

  /**
   * Retrieve a random value in the interval (lower bound, upper bound).
   * Optionally one may provide a random number generator to be used
   * to create the random value.
   * @param CRandom * pRandom (default: NULL)
   * @return C_FLOAT64 randomValue
   */
  C_FLOAT64 getRandomValue(CRandom * pRandom = NULL);

  /**
   * Output stream operator
   * @param ostream & os
   * @param const COptItem & A
   * @return ostream & os
   */
  friend std::ostream &operator<<(std::ostream &os, const COptItem & o);

private:
  /**
   * Allocates all group parameters and assures that they are
   * properly initialized.
   */
  void initializeParameter();

  /**
   * Compile the lower bound to hold the value given by the bound
   * @param const std::vector< CCopasiContainer * > & listOfContainer
   * @return bool success
   */
  bool compileLowerBound(const std::vector< CCopasiContainer * > & listOfContainer);

  /**
   * Compile the upper bound to hold the value given by the bound
   * @param const std::vector< CCopasiContainer * > & listOfContainer
   * @return bool success
   */
  bool compileUpperBound(const std::vector< CCopasiContainer * > & listOfContainer);

  //Attributes:
protected:
  /**
   * A pointer to the value of the CCopasiParameter holding the ObjectCN
   */
  std::string * mpParmObjectCN;

  /**
   * A pointer to the value of the CCopasiParameter holding the LowerBound
   */
  std::string * mpParmLowerBound;

  /**
   * A pointer to the value of the CCopasiParameter holding the UpperBound
   */
  std::string * mpParmUpperBound;

  /**
   * A pointer to the value of the CCopasiParameter holding the start value
   */
  C_FLOAT64 * mpParmStartValue;

  /**
   * A pointer to the object
   */
  const CCopasiObject * mpObject;

  /**
   * A pointer to the object update method
   */
  UpdateMethod * mpMethod;

  /**
   * A pointer to the object value
   */
  const C_FLOAT64 * mpObjectValue;

  /**
   * A pointer to the object for the lower bound
   */
  const CCopasiObject * mpLowerObject;

  /**
   * A pointer to the lower bound value
   */
  const C_FLOAT64 * mpLowerBound;

  /**
   * The value of the lower bound (only if not on object)
   */
  C_FLOAT64 mLowerBound;

  /**
   * A pointer to the object for the upper bound
   */
  const CCopasiObject * mpUpperObject;

  /**
   * A pointer to the upper bound value
   */
  const C_FLOAT64 * mpUpperBound;

  /**
   * The value of the upper bound (only if not on object)
   */
  C_FLOAT64 mUpperBound;

  /**
   * A pointer to the random number generator used in randomizeStartValue
   */
  static CRandom * mpRandom;
};

#endif // COPASI_COptItem
