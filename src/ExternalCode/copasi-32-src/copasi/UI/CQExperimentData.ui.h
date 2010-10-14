// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/UI/CQExperimentData.ui.h,v $
//   $Revision: 1.44.2.3 $
//   $Name: Build-31 $
//   $Author: shoops $
//   $Date: 2010/06/03 16:43:27 $
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

#include <algorithm>
#include <limits>
#include <math.h>

#include <qsignalmapper.h>
#include <qcombobox.h>

#include "copasi.h"

#include "UI/CCopasiSelectionDialog.h"
#include "UI/CopasiFileDialog.h"
#include "UI/CQValidator.h"
#include "UI/qtUtilities.h"
#include "UI/CQMessageBox.h"

#include "parameterFitting/CExperimentSet.h"
#include "parameterFitting/CExperiment.h"
#include "parameterFitting/CExperimentFileInfo.h"
#include "parameterFitting/CExperimentObjectMap.h"

#include "report/CKeyFactory.h"
#include "utilities/CDirEntry.h"
#include "utilities/utility.h"
#include "copasi/report/CCopasiRootContainer.h"

#define COL_NAME 0
#define COL_TYPE 1
#define COL_TYPE_HIDDEN 2
#define COL_BTN 3
#define COL_OBJECT 4
#define COL_OBJECT_HIDDEN 5
#define COL_WEIGHT 6

static const unsigned char copasi_data[] =
{
  0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
  0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10,
  0x08, 0x06, 0x00, 0x00, 0x00, 0x1f, 0xf3, 0xff, 0x61, 0x00, 0x00, 0x02,
  0x5c, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0xa5, 0x93, 0x4d, 0x4f, 0x13,
  0x71, 0x10, 0x87, 0x9f, 0xff, 0xee, 0xd6, 0xd6, 0xb6, 0xdb, 0x52, 0x5a,
  0x40, 0x81, 0x16, 0x85, 0x5a, 0x5e, 0x04, 0xa2, 0xa9, 0x26, 0x26, 0x98,
  0x88, 0x89, 0x07, 0xaf, 0xc6, 0x0f, 0xe8, 0x47, 0xc0, 0x98, 0x78, 0x30,
  0x6a, 0x0c, 0x97, 0x62, 0xc4, 0x82, 0xc8, 0x6b, 0x63, 0x43, 0xaa, 0xa0,
  0xad, 0x5d, 0xe8, 0xf2, 0x62, 0x29, 0xdd, 0x6d, 0x3b, 0x1e, 0x10, 0x22,
  0x41, 0xf4, 0xe0, 0x9c, 0x26, 0x33, 0xf3, 0xfc, 0x0e, 0xbf, 0x99, 0x51,
  0x99, 0x4c, 0x86, 0xff, 0x09, 0xe3, 0x6f, 0x4d, 0x9f, 0xaf, 0x2c, 0xae,
  0xab, 0x61, 0xdb, 0x65, 0xb6, 0xb6, 0x2a, 0x78, 0xbd, 0x06, 0x3d, 0x3d,
  0x77, 0xd4, 0x3f, 0x05, 0x4c, 0xd3, 0x96, 0x4a, 0xe5, 0x80, 0x6c, 0xb6,
  0x40, 0xa1, 0x50, 0xc7, 0xeb, 0x15, 0x62, 0x31, 0x61, 0x60, 0x20, 0x4a,
  0x38, 0x5c, 0x91, 0xdd, 0xdd, 0x76, 0x75, 0xae, 0x80, 0xcf, 0x57, 0x97,
  0xf9, 0xf9, 0x0d, 0xe6, 0xe6, 0x2c, 0x82, 0x41, 0xc5, 0xc4, 0x44, 0x37,
  0x89, 0x44, 0x02, 0x91, 0x1f, 0x18, 0x86, 0xf0, 0x3b, 0x7c, 0x46, 0xc0,
  0xb6, 0xbf, 0xca, 0xcc, 0xcc, 0x67, 0x2c, 0xeb, 0x80, 0x64, 0xd2, 0xc3,
  0xe8, 0x68, 0x2f, 0xe1, 0xf0, 0x80, 0x72, 0x1c, 0x00, 0x3f, 0xae, 0xfb,
  0x17, 0x0f, 0xf2, 0xf9, 0x9c, 0x64, 0xe7, 0x4a, 0x04, 0xfc, 0x1a, 0x93,
  0x93, 0x7d, 0xf4, 0xf5, 0x5d, 0x53, 0x67, 0xc7, 0xcf, 0x11, 0xc8, 0xe7,
  0xd7, 0x64, 0x61, 0xe1, 0x3b, 0x83, 0xa9, 0x20, 0xe9, 0xf4, 0x75, 0x9a,
  0x4d, 0xdf, 0x29, 0x38, 0xac, 0xd6, 0x44, 0x73, 0x04, 0x6b, 0x7d, 0x95,
  0xda, 0x4e, 0x85, 0x50, 0x7b, 0x94, 0xee, 0xe1, 0x34, 0x5f, 0x1b, 0x09,
  0x65, 0x94, 0x4a, 0x39, 0xc9, 0x66, 0xbf, 0x91, 0x4c, 0x06, 0x19, 0x1b,
  0xeb, 0x3a, 0x05, 0x07, 0xdc, 0x05, 0xd9, 0x2f, 0x16, 0x59, 0x5a, 0x5a,
  0xa2, 0xb4, 0xd1, 0xc4, 0xda, 0x0f, 0x50, 0x6f, 0x18, 0xb4, 0x7b, 0x3e,
  0x71, 0x75, 0x3e, 0xc7, 0xed, 0xc7, 0x0f, 0xc4, 0x98, 0x9d, 0x9d, 0xc7,
  0x34, 0x03, 0xa4, 0x52, 0x09, 0x74, 0xbd, 0xf7, 0x04, 0xbe, 0xb0, 0xf1,
  0x42, 0x16, 0x3f, 0xac, 0x91, 0x2b, 0x18, 0x78, 0xc2, 0x31, 0xe2, 0x63,
  0x6d, 0xdc, 0x1c, 0xe9, 0xc7, 0x17, 0x08, 0x52, 0xdb, 0xb6, 0xc9, 0x3e,
  0x7f, 0x49, 0x7e, 0xe6, 0x15, 0x86, 0x65, 0xd9, 0x8c, 0x8f, 0xb7, 0x61,
  0x9a, 0xc9, 0x13, 0x58, 0xcf, 0x3f, 0x93, 0x77, 0xaf, 0x57, 0xd8, 0xb9,
  0x18, 0x65, 0xf0, 0x5e, 0x92, 0xc1, 0xf1, 0x1b, 0xb8, 0x44, 0x14, 0x40,
  0x03, 0xd0, 0xcd, 0x4d, 0xb1, 0x1b, 0x21, 0x76, 0xec, 0x6f, 0x67, 0xd7,
  0x98, 0x08, 0x94, 0xe5, 0xcd, 0xdb, 0x45, 0x0e, 0x82, 0x31, 0x26, 0x1f,
  0x3d, 0x04, 0x7f, 0x5c, 0xfd, 0x6e, 0xbe, 0x6e, 0xbd, 0x97, 0xcc, 0xf4,
  0x3a, 0x5e, 0xd1, 0xb8, 0x9c, 0x7e, 0x88, 0xd1, 0xd1, 0x11, 0xa1, 0x54,
  0x72, 0xb0, 0xac, 0x15, 0xe9, 0xe8, 0x18, 0x51, 0xf5, 0xba, 0xcd, 0x8f,
  0xea, 0x01, 0xa1, 0x78, 0x83, 0x20, 0x45, 0xcc, 0xe6, 0xb6, 0xb4, 0x9a,
  0x0d, 0xaa, 0xd5, 0x2a, 0x85, 0x8f, 0xab, 0x7c, 0x59, 0x2c, 0x72, 0xa8,
  0x5d, 0x62, 0xfc, 0xfe, 0x18, 0x46, 0xf7, 0x5d, 0xa5, 0xa6, 0xa6, 0x9e,
  0xc8, 0xf4, 0xf4, 0x17, 0xa2, 0x51, 0x97, 0x91, 0xe1, 0x5e, 0xa2, 0xa1,
  0x06, 0x9b, 0xb3, 0x4f, 0x29, 0xe7, 0xca, 0x38, 0xc5, 0x0b, 0x38, 0x7b,
  0xa0, 0xeb, 0x1a, 0x8e, 0x3f, 0x42, 0x35, 0x10, 0xa3, 0x2b, 0xd5, 0xc6,
  0xc8, 0xad, 0x21, 0x22, 0xf1, 0xb4, 0x02, 0x50, 0x99, 0x4c, 0x86, 0x5a,
  0xad, 0x20, 0xcb, 0xcb, 0x6b, 0x2c, 0x2f, 0x7b, 0xa8, 0x1f, 0x2a, 0xdc,
  0x9a, 0x8d, 0xb3, 0x5f, 0xa7, 0xbe, 0x27, 0xe8, 0x2d, 0xa1, 0x27, 0x2e,
  0xa4, 0x46, 0x4d, 0xae, 0x0c, 0xc5, 0x69, 0xef, 0x8a, 0xa0, 0x79, 0xfa,
  0x4f, 0xfc, 0x52, 0xc7, 0xdf, 0xe8, 0xf1, 0x6c, 0x8a, 0xeb, 0x7a, 0x68,
  0xb5, 0xe4, 0xa8, 0xd3, 0x82, 0x96, 0x80, 0xae, 0x0c, 0xfc, 0xc1, 0x10,
  0xd2, 0xda, 0xe1, 0xd0, 0xe9, 0x3c, 0x73, 0x5c, 0x27, 0x26, 0xba, 0xee,
  0xd1, 0x0a, 0x35, 0xed, 0x57, 0x41, 0x83, 0xe3, 0xb4, 0x76, 0x08, 0xd0,
  0xf9, 0xc7, 0x4b, 0xfc, 0x09, 0x52, 0xcb, 0x07, 0x62, 0x36, 0x43, 0x92,
  0xc6, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60,
  0x82
};

class CQExperimentDataValidator: public CQValidatorNotEmpty
{
public:
  enum Type
  {
    Name = 0,
    FirstRow,
    LastRow,
    HeaderRow
  };

  // Operations
public:
  CQExperimentDataValidator(QLineEdit * parent,
                            const char * name,
                            CQExperimentData * pContext,
                            const Type & type):
      CQValidatorNotEmpty(parent, name),
      mpIntValidator(new QIntValidator(1, std::numeric_limits< int >::max(), parent)),
      mpContext(pContext),
      mType(type)
  {}

  virtual State validate(QString & input, int & pos) const
  {
    if (mpContext->mShown == (unsigned int) - 1) return Acceptable;

    if (mType == Name)
      {
        if (input == "All")
          {
            setColor(Invalid);
            return Intermediate;
          }

        if (mLastAccepted != input &&
            mpContext->mpExperimentSetCopy->getParameter(TO_UTF8(input)))
          {
            setColor(Invalid);
            return Intermediate;
          }
      }
    else
      {
        if (mpIntValidator->validate(input, pos) != Acceptable)
          {
            setColor(Invalid);
            return Intermediate;
          }

        unsigned C_INT32 First, Last;

        switch (mType)
          {
            case FirstRow:

              if (!mpContext->mpFileInfo->validateFirst(mpContext->mShown, input.toULong()))
                {
                  unsigned C_INT32 NewFirst = input.toULong();

                  mpContext->mpFileInfo->getFirstUnusedSection(First, Last);

                  while (NewFirst > Last)
                    mpContext->mpFileInfo->getNextUnusedSection(First, Last);

                  if (First <= NewFirst && NewFirst <= Last)
                    {
                      if (First > mpContext->mpExperiment->getLastRow())
                        {
                          mpContext->mpExperiment->setLastRow(Last);
                          mpContext->mpExperiment->setFirstRow(First);
                        }
                      else
                        {
                          mpContext->mpExperiment->setFirstRow(First);
                          mpContext->mpExperiment->setLastRow(Last);
                        }

                      mpContext->syncExperiments();

                      mpContext->mpEditFirst->setText(QString::number(First));
                      mpContext->mpEditLast->setText(QString::number(Last));
                      mpContext->mpValidatorLast->revalidate();

                      return validate(input, pos);
                    }

                  setColor(Invalid);
                  return Intermediate;
                }

              mpContext->mpExperiment->setFirstRow(input.toULong());
              mpContext->mpFileInfo->sync();
              mpContext->mpBtnExperimentAdd->setEnabled(mpContext->mpFileInfo->getFirstUnusedSection(First, Last));
              break;

            case LastRow:

              if (!mpContext->mpFileInfo->validateLast(mpContext->mShown, input.toULong()))
                {
                  setColor(Invalid);
                  return Intermediate;
                }

              mpContext->mpExperiment->setLastRow(input.toULong());
              mpContext->mpFileInfo->sync();
              mpContext->mpBtnExperimentAdd->setEnabled(mpContext->mpFileInfo->getFirstUnusedSection(First, Last));
              break;

            case HeaderRow:

              if (!mpContext->mpFileInfo->validateHeader(mpContext->mShown, input.toULong()))
                {
                  setColor(Invalid);
                  return Intermediate;
                }

              mpContext->mpExperiment->setHeaderRow(input.toULong());
              break;

            default:
              break;
          }
      }

    return CQValidatorNotEmpty::validate(input, pos);
  }

  // virtual State revalidate();

  // virtual void forceAcceptance(const QString & input) const;

  // virtual void saved() const;

  // Attributes
private:
  QIntValidator * mpIntValidator;

  CQExperimentData * mpContext;

  Type mType;
};

void CQExperimentData::slotRevert()
{
  load(mpExperimentSet, mpDataModel);
}

void CQExperimentData::slotFirst()
{
  qWarning("CQExperimentData::slotFirst(): Not implemented yet");

  unsigned C_INT32 Row = C_INVALID_INDEX;

  if (mpEditFirst->text() != "")
    Row = mpEditFirst->text().toULong();

  if (Row == C_INVALID_INDEX)
    {
      //  Row = find first non used row in file
    }

  // display dialog with table showing file section of First row

  // if accept
  //  set mpEditFirst
}

void CQExperimentData::slotLast()
{
  unsigned C_INT32 Row = C_INVALID_INDEX;

  if (mpEditLast->text() != "")
    Row = mpEditLast->text().toULong();

  if (Row == C_INVALID_INDEX && mpEditFirst->text() != "")
    Row = mpEditFirst->text().toULong();

  // display dialog with table showing file section of First row

  // if accept
  //  set mpEditFirst
  // if last row
  //  display table showing file section of last row inexperiment
  // else if  first
  //  display table showing file section of  first row in file
  // else
  //  display table showing file section of last non used row in file

  // if accept
  //  set mpEditLast
}

void CQExperimentData::slotHeader()
{
  qWarning("CQExperimentData::slotHeader(): Not implemented yet");

  // if header row
  //  display table showing file section of header row inexperiment
  // if first row
  //  display table showing file section of first row inexperiment
  // else if last row
  //  display table showing file section of last row inexperiment
  // else
  //  display table showing file section of  first non used row in file

  // if accept
  //  set mpEditHeader
  //  check mpCheckHeader
  // else
  // uncheck mpCheckHeader
}

void CQExperimentData::slotExprimentType(bool isSteadyState)
{
  if (!mpExperiment) return;

  if (isSteadyState)
    mpBtnSteadystate->setFocus();
  else
    mpBtnTimeCourse->setFocus();

  saveTable(mpExperiment);

  unsigned C_INT32 i, imax = mpTable->numRows();

  if (isSteadyState)
    for (i = 0; i < imax; i++)
      {
        CExperiment::Type Type =
          static_cast<CExperiment::Type>(static_cast<QComboBox *>(mpTable->cellWidget(i, COL_TYPE))->currentItem());

        if (Type == CExperiment::time)
          mpExperiment->getObjectMap().setRole(i, CExperiment::ignore);
      };

  loadTable(mpExperiment, true);
  return;
}

void CQExperimentData::slotCheckTab(bool checked)
{
  mpEditSeparator->setEnabled(!checked);

  if (checked)
    mpCheckTab->setFocus();
  else
    mpEditSeparator->setFocus();

  if (mpEditSeparator->isEnabled() &&
      mpEditSeparator->text().isEmpty())
    mpEditSeparator->setText(",");
  else
    slotSeparator();
}

void CQExperimentData::slotCheckHeader(bool checked)
{mpEditHeader->setEnabled(checked);}

void CQExperimentData::slotExperimentAdd()
{
  mShowError = false;

  CExperiment Experiment(mpDataModel);
  CExperiment * pExperiment = mpExperimentSetCopy->addExperiment(Experiment);

  unsigned C_INT32 First, Last;
  mpFileInfo->getFirstUnusedSection(First, Last);
  pExperiment->setFirstRow(First);
  pExperiment->setLastRow(Last);
  pExperiment->setHeaderRow(First);
  pExperiment->setFileName(mpFileInfo->getFileName());

  pExperiment->setNumColumns(pExperiment->guessColumnNumber());
  mpFileInfo->sync();

  mpBoxExperiment->insertItem(FROM_UTF8(pExperiment->getObjectName()));
  mpBoxExperiment->setSelected(mpBoxExperiment->count() - 1, true);

  syncExperiments();
  mpBtnExperimentAdd->setEnabled(mpFileInfo->getFirstUnusedSection(First, Last));

  mShowError = true;
}

void CQExperimentData::slotExperimentChanged(Q3ListBoxItem * pItem)
{
  std::string Name;

  if (pItem != NULL)
    Name = TO_UTF8(pItem->text());

  CCopasiMessage::clearDeque();

  bool success = true;

  saveExperiment(mpExperiment, true);

  if (pItem != NULL)
    {
      mpExperiment = mpFileInfo->getExperiment(Name);
      mShown = mpBoxExperiment->currentItem();

      std::ifstream File;
      File.open(utf8ToLocale(mpExperiment->getFileName()).c_str());

      unsigned C_INT32 CurrentLine = 1;
      success &= mpExperiment->read(File, CurrentLine);

      if (success)
        success &= mpExperiment->compile();
    }
  else
    {
      mpExperiment = NULL;
      mShown = (unsigned int) - 1;
    }

  loadExperiment(mpExperiment);

  if (!success && CCopasiMessage::size() > 0 && mShowError)
    {
      CQMessageBox::information(this, "Specification Error", FROM_UTF8(CCopasiMessage::getAllMessageText()),
                                QMessageBox::Ok, QMessageBox::Ok);
      CCopasiMessage::clearDeque();
    }

  enableEdit(!mpCheckFrom->isChecked());
}

void CQExperimentData::slotExperimentDelete()
{
  // Get info from current selection
  unsigned C_INT32 index = mpBoxExperiment->currentItem();

  if (index == C_INVALID_INDEX) return;

  std::string key =
    mpFileInfo->getExperiment(TO_UTF8(mpBoxExperiment->item(index)->text()))->CCopasiParameter::getKey();

  // change selection
  if (mpBoxExperiment->count() > 1)
    {
      if (mpBoxExperiment->count() > index + 1)
        mpBoxExperiment->setSelected(index + 1, true);
      else
        mpBoxExperiment->setSelected(index - 1, true);
    }
  else
    slotExperimentChanged(NULL);

  // remove experiment
  mpExperimentSetCopy->removeExperiment(mpExperimentSetCopy->keyToIndex(key));
  syncExperiments();

  unsigned C_INT32 First, Last;
  mpBtnExperimentAdd->setEnabled(mpFileInfo->getFirstUnusedSection(First, Last));

  // We need to correct mpCheckFrom and mpCheckTo since the removal of the experiment
  // may have changed their status.
  disconnect(mpCheckTo, SIGNAL(toggled(bool)), this, SLOT(slotCheckTo(bool)));
  disconnect(mpCheckFrom, SIGNAL(toggled(bool)), this, SLOT(slotCheckFrom(bool)));

  mpCheckFrom->setChecked(isLikePreviousExperiment(mpExperiment));
  enableEdit(!mpCheckFrom->isChecked());

  if (mpExperiment)
    {
      unsigned C_INT32 Next =
        mpExperimentSetCopy->keyToIndex(mpExperiment->CCopasiParameter::getKey()) + 1;

      mpCheckTo->setChecked(isLikePreviousExperiment(mpExperimentSetCopy->getExperiment(Next)));
    }

  connect(mpCheckFrom, SIGNAL(toggled(bool)), this, SLOT(slotCheckFrom(bool)));
  connect(mpCheckTo, SIGNAL(toggled(bool)), this, SLOT(slotCheckTo(bool)));
}

void CQExperimentData::slotFileAdd()
{
  QString File =
    CopasiFileDialog::getOpenFileName(this,
                                      "Open File Dialog",
                                      "",
                                      "Data Files (*.txt *.csv);;All Files (*.*);;",
                                      "Open Data Files");

  if (File.isNull()) return;

  std::map<std::string, std::string>::const_iterator it = mFileMap.begin();
  std::map<std::string, std::string>::const_iterator end = mFileMap.end();
  unsigned C_INT32 i;

  for (; it != end; ++it)
    if (it->second == TO_UTF8(File))
      {
        for (i = 0; i < mpBoxFile->count(); i++)
          if (it->first == TO_UTF8(mpBoxFile->item(i)->text()))
            {
              mpBoxFile->setSelected(i, true);
              break;
            }

        return;
      }

  std::string FileName = CDirEntry::fileName(TO_UTF8(File));

  i = 0;

  while (mFileMap.find(FileName) != mFileMap.end())
    FileName = StringPrint("%s_%d", CDirEntry::fileName(TO_UTF8(File)).c_str(), i++);

  mFileMap[FileName] = TO_UTF8(File);
  mpBoxFile->insertItem(FROM_UTF8(FileName));

  mpBoxFile->setSelected(mpBoxFile->count() - 1, true);

  unsigned C_INT32 First, Last;

  if (mpFileInfo->getFirstUnusedSection(First, Last))
    {
      do
        {
          slotExperimentAdd();
        }
      while (mpBtnExperimentAdd->isEnabled());

      mpBoxExperiment->setSelected(0, true);
    }
}

void CQExperimentData::slotFileChanged(Q3ListBoxItem * pItem)
{
  if (pItem)
    {
      slotExperimentChanged(NULL); // Assure that changes are saved.
      mpBoxExperiment->clear();

      if (mpFileInfo->setFileName(mFileMap[TO_UTF8(pItem->text())]))
        {
          // fill experiment list box

          std::vector< std::string > ExperimentNames = mpFileInfo->getExperimentNames();
          std::vector< std::string >::const_iterator it = ExperimentNames.begin();
          std::vector< std::string >::const_iterator end = ExperimentNames.end();

          for (; it != end; ++it)
            mpBoxExperiment->insertItem(FROM_UTF8((*it)));
        }

      if (mpBoxExperiment->count())
        mpBoxExperiment->setSelected(0, true);
      else
        slotExperimentChanged(NULL);
    }
  else
    {
      mpBoxExperiment->clear();
      slotExperimentChanged(NULL);
    }

  unsigned C_INT32 First, Last;
  mpBtnExperimentAdd->setEnabled(mpFileInfo->getFirstUnusedSection(First, Last));
}

void CQExperimentData::slotFileDelete()
{
  // Get info from current selection
  unsigned C_INT32 index = mpBoxFile->currentItem();

  if (index == C_INVALID_INDEX) return;

  std::string FileName = mFileMap[TO_UTF8(mpBoxFile->item(index)->text())];

  // change selection
  if (mpBoxFile->count() > 1)
    {
      if (mpBoxFile->count() > index + 1)
        mpBoxFile->setSelected(index + 1, true);
      else
        mpBoxFile->setSelected(index - 1, true);
    }
  else
    slotFileChanged(NULL);

  // remove file
  mFileMap.erase(TO_UTF8(mpBoxFile->item(index)->text()));
  mpBoxFile->removeItem(index);

  // delete all experiments in current file.
  unsigned C_INT32 i = mpExperimentSetCopy->getExperimentCount() - 1;

  for (; i < C_INVALID_INDEX; i--)
    if (mpExperimentSetCopy->getExperiment(i)->getFileName() == FileName)
      mpExperimentSetCopy->removeExperiment(i);
}

void CQExperimentData::slotCancel()
{
  pdelete(mpExperimentSetCopy);
  reject();
}

void CQExperimentData::slotOK()
{
  // Force the save all current changes.
  slotExperimentChanged(NULL);

  CExperiment * pExperiment;

  unsigned C_INT32 i = mpExperimentSet->getExperimentCount() - 1;

  for (; i < C_INVALID_INDEX; i--)
    {
      pExperiment =
        dynamic_cast<CExperiment *>(CCopasiRootContainer::getKeyFactory()->get(mKeyMap[mpExperimentSet->getExperiment(i)->CCopasiParameter::getKey()]));

      if (pExperiment)
        {
          *mpExperimentSet->getExperiment(i) = *pExperiment;
          mpExperimentSetCopy->removeParameter(pExperiment->getObjectName());
        }
      else
        mpExperimentSet->removeExperiment(i);
    }

  emit experimentChanged();

  for (i = 0; i < mpExperimentSetCopy->getExperimentCount(); i++)
    mpExperimentSet->addExperiment(*mpExperimentSetCopy->getExperiment(i));


  pdelete(mpExperimentSetCopy);
  accept();
}

bool CQExperimentData::load(CExperimentSet * pExperimentSet, CCopasiDataModel * pDataModel)
{
  mpDataModel = pDataModel;


  if (mCrossValidation)
    {
      setCaption("Cross Validation Data");
      mpLblWeight->show();
      mpEditWeight->show();
      mpLblThreshold->show();
      mpEditThreshold->show();
      mpLineCrossValidation->show();

    }
  else
    {
      mpLblWeight->hide();
      mpEditWeight->hide();
      mpLblThreshold->hide();
      mpEditThreshold->hide();
      mpLineCrossValidation->hide();
    }

  if (!pExperimentSet) return false;

  mpExperiment = NULL;
  mShown = (unsigned int) - 1;

  mpExperimentSet = pExperimentSet;

  pdelete(mpExperimentSetCopy);

  mpExperimentSetCopy = new CExperimentSet(*pExperimentSet);


  pdelete(mpFileInfo);
  mpFileInfo = new CExperimentFileInfo(*mpExperimentSetCopy);

  // Build the key map so that we are able to update the correct experiments
  // on OK.
  mKeyMap.clear();
  unsigned C_INT32 i, imax = mpExperimentSet->getExperimentCount();

  for (i = 0; i < imax; i++)
    mKeyMap[mpExperimentSet->getExperiment(i)->CCopasiParameter::getKey()] =
      mpExperimentSetCopy->getExperiment(i)->CCopasiParameter::getKey();

  // fill file list box
  mpBoxFile->clear();

  std::vector< std::string > FileNames = mpExperimentSetCopy->getFileNames();
  std::vector< std::string >::const_iterator it = FileNames.begin();
  std::vector< std::string >::const_iterator end = FileNames.end();

  std::string FileName;
  i = 0;

  mFileMap.clear();

  for (; it != end; ++it)
    {
      FileName = CDirEntry::fileName(*it);

      while (mFileMap.find(FileName) != mFileMap.end())
        FileName = StringPrint("%s_%d", CDirEntry::fileName(*it).c_str(), i++);

      mFileMap[FileName] = *it;
      mpBoxFile->insertItem(FROM_UTF8(FileName));
    }

  if (mpBoxFile->count())
    mpBoxFile->setSelected(0, true); // This tiggers the rest of the update :)
  else
    slotFileChanged(NULL);

  return true;
}

void CQExperimentData::init()
{
  QImage copasi;
  copasi.loadFromData(copasi_data, sizeof(copasi_data), "PNG");
  mCopasi = copasi;

  mpComboMap = NULL;
  mpBtnMap = NULL;

  mpTable->setColumnReadOnly(COL_NAME, true);
  mpTable->hideColumn(COL_TYPE_HIDDEN);
  mpTable->setColumnWidth(COL_BTN, 20);
  mpTable->horizontalHeader()->setLabel(COL_BTN, " ");
  mpTable->setColumnStretchable(COL_OBJECT, true);
  mpTable->setColumnReadOnly(COL_OBJECT, true);
  mpTable->hideColumn(COL_OBJECT_HIDDEN);

  const std::string * pWeightMethod = CExperiment::WeightMethodName;

  while (*pWeightMethod != "")
    mpBoxWeightMethod->insertItem(FROM_UTF8(*pWeightMethod++));

  mpExperimentSetCopy = NULL;
  mpFileInfo = NULL;
  mpExperiment = NULL;

  mpValidatorName = new CQExperimentDataValidator(mpEditName, 0, this, CQExperimentDataValidator::Name);
  mpEditName->setValidator(mpValidatorName);
  mpValidatorFirst = new CQExperimentDataValidator(mpEditFirst, 0, this, CQExperimentDataValidator::FirstRow);
  mpEditFirst->setValidator(mpValidatorFirst);
  mpValidatorLast = new CQExperimentDataValidator(mpEditLast, 0, this, CQExperimentDataValidator::LastRow);
  mpEditLast->setValidator(mpValidatorLast);
  mpValidatorHeader = new CQExperimentDataValidator(mpEditHeader, 0, this, CQExperimentDataValidator::HeaderRow);
  mpEditHeader->setValidator(mpValidatorHeader);

  mShown = (unsigned int) - 1;
  mCrossValidation = false;
  mShowError = true;

  mpDataModel = NULL;
}

void CQExperimentData::destroy()
{
  pdelete(mpComboMap);
  pdelete(mpBtnMap);

  pdelete(mpExperimentSetCopy);
  pdelete(mpFileInfo);
}

bool CQExperimentData::loadExperiment(CExperiment * pExperiment)
{
  // Temporarily diconnect signals
  disconnect(mpCheckTo, SIGNAL(toggled(bool)), this, SLOT(slotCheckTo(bool)));
  disconnect(mpCheckFrom, SIGNAL(toggled(bool)), this, SLOT(slotCheckFrom(bool)));
  disconnect(mpBtnSteadystate, SIGNAL(toggled(bool)), this, SLOT(slotExprimentType(bool)));

  if (!pExperiment)
    {
      mpEditName->setText("");
      mpEditSeparator->setText("");
      mpCheckTab->setChecked(true);
      mpEditFirst->setText("");
      mpEditLast->setText("");
      mpEditHeader->setText("");
      mpCheckHeader->setChecked(false);
      mpBtnTimeCourse->setChecked(true);
      mpCheckFrom->setChecked(false);
      mpCheckTo->setChecked(false);
      mpBoxWeightMethod->setCurrentItem(CExperiment::SD);
    }
  else
    {
      mpEditName->setText(FROM_UTF8(pExperiment->getObjectName()));

      if (pExperiment->getSeparator() == "\t")
        {
          mpEditSeparator->setText("");
          mpCheckTab->setChecked(true);
        }
      else
        {
          mpEditSeparator->setText(FROM_UTF8(pExperiment->getSeparator()));
          mpCheckTab->setChecked(false);
        }

      QString Row = (pExperiment->getFirstRow() == C_INVALID_INDEX) ?
                    "" : QString::number(pExperiment->getFirstRow());
      mpEditFirst->setText(Row);
      Row = (pExperiment->getLastRow() == C_INVALID_INDEX) ?
            "" : QString::number(pExperiment->getLastRow());
      mpEditLast->setText(Row);

      if (pExperiment->getHeaderRow() == C_INVALID_INDEX)
        {
          mpEditHeader->setText("");
          mpCheckHeader->setChecked(false);
        }
      else
        {
          mpEditHeader->setText(QString::number(pExperiment->getHeaderRow()));
          mpCheckHeader->setChecked(true);
        }

      if (pExperiment->getExperimentType() == CCopasiTask::timeCourse)
        mpBtnTimeCourse->setChecked(true);
      else
        mpBtnSteadystate->setChecked(true);

      mOldWeightMethod = pExperiment->getWeightMethod();
      mpBoxWeightMethod->setCurrentItem(mOldWeightMethod);

      unsigned C_INT32 Next =
        mpExperimentSetCopy->keyToIndex(pExperiment->CCopasiParameter::getKey()) + 1;

      mpCheckFrom->setChecked(isLikePreviousExperiment(pExperiment));

      if (Next < mpExperimentSetCopy->getExperimentCount())
        mpCheckTo->setChecked(isLikePreviousExperiment(mpExperimentSetCopy->getExperiment(Next)));
      else
        mpCheckTo->setChecked(false);
    }

  mpValidatorName->saved();
  mpValidatorFirst->saved();
  mpValidatorLast->saved();
  mpValidatorHeader->saved();

  loadTable(pExperiment, false);

  // Reconnect signals
  connect(mpBtnSteadystate, SIGNAL(toggled(bool)), this, SLOT(slotExprimentType(bool)));
  connect(mpCheckFrom, SIGNAL(toggled(bool)), this, SLOT(slotCheckFrom(bool)));
  connect(mpCheckTo, SIGNAL(toggled(bool)), this, SLOT(slotCheckTo(bool)));

  return true;
}

bool CQExperimentData::saveExperiment(CExperiment * pExperiment, const bool & full)
{
  if (!pExperiment) return false;

  bool success = true;

  unsigned C_INT32 Next =
    mpExperimentSetCopy->keyToIndex(pExperiment->CCopasiParameter::getKey()) + 1;

  if (Next < mpExperimentSetCopy->getExperimentCount() && mpCheckTo->isChecked())
    {
      CExperiment * pNext = mpExperimentSetCopy->getExperiment(Next);

      if (isLikePreviousExperiment(pNext))
        success &= saveExperiment(pNext, false);
    }

  QString value = mpEditName->text();
  int pos = value.length();

  if (full &&
      pExperiment->getObjectName() != (const char *) value &&
      mpValidatorName->validate(value, pos) == QValidator::Acceptable)
    {
      int current = mpBoxExperiment->currentItem();
      disconnect(mpBoxExperiment, SIGNAL(currentChanged(Q3ListBoxItem*)),
                 this, SLOT(slotExperimentChanged(Q3ListBoxItem*)));
      mpBoxExperiment->changeItem(value, mShown);
      mpBoxExperiment->setSelected(current, true);
      connect(mpBoxExperiment, SIGNAL(currentChanged(Q3ListBoxItem*)),
              this, SLOT(slotExperimentChanged(Q3ListBoxItem*)));
      pExperiment->setObjectName((const char *) value);
    }

  if (mpCheckTab->isChecked())
    pExperiment->setSeparator("\t");
  else
    pExperiment->setSeparator(TO_UTF8(mpEditSeparator->text()));

  value = mpEditFirst->text();
  pos = value.length();

  if (full &&
      mpValidatorFirst->validate(value, pos) == QValidator::Acceptable)
    pExperiment->setFirstRow(value.toULong());

  value = mpEditLast->text();
  pos = value.length();

  if (full &&
      mpValidatorLast->validate(value, pos) == QValidator::Acceptable)
    pExperiment->setLastRow(value.toULong());

  value = mpEditHeader->text();
  pos = value.length();

  if (mpCheckHeader->isChecked() &&
      mpValidatorHeader->validate(value, pos) == QValidator::Acceptable)
    pExperiment->setHeaderRow(value.toULong());
  else
    {
      pExperiment->setHeaderRow(C_INVALID_INDEX);
      mpCheckHeader->setChecked(false);
    }

  if (mpBtnTimeCourse->isChecked())
    pExperiment->setExperimentType(CCopasiTask::timeCourse);
  else
    pExperiment->setExperimentType(CCopasiTask::steadyState);

  pExperiment->setWeightMethod((CExperiment::WeightMethod) mpBoxWeightMethod->currentItem());

  mpFileInfo->sync();

  unsigned C_INT32 First, Last;
  mpBtnExperimentAdd->setEnabled(mpFileInfo->getFirstUnusedSection(First, Last));

  mpValidatorName->saved();
  mpValidatorFirst->saved();
  mpValidatorLast->saved();
  mpValidatorHeader->saved();

  saveTable(pExperiment);

  return success;
}

void CQExperimentData::syncExperiments()
{
  std::string Current = TO_UTF8(mpBoxExperiment->currentText());
  std::string Shown;

  if (mShown != (unsigned int) - 1)
    Shown = TO_UTF8(mpBoxExperiment->item(mShown)->text());

  mpFileInfo->sync();

  mpBoxExperiment->clear();

  std::vector< std::string > ExperimentNames = mpFileInfo->getExperimentNames();
  std::vector< std::string >::const_iterator it = ExperimentNames.begin();
  std::vector< std::string >::const_iterator end = ExperimentNames.end();

  unsigned C_INT32 i;

  for (i = 0; it != end; ++it, i++)
    {
      mpBoxExperiment->insertItem(FROM_UTF8((*it)));

      if (*it == Current)
        {
          disconnect(mpBoxExperiment, SIGNAL(currentChanged(Q3ListBoxItem*)),
                     this, SLOT(slotExperimentChanged(Q3ListBoxItem*)));
          mpBoxExperiment->setSelected(mpBoxExperiment->count() - 1, true);
          connect(mpBoxExperiment, SIGNAL(currentChanged(Q3ListBoxItem*)),
                  this, SLOT(slotExperimentChanged(Q3ListBoxItem*)));
        }

      if (*it == Shown) mShown = i;
    }

  return;
}

void CQExperimentData::slotUpdateTable()
{loadTable(mpExperiment, true);}

void CQExperimentData::slotModelObject(int row)
{
  // :TODO: Implement object browser and update of column 'Model Object'.

  CCopasiSimpleSelectionTree::ObjectClasses Classes;
  CExperiment::Type Type =
    static_cast<CExperiment::Type>(static_cast<QComboBox *>(mpTable->cellWidget(row, COL_TYPE))->currentItem());

  if (Type == CExperiment::independent)
    Classes =
      CCopasiSimpleSelectionTree::InitialTime |
      CCopasiSimpleSelectionTree::Parameters;
  else
    Classes =
      CCopasiSimpleSelectionTree::Variables |
      CCopasiSimpleSelectionTree::ObservedValues |
      CCopasiSimpleSelectionTree::ObservedConstants;

  const CCopasiObject * pObject =
    CCopasiSelectionDialog::getObjectSingle(this, Classes);

  if (pObject)
    {
      mpTable->setText(row, COL_OBJECT, FROM_UTF8(pObject->getObjectDisplayName()));
      mpTable->setText(row, COL_OBJECT_HIDDEN, FROM_UTF8(pObject->getCN()));
    }
}

void CQExperimentData::loadTable(CExperiment * pExperiment, const bool & guess)
{
  if (!pExperiment)
    {
      mpTable->setNumRows(0);
      mpTable->setNumRows(3);

      pdelete(mpComboMap);
      pdelete(mpBtnMap);

      return;
    }

  unsigned C_INT32 TimeRow = C_INVALID_INDEX;

  pdelete(mpComboMap);
  mpComboMap = new QSignalMapper(this);
  connect(mpComboMap, SIGNAL(mapped(int)), this, SLOT(slotTypeChanged(int)));

  pdelete(mpBtnMap);
  mpBtnMap = new QSignalMapper(this);
  connect(mpBtnMap, SIGNAL(mapped(int)), this, SLOT(slotModelObject(int)));

  pExperiment->readColumnNames();
  const std::vector<std::string> & ColumnNames = pExperiment->getColumnNames();

  QStringList ColumnTypes;
  const std::string * pTmp = CExperiment::TypeName;

  while (*pTmp != "")
    {
      ColumnTypes.push_back(FROM_UTF8(*pTmp));
      pTmp++;
    }

  // This assumes that time is always the last type.
  if (mpBtnSteadystate->isChecked())
    ColumnTypes.pop_back();

  unsigned C_INT32 i, imax = ColumnNames.size();
  mpTable->setNumRows(imax);

  CExperimentObjectMap & ObjectMap = pExperiment->getObjectMap();

  QComboBox * pComboBox;
  QToolButton* pBtn;
  const CCopasiObject * pObject;
  CExperiment::Type Type;

  for (i = 0; i < imax; i++)
    {
      // COL_NAME
      mpTable->setText(i, COL_NAME, FROM_UTF8(ColumnNames[i]));

      // COL_TYPE
      pComboBox = new QComboBox(mpTable);
      pComboBox->insertStringList(ColumnTypes);
      pComboBox->setEditable(false);

      if (guess && TimeRow == C_INVALID_INDEX &&
          mpBtnTimeCourse->isChecked() &&
          mpTable->text(i, COL_NAME).contains("time", false))
        ObjectMap.setRole(i, CExperiment::time);

      Type = ObjectMap.getRole(i);

      if (Type == CExperiment::time) TimeRow = i;

      pComboBox->setCurrentItem(Type);

      mpComboMap->setMapping(pComboBox, i);
      connect(pComboBox, SIGNAL(activated(int)), mpComboMap, SLOT(map()));

      mpTable->setCellWidget(i, COL_TYPE, pComboBox);

      // COL_TYPE_HIDDEN
      mpTable->setText(i, COL_TYPE_HIDDEN, QString::number(pComboBox->currentItem()));

      // COL_BTN
      pBtn = new QToolButton(mpTable);
      pBtn->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, pBtn->sizePolicy().hasHeightForWidth()));
      pBtn->setMaximumSize(QSize(20, 20));
      pBtn->setIconSet(QIcon(mCopasi));

      if (Type == CExperiment::ignore || Type == CExperiment::time)
        pBtn->setEnabled(false);

      mpBtnMap->setMapping(pBtn, i);
      connect(pBtn, SIGNAL(clicked()), mpBtnMap, SLOT(map()));

      mpTable->setCellWidget(i, COL_BTN, pBtn);

      // COL_OBJECT and COL_OBJECT_HIDDEN
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
      assert(pDataModel != NULL);

      if (ObjectMap.getObjectCN(i) != "")
        {
          pObject = pDataModel->getObject(ObjectMap.getObjectCN(i));

          if (pObject)
            mpTable->setText(i, COL_OBJECT, FROM_UTF8(pObject->getObjectDisplayName()));
          else
            mpTable->setText(i, COL_OBJECT, "not found");

          mpTable->setText(i, COL_OBJECT_HIDDEN, FROM_UTF8(ObjectMap.getObjectCN(i)));
        }
      else
        {
          mpTable->setText(i, COL_OBJECT, "");
          mpTable->setText(i, COL_OBJECT_HIDDEN, "");
        }

      if (Type != CExperiment::dependent)
        mpTable->setText(i, COL_WEIGHT, "");
      else
        {
          C_FLOAT64 DefaultWeight = ObjectMap.getDefaultWeight(i);
          C_FLOAT64 Weight = ObjectMap.getWeight(i);

          QString WeightText;

          if ((isnan(DefaultWeight) &&
               isnan(Weight)) ||
              DefaultWeight == Weight)
            WeightText = "(" + QString::number(DefaultWeight) + ")";
          else
            WeightText = QString::number(Weight);

          mpTable->setText(i, COL_WEIGHT, WeightText);
        }
    }

  if (TimeRow != C_INVALID_INDEX)
    for (i = 0; i < imax; i++)
      if (i != TimeRow)
        static_cast<QComboBox *>(mpTable->cellWidget(i, COL_TYPE))->removeItem(CExperiment::time);
}

void CQExperimentData::slotTypeChanged(int row)
{
  CExperiment::Type NewType =
    static_cast<CExperiment::Type>(static_cast<QComboBox *>(mpTable->cellWidget(row, COL_TYPE))->currentItem());
  CExperiment::Type OldType =
    static_cast<CExperiment::Type>(mpTable->text(row, COL_TYPE_HIDDEN).toLong());

  if (OldType == NewType) return;

  bool BtnEnabled = true;
  C_INT32 i, imax = mpTable->numRows();

  CCopasiObjectName CN = CCopasiObjectName(TO_UTF8(mpTable->text(row, COL_OBJECT_HIDDEN)));
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  switch (NewType)
    {
      case CExperiment::ignore:
        BtnEnabled = false;
        break;

      case CExperiment::independent:

        if (!CCopasiSimpleSelectionTree::filter(CCopasiSimpleSelectionTree::InitialTime |
                                                CCopasiSimpleSelectionTree::Parameters,
                                                pDataModel->getObject(CN)))
          slotModelObject(row);

        BtnEnabled = true;
        break;

      case CExperiment::dependent:

        if (!CCopasiSimpleSelectionTree::filter(CCopasiSimpleSelectionTree::Variables |
                                                CCopasiSimpleSelectionTree::ObservedValues,
                                                pDataModel->getObject(CN)))
          slotModelObject(row);

        BtnEnabled = true;
        break;

      case CExperiment::time:
        BtnEnabled = false;

        // Remove Time from combo items
        for (i = 0; i < imax; i++)
          if (i != row)
            static_cast<QComboBox *>(mpTable->cellWidget(i, COL_TYPE))->removeItem(CExperiment::time);

        break;
    }

  static_cast<QToolButton *>(mpTable->cellWidget(row, COL_BTN))->setEnabled(BtnEnabled);

  switch (OldType)
    {
      case CExperiment::ignore:
      case CExperiment::independent:
      case CExperiment::dependent:
        break;

      case CExperiment::time:

        // Add time to combo items
        for (i = 0; i < imax; i++)
          if (i != row)
            static_cast<QComboBox *>(mpTable->cellWidget(i, COL_TYPE))->insertItem(FROM_UTF8(CExperiment::TypeName[CExperiment::time]));

        break;
    }

  mpTable->setText(row, COL_TYPE_HIDDEN, QString::number(NewType));

  // The default weights need to be recalculated and the table updated if the type change
  // involves dependent values.
  if (OldType == CExperiment::dependent ||
      NewType == CExperiment::dependent)
    {
      saveExperiment(mpExperiment, true);

      // Since the iterpretation of the data has changed we need read the file again
      std::ifstream File;
      File.open(utf8ToLocale(mpExperiment->getFileName()).c_str());

      unsigned C_INT32 CurrentLine = 1;
      mpExperiment->read(File, CurrentLine);
      mpExperiment->compile();

      // We can not simply use loadTable as this would destroy the two signal maps
      // for the buttons and comboboxes leading to crashes in Qt.
      CExperimentObjectMap & ObjectMap = mpExperiment->getObjectMap();

      for (i = 0; i < imax; i++)
        {
          // COL_WEIGHT
          if (ObjectMap.getRole(i) != CExperiment::dependent)
            mpTable->setText(i, COL_WEIGHT, "");
          else
            {
              QString WeightText = mpTable->text(i, COL_WEIGHT);

              // Keep non default values
              if (WeightText == "" || WeightText[0] == '(')
                {

                  C_FLOAT64 DefaultWeight = ObjectMap.getDefaultWeight(i);
                  WeightText = "(" + QString::number(DefaultWeight) + ")";

                  mpTable->setText(i, COL_WEIGHT, WeightText);
                }
            }
        }
    }

  return;
}

void CQExperimentData::slotSeparator()
{
  if (!mpExperiment) return;

  //  saveTable(mpExperiment);

  if (mpCheckTab->isChecked())
    mpExperiment->setSeparator("\t");
  else
    mpExperiment->setSeparator(TO_UTF8(mpEditSeparator->text()));

  mpExperiment->setNumColumns(mpExperiment->guessColumnNumber());
  mpExperiment->readColumnNames();

  loadTable(mpExperiment, true);
}

bool CQExperimentData::saveTable(CExperiment * pExperiment)
{
  CExperimentObjectMap & ObjectMap = pExperiment->getObjectMap();
  CExperimentObjectMap & MasterObjectMap = mpExperiment->getObjectMap();
  unsigned C_INT32 i, imax = mpTable->numRows();
  bool FoundTime = false;
  bool Changed = false;

  ObjectMap.setNumCols(imax);

  for (i = 0; i < imax; i++)
    {
      CExperiment::Type Type =
        static_cast<CExperiment::Type>(static_cast<QComboBox *>(mpTable->cellWidget(i, COL_TYPE))->currentItem());

      if (Type == CExperiment::time)
        FoundTime = true;

      if (ObjectMap.getRole(i) != Type)
        {
          ObjectMap.setRole(i, Type);
          Changed = true;
        }

      if (ObjectMap.getObjectCN(i) != TO_UTF8(mpTable->text(i, COL_OBJECT_HIDDEN)))
        {
          ObjectMap.setObjectCN(i, TO_UTF8(mpTable->text(i, COL_OBJECT_HIDDEN)));
          Changed = true;
        }

      QString WeightText = mpTable->text(i, COL_WEIGHT);

      // Empty fields are treated as default.
      if (WeightText == "")
        WeightText = QString::number(std::numeric_limits<C_FLOAT64>::quiet_NaN());

      if (Type == CExperiment::dependent &&
          WeightText[0] != '(' &&
          QString::number(MasterObjectMap.getWeight(i)) != WeightText)
        {
          ObjectMap.setWeight(i, WeightText.toDouble());
          Changed = true;
        }
    }

  pExperiment->updateFittedPoints();

  if (!FoundTime &&
      pExperiment->getExperimentType() == CCopasiTask::timeCourse)
    {
      CCopasiMessage(CCopasiMessage::WARNING, MCFitting + 3);

      CQMessageBox::information(this, "Specification Error", FROM_UTF8(CCopasiMessage::getAllMessageText()),
                                QMessageBox::Ok, QMessageBox::Ok);
      CCopasiMessage::clearDeque();
    }

  return Changed;
}

void CQExperimentData::slotCheckFrom(bool checked)
{
  mpCheckFrom->setFocus();

  unsigned C_INT32 Current = this->mpBoxExperiment->currentItem();

  if (checked && Current && Current != C_INVALID_INDEX)
    {
      // Load the information from the previous experiment
      CExperiment * pPrevious =
        mpFileInfo->getExperiment(TO_UTF8(mpBoxExperiment->text(Current - 1)));

      unsigned C_INT32 OldWeightMethod = mOldWeightMethod;
      loadExperiment(pPrevious);
      mOldWeightMethod = OldWeightMethod;

      // Load the experiment individual information.
      mpEditName->setText(FROM_UTF8(mpExperiment->getObjectName()));
      QString Row = (mpExperiment->getFirstRow() == C_INVALID_INDEX) ?
                    "" : QString::number(mpExperiment->getFirstRow());
      mpEditFirst->setText(Row);
      Row = (mpExperiment->getLastRow() == C_INVALID_INDEX) ?
            "" : QString::number(mpExperiment->getLastRow());
      mpEditLast->setText(Row);

      mpValidatorName->saved();
      mpValidatorFirst->saved();
      mpValidatorLast->saved();
    }
  else
    {
      loadExperiment(mpExperiment);
    }

  // loadExperiment determines the status of mpCheckFrom and may have overwritten
  // the desired setting. We correct that here.
  disconnect(mpCheckFrom, SIGNAL(toggled(bool)), this, SLOT(slotCheckFrom(bool)));
  mpCheckFrom->setChecked(checked);
  connect(mpCheckFrom, SIGNAL(toggled(bool)), this, SLOT(slotCheckFrom(bool)));

  enableEdit(!checked);
}

bool CQExperimentData::isLikePreviousExperiment(CExperiment * pExperiment)
{
  if (!pExperiment) return false;

  unsigned C_INT32 Previous =
    mpExperimentSetCopy->keyToIndex(pExperiment->CCopasiParameter::getKey()) - 1;

  if (Previous == C_INVALID_INDEX) return false;

  CExperiment * pPrevious = mpExperimentSetCopy->getExperiment(Previous);

  if (pExperiment->getSeparator() != pPrevious->getSeparator()) return false;

  if (pExperiment->getHeaderRow() != pPrevious->getHeaderRow()) return false;

  if (pExperiment->getExperimentType() != pPrevious->getExperimentType()) return false;

  if (mpExperiment != pExperiment)
    {
      if (pExperiment->getWeightMethod() != (CExperiment::WeightMethod) mOldWeightMethod) return false;
    }
  else
    {
      if ((CExperiment::WeightMethod) mOldWeightMethod != pPrevious->getWeightMethod()) return false;
    }

  if (!(pExperiment->getObjectMap() == pPrevious->getObjectMap())) return false;

  return true;
}

void CQExperimentData::slotCheckTo(bool checked)
{
  mpCheckTo->setFocus();

  if (!checked || !mpExperiment) return;

  unsigned C_INT32 Next =
    mpExperimentSetCopy->keyToIndex(mpExperiment->CCopasiParameter::getKey()) + 1;

  if (Next < mpExperimentSetCopy->getExperimentCount())
    {
      CExperiment * pNext = mpExperimentSetCopy->getExperiment(Next);
      unsigned C_INT32 OldWeightMethod = mOldWeightMethod;
      mOldWeightMethod = pNext->getWeightMethod();
      saveExperiment(mpExperimentSetCopy->getExperiment(Next), false);
      mOldWeightMethod = OldWeightMethod;
    }
}

void CQExperimentData::enableEdit(const bool & enable)
{
  if (enable)
    {
      mpBtnSteadystate->setEnabled(true);
      mpBtnTimeCourse->setEnabled(true);

      if (mpCheckHeader->isChecked()) mpEditHeader->setEnabled(true);

      mpCheckHeader->setEnabled(true);

      if (!mpCheckTab->isChecked()) mpEditSeparator->setEnabled(true);

      mpCheckTab->setEnabled(true);
      mpTable->setEnabled(true);
      mpBoxWeightMethod->setEnabled(true);

      // We need to enable all items in COL_TYPE and some in COL_BTN
      // Disable is inheritted but enable not.
      if (mpExperiment)
        {
          unsigned C_INT32 i, imax = mpTable->numRows();

          for (i = 0; i < imax; i++)
            {
              mpTable->cellWidget(i, COL_TYPE)->setEnabled(true);

              CExperiment::Type Type =
                static_cast<CExperiment::Type>(static_cast<QComboBox *>(mpTable->cellWidget(i, COL_TYPE))->currentItem());

              if (Type == CExperiment::ignore || Type == CExperiment::time) continue;

              mpTable->cellWidget(i, COL_BTN)->setEnabled(true);
            }
        }
    }
  else
    {
      mpBtnSteadystate->setEnabled(false);
      mpBtnTimeCourse->setEnabled(false);
      mpEditHeader->setEnabled(false);
      mpCheckHeader->setEnabled(false);
      mpEditSeparator->setEnabled(false);
      mpCheckTab->setEnabled(false);
      mpTable->setEnabled(false);
      mpBoxWeightMethod->setEnabled(false);
    }
}

void CQExperimentData::slotWeightMethod(int weightMethod)
{
  if (mpExperiment == NULL) return;

  if ((CExperiment::WeightMethod) weightMethod ==
      mpExperiment->getWeightMethod()) return;

  unsigned C_INT32 Current =
    mpExperimentSetCopy->keyToIndex(mpExperiment->CCopasiParameter::getKey());
  unsigned C_INT32 Next = Current + 1;

  // Find all experiments which are like this.
  while (Next < mpExperimentSetCopy->getExperimentCount() && mpCheckTo->isChecked())
    {
      CExperiment * pNext = mpExperimentSetCopy->getExperiment(Next);

      if (!isLikePreviousExperiment(pNext)) break;

      Next++;
    }

  // Update each of them.
  while (true)
    {
      Next--;

      CExperiment * pNext = mpExperimentSetCopy->getExperiment(Next);

      bool Changed = saveTable(pNext);

      if (Changed)
        {
          std::ifstream File;
          File.open(utf8ToLocale(pNext->getFileName()).c_str());

          unsigned C_INT32 CurrentLine = 1;
          pNext->read(File, CurrentLine);
          pNext->compile();
        }

      pNext->setWeightMethod((CExperiment::WeightMethod) weightMethod);
      pNext->calculateWeights();

      if (Next == Current) break;
    }

  loadTable(mpExperiment, false);
}
