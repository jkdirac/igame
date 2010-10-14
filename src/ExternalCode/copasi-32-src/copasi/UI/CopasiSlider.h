/* Begin CVS Header
 $Source: /fs/turing/cvs/copasi_dev/copasi/UI/CopasiSlider.h,v $
 $Revision: 1.17 $
 $Name: Build-31 $
 $Author: gauges $
 $Date: 2009/07/28 07:33:35 $
 End CVS Header */

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CopasiSlider_H__
#define CopasiSlider_H__

#include <QFrame>
#include <QLabel>

#include "copasi.h"

#include "utilities/CCopasiParameter.h"
#include "utilities/CSlider.h"

class QSlider;
class QWidget;
class CCopasiObject;
class QLabel;
class CCopasiParameterGroup;
class QToolButton;

class CopasiSlider: public QFrame
{
  Q_OBJECT
public:
  CopasiSlider(CSlider* pSlider, QWidget* parent = 0);
  virtual ~CopasiSlider();

  CSlider::Type type() const;
  void setType(CSlider::Type type);

  C_FLOAT64 value() const;
  void setValue(C_FLOAT64 value);
  unsigned C_INT32 minorMajorFactor() const;
  void setMinorMajorFactor(unsigned C_INT32 factor);
  C_FLOAT64 minorTickInterval() const;
  unsigned C_INT32 numMinorTicks() const;
  void setNumMinorTicks(unsigned C_INT32 numMinorTicks);
  void setMinValue(C_FLOAT64 value);
  void setMaxValue(C_FLOAT64 value);
  void setOriginalValue(C_FLOAT64 value);
  C_FLOAT64 minValue() const;
  C_FLOAT64 maxValue() const;
  C_FLOAT64 originalValue() const;
  void updateValue(bool modifyRange);
  CCopasiObject* object() const;
  void setObject(CCopasiObject* object);
  CSlider* getCSlider() const;
  void updateLabel();
  void updateSliderData();
  void resetValue();

public slots:
  void sliderValueChanged(int value);
  void qSliderReleased();
  void qSliderPressed();
  void closeButtonClicked();
  void editButtonClicked();

signals:
  void valueChanged(double);
  void sliderReleased();
  void sliderPressed();
  void closeClicked(CopasiSlider* slider);
  void editClicked(CopasiSlider* slider);

protected:
  CSlider* mpCSlider;
  QSlider* mpQSlider;
  QLabel* mpLabel;
  QToolButton* mpCloseButton;
  QToolButton* mpEditButton;
  bool mValueOutOfRange;

  int calculatePositionFromValue(C_FLOAT64 value);
  C_FLOAT64 calculateValueFromPosition(int position);
};

#endif // CopasiSlider_H__
