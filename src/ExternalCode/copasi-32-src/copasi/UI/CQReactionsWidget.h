// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/UI/CQReactionsWidget.h,v $
//   $Revision: 1.9 $
//   $Name: Build-31 $
//   $Author: aekamal $
//   $Date: 2010/01/11 15:30:51 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQReactionsWidget_h
#define CQReactionsWidget_h

#include "CQSortFilterProxyModel.h"
#include "ui_CQReactionsWidget.h"
#include "CQReactionDM.h"

class CQReactionsWidget : public CopasiWidget, public Ui::CQReactionsWidget
{
  Q_OBJECT

public:
  CQReactionsWidget(QWidget* parent = 0, const char* name = 0);
  ~CQReactionsWidget();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();
  virtual void setFramework(int framework);

private:
  CQReactionDM* mpReactionDM;
  CQSortFilterProxyModel *mpProxyModel;
  void deleteSelectedReactions();

protected:
  virtual bool enterProtected();
  virtual void keyPressEvent(QKeyEvent* ev);

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

#endif // CQReactionsWidget_h
