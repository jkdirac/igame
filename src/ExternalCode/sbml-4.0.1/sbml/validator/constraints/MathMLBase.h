/**
 * @file    MathMLBase.h
 * @brief   Base class for MathML Constraints
 * @author  Sarah Keating
 *
 * $Id: MathMLBase.h 9686 2009-06-30 17:37:35Z ajouraku $
 * $HeadURL: https://sbml.svn.sourceforge.net/svnroot/sbml/branches/rel-4-0-0/src/validator/constraints/MathMLBase.h $
 */
/* Copyright 2005 California Institute of Technology and Japan Science and
 * Technology Corporation.
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation.  A copy of the license agreement is
 * provided in the file named "LICENSE.txt" included with this software
 * distribution.  It is also available online at
 * http://sbml.org/software/libsbml/license.html
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 */


#ifndef MathMLBase_h
#define MathMLBase_h


#ifdef __cplusplus


#include <string>
#include <math.h>

#include <sbml/validator/VConstraint.h>
#include <sbml/util/memory.h>
#include "IdList.h"

LIBSBML_CPP_NAMESPACE_BEGIN

class ASTNode;


class MathMLBase: public TConstraint<Model>
{
public:

  /**
   * Creates a new Constraint with the given id.
   */
  MathMLBase (unsigned int id, Validator& v);

  /**
   * Destroys this Constraint.
   */
  virtual ~MathMLBase ();


protected:

  /**
   * loops through all occurences of MathML within a model
   */
  void check_(const Model& m, const Model& object);

  /**
   * Checks the MathML of the ASTnode 
   * is appropriate for the function being performed
   *
   * If an inconsistency is found, an error message is logged.
   */
  virtual void checkMath (const Model& m, const ASTNode& node, const SBase & sb) = 0;
 
  /**
   * Checks the MathML of the children of ASTnode 
   * forces recursion through the AST tree
   *
   * calls checkMath for each child
   */
  void checkChildren (const Model& m, const ASTNode& node, const SBase & sb);
 
  /**
   * Checks the MathML of a function definition 
   * as applied to the arguments supplied to it
   *
   * creates an ASTNode of the function with appropriate arguments
   * and calls checkMath
   */
  void checkFunction (const Model& m, const ASTNode& node, const SBase & sb);
  
  /**
   * @return the fieldname to use logging constraint violations.  If not
   * overridden, "math" is returned.
   */
  virtual const char* getFieldname ();

  /**
   * @return the preamble to use when logging constraint violations.  The
   * preamble will be prepended to each log message.  If not overriden,
   * returns an empty string.
   */
  virtual const char* getPreamble ();

  /**
   * @return the error message to use when logging constraint violations.
   * This method is called by logFailure.
   *
   * If at all possible please use getPreamble() and getFieldname() when
   * constructing error messages.  This will help to make your constraint
   * easily customizable.
   */
  virtual const std::string
  getMessage (const ASTNode& node, const SBase& object) = 0;

  /**
   * @return the typename of the given SBase object.
   */
  const char* getTypename (const SBase& object);

  /**
   * Logs a message that the math (and its corresponding object) have
   * failed to satisfy this constraint.
   */
  void logMathConflict (const ASTNode& node, const SBase& object);

  /**
   * Checks that the math will return a numeric result
   * forces recursion thru the AST tree
   * 
   * @returns true if produces a numeric; false otherwise
   */
  bool returnsNumeric(const Model &, const ASTNode* node);

  /**
   * Checks that the MathML of a function definition 
   * as applied to the arguments supplied to it will return a numeric
   *
   * creates an ASTNode of the function with appropriate arguments
   * and calls returnsNumeric
   * 
   * @returns true if produces a numeric; false otherwise
   */
  bool checkNumericFunction (const Model& m, const ASTNode* node);

  /**
  * Checks that the math will uses numeric functions 
  * forces recursion thru the AST tree
  * 
  * returns true if numeric functions; false otherwise
  */
  bool isNumericFunction(const Model & m, const ASTNode* node);

 /* occasionally a mathML constraint will need to know which reaction
   * the kineticLaw it is testing comes from
   * or whether the math from an event is a trigger or a delay
   *
   * this information isnt available from just the math and the model
   * and so these flags provide it
   */
  unsigned int mKLCount;
  unsigned int mIsTrigger;

  IdList mLocalParameters;

};

//void
//ReplaceArgument(ASTNode * math, const ASTNode * bvar, ASTNode * arg);

LIBSBML_CPP_NAMESPACE_END

#endif  /* __cplusplus */
#endif  /* MathMLBase_h */
