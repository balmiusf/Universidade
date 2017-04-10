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

#ifndef YY_YY_AST_TAB_H_INCLUDED
# define YY_YY_AST_TAB_H_INCLUDED
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
    FUN = 258,
    VAR = 259,
    ARG = 260,
    LOCAL = 261,
    BODY = 262,
    OPPAR = 263,
    CLPAR = 264,
    OPRPAR = 265,
    CLRPAR = 266,
    COLON = 267,
    INT_LITERAL_VALUE = 268,
    REAL_LITERAL_VALUE = 269,
    BOOL_LITERAL = 270,
    INT = 271,
    REAL = 272,
    BOOL = 273,
    TOREAL = 274,
    IDENTIFIER = 275,
    ID = 276,
    INT_LITERAL = 277,
    REAL_LITERAL = 278,
    TYPE = 279,
    ASSIGN = 280,
    WHILE = 281,
    PRINT = 282,
    CALL = 283,
    IF = 284,
    ELSE = 285,
    NIL = 286,
    OR = 287,
    AND = 288,
    EQ = 289,
    NE = 290,
    LT = 291,
    LE = 292,
    GT = 293,
    GE = 294,
    PLUS = 295,
    MINUS = 296,
    TIMES = 297,
    DIV = 298,
    MOD = 299,
    NOT = 300,
    INV = 301,
    ERROR = 302
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 14 "ast.y" /* yacc.c:1909  */

    char   *string;
    int    integer;
    double real;

    struct global_declaration *global_declaration;
    struct global_declarations *global_declarations;
    struct atomic_expression *atomic_expression;
    struct expression *expression;
    struct conditional *conditional;
    struct more_vardecls *more_vardecls;
    struct vardecls *vardecls;
    struct stmt *stmt;
    struct stmts *stmts;
    struct body *body_fun;
    struct id *id_;
    struct type *type;
    struct kind *kind;
    struct operator *operator;
    struct fundef *fundef;
    struct function_call *function_call;
    struct actual_args *actual_args;
    struct more_actual_args *more_actual_args;
    struct literal *literal;
    struct formal_args *formal_args;
    struct more_formal_args *more_formal_args;
    struct ast *ast;
    

#line 132 "ast.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_AST_TAB_H_INCLUDED  */
