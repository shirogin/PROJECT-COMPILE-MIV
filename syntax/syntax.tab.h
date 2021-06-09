
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
     CODE = 258,
     START = 259,
     END = 260,
     CONST = 261,
     IDF = 262,
     EOI = 263,
     PROD = 264,
     SEPARATOR = 265,
     BRACKETS_B = 266,
     BRACKETS_E = 267,
     C_BRACKETS_B = 268,
     C_BRACKETS_E = 269,
     PARENTHESIS_B = 270,
     PARENTHESIS_E = 271,
     TYPE = 272,
     INTEGER = 273,
     FLOAT = 274,
     CHAR = 275,
     STRING = 276,
     WHEN = 277,
     OTHERWISE = 278,
     WHILE = 279,
     EXECUTE = 280,
     DO = 281,
     AFFECT = 282,
     ARTH_OP = 283,
     LOGIC_OP = 284
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 25 ".\\syntax.y"

    int myINT;
    char myCHAR;
    char mySTRING[100];
    float myFLOAT;



/* Line 1676 of yacc.c  */
#line 90 "syntax.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

