// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/plotUI/CopasiPlot.h,v $
//   $Revision: 1.37 $
//   $Name: Build-31 $
//   $Author: shoops $
//   $Date: 2010/02/18 20:01:58 $
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

// the plot object for COPASI

#ifndef COPASIPLOT_H
#define COPASIPLOT_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include <qpainter.h>
#include <qwt_plot.h>
#include <qwt_painter.h>
#include <qwt_data.h>
#include <qwt_plot_curve.h>

#include "plotUI/CHistogram.h"
#include "plot/CPlotItem.h"

#include "report/CCopasiObject.h"
#include "utilities/COutputHandler.h"
#include "utilities/CopasiTime.h"
#include "utilities/CVector.h"

// class CCopasiObjectName;

// NaN are ignored bounding rectangle
class MyQwtCPointerData : public QwtCPointerData
{
public:
  MyQwtCPointerData(const double *x, const double *y, size_t size);

  MyQwtCPointerData &operator=(const MyQwtCPointerData & rhs);

  virtual QwtData *copy() const;

  virtual QwtDoubleRect boundingRect() const;
};

// NaN in data splits curve
class MyQwtPlotCurve : public QwtPlotCurve
{
public:
  MyQwtPlotCurve(const QString &title = QString::null)
      : QwtPlotCurve(title)
  {}

protected:
  void myDrawLines(QPainter *painter,
                   const QwtScaleMap &xMap, const QwtScaleMap &yMap,
                   int from, int to) const;

  //Reroute curve plotting to our own routine
  virtual void drawCurve(QPainter *painter, int style,
                         const QwtScaleMap &xMap, const QwtScaleMap &yMap,
                         int from, int to) const;
};

//*******************************************************

class CPlotSpec2Vector;
class CPlotSpecification;
class QwtPlotZoomer;

class CopasiPlot : public QwtPlot, public COutputInterface
{
  Q_OBJECT
private:
  /**
   * Default constructor which may never be called.
   * @param QWidget* parent (default: NULL)
   */
  CopasiPlot(QWidget* parent = NULL);

public:
  /**
   * Specific constructor
   * @param const CPlotSpecification* plotspec
   * @param QWidget* parent (default: NULL)
   */
  CopasiPlot(const CPlotSpecification* plotspec, QWidget* parent = NULL);

  /**
   * Initialize the the plot from the specification
   * @param const CPlotSpecification* plotspec
   */
  bool initFromSpec(const CPlotSpecification* plotspec);

  /**
   * Destructor
   */
  virtual ~CopasiPlot();

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
   * Save tab delimited data to file
   * @param const std::string & filename
   * @return bool success
   */
  bool saveData(const std::string & filename);

  /**
   * Shows or hide all curves depending on whether visibility is false or true
   * @param const bool & visibility
   */
  void setCurvesVisibility(const bool & visibility);

private:
  /**
   * Tell the curves where the data is located. It must be called
   * after reallocating the memory for the curve data.
   */
  void updateCurves(const unsigned C_INT32 & activity, const bool & doHisto);

  /**
   * Redraw the plot
   */
  void updatePlot();

  /**
   * Clear all allocate buffers and set reset values
   */
  void clearBuffers();

  /**
   * Set the units of the indexed axis based on the
   * type of the object.
   * @param const C_INT32 & index
   * @param const CCopasiObject * pObject
   */
  void setAxisUnits(const C_INT32 & index,
                    const CCopasiObject * pObject);

private slots:
  /**
   * Slot used to turn curves on and of through the legend buttons.
   * @param QwtPlotItem *item
   * @param bool on
   */
  void showCurve(QwtPlotItem *item, bool on);

private:
  /**
   * The value for missing objects
   */
  static C_FLOAT64 MissingValue;

  /**
   * Vector that contains pointers to vectors of data in the selected columns.
   */
  std::vector< std::vector< CVector< double > * > > mData;

  /**
   * Vector of pointers to the current object values
   */
  std::vector< std::vector< const C_FLOAT64 * > > mObjectValues;

  /**
   * Vector of bool indicating whether the current object value is integer
   */
  std::vector< std::vector< bool > > mObjectInteger;

  /**
   * The order of 2d curve objects used when the data is saved.
   * The first object in each vector is the object for the X axis.
   */
  std::vector< std::vector < const CCopasiObject * > > mSaveCurveObjects;

  /**
   * The order of histogram objects used when the data is saved.
   */
  std::vector< const CCopasiObject * > mSaveHistogramObjects;

  /**
   * Vector of actual data lines in the local buffers
   */
  std::vector< unsigned C_INT32 > mDataSize;

  /**
   * Map curve and channel to index pair indicating where the data is stored.
   */
  std::vector< std::vector< std::pair < Activity, unsigned C_INT32 > > > mDataIndex;

  /**
   * Map activity and object to index indicating where data is stored within
   * the current activity.
   */
  std::map< Activity, std::map< const CCopasiObject *, unsigned C_INT32 > > mObjectIndex;

  /**
   * The list of curves
   */
  std::vector<QwtPlotCurve*> mCurves;

  /**
   * A map between a specification identified by its key and a curve
   */
  std::map< std::string, QwtPlotCurve * > mCurveMap;

  /**
   * Vector of type of each item (curve)
   */
  std::vector<CPlotItem::Type> mCurveTypes;

  /**
   * Vector of the activity of each item (curve)
   */
  std::vector<Activity> mCurveActivities;

  /**
   * List of the histograms (if there are some)
   */
  std::vector<CHistogram> mHistograms;

  /**
   * Map of curve to the index to the corresponding histogram.
   */
  std::vector<C_INT32> mHistoIndices;

  /**
   * Count af data lines recorded during activity BEFORE.
   */
  unsigned C_INT32 mDataBefore;

  /**
   * Count af data lines recorded during activity DURING.
   */
  unsigned C_INT32 mDataDuring;

  /**
   * Count af data lines recorded during activity AFTER.
   */
  unsigned C_INT32 mDataAfter;

  /**
   * Flag indicating whether there are any curves recording
   * data during activity BEFORE.
   */
  bool mHaveBefore;

  /**
   * Flag indicating whether there are any curves recording
   * data during activity DURING.
   */
  bool mHaveDuring;

  /**
   * Flag indicating whether there are any curves recording
   * data during activity AFTER.
   */
  bool mHaveAfter;

  /**
   * Pointer to the specification for the plot.
   */
  const CPlotSpecification * mpPlotSpecification;

  /**
   * The next time a plot update is performed
   */
  CCopasiTimeVariable mNextPlotTime;

  /**
   * Indicates whether redrawing/updating shall be suppressed during initialization.
   */
  bool mIgnoreUpdate;

public:
  /**
   * Pointer to the zooming engine for the plot.
   */
  QwtPlotZoomer * mpZoomer;
};

#endif // COPASIPLOT_H
