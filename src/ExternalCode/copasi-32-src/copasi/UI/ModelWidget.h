// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/UI/ModelWidget.h,v $
//   $Revision: 1.18 $
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

/****************************************************************************
 **  $ CopasiUI/ModelWidget.h
 **  $ Author  : Mudita Singhal
 **
 ** This is the header file for the Model Widget
 *****************************************************************************/
#ifndef MODELWIDGET_H
#define MODELWIDGET_H

#include <qvariant.h>
#include <qwidget.h>
//Added by qt3to4:
#include <Q3GridLayout>
#include <Q3HBoxLayout>
#include <Q3VBoxLayout>
#include <QLabel>
#include <Q3Frame>
#include "UI/copasiWidget.h"
#include <q3textbrowser.h>

class Q3VBoxLayout;
class Q3HBoxLayout;
class Q3GridLayout;
class Q3Frame;
class QSpacerItem;
class QLineEdit;
class QLabel;
class QComboBox;
class QPushButton;
class CModel;

class ModelWidget : public CopasiWidget
{
  Q_OBJECT

public:
  ModelWidget(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0);
  ~ModelWidget();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();

protected slots:
  virtual void slotBtnCancelClicked();
  virtual void slotBtnOKClicked();

public slots:
  virtual void toggleEditorBox();

protected:
  virtual bool enterProtected();
  bool loadModel(CModel *model);
  bool saveToModel();
  QString mOldComment;

  Q3GridLayout* ModelWidgetLayout;
  Q3HBoxLayout* Layout5;
  Q3VBoxLayout* showMarkupLayout;
  QSpacerItem* spacer;
  QLineEdit* LineEdit;
  // QTextBrowser* textBrowser;
  Q3TextEdit* mpEditComment;
  QLabel* TextLabel1;
  QLabel* TextLabel2;
  QLabel* TextLabel3;
  QLabel* TextLabel4;
  QLabel* TextLabelArea;
  QLabel* TextLabelLength;
  QLabel* mpLblModelType;
  QLabel* mpLblInitial;
  QLabel* mpLblCurrent;
  QLabel* mpLblTime;
  QLineEdit *mpInitialTime;
  QLineEdit *mpCurrentTime;
  QPushButton* mpToggleMarkup;
  QComboBox* ComboBox1;
  QComboBox* ComboBox2;
  QComboBox* ComboBox3;
  QComboBox* ComboBoxArea;
  QComboBox* ComboBoxLength;
  QComboBox* mpBoxModelType;

  QPushButton* commitChanges;
  QPushButton* cancelChanges;
};

#endif // MODELWIDGET_H
