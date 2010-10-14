// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/wizard/Attic/wizard.h,v $
//   $Revision: 1.11.2.3 $
//   $Name: Build-31 $
//   $Author: shoops $
//   $Date: 2010/04/28 16:39:21 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef WIZARDDIALOG_H
#define WIZARDDIALOG_H

#include <qvariant.h>

#include "copasi/wizard/ui_wizard.h"

class QUrl;

class WizardDialog : public QDialog, public Ui::WizardDialog
{
  Q_OBJECT

public:
  WizardDialog(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);
  ~WizardDialog();

  static const char* texts[6];

  virtual void setCopasiMainWindow(QWidget * copasiMainWindow);

public slots:
  virtual void buttonGroup2_clicked(int);
  virtual void forwardButton_clicked();
  virtual void backButton_clicked();
  virtual void textBrowser_anchorClicked(const QUrl & url);

protected:
  static const char* Error;
  static QString helpPath;
  QWidget* copasiMainWindow;
  QButtonGroup * buttonGroup;

protected slots:
  virtual void languageChange();

};

#endif // WIZARDDIALOG_H
