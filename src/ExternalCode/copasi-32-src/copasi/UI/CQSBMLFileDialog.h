// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/UI/CQSBMLFileDialog.h,v $
//   $Revision: 1.4.2.1 $
//   $Name: Build-31 $
//   $Author: gauges $
//   $Date: 2010/03/03 09:14:09 $
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

#ifndef CQSBML_FILE_DIALOG
#define CQSBML_FILE_DIALOG

#include <qstring.h>

#include <vector>
#include <utility>
#include "copasi.h"
//Added by qt3to4:
#include <QLabel>

class QWidget;

class CQSBMLFileDialog
{
public:
  static
  std::pair<QString, std::pair<unsigned C_INT32, unsigned C_INT32> > getSaveFileName(QWidget * parent,
      const char * name,
      const QString & startWith,
      const QString & caption,
      unsigned int sbmlLevel = 2,
      unsigned int sbmlVersion = 4);
};

#endif // CQSBML_FILE_DIALOG
