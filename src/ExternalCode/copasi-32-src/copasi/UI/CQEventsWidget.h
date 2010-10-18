// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/UI/CQEventsWidget.h,v $
//   $Revision: 1.6 $
//   $Name: Build-31 $
//   $Author: aekamal $
//   $Date: 2010/01/11 15:30:51 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQEventsWidget_h
#define CQEventsWidget_h

#include "CQSpinBoxDelegate.h"
#include "CQSortFilterProxyModel.h"
#include "ui_CQEventsWidget.h"
#include "CQEventDM.h"

class CQEventsWidget : public CopasiWidget, public Ui::CQEventsWidget
{
  Q_OBJECT

public:
  CQEventsWidget(QWidget* parent = 0, const char* name = 0);
  ~CQEventsWidget();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();

private:
  CQEventDM* mpEventDM;
  CQSortFilterProxyModel *mpProxyModel;
  CQSpinBoxDelegate *mpOrderDelegate;
  void deleteSelectedEvents();

protected:
  virtual void keyPressEvent(QKeyEvent* ev);
  virtual bool enterProtected();

protected slots:
  virtual void languageChange();
  virtual void slotBtnNewClicked();
  virtual void slotBtnDeleteClicked();
  virtual void slotBtnClearClicked();
  virtual void slotDoubleClicked(const QModelIndex proxyIndex);
  virtual void dataChanged(const QModelIndex& topLeft,
                           const QModelIndex& bottomRight);
  virtual void slotFilterChanged();
};

#endif // CQEventsWidget_h
