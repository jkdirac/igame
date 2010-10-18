/**
 * @file    LibXMLAttributes.h
 * @brief   Creates new XMLAttributes from "raw" LibXML attributes.
 * @author  Ben Bornstein
 *
 * $Id: LibXMLAttributes.h 9686 2009-06-30 17:37:35Z ajouraku $
 * $HeadURL: https://sbml.svn.sourceforge.net/svnroot/sbml/branches/rel-4-0-0/src/xml/LibXMLAttributes.h $
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

#ifndef LibXMLAttributes_h
#define LibXMLAttributes_h

#ifdef __cplusplus

#include <string>

#include <libxml/parser.h>
#include <sbml/xml/XMLAttributes.h>

LIBSBML_CPP_NAMESPACE_BEGIN

/** @cond doxygen-libsbml-internal */

class LibXMLAttributes : public XMLAttributes
{
public:

  /**
   * Creates a new XMLAttributes set from the given "raw" LibXML attributes.
   */
  LibXMLAttributes (  const xmlChar** attributes
		    , const xmlChar*  elementName
		    , const unsigned int& size);


  /**
   * Destroys this LibXMLAttributes set.
   */
  virtual ~LibXMLAttributes ();
};

/** @endcond doxygen-libsbml-internal */

LIBSBML_CPP_NAMESPACE_END

#endif  /* __cplusplus */
#endif  /* LibXMLAttributes_h */
