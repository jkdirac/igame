// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/UI/ScanWidget.h,v $
//   $Revision: 1.62 $
//   $Name: Build-31 $
//   $Author: pwilly $
//   $Date: 2009/03/18 12:40:35 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef SCANWIDGET_H
#define SCANWIDGET_H

#include "copasi.h"
#include "TaskWidget.h"

#include <QGridLayout>
#include <QHBoxLayout>

//Added by qt3to4:
#include <Q3GridLayout>
#include <Q3HBoxLayout>

//class Q3HBoxLayout;
//class Q3GridLayout;
class QPushButton;
class QComboBox;

class CScanContainerWidget;

class ScanWidget : public TaskWidget
{
  Q_OBJECT

public:
  ScanWidget(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0);
  ~ScanWidget();

  virtual bool runTask();

protected:

  virtual bool loadTask();

  virtual bool saveTask();

  //dummy, should not be used in this widget
  virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & /*type*/) {return NULL;};

  CScanContainerWidget* scrollview;

  QPushButton* buttonNewItem;
  QComboBox* comboType;

  /*
      Q3GridLayout* ScanWidgetLayout;
      Q3HBoxLayout* Layout24;
  */
  QGridLayout* ScanWidgetLayout;
  QHBoxLayout* Layout24;

protected slots:
  bool slotAddItem();
};

#endif
