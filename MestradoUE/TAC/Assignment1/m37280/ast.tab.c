/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "ast.y" /* yacc.c:339  */

    #include <stdio.h>
    #include <stdbool.h>
    #include <stdlib.h>
    #include <string.h>
    #include "tacl_ir.h"
    
    int yylex(void);
    void yyerror(const char *);	// see below
    

#line 78 "ast.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "ast.tab.h".  */
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
#line 14 "ast.y" /* yacc.c:355  */

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
    

#line 196 "ast.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_AST_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 213 "ast.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   128

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  68
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  140

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   302

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   100,   100,   104,   105,   109,   110,   114,   118,   119,
     120,   124,   125,   126,   130,   134,   135,   139,   140,   144,
     145,   146,   147,   151,   152,   156,   157,   158,   159,   160,
     161,   165,   166,   170,   175,   176,   180,   184,   185,   189,
     190,   194,   195,   196,   197,   198,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   221,   222,   223,   224,   228,   229,   230
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "FUN", "VAR", "ARG", "LOCAL", "BODY",
  "OPPAR", "CLPAR", "OPRPAR", "CLRPAR", "COLON", "INT_LITERAL_VALUE",
  "REAL_LITERAL_VALUE", "BOOL_LITERAL", "INT", "REAL", "BOOL", "TOREAL",
  "IDENTIFIER", "ID", "INT_LITERAL", "REAL_LITERAL", "TYPE", "ASSIGN",
  "WHILE", "PRINT", "CALL", "IF", "ELSE", "NIL", "OR", "AND", "EQ", "NE",
  "LT", "LE", "GT", "GE", "PLUS", "MINUS", "TIMES", "DIV", "MOD", "NOT",
  "INV", "ERROR", "$accept", "ast", "global_declarations",
  "global_declaration", "vardecls", "kind", "type", "fundef",
  "formal_args", "more_formal_args", "body_fun", "more_vardecls",
  "statement", "statements", "id_", "conditional", "function_call",
  "actual_args", "more_actual_args", "expression", "operator",
  "atomic_expression", "literal", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302
};
# endif

#define YYPACT_NINF -80

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-80)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      -1,    44,    16,   -80,    -1,   -80,   -80,    17,    11,   -80,
     -80,    49,    41,    58,    53,    69,    74,    70,    48,    30,
      60,    75,   -80,   -80,   -80,    40,   -11,    72,   -80,    73,
      40,    78,   -80,   -80,   -80,   -80,   -80,   -80,    77,    80,
      66,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,
     -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,    30,    82,
     -80,    79,   -80,    83,    86,   -80,   -80,    88,     5,    87,
     -80,    92,    -2,    93,    30,    89,    94,    40,    99,   -80,
     101,    33,    98,    96,   100,    97,    30,    40,   102,   -80,
      90,    43,    55,    30,    30,   -80,   -80,    55,   -80,   -80,
     -80,    30,   -80,    40,    40,   103,    30,    30,    30,   106,
      55,   105,   -80,   -80,    30,   -80,   -80,   108,    41,    55,
     109,    55,   -80,   -80,   -80,   -80,    92,   110,   111,   -80,
      36,   -80,    30,   -80,   112,   113,   114,   -80,   -80,   -80
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     4,     5,     6,     0,     0,     1,
       3,     0,     0,    16,     0,     0,     0,     0,     0,     0,
       0,     0,     8,    10,     9,     0,    65,     0,    43,     0,
       0,     0,    12,    13,    11,    33,    68,    61,     0,     0,
       0,    50,    51,    53,    54,    55,    58,    56,    57,    47,
      52,    46,    49,    48,    59,    60,    62,    63,     0,     0,
      64,     0,     7,     0,    22,    66,    67,     0,     0,     0,
      45,    18,     0,     0,    38,     0,     0,     0,     0,    15,
       0,     0,    23,     0,     0,     0,    40,     0,     0,    42,
       0,     0,    32,     0,     0,    27,    24,     0,    14,    36,
      37,    40,    44,     0,     0,     0,     0,     0,     0,     0,
      32,     0,    21,    20,     0,    39,    41,     0,     0,     0,
       0,     0,    29,    31,    25,    19,    18,     0,     0,    30,
       0,    17,     0,    26,     0,     0,     0,    35,    34,    28
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -80,   -80,   120,   -80,   -67,   -80,   -27,   -80,   -80,   -14,
     -80,    45,   -79,    15,   -25,   -80,    35,   -80,    27,   -19,
     -80,   -80,   -80
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,     4,     5,    25,    35,     6,    17,    79,
      73,    83,   110,   111,    15,    95,    57,    85,   100,   101,
      58,    59,    60
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      29,    56,    94,    63,    36,    82,    80,     1,    37,    81,
      14,    38,    39,    26,    75,    82,     9,    40,   114,    12,
      27,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    28,    11,    26,    68,
     128,    91,   130,    92,    91,    27,    92,     7,     8,    76,
      89,   135,    22,    23,    24,    86,    32,    33,    34,    13,
     102,    28,    14,    91,    93,    92,    16,   134,   105,   106,
     107,    40,   108,    18,   112,   113,   116,   117,    19,    20,
      30,    21,    62,    31,    61,    64,    67,   119,   120,   121,
      65,    69,    71,   127,    66,   125,    72,    70,    74,    77,
      78,    87,    84,    88,    90,     8,    80,    97,    99,    98,
     104,   118,   131,   136,   103,   122,   124,   126,   129,   132,
     133,   137,   138,   139,    10,   123,   109,    96,   115
};

static const yytype_uint8 yycheck[] =
{
      19,    26,    81,    30,    15,    72,     8,     8,    19,    11,
      21,    22,    23,     8,     9,    82,     0,    28,    97,     8,
      15,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    31,    20,     8,    58,
     119,     8,   121,    10,     8,    15,    10,     3,     4,    68,
      77,   130,     4,     5,     6,    74,    16,    17,    18,    10,
      87,    31,    21,     8,    31,    10,     8,    31,    25,    26,
      27,    28,    29,    20,    93,    94,   103,   104,     9,     5,
      20,    11,     9,     8,    12,     7,    20,   106,   107,   108,
      13,     9,     9,   118,    14,   114,    10,    18,    10,    12,
       8,    12,     9,     9,     5,     4,     8,    11,    11,     9,
      20,     8,   126,   132,    12,     9,    11,     9,     9,     9,
       9,     9,     9,     9,     4,   110,    91,    82,   101
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     8,    49,    50,    51,    52,    55,     3,     4,     0,
      50,    20,     8,    10,    21,    62,     8,    56,    20,     9,
       5,    11,     4,     5,     6,    53,     8,    15,    31,    67,
      20,     8,    16,    17,    18,    54,    15,    19,    22,    23,
      28,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    62,    64,    68,    69,
      70,    12,     9,    54,     7,    13,    14,    20,    67,     9,
      18,     9,    10,    58,    10,     9,    67,    12,     8,    57,
       8,    11,    52,    59,     9,    65,    67,    12,     9,    54,
       5,     8,    10,    31,    60,    63,    59,    11,     9,    11,
      66,    67,    54,    12,    20,    25,    26,    27,    29,    64,
      60,    61,    67,    67,    60,    66,    54,    54,     8,    67,
      67,    67,     9,    61,    11,    67,     9,    62,    60,     9,
      60,    57,     9,     9,    31,    60,    67,     9,     9,     9
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    48,    49,    50,    50,    51,    51,    52,    53,    53,
      53,    54,    54,    54,    55,    56,    56,    57,    57,    58,
      58,    58,    58,    59,    59,    60,    60,    60,    60,    60,
      60,    61,    61,    62,    63,    63,    64,    65,    65,    66,
      66,    67,    67,    67,    67,    67,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    69,    69,    69,    69,    70,    70,    70
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     7,     1,     1,
       1,     1,     1,     1,    11,     6,     0,     6,     0,     5,
       4,     4,     0,     1,     2,     3,     5,     1,     7,     3,
       4,     2,     0,     4,     6,     6,     5,     2,     0,     2,
       0,     7,     5,     1,     6,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     2,     2,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 100 "ast.y" /* yacc.c:1646  */
    {the_root((yyvsp[0].global_declarations));}
#line 1382 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 104 "ast.y" /* yacc.c:1646  */
    {(yyval.global_declarations) = new_global_declarations((yyvsp[-1].global_declaration),(yyvsp[0].global_declarations));}
#line 1388 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 105 "ast.y" /* yacc.c:1646  */
    {(yyval.global_declarations) = new_global_declarations((yyvsp[0].global_declaration), NULL);}
#line 1394 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 109 "ast.y" /* yacc.c:1646  */
    {(yyval.global_declaration) = new_global_declaration_decl((yyvsp[0].vardecls));}
#line 1400 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 110 "ast.y" /* yacc.c:1646  */
    {(yyval.global_declaration) = new_global_declaration_fun((yyvsp[0].fundef));}
#line 1406 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 114 "ast.y" /* yacc.c:1646  */
    {(yyval.vardecls) = new_vardecls((yyvsp[-3].id_),(yyvsp[-1].expression));}
#line 1412 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 118 "ast.y" /* yacc.c:1646  */
    {(yyval.kind) = new_kind(VAR_);}
#line 1418 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 119 "ast.y" /* yacc.c:1646  */
    {(yyval.kind) = new_kind(LOCAL_);}
#line 1424 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 120 "ast.y" /* yacc.c:1646  */
    {(yyval.kind) = new_kind(ARG_);}
#line 1430 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 124 "ast.y" /* yacc.c:1646  */
    {(yyval.type) = new_type(BOOL_);}
#line 1436 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 125 "ast.y" /* yacc.c:1646  */
    {(yyval.type) = new_type(INT_);}
#line 1442 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 126 "ast.y" /* yacc.c:1646  */
    {(yyval.type) = new_type(REAL_);}
#line 1448 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 130 "ast.y" /* yacc.c:1646  */
    {(yyval.fundef) = new_fundef((yyvsp[-8].string),(yyvsp[-6].formal_args),(yyvsp[-2].body_fun));}
#line 1454 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 134 "ast.y" /* yacc.c:1646  */
    {(yyval.formal_args) = new_formal_args((yyvsp[-3].string),(yyvsp[-2].type),(yyvsp[0].more_formal_args));}
#line 1460 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 135 "ast.y" /* yacc.c:1646  */
    {(yyval.formal_args) = NULL;}
#line 1466 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 139 "ast.y" /* yacc.c:1646  */
    {(yyval.more_formal_args) = new_more_formal_args((yyvsp[-3].string),(yyvsp[-2].type),(yyvsp[0].more_formal_args));}
#line 1472 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 140 "ast.y" /* yacc.c:1646  */
    {(yyval.more_formal_args) = NULL;}
#line 1478 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 144 "ast.y" /* yacc.c:1646  */
    {(yyval.body_fun) = new_body((yyvsp[-3].more_vardecls),(yyvsp[-1].stmt),(yyvsp[0].expression));}
#line 1484 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 145 "ast.y" /* yacc.c:1646  */
    {(yyval.body_fun) = new_body(NULL,(yyvsp[-1].stmt),(yyvsp[0].expression));}
#line 1490 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 146 "ast.y" /* yacc.c:1646  */
    {(yyval.body_fun) = new_body(NULL,NULL,(yyvsp[0].expression));}
#line 1496 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 147 "ast.y" /* yacc.c:1646  */
    {(yyval.body_fun) = NULL;}
#line 1502 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 151 "ast.y" /* yacc.c:1646  */
    {(yyval.more_vardecls) = new_more_vardecls((yyvsp[0].vardecls),NULL);}
#line 1508 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 152 "ast.y" /* yacc.c:1646  */
    {(yyval.more_vardecls) = new_more_vardecls((yyvsp[-1].vardecls),(yyvsp[0].more_vardecls));}
#line 1514 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 156 "ast.y" /* yacc.c:1646  */
    {(yyval.stmt) = new_stmt((yyvsp[-1].stmts));}
#line 1520 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 157 "ast.y" /* yacc.c:1646  */
    {(yyval.stmt) = new_stmt_loop((yyvsp[-2].expression),(yyvsp[-1].stmt));}
#line 1526 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 158 "ast.y" /* yacc.c:1646  */
    {(yyval.stmt) = new_stmt_cond((yyvsp[0].conditional));}
#line 1532 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 159 "ast.y" /* yacc.c:1646  */
    {(yyval.stmt) = new_stmt_assign((yyvsp[-3].id_),(yyvsp[-1].expression));}
#line 1538 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 160 "ast.y" /* yacc.c:1646  */
    {(yyval.stmt) = new_stmt_call((yyvsp[-1].function_call));}
#line 1544 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 161 "ast.y" /* yacc.c:1646  */
    {(yyval.stmt) = new_stmt_print((yyvsp[-1].expression));}
#line 1550 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 165 "ast.y" /* yacc.c:1646  */
    {(yyval.stmts) = new_stmts((yyvsp[-1].stmt),(yyvsp[0].stmts));}
#line 1556 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 166 "ast.y" /* yacc.c:1646  */
    {(yyval.stmts) = NULL;}
#line 1562 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 170 "ast.y" /* yacc.c:1646  */
    {(yyval.id_) = new_id((yyvsp[-2].string),(yyvsp[-1].kind),(yyvsp[0].type));}
#line 1568 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 175 "ast.y" /* yacc.c:1646  */
    {(yyval.conditional) = new_conditional((yyvsp[-3].expression),(yyvsp[-2].stmt),(yyvsp[-1].stmt));}
#line 1574 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 176 "ast.y" /* yacc.c:1646  */
    {(yyval.conditional) = new_conditional((yyvsp[-3].expression),(yyvsp[-2].stmt),NULL);}
#line 1580 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 180 "ast.y" /* yacc.c:1646  */
    {(yyval.function_call) = new_function_call((yyvsp[-3].string),(yyvsp[-1].actual_args));}
#line 1586 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 184 "ast.y" /* yacc.c:1646  */
    {(yyval.actual_args) = new_actual_args((yyvsp[-1].expression),(yyvsp[0].more_actual_args));}
#line 1592 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 185 "ast.y" /* yacc.c:1646  */
    {(yyval.actual_args) = new_actual_args(NULL,NULL);}
#line 1598 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 189 "ast.y" /* yacc.c:1646  */
    {(yyval.more_actual_args) = new_more_actual_args((yyvsp[-1].expression),(yyvsp[0].more_actual_args));}
#line 1604 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 190 "ast.y" /* yacc.c:1646  */
    {(yyval.more_actual_args) = new_more_actual_args(NULL,NULL);}
#line 1610 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 194 "ast.y" /* yacc.c:1646  */
    {(yyval.expression) = new_expression_op((yyvsp[-5].operator),(yyvsp[-4].expression),(yyvsp[-3].expression),(yyvsp[0].type));}
#line 1616 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 195 "ast.y" /* yacc.c:1646  */
    {(yyval.expression) = new_expression_atom((yyvsp[-3].atomic_expression),(yyvsp[0].type));}
#line 1622 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 196 "ast.y" /* yacc.c:1646  */
    {(yyval.expression) = no_exp(NIL_);}
#line 1628 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 197 "ast.y" /* yacc.c:1646  */
    {(yyval.expression) = new_expression_unop((yyvsp[-4].operator),(yyvsp[-3].expression),(yyvsp[0].type));}
#line 1634 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 198 "ast.y" /* yacc.c:1646  */
    {(yyval.expression) = new_expression_lit((yyvsp[-2].integer));}
#line 1640 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 202 "ast.y" /* yacc.c:1646  */
    {(yyval.operator) = new_operator(TIMES_);}
#line 1646 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 203 "ast.y" /* yacc.c:1646  */
    {(yyval.operator) = new_operator(PLUS_);}
#line 1652 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 204 "ast.y" /* yacc.c:1646  */
    {(yyval.operator) = new_operator(MOD_);}
#line 1658 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 205 "ast.y" /* yacc.c:1646  */
    {(yyval.operator) = new_operator(DIV_);}
#line 1664 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 206 "ast.y" /* yacc.c:1646  */
    {(yyval.operator) = new_operator(OR_);}
#line 1670 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 207 "ast.y" /* yacc.c:1646  */
    {(yyval.operator) = new_operator(AND_);}
#line 1676 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 208 "ast.y" /* yacc.c:1646  */
    {(yyval.operator) = new_operator(MINUS_);}
#line 1682 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 209 "ast.y" /* yacc.c:1646  */
    {(yyval.operator) = new_operator(EQ_);}
#line 1688 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 210 "ast.y" /* yacc.c:1646  */
    {(yyval.operator) = new_operator(NE_);}
#line 1694 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 211 "ast.y" /* yacc.c:1646  */
    {(yyval.operator) = new_operator(LT_);}
#line 1700 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 212 "ast.y" /* yacc.c:1646  */
    {(yyval.operator) = new_operator(GT_);}
#line 1706 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 213 "ast.y" /* yacc.c:1646  */
    {(yyval.operator) = new_operator(GE_);}
#line 1712 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 214 "ast.y" /* yacc.c:1646  */
    {(yyval.operator) = new_operator(LE_);}
#line 1718 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 215 "ast.y" /* yacc.c:1646  */
    {(yyval.operator) = new_operator(NOT_);}
#line 1724 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 216 "ast.y" /* yacc.c:1646  */
    {(yyval.operator) = new_operator(INV_);}
#line 1730 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 217 "ast.y" /* yacc.c:1646  */
    {(yyval.operator) = new_operator(TOREAL_);}
#line 1736 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 221 "ast.y" /* yacc.c:1646  */
    {(yyval.atomic_expression) = new_atomic_expression_id((yyvsp[0].id_));}
#line 1742 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 222 "ast.y" /* yacc.c:1646  */
    {(yyval.atomic_expression) = new_atomic_expression_call((yyvsp[0].function_call));}
#line 1748 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 223 "ast.y" /* yacc.c:1646  */
    {(yyval.atomic_expression) = new_atomic_expression_lit((yyvsp[0].literal));}
#line 1754 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 224 "ast.y" /* yacc.c:1646  */
    {(yyval.atomic_expression) = NULL;}
#line 1760 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 228 "ast.y" /* yacc.c:1646  */
    {(yyval.literal) = new_literal_int((yyvsp[0].integer));}
#line 1766 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 229 "ast.y" /* yacc.c:1646  */
    {(yyval.literal) = new_literal_real((yyvsp[0].real));}
#line 1772 "ast.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 230 "ast.y" /* yacc.c:1646  */
    {(yyval.literal) = new_literal_bool((yyvsp[0].integer));}
#line 1778 "ast.tab.c" /* yacc.c:1646  */
    break;


#line 1782 "ast.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 236 "ast.y" /* yacc.c:1906  */


// called when there is a syntax error
void yyerror(const char *msg)
{
    extern int yylineno;     
    fprintf(stderr, "error: %s\n " , msg);
    fprintf(stderr, "Syntax error at line %d\n",yylineno); // TELL ME EXACTLY WHERE THE ERRORS ARE
}

int main()
{
  return yyparse();
}
