/**
 * @cond doxygen-libsbml-internal
 *
 * @file    IdentifierConsistencyValidator.h
 * @brief   Performs consistency checks on an SBML model
 * @author  Ben Bornstein
 *
 * $Id: IdentifierConsistencyValidator.h 8704 2009-01-04 02:26:05Z mhucka $
 * $HeadURL: https://sbml.svn.sourceforge.net/svnroot/sbml/trunk/libsbml/src/validator/IdentifierConsistencyValidator.h $
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

#ifndef IdentifierConsistencyValidator_h
#define IdentifierConsistencyValidator_h


#ifdef __cplusplus


#include <sbml/validator/Validator.h>


class IdentifierConsistencyValidator: public Validator
{
public:

  IdentifierConsistencyValidator () :
    Validator( LIBSBML_CAT_IDENTIFIER_CONSISTENCY ) { }

  virtual ~IdentifierConsistencyValidator () { }

  /**
   * Initializes this Validator with a set of Constraints.
   */
  virtual void init ();
};


#endif  /* __cplusplus */
#endif  /* ConsistencyValidator_h */


/** @endcond doxygen-libsbml-internal */
