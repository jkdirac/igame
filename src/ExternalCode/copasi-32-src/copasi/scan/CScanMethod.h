// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/scan/CScanMethod.h,v $
//   $Revision: 1.35 $
//   $Name: Build-31 $
//   $Author: gauges $
//   $Date: 2009/02/19 15:40:11 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CScanMethod class.
 *  This class describes the method for doing the Scan.
 */

#ifndef COPASI_CScanMethod
#define COPASI_CScanMethod

#include <string>

#include "utilities/CCopasiMethod.h"
#include "steadystate/CSteadyStateTask.h"
#include "trajectory/CTrajectoryTask.h"
#include "report/CReport.h"

class CScanProblem;
class CScanTask;
class CSteadyStateTask;
class CTrajectory;
class CRandom;

class CScanItem
  {
  protected:
    unsigned C_INT32 mNumSteps;

    // C_FLOAT64 * mpValue;
    CCopasiObject * mpValue;

    C_FLOAT64 mStoreValue;

    unsigned C_INT32 mIndex;

    bool mFlagFinished;

  public:
    static
    CScanItem* createScanItemFromParameterGroup(CCopasiParameterGroup* si,
        CRandom* rg,
        CScanTask* st);

    unsigned C_INT32 getNumSteps() const;

    void restoreValue() const;

    void storeValue();

    virtual void reset();

    virtual void step() = 0;

    virtual bool isFinished() const;

    virtual bool isNesting() const {return true;};

    virtual ~CScanItem(){};

    /**
     * perform checks. This is used in the method::isValidProblem() method.
     * It returns false for an invalid ScanItem and generates a CCopasiMessage
     */
    virtual bool isValidScanItem();

    /**
     * Retrieve the object which is scanned by the item.
     * @return const CCopasiObject * object
     */
    const CCopasiObject * getObject() const;

  protected:

    CScanItem(CCopasiParameterGroup* si);

    //initObject();

  private:
    CScanItem() {};
  };

//***********************************+

class CScanItemRepeat: public CScanItem
  {
  public:
    CScanItemRepeat(CCopasiParameterGroup* si);
    void step();

    virtual ~CScanItemRepeat(){};
  };

//***********************************+

class CScanItemLinear: public CScanItem
  {
  private:
    C_FLOAT64 mMin, mMax, mFaktor;
    bool mLog;
  public:
    CScanItemLinear(CCopasiParameterGroup* si);
    void step();

    virtual ~CScanItemLinear(){};

    virtual bool isValidScanItem();
  };

//***********************************+

class CScanItemRandom: public CScanItem
  {
  private:
    C_FLOAT64 mMin, mMax, mFaktor;
    CRandom* mRg;
    unsigned C_INT32 mRandomType;
    bool mLog;
  public:
    CScanItemRandom(CCopasiParameterGroup* si, CRandom* rg);
    virtual ~CScanItemRandom(){};

    void step();
    virtual bool isNesting() const {return false;};
    virtual bool isValidScanItem();
  };

//***********************************+

/*class CScanItemBreak: public CScanItem
  {
  private:
    unsigned C_INT32 mPlotB, mReportB;
    CScanTask* mST;
  public:
    CScanItemBreak(const CCopasiParameterGroup* si, CScanTask* st);
    void step();
    virtual bool isNesting() const {return false;};
  };*/

//*******************************************+
//*******************************************+

class CScanMethod : public CCopasiMethod
  {
  protected:
    /**
     *  A pointer to the trajectory problem.
     */
    CScanProblem * mpProblem;

    /**
     *  A pointer to the scan Task.
     */
    CScanTask * mpTask;

    /**
     * A pointer to the random number generator
     */
    CRandom * mpRandomGenerator;

    std::vector<CScanItem*> mScanItems;

    std::vector< Refresh * > mInitialRefreshes;

    unsigned C_INT32 mTotalSteps;

    /**
     * the index of the last item that has several subitems,
     * also the last item that need to generate output separators
     */
    C_INT32 mLastNestingItem;

    /**
     *
     */
    //unsigned C_INT32 mVariableSize;

    /**
     *
     */
    //C_FLOAT64 * mpVariables;

    // Operations
  private:
    /**
     * Default constructor.
     */
    CScanMethod();

  protected:
    /**
     * Specific constructor.
     * @param CCopasiMethod::SubType subType
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CScanMethod(CCopasiMethod::SubType subType,
                const CCopasiContainer * pParent = NULL);

  public:
    /**
     * Create a trajectory method.
     * Note: the returned object has to be released after use with delete
     */

    static CScanMethod * createMethod();

    /**
     *  Copy constructor.
     *  @param "const CTrajectoryMethod &" src
     */
    //CScanMethod(const CScanMethod & src,
    //            const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    ~CScanMethod();

    /**
     *  Set a pointer to the problem.
     *  This method is used by CTrajectory
     *  @param "CTrajectoryProblem *" problem
     */
    void setProblem(CScanProblem * problem);

    bool init();

    bool scan();

    unsigned C_INT32 getTotalNumberOfSteps() const {return mTotalSteps;};

    /**
     *  The main scan method.
     */
    //void scan(unsigned C_INT32 s, bool C_UNUSED(nl), void (*pCallback)(CReport *), CReport *pReport);

    /**
     * Check if the method is suitable for this problem
     * @return bool suitability of the method
     */
    virtual bool isValidProblem(const CCopasiProblem * pProblem);

  private:

    bool cleanupScanItems();

    bool loop(unsigned C_INT32 level);

    bool calculate();

    /**
     *  Set the value of the scan parameter based on the distribution
     *  @param unsigned C_INT32 i where to start in the distribution
     *  @param unsigned C_INT32 first first parameter in the set of Master/Slaves
     *  @param unsigned C_INT32 last last parameter in the set of Master/Slaves
     */
    //void setScanParameterValue(unsigned C_INT32 i,
    //                           unsigned C_INT32 first,
    //                           unsigned C_INT32 last);
  };

#endif // COPASI_CTrajectoryMethod
