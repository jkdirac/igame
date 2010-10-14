/**
 * @file    LibXMLTranscode.h
 * @brief   Transcodes a LibXML xmlChar string to UTF-8.
 * @author  Ben Bornstein
 *
 * $Id: LibXMLTranscode.h 9686 2009-06-30 17:37:35Z ajouraku $
 * $HeadURL: https://sbml.svn.sourceforge.net/svnroot/sbml/branches/rel-4-0-0/src/xml/LibXMLTranscode.h $
 *
 *<!---------------------------------------------------------------------------
 * This file is part of libSBML.  Please visit http://sbml.org for more
 * information about SBML, and the latest version of libSBML.
 *
 * Copyright 2005-2009 California Institute of Technology.
 * Copyright 2002-2005 California Institute of Technology and
 *                     Japan Science and Technology Corporation.
 * 
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation.  A copy of the license agreement is provided
 * in the file named "LICENSE.txt" included with this software distribution and
 * also available online as http://sbml.org/software/libsbml/license.html
 *----------------------------------------------------------------------- -->*/

#ifndef LibXMLTranscode_h
#define LibXMLTranscode_h

#ifdef __cplusplus

#include <string>
#include <libxml/parser.h>
#include <sbml/xml/XMLExtern.h>

LIBSBML_CPP_NAMESPACE_BEGIN

/** @cond doxygen-libsbml-internal */

/**
 * Transcodes a LibXML xmlChar* string to UTF-8.  This class offers
 * implicit conversion to a C++ string.
 */
class LibXMLTranscode
{
public:

  LibXMLTranscode (const xmlChar* s, int len = -1) :
    mBuffer(reinterpret_cast<const char*>(s)), mLen(len), mReplaceNCR(false) { }

  LibXMLTranscode (const xmlChar* s, bool replace, int len = -1) :
    mBuffer(reinterpret_cast<const char*>(s)), mLen(len), mReplaceNCR(replace) { }

  ~LibXMLTranscode () { }

  operator std::string ();

private:

  const char* mBuffer;
  int         mLen;
  bool        mReplaceNCR;

  LibXMLTranscode  ();
  LibXMLTranscode  (const LibXMLTranscode&);
  LibXMLTranscode& operator= (const LibXMLTranscode&);

};

/** @endcond doxygen-libsbml-internal */

LIBSBML_CPP_NAMESPACE_END

#endif  /* __cplusplus */
#endif  /* LibXMLTranscode_h */
