// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/tssanalysis/CILDMMethod.h,v $
//   $Revision: 1.11 $
//   $Name: Build-31 $
//   $Author: shoops $
//   $Date: 2009/04/21 16:20:02 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CILDMMethod
#define COPASI_CILDMMethod

#include <sstream>
#include "utilities/CVector.h"
#include "utilities/CMatrix.h"

#include "CTSSAMethod.h"

//#include "odepack++/CLSODA.h"

//#include "utilities/CMatrix.h"
//#include "utilities/CAnnotatedMatrix.h"

class CModel;
class CState;

class CILDMMethod : public CTSSAMethod
{
  friend CTSSAMethod *
  CTSSAMethod::createTSSAMethod(CCopasiMethod::SubType subType,
                                CTSSAProblem * pProblem);
  // Operations
private:
  /**
   * Default constructor.
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CILDMMethod(const CCopasiContainer * pParent = NULL);

public:
  /**
   * Copy constructor.
   * @param "const CILDMMethod &" src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CILDMMethod(const CILDMMethod & src,
              const CCopasiContainer * pParent = NULL);

  /**
   *  Destructor.
   */
  ~CILDMMethod();

  /**
   *  Intialize the method parameter
   */
  virtual void initializeParameter();

  /**
   *  This instructs the method to calculate a time step of deltaT
   *  starting with the current state, i.e., the result of the previous
   *  step.
   *  The new state (after deltaT) is expected in the current state.
   *  The return value is the actual timestep taken.
   *  @param "const double &" deltaT
   */
  virtual void step(const double & deltaT);

  /**
   *  This instructs the method to prepare for integration
   *  starting with the initialState given.
   *  @param "const CState *" initialState
   */
  virtual void start(const CState * initialState);

  /**
   *
   **/
  void newton(C_FLOAT64 *ys, C_INT & slow, C_INT & info);

  /**
     *
     **/

  void transformation_norm(C_INT & slow, C_INT & info);

  void deuflhard(C_INT & slow, C_INT & info);

  /**
     *vectors contain whole data for all calculation steps
     **/

  CVector<C_FLOAT64> mReacSlowSpace; // NEW TAB

  /* temporary tabs */

  CMatrix<C_FLOAT64> mTMP1;
  CMatrix<C_FLOAT64> mTMP2;
  CMatrix<C_FLOAT64> mTMP3;

  std::vector< CMatrix<C_FLOAT64> > mVec_mVslow;
  std::vector< CMatrix<C_FLOAT64> > mVec_mVslowMetab;
  std::vector< CVector<C_FLOAT64> > mVec_mVslowSpace;
  std::vector< CVector<C_FLOAT64> > mVec_mVfastSpace;
  std::vector< CVector<C_FLOAT64> > mVec_mReacSlowSpace;

  /* temporary tabs */
  std::vector< CMatrix<C_FLOAT64> > mVec_mTMP1;
  std::vector< CMatrix<C_FLOAT64> > mVec_mTMP2;
  std::vector< CMatrix<C_FLOAT64> > mVec_mTMP3;

  /**
   *CArraAnnotations for every ILDM-tab in the CQTSSAResultSubWidget
   **/
  CArrayAnnotation* pVslowPrintAnn;
  CArrayAnnotation* pVslowMetabPrintAnn;
  CArrayAnnotation* pVslowSpacePrintAnn;
  CArrayAnnotation* pVfastSpacePrintAnn;
  CArrayAnnotation* pReacSlowSpacePrintAnn;

  /* temporary tabs */

  CArrayAnnotation* pTMP1PrintAnn;
  CArrayAnnotation* pTMP2PrintAnn;
  CArrayAnnotation* pTMP3PrintAnn;

  /**
  *required for creation of above listed CArrayAnnotation
  **/
  CArrayAnnotation* pTmp1;
  CArrayAnnotation* pTmp2;
  CArrayAnnotation* pTmp3;
  CArrayAnnotation* pTmp4;
  CArrayAnnotation* pTmp5;

  /* temporary tabs */

  CArrayAnnotation* pTMP1;
  CArrayAnnotation* pTMP2;
  CArrayAnnotation* pTMP3;

  /**
  *input for every CArraAnnotations
  *contain data for single stepcalculation
  **/
  CMatrix<C_FLOAT64> mVslowPrint;
  CMatrix<C_FLOAT64> mVslowSpacePrint;
  CMatrix<C_FLOAT64> mVfastSpacePrint;
  CMatrix<C_FLOAT64> mVslowMetabPrint;
  CMatrix<C_FLOAT64> mReacSlowSpacePrint;

  /* temporary tabs */

  CMatrix<C_FLOAT64> mTMP1Print;
  CMatrix<C_FLOAT64> mTMP2Print;
  CMatrix<C_FLOAT64> mTMP3Print;

  /**
  * return CArrayAnnotation for visualization in ILDM-tab
  * in the CQTSSAResultSubWidget
  **/
  const CArrayAnnotation* getVslowPrintAnn() const
  {return pVslowPrintAnn;}
  const CArrayAnnotation* getVslowSpacePrintAnn() const
  {return pVslowSpacePrintAnn;}
  const CArrayAnnotation* getVfastSpacePrintAnn() const
  {return pVfastSpacePrintAnn;}
  const CArrayAnnotation* getVslowMetabPrintAnn() const
  {return pVslowMetabPrintAnn;}
  const CArrayAnnotation* getReacSlowSpacePrintAnn() const
  {return pReacSlowSpacePrintAnn;}

  /* temporary tabs */
  const CArrayAnnotation* getTMP1PrintAnn() const
  {return pTMP1PrintAnn;}
  const CArrayAnnotation* getTMP2PrintAnn() const
  {return pTMP2PrintAnn;}
  const CArrayAnnotation* getTMP3PrintAnn() const
  {return pTMP3PrintAnn;}

  /* temporary tabs */

  /**
  * upgrade all vectors with values from actually calculalion for current step
  **/
  void setVectors(int slowMode);

  /**
  * empty every vector to be able to fill them with new values for a
  * new calculation also nullify the step counter
  **/
  void emptyVectors();

  /**
   * create the CArraAnnotations for every ILDM-tab in the CQTSSAResultSubWidget
   * input for each CArraAnnotations is a seperate CMatrix
   **/
  void createAnnotationsM();

  /**
  * set the every CArrayAnnotation for the requested step
  * set the desription of CArayAnnotation for both dimensions
  **/
  void setAnnotationM(int step);

  /**
   *  print of the standart report sequence for ILDM Method
   *  @param std::ostream * ostream
   **/
  void printResult(std::ostream * ostream) const;
};
#endif // COPASI_CILDMMethod
