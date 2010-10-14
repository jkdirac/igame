// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/UI/CQComboDelegate.h,v $
//   $Revision: 1.1 $
//   $Name: Build-31 $
//   $Author: aekamal $
//   $Date: 2009/05/04 15:24:00 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQComboDelegate_H
#define CQComboDelegate_H

#include <QItemDelegate>

class CQComboDelegate : public QItemDelegate
{
  Q_OBJECT

public:
  CQComboDelegate(const QStringList* pComboItems, QObject *parent = 0);

  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const;

  void setEditorData(QWidget *editor, const QModelIndex &index) const;
  void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex &index) const;

  void updateEditorGeometry(QWidget *editor,
                            const QStyleOptionViewItem &option, const QModelIndex &index) const;
private:
  const QStringList* mpComboItems;
};

class CQIndexComboDelegate : public CQComboDelegate
{
public:
  CQIndexComboDelegate(const QStringList *pComboItems, QObject *parent);
  void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex &index) const;
};
#endif //CQComboDelegate_H
