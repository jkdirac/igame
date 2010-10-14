/* Begin CVS Header
   $Source: /fs/turing/cvs/copasi_dev/copasi/UI/CQFittingResultTab1.ui.h,v $
   $Revision: 1.6 $
   $Name: Build-31 $
   $Author: shoops $
   $Date: 2007/01/09 14:25:14 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** ui.h extension file, included from the uic-generated form implementation.
 **
 ** If you want to add, delete, or rename functions or slots, use
 ** Qt Designer to update this file, preserving your code.
 **
 ** You should not define a constructor or destructor in this file.
 ** Instead, write your code in functions called init() and destroy().
 ** These will automatically be called by the form's constructor and
 ** destructor.
 *****************************************************************************/

#include "copasi.h"

#include "parameterFitting/CFitProblem.h"
#include "parameterFitting/CFitItem.h"
#include "parameterFitting/CExperimentSet.h"
#include "parameterFitting/CExperiment.h"

#include "UI/qtUtilities.h"

void CQFittingResultTab1::load(const CFitProblem * pProblem)
{
  mpEditObjectiveValue->setText(QString::number(pProblem->getSolutionValue()));
  mpEditRMS->setText(QString::number(pProblem->getRMS()));
  mpEditStdDeviation->setText(QString::number(pProblem->getStdDeviation()));


#ifndef COPASI_CROSSVALIDATION
  mpLblCVObjectiveValue->hide();
  mpEditCVObjectiveValue->hide();
  mpLblCVRMS->hide();
  mpEditCVRMS->hide();
  mpLblCVStdDeviation->hide();
  mpEditCVStdDeviation->hide();
#endif // not COPASI_CROSSVALIDATION

  const unsigned C_INT32 & FunctionEvaluations = pProblem->getFunctionEvaluations();
  mpEditEvaluations->setText(QString::number(FunctionEvaluations));
  const C_FLOAT64 & ExecutionTime = pProblem->getExecutionTime();
  mpEditCPUTime->setText(QString::number(ExecutionTime));
  mpEditSpeed->setText(QString::number(FunctionEvaluations / ExecutionTime));
}

void CQFittingResultTab1::init()
{}
