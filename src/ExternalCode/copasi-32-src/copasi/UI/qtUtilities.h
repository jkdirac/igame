// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/UI/qtUtilities.h,v $
//   $Revision: 1.11 $
//   $Name: Build-31 $
//   $Author: shoops $
//   $Date: 2009/01/08 16:07:44 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_qtUtilities
#define COPASI_qtUtilities

#include <qstring.h>
#include "utilities/CCopasiParameter.h"

class QStringList;
class CCopasiParameterGroup;

/**
 * Retrieve a parameter from a parameter group and convert it to a QString.
 * @param const CCopasiParameterGroup * group
 * @param const unsigned C_INT32 & index
 * @param CCopasiParameter::Type * type (default: NULL)
 * @return QString value
 */
QString getParameterValue(const CCopasiParameterGroup * group,
                          const unsigned C_INT32 & index,
                          CCopasiParameter::Type * type = NULL);
/**
 * Retrieve a parameter from a parameter group and convert it to a QString.
 * @param const CCopasiParameterGroup * group
 * @param const std::string & name
 * @param CCopasiParameter::Type * type (default: NULL)
 * @return QString value
 */
QString getParameterValue(const CCopasiParameterGroup * group,
                          const std::string & name,
                          CCopasiParameter::Type * type = NULL);
/**
 * Set a parameter of a parameter group from a value given as a QString.
 * Success = true is returned when the set operation was succesful, i.e.,
 * value == getParameterValue.
 * @param CCopasiParameterGroup * group
 * @param const std::string & name
 * @param const QString & value
 * @return bool success.
 */
bool setParameterValue(CCopasiParameterGroup * group,
                       const unsigned C_INT32 & index,
                       const QString & value);

/**
 * Set a parameter of a parameter group from a value given as a QString.
 * Success = true is returned when the set operation was succesful, i.e.,
 * value == getParameterValue.
 * @param CCopasiParameterGroup * group
 * @param const unsigned C_INT32 & index
 * @param const QString & value
 * @return bool success.
 */
bool setParameterValue(CCopasiParameterGroup * group,
                       const std::string & name,
                       const QString & value);

/**
 * Convert a utf8 encoded std::string to a QString
 */
#define FROM_UTF8(__x) QString::fromUtf8((__x).c_str())
#define TO_UTF8(__x) (__x).toUtf8().data()

/**
 * Checks whether the file exists. If the file exist the user
 * is prompted whether to overwrite the file. The return value is
 * one of QMessageBox::Yes, QMessageBox::No, or QMessageBox::Cancel.
 * If the file does not exist QMessageBox::Yes is returned.
 * param const QString & file
 * @return C_INT32 overwrite
 */
C_INT32 checkSelection(const QString & file);

/**
 * This converts a std::vector<std::string> into a QStringList
 */
void vectorOfStrings2QStringList(std::vector<std::string> vs, QStringList & qsl);

#endif // COPASI_qtUtilities
