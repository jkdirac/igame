// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/function/CEvaluationParser_yacc.h,v $
//   $Revision: 1.24 $
//   $Name: Build-31 $
//   $Author: shoops $
//   $Date: 2009/07/30 21:08:33 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/* A Bison parser, made by GNU Bison 2.0.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
/* Put the tokens into the symbol table, so that GDB and other debuggers
   know about them.  */
enum yytokentype
{
  TOKEN_NUMBER = 258,
  TOKEN_VARIABLE = 259,
  TOKEN_CALL = 260,
  TOKEN_FUNCTION = 261,
  TOKEN_FUNCTION_2 = 262,
  TOKEN_SIGN = 263,
  TOKEN_OPERATOR_POWER = 264,
  TOKEN_OPERATOR_MULTIPLY = 265,
  TOKEN_OPERATOR_MODULUS = 266,
  TOKEN_OPERATOR_PLUS = 267,
  TOKEN_LOGICAL_CHOICE = 268,
  TOKEN_LOGICAL_VALUE = 269,
  TOKEN_LOGICAL_NOT = 270,
  TOKEN_LOGICAL_OR = 271,
  TOKEN_LOGICAL_XOR = 272,
  TOKEN_LOGICAL_AND = 273,
  TOKEN_LOGICAL_EQ = 274,
  TOKEN_LOGICAL_NE = 275,
  TOKEN_LOGICAL_GT = 276,
  TOKEN_LOGICAL_GE = 277,
  TOKEN_LOGICAL_LT = 278,
  TOKEN_LOGICAL_LE = 279,
  TOKEN_STRUCTURE_OPEN = 280,
  TOKEN_STRUCTURE_VECTOR_OPEN = 281,
  TOKEN_STRUCTURE_COMMA = 282,
  TOKEN_STRUCTURE_CLOSE = 283,
  TOKEN_STRUCTURE_VECTOR_CLOSE = 284
};
#endif
#define TOKEN_NUMBER 258
#define TOKEN_VARIABLE 259
#define TOKEN_CALL 260
#define TOKEN_FUNCTION 261
#define TOKEN_FUNCTION_2 262
#define TOKEN_SIGN 263
#define TOKEN_OPERATOR_POWER 264
#define TOKEN_OPERATOR_MULTIPLY 265
#define TOKEN_OPERATOR_MODULUS 266
#define TOKEN_OPERATOR_PLUS 267
#define TOKEN_LOGICAL_CHOICE 268
#define TOKEN_LOGICAL_VALUE 269
#define TOKEN_LOGICAL_NOT 270
#define TOKEN_LOGICAL_OR 271
#define TOKEN_LOGICAL_XOR 272
#define TOKEN_LOGICAL_AND 273
#define TOKEN_LOGICAL_EQ 274
#define TOKEN_LOGICAL_NE 275
#define TOKEN_LOGICAL_GT 276
#define TOKEN_LOGICAL_GE 277
#define TOKEN_LOGICAL_LT 278
#define TOKEN_LOGICAL_LE 279
#define TOKEN_STRUCTURE_OPEN 280
#define TOKEN_STRUCTURE_VECTOR_OPEN 281
#define TOKEN_STRUCTURE_COMMA 282
#define TOKEN_STRUCTURE_CLOSE 283
#define TOKEN_STRUCTURE_VECTOR_CLOSE 284

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE CEvaluationParserlval;
