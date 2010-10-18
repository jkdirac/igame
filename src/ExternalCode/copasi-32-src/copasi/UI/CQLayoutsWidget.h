// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/UI/CQLayoutsWidget.h,v $
//   $Revision: 1.4.2.1 $
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

#ifndef CQLAYOUTS_WIDGET_H
#define CQLAYOUTS_WIDGET_H

#include <map>

#include <qtoolbutton.h>

#include "copasi/UI/CopasiTableWidget.h"

#ifdef USE_CRENDER_EXTENSION
class CQNewMainWindow;
#else
class CQLayoutMainWindow;
#endif // USE_CRENDER_EXTENSION

class CQLayoutsWidget : public CopasiTableWidget
{
  Q_OBJECT

public:
  CQLayoutsWidget(QWidget *parent, const char * name = 0, Qt::WFlags f = 0)
      : CopasiTableWidget(parent, false, name, f)
  {init();}

  void deleteLayoutWindows();

protected:
  /**
   * shows units for the quantities
   */
  virtual void updateHeaderUnits();

  /**
   * This initializes the widget
   */
  virtual void init();

  /**
   * returns a list of objects that should be displayed
   */
  virtual std::vector<const CCopasiObject*> getObjects() const;

  /**
   * fills one table row with the data from one object
   */
  virtual void tableLineFromObject(const CCopasiObject* obj, unsigned C_INT32 row);

  /**
   * reads the contents of one row of the table and writes it to the object
   */
  virtual void tableLineToObject(unsigned C_INT32 row, CCopasiObject* obj);

  /**
   * creates a new object
   */
  virtual CCopasiObject* createNewObject(const std::string & name);

  /**
   * deletes objects. Performs all additional tasks, like asking the user, ...
   */
  virtual void deleteObjects(const std::vector<std::string> & keys);

  /**
   * this is used to fill a row of the table when a new object is added to the table.
   * it fills only the data columns, not the name. It should not fill column exc.
   */
  virtual void defaultTableLineContent(unsigned C_INT32 row, unsigned C_INT32 exc);

  /**
   * the prefix that is used to construct new object names
   */
  virtual QString defaultObjectName() const;

  /**
   * This method provides a hook for derived classes to act on changes in
   * the table.
   * @param unsigned C_INT32 row
   * @param unsigned C_INT32 col
   */
  virtual void valueChanged(unsigned C_INT32 row, unsigned C_INT32 col);

protected:

  /**
   * map that stores the layout windows for each layout.
   */
#ifdef USE_CRENDER_EXTENSION
  std::map<std::string, CQNewMainWindow*> mLayoutWindowMap;
#else
  std::map<std::string, CQLayoutMainWindow*> mLayoutWindowMap;
#endif // USE_CRENDER_EXTENSION

protected slots:
  void slotDoubleClicked(int row, int col, int m, const QPoint & n);
  void slot_show(int row);
};

class CQShowLayoutButton : public QToolButton
{
  Q_OBJECT

public:
  CQShowLayoutButton(unsigned int row, QWidget* pParent = NULL, const char* name = "");

signals:
  void signal_show(int row);

protected:
  unsigned int mRow;

protected slots:
  void slot_clicked();
};

#endif // CQLAYOUT_WIDGETS_H
