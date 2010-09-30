
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TOKEN_EQU = 258,
     TOKEN_NEQU = 259,
     TOKEN_LESS_EQ = 260,
     TOKEN_MORE_EQ = 261,
     TOKEN_AND = 262,
     TOKEN_OR = 263,
     TOKEN_PLUS = 264,
     TOKEN_MINUS = 265,
     TOKEN_TIMES = 266,
     TOKEN_DIVIDE = 267,
     TOKEN_IDENTIFIER = 268,
     TOKEN_NUM = 269,
     TOKEN_REAL = 270,
     TOKEN_LEFT_BRACKET = 271,
     TOKEN_RIGHT_BRACKET = 272
   };
#endif
/* Tokens.  */
#define TOKEN_EQU 258
#define TOKEN_NEQU 259
#define TOKEN_LESS_EQ 260
#define TOKEN_MORE_EQ 261
#define TOKEN_AND 262
#define TOKEN_OR 263
#define TOKEN_PLUS 264
#define TOKEN_MINUS 265
#define TOKEN_TIMES 266
#define TOKEN_DIVIDE 267
#define TOKEN_IDENTIFIER 268
#define TOKEN_NUM 269
#define TOKEN_REAL 270
#define TOKEN_LEFT_BRACKET 271
#define TOKEN_RIGHT_BRACKET 272




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 15 "cacu.y"
 
    char *string;     /* string buffer */
    int    integer;          /* int value */
    double real;



/* Line 1676 of yacc.c  */
#line 94 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


