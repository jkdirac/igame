// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/trajectory/CStochMethod.h,v $
//   $Revision: 1.32 $
//   $Name: Build-31 $
//   $Author: shoops $
//   $Date: 2009/11/20 18:24:25 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CStochMethod
#define COPASI_CStochMethod

#include <set>
#include <vector>
#include "trajectory/CTrajectoryMethod.h"
#include "utilities/CDependencyGraph.h"

class CModel;
class CMetab;
class CTrajectoryProblem;

/**
 * Integer Balances  for internal use
 */
class CStochBalance
{
public:
  C_INT32 mIndex;
  C_INT32 mMultiplicity;
};

class CRandom;

class CStochMethod : public CTrajectoryMethod
{
  friend CTrajectoryMethod *
  CTrajectoryMethod::createTrajectoryMethod(CCopasiMethod::SubType subType,
      CTrajectoryProblem * pProblem);

protected:

  /**
   * The propensities for the reactions
   */
  std::vector<C_FLOAT64> mAmu;

  /**
   * The sum of the propensities
   */
  C_FLOAT64 mA0;

  /**
   * The stored propensities for the reactions before the last update
   */
  std::vector<C_FLOAT64> mAmuOld;

  /**
   * indicates if the correction N^2 -> N*(N-1) should be performed
   */
  bool mDoCorrection;

  /**
   * Indicates whether the model has global quantities with assignment rules.
   * If it has, we will use a less efficient way to update the model
   * state to handle this.
   */
  bool mHasAssignments;

  /**
   * Initialization.
   */
  virtual void initMethod(C_FLOAT64 start_time) = 0;

  /**
   * Do one iteration of the simulation
   * @return Current simulation time or -1 if error.
   */
  virtual C_FLOAT64 doSingleStep(C_FLOAT64 time, C_FLOAT64 endtime) = 0;

  /**
   * Calculate the propensities for all reactions
   * @return mFail
   * @see mFail
   */
  C_INT32 updatePropensities();

  /**
   * Calculate one of the propensities
   * @return mFail
   * @see mFail
   */
  C_INT32 calculateAmu(C_INT32 reaction_index);

  /**
   * Generate the index of a putative reaction.
   * @return The reaction index
   */
  C_INT32 generateReactionIndex();

  /**
   * Generate the putative time taken before any reaction takes place
   * @return The time before the reaction
   */
  C_FLOAT64 generateReactionTime();

  /**
   * Generate the putative time taken before a special reaction takes place
   * @return The time before the reaction
   */
  C_FLOAT64 generateReactionTime(C_INT32 reaction_index);

  /**
   * Update the particle numbers according to which reaction ocurred
   * @return mFail
   * @see mFail
   */
  C_INT32 updateSystemState(C_INT32 reaction_index);

  /**
  * Set up the dependency graph and the balances
  */
  void setupDependencyGraphAndBalances();

private:

  /**
   *  This checks if a model is suitable for stochastic simulation.
   *  It returns a suggestion which method to use
   *  @param model The model to check
   *  @return 1: direct method, 2: next reaction method, -1: no stochastic simulation possible
   */
  static C_INT32 checkModel(CModel * pmodel);

  /**
   * Get the set of metabolites on which a given reaction depends.
   * @param reaction_index The index of the reaction being executed.
   * @return The set of metabolites depended on.
   */
  std::set<std::string> *getDependsOn(C_INT32 reaction_index);

  /**
   * Get the set of metabolites which change number when a given
   * reaction is executed.
   * @param reaction_index The index of the reaction being executed.
   * @return The set of affected metabolites.
   */
  std::set<std::string> *getAffects(C_INT32 reaction_index);

  /**
  * max number of single stochastic steps to do in one step()
  */
  C_INT32 mMaxSteps;

  /**
  * maximal increase of a particle number in one step.
  */
  C_INT32 mMaxBalance;

  /**
  * This is set to maxint - mMaxSteps*mMaxBalance
  */
  C_INT64 mMaxIntBeforeStep;

  bool mMaxStepsReached;

protected:
  /**
   * Default constructor.
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CStochMethod(const CCopasiContainer * pParent = NULL);

public:
  /**
   * Copy constructor.
   * @param const CStochMethod & src,
   * @param const CCopasiContainer * pParent (Default: NULL)
   */
  CStochMethod(const CStochMethod & src,
               const CCopasiContainer * pParent = NULL);

  /**
   *  Destructor.
   */
  ~CStochMethod();

  /**
   * This methods must be called to elevate subgroups to
   * derived objects. The default implementation does nothing.
   * @return bool success
   */
  virtual bool elevateChildren();

  /**
   *  Chooses a stochastic method adequate for the problem
   */
  static CStochMethod * createStochMethod();

  /**
   *  This instructs the method to calculate a time step of deltaT
   *  starting with the current state, i.e., the result of the previous
   *  step.
   *  The new state (after deltaT) is expected in the current state.
   *  The return value is the actual timestep taken.
   *  @param "const double &" deltaT
   *  @return Status status
   */
  virtual Status step(const double & deltaT);

  /**
   *  This instructs the method to prepare for integration
   *  starting with the initialState given.
   *  @param "const CState *" initialState
   */
  virtual void start(const CState * initialState);

  /**
  * Check if the method is suitable for this problem
  * @return bool suitability of the method
  */
  virtual bool isValidProblem(const CCopasiProblem * pProblem);

private:
  /**
   * Intialize the method parameter
   */
  void initializeParameter();

protected:

  /**
   * The random number generator
   */
  CRandom *mpRandomGenerator;

  /**
   * A pointer to the instance of CModel being used.
   */
  CModel *mpModel;

  /**
   * The graph of reactions and their dependent reactions. When a reaction is
   * executed, the propensities for each of its dependents must be updated.
   */
  CDependencyGraph mDG;

  /**
   * The balances of the reactions as integers
   */
  std::vector < std::vector <CStochBalance> > mLocalBalances;

  /**
   * the substrates of each reaction with their multiplicities
   */
  std::vector < std::vector <CStochBalance> > mLocalSubstrates;

  /**
   * The particle numbers
   */
  std::vector <C_INT64> mNumbers;

  unsigned C_INT32 mNumReactions;

  /**
   * index of first metab in a CState
   */
  unsigned C_INT32 mFirstMetabIndex;

  /**
   * tests if the model contains a global value with an assignment rule that is
   * used in calculations
   */
  static bool modelHasAssignments(const CModel* pModel);
};

//#include "CStochDirectMethod.h"
//#include "CStochNextReactionMethod.h"

#endif // COPASI_CStochMethod
