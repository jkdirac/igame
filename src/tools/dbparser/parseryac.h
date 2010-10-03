
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
     TOK_NODENAME = 258,
     VALUESTRING = 259,
     QSTRING = 260,
     SSTRING = 261,
     TOKEN_COMMENT = 262,
     TOKEN_IDENTIFIER = 263,
     TOK_GROUPSTART = 264,
     TOK_GROUPEND = 265,
     TOK_MODULE = 266,
     TOK_ID = 267,
     TOK_NAME = 268,
     TOK_CLASS = 269,
     TOK_MODULE_REGID = 270,
     TOK_MODULE_UR = 271,
     TOK_SHORT_DESC = 272,
     TOK_PARAMETERS = 273,
     TOK_MODULE_FW_PROM_EFF = 274,
     TOK_MODULE_EV_PROM_EFF = 275,
     TOK_MODULE_FW_TERM_EFF = 276,
     TOK_MODULE_REV_TERM_EFF = 277,
     TOK_MODULE_RBS_EFF = 278,
     TOK_MODULE_REV_RBS_EFF = 279,
     TOK_MODULE_FW_START_CONDON = 280,
     TOK_MODULE_REV_START_CONDON = 281,
     TOK_MODULE_FW_STOP_CONDON = 282,
     TOK_MODULE_REV_STOP_CONDON = 283,
     TOK_MODULE_LISTOFSPECIESLINKS = 284,
     TOK_MODULE_SPECIESLINKS = 285,
     TOK_TYPE = 286,
     TOK_DIRECTION = 287,
     TOK_FILENAME = 288
   };
#endif
/* Tokens.  */
#define TOK_NODENAME 258
#define VALUESTRING 259
#define QSTRING 260
#define SSTRING 261
#define TOKEN_COMMENT 262
#define TOKEN_IDENTIFIER 263
#define TOK_GROUPSTART 264
#define TOK_GROUPEND 265
#define TOK_MODULE 266
#define TOK_ID 267
#define TOK_NAME 268
#define TOK_CLASS 269
#define TOK_MODULE_REGID 270
#define TOK_MODULE_UR 271
#define TOK_SHORT_DESC 272
#define TOK_PARAMETERS 273
#define TOK_MODULE_FW_PROM_EFF 274
#define TOK_MODULE_EV_PROM_EFF 275
#define TOK_MODULE_FW_TERM_EFF 276
#define TOK_MODULE_REV_TERM_EFF 277
#define TOK_MODULE_RBS_EFF 278
#define TOK_MODULE_REV_RBS_EFF 279
#define TOK_MODULE_FW_START_CONDON 280
#define TOK_MODULE_REV_START_CONDON 281
#define TOK_MODULE_FW_STOP_CONDON 282
#define TOK_MODULE_REV_STOP_CONDON 283
#define TOK_MODULE_LISTOFSPECIESLINKS 284
#define TOK_MODULE_SPECIESLINKS 285
#define TOK_TYPE 286
#define TOK_DIRECTION 287
#define TOK_FILENAME 288




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 16 "parser.y"
 char    *string;     /* string buffer */
    int    integer;          /* int value */



/* Line 1676 of yacc.c  */
#line 124 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


