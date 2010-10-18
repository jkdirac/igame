// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/plotUI/plotwindow.h,v $
//   $Revision: 1.27 $
//   $Name: Build-31 $
//   $Author: pwilly $
//   $Date: 2009/06/21 05:31:02 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <fstream>
#include <string>
#include <vector>
#include <QMainWindow>
#include <QToolButton>

#include "copasi.h"
#include "UI/CopasiFileDialog.h"
#include "utilities/COutputHandler.h"

class QAction;

class CopasiPlot;
class CPlotSpecification;
class CPlotSpec2Vector;
class CCopasiContainer;
class COutputHandlerPlot;

class PlotWindow : public QMainWindow, public COutputInterface
{
  Q_OBJECT

private:

  // points to the plot instance inside this window
  CopasiPlot *mpPlot;
  COutputHandlerPlot *mpHandler;

  void createToolBar();
  void createActions();

public:
  PlotWindow(COutputHandlerPlot * pHandler, const CPlotSpecification* ptrSpec);

  bool initFromSpec(const CPlotSpecification* ptrSpec);

  QToolButton * zoomButton;
  QToolButton * printButton;
  QToolButton * print2Button;
  QToolButton * saveButton;

  QToolButton * mpSelectAll;
  QToolButton * mpDeselectAll;

  ~PlotWindow();

  /**
   * compile the object list from name vector
   * @param std::vector< CCopasiContainer * > listOfContainer
   * @param  const CCopasiDataModel* pDataModel
   * @return bool success
   */
  virtual bool compile(std::vector< CCopasiContainer * > listOfContainer, const CCopasiDataModel* pDataModel);

  /**
   * Perform an output event for the current activity
   * @param const Activity & activity
   */
  virtual void output(const Activity & activity);

  /**
   * Introduce an additional separator into the output
   * @param const Activity & activity
   */
  virtual void separate(const Activity & activity);

  /**
   * Finish the output
   */
  virtual void finish();

  /**
   * Retrieve the list of objects handled by the interface
   * @return const std::set< const CCopasiObject * > & objects
   */
  virtual const std::set< const CCopasiObject * > & getObjects() const;

private slots:
  //void enableZoom();

  //void mouseReleased(const QMouseEvent &e);

  // Print the plot to printer
  void printPlot();

  // Print the plot as an image
  void printAsImage();

  /// Save data into a file
  void slotSaveData();

  /// Zoom out
  void slotZoomOut();

  /**
   * Show all curves.
   */
  void slotSelectAll();

  /**
   * Hide all curves.
   */
  void slotDeselectAll();

  /*
   * Close current window
   */
  void slotCloseWindow();
};
