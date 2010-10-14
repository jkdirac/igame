/* Begin CVS Header
   $Source: /fs/turing/cvs/copasi_dev/copasi/utilities/utility.h,v $
   $Revision: 1.23.2.1 $
   $Name: Build-31 $
   $Author: shoops $
   $Date: 2010/06/04 14:24:16 $
   End CVS Header */

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

#ifndef COPASI_utilities
#define COPASI_utilities

#include <string>
#include <string.h>
// #include <stdio.h>
#include <stdarg.h>

#define INITIALTEXTSIZE 1024

struct tm;

/**
 * Returns the time pointed to by pTime in ISO format
 */
std::string ISODateTime(tm * pTime);

/**
 * Returns the current local time in ISO format
 */
std::string LocalTimeStamp();

/**
 * Returns the current time in ISO format
 */
std::string UTCTimeStamp();

/**
 * Check whether the given string represents a number
 * @param const std::string & str
 * @return bool isNumber
 */
bool isNumber(const std::string & str);

/**
 *  sprintf like function for strings
 *  @param "const char *" format sprintf like format string
 *  @param ...
 *  @return "string"
 */
std::string StringPrint(const char * format, ...);

/**
 * Unesacape a quoted name. If the name is surrounded by quotes
 * these are removed and included escape sequences '\.' are reduced
 * to '.' else the name is returned unmodified.
 * @param const std::string & name
 * @return std::string unQuote
 */
std::string unQuote(const std::string & name);

/**
 * Surround a name with quotes if the name contains a space or
 * double quote else the name is returned unmodified. In the
 * quoted name " and \ are escaped. The parameter additionalEscapes
 * forces quotes around names containing any of the character in the
 * parameter.
 * @param const std::string & name
 * @param const std::string & additionalEscapes (default: "")
 * @return std::string quote
 */
std::string quote(const std::string & name,
                  const std::string & additionalEscapes = "");

/*
 * Fixes a string to be a SName element from SBML
 * (this is a destructive function, some changes are irreversible)
 *
 */
void FixSName(const std::string &original, std::string &fixed)
;

/*
 * Fixes a string to a XHTML valid equivalent
 */
void FixXHTML(const std::string &original, std::string &fixed)
;

/**
  * Convert an attribute to enum. If attribute is NULL
  * or no matching name is found the parameter enumDefault is returned.
  * Note: enumNames must be zero terminated.
  * @param const char * attribute
  * @param const char ** enumNames
  * @param const CType & enumDefault
  * @return CType enum
  */
template <class CType> CType toEnum(const char * attribute,
                                    const char ** enumNames,
                                    const CType & enumDefault)
{
  if (!attribute) return enumDefault;

  for (int i = 0; *enumNames; i++, enumNames++)
    if (!strcmp(attribute, *enumNames)) return static_cast< CType >(i);

  return enumDefault;
}

/**
 * Convert a utf8 string to the local used code page
 * This only has an effect on Windows as utf8 is the local
 * code page everywhere else
 * @param const std::string & utf8
 * @return std::string locale
 */
std::string utf8ToLocale(const std::string & utf8);

/**
 * Convert a string in the local used code page to utf8
 * This only has an effect on Windows as utf8 is the local
 * code page everywhere else
 * @param const std::string & locale
 * @return std::string utf8
 */
std::string localeToUtf8(const std::string & locale);

/**
 * Convert a character sequence to a double
 * @param const char * str
 * @param char const ** pTail (default: NULL)
 * @return double
 */
double strToDouble(const char * str,
                   char const ** pTail = NULL);

#endif // COPASI_utilities
