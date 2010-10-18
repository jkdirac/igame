// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/UI/CQTrajectoryWidget.h,v $
//   $Revision: 1.9 $
//   $Name: Build-31 $
//   $Author: shoops $
//   $Date: 2009/11/30 19:28:01 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQTRAJECTORYWIDGET_H
#define CQTRAJECTORYWIDGET_H

#include <qvariant.h>

#include "ui_CQTrajectoryWidget.h"

class CTrajectoryProblem;
class CQValidatorInt;
class CQValidatorDouble;

#include "TaskWidget.h"

#define TSMAX 10000000

class CQTrajectoryWidget : public TaskWidget, public Ui::CQTrajectoryWidget
{
  Q_OBJECT

public:
  CQTrajectoryWidget(QWidget* parent = 0, const char* name = 0);
  ~CQTrajectoryWidget();

  virtual bool runTask();
  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);

public slots:
  void slotDuration();
  void slotIntervalSize();
  void slotIntervals();
  void updateIntervals();
  void slotOutputDelay(bool checked);

protected:
  virtual bool saveTask();
  virtual bool loadTask();
  virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);

protected slots:
  virtual void languageChange();

private:
  CQValidatorInt * mpValidatorIntervals;
  CQValidatorDouble * mpValidatorDelay;
  CQValidatorDouble * mpValidatorIntervalSize;
  CQValidatorDouble * mpValidatorDuration;
  CTrajectoryProblem * mpTrajectoryProblem;

  void init();
  void destroy();
  void checkTimeSeries();
  void showUnits();
};

#endif // CQTRAJECTORYWIDGET_H
