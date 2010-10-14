// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/UI/CQTSSAResultWidget.h,v $
//   $Revision: 1.5 $
//   $Name: Build-31 $
//   $Author: shoops $
//   $Date: 2009/07/16 15:47:26 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef TSSARESULTWIDGET_H
#define TSSARESULTWIDGET_H

#include "UI/copasiWidget.h"
//Added by qt3to4:
#include <Q3VBoxLayout>
#include <Q3GridLayout>
#include <Q3HBoxLayout>

class Q3VBoxLayout;
class Q3HBoxLayout;
class Q3GridLayout;
//class QPushButton;

class CQTSSAResultSubWidget;

class CQTSSAResultWidget : public CopasiWidget
{
  Q_OBJECT

public:
  CQTSSAResultWidget(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0);
  ~CQTSSAResultWidget();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();
  CQTSSAResultSubWidget* getSubWidget() {return mCentralWidget;};

protected slots:
  //virtual void slotBtnCancelClicked();
  //virtual void slotBtnOKClicked();

public:
  bool loadFromBackend();
  bool saveToBackend();

protected:
  virtual bool enterProtected();
  Q3GridLayout* mWidgetLayout;
  CQTSSAResultSubWidget* mCentralWidget;
};

#endif
