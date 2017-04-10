/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    NUM_LIT = 259,
    NUM_FLOAT_LIT = 260,
    STRING_LIT = 261,
    BOOL_LIT = 262,
    NL = 263,
    INT = 264,
    FLOAT = 265,
    BOOL = 266,
    STRING = 267,
    VOID = 268,
    DEFINE = 269,
    EQUALS = 270,
    LESSOREQUAL = 271,
    LESSTHAN = 272,
    DIFFERENTTHAN = 273,
    EQUALLESSTHAN = 274,
    EQUALMORETHAN = 275,
    MORETHAN = 276,
    POINT = 277,
    COMMA = 278,
    DOUBLEPOINT = 279,
    END_OF_STMT = 280,
    DO = 281,
    WHILE = 282,
    BREAK = 283,
    NEXT = 284,
    RETURN = 285,
    AND = 286,
    OR = 287,
    NOT = 288,
    ASSIGN = 289,
    SUB = 290,
    SUM = 291,
    MUL = 292,
    DIV = 293,
    MOD = 294,
    POT = 295,
    NEG = 296,
    LCURLYPAR = 297,
    RCURLYPAR = 298,
    LPAR = 299,
    RPAR = 300,
    LRECTPAR = 301,
    RRECTPAR = 302,
    IF = 303,
    ELSE = 304,
    THEN = 305
  };
#endif
/* Tokens.  */
#define ID 258
#define NUM_LIT 259
#define NUM_FLOAT_LIT 260
#define STRING_LIT 261
#define BOOL_LIT 262
#define NL 263
#define INT 264
#define FLOAT 265
#define BOOL 266
#define STRING 267
#define VOID 268
#define DEFINE 269
#define EQUALS 270
#define LESSOREQUAL 271
#define LESSTHAN 272
#define DIFFERENTTHAN 273
#define EQUALLESSTHAN 274
#define EQUALMORETHAN 275
#define MORETHAN 276
#define POINT 277
#define COMMA 278
#define DOUBLEPOINT 279
#define END_OF_STMT 280
#define DO 281
#define WHILE 282
#define BREAK 283
#define NEXT 284
#define RETURN 285
#define AND 286
#define OR 287
#define NOT 288
#define ASSIGN 289
#define SUB 290
#define SUM 291
#define MUL 292
#define DIV 293
#define MOD 294
#define POT 295
#define NEG 296
#define LCURLYPAR 297
#define RCURLYPAR 298
#define LPAR 299
#define RPAR 300
#define LRECTPAR 301
#define RRECTPAR 302
#define IF 303
#define ELSE 304
#define THEN 305

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 19 "YA.y" /* yacc.c:1909  */

	int val;
    char *id;
    float valfloat;
    char *str;
    bool booleano;
    struct nl *nl;
    struct Id *id_2;
    struct ids *ids;
	struct calc_exp *CExp;
	struct op *op;
	struct type *type;
	struct stmts *stmts;
	struct corpo *corpo;
	struct corpo_cycle *corpo_cycle;
	struct Corpo_cond *corpo_cond;
	struct decl *decl;
	struct decl1 *decl1;
	struct decl2 *decl2;
	struct ifs *ifs;
	struct afect *afect;
	struct afects *afects;
	struct funcdeclar *funcdeclar;
	struct funcdeclar2 *funcdeclar2;
	struct whiles *whiles;
	struct expBools *expBools;
	struct decls *decls;
	struct literalExp *literalExp;
	struct funcCall *funcCall;

#line 185 "parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
