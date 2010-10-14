// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/UI/CQCompartmentDM.h,v $
//   $Revision: 1.4 $
//   $Name: Build-31 $
//   $Author: aekamal $
//   $Date: 2009/06/04 16:09:42 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQCompartmentDM_H
#define CQCompartmentDM_H

#include "model/CModel.h"
#include "CQBaseDataModel.h"

#define COL_NAME_COMPARTMENTS         1
#define COL_TYPE_COMPARTMENTS         2
#define COL_IVOLUME                   3
#define COL_VOLUME                    4
#define COL_RATE_COMPARTMENTS         5
#define COL_IEXPRESSION_COMPARTMENTS  6
#define COL_EXPRESSION_COMPARTMENTS   7
#define TOTAL_COLS_COMPARTMENTS       8

class CQCompartmentDM : public CQBaseDataModel
{
  Q_OBJECT

public:
  CQCompartmentDM(QObject *parent = 0);
  const QStringList& getTypes();
  const std::vector< unsigned C_INT32 >& getItemToType();
  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  int columnCount(const QModelIndex &parent = QModelIndex()) const;
  Qt::ItemFlags flags(const QModelIndex &index) const;
  QVariant data(const QModelIndex &index, int role) const;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole);
  bool removeRows(QModelIndexList rows, const QModelIndex &index = QModelIndex());

protected:
  QStringList mTypes;
  /**
    * A vector mapping the item index to a model valu type
    */
  std::vector< unsigned C_INT32 > mItemToType;
  bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
  bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());
};

#endif //CQCompartmentDM_H
