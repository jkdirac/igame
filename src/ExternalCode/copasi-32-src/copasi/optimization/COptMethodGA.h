/* Begin CVS Header
 $Source: /fs/turing/cvs/copasi_dev/copasi/optimization/COptMethodGA.h,v $
 $Revision: 1.15 $
 $Name: Build-31 $
 $Author: shoops $
 $Date: 2008/12/18 19:00:32 $
 End CVS Header */

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * COptMethodGA class
 */

#ifndef COPASI_COptMethodGA
#define COPASI_COptMethodGA
#include <limits.h>

#include "optimization/COptMethod.h"
#include "utilities/CVector.h"

class CRandom;

class COptMethodGA : public COptMethod
  {
    friend COptMethod * COptMethod::createMethod(CCopasiMethod::SubType subType);

    // Operations
  public:
    /**
     * Copy Constructor
     * @param const COptMethodGA & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    COptMethodGA(const COptMethodGA & src,
                 const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~COptMethodGA();

    /**
     * Execute the optimization algorithm calling simulation routine
     * when needed. It is noted that this procedure can give feedback
     * of its progress by the callback function set with SetCallback.
     * @ return success;
     */
    virtual bool optimise();

  private:
    /**
     * Default Constructor
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    COptMethodGA(const CCopasiContainer * pParent = NULL);

    /**
     * Initialize contained objects.
     */
    void initObjects();

    /**
     * Initialize arrays and pointer.
     * @return bool success
     */
    virtual bool initialize();

    /**
     * Cleanup arrays and pointers.
     * @return bool success
     */
    virtual bool cleanup();

    /**
     * Evaluate the fitness of one individual
     * @param const CVector< C_FLOAT64 > & individual
     * @return bool continue
     */
    bool evaluate(const CVector< C_FLOAT64 > & individual);

    /**
     * Swap individuals from and to
     * @param unsigned C_INT32 from
     * @param unsigned C_INT32 to
     * @return bool success
     */
    bool swap(unsigned C_INT32 from, unsigned C_INT32 to);

    /**
     * Mutate one individual
     * @param CVector< C_FLOAT64 > & individual
     * @return bool success
     */
    bool mutate(CVector< C_FLOAT64 > & individual);

    /**
     * @param const CVector< C_FLOAT64 > & parent1
     * @param const CVector< C_FLOAT64 > & parent2
     * @param CVector< C_FLOAT64 > & child1
     * @param CVector< C_FLOAT64 > & child2
     */
    bool crossover(const CVector< C_FLOAT64 > & parent1,
                   const CVector< C_FLOAT64 > & parent2,
                   CVector< C_FLOAT64 > & child1,
                   CVector< C_FLOAT64 > & child2);

    /**
     * Shuffle the parents for breading
     * @return bool success
     */
    bool shuffle();

    /**
     * Replicate the individuals with crossover
     * @return bool continue
     */
    bool replicate();

    /**
     * Select surviving population
     * @return bool success
     */
    bool select();

    /**
     * Find the best individual at this generation
     * @return unsigned C_INT32 fittest
     */
    unsigned C_INT32 fittest();

    /**
     * Initialise the population
     * @param unsigned C_INT32 first
     * @param unsigned C_INT32 last (default: population size)
     * @return bool continue
     */
    bool creation(unsigned C_INT32 first, unsigned C_INT32 last = ULONG_MAX);

    // Attributes
  private:
    /**
     * number of generations
     */
    unsigned C_INT32 mGenerations;

    /**
     * Handle to the process report item "Current Generation"
     */
    unsigned C_INT32 mhGenerations;

    /**
     * size of the population
     */
    unsigned C_INT32 mPopulationSize;

    /**
     * a pointer to the randomnumber generator.
     */
    CRandom * mpRandom;

    /**
     * number of parameters
     */
    unsigned C_INT32 mVariableSize;

    /**
     * for array of individuals w/ candidate values for the parameters
     */
    std::vector< CVector < C_FLOAT64 > * > mIndividual;

    /**
     * Vector used to initialize the crossover point to false
     */
    CVector< bool > mCrossOverFalse;

    /**
     * Vector of crossover points.
     */
    CVector< bool > mCrossOver;

    /**
     * The value of the last evaluation.
     */
    C_FLOAT64 mEvaluationValue;

    /**
     * array of values of objective function f/ individuals
     */
    CVector< C_FLOAT64 > mValue;

    /**
     * indexes for shuffling the population
     */
    CVector< unsigned C_INT32 > mShuffle;

    /**
     * number of losses of each individual in the tournament
     */
    CVector< unsigned C_INT32 > mLosses;

    /**
     * The pivot vector used for sorting
     */
    CVector<unsigned C_INT32> mPivot;

    /**
     * variance for mutations
     */
    C_FLOAT64 mMutationVarians;

    C_FLOAT64 mBestValue;
    unsigned C_INT32 mBestIndex;
    unsigned C_INT32 mGeneration;
  };

#endif  // COPASI_COptMethodGA
