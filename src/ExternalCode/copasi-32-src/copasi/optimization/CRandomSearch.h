/* Begin CVS Header
   $Source: /fs/turing/cvs/copasi_dev/copasi/optimization/CRandomSearch.h,v $
   $Revision: 1.12 $
   $Name: Build-31 $
   $Author: shoops $
   $Date: 2006/04/27 01:29:53 $
   End CVS Header */

// Copyright � 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CRandomSearch class
 */

#ifndef COPASI_CRandomSearch
#define COPASI_CRandomSearch

//class CRandom;
//*** need to be added for definition
class COptProblem;
class COptMethod;

#include "randomGenerator/CRandom.h"
#include "utilities/CVector.h"

// YOHE: this is an abstract class that contains many virtual functions
// without definitions
//
/** @dia:pos 48.05,34.05 */
/** @dia:route COptMethod; v,46.9608,16.35,33,59.1652,34.05 */
class CRandomSearch : public COptMethod
  {
    friend COptMethod * COptMethod::createMethod(CCopasiMethod::SubType subType);

    // Operations
  private:
    /**
     * Default Constructor
     */
    CRandomSearch();

    /**
        * Initialize arrays and pointer.
        * @return bool success
        */
    virtual bool initialize();

    /**
     * Initialize contained objects.
     */
    void initObjects();

    /**
     * Evaluate the fitness of one individual
     * @param const CVector< C_FLOAT64 > & individual
     * @return bool continue
     */
    bool evaluate(const CVector< C_FLOAT64 > & individual);

    /**
     * Find the best individual at this generation
     * @return unsigned C_INT32 fittest
     */
    unsigned C_INT32 fittest();

    /**
     * number of iterations
     */
    unsigned C_INT32 mIterations;

    /**
     * The current iteration
     */
    unsigned C_INT32 mCurrentIteration;

    /**
     * a vector of the number of individuals.
     */
    CVector<C_FLOAT64> mIndividual;

    /**
     * array of values of objective function f/ individuals
     */
    C_FLOAT64 mValue;

    /**
     * a pointer to the randomnumber generator.
     */
    CRandom * mpRandom;

    /**
     * *** Perhaps this is actually not needed ****number of parameters
     */
    unsigned C_INT32 mVariableSize;

    /**
     * The best value found so far.
     */
    C_FLOAT64 mBestValue;

  public:
    /**
     * Copy Constructor
     * @param const CRandomSearch & src
     */
    CRandomSearch(const CRandomSearch & src);

    /**
     * Destructor
     */
    virtual ~CRandomSearch();

    /**
     * Execute the optimization algorithm calling simulation routine
     * when needed. It is noted that this procedure can give feedback
     * of its progress by the callback function set with SetCallback.
     */
    virtual bool optimise();
  };

#endif  // COPASI_CRandomSearch
