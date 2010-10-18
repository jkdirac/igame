// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/UI/CCopasiSelectionDialog.h,v $
//   $Revision: 1.14 $
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

#ifndef CCopasiSelectionDialog_H__
#define CCopasiSelectionDialog_H__

#include <vector>

#include <qdialog.h>
//Added by qt3to4:
#include <Q3VBoxLayout>
#include <Q3HBoxLayout>

#include "UI/CCopasiSimpleSelectionTree.h"

class QPushButton;
class QCheckBox;
class CCopasiSelectionWidget;
class Q3HBox;
class Q3VBoxLayout;
class Q3HBoxLayout;
class CCopasiObject;
class CModel;
class CArrayAnnotation;

class CCopasiSelectionDialog: public QDialog
{
  Q_OBJECT

protected:
  QPushButton* mpOKButton;
  QPushButton* mpCancelButton;
  QCheckBox* mpModeCheckBox;
  Q3HBoxLayout* mpButtonBox;
  QWidget* mpMainWidget;
  CCopasiSelectionWidget* mpSelectionWidget;
  Q3VBoxLayout* mpMainLayout;
  std::vector<const CCopasiObject * > * mpTmpVector;
  std::vector<const CCopasiObject * > * mpOutputVector;
  bool mExpertMode;
  bool mExpertModeEnabled;

protected slots:
  void okButton_clicked();
  void cancelButton_clicked();
  void modeButton_toggled(bool checked);

public:
  CCopasiSelectionDialog(QWidget * parent = 0, const char * name = 0, bool modal = false);
  ~CCopasiSelectionDialog();
  void setOutputVector(std::vector< const CCopasiObject * > * outputVector);
  void setModel(const CModel* model,
                const CCopasiSimpleSelectionTree::ObjectClasses & classes);
  void setSingleSelection(bool singleSelectionMode);
  void enableExpertMode(bool enable);

  static
  const CCopasiObject * getObjectSingle(QWidget * pParent,
                                        const CCopasiSimpleSelectionTree::ObjectClasses & classes,
                                        const CCopasiObject * pCurrentObject = NULL);
  static
  std::vector< const CCopasiObject * > getObjectVector(QWidget * pParent,
      const CCopasiSimpleSelectionTree::ObjectClasses & classes,
      const std::vector< const CCopasiObject * > * pCurrentSelection = NULL);

  /**
   * single=true means only one object can be returned (in the first element of the return vector)
   *  when single=true and the dialog is canceled the return vector will have size=1 and contain the NULL pointer.
   *  when single=false and the dialog is canceled the return vector will be empty.
   * value=true means only objects that have a value (i.e. arrayElementReferences) are allowed.
   * otherwise also the whole array annotation may be returned.
   */
  static std::vector<const CCopasiObject*> chooseCellMatrix(const CArrayAnnotation * pArrayAnnotation,
      bool single, bool value, std::string caption = "");
};
#endif /* SimpleSelectionDialog_H__ */
