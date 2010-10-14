/**
 * @file    libsbml-version.h
 * @brief   Define libSBML version numbers for access from client software.
 * @author  Michael Hucka
 *
 * $Id: libsbml-version.h.in 8704 2009-01-04 02:26:05Z mhucka $
 * $HeadURL: https://sbml.svn.sourceforge.net/svnroot/sbml/trunk/libsbml/src/common/libsbml-version.h.in $
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
 *------------------------------------------------------------------------- -->
 */

#ifndef LIBSBML_VERSION_H
#define LIBSBML_VERSION_H 

#include <sbml/common/extern.h>

/**
 * LIBSBML_DOTTED_VERSION:
 *
 * A version string of the form "1.2.3".
 */
#define LIBSBML_DOTTED_VERSION	"3.4.1"

/**
 * LIBSBML_VERSION:
 *
 * The version as an integer: version 1.2.3 becomes 10203.  Since the major
 * number comes first, the overall number will always increase when a new
 * libSBML is released, making it easy to use less-than and greater-than
 * comparisons when testing versions numbers.
 */
#define LIBSBML_VERSION		30401

/**
 * LIBSBML_VERSION_STRING:
 *
 * The numeric version as a string: version 1.2.3 becomes "10203".
 */
#define LIBSBML_VERSION_STRING	"30401"


BEGIN_C_DECLS

/**
 * Returns the libSBML version as an integer: version 1.2.3 becomes 10203.
 *
 * @return the libSBML version as an integer: version 1.2.3 becomes 10203.
 */
LIBSBML_EXTERN
int 
getLibSBMLVersion () ;


/**
 * Returns the libSBML version as a string of the form "1.2.3".
 *
 * @return the libSBML version as a string of the form "1.2.3".
 */
LIBSBML_EXTERN
const char* 
getLibSBMLDottedVersion ();


/**
 * Returns the libSBML version as a string: version 1.2.3 becomes "10203".
 *
 * @return the libSBML version as a string: version 1.2.3 becomes "10203".
 */
LIBSBML_EXTERN
const char* 
getLibSBMLVersionString ();

END_C_DECLS

#endif  /* LIBSBML_VERSION_H */
