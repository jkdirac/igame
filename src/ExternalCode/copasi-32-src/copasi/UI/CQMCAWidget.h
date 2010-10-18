// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/UI/CQMCAWidget.h,v $
//   $Revision: 1.5 $
//   $Name: Build-31 $
//   $Author: pwilly $
//   $Date: 2009/04/12 13:20:35 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQMCAWIDGET_H
#define CQMCAWIDGET_H

#include <qvariant.h>

/*
#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <Qt3Support/Q3ButtonGroup>
#include <QtGui/QCheckBox>
#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3GridLayout>
#include <QtGui/QSpacerItem>
#include <Qt3Support/Q3VBoxLayout>
//Added by qt3to4:
#include <Q3GridLayout>
#include <Q3VBoxLayout>
#include <Q3Frame>
 */

#include "ui_CQMCAWidget.h"

#include "TaskWidget.h"

class CQMCAWidget : public TaskWidget, public Ui::CQMCAWidget
{
  Q_OBJECT

public:
  CQMCAWidget(QWidget* parent = 0, const char* name = 0);
  ~CQMCAWidget();

  virtual bool runTask();

public slots:
  virtual void slotSteadyStateChecked();

protected:
  virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);
  virtual bool loadTask();
  virtual bool saveTask();

protected slots:
  virtual void languageChange();

private:
  void init();
  bool loadParameterTable();
  bool saveParameterTable();
};

#endif // CQMCAWIDGET_H
