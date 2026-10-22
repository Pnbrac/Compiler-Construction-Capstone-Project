/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

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
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
     ID = 258,
     INTCONST = 259,
     CHARCONST = 260,
     KWD_INT = 261,
     KWD_CHAR = 262,
     KWD_VOID = 263,
     KWD_WHILE = 264,
     KWD_RETURN = 265,
     KWD_IF = 266,
     KWD_ELSE = 267,
     KWD_FOR = 268,
     LSQ_BRKT = 269,
     RSQ_BRKT = 270,
     LCRLY_BRKT = 271,
     RCRLY_BRKT = 272,
     LPAREN = 273,
     RPAREN = 274,
     COMMA = 275,
     SEMICLN = 276,
     OPER_LTE = 277,
     OPER_LT = 278,
     OPER_DIV = 279,
     OPER_GT = 280,
     OPER_GTE = 281,
     OPER_EQ = 282,
     OPER_ASGN = 283,
     OPER_NEQ = 284,
     OPER_ADD = 285,
     OPER_SUB = 286,
     OPER_MUL = 287,
     ERROR = 288,
     ILLEGAL_TOK = 289,
     LOWER_THAN_ELSE = 290
   };
#endif
/* Tokens.  */
#define ID 258
#define INTCONST 259
#define CHARCONST 260
#define KWD_INT 261
#define KWD_CHAR 262
#define KWD_VOID 263
#define KWD_WHILE 264
#define KWD_RETURN 265
#define KWD_IF 266
#define KWD_ELSE 267
#define KWD_FOR 268
#define LSQ_BRKT 269
#define RSQ_BRKT 270
#define LCRLY_BRKT 271
#define RCRLY_BRKT 272
#define LPAREN 273
#define RPAREN 274
#define COMMA 275
#define SEMICLN 276
#define OPER_LTE 277
#define OPER_LT 278
#define OPER_DIV 279
#define OPER_GT 280
#define OPER_GTE 281
#define OPER_EQ 282
#define OPER_ASGN 283
#define OPER_NEQ 284
#define OPER_ADD 285
#define OPER_SUB 286
#define OPER_MUL 287
#define ERROR 288
#define ILLEGAL_TOK 289
#define LOWER_THAN_ELSE 290




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 147 "src/parser.y"
{
    int value;
    struct treenode *node;
    char *strval;
}
/* Line 1529 of yacc.c.  */
#line 125 "obj/y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

