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
#line 1 "YA.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "apt.h"

int yylex (void);
void yyerror (char const *);

enum type_kind lookup_type(char *id);
void table_insert_1(char *id, type type);
void table_insert_2(belos_ids ids, type type);
void insertFunc(funcdeclar funcdeclar, type type);


#line 84 "parser.c" /* yacc.c:339  */

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
   by #include "parser.h".  */
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
#line 19 "YA.y" /* yacc.c:355  */

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

#line 255 "parser.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 272 "parser.c" /* yacc.c:358  */

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
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   224

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  71
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  148

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   305

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
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   104,   104,   109,   110,   114,   115,   118,   120,   123,
     126,   127,   128,   129,   130,   133,   136,   137,   140,   141,
     142,   145,   146,   147,   148,   149,   150,   153,   154,   155,
     156,   159,   160,   163,   164,   167,   170,   171,   174,   175,
     178,   179,   180,   181,   182,   185,   186,   187,   188,   189,
     190,   191,   194,   195,   196,   197,   198,   199,   200,   201,
     204,   205,   206,   207,   211,   212,   213,   214,   215,   216,
     217,   218
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "NUM_LIT", "NUM_FLOAT_LIT",
  "STRING_LIT", "BOOL_LIT", "NL", "INT", "FLOAT", "BOOL", "STRING", "VOID",
  "DEFINE", "EQUALS", "LESSOREQUAL", "LESSTHAN", "DIFFERENTTHAN",
  "EQUALLESSTHAN", "EQUALMORETHAN", "MORETHAN", "POINT", "COMMA",
  "DOUBLEPOINT", "END_OF_STMT", "DO", "WHILE", "BREAK", "NEXT", "RETURN",
  "AND", "OR", "NOT", "ASSIGN", "SUB", "SUM", "MUL", "DIV", "MOD", "POT",
  "NEG", "LCURLYPAR", "RCURLYPAR", "LPAR", "RPAR", "LRECTPAR", "RRECTPAR",
  "IF", "ELSE", "THEN", "$accept", "input", "decls", "decl", "ifs",
  "whiles", "decl1", "decl2", "corpo", "corpo_cycle", "stmts", "funcCall",
  "funcdeclar", "funcdeclar2", "afect", "afects", "ids", "type",
  "expBools", "op", "literalExp", "exp", YY_NULLPTR
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305
};
# endif

#define YYPACT_NINF -70

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-70)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       9,   -19,    10,    22,     9,   -70,   -70,   -70,     0,    25,
      58,    13,     4,   134,   -70,   -70,   134,   134,    14,   -70,
      40,   -70,   -70,   -70,   -70,   -70,    95,    95,   134,   -70,
     160,   -70,   -70,   -70,   -70,   -70,    44,    23,    34,   134,
     -70,    83,    47,    95,    95,    95,    95,    95,   134,   -70,
      33,   -70,    95,     5,   -70,   -70,   178,   178,    55,    55,
      55,    48,    81,    82,    95,    82,    72,    80,   -70,    63,
      33,    91,   -70,   133,   104,   -70,   -70,   -70,    87,    39,
     170,    82,    82,    98,   146,   168,    79,   -70,   -70,   108,
     -70,   -70,   -70,   116,   126,   125,    42,   -18,   -70,   111,
     114,   174,   -70,   -70,   -70,   -70,   -70,   -70,   -70,   -70,
     107,   -70,   115,   117,   130,    82,   -70,   132,   -70,   134,
      87,   -70,   -70,   -70,   -70,   -70,    42,   -70,    27,   -70,
     146,    33,     5,   -70,   150,   151,   136,   -70,   137,   -70,
     -70,   -70,   -70,   143,   152,    33,   156,   -70
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    38,     0,     0,     2,     4,     6,     5,     0,     0,
       0,     0,     0,     0,     1,     3,     0,     0,    38,    39,
       0,    32,    60,    61,    62,    63,     0,     0,     0,    71,
       0,    40,    44,    41,    42,    43,     0,     0,     0,     0,
      69,     0,     0,     0,     0,     0,     0,     0,     0,    12,
       0,    10,     0,     0,    70,    14,    65,    64,    66,    67,
      68,     0,    38,     0,     0,     0,     0,     0,    21,     0,
      16,     0,    25,     0,     0,    33,    31,    13,     0,     0,
      46,     0,     0,     0,     0,     0,     0,    22,    23,     0,
      17,    26,    11,     0,     0,     0,    37,    38,    27,     0,
       0,     0,    52,    54,    53,    56,    57,    55,    58,    59,
       0,    50,     0,     0,     0,     0,    24,     0,    15,     0,
       0,    35,    30,    28,    29,    48,    47,    51,     0,    49,
      45,     0,     0,    36,     0,     0,     0,    18,     0,    34,
      19,    20,     9,     8,     0,     0,     0,     7
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -70,   -70,   -70,   209,   -70,   -70,    17,   -70,   -69,   -70,
      89,   141,   -70,    90,   -70,   101,    -8,   -10,   -62,   144,
     -70,   -12
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     5,    66,    67,    68,     7,    69,   136,
      70,    71,     8,    76,    72,    95,     9,    36,    83,   115,
      29,    84
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      30,    90,    19,    86,    10,    10,    37,    38,    22,    23,
      24,    25,     1,    13,    40,    41,    20,     6,    42,   111,
     112,     6,    14,     2,    16,    11,    79,    12,    74,    53,
      62,    56,    57,    58,    59,    60,    62,    10,    61,    26,
      73,     2,    97,    22,    23,    24,    25,     2,    27,    17,
      75,    28,    85,   129,    63,   134,   135,    64,    21,    51,
      63,    18,   138,    64,    39,    50,    96,   101,    52,    49,
     113,   100,    55,    77,    26,    65,   146,    43,    44,    45,
      46,    65,    47,    27,    98,    80,    22,    23,    24,    25,
      94,    22,    23,    24,    25,    47,    78,    87,   126,    22,
      23,    24,    25,   130,    10,    88,    89,    93,    96,   132,
     125,    22,    23,    24,    25,    81,    91,    26,    43,    44,
      45,    46,    26,    47,   114,    79,    82,    12,    54,   117,
      26,    27,   102,   118,   103,   104,   105,   106,   107,    27,
     119,   120,    26,    31,    32,    33,    34,    35,   108,   109,
     121,    27,    43,    44,    45,    46,   122,    47,    92,   123,
     127,   102,    54,   103,   104,   105,   106,   107,    43,    44,
      45,    46,   128,    47,   131,   140,   141,   108,   109,   142,
     143,    43,    44,    45,    46,   102,    47,   103,   104,   105,
     106,   107,   144,   116,   145,    43,    44,    45,    46,   147,
      47,   108,   109,    43,    44,    45,    46,    48,    47,    43,
      44,    45,    46,    15,    47,    45,    46,   137,    47,   124,
      99,   133,   139,     0,   110
};

static const yytype_int16 yycheck[] =
{
      12,    70,    10,    65,    23,    23,    16,    17,     4,     5,
       6,     7,     3,     3,    26,    27,     3,     0,    28,    81,
      82,     4,     0,    14,    24,    44,    44,    46,    23,    39,
       3,    43,    44,    45,    46,    47,     3,    23,    48,    35,
      52,    14,     3,     4,     5,     6,     7,    14,    44,    24,
      45,    47,    64,   115,    27,    28,    29,    30,    45,    25,
      27,     3,   131,    30,    24,    42,    78,    79,    34,    25,
      82,    79,    25,    25,    35,    48,   145,    35,    36,    37,
      38,    48,    40,    44,    45,     3,     4,     5,     6,     7,
       3,     4,     5,     6,     7,    40,    15,    25,   110,     4,
       5,     6,     7,   115,    23,    25,    43,     3,   120,   119,
       3,     4,     5,     6,     7,    33,    25,    35,    35,    36,
      37,    38,    35,    40,    26,    44,    44,    46,    45,    50,
      35,    44,    15,    25,    17,    18,    19,    20,    21,    44,
      24,    15,    35,     9,    10,    11,    12,    13,    31,    32,
      25,    44,    35,    36,    37,    38,    45,    40,    25,    45,
      45,    15,    45,    17,    18,    19,    20,    21,    35,    36,
      37,    38,    42,    40,    42,    25,    25,    31,    32,    43,
      43,    35,    36,    37,    38,    15,    40,    17,    18,    19,
      20,    21,    49,    25,    42,    35,    36,    37,    38,    43,
      40,    31,    32,    35,    36,    37,    38,    47,    40,    35,
      36,    37,    38,     4,    40,    37,    38,   128,    40,    45,
      79,   120,   132,    -1,    80
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    14,    52,    53,    54,    57,    58,    63,    67,
      23,    44,    46,     3,     0,    54,    24,    24,     3,    67,
       3,    45,     4,     5,     6,     7,    35,    44,    47,    71,
      72,     9,    10,    11,    12,    13,    68,    68,    68,    24,
      72,    72,    68,    35,    36,    37,    38,    40,    47,    25,
      42,    25,    34,    68,    45,    25,    72,    72,    72,    72,
      72,    68,     3,    27,    30,    48,    55,    56,    57,    59,
      61,    62,    65,    72,    23,    45,    64,    25,    15,    44,
       3,    33,    44,    69,    72,    72,    69,    25,    25,    43,
      59,    25,    25,     3,     3,    66,    72,     3,    45,    62,
      67,    72,    15,    17,    18,    19,    20,    21,    31,    32,
      70,    69,    69,    72,    26,    70,    25,    50,    25,    24,
      15,    25,    45,    45,    45,     3,    72,    45,    42,    69,
      72,    42,    68,    66,    28,    29,    60,    61,    59,    64,
      25,    25,    43,    43,    49,    42,    59,    43
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    51,    52,    53,    53,    54,    54,    55,    55,    56,
      57,    57,    57,    57,    57,    58,    59,    59,    60,    60,
      60,    61,    61,    61,    61,    61,    61,    62,    62,    62,
      62,    63,    63,    64,    64,    65,    66,    66,    67,    67,
      68,    68,    68,    68,    68,    69,    69,    69,    69,    69,
      69,    69,    70,    70,    70,    70,    70,    70,    70,    70,
      71,    71,    71,    71,    72,    72,    72,    72,    72,    72,
      72,    72
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,    10,     6,     6,
       4,     6,     4,     6,     5,     7,     1,     2,     1,     2,
       2,     1,     2,     2,     3,     1,     2,     3,     4,     4,
       4,     6,     3,     1,     5,     4,     3,     1,     1,     3,
       1,     1,     1,     1,     1,     3,     1,     3,     3,     3,
       2,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     2,
       3,     1
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
#line 104 "YA.y" /* yacc.c:1646  */
    {printf("END\n");}
#line 1467 "parser.c" /* yacc.c:1646  */
    break;

  case 3:
#line 109 "YA.y" /* yacc.c:1646  */
    {(yyval.decls) = new_decls((yyvsp[0].decl),(yyvsp[-1].decls)); printf("DECL DECLS\n");}
#line 1473 "parser.c" /* yacc.c:1646  */
    break;

  case 4:
#line 110 "YA.y" /* yacc.c:1646  */
    {(yyval.decls) = new_decls((yyvsp[0].decl),NULL);printf("DECL ;\n");}
#line 1479 "parser.c" /* yacc.c:1646  */
    break;

  case 5:
#line 114 "YA.y" /* yacc.c:1646  */
    {(yyval.decl) = new_decl_func((yyvsp[0].decl2));printf("DECL2\n");}
#line 1485 "parser.c" /* yacc.c:1646  */
    break;

  case 6:
#line 115 "YA.y" /* yacc.c:1646  */
    {(yyval.decl) = new_decl_normal((yyvsp[0].decl1));printf("DECL1\n");}
#line 1491 "parser.c" /* yacc.c:1646  */
    break;

  case 7:
#line 118 "YA.y" /* yacc.c:1646  */
    {(yyval.ifs) = new_ifs((yyvsp[-8].expBools),(yyvsp[-5].corpo),(yyvsp[-1].corpo));printf("IF_ELSE_THEN\n");}
#line 1497 "parser.c" /* yacc.c:1646  */
    break;

  case 8:
#line 120 "YA.y" /* yacc.c:1646  */
    {(yyval.ifs) = new_ifs((yyvsp[-4].expBools),(yyvsp[-1].corpo),NULL);printf("IF_ELSE\n");}
#line 1503 "parser.c" /* yacc.c:1646  */
    break;

  case 9:
#line 123 "YA.y" /* yacc.c:1646  */
    {(yyval.whiles) = new_whiles((yyvsp[-4].expBools),(yyvsp[-1].corpo_cycle));printf("WHILE\n");}
#line 1509 "parser.c" /* yacc.c:1646  */
    break;

  case 10:
#line 126 "YA.y" /* yacc.c:1646  */
    {(yyval.decl1) = new_decl1_wo_type((yyvsp[-3].ids),(yyvsp[-1].type)); table_insert_2((yyvsp[-3].ids),(yyvsp[-1].type)); printf("IDS : TYPE\n");}
#line 1515 "parser.c" /* yacc.c:1646  */
    break;

  case 11:
#line 127 "YA.y" /* yacc.c:1646  */
    {(yyval.decl1) = new_decl1_type((yyvsp[-5].ids),(yyvsp[-3].type),(yyvsp[-1].CExp)); table_insert_2((yyvsp[-5].ids),(yyvsp[-3].type));printf("IDS : TYPE = EXP\n");}
#line 1521 "parser.c" /* yacc.c:1646  */
    break;

  case 12:
#line 128 "YA.y" /* yacc.c:1646  */
    {(yyval.decl1) = new_decl1_define((yyvsp[-2].id),(yyvsp[-1].type));table_insert_1((yyvsp[-2].id),(yyvsp[-1].type));printf("DEFINE ID TYPE\n");}
#line 1527 "parser.c" /* yacc.c:1646  */
    break;

  case 13:
#line 129 "YA.y" /* yacc.c:1646  */
    {(yyval.decl1) = new_decl1_array((yyvsp[-5].id),(yyvsp[-3].CExp),(yyvsp[-1].type));printf("ID[EXP]\n");}
#line 1533 "parser.c" /* yacc.c:1646  */
    break;

  case 14:
#line 130 "YA.y" /* yacc.c:1646  */
    {(yyval.decl1) = new_decl1_array((yyvsp[-4].id),NULL,(yyvsp[-1].type));printf("ID[]\n");}
#line 1539 "parser.c" /* yacc.c:1646  */
    break;

  case 15:
#line 133 "YA.y" /* yacc.c:1646  */
    {(yyval.decl2) = new_decl2((yyvsp[-6].funcdeclar),(yyvsp[-4].type),(yyvsp[-2].corpo));insertFunc((yyvsp[-6].funcdeclar),(yyvsp[-4].type));printf("FUNCAO\n");}
#line 1545 "parser.c" /* yacc.c:1646  */
    break;

  case 16:
#line 136 "YA.y" /* yacc.c:1646  */
    {(yyval.corpo) =  new_corpo((yyvsp[0].stmts),NULL);printf("STMTS\n");}
#line 1551 "parser.c" /* yacc.c:1646  */
    break;

  case 17:
#line 137 "YA.y" /* yacc.c:1646  */
    {(yyval.corpo) = new_corpo((yyvsp[-1].stmts),(yyvsp[0].corpo)); printf("STMTS CORPO\n");}
#line 1557 "parser.c" /* yacc.c:1646  */
    break;

  case 18:
#line 140 "YA.y" /* yacc.c:1646  */
    {(yyval.corpo_cycle) = new_corpo_cycle((yyvsp[0].stmts));}
#line 1563 "parser.c" /* yacc.c:1646  */
    break;

  case 19:
#line 141 "YA.y" /* yacc.c:1646  */
    {(yyval.corpo_cycle) = new_corpo_cycle_break(BREAK_);printf("BREAK\n");}
#line 1569 "parser.c" /* yacc.c:1646  */
    break;

  case 20:
#line 142 "YA.y" /* yacc.c:1646  */
    {(yyval.corpo_cycle) = new_corpo_cycle_next(NEXT_);printf("NEXT\n");}
#line 1575 "parser.c" /* yacc.c:1646  */
    break;

  case 21:
#line 145 "YA.y" /* yacc.c:1646  */
    {(yyval.stmts) = new_stmts_decl((yyvsp[0].decl1));		printf("STMTS -> DECL1\n");}
#line 1581 "parser.c" /* yacc.c:1646  */
    break;

  case 22:
#line 146 "YA.y" /* yacc.c:1646  */
    {(yyval.stmts) = new_stmts_cond((yyvsp[-1].ifs));		printf("STMTS -> IFS\n");}
#line 1587 "parser.c" /* yacc.c:1646  */
    break;

  case 23:
#line 147 "YA.y" /* yacc.c:1646  */
    {(yyval.stmts) = new_stmts_cycle((yyvsp[-1].whiles));		printf("STMTS -> WHILE\n");}
#line 1593 "parser.c" /* yacc.c:1646  */
    break;

  case 24:
#line 148 "YA.y" /* yacc.c:1646  */
    {(yyval.stmts) = new_stmts_return((yyvsp[-1].CExp));		printf("STMTS -> RETURN\n");}
#line 1599 "parser.c" /* yacc.c:1646  */
    break;

  case 25:
#line 149 "YA.y" /* yacc.c:1646  */
    {(yyval.stmts) = new_stmts_afect((yyvsp[0].afect));		printf("STMTS -> AFECT\n");}
#line 1605 "parser.c" /* yacc.c:1646  */
    break;

  case 26:
#line 150 "YA.y" /* yacc.c:1646  */
    {(yyval.stmts) = new_stmts_funcCalls((yyvsp[-1].funcCall));	printf("STMTS -> FUNC CALL\n");}
#line 1611 "parser.c" /* yacc.c:1646  */
    break;

  case 27:
#line 153 "YA.y" /* yacc.c:1646  */
    {(yyval.funcCall) = new_function_calls_no_args((yyvsp[-2].id));printf("FUNC_CALL_NO_ARGS\n");}
#line 1617 "parser.c" /* yacc.c:1646  */
    break;

  case 28:
#line 154 "YA.y" /* yacc.c:1646  */
    {(yyval.funcCall) = new_function_calls_args((yyvsp[-3].id),(yyvsp[-1].ids));printf("FUNC_CALL_ARGS\n");}
#line 1623 "parser.c" /* yacc.c:1646  */
    break;

  case 29:
#line 155 "YA.y" /* yacc.c:1646  */
    {(yyval.funcCall) = new_function_calls_exp((yyvsp[-3].id),(yyvsp[-1].CExp));printf("FUNC_CALL_EXPS\n");}
#line 1629 "parser.c" /* yacc.c:1646  */
    break;

  case 30:
#line 156 "YA.y" /* yacc.c:1646  */
    {(yyval.funcCall) = new_function_calls_func((yyvsp[-3].id),(yyvsp[-1].funcCall));printf("FUNC_CALL_FUNC\n");}
#line 1635 "parser.c" /* yacc.c:1646  */
    break;

  case 31:
#line 159 "YA.y" /* yacc.c:1646  */
    {(yyval.funcdeclar) = new_func_args((yyvsp[-5].id),(yyvsp[-3].id),(yyvsp[-1].type),(yyvsp[0].funcdeclar2));printf("FUNCTION_WITH_ARGS\n");}
#line 1641 "parser.c" /* yacc.c:1646  */
    break;

  case 32:
#line 160 "YA.y" /* yacc.c:1646  */
    {(yyval.funcdeclar) = new_func_no_args((yyvsp[-2].id));printf("FUNCTION_NO_ARGS\n");}
#line 1647 "parser.c" /* yacc.c:1646  */
    break;

  case 33:
#line 163 "YA.y" /* yacc.c:1646  */
    {(yyval.funcdeclar2) = NULL;}
#line 1653 "parser.c" /* yacc.c:1646  */
    break;

  case 34:
#line 164 "YA.y" /* yacc.c:1646  */
    {(yyval.funcdeclar2) = new_func_args_2((yyvsp[-3].id),(yyvsp[-1].type),(yyvsp[0].funcdeclar2));printf("FUNC DECLAR 2\n");}
#line 1659 "parser.c" /* yacc.c:1646  */
    break;

  case 35:
#line 167 "YA.y" /* yacc.c:1646  */
    {(yyval.afect) = new_afect((yyvsp[-3].id),(yyvsp[-1].afects));printf("1 - ID = AFECTS\n");}
#line 1665 "parser.c" /* yacc.c:1646  */
    break;

  case 36:
#line 170 "YA.y" /* yacc.c:1646  */
    {(yyval.afects) = new_afects((yyvsp[-2].id),(yyvsp[0].afects));printf("2 - ID = AFECTS\n");}
#line 1671 "parser.c" /* yacc.c:1646  */
    break;

  case 37:
#line 171 "YA.y" /* yacc.c:1646  */
    {(yyval.afects) = new_afects_end((yyvsp[0].CExp));printf("AFECTS - EXP\n");}
#line 1677 "parser.c" /* yacc.c:1646  */
    break;

  case 38:
#line 174 "YA.y" /* yacc.c:1646  */
    {(yyval.ids) = new_ids_solo((yyvsp[0].id));printf("ID\n");}
#line 1683 "parser.c" /* yacc.c:1646  */
    break;

  case 39:
#line 175 "YA.y" /* yacc.c:1646  */
    {(yyval.ids) = new_ids_more((yyvsp[-2].id),(yyvsp[0].ids));printf("MULTIPLE IDS\n");}
#line 1689 "parser.c" /* yacc.c:1646  */
    break;

  case 40:
#line 178 "YA.y" /* yacc.c:1646  */
    {(yyval.type) = new_type(INTEGER_);printf("INT\n");}
#line 1695 "parser.c" /* yacc.c:1646  */
    break;

  case 41:
#line 179 "YA.y" /* yacc.c:1646  */
    {(yyval.type) = new_type(BOOLEAN_);printf("BOOL\n");}
#line 1701 "parser.c" /* yacc.c:1646  */
    break;

  case 42:
#line 180 "YA.y" /* yacc.c:1646  */
    {(yyval.type) = new_type(STRING_);printf("STRING\n");}
#line 1707 "parser.c" /* yacc.c:1646  */
    break;

  case 43:
#line 181 "YA.y" /* yacc.c:1646  */
    {(yyval.type) = new_type(VOID_);printf("VOID\n");}
#line 1713 "parser.c" /* yacc.c:1646  */
    break;

  case 44:
#line 182 "YA.y" /* yacc.c:1646  */
    {(yyval.type) = new_type(FLOATING_);printf("FLOAT\n");}
#line 1719 "parser.c" /* yacc.c:1646  */
    break;

  case 45:
#line 185 "YA.y" /* yacc.c:1646  */
    {(yyval.expBools) = new_exp_bools_1((yyvsp[-2].CExp),(yyvsp[-1].op),(yyvsp[0].CExp));printf("EXP OP EXP\n");}
#line 1725 "parser.c" /* yacc.c:1646  */
    break;

  case 46:
#line 186 "YA.y" /* yacc.c:1646  */
    {(yyval.expBools) = new_exp_bools_id((yyvsp[0].id));printf("EXPBOOLS ID\n");}
#line 1731 "parser.c" /* yacc.c:1646  */
    break;

  case 47:
#line 187 "YA.y" /* yacc.c:1646  */
    {(yyval.expBools) = new_exp_bools_id_exp((yyvsp[-2].id),(yyvsp[-1].op),(yyvsp[0].CExp));printf("ID op EXP\n");}
#line 1737 "parser.c" /* yacc.c:1646  */
    break;

  case 48:
#line 188 "YA.y" /* yacc.c:1646  */
    {(yyval.expBools) = new_exp_bools_id_exp_2((yyvsp[-2].id),(yyvsp[-1].op),(yyvsp[0].id));printf("ID op ID\n");}
#line 1743 "parser.c" /* yacc.c:1646  */
    break;

  case 49:
#line 189 "YA.y" /* yacc.c:1646  */
    {(yyval.expBools) = new_exp_bools_2((yyvsp[-2].CExp),(yyvsp[-1].op),(yyvsp[0].expBools));printf("EXP OP BOOLS EXP\n");}
#line 1749 "parser.c" /* yacc.c:1646  */
    break;

  case 50:
#line 190 "YA.y" /* yacc.c:1646  */
    {(yyval.expBools) = new_exp_bools_not((yyvsp[0].expBools));printf("NOT EXP BOOLS\n");}
#line 1755 "parser.c" /* yacc.c:1646  */
    break;

  case 51:
#line 191 "YA.y" /* yacc.c:1646  */
    {(yyval.expBools) = new_exp_bools_par((yyvsp[-1].expBools));printf("( EXP BOOLS )\n");}
#line 1761 "parser.c" /* yacc.c:1646  */
    break;

  case 52:
#line 194 "YA.y" /* yacc.c:1646  */
    {(yyval.op) = new_op(EQUALS_);printf("equals\n");}
#line 1767 "parser.c" /* yacc.c:1646  */
    break;

  case 53:
#line 195 "YA.y" /* yacc.c:1646  */
    {(yyval.op) = new_op(DIFFERENTTHAN_);printf("!=\n");}
#line 1773 "parser.c" /* yacc.c:1646  */
    break;

  case 54:
#line 196 "YA.y" /* yacc.c:1646  */
    {(yyval.op) = new_op(LESSTHAN_);printf("<\n ");}
#line 1779 "parser.c" /* yacc.c:1646  */
    break;

  case 55:
#line 197 "YA.y" /* yacc.c:1646  */
    {(yyval.op) = new_op(MORETHAN_);printf(">\n");}
#line 1785 "parser.c" /* yacc.c:1646  */
    break;

  case 56:
#line 198 "YA.y" /* yacc.c:1646  */
    {(yyval.op) = new_op(EQUALESSTHAN_);printf("<=\n");}
#line 1791 "parser.c" /* yacc.c:1646  */
    break;

  case 57:
#line 199 "YA.y" /* yacc.c:1646  */
    {(yyval.op) = new_op(EQUALMORETHAN_);printf(">=\n");}
#line 1797 "parser.c" /* yacc.c:1646  */
    break;

  case 58:
#line 200 "YA.y" /* yacc.c:1646  */
    {(yyval.op) = new_op(AND_);printf("and\n");}
#line 1803 "parser.c" /* yacc.c:1646  */
    break;

  case 59:
#line 201 "YA.y" /* yacc.c:1646  */
    {(yyval.op) = new_op(OR_);printf("or\n");}
#line 1809 "parser.c" /* yacc.c:1646  */
    break;

  case 60:
#line 204 "YA.y" /* yacc.c:1646  */
    {(yyval.literalExp) = new_literal_int((yyvsp[0].val));printf("INT_LIT\n");}
#line 1815 "parser.c" /* yacc.c:1646  */
    break;

  case 61:
#line 205 "YA.y" /* yacc.c:1646  */
    {(yyval.literalExp) = new_literal_float((yyvsp[0].valfloat));printf("FLOAT_LIT\n");}
#line 1821 "parser.c" /* yacc.c:1646  */
    break;

  case 62:
#line 206 "YA.y" /* yacc.c:1646  */
    {(yyval.literalExp) = new_literal_string((yyvsp[0].str));printf("STRING_LIT\n");}
#line 1827 "parser.c" /* yacc.c:1646  */
    break;

  case 63:
#line 207 "YA.y" /* yacc.c:1646  */
    {(yyval.literalExp) = new_literal_bool((yyvsp[0].booleano));printf("BOOL_LIT\n");}
#line 1833 "parser.c" /* yacc.c:1646  */
    break;

  case 64:
#line 211 "YA.y" /* yacc.c:1646  */
    { (yyval.CExp) = calc_exp_new_binop("+",(yyvsp[-2].CExp),(yyvsp[0].CExp));printf("exp + exp\n");}
#line 1839 "parser.c" /* yacc.c:1646  */
    break;

  case 65:
#line 212 "YA.y" /* yacc.c:1646  */
    { (yyval.CExp) = calc_exp_new_binop("-",(yyvsp[-2].CExp),(yyvsp[0].CExp));printf("exp - exp\n");}
#line 1845 "parser.c" /* yacc.c:1646  */
    break;

  case 66:
#line 213 "YA.y" /* yacc.c:1646  */
    { (yyval.CExp) = calc_exp_new_binop("*",(yyvsp[-2].CExp),(yyvsp[0].CExp));printf("exp * exp\n");}
#line 1851 "parser.c" /* yacc.c:1646  */
    break;

  case 67:
#line 214 "YA.y" /* yacc.c:1646  */
    { (yyval.CExp) = calc_exp_new_binop("/",(yyvsp[-2].CExp), (yyvsp[0].CExp));printf("exp / exp\n");}
#line 1857 "parser.c" /* yacc.c:1646  */
    break;

  case 68:
#line 215 "YA.y" /* yacc.c:1646  */
    { (yyval.CExp) = calc_exp_new_binop("^",(yyvsp[-2].CExp),(yyvsp[0].CExp));printf("exp ^ exp\n");}
#line 1863 "parser.c" /* yacc.c:1646  */
    break;

  case 69:
#line 216 "YA.y" /* yacc.c:1646  */
    { (yyval.CExp) = calc_exp_new_binop("-",0,(yyvsp[0].CExp));printf(" - exp \n");}
#line 1869 "parser.c" /* yacc.c:1646  */
    break;

  case 70:
#line 217 "YA.y" /* yacc.c:1646  */
    { (yyval.CExp) = calc_exp_new_par((yyvsp[-1].CExp));printf( "( exp ) \n");}
#line 1875 "parser.c" /* yacc.c:1646  */
    break;

  case 71:
#line 218 "YA.y" /* yacc.c:1646  */
    { (yyval.CExp) = calc_exp_new_literal((yyvsp[0].literalExp));printf("FOUND LITERAL\n");}
#line 1881 "parser.c" /* yacc.c:1646  */
    break;


#line 1885 "parser.c" /* yacc.c:1646  */
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
#line 221 "YA.y" /* yacc.c:1906  */


	/*
	*
	*
	*			SYMBOL TABLE
	*
	*
	*/

struct node{
	char *id;
	enum type_kind kind;
	int ocupado;
};


struct node table[267];	// hashtable
int size = 0;

int hash(char word[], int size)
{

  	int h = 0;
 	int i = 0;

  	while (word[i] != '\0')
  	{
      	h += word[i];
      	i++;
  	}
  	int c;
  	if(size == 0)
  		c = 0;
  	else
  		c = h % size;
 // 	printf("%d\n", h % size);
  return c;
}


enum type_kind lookup_type(char *id)
{
	int h = hash(id,size);


	while(true)
	{
		if(table[h].ocupado  == 1 &&
			strcmp(id,table[h].id) == 0)
		{
			return table[h].kind;
		}
		else
		{
			h = 0;
			while(table[h].ocupado != 1)
			{
				h++;
				h%= 267;
			}
		}
	}

	return 0;	// no symbol was found
}

void table_insert_1(char *id, type type){
	int h = hash(id,size);

	while(true)
	{
		if(table[h].ocupado  == 0)
		{
			table[h].id = strdup(id);
			table[h].kind = type->kind;
			table[h].ocupado = 1;
			break;
		}

		else{
			h = 0;
			while(table[h].ocupado != 1)
			{
				h++;
				h%= 267;
			}
		}
	}

	size++;
}


// declaracoes do genero, a,b,c,d,e : int;
void table_insert_2( belos_ids ids,type type)
{
	belos_ids root = ids;

	while(root != NULL)
	{
		table_insert_1(root->u.many_ids.id,type);
		root = root->u.many_ids.more_ids;
	}
}

void insertFunc(funcdeclar funcdeclar, type type){
	table_insert_1(funcdeclar->u.id,type);

}

void table_remove(char *id, type type){
	int h = hash(id,size);

	while(true){
		if(table[h].ocupado  == 1 && strcmp(table[h].id,id)==0 
			&& type->kind == table[h].kind)
		{
			table[size].ocupado = 0;
			break;
		}
		else if(table[h].ocupado == 1 && strcmp(table[h].id,id)!=0)
		{
			h = 0;
			while(table[h].ocupado != 1)
			{
				h++;
				h%= 267;
			}
		}
		else
			break; // no symbol was found
	}
	size--;
}


void yyerror (char const *s)
{
  fprintf (stderr, "%s\n", s);
}


int main (void)
{
  return yyparse();
}
