// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/MIRIAMUI/CQModifiedDM.h,v $
//   $Revision: 1.6.2.1 $
//   $Name: Build-31 $
//   $Author: shoops $
//   $Date: 2010/05/25 21:26:30 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQModifiedDM_H
#define CQModifiedDM_H

#include "UI/CQBaseDataModel.h"

class CMIRIAMInfo;

#define COL_DATE_MODIFIED      1
#define TOTAL_COLS_MODIFIEDS   2

class CQModifiedDM : public CQBaseDataModel
{
  Q_OBJECT

public:
  CQModifiedDM(CMIRIAMInfo* MIRIAMInfo, QObject *parent = 0);
  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  int columnCount(const QModelIndex &parent = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role) const;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole);
  bool removeRows(QModelIndexList rows, const QModelIndex &index = QModelIndex());

protected:
  bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
  bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());
  CMIRIAMInfo* mpMIRIAMInfo;
};

#endif //CQModifiedDM_H
