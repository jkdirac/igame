// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/barChart/qwt3dScale.h,v $
//   $Revision: 1.4 $
//   $Name: Build-31 $
//   $Author: shoops $
//   $Date: 2009/02/19 15:17:50 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef SCALE_H
#define SCALE_H

#include <qstring.h>
#include <qwt3d_scale.h>
#include <qwt3d_types.h>
#include <qwt3d_autoptr.h>
#include <qwt3d_axis.h>

//! Automatic beautifying of linear scales
class LinearAutoScaler2 : public Qwt3D::LinearAutoScaler
  {
  public:
    int execute2(double& a, double& b, double start, double stop, int ivals);
  };

//! The standard (1:1) mapping class for axis numbering
class ValueScale : public Qwt3D::Scale
  {
    friend class Qwt3D::Axis;
    friend class Qwt3D::qwt3d_ptr<Qwt3D::Scale>;
  protected:
    int autoscale(double& a, double& b, double start, double stop, int ivals);
    //! Returns a new heap based object utilized from qwt3d_ptr
    Qwt3D::Scale* clone() const {return new ValueScale(*this);}
    void calculate();
    LinearAutoScaler2 autoscaler_p2;
  public:
    QString ticLabel(unsigned int idx) const;
  };

class ColumnScale : public ValueScale
  {
    friend class Qwt3D::Axis;
    friend class Qwt3D::qwt3d_ptr<Scale>;
  protected:
    Qwt3D::Scale* clone() const {return new ColumnScale(*this);}
  public:
    ColumnScale(const std::vector<std::string> * vos, int showColumn = -1);
    virtual QString ticLabel(unsigned int idx) const;
    const std::vector<std::string> *mpColumnsDes;
    unsigned int showColumn;
  };

class RowScale : public ValueScale
  {
    friend class Qwt3D::Axis;
    friend class Qwt3D::qwt3d_ptr<Scale>;
  protected:
    Qwt3D::Scale* clone() const {return new RowScale(*this);}
  public:
    RowScale(const std::vector<std::string> * vos, int showRow = -1);
    QString ticLabel(unsigned int idx) const;
    const std::vector<std::string> *mpRowsDes;
    unsigned int showRow;
  };
#endif // SCALE_H
