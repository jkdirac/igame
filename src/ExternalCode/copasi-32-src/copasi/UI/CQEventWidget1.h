// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/UI/CQEventWidget1.h,v $
//   $Revision: 1.11.2.2 $
//   $Name: Build-31 $
//   $Author: shoops $
//   $Date: 2010/07/07 21:07:26 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQEVENTWIDGET1_H
#define CQEVENTWIDGET1_H

#include <qvariant.h>

#include "ui_CQEventWidget1.h"

#include "copasi/model/CEvent.h"
#include "copasi/utilities/CCopasiVector.h"

class CQExpressionWidget;
class CCompartment;
class CExpression;

class CQEventWidget1 : public CopasiWidget, public Ui::CQEventWidget1
{
  Q_OBJECT

public:
  CQEventWidget1(QWidget* parent = 0, const char* name = 0);
  ~CQEventWidget1();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();

protected:
  virtual bool enterProtected();

protected slots:
  virtual void languageChange();

private:
  bool mExpressionTriggerValid;
  bool mExpressionDelayValid;
  bool mExpressionEAValid;
  QString mEAName;
  bool mChanged;
  CEvent *mpEvent;
  std::string mAssignmentKey;
  unsigned C_INT32 mCurrentTarget;
  CCopasiVector< CEventAssignment > mAssignments;

  void init();
  bool loadFromEvent();
  void saveToEvent();

private slots:
  void slotBtnCommitClicked();
  void slotBtnDeleteClicked();
  void slotBtnNewClicked();
  void slotBtnRevertClicked();
  virtual void slotNameChanged();
  void slotAddTarget();
  void slotDeleteTarget();
  void slotSelectObject();
  void slotActualizeAssignmentExpression(int index);
  void slotApplyDelay(bool display);
};

#endif // CQEVENTWIDGET1_H
