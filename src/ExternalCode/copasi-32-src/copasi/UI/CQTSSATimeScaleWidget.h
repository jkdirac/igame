// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/UI/CQTSSATimeScaleWidget.h,v $
//   $Revision: 1.2 $
//   $Name: Build-31 $
//   $Author: shoops $
//   $Date: 2008/12/18 19:57:33 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQTSSATIMESCALEWIDGET_H
#define CQTSSATIMESCALEWIDGET_H

#include <qwidget.h>
#include <qlayout.h>
//Added by qt3to4:
#include <QPaintEvent>
#include <Q3VBoxLayout>
#include "utilities/CVector.h"
#include <qslider.h>
#include <qpainter.h>

class PaintWidget : public QWidget
  {
    Q_OBJECT

  public:
    PaintWidget(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0);
    ~PaintWidget();

    void paintTimeScale(int select);

    CVector< C_FLOAT64> mVector;
    bool mClear;

  protected:
    void paintEvent(QPaintEvent *);

  private:
    int mSelection;
  };

class CQTSSATimeScaleWidget : public QWidget
  {
    Q_OBJECT

  public:
    CQTSSATimeScaleWidget(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0);
    ~CQTSSATimeScaleWidget();

    void paintTimeScale(CVector< C_FLOAT64> vector);
    void clearWidget();

  public slots:
    void changedInterval();

  private:
    Q3VBoxLayout * mpVLayout;
    PaintWidget * mpPaintWidget;
    QSlider * mpSlider;
  };

#endif // CQTSSATIMESCALEWIDGET_H
