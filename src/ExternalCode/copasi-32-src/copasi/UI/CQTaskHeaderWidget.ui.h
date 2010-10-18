/* Begin CVS Header
   $Source: /fs/turing/cvs/copasi_dev/copasi/UI/CQTaskHeaderWidget.ui.h,v $
   $Revision: 1.7 $
   $Name: Build-31 $
   $Author: shoops $
   $Date: 2006/10/28 00:26:44 $
   End CVS Header */

// Copyright � 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "UI/qtUtilities.h"

#include "utilities/CCopasiTask.h"

bool CQTaskHeaderWidget::setTaskName(const std::string & name)
{
  mpLblName->setText("<h2>" + FROM_UTF8(name) + "</h2>");
  return true;
}

void CQTaskHeaderWidget::saved()
{
  mUpdateChanged = false;
  mpUpdateModel->setPaletteBackgroundColor(mSavedColor);

  mExecutableChanged = false;
  mpBoxExecutable->setPaletteBackgroundColor(mSavedColor);
}

void CQTaskHeaderWidget::slotUpdate()
{
  mUpdateChanged = !mUpdateChanged;

  if (mUpdateChanged)
    mpUpdateModel->setPaletteBackgroundColor(mChangedColor);
  else
    mpUpdateModel->setPaletteBackgroundColor(mSavedColor);
}

void CQTaskHeaderWidget::slotExecutable()
{
  mExecutableChanged = !mExecutableChanged;

  if (mExecutableChanged)
    mpBoxExecutable->setPaletteBackgroundColor(mChangedColor);
  else
    mpBoxExecutable->setPaletteBackgroundColor(mSavedColor);
}

void CQTaskHeaderWidget::init()
{
  mUpdateChanged = false;
  mExecutableChanged = false;

  int h, s, v;

  mSavedColor = paletteBackgroundColor();
  mSavedColor.getHsv(&h, &s, &v);

  if (s < 20) s = 20;
  mChangedColor.setHsv(240, s, v);
}
