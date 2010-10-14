/* Begin CVS Header
$Source: /fs/turing/cvs/copasi_dev/copasi/UI/DefaultplotDialog.ui.h,v $
$Revision: 1.11 $
$Name: Build-31 $
$Author: shoops $
$Date: 2009/02/19 19:53:30 $
End CVS Header */

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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

#include "UI/qtUtilities.h"
#include "utilities/CCopasiTask.h"
#include "report/COutputAssistant.h"
#include "report/CCopasiRootContainer.h"

void DefaultPlotDialog::slotCreate()
{
  if (!mpTask) return;
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  if (COutputAssistant::createDefaultOutput(mIndex, mpTask, pDataModel))
    this->accept();
  else
    this->reject();
}

void DefaultPlotDialog::setTask(CCopasiTask * t)
{
  //set window header
  //this->resize(640, 480);
  this->setCaption("Output definition assistant");

  mpTask = t;
  if (!mpTask->getProblem()) return;
  //todo check
  mList = COutputAssistant::getListOfDefaultOutputDescriptions(mpTask->getProblem());
  listBox->clear();

  std::vector<C_INT32>::const_iterator it, itEnd = mList.end();
  for (it = mList.begin(); it != itEnd; ++it)
    {
      QString Name = FROM_UTF8(COutputAssistant::getItemName(*it));
      if (!Name.startsWith("--")) Name = "   " + Name;

      listBox->insertItem(Name);
    }
  listBox->setSelected(0, true);
}

void DefaultPlotDialog::slotSelect()
{
  if (!mpTask) return;

  C_INT32 i = listBox->currentItem();
  mIndex = mList[i];
  lineEditTitle->setText(FROM_UTF8(COutputAssistant::getItemName(mIndex)));
  textEdit->setText(FROM_UTF8(COutputAssistant::getItem(mIndex).description));

  createButton->setEnabled(!lineEditTitle->text().startsWith("-- "));
}

void DefaultPlotDialog::newSlot()
{}
