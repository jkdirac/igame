// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/UI/CQSensResultWidget.h,v $
//   $Revision: 1.11.2.1 $
//   $Name: Build-31 $
//   $Author: shoops $
//   $Date: 2010/04/07 16:51:57 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQSENSRESULT_H
#define CQSENSRESULT_H

#include "ui_CQSensResultWidget.h"

#include "CQArrayAnnotationsWidget.h"
#include "utilities/CAnnotatedMatrix.h"
#include "mathematics.h"

class CQSensResultWidget : public CopasiWidget, public Ui::CQSensResultWidget
{
  Q_OBJECT

public:
  CQSensResultWidget(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0);
  ~CQSensResultWidget();

  void newResult();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();

protected slots:
  virtual void languageChange();

  void saveToFile();

protected:
  virtual bool enterProtected();
  //bool loadFromBackend();
  void clearArrays();

  const CArrayAnnotation * mpResult;
  const CArrayAnnotation * mpScaledResult;
  const CArrayAnnotation * mpCollapsedResult;

private:
  void init();
};

#endif
