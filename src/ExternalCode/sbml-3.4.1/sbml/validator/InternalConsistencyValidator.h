/**
 * @cond doxygen-libsbml-internal
 *
 * @file    InternalConsistencyValidator.h
 * @brief   Checks the validity of internal respresentation of SBML model
 * @author  Sarah Keating
 *
 * $Id: InternalConsistencyValidator.h 8704 2009-01-04 02:26:05Z mhucka $
 * $HeadURL: https://sbml.svn.sourceforge.net/svnroot/sbml/trunk/libsbml/src/validator/InternalConsistencyValidator.h $
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

#ifndef InternalConsistencyValidator_h
#define InternalConsistencyValidator_h


#ifdef __cplusplus


#include <sbml/validator/Validator.h>
#include <sbml/SBMLError.h>


class InternalConsistencyValidator: public Validator
{
public:

  InternalConsistencyValidator () : Validator( LIBSBML_CAT_INTERNAL_CONSISTENCY ) { }

  virtual ~InternalConsistencyValidator () { }

  /**
   * Initializes this Validator with a set of Constraints.
   */
  virtual void init ();
};


#endif  /* __cplusplus */
#endif  /* InternalConsistencyValidator_h */


/** @endcond doxygen-libsbml-internal */
