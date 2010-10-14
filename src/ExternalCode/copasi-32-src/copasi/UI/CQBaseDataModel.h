// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/UI/CQBaseDataModel.h,v $
//   $Revision: 1.7 $
//   $Name: Build-31 $
//   $Author: aekamal $
//   $Date: 2009/07/13 15:43:44 $
// End CVS Header
// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQBaseDataModel_H
#define CQBaseDataModel_H

#include <QTableView>
#include <QAbstractTableModel>

#include "listviews.h"

#define COL_ROW_NUMBER   0

class CQBaseDataModel : public QAbstractTableModel
{
  Q_OBJECT

public:
  CQBaseDataModel(QObject *parent = 0);
  virtual QVariant data(const QModelIndex &index, int role) const = 0;
  virtual QVariant headerData(int section, Qt::Orientation orientation,
                              int role = Qt::DisplayRole) const = 0;
  virtual Qt::ItemFlags flags(const QModelIndex &index) const;
  virtual bool setData(const QModelIndex &index, const QVariant &value,
                       int role = Qt::EditRole) = 0;
  bool insertRow();
  bool removeRow(int position);
  bool clear();
  virtual bool isDefaultRow(const QModelIndex& i) const;
  QString createNewName(const QString name, const int nameCol);

protected:
  virtual bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) = 0;
  virtual bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) = 0;

signals:
  void notifyGUI(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key = "");
};

#endif //CQBaseDataModel_H
