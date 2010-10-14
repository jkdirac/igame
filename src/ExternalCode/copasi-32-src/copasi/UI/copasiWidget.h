// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/UI/copasiWidget.h,v $
//   $Revision: 1.27 $
//   $Name: Build-31 $
//   $Author: shoops $
//   $Date: 2009/07/20 16:06:21 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/********************************************************
 Author: Liang Xu
 Version : 1.xx  <first>
 Description:
 Date: 04/03
 Comment : CopasiWidget: Provide base class for all widget: for resizable/minimize
 Contact: Please contact lixu1@vt.edu.
 *********************************************************/

#ifndef COPASI_WIDGET_H
#define COPASI_WIDGET_H
#include <qwidget.h>
//Added by qt3to4:
#include <QResizeEvent>
#include "UI/listviews.h"

class DataModelGUI;
class QResizeEvent;
class ListViews;
class CCopasiDataModel;
class CCopasiObject;

class CopasiWidget : public QWidget
{
  Q_OBJECT

public:
  CopasiWidget(QWidget * parent = 0, const char * name = 0, Qt::WFlags f = 0);
  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();
  bool enter(const std::string & key);
  virtual void setFramework(int framework);
  bool getIgnoreUpdates();
  void setIgnoreUpdates(bool v);
  CCopasiDataModel * getDataModel();

protected:
  virtual bool enterProtected();

  ListViews * mpListView;
  std::string mKey;
  CCopasiObject * mpObject;
  CCopasiDataModel * mpDataModel;

  bool mIgnoreUpdates;
  int mFramework;

protected slots:
  virtual bool protectedNotify(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key = "");
};

#endif // !defined(COPASI_WIDGET_H)
