// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/UI/CCopasiPlotSelectionDialog.h,v $
//   $Revision: 1.8 $
//   $Name: Build-31 $
//   $Author: shoops $
//   $Date: 2009/04/21 16:20:31 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CCopasiPlotSelectionDialog_H__
#define CCopasiPlotSelectionDialog_H__

#include <vector>

#include <qdialog.h>
//Added by qt3to4:
#include <Q3VBoxLayout>
#include <Q3HBoxLayout>
#include <QLabel>

#include "UI/CCopasiSimpleSelectionTree.h"

class QWidget;
class QPushButton;
class QSplitter;
class QCheckBox;
class Q3VBox;
class Q3HBoxLayout;
class Q3VBoxLayout;
class QLabel;
class CCopasiObject;
class CModel;
class CCopasiSelectionWidget;

class CCopasiPlotSelectionDialog: public QDialog
{
  Q_OBJECT

public:
  CCopasiPlotSelectionDialog(QWidget * parent = 0, const char * name = 0, bool modal = false, Qt::WFlags f = 0);
  ~CCopasiPlotSelectionDialog();
  void setOutputVectors(std::vector< const CCopasiObject * > * outputVector1,
                        std::vector< const CCopasiObject * > * outputVector2);
  void setModel(CModel* model,
                const CCopasiSimpleSelectionTree::ObjectClasses & classes);

protected slots:
  void slotOKButtonClicked();
  void slotCancelButtonClicked();
  void slotExpertCheckBoxToggled(bool checked);

protected:
  void setTabOrder();

protected:
  QPushButton* mpOKButton;
  QPushButton* mpCancelButton;
  QCheckBox* mpExpertCheckBox;
  CCopasiSelectionWidget* mpXAxisSelectionWidget;
  CCopasiSelectionWidget* mpYAxisSelectionWidget;
  QSplitter* mpSplitter;
  Q3HBoxLayout* mpButtonBox;
  Q3VBoxLayout* mpMainLayout;
  QLabel* mpXAxisLabel;
  QLabel* mpYAxisLabel;
  Q3VBox* mpXAxisSelectionBox;
  Q3VBox* mpYAxisSelectionBox;
  std::vector< const CCopasiObject * > * mpXAxisOutputVector;
  std::vector< const CCopasiObject * > * mpYAxisOutputVector;
};

#endif // CPlotSelectionDialog_H__
