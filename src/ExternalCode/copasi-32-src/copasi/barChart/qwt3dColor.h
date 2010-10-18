// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/barChart/qwt3dColor.h,v $
//   $Revision: 1.1 $
//   $Name: Build-31 $
//   $Author: akoenig $
//   $Date: 2007/11/12 17:01:07 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef BAR_COLOR_H
#define BAR_COLOR_H

#include "qwt3d_plot.h"

class QWT3D_EXPORT BarColor : public Qwt3D::Color
  {
  public:
    //! Initializes with data and set up a ColorVector with a size of 100 z values (default);
    explicit BarColor(Qwt3D::Plot3D* data, unsigned size = 100, double min = 0, double max = 0);
    Qwt3D::RGBA operator()(double x, double y, double z) const; //!< Receives z-dependend color from ColorVector
    void setColorVector(Qwt3D::ColorVector const& cv);
    void reset(unsigned size = 100); //!< Resets the standard colors;
    void setAlpha(double a); //!< Sets unitary alpha value for all colors

    /**
    *  Creates a color vector used by ColorLegend.
    *  This is essentially a copy from the internal used vector.
    *  \return The vector created
    */
    Qwt3D::ColorVector& createVector(Qwt3D::ColorVector& vec) {vec = colors_; return vec;}

    double maxZ;
    double minZ;
  protected:
    Qwt3D::ColorVector colors_;
    Qwt3D::Plot3D* data_;
  };

#endif // BAR_COLOR_H
