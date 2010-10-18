// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/UI/CQReportDefinition.h,v $
//   $Revision: 1.13.2.2 $
//   $Name: Build-31 $
//   $Author: shoops $
//   $Date: 2010/07/16 14:57:33 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQREPORTDEFINITION_H
#define CQREPORTDEFINITION_H

#include "ui_CQReportDefinition.h"

class CReportDefinition;

class CQReportDefinition : public CopasiWidget, public Ui::CQReportDefinition
{
  Q_OBJECT

public:
  CQReportDefinition(QWidget* parent = 0, const char* name = 0);
  ~CQReportDefinition();

  virtual bool leave();
  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);

protected:
  virtual bool enterProtected();

protected slots:
  virtual void languageChange();

private:
  bool mAdvanced;
  bool mChanged;
  CReportDefinition * mpReportDefinition;
  QString mOldComment;

  bool load();
  bool save();
  bool setAdvancedMode(const bool & advanced);

private slots:
  void nameChanged(const QString & string);
  void taskChanged(const QString & string);
  void commentChanged();
  void separatorChanged(const QString & string);
  void precisionChanged(const QString & string);
  void chkTabClicked();
  void btnAdvancedClicked();
  void btnItemClicked();
  void btnSeparatorClicked();
  void btnTextClicked();
  void btnDeleteClicked();
  void btnUpClicked();
  void btnDownClicked();
  void chkTitleClicked();
  void btnDeleteReportClicked();
  void btnNewReportClicked();
  void btnRevertClicked();
  void btnCommitClicked();
};

#endif // CQREPORTDEFINITION_H
