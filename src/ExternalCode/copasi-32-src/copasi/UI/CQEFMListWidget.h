// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/UI/CQEFMListWidget.h,v $
//   $Revision: 1.1 $
//   $Name: Build-31 $
//   $Author: shoops $
//   $Date: 2009/09/29 16:35:36 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CQEFMListWidget
#define COPASI_CQEFMListWidget

#include <qvariant.h>

#include "copasi/UI/ui_CQEFMListWidget.h"
#include "copasi/UI/CQSortFilterProxyModel.h"
#include "copasi/UI/CQFluxModeDM.h"

class CEFMTask;

class CQEFMListWidget : public QWidget, public Ui::CQEFMListWidget
{
  Q_OBJECT

public:
  CQEFMListWidget(QWidget* parent = 0, const char* name = 0);
  virtual ~CQEFMListWidget();

  bool loadResult(const CEFMTask * pTask);

protected slots:
  virtual void languageChange();
  virtual void slotFilterChanged();

private:
  const CEFMTask * mpTask;
  CQSortFilterProxyModel *mpProxyModel;
  CQFluxModeDM * mpFluxModeDM;
};

#endif // COPASI_CQEFMListWidget
