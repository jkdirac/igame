// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/layoutUI/CQGLViewport.h,v $
//   $Revision: 1.8 $
//   $Name: Build-31 $
//   $Author: gauges $
//   $Date: 2010/02/03 13:53:00 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <QFrame>

class CQGLNetworkPainter;
class QScrollBar;
class CLayout;
class QResizeEvent;

/**
 * This class is supposed to act as a sort of scrollview for a
 * CQGLNetworkPainter.
 */
class CQGLViewport : public QFrame
{
  Q_OBJECT

protected:
  QScrollBar* mpVerticalScrollbar;
  QScrollBar* mpHorizontalScrollbar;
  CQGLNetworkPainter* mpNetworkPainter;

public:
  /**
   * Constructor.
   */
  CQGLViewport(QWidget* pParent = 0, Qt::WFlags f = 0);

  /**
   * Destructor.
   */
  virtual ~CQGLViewport();

  const CQGLNetworkPainter* getPainter() const;

  CQGLNetworkPainter* getPainter();

  /**
   * Pass the layout on to the network painters createGraph and set the
   * scrollbar ranges.
   */
  void createGraph(CLayout *lP);

  /**
   * Sets the zoom factor on the network painter and updates the
   *scrollbars.
   */
  void setZoomFactor(double zoom);

  void resetView();

  /**
   * Returns whether the layout window is in circle (animation mode) or not.
   * This method only calls the corresponding method in the contained network
   * painter.
   */
  bool isCircleMode() const;

protected:
  virtual void resizeEvent(QResizeEvent* e);

  void updateScrollbars();

protected slots:
  void slotVValueChanged(int value);
  void slotHValueChanged(int value);

public slots:
  void updateWidget();
};
