// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/UI/ParametersWidget.h,v $
//   $Revision: 1.11 $
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

#ifndef PARAMETERSWIDGET_H
#define PARAMETERSWIDGET_H

#include <qvariant.h>
#include <qdialog.h>
//Added by qt3to4:
#include <Q3VBoxLayout>
#include <Q3GridLayout>
#include <Q3HBoxLayout>
#include <QLabel>

#include "UI/copasiWidget.h"

class Q3VBoxLayout;
class Q3HBoxLayout;
class Q3GridLayout;
class QSpacerItem;
class QPushButton;
class Q3ListView;
class Q3ListViewItem;
class QLabel;
class CParameterListItem;

class ParametersWidget : public CopasiWidget
{
  Q_OBJECT

public:
  ParametersWidget(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0);
  ~ParametersWidget();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();
  virtual void setFramework(int framework);

protected:
  virtual bool enterProtected();
  bool loadFromModel();
  bool saveToModel();

  QPushButton* commitButton;
  QPushButton* revertButton;
  QPushButton* saveButton;
  Q3ListView* listView;
  QLabel* labelTitle;

  Q3GridLayout* ParametersWidgetLayout;
  QSpacerItem* spacer2;
  Q3VBoxLayout* layoutLeft;
  QSpacerItem* spacer1;

  CParameterListItem* mTimeItem;
  CParameterListItem* mCompItem;
  CParameterListItem* mReacItem;
  CParameterListItem* mMetabItem;
  CParameterListItem* mParamItem;

protected slots:
  virtual void commitPressed();
  virtual void revertPressed();
  virtual void savePressed();

  virtual void editItem(Q3ListViewItem * item, const QPoint & pnt, int c);
  virtual void editItem(Q3ListViewItem * item);
};

#endif // PARAMETERSWIDGET_H
