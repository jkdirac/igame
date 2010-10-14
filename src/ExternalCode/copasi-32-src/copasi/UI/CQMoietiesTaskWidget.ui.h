// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/UI/CQMoietiesTaskWidget.ui.h,v $
//   $Revision: 1.5 $
//   $Name: Build-31 $
//   $Author: aekamal $
//   $Date: 2010/02/01 16:48:36 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
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

#include <qcheckbox.h>

#include "copasi/UI/CQTaskBtnWidget.h"
#include "copasi/UI/CQTaskHeaderWidget.h"

#include "copasi/moieties/CMoietiesMethod.h"
#include "copasi/moieties/CMoietiesTask.h"

void CQMoietiesTaskWidget::init()
{
  mpHeaderWidget->setTaskName("Mass Conservation");
  mpHeaderWidget->mpUpdateModel->hide();

  vboxLayout->insertWidget(0, mpHeaderWidget);
  vboxLayout->addWidget(mpBtnWidget);
}

void CQMoietiesTaskWidget::destroy()
{}

bool CQMoietiesTaskWidget::runTask()
{
  if (dynamic_cast< CMoietiesTask * >(mpTask) == NULL)
    return false;

  if (!commonBeforeRunTask()) return false;

  bool success = commonRunTask();

  commonAfterRunTask();

  if (success && isShown())
    mpListView->switchToOtherWidget(2221, ""); //change to the results window

  return success;
}

bool CQMoietiesTaskWidget::saveTask()
{
  if (dynamic_cast< CMoietiesTask * >(mpTask) == NULL)
    return false;

  saveCommon();

  return true;
}

bool CQMoietiesTaskWidget::loadTask()
{
  if (dynamic_cast< CMoietiesTask * >(mpTask) == NULL)
    return false;

  loadCommon();

  return true;
}

CCopasiMethod * CQMoietiesTaskWidget::createMethod(const CCopasiMethod::SubType & type)
{
  return CMoietiesMethod::createMethod(type);
}
