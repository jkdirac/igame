// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/UI/CQLyapWidget.h,v $
//   $Revision: 1.9 $
//   $Name: Build-31 $
//   $Author: pwilly $
//   $Date: 2009/04/12 19:49:56 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQLYAPWIDGET_H
#define CQLYAPWIDGET_H

#include <qvariant.h>

#include "ui_CQLyapWidget.h"
/*
#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <Qt3Support/Q3ButtonGroup>
#include <QtGui/QCheckBox>
#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3GridLayout>
#include <Qt3Support/Q3HBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <Qt3Support/Q3VBoxLayout>
//Added by qt3to4:
#include <Q3GridLayout>
#include <Q3HBoxLayout>
#include <Q3VBoxLayout>
#include <QLabel>
#include <Q3Frame>
 */
#include "TaskWidget.h"

class CQLyapWidget : public TaskWidget, public Ui::CQLyapWidget
{
  Q_OBJECT

public:
  CQLyapWidget(QWidget* parent = 0, const char* name = 0);
  ~CQLyapWidget();

  virtual bool runTask();

protected:
  virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);
  virtual bool loadTask();
  virtual bool saveTask();

protected slots:
  virtual void languageChange();

  void slotDelayChecked();

private:
  void init();
};

#endif // CQLYAPWIDGET_H
