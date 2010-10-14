// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/layoutUI/CQCurrentValueTable.h,v $
//   $Revision: 1.9 $
//   $Name: Build-31 $
//   $Author: gauges $
//   $Date: 2010/02/03 13:53:00 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQCURRENTVALUETABLE_H_
#define  CQCURRENTVALUETABLE_H_
#include <qwidget.h>

#include <string>
#include <map>

#include "copasi.h"

#include "layoutUI/CDataEntity.h"

class QPushButton;
class QTableWidget;
class QHeaderView;

class CQCurrentValueTable : public QWidget
{

  Q_OBJECT        // must include this if you use Qt signals/slots

protected:
  std::map<int, std::string> mIndexMap;
  QTableWidget* mpTable;
  QPushButton* mpCheckAllButton;
  QPushButton* mpUncheckAllButton;

public:
  CQCurrentValueTable(QWidget *parent = 0);
  ~CQCurrentValueTable();

  void setNumRows(int rows);
  void setNumCols(int columns);
  void updateRowInTable(int row, C_FLOAT64 val);
  void setRowInTable(int row, std::string key, std::string s, C_FLOAT64 val);
  int numRows() const;

  QHeaderView* verticalHeader();
  std::string getKeyForRow(int row) const;
  bool getValueForRow(int row) const;

protected:
  void setValue(int row, C_FLOAT64 val);
  void setKeyIndex(std::string key, int row);
  void setAllBoxesChecked(bool checked = true);
  void setAllBoxesUnchecked();
  void init();

private slots:
  //void mouseClickedOverTable(int row, int col , int button, const QPoint & mousepos);
  void slotCheckAllClicked();
  void slotUncheckAllClicked();
  void tableValueChanged(int row, int column);

signals:
  void valueChanged(int row);
};

#endif /*CQCURRENTVALUETABLE_H_*/
