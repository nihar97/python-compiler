/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Skeleton implementation for Bison GLR parsers in C

   Copyright (C) 2002-2015 Free Software Foundation, Inc.

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

/* C GLR parser skeleton written by Paul Hilfinger.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "glr.c"

/* Pure parsers.  */
#define YYPURE 0






/* First part of user declarations.  */
#line 7 "apyc-parser.y" /* glr.c:240  */

    #include <iostream>
    #include <string>
    #include "apyc.h"
    #include "ast.h"
    #include <cassert>

    using namespace std;

    static AST_Ptr theTree;

    /* Utilities */

    /** Make a new "unop" node with function name TOKEN, operand EXPR1, and
     *  location LOC. */
    static AST_Ptr makeUnopExpr (const char* token, AST_Ptr expr1,
                                 Location loc);

    /** Make a new "binop" node with function name TOKEN, and operands EXPR1
     *  and EXPR2. */
    static AST_Ptr makeBinopExpr (const char* token,
                                  AST_Ptr expr1, AST_Ptr expr2);

    /** Type used for locations (@1, @2, etc.). */
    #define YYLTYPE Location

    #define YYLLOC_DEFAULT(Current, Rhs, N)                                 \
        do  {                                                               \
           if (N) {                                                         \
               Current = YYRHSLOC(Rhs, 1);                                  \
           } else {                                                         \
               Current = YYRHSLOC(Rhs, 0);                                  \
           }                                                                \
        } while (0)                                                         \

    static void yyerror (const char* s);

    static int yylex ();


#line 95 "apyc-parser.cc" /* glr.c:240  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
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
    STRING = 259,
    INT = 260,
    TYPE_VAR = 261,
    NEWLINE = 262,
    INDENT = 263,
    DEDENT = 264,
    POW = 265,
    GE = 266,
    LE = 267,
    EQ = 268,
    NE = 269,
    IN = 270,
    IS = 271,
    COLONCOLON = 272,
    FUNCARROW = 273,
    AND = 274,
    BREAK = 275,
    CLASS = 276,
    CONTINUE = 277,
    DEF = 278,
    ELIF = 279,
    ELSE = 280,
    FALSE = 281,
    FOR = 282,
    IF = 283,
    NATIVE = 284,
    NONE = 285,
    NOT = 286,
    OF = 287,
    OR = 288,
    PASS = 289,
    PRINT = 290,
    RETURN = 291,
    TRUE = 292,
    WHILE = 293,
    UNOP = 294
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 151 "apyc-parser.y" /* glr.c:244  */

    std::string* str;
    AST_Ptr ast;
    AST_Vect* astVect;
    const char* cstr;

#line 170 "apyc-parser.cc" /* glr.c:244  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);


/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Default (constant) value used for initialization for null
   right-hand sides.  Unlike the standard yacc.c template, here we set
   the default value of $$ to a zeroed-out value.  Since the default
   value is undefined, this behavior is technically correct.  */
static YYSTYPE yyval_default;
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;

/* Copy the second part of user declarations.  */

#line 219 "apyc-parser.cc" /* glr.c:263  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

#ifndef YYFREE
# define YYFREE free
#endif
#ifndef YYMALLOC
# define YYMALLOC malloc
#endif
#ifndef YYREALLOC
# define YYREALLOC realloc
#endif

#define YYSIZEMAX ((size_t) -1)

#ifdef __cplusplus
   typedef bool yybool;
#else
   typedef unsigned char yybool;
#endif
#define yytrue 1
#define yyfalse 0

#ifndef YYSETJMP
# include <setjmp.h>
# define YYJMP_BUF jmp_buf
# define YYSETJMP(Env) setjmp (Env)
/* Pacify clang.  */
# define YYLONGJMP(Env, Val) (longjmp (Env, Val), YYASSERT (0))
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


#ifndef YYASSERT
# define YYASSERT(Condition) ((void) ((Condition) || (abort (), 0)))
#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  98
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   869

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  58
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  72
/* YYNRULES -- Number of rules.  */
#define YYNRULES  172
/* YYNRULES -- Number of states.  */
#define YYNSTATES  292
/* YYMAXRHS -- Maximum number of symbols on right-hand side of rule.  */
#define YYMAXRHS 7
/* YYMAXLEFT -- Maximum number of symbols to the left of a handle
   accessed by $0, $-1, etc., in any rule.  */
#define YYMAXLEFT 0

/* YYTRANSLATE(X) -- Bison symbol number corresponding to X.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   294

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    43,     2,     2,
      47,    48,    44,    41,    53,    42,    55,    45,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    54,    57,
      39,    56,    40,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    49,     2,    50,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    51,     2,    52,     2,     2,     2,     2,
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
      35,    36,    37,    38,    46
};

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   199,   199,   200,   205,   206,   210,   210,   210,   213,
     217,   218,   219,   220,   221,   225,   226,   230,   230,   230,
     234,   235,   239,   244,   246,   250,   251,   255,   259,   260,
     261,   262,   263,   267,   269,   273,   279,   285,   292,   301,
     302,   307,   308,   312,   314,   319,   323,   326,   331,   332,
     334,   336,   341,   342,   344,   349,   350,   351,   352,   353,
     354,   355,   356,   357,   359,   364,   366,   368,   372,   374,
     379,   380,   382,   384,   386,   388,   390,   392,   394,   399,
     400,   401,   402,   403,   404,   407,   411,   413,   418,   419,
     421,   423,   425,   427,   429,   431,   436,   438,   443,   444,
     446,   447,   448,   452,   454,   456,   460,   462,   468,   472,
     477,   478,   479,   480,   481,   485,   490,   492,   494,   496,
     501,   503,   507,   509,   511,   513,   518,   527,   529,   533,
     534,   539,   546,   553,   558,   566,   567,   569,   574,   579,
     581,   586,   587,   592,   593,   596,   598,   606,   607,   614,
     615,   619,   623,   627,   628,   630,   631,   638,   642,   646,
     648,   653,   654,   658,   659,   664,   665,   670,   671,   676,
     677,   681,   682
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "STRING", "INT", "TYPE_VAR",
  "NEWLINE", "INDENT", "DEDENT", "\"**\"", "\">=\"", "\"<=\"", "\"==\"",
  "\"!=\"", "\"in\"", "\"is\"", "\"::\"", "\"->\"", "\"and\"", "\"break\"",
  "\"class\"", "\"continue\"", "\"def\"", "\"elif\"", "\"else\"",
  "\"False\"", "\"for\"", "\"if\"", "\"native\"", "\"None\"", "\"not\"",
  "\"of\"", "\"or\"", "\"pass\"", "\"print\"", "\"return\"", "\"True\"",
  "\"while\"", "'<'", "'>'", "'+'", "'-'", "'%'", "'*'", "'/'", "UNOP",
  "'('", "')'", "'['", "']'", "'{'", "'}'", "','", "':'", "'.'", "'='",
  "';'", "$accept", "program", "statements", "atom", "identifier",
  "literal", "stringliteral", "enclosure", "parenth_form", "list_display",
  "dict_display", "key_datum_list1", "key_datum", "primary",
  "attributeref", "subscript", "slice", "subscript_target", "slice_target",
  "low_bound", "high_bound", "call", "expression",
  "conditional_expression", "expr1", "expression_or_list", "comp_operator",
  "expr2", "left_compare", "expr3", "simple_stmt", "expression_stmt",
  "assignment_stmt", "target_list", "target_list2", "target", "print_stmt",
  "return_stmt", "break_stmt", "continue_stmt", "compound_stmt", "suite",
  "suite_stmts", "statement", "stmt_list", "if_stmt", "elifs",
  "else_clause", "while_stmt", "for_stmt", "funcdef", "funcbody", "native",
  "parameter_list", "parameters1", "parameter", "funcname", "classdef",
  "type_formals", "type_var_list1", "classbody", "type_annotation", "type",
  "type_var", "parameterized_type", "type_params", "type_list", "types",
  "expression_list1", "expression_list_opt_comma", "opt_comma", "opt_semi", YY_NULLPTR
};
#endif

#define YYPACT_NINF -204
#define YYTABLE_NINF -101

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const short int yypact[] =
{
     559,  -204,  -204,  -204,  -204,    42,  -204,    42,  -204,   723,
     652,  -204,   652,   -28,   652,   652,  -204,   652,   683,   683,
     612,   652,   284,    49,   559,  -204,   752,  -204,    57,  -204,
    -204,  -204,  -204,    28,    39,  -204,  -204,  -204,  -204,  -204,
      10,  -204,    23,  -204,  -204,   266,   780,    15,  -204,  -204,
      11,    33,    41,  -204,  -204,  -204,  -204,  -204,  -204,    89,
    -204,  -204,  -204,  -204,  -204,   -15,    76,  -204,    63,    28,
     106,   612,   652,    93,    96,  -204,    74,  -204,   599,  -204,
    -204,    77,  -204,    79,   129,   129,  -204,    98,    -9,    -5,
      33,   103,   112,   109,  -204,   116,  -204,   117,  -204,  -204,
      35,     8,  -204,  -204,  -204,   652,   652,    42,   652,   652,
     652,   652,  -204,  -204,  -204,  -204,  -204,   143,   157,  -204,
    -204,   683,   683,   683,   683,   683,   683,   683,   683,   599,
    -204,   665,   738,  -204,   738,  -204,   652,    42,   126,   123,
      22,    20,   652,   652,   484,  -204,   652,   484,  -204,  -204,
     738,  -204,   714,   131,   738,   137,   652,  -204,  -204,   652,
     127,   652,  -204,    35,    93,  -204,  -204,  -204,    35,  -204,
     142,   139,    38,   145,  -204,   112,  -204,    40,   179,  -204,
    -204,   802,   129,   222,   222,   129,   129,   129,   824,  -204,
    -204,  -204,  -204,  -204,   151,  -204,   200,   484,  -204,   192,
     158,  -204,   435,   159,   161,   163,   169,   213,   214,   124,
    -204,   218,  -204,   201,  -204,  -204,  -204,  -204,  -204,  -204,
    -204,   181,   174,    53,  -204,   652,    70,  -204,   652,  -204,
      69,  -204,  -204,  -204,  -204,    42,   182,   225,   232,  -204,
    -204,   180,   435,   484,   652,  -204,  -204,   386,   652,   185,
    -204,  -204,  -204,  -204,   228,    35,  -204,   190,  -204,  -204,
    -204,   200,  -204,  -204,   337,    72,  -204,  -204,  -204,   201,
     198,   241,   519,   199,   484,    35,  -204,   168,  -204,   180,
    -204,  -204,  -204,  -204,  -204,   484,  -204,  -204,   243,   124,
    -204,  -204
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const unsigned char yydefact[] =
{
       2,     9,    15,    11,   108,     0,   109,     0,    13,     0,
       0,    14,     0,   171,   104,   107,    12,     0,     0,     0,
       0,   167,     0,     0,     3,    28,     6,     7,    10,     8,
      17,    18,    19,    70,    29,    30,    31,   101,   102,    32,
      52,    45,    47,    85,    48,     0,    67,   171,    79,    80,
       0,   169,    88,    81,    82,    83,    84,   121,     4,     0,
     110,   111,   112,   113,   114,     0,   147,   145,     0,     0,
       0,     0,   167,     6,    70,    29,     0,    51,   172,   122,
     165,   103,   106,     0,    72,    71,    20,     0,     0,     0,
     169,   169,   169,     0,    24,   169,    25,     0,     1,     5,
       0,     0,    99,   158,    16,   167,    40,     0,    53,     0,
       0,     0,    57,    58,    59,    60,    61,    62,     0,    56,
      55,     0,     0,     0,     0,     0,     0,     0,     0,   172,
     123,     0,   170,    93,    90,   120,   167,     0,     0,     0,
       0,     0,     0,    40,     0,   124,   105,     0,    21,    94,
       0,    89,     0,     0,   170,     0,   170,   168,    22,   170,
       0,     0,   157,   161,   154,   152,   155,   153,     0,   160,
       0,     0,    39,     0,    33,   169,    50,     0,    49,    64,
      63,    65,    78,    73,    74,    77,    75,    76,    66,   125,
      86,    87,    97,    96,     0,    34,     0,     0,   139,   143,
     169,   141,     0,     0,     0,     0,     0,     0,     0,   129,
     115,     0,   166,   129,    91,    95,    92,    26,    23,    27,
     163,     0,   162,     0,    43,    42,    35,    54,     0,    44,
       0,   149,   151,   146,   144,   170,     0,     0,     0,   135,
     134,   171,     0,     0,    42,    35,   118,     0,     0,     0,
     126,   128,   116,   131,     0,     0,   159,     0,    41,    46,
     148,     0,   142,   140,     0,     0,   172,   136,   133,   129,
       0,     0,     0,     0,     0,     0,   164,    36,   150,   171,
     138,   132,    36,   119,   117,     0,   130,   156,     0,   129,
     137,   127
};

  /* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -204,  -204,   258,  -204,     0,  -204,    25,  -204,  -204,  -204,
    -204,  -204,   101,    26,    60,  -204,  -204,  -204,  -204,   118,
      27,  -204,    95,  -204,     4,    -7,   224,  -204,  -204,   226,
    -204,  -204,   152,   277,   141,    32,  -204,  -204,  -204,  -204,
    -204,  -132,  -174,   -23,    12,  -204,     2,  -203,  -204,  -204,
    -204,    50,    29,  -204,  -204,    59,  -204,  -204,  -204,  -204,
    -204,  -137,   -67,  -190,   -70,  -204,  -204,   128,   -11,   -78,
     -73,   -45
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const short int yydefgoto[] =
{
      -1,    23,   272,    25,    73,    27,    28,    29,    30,    31,
      32,    95,    96,    74,    75,    35,    36,    37,    38,   171,
     257,    39,    40,    41,    42,    43,   121,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,   209,   210,    58,   211,    60,   250,   251,    61,    62,
      63,   240,   241,   141,   200,   201,    68,    64,   139,   230,
     233,   102,   220,   166,    65,   103,   221,   222,    92,    93,
     133,    79
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const short int yytable[] =
{
      26,    99,   130,    81,   203,    66,   231,    67,    82,    26,
     253,     1,    59,    87,   162,   213,    77,   153,   155,   157,
      26,    26,   160,   232,    26,     1,    33,   170,   239,    78,
     167,   167,   136,   165,   169,    69,    59,   100,     1,   149,
     137,   162,   109,   151,   150,     1,    33,    33,   152,    98,
      33,   110,    89,    91,   -29,   163,   111,   168,   194,   109,
      34,   104,   234,   108,    87,   228,   281,   131,   239,    34,
     198,   278,   129,   111,   202,   105,   104,   106,    26,   280,
      34,    34,   163,   107,    34,   -35,   132,   -29,   -52,   -29,
     145,   108,   -29,   167,   134,  -100,   135,   175,   167,   173,
     164,   164,   227,   256,    33,    76,   255,   174,   138,    80,
     140,   269,    83,   176,   177,   178,    80,    97,   -35,   260,
     -35,   142,   261,   -35,   190,   101,   -37,   236,   144,    26,
     146,    26,    26,   147,    26,   204,   206,   195,    34,   122,
     199,   189,   286,   105,    26,   143,   148,    26,   248,   249,
      26,   107,    26,   289,    26,    33,   154,    33,    69,   158,
      69,    88,    90,   164,   192,   156,   193,    80,   164,   159,
      33,   161,   180,    33,   179,   196,    69,   197,    69,   218,
      69,   215,   192,   -36,   193,   167,   193,   216,   276,    34,
     224,    34,    34,   225,    34,   226,   267,    26,   109,   229,
      80,   172,    26,    80,    34,   167,   162,    34,   287,   100,
      34,   235,    34,   242,    34,   243,   -36,   244,   -36,   245,
     246,   -36,   247,    33,   -38,   252,   249,   255,    33,   254,
     263,    80,   122,   264,   288,   199,     2,   266,   172,   274,
     277,   212,    26,    26,    84,    85,   275,    26,   282,    99,
     283,   212,   290,   285,    97,   164,   219,    34,    24,    59,
     217,   205,    34,   265,    26,   125,   126,   127,    33,    33,
     128,   270,    26,    33,    26,   164,    59,   112,   113,   114,
     115,   116,   117,   191,    59,    26,    70,     1,     2,     3,
      33,   291,   268,   279,   262,     0,   223,   118,    33,     0,
      33,     0,    34,    34,     0,   119,   120,    34,     0,     0,
       8,    33,     0,     0,    11,    12,     0,     0,     0,     0,
     258,    16,     0,   259,    34,    18,    19,     0,     0,     0,
       0,    71,    34,    72,    34,    22,    94,     0,   271,   258,
       1,     2,     3,   273,     0,    34,     0,   181,   182,   183,
     184,   185,   186,   187,   188,     0,     0,     4,     5,     6,
       7,     0,     0,     8,     9,    10,   238,    11,    12,     0,
       0,    13,    14,    15,    16,    17,     0,     0,    18,    19,
       0,     0,     0,     0,    20,     0,    21,   271,    22,     1,
       2,     3,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     4,     5,     6,     7,
       0,     0,     8,     9,    10,     0,    11,    12,     0,     0,
      13,    14,    15,    16,    17,     0,     0,    18,    19,     0,
       0,     0,     0,    20,     0,    21,   207,    22,     1,     2,
       3,     0,   237,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     4,     0,     6,     0,     0,
       0,     8,     0,     0,   238,    11,    12,     0,     0,    13,
      14,    15,    16,     0,     0,     0,    18,    19,     0,     0,
       0,     0,    20,     0,    21,   207,    22,     1,     2,     3,
       0,   208,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     4,     0,     6,     0,     0,     0,
       8,     0,     0,     0,    11,    12,     0,     0,    13,    14,
      15,    16,     1,     2,     3,    18,    19,     0,   284,     0,
       0,    20,     0,    21,     0,    22,     0,     0,     0,     4,
       5,     6,     7,     0,     0,     8,     9,    10,     0,    11,
      12,     0,     0,    13,    14,    15,    16,    17,     0,     0,
      18,    19,     1,     2,     3,     0,    20,     0,    21,     0,
      22,     0,     0,     0,     0,     0,     0,     0,     0,     4,
       5,     6,     7,     0,     0,     8,     9,    10,     0,    11,
      12,     0,     0,    13,    14,    15,    16,    17,     0,     0,
      18,    19,     1,     2,     3,     0,    20,     0,    21,     0,
      22,     0,     0,     0,     0,     1,     2,     3,     0,     4,
       0,     6,     0,     0,     0,     8,     0,     0,     0,    11,
      12,     0,     0,    13,    14,    15,    16,     0,     8,     0,
      18,    19,    11,    12,     0,     0,    20,     0,    21,    16,
      22,     0,     0,    18,    19,     1,     2,     3,     0,    71,
      86,    72,     0,    22,     0,     0,     0,     0,     1,     2,
       3,     0,     0,     0,     0,     0,     0,     0,     8,     0,
       0,     0,    11,    12,     0,     0,     1,     2,     3,    16,
       0,     8,     0,    18,    19,    11,    12,     0,     0,    71,
       0,    72,    16,    22,     0,     0,    18,    19,     0,     8,
       0,     0,    20,    11,    21,     0,    22,     1,     2,     3,
      16,     0,     0,     0,    18,    19,     1,     2,     3,     0,
      71,     0,    72,     0,    22,     0,     0,     0,     0,     0,
       8,     1,     2,     3,    11,     0,     0,     0,     0,     8,
       0,    16,     0,    11,     0,     0,     0,     0,     0,     0,
      16,    71,   214,    72,     8,    22,     0,    -6,    11,   100,
      20,     0,    21,     0,    22,    16,     0,     0,     0,     0,
       0,     0,     0,     0,   101,    71,     0,    72,     0,    22,
     122,   112,   113,   114,   115,   116,   117,     0,     0,     0,
      -6,     0,    -6,     0,     0,    -6,     0,     0,   -98,     0,
       0,   118,   122,   -69,   -69,   -69,   -69,   -69,   -69,   119,
     120,   123,   124,   125,   126,   127,     0,     0,     0,     0,
       0,     0,     0,   -69,   122,   -68,   -68,   -68,   -68,   -68,
     -68,   -69,   -69,   123,   124,   125,   126,   127,     0,     0,
       0,     0,     0,     0,     0,   -68,     0,     0,     0,     0,
       0,     0,     0,   -68,   -68,   123,   124,   125,   126,   127
};

static const short int yycheck[] =
{
       0,    24,    47,    14,   141,     5,   196,     7,    15,     9,
     213,     3,     0,    20,     6,   147,    12,    90,    91,    92,
      20,    21,    95,   197,    24,     3,     0,   105,   202,    57,
     100,   101,    47,   100,   101,     9,    24,    17,     3,    48,
      55,     6,    19,    48,    53,     3,    20,    21,    53,     0,
      24,    28,    20,    21,    15,    47,    33,    49,   136,    19,
       0,     4,   199,    53,    71,    25,   269,    56,   242,     9,
      48,   261,    57,    33,    54,    47,     4,    49,    78,     7,
      20,    21,    47,    55,    24,    15,    53,    48,    50,    50,
      78,    53,    53,   163,    53,    56,     7,   108,   168,   106,
     100,   101,   175,    50,    78,    10,    53,   107,    32,    14,
      47,   243,    17,   109,   110,   111,    21,    22,    48,    50,
      50,    15,    53,    53,   131,    32,    56,   200,    54,   129,
      53,   131,   132,    54,   134,   142,   143,   137,    78,    10,
     140,   129,   274,    47,   144,    49,    48,   147,    24,    25,
     150,    55,   152,   285,   154,   129,    53,   131,   132,    50,
     134,    20,    21,   163,   132,    53,   134,    72,   168,    53,
     144,    54,    15,   147,    31,    49,   150,    54,   152,    52,
     154,    50,   150,    15,   152,   255,   154,    50,   255,   129,
      48,   131,   132,    54,   134,    50,   241,   197,    19,    48,
     105,   106,   202,   108,   144,   275,     6,   147,   275,    17,
     150,    53,   152,    54,   154,    54,    48,    54,    50,    50,
       7,    53,     8,   197,    56,     7,    25,    53,   202,    48,
      48,   136,    10,     8,   279,   235,     4,    57,   143,    54,
      50,   146,   242,   243,    18,    19,    18,   247,    50,   272,
       9,   156,     9,    54,   159,   255,   161,   197,     0,   247,
     159,   143,   202,   238,   264,    43,    44,    45,   242,   243,
      46,   244,   272,   247,   274,   275,   264,    11,    12,    13,
      14,    15,    16,   131,   272,   285,     9,     3,     4,     5,
     264,   289,   242,   264,   235,    -1,   168,    31,   272,    -1,
     274,    -1,   242,   243,    -1,    39,    40,   247,    -1,    -1,
      26,   285,    -1,    -1,    30,    31,    -1,    -1,    -1,    -1,
     225,    37,    -1,   228,   264,    41,    42,    -1,    -1,    -1,
      -1,    47,   272,    49,   274,    51,    52,    -1,     1,   244,
       3,     4,     5,   248,    -1,   285,    -1,   121,   122,   123,
     124,   125,   126,   127,   128,    -1,    -1,    20,    21,    22,
      23,    -1,    -1,    26,    27,    28,    29,    30,    31,    -1,
      -1,    34,    35,    36,    37,    38,    -1,    -1,    41,    42,
      -1,    -1,    -1,    -1,    47,    -1,    49,     1,    51,     3,
       4,     5,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    20,    21,    22,    23,
      -1,    -1,    26,    27,    28,    -1,    30,    31,    -1,    -1,
      34,    35,    36,    37,    38,    -1,    -1,    41,    42,    -1,
      -1,    -1,    -1,    47,    -1,    49,     1,    51,     3,     4,
       5,    -1,     7,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    20,    -1,    22,    -1,    -1,
      -1,    26,    -1,    -1,    29,    30,    31,    -1,    -1,    34,
      35,    36,    37,    -1,    -1,    -1,    41,    42,    -1,    -1,
      -1,    -1,    47,    -1,    49,     1,    51,     3,     4,     5,
      -1,     7,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    20,    -1,    22,    -1,    -1,    -1,
      26,    -1,    -1,    -1,    30,    31,    -1,    -1,    34,    35,
      36,    37,     3,     4,     5,    41,    42,    -1,     9,    -1,
      -1,    47,    -1,    49,    -1,    51,    -1,    -1,    -1,    20,
      21,    22,    23,    -1,    -1,    26,    27,    28,    -1,    30,
      31,    -1,    -1,    34,    35,    36,    37,    38,    -1,    -1,
      41,    42,     3,     4,     5,    -1,    47,    -1,    49,    -1,
      51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    20,
      21,    22,    23,    -1,    -1,    26,    27,    28,    -1,    30,
      31,    -1,    -1,    34,    35,    36,    37,    38,    -1,    -1,
      41,    42,     3,     4,     5,    -1,    47,    -1,    49,    -1,
      51,    -1,    -1,    -1,    -1,     3,     4,     5,    -1,    20,
      -1,    22,    -1,    -1,    -1,    26,    -1,    -1,    -1,    30,
      31,    -1,    -1,    34,    35,    36,    37,    -1,    26,    -1,
      41,    42,    30,    31,    -1,    -1,    47,    -1,    49,    37,
      51,    -1,    -1,    41,    42,     3,     4,     5,    -1,    47,
      48,    49,    -1,    51,    -1,    -1,    -1,    -1,     3,     4,
       5,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,    -1,
      -1,    -1,    30,    31,    -1,    -1,     3,     4,     5,    37,
      -1,    26,    -1,    41,    42,    30,    31,    -1,    -1,    47,
      -1,    49,    37,    51,    -1,    -1,    41,    42,    -1,    26,
      -1,    -1,    47,    30,    49,    -1,    51,     3,     4,     5,
      37,    -1,    -1,    -1,    41,    42,     3,     4,     5,    -1,
      47,    -1,    49,    -1,    51,    -1,    -1,    -1,    -1,    -1,
      26,     3,     4,     5,    30,    -1,    -1,    -1,    -1,    26,
      -1,    37,    -1,    30,    -1,    -1,    -1,    -1,    -1,    -1,
      37,    47,    48,    49,    26,    51,    -1,    15,    30,    17,
      47,    -1,    49,    -1,    51,    37,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    32,    47,    -1,    49,    -1,    51,
      10,    11,    12,    13,    14,    15,    16,    -1,    -1,    -1,
      48,    -1,    50,    -1,    -1,    53,    -1,    -1,    56,    -1,
      -1,    31,    10,    11,    12,    13,    14,    15,    16,    39,
      40,    41,    42,    43,    44,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    10,    11,    12,    13,    14,    15,
      16,    39,    40,    41,    42,    43,    44,    45,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    39,    40,    41,    42,    43,    44,    45
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     3,     4,     5,    20,    21,    22,    23,    26,    27,
      28,    30,    31,    34,    35,    36,    37,    38,    41,    42,
      47,    49,    51,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    71,    72,    73,    74,    75,    76,    79,
      80,    81,    82,    83,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,   101,   102,
     103,   106,   107,   108,   115,   122,    62,    62,   114,    71,
      91,    47,    49,    62,    71,    72,    80,    82,    57,   129,
      80,   126,    83,    80,    87,    87,    48,    83,    92,    93,
      92,    93,   126,   127,    52,    69,    70,    80,     0,   101,
      17,    32,   119,   123,     4,    47,    49,    55,    53,    19,
      28,    33,    11,    12,    13,    14,    15,    16,    31,    39,
      40,    84,    10,    41,    42,    43,    44,    45,    84,    57,
     129,    56,    53,   128,    53,     7,    47,    55,    32,   116,
      47,   111,    15,    49,    54,   102,    53,    54,    48,    48,
      53,    48,    53,   128,    53,   128,    53,   128,    50,    53,
     128,    54,     6,    47,    62,   120,   121,   122,    49,   120,
     127,    77,    80,    83,    62,   126,    82,    82,    82,    31,
      15,    87,    87,    87,    87,    87,    87,    87,    87,   102,
      83,    90,    93,    93,   127,    62,    49,    54,    48,    62,
     112,   113,    54,   119,    83,    77,    83,     1,     7,    99,
     100,   102,    80,    99,    48,    50,    50,    70,    52,    80,
     120,   124,   125,   125,    48,    54,    50,   128,    25,    48,
     117,   121,   100,   118,   119,    53,   128,     7,    29,   100,
     109,   110,    54,    54,    54,    50,     7,     8,    24,    25,
     104,   105,     7,   105,    48,    53,    50,    78,    80,    80,
      50,    53,   113,    48,     8,    64,    57,   129,   109,    99,
      78,     1,    60,    80,    54,    18,   120,    50,   121,   110,
       7,   105,    50,     9,     9,    54,    99,   120,   129,    99,
       9,   104
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    58,    59,    59,    60,    60,    61,    61,    61,    62,
      63,    63,    63,    63,    63,    64,    64,    65,    65,    65,
      66,    66,    67,    68,    68,    69,    69,    70,    71,    71,
      71,    71,    71,    72,    72,    73,    74,    75,    76,    77,
      77,    78,    78,    79,    79,    80,    81,    81,    82,    82,
      82,    82,    83,    83,    83,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    85,    85,    85,    86,    86,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    88,
      88,    88,    88,    88,    88,    89,    90,    90,    91,    91,
      91,    91,    91,    91,    91,    91,    92,    92,    93,    93,
      93,    93,    93,    94,    94,    94,    95,    95,    96,    97,
      98,    98,    98,    98,    98,    99,   100,   100,   100,   100,
     101,   101,   102,   102,   102,   102,   103,   104,   104,   105,
     105,   106,   107,   108,   108,   109,   109,   109,   110,   111,
     111,   112,   112,   113,   113,   114,   115,   116,   116,   117,
     117,   118,   119,   120,   120,   120,   120,   121,   122,   123,
     123,   124,   124,   125,   125,   126,   126,   127,   127,   128,
     128,   129,   129
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     0,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     1,
       2,     3,     3,     4,     2,     1,     3,     3,     1,     1,
       1,     1,     1,     3,     3,     4,     6,     4,     6,     1,
       0,     1,     0,     4,     4,     1,     5,     1,     1,     3,
       3,     2,     1,     2,     4,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     3,     3,     1,     3,     3,
       1,     2,     2,     3,     3,     3,     3,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     1,     3,
       2,     4,     4,     2,     3,     4,     3,     3,     1,     2,
       1,     1,     1,     2,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     4,     2,     4,
       2,     1,     2,     2,     3,     3,     5,     5,     1,     0,
       3,     5,     7,     6,     5,     1,     2,     5,     3,     2,
       4,     1,     3,     1,     2,     1,     5,     0,     4,     1,
       3,     1,     2,     1,     1,     1,     5,     1,     2,     4,
       2,     0,     1,     1,     3,     1,     3,     0,     2,     0,
       1,     0,     1
};


/* YYDPREC[RULE-NUM] -- Dynamic precedence of rule #RULE-NUM (0 if none).  */
static const unsigned char yydprec[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0
};

/* YYMERGER[RULE-NUM] -- Index of merging function for rule #RULE-NUM.  */
static const unsigned char yymerger[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0
};

/* YYIMMEDIATE[RULE-NUM] -- True iff rule #RULE-NUM is not to be deferred, as
   in the case of predicates.  */
static const yybool yyimmediate[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0
};

/* YYCONFLP[YYPACT[STATE-NUM]] -- Pointer into YYCONFL of start of
   list of conflicting reductions corresponding to action entry for
   state STATE-NUM in yytable.  0 means no conflicts.  The list in
   yyconfl is terminated by a rule number of 0.  */
static const unsigned char yyconflp[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     9,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    17,     0,    11,     0,    13,
       0,     0,    15,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    19,     0,
      21,     0,     0,    23,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    25,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    27,     0,    29,     0,
       0,    31,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     1,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       3,     0,     5,     0,     0,     7,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0
};

/* YYCONFL[I] -- lists of conflicting rule numbers, each terminated by
   0, pointed into by YYCONFLP.  */
static const short int yyconfl[] =
{
       0,    98,     0,    98,     0,    98,     0,    98,     0,   100,
       0,   100,     0,   100,     0,   100,     0,    37,     0,    37,
       0,    37,     0,    37,     0,    38,     0,    38,     0,    38,
       0,    38,     0
};

/* Error token number */
#define YYTERROR 1


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

# define YYRHSLOC(Rhs, K) ((Rhs)[K].yystate.yyloc)


YYSTYPE yylval;
YYLTYPE yylloc;

int yynerrs;
int yychar;

static const int YYEOF = 0;
static const int YYEMPTY = -2;

typedef enum { yyok, yyaccept, yyabort, yyerr } YYRESULTTAG;

#define YYCHK(YYE)                              \
  do {                                          \
    YYRESULTTAG yychk_flag = YYE;               \
    if (yychk_flag != yyok)                     \
      return yychk_flag;                        \
  } while (0)

#if YYDEBUG

# ifndef YYFPRINTF
#  define YYFPRINTF fprintf
# endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YYDPRINTF(Args)                        \
  do {                                          \
    if (yydebug)                                \
      YYFPRINTF Args;                           \
  } while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                  \
  do {                                                                  \
    if (yydebug)                                                        \
      {                                                                 \
        YYFPRINTF (stderr, "%s ", Title);                               \
        yy_symbol_print (stderr, Type, Value, Location);        \
        YYFPRINTF (stderr, "\n");                                       \
      }                                                                 \
  } while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;

struct yyGLRStack;
static void yypstack (struct yyGLRStack* yystackp, size_t yyk)
  YY_ATTRIBUTE_UNUSED;
static void yypdumpstack (struct yyGLRStack* yystackp)
  YY_ATTRIBUTE_UNUSED;

#else /* !YYDEBUG */

# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)

#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYMAXDEPTH * sizeof (GLRStackItem)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

/* Minimum number of free items on the stack allowed after an
   allocation.  This is to allow allocation and initialization
   to be completed by functions that call yyexpandGLRStack before the
   stack is expanded, thus insuring that all necessary pointers get
   properly redirected to new data.  */
#define YYHEADROOM 2

#ifndef YYSTACKEXPANDABLE
#  define YYSTACKEXPANDABLE 1
#endif

#if YYSTACKEXPANDABLE
# define YY_RESERVE_GLRSTACK(Yystack)                   \
  do {                                                  \
    if (Yystack->yyspaceLeft < YYHEADROOM)              \
      yyexpandGLRStack (Yystack);                       \
  } while (0)
#else
# define YY_RESERVE_GLRSTACK(Yystack)                   \
  do {                                                  \
    if (Yystack->yyspaceLeft < YYHEADROOM)              \
      yyMemoryExhausted (Yystack);                      \
  } while (0)
#endif


#if YYERROR_VERBOSE

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
static size_t
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      size_t yyn = 0;
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
    return strlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

#endif /* !YYERROR_VERBOSE */

/** State numbers, as in LALR(1) machine */
typedef int yyStateNum;

/** Rule numbers, as in LALR(1) machine */
typedef int yyRuleNum;

/** Grammar symbol */
typedef int yySymbol;

/** Item references, as in LALR(1) machine */
typedef short int yyItemNum;

typedef struct yyGLRState yyGLRState;
typedef struct yyGLRStateSet yyGLRStateSet;
typedef struct yySemanticOption yySemanticOption;
typedef union yyGLRStackItem yyGLRStackItem;
typedef struct yyGLRStack yyGLRStack;

struct yyGLRState {
  /** Type tag: always true.  */
  yybool yyisState;
  /** Type tag for yysemantics.  If true, yysval applies, otherwise
   *  yyfirstVal applies.  */
  yybool yyresolved;
  /** Number of corresponding LALR(1) machine state.  */
  yyStateNum yylrState;
  /** Preceding state in this stack */
  yyGLRState* yypred;
  /** Source position of the last token produced by my symbol */
  size_t yyposn;
  union {
    /** First in a chain of alternative reductions producing the
     *  non-terminal corresponding to this state, threaded through
     *  yynext.  */
    yySemanticOption* yyfirstVal;
    /** Semantic value for this state.  */
    YYSTYPE yysval;
  } yysemantics;
  /** Source location for this state.  */
  YYLTYPE yyloc;
};

struct yyGLRStateSet {
  yyGLRState** yystates;
  /** During nondeterministic operation, yylookaheadNeeds tracks which
   *  stacks have actually needed the current lookahead.  During deterministic
   *  operation, yylookaheadNeeds[0] is not maintained since it would merely
   *  duplicate yychar != YYEMPTY.  */
  yybool* yylookaheadNeeds;
  size_t yysize, yycapacity;
};

struct yySemanticOption {
  /** Type tag: always false.  */
  yybool yyisState;
  /** Rule number for this reduction */
  yyRuleNum yyrule;
  /** The last RHS state in the list of states to be reduced.  */
  yyGLRState* yystate;
  /** The lookahead for this reduction.  */
  int yyrawchar;
  YYSTYPE yyval;
  YYLTYPE yyloc;
  /** Next sibling in chain of options.  To facilitate merging,
   *  options are chained in decreasing order by address.  */
  yySemanticOption* yynext;
};

/** Type of the items in the GLR stack.  The yyisState field
 *  indicates which item of the union is valid.  */
union yyGLRStackItem {
  yyGLRState yystate;
  yySemanticOption yyoption;
};

struct yyGLRStack {
  int yyerrState;
  /* To compute the location of the error token.  */
  yyGLRStackItem yyerror_range[3];

  YYJMP_BUF yyexception_buffer;
  yyGLRStackItem* yyitems;
  yyGLRStackItem* yynextFree;
  size_t yyspaceLeft;
  yyGLRState* yysplitPoint;
  yyGLRState* yylastDeleted;
  yyGLRStateSet yytops;
};

#if YYSTACKEXPANDABLE
static void yyexpandGLRStack (yyGLRStack* yystackp);
#endif

static _Noreturn void
yyFail (yyGLRStack* yystackp, const char* yymsg)
{
  if (yymsg != YY_NULLPTR)
    yyerror (yymsg);
  YYLONGJMP (yystackp->yyexception_buffer, 1);
}

static _Noreturn void
yyMemoryExhausted (yyGLRStack* yystackp)
{
  YYLONGJMP (yystackp->yyexception_buffer, 2);
}

#if YYDEBUG || YYERROR_VERBOSE
/** A printable representation of TOKEN.  */
static inline const char*
yytokenName (yySymbol yytoken)
{
  if (yytoken == YYEMPTY)
    return "";

  return yytname[yytoken];
}
#endif

/** Fill in YYVSP[YYLOW1 .. YYLOW0-1] from the chain of states starting
 *  at YYVSP[YYLOW0].yystate.yypred.  Leaves YYVSP[YYLOW1].yystate.yypred
 *  containing the pointer to the next state in the chain.  */
static void yyfillin (yyGLRStackItem *, int, int) YY_ATTRIBUTE_UNUSED;
static void
yyfillin (yyGLRStackItem *yyvsp, int yylow0, int yylow1)
{
  int i;
  yyGLRState *s = yyvsp[yylow0].yystate.yypred;
  for (i = yylow0-1; i >= yylow1; i -= 1)
    {
#if YYDEBUG
      yyvsp[i].yystate.yylrState = s->yylrState;
#endif
      yyvsp[i].yystate.yyresolved = s->yyresolved;
      if (s->yyresolved)
        yyvsp[i].yystate.yysemantics.yysval = s->yysemantics.yysval;
      else
        /* The effect of using yysval or yyloc (in an immediate rule) is
         * undefined.  */
        yyvsp[i].yystate.yysemantics.yyfirstVal = YY_NULLPTR;
      yyvsp[i].yystate.yyloc = s->yyloc;
      s = yyvsp[i].yystate.yypred = s->yypred;
    }
}

/* Do nothing if YYNORMAL or if *YYLOW <= YYLOW1.  Otherwise, fill in
 * YYVSP[YYLOW1 .. *YYLOW-1] as in yyfillin and set *YYLOW = YYLOW1.
 * For convenience, always return YYLOW1.  */
static inline int yyfill (yyGLRStackItem *, int *, int, yybool)
     YY_ATTRIBUTE_UNUSED;
static inline int
yyfill (yyGLRStackItem *yyvsp, int *yylow, int yylow1, yybool yynormal)
{
  if (!yynormal && yylow1 < *yylow)
    {
      yyfillin (yyvsp, *yylow, yylow1);
      *yylow = yylow1;
    }
  return yylow1;
}

/** Perform user action for rule number YYN, with RHS length YYRHSLEN,
 *  and top stack item YYVSP.  YYLVALP points to place to put semantic
 *  value ($$), and yylocp points to place for location information
 *  (@$).  Returns yyok for normal return, yyaccept for YYACCEPT,
 *  yyerr for YYERROR, yyabort for YYABORT.  */
static YYRESULTTAG
yyuserAction (yyRuleNum yyn, size_t yyrhslen, yyGLRStackItem* yyvsp,
              yyGLRStack* yystackp,
              YYSTYPE* yyvalp, YYLTYPE *yylocp)
{
  yybool yynormal YY_ATTRIBUTE_UNUSED = (yystackp->yysplitPoint == YY_NULLPTR);
  int yylow;
  YYUSE (yyvalp);
  YYUSE (yylocp);
  YYUSE (yyrhslen);
# undef yyerrok
# define yyerrok (yystackp->yyerrState = 0)
# undef YYACCEPT
# define YYACCEPT return yyaccept
# undef YYABORT
# define YYABORT return yyabort
# undef YYERROR
# define YYERROR return yyerrok, yyerr
# undef YYRECOVERING
# define YYRECOVERING() (yystackp->yyerrState != 0)
# undef yyclearin
# define yyclearin (yychar = YYEMPTY)
# undef YYFILL
# define YYFILL(N) yyfill (yyvsp, &yylow, N, yynormal)
# undef YYBACKUP
# define YYBACKUP(Token, Value)                                              \
  return yyerror (YY_("syntax error: cannot back up")),     \
         yyerrok, yyerr

  yylow = 1;
  if (yyrhslen == 0)
    *yyvalp = yyval_default;
  else
    *yyvalp = yyvsp[YYFILL (1-yyrhslen)].yystate.yysemantics.yysval;
  YYLLOC_DEFAULT ((*yylocp), (yyvsp - yyrhslen), yyrhslen);
  yystackp->yyerror_range[1].yystate.yyloc = *yylocp;

  switch (yyn)
    {
        case 2:
#line 199 "apyc-parser.y" /* glr.c:816  */
    { theTree = NODE (MODULE_AST); }
#line 1473 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 3:
#line 201 "apyc-parser.y" /* glr.c:816  */
    { theTree = NODE (MODULE_AST, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.astVect)); }
#line 1479 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 4:
#line 205 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).astVect) = new AST_Vect(1, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)); }
#line 1485 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 5:
#line 207 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).astVect) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.astVect); ((*yyvalp).astVect)->push_back((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)); }
#line 1491 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 9:
#line 213 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = makeId (*(((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc)); }
#line 1497 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 11:
#line 218 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = LEAF(INT_LITERAL_AST, *(((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc)); }
#line 1503 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 12:
#line 219 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (TRUE_AST); ((*yyvalp).ast)->setLoc((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc)); }
#line 1509 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 13:
#line 220 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (FALSE_AST); ((*yyvalp).ast)->setLoc((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc)); }
#line 1515 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 14:
#line 221 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (NONE_AST); ((*yyvalp).ast)->setLoc((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc)); }
#line 1521 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 15:
#line 225 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = LEAF(STRING_LITERAL_AST, *(((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc)); }
#line 1527 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 16:
#line 227 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast); ((*yyvalp).ast)->appendText(*(((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str)); }
#line 1533 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 20:
#line 234 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (TUPLE_AST); }
#line 1539 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 21:
#line 236 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast); }
#line 1545 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 22:
#line 240 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (LIST_DISPLAY_AST, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.astVect)); ((*yyvalp).ast)->setLoc ((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc)); }
#line 1551 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 23:
#line 245 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (DICT_DISPLAY_AST, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.astVect)); ((*yyvalp).ast)->setLoc ((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yyloc)); }
#line 1557 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 24:
#line 246 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (DICT_DISPLAY_AST); ((*yyvalp).ast)->setLoc ((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc)); }
#line 1563 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 25:
#line 250 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).astVect) = new AST_Vect(1, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)); }
#line 1569 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 26:
#line 252 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).astVect) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.astVect); ((*yyvalp).astVect)->push_back ((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)); }
#line 1575 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 27:
#line 256 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (PAIR_AST, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)); }
#line 1581 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 33:
#line 268 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (ATTRIBUTEREF_AST, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)); ((*yyvalp).ast)->setLoc((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc)); }
#line 1587 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 34:
#line 270 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (ATTRIBUTEREF_AST, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)); ((*yyvalp).ast)->setLoc((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc)); }
#line 1593 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 35:
#line 274 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (SUBSCRIPT_AST,
                             makeId("__getitem__", (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast)->location ()),
                             (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)); ((*yyvalp).ast)->setLoc((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yyloc)); }
#line 1601 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 36:
#line 280 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (SLICE_AST,
                             makeId ("__getslice__", (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.ast)->location ()),
                             (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)); ((*yyvalp).ast)->setLoc((((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yyloc)); }
#line 1609 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 37:
#line 286 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (SUBSCRIPT_ASSIGN_AST,
                             makeId ("__setitem__", (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast)->location ()),
                             (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), NODE (NEXT_VALUE_AST)); ((*yyvalp).ast)->setLoc((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yyloc));
                }
#line 1618 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 38:
#line 293 "apyc-parser.y" /* glr.c:816  */
    { AST_Ptr obj = (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.ast), low = (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), high = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), result;
                  result = NODE (SLICE_ASSIGN_AST,
                                 makeId ("__setslice__", (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.ast)->location ()),
                                 (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), NODE (NEXT_VALUE_AST)); 
                  ((*yyvalp).ast) = result; ((*yyvalp).ast)->setLoc((((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yyloc));}
#line 1628 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 40:
#line 303 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = LEAF (INT_LITERAL_AST, "0", 0); }
#line 1634 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 42:
#line 309 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = LEAF (INT_LITERAL_AST, "0x3fffffff", 0); }
#line 1640 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 43:
#line 313 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (CALL_AST, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.astVect)); ((*yyvalp).ast)->setLoc((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yyloc)); }
#line 1646 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 44:
#line 315 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (CALL_AST, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.astVect)); ((*yyvalp).ast)->setLoc((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yyloc)); }
#line 1652 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 46:
#line 324 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (IF_EXPR_AST, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
                  ((*yyvalp).ast)->setLoc((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast)->location ()); ((*yyvalp).ast)->setLoc((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yyloc)); }
#line 1659 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 49:
#line 333 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE(OR_AST, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)); ((*yyvalp).ast)->setLoc((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc)); }
#line 1665 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 50:
#line 335 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE(AND_AST, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)); ((*yyvalp).ast)->setLoc((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc)); }
#line 1671 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 51:
#line 337 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = makeUnopExpr ("__not__", (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc)); }
#line 1677 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 53:
#line 343 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (TUPLE_AST, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)); ((*yyvalp).ast)->setLoc((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc)); }
#line 1683 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 54:
#line 345 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (TUPLE_AST, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.astVect)); ((*yyvalp).ast)->setLoc((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yyloc)); }
#line 1689 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 55:
#line 349 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).cstr) = "__gt__"; }
#line 1695 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 56:
#line 350 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).cstr) = "__lt__"; }
#line 1701 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 57:
#line 351 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).cstr) = "__ge__"; }
#line 1707 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 58:
#line 352 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).cstr) = "__le__"; }
#line 1713 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 59:
#line 353 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).cstr) = "__eq__"; }
#line 1719 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 60:
#line 354 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).cstr) = "__ne__"; }
#line 1725 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 61:
#line 355 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).cstr) = "__in__"; }
#line 1731 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 62:
#line 356 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).cstr) = "__is__"; }
#line 1737 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 63:
#line 358 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).cstr) = "__notin__"; }
#line 1743 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 64:
#line 360 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).cstr) = "__isnot__"; }
#line 1749 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 65:
#line 365 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (COMPARE_AST, makeId((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.cstr), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc)), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)); }
#line 1755 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 66:
#line 367 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (COMPARE_AST, makeId((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.cstr), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc)), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)); }
#line 1761 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 68:
#line 373 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (LEFT_COMPARE_AST, makeId((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.cstr), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc)), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)); }
#line 1767 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 69:
#line 375 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (LEFT_COMPARE_AST, makeId((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.cstr), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc)), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)); }
#line 1773 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 71:
#line 381 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = makeUnopExpr ("__neg__", (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc)); }
#line 1779 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 72:
#line 383 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = makeUnopExpr ("__pos__", (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc)); }
#line 1785 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 73:
#line 385 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = makeBinopExpr ("__add__", (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)); }
#line 1791 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 74:
#line 387 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = makeBinopExpr ("__sub__", (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)); }
#line 1797 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 75:
#line 389 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = makeBinopExpr ("__mul__", (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)); }
#line 1803 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 76:
#line 391 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = makeBinopExpr ("__floordiv__", (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)); }
#line 1809 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 77:
#line 393 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = makeBinopExpr ("__mod__", (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)); }
#line 1815 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 78:
#line 395 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = makeBinopExpr ("__pow__", (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)); }
#line 1821 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 86:
#line 412 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (ASSIGN_AST, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)); ((*yyvalp).ast)->setLoc((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc)); }
#line 1827 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 87:
#line 414 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (ASSIGN_AST, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)); ((*yyvalp).ast)->setLoc((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc)); }
#line 1833 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 89:
#line 420 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast); }
#line 1839 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 90:
#line 422 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (TARGET_LIST_AST, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)); ((*yyvalp).ast)->setLoc((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc)); }
#line 1845 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 91:
#line 424 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (TARGET_LIST_AST, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)); ((*yyvalp).ast)->setLoc((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yyloc)); }
#line 1851 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 92:
#line 426 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (TARGET_LIST_AST, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)); ((*yyvalp).ast)->setLoc ((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yyloc)); }
#line 1857 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 93:
#line 428 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast); }
#line 1863 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 94:
#line 430 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast); ((*yyvalp).ast)->setLoc ((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc)); }
#line 1869 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 95:
#line 432 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast); ((*yyvalp).ast)->setLoc ((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yyloc)); }
#line 1875 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 96:
#line 437 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (TARGET_LIST_AST, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)); ((*yyvalp).ast)->setLoc((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc)); }
#line 1881 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 97:
#line 439 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast); ((*yyvalp).ast)->add ((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)); }
#line 1887 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 99:
#line 445 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (TYPED_ID_AST, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)); ((*yyvalp).ast)->setLoc((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc)); }
#line 1893 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 103:
#line 453 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (PRINTLN_AST, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.astVect)); ((*yyvalp).ast)->setLoc ((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc)); }
#line 1899 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 104:
#line 455 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (PRINTLN_AST); ((*yyvalp).ast)->setLoc ((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc)); }
#line 1905 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 105:
#line 457 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (PRINT_AST, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.astVect)); ((*yyvalp).ast)->setLoc ((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc)); }
#line 1911 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 106:
#line 461 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (RETURN_AST, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)); ((*yyvalp).ast)->setLoc ((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc)); }
#line 1917 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 107:
#line 463 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (RETURN_AST, NODE (NONE_AST));
                  ((*yyvalp).ast)->setLoc ((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc)); 
                }
#line 1925 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 108:
#line 469 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (BREAK_AST); ((*yyvalp).ast)->setLoc ((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc)); }
#line 1931 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 109:
#line 473 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (CONTINUE_AST); ((*yyvalp).ast)->setLoc ((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc)); }
#line 1937 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 115:
#line 486 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (STMT_LIST_AST, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.astVect)); }
#line 1943 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 116:
#line 491 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).astVect) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.astVect); }
#line 1949 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 117:
#line 493 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).astVect) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.astVect); }
#line 1955 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 118:
#line 495 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).astVect) = new AST_Vect; }
#line 1961 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 119:
#line 497 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).astVect) = new AST_Vect; }
#line 1967 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 120:
#line 502 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (STMT_LIST_AST, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.astVect)); }
#line 1973 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 122:
#line 508 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).astVect) = new AST_Vect; }
#line 1979 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 123:
#line 510 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).astVect) = new AST_Vect (1, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)); }
#line 1985 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 124:
#line 512 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).astVect) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.astVect); }
#line 1991 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 125:
#line 514 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).astVect) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.astVect); ((*yyvalp).astVect)->insert (((*yyvalp).astVect)->begin (), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)); }
#line 1997 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 126:
#line 521 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (IF_AST, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
                  ((*yyvalp).ast)->setLoc ((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yyloc));
                }
#line 2005 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 127:
#line 528 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (IF_AST, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)); ((*yyvalp).ast)->setLoc((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yyloc)); }
#line 2011 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 129:
#line 533 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (STMT_LIST_AST); }
#line 2017 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 130:
#line 535 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast); }
#line 2023 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 131:
#line 542 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (WHILE_AST, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)); ((*yyvalp).ast)->setLoc ((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yyloc)); }
#line 2029 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 132:
#line 549 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (FOR_AST, (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)); ((*yyvalp).ast)->setLoc ((((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yyloc)); }
#line 2035 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 133:
#line 555 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (DEF_AST, (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.astVect));
                  ((*yyvalp).ast)->setLoc ((((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yyloc));
                }
#line 2043 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 134:
#line 560 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (DEF_AST, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), newTypeVar(), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.astVect));
                  ((*yyvalp).ast)->setLoc ((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yyloc));
                }
#line 2051 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 136:
#line 568 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).astVect) = new AST_Vect (1, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)); }
#line 2057 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 137:
#line 570 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).astVect) = new AST_Vect (1, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)); }
#line 2063 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 138:
#line 575 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (NATIVE_AST, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)); ((*yyvalp).ast)->setLoc ((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yyloc)); }
#line 2069 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 139:
#line 580 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (FORMALS_LIST_AST); }
#line 2075 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 140:
#line 582 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast); ((*yyvalp).ast)->setLoc ((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yyloc)); }
#line 2081 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 141:
#line 586 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (FORMALS_LIST_AST, AST_Vect(1, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast))); }
#line 2087 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 142:
#line 588 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast); ((*yyvalp).ast)->add ((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)); }
#line 2093 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 144:
#line 593 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (TYPED_ID_AST, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)); ((*yyvalp).ast)->setLoc((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc)); }
#line 2099 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 146:
#line 600 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (CLASS_AST, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.astVect));
                  ((*yyvalp).ast)->setLoc ((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yyloc));
                }
#line 2107 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 147:
#line 606 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (TYPE_FORMALS_LIST_AST); }
#line 2113 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 148:
#line 608 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (TYPE_FORMALS_LIST_AST, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.astVect));
                  ((*yyvalp).ast)->setLoc ((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yyloc));
                }
#line 2121 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 149:
#line 614 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).astVect) = new AST_Vect (1, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)); }
#line 2127 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 150:
#line 616 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).astVect) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.astVect); ((*yyvalp).astVect)->push_back ((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)); }
#line 2133 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 152:
#line 623 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast); }
#line 2139 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 154:
#line 629 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (TYPE_AST, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)); ((*yyvalp).ast)->setLoc((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc)); }
#line 2145 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 156:
#line 632 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (FUNCTION_TYPE_AST, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.astVect));
                  ((*yyvalp).ast)->setLoc ((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yyloc));
                }
#line 2153 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 157:
#line 638 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = newTypeVar (*(((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str)); ((*yyvalp).ast)->setLoc ((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yyloc)); }
#line 2159 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 158:
#line 642 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).ast) = NODE (TYPE_AST, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.astVect)); ((*yyvalp).ast)->setLoc((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yyloc)); }
#line 2165 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 159:
#line 647 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).astVect) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.astVect); }
#line 2171 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 160:
#line 648 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).astVect) = new AST_Vect (1, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)); }
#line 2177 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 161:
#line 653 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).astVect) = new AST_Vect; }
#line 2183 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 163:
#line 658 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).astVect) = new AST_Vect (1, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)); }
#line 2189 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 164:
#line 660 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).astVect) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.astVect); (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.astVect)->push_back ((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)); }
#line 2195 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 165:
#line 664 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).astVect) = new AST_Vect(1, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)); }
#line 2201 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 166:
#line 666 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).astVect) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.astVect); ((*yyvalp).astVect)->push_back ((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)); }
#line 2207 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 167:
#line 670 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).astVect) = new AST_Vect; }
#line 2213 "apyc-parser.cc" /* glr.c:816  */
    break;

  case 168:
#line 672 "apyc-parser.y" /* glr.c:816  */
    { ((*yyvalp).astVect) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.astVect); }
#line 2219 "apyc-parser.cc" /* glr.c:816  */
    break;


#line 2223 "apyc-parser.cc" /* glr.c:816  */
      default: break;
    }

  return yyok;
# undef yyerrok
# undef YYABORT
# undef YYACCEPT
# undef YYERROR
# undef YYBACKUP
# undef yyclearin
# undef YYRECOVERING
}


static void
yyuserMerge (int yyn, YYSTYPE* yy0, YYSTYPE* yy1)
{
  YYUSE (yy0);
  YYUSE (yy1);

  switch (yyn)
    {

      default: break;
    }
}

                              /* Bison grammar-table manipulation.  */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}

/** Number of symbols composing the right hand side of rule #RULE.  */
static inline int
yyrhsLength (yyRuleNum yyrule)
{
  return yyr2[yyrule];
}

static void
yydestroyGLRState (char const *yymsg, yyGLRState *yys)
{
  if (yys->yyresolved)
    yydestruct (yymsg, yystos[yys->yylrState],
                &yys->yysemantics.yysval, &yys->yyloc);
  else
    {
#if YYDEBUG
      if (yydebug)
        {
          if (yys->yysemantics.yyfirstVal)
            YYFPRINTF (stderr, "%s unresolved", yymsg);
          else
            YYFPRINTF (stderr, "%s incomplete", yymsg);
          YY_SYMBOL_PRINT ("", yystos[yys->yylrState], YY_NULLPTR, &yys->yyloc);
        }
#endif

      if (yys->yysemantics.yyfirstVal)
        {
          yySemanticOption *yyoption = yys->yysemantics.yyfirstVal;
          yyGLRState *yyrh;
          int yyn;
          for (yyrh = yyoption->yystate, yyn = yyrhsLength (yyoption->yyrule);
               yyn > 0;
               yyrh = yyrh->yypred, yyn -= 1)
            yydestroyGLRState (yymsg, yyrh);
        }
    }
}

/** Left-hand-side symbol for rule #YYRULE.  */
static inline yySymbol
yylhsNonterm (yyRuleNum yyrule)
{
  return yyr1[yyrule];
}

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-204)))

/** True iff LR state YYSTATE has only a default reduction (regardless
 *  of token).  */
static inline yybool
yyisDefaultedState (yyStateNum yystate)
{
  return yypact_value_is_default (yypact[yystate]);
}

/** The default reduction for YYSTATE, assuming it has one.  */
static inline yyRuleNum
yydefaultAction (yyStateNum yystate)
{
  return yydefact[yystate];
}

#define yytable_value_is_error(Yytable_value) \
  0

/** Set *YYACTION to the action to take in YYSTATE on seeing YYTOKEN.
 *  Result R means
 *    R < 0:  Reduce on rule -R.
 *    R = 0:  Error.
 *    R > 0:  Shift to state R.
 *  Set *YYCONFLICTS to a pointer into yyconfl to a 0-terminated list
 *  of conflicting reductions.
 */
static inline void
yygetLRActions (yyStateNum yystate, int yytoken,
                int* yyaction, const short int** yyconflicts)
{
  int yyindex = yypact[yystate] + yytoken;
  if (yypact_value_is_default (yypact[yystate])
      || yyindex < 0 || YYLAST < yyindex || yycheck[yyindex] != yytoken)
    {
      *yyaction = -yydefact[yystate];
      *yyconflicts = yyconfl;
    }
  else if (! yytable_value_is_error (yytable[yyindex]))
    {
      *yyaction = yytable[yyindex];
      *yyconflicts = yyconfl + yyconflp[yyindex];
    }
  else
    {
      *yyaction = 0;
      *yyconflicts = yyconfl + yyconflp[yyindex];
    }
}

/** Compute post-reduction state.
 * \param yystate   the current state
 * \param yysym     the nonterminal to push on the stack
 */
static inline yyStateNum
yyLRgotoState (yyStateNum yystate, yySymbol yysym)
{
  int yyr = yypgoto[yysym - YYNTOKENS] + yystate;
  if (0 <= yyr && yyr <= YYLAST && yycheck[yyr] == yystate)
    return yytable[yyr];
  else
    return yydefgoto[yysym - YYNTOKENS];
}

static inline yybool
yyisShiftAction (int yyaction)
{
  return 0 < yyaction;
}

static inline yybool
yyisErrorAction (int yyaction)
{
  return yyaction == 0;
}

                                /* GLRStates */

/** Return a fresh GLRStackItem in YYSTACKP.  The item is an LR state
 *  if YYISSTATE, and otherwise a semantic option.  Callers should call
 *  YY_RESERVE_GLRSTACK afterwards to make sure there is sufficient
 *  headroom.  */

static inline yyGLRStackItem*
yynewGLRStackItem (yyGLRStack* yystackp, yybool yyisState)
{
  yyGLRStackItem* yynewItem = yystackp->yynextFree;
  yystackp->yyspaceLeft -= 1;
  yystackp->yynextFree += 1;
  yynewItem->yystate.yyisState = yyisState;
  return yynewItem;
}

/** Add a new semantic action that will execute the action for rule
 *  YYRULE on the semantic values in YYRHS to the list of
 *  alternative actions for YYSTATE.  Assumes that YYRHS comes from
 *  stack #YYK of *YYSTACKP. */
static void
yyaddDeferredAction (yyGLRStack* yystackp, size_t yyk, yyGLRState* yystate,
                     yyGLRState* yyrhs, yyRuleNum yyrule)
{
  yySemanticOption* yynewOption =
    &yynewGLRStackItem (yystackp, yyfalse)->yyoption;
  YYASSERT (!yynewOption->yyisState);
  yynewOption->yystate = yyrhs;
  yynewOption->yyrule = yyrule;
  if (yystackp->yytops.yylookaheadNeeds[yyk])
    {
      yynewOption->yyrawchar = yychar;
      yynewOption->yyval = yylval;
      yynewOption->yyloc = yylloc;
    }
  else
    yynewOption->yyrawchar = YYEMPTY;
  yynewOption->yynext = yystate->yysemantics.yyfirstVal;
  yystate->yysemantics.yyfirstVal = yynewOption;

  YY_RESERVE_GLRSTACK (yystackp);
}

                                /* GLRStacks */

/** Initialize YYSET to a singleton set containing an empty stack.  */
static yybool
yyinitStateSet (yyGLRStateSet* yyset)
{
  yyset->yysize = 1;
  yyset->yycapacity = 16;
  yyset->yystates = (yyGLRState**) YYMALLOC (16 * sizeof yyset->yystates[0]);
  if (! yyset->yystates)
    return yyfalse;
  yyset->yystates[0] = YY_NULLPTR;
  yyset->yylookaheadNeeds =
    (yybool*) YYMALLOC (16 * sizeof yyset->yylookaheadNeeds[0]);
  if (! yyset->yylookaheadNeeds)
    {
      YYFREE (yyset->yystates);
      return yyfalse;
    }
  return yytrue;
}

static void yyfreeStateSet (yyGLRStateSet* yyset)
{
  YYFREE (yyset->yystates);
  YYFREE (yyset->yylookaheadNeeds);
}

/** Initialize *YYSTACKP to a single empty stack, with total maximum
 *  capacity for all stacks of YYSIZE.  */
static yybool
yyinitGLRStack (yyGLRStack* yystackp, size_t yysize)
{
  yystackp->yyerrState = 0;
  yynerrs = 0;
  yystackp->yyspaceLeft = yysize;
  yystackp->yyitems =
    (yyGLRStackItem*) YYMALLOC (yysize * sizeof yystackp->yynextFree[0]);
  if (!yystackp->yyitems)
    return yyfalse;
  yystackp->yynextFree = yystackp->yyitems;
  yystackp->yysplitPoint = YY_NULLPTR;
  yystackp->yylastDeleted = YY_NULLPTR;
  return yyinitStateSet (&yystackp->yytops);
}


#if YYSTACKEXPANDABLE
# define YYRELOC(YYFROMITEMS,YYTOITEMS,YYX,YYTYPE) \
  &((YYTOITEMS) - ((YYFROMITEMS) - (yyGLRStackItem*) (YYX)))->YYTYPE

/** If *YYSTACKP is expandable, extend it.  WARNING: Pointers into the
    stack from outside should be considered invalid after this call.
    We always expand when there are 1 or fewer items left AFTER an
    allocation, so that we can avoid having external pointers exist
    across an allocation.  */
static void
yyexpandGLRStack (yyGLRStack* yystackp)
{
  yyGLRStackItem* yynewItems;
  yyGLRStackItem* yyp0, *yyp1;
  size_t yynewSize;
  size_t yyn;
  size_t yysize = yystackp->yynextFree - yystackp->yyitems;
  if (YYMAXDEPTH - YYHEADROOM < yysize)
    yyMemoryExhausted (yystackp);
  yynewSize = 2*yysize;
  if (YYMAXDEPTH < yynewSize)
    yynewSize = YYMAXDEPTH;
  yynewItems = (yyGLRStackItem*) YYMALLOC (yynewSize * sizeof yynewItems[0]);
  if (! yynewItems)
    yyMemoryExhausted (yystackp);
  for (yyp0 = yystackp->yyitems, yyp1 = yynewItems, yyn = yysize;
       0 < yyn;
       yyn -= 1, yyp0 += 1, yyp1 += 1)
    {
      *yyp1 = *yyp0;
      if (*(yybool *) yyp0)
        {
          yyGLRState* yys0 = &yyp0->yystate;
          yyGLRState* yys1 = &yyp1->yystate;
          if (yys0->yypred != YY_NULLPTR)
            yys1->yypred =
              YYRELOC (yyp0, yyp1, yys0->yypred, yystate);
          if (! yys0->yyresolved && yys0->yysemantics.yyfirstVal != YY_NULLPTR)
            yys1->yysemantics.yyfirstVal =
              YYRELOC (yyp0, yyp1, yys0->yysemantics.yyfirstVal, yyoption);
        }
      else
        {
          yySemanticOption* yyv0 = &yyp0->yyoption;
          yySemanticOption* yyv1 = &yyp1->yyoption;
          if (yyv0->yystate != YY_NULLPTR)
            yyv1->yystate = YYRELOC (yyp0, yyp1, yyv0->yystate, yystate);
          if (yyv0->yynext != YY_NULLPTR)
            yyv1->yynext = YYRELOC (yyp0, yyp1, yyv0->yynext, yyoption);
        }
    }
  if (yystackp->yysplitPoint != YY_NULLPTR)
    yystackp->yysplitPoint = YYRELOC (yystackp->yyitems, yynewItems,
                                      yystackp->yysplitPoint, yystate);

  for (yyn = 0; yyn < yystackp->yytops.yysize; yyn += 1)
    if (yystackp->yytops.yystates[yyn] != YY_NULLPTR)
      yystackp->yytops.yystates[yyn] =
        YYRELOC (yystackp->yyitems, yynewItems,
                 yystackp->yytops.yystates[yyn], yystate);
  YYFREE (yystackp->yyitems);
  yystackp->yyitems = yynewItems;
  yystackp->yynextFree = yynewItems + yysize;
  yystackp->yyspaceLeft = yynewSize - yysize;
}
#endif

static void
yyfreeGLRStack (yyGLRStack* yystackp)
{
  YYFREE (yystackp->yyitems);
  yyfreeStateSet (&yystackp->yytops);
}

/** Assuming that YYS is a GLRState somewhere on *YYSTACKP, update the
 *  splitpoint of *YYSTACKP, if needed, so that it is at least as deep as
 *  YYS.  */
static inline void
yyupdateSplit (yyGLRStack* yystackp, yyGLRState* yys)
{
  if (yystackp->yysplitPoint != YY_NULLPTR && yystackp->yysplitPoint > yys)
    yystackp->yysplitPoint = yys;
}

/** Invalidate stack #YYK in *YYSTACKP.  */
static inline void
yymarkStackDeleted (yyGLRStack* yystackp, size_t yyk)
{
  if (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
    yystackp->yylastDeleted = yystackp->yytops.yystates[yyk];
  yystackp->yytops.yystates[yyk] = YY_NULLPTR;
}

/** Undelete the last stack in *YYSTACKP that was marked as deleted.  Can
    only be done once after a deletion, and only when all other stacks have
    been deleted.  */
static void
yyundeleteLastStack (yyGLRStack* yystackp)
{
  if (yystackp->yylastDeleted == YY_NULLPTR || yystackp->yytops.yysize != 0)
    return;
  yystackp->yytops.yystates[0] = yystackp->yylastDeleted;
  yystackp->yytops.yysize = 1;
  YYDPRINTF ((stderr, "Restoring last deleted stack as stack #0.\n"));
  yystackp->yylastDeleted = YY_NULLPTR;
}

static inline void
yyremoveDeletes (yyGLRStack* yystackp)
{
  size_t yyi, yyj;
  yyi = yyj = 0;
  while (yyj < yystackp->yytops.yysize)
    {
      if (yystackp->yytops.yystates[yyi] == YY_NULLPTR)
        {
          if (yyi == yyj)
            {
              YYDPRINTF ((stderr, "Removing dead stacks.\n"));
            }
          yystackp->yytops.yysize -= 1;
        }
      else
        {
          yystackp->yytops.yystates[yyj] = yystackp->yytops.yystates[yyi];
          /* In the current implementation, it's unnecessary to copy
             yystackp->yytops.yylookaheadNeeds[yyi] since, after
             yyremoveDeletes returns, the parser immediately either enters
             deterministic operation or shifts a token.  However, it doesn't
             hurt, and the code might evolve to need it.  */
          yystackp->yytops.yylookaheadNeeds[yyj] =
            yystackp->yytops.yylookaheadNeeds[yyi];
          if (yyj != yyi)
            {
              YYDPRINTF ((stderr, "Rename stack %lu -> %lu.\n",
                          (unsigned long int) yyi, (unsigned long int) yyj));
            }
          yyj += 1;
        }
      yyi += 1;
    }
}

/** Shift to a new state on stack #YYK of *YYSTACKP, corresponding to LR
 * state YYLRSTATE, at input position YYPOSN, with (resolved) semantic
 * value *YYVALP and source location *YYLOCP.  */
static inline void
yyglrShift (yyGLRStack* yystackp, size_t yyk, yyStateNum yylrState,
            size_t yyposn,
            YYSTYPE* yyvalp, YYLTYPE* yylocp)
{
  yyGLRState* yynewState = &yynewGLRStackItem (yystackp, yytrue)->yystate;

  yynewState->yylrState = yylrState;
  yynewState->yyposn = yyposn;
  yynewState->yyresolved = yytrue;
  yynewState->yypred = yystackp->yytops.yystates[yyk];
  yynewState->yysemantics.yysval = *yyvalp;
  yynewState->yyloc = *yylocp;
  yystackp->yytops.yystates[yyk] = yynewState;

  YY_RESERVE_GLRSTACK (yystackp);
}

/** Shift stack #YYK of *YYSTACKP, to a new state corresponding to LR
 *  state YYLRSTATE, at input position YYPOSN, with the (unresolved)
 *  semantic value of YYRHS under the action for YYRULE.  */
static inline void
yyglrShiftDefer (yyGLRStack* yystackp, size_t yyk, yyStateNum yylrState,
                 size_t yyposn, yyGLRState* yyrhs, yyRuleNum yyrule)
{
  yyGLRState* yynewState = &yynewGLRStackItem (yystackp, yytrue)->yystate;
  YYASSERT (yynewState->yyisState);

  yynewState->yylrState = yylrState;
  yynewState->yyposn = yyposn;
  yynewState->yyresolved = yyfalse;
  yynewState->yypred = yystackp->yytops.yystates[yyk];
  yynewState->yysemantics.yyfirstVal = YY_NULLPTR;
  yystackp->yytops.yystates[yyk] = yynewState;

  /* Invokes YY_RESERVE_GLRSTACK.  */
  yyaddDeferredAction (yystackp, yyk, yynewState, yyrhs, yyrule);
}

#if !YYDEBUG
# define YY_REDUCE_PRINT(Args)
#else
# define YY_REDUCE_PRINT(Args)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print Args;               \
} while (0)

/*----------------------------------------------------------------------.
| Report that stack #YYK of *YYSTACKP is going to be reduced by YYRULE. |
`----------------------------------------------------------------------*/

static inline void
yy_reduce_print (int yynormal, yyGLRStackItem* yyvsp, size_t yyk,
                 yyRuleNum yyrule)
{
  int yynrhs = yyrhsLength (yyrule);
  int yylow = 1;
  int yyi;
  YYFPRINTF (stderr, "Reducing stack %lu by rule %d (line %lu):\n",
             (unsigned long int) yyk, yyrule - 1,
             (unsigned long int) yyrline[yyrule]);
  if (! yynormal)
    yyfillin (yyvsp, 1, -yynrhs);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyvsp[yyi - yynrhs + 1].yystate.yylrState],
                       &yyvsp[yyi - yynrhs + 1].yystate.yysemantics.yysval
                       , &(((yyGLRStackItem const *)yyvsp)[YYFILL ((yyi + 1) - (yynrhs))].yystate.yyloc)                       );
      if (!yyvsp[yyi - yynrhs + 1].yystate.yyresolved)
        YYFPRINTF (stderr, " (unresolved)");
      YYFPRINTF (stderr, "\n");
    }
}
#endif

/** Pop the symbols consumed by reduction #YYRULE from the top of stack
 *  #YYK of *YYSTACKP, and perform the appropriate semantic action on their
 *  semantic values.  Assumes that all ambiguities in semantic values
 *  have been previously resolved.  Set *YYVALP to the resulting value,
 *  and *YYLOCP to the computed location (if any).  Return value is as
 *  for userAction.  */
static inline YYRESULTTAG
yydoAction (yyGLRStack* yystackp, size_t yyk, yyRuleNum yyrule,
            YYSTYPE* yyvalp, YYLTYPE *yylocp)
{
  int yynrhs = yyrhsLength (yyrule);

  if (yystackp->yysplitPoint == YY_NULLPTR)
    {
      /* Standard special case: single stack.  */
      yyGLRStackItem* yyrhs = (yyGLRStackItem*) yystackp->yytops.yystates[yyk];
      YYASSERT (yyk == 0);
      yystackp->yynextFree -= yynrhs;
      yystackp->yyspaceLeft += yynrhs;
      yystackp->yytops.yystates[0] = & yystackp->yynextFree[-1].yystate;
      YY_REDUCE_PRINT ((1, yyrhs, yyk, yyrule));
      return yyuserAction (yyrule, yynrhs, yyrhs, yystackp,
                           yyvalp, yylocp);
    }
  else
    {
      int yyi;
      yyGLRState* yys;
      yyGLRStackItem yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
      yys = yyrhsVals[YYMAXRHS + YYMAXLEFT].yystate.yypred
        = yystackp->yytops.yystates[yyk];
      if (yynrhs == 0)
        /* Set default location.  */
        yyrhsVals[YYMAXRHS + YYMAXLEFT - 1].yystate.yyloc = yys->yyloc;
      for (yyi = 0; yyi < yynrhs; yyi += 1)
        {
          yys = yys->yypred;
          YYASSERT (yys);
        }
      yyupdateSplit (yystackp, yys);
      yystackp->yytops.yystates[yyk] = yys;
      YY_REDUCE_PRINT ((0, yyrhsVals + YYMAXRHS + YYMAXLEFT - 1, yyk, yyrule));
      return yyuserAction (yyrule, yynrhs, yyrhsVals + YYMAXRHS + YYMAXLEFT - 1,
                           yystackp, yyvalp, yylocp);
    }
}

/** Pop items off stack #YYK of *YYSTACKP according to grammar rule YYRULE,
 *  and push back on the resulting nonterminal symbol.  Perform the
 *  semantic action associated with YYRULE and store its value with the
 *  newly pushed state, if YYFORCEEVAL or if *YYSTACKP is currently
 *  unambiguous.  Otherwise, store the deferred semantic action with
 *  the new state.  If the new state would have an identical input
 *  position, LR state, and predecessor to an existing state on the stack,
 *  it is identified with that existing state, eliminating stack #YYK from
 *  *YYSTACKP.  In this case, the semantic value is
 *  added to the options for the existing state's semantic value.
 */
static inline YYRESULTTAG
yyglrReduce (yyGLRStack* yystackp, size_t yyk, yyRuleNum yyrule,
             yybool yyforceEval)
{
  size_t yyposn = yystackp->yytops.yystates[yyk]->yyposn;

  if (yyforceEval || yystackp->yysplitPoint == YY_NULLPTR)
    {
      YYSTYPE yysval;
      YYLTYPE yyloc;

      YYRESULTTAG yyflag = yydoAction (yystackp, yyk, yyrule, &yysval, &yyloc);
      if (yyflag == yyerr && yystackp->yysplitPoint != YY_NULLPTR)
        {
          YYDPRINTF ((stderr, "Parse on stack %lu rejected by rule #%d.\n",
                     (unsigned long int) yyk, yyrule - 1));
        }
      if (yyflag != yyok)
        return yyflag;
      YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyrule], &yysval, &yyloc);
      yyglrShift (yystackp, yyk,
                  yyLRgotoState (yystackp->yytops.yystates[yyk]->yylrState,
                                 yylhsNonterm (yyrule)),
                  yyposn, &yysval, &yyloc);
    }
  else
    {
      size_t yyi;
      int yyn;
      yyGLRState* yys, *yys0 = yystackp->yytops.yystates[yyk];
      yyStateNum yynewLRState;

      for (yys = yystackp->yytops.yystates[yyk], yyn = yyrhsLength (yyrule);
           0 < yyn; yyn -= 1)
        {
          yys = yys->yypred;
          YYASSERT (yys);
        }
      yyupdateSplit (yystackp, yys);
      yynewLRState = yyLRgotoState (yys->yylrState, yylhsNonterm (yyrule));
      YYDPRINTF ((stderr,
                  "Reduced stack %lu by rule #%d; action deferred.  "
                  "Now in state %d.\n",
                  (unsigned long int) yyk, yyrule - 1, yynewLRState));
      for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
        if (yyi != yyk && yystackp->yytops.yystates[yyi] != YY_NULLPTR)
          {
            yyGLRState *yysplit = yystackp->yysplitPoint;
            yyGLRState *yyp = yystackp->yytops.yystates[yyi];
            while (yyp != yys && yyp != yysplit && yyp->yyposn >= yyposn)
              {
                if (yyp->yylrState == yynewLRState && yyp->yypred == yys)
                  {
                    yyaddDeferredAction (yystackp, yyk, yyp, yys0, yyrule);
                    yymarkStackDeleted (yystackp, yyk);
                    YYDPRINTF ((stderr, "Merging stack %lu into stack %lu.\n",
                                (unsigned long int) yyk,
                                (unsigned long int) yyi));
                    return yyok;
                  }
                yyp = yyp->yypred;
              }
          }
      yystackp->yytops.yystates[yyk] = yys;
      yyglrShiftDefer (yystackp, yyk, yynewLRState, yyposn, yys0, yyrule);
    }
  return yyok;
}

static size_t
yysplitStack (yyGLRStack* yystackp, size_t yyk)
{
  if (yystackp->yysplitPoint == YY_NULLPTR)
    {
      YYASSERT (yyk == 0);
      yystackp->yysplitPoint = yystackp->yytops.yystates[yyk];
    }
  if (yystackp->yytops.yysize >= yystackp->yytops.yycapacity)
    {
      yyGLRState** yynewStates;
      yybool* yynewLookaheadNeeds;

      yynewStates = YY_NULLPTR;

      if (yystackp->yytops.yycapacity
          > (YYSIZEMAX / (2 * sizeof yynewStates[0])))
        yyMemoryExhausted (yystackp);
      yystackp->yytops.yycapacity *= 2;

      yynewStates =
        (yyGLRState**) YYREALLOC (yystackp->yytops.yystates,
                                  (yystackp->yytops.yycapacity
                                   * sizeof yynewStates[0]));
      if (yynewStates == YY_NULLPTR)
        yyMemoryExhausted (yystackp);
      yystackp->yytops.yystates = yynewStates;

      yynewLookaheadNeeds =
        (yybool*) YYREALLOC (yystackp->yytops.yylookaheadNeeds,
                             (yystackp->yytops.yycapacity
                              * sizeof yynewLookaheadNeeds[0]));
      if (yynewLookaheadNeeds == YY_NULLPTR)
        yyMemoryExhausted (yystackp);
      yystackp->yytops.yylookaheadNeeds = yynewLookaheadNeeds;
    }
  yystackp->yytops.yystates[yystackp->yytops.yysize]
    = yystackp->yytops.yystates[yyk];
  yystackp->yytops.yylookaheadNeeds[yystackp->yytops.yysize]
    = yystackp->yytops.yylookaheadNeeds[yyk];
  yystackp->yytops.yysize += 1;
  return yystackp->yytops.yysize-1;
}

/** True iff YYY0 and YYY1 represent identical options at the top level.
 *  That is, they represent the same rule applied to RHS symbols
 *  that produce the same terminal symbols.  */
static yybool
yyidenticalOptions (yySemanticOption* yyy0, yySemanticOption* yyy1)
{
  if (yyy0->yyrule == yyy1->yyrule)
    {
      yyGLRState *yys0, *yys1;
      int yyn;
      for (yys0 = yyy0->yystate, yys1 = yyy1->yystate,
           yyn = yyrhsLength (yyy0->yyrule);
           yyn > 0;
           yys0 = yys0->yypred, yys1 = yys1->yypred, yyn -= 1)
        if (yys0->yyposn != yys1->yyposn)
          return yyfalse;
      return yytrue;
    }
  else
    return yyfalse;
}

/** Assuming identicalOptions (YYY0,YYY1), destructively merge the
 *  alternative semantic values for the RHS-symbols of YYY1 and YYY0.  */
static void
yymergeOptionSets (yySemanticOption* yyy0, yySemanticOption* yyy1)
{
  yyGLRState *yys0, *yys1;
  int yyn;
  for (yys0 = yyy0->yystate, yys1 = yyy1->yystate,
       yyn = yyrhsLength (yyy0->yyrule);
       yyn > 0;
       yys0 = yys0->yypred, yys1 = yys1->yypred, yyn -= 1)
    {
      if (yys0 == yys1)
        break;
      else if (yys0->yyresolved)
        {
          yys1->yyresolved = yytrue;
          yys1->yysemantics.yysval = yys0->yysemantics.yysval;
        }
      else if (yys1->yyresolved)
        {
          yys0->yyresolved = yytrue;
          yys0->yysemantics.yysval = yys1->yysemantics.yysval;
        }
      else
        {
          yySemanticOption** yyz0p = &yys0->yysemantics.yyfirstVal;
          yySemanticOption* yyz1 = yys1->yysemantics.yyfirstVal;
          while (yytrue)
            {
              if (yyz1 == *yyz0p || yyz1 == YY_NULLPTR)
                break;
              else if (*yyz0p == YY_NULLPTR)
                {
                  *yyz0p = yyz1;
                  break;
                }
              else if (*yyz0p < yyz1)
                {
                  yySemanticOption* yyz = *yyz0p;
                  *yyz0p = yyz1;
                  yyz1 = yyz1->yynext;
                  (*yyz0p)->yynext = yyz;
                }
              yyz0p = &(*yyz0p)->yynext;
            }
          yys1->yysemantics.yyfirstVal = yys0->yysemantics.yyfirstVal;
        }
    }
}

/** Y0 and Y1 represent two possible actions to take in a given
 *  parsing state; return 0 if no combination is possible,
 *  1 if user-mergeable, 2 if Y0 is preferred, 3 if Y1 is preferred.  */
static int
yypreference (yySemanticOption* y0, yySemanticOption* y1)
{
  yyRuleNum r0 = y0->yyrule, r1 = y1->yyrule;
  int p0 = yydprec[r0], p1 = yydprec[r1];

  if (p0 == p1)
    {
      if (yymerger[r0] == 0 || yymerger[r0] != yymerger[r1])
        return 0;
      else
        return 1;
    }
  if (p0 == 0 || p1 == 0)
    return 0;
  if (p0 < p1)
    return 3;
  if (p1 < p0)
    return 2;
  return 0;
}

static YYRESULTTAG yyresolveValue (yyGLRState* yys,
                                   yyGLRStack* yystackp);


/** Resolve the previous YYN states starting at and including state YYS
 *  on *YYSTACKP. If result != yyok, some states may have been left
 *  unresolved possibly with empty semantic option chains.  Regardless
 *  of whether result = yyok, each state has been left with consistent
 *  data so that yydestroyGLRState can be invoked if necessary.  */
static YYRESULTTAG
yyresolveStates (yyGLRState* yys, int yyn,
                 yyGLRStack* yystackp)
{
  if (0 < yyn)
    {
      YYASSERT (yys->yypred);
      YYCHK (yyresolveStates (yys->yypred, yyn-1, yystackp));
      if (! yys->yyresolved)
        YYCHK (yyresolveValue (yys, yystackp));
    }
  return yyok;
}

/** Resolve the states for the RHS of YYOPT on *YYSTACKP, perform its
 *  user action, and return the semantic value and location in *YYVALP
 *  and *YYLOCP.  Regardless of whether result = yyok, all RHS states
 *  have been destroyed (assuming the user action destroys all RHS
 *  semantic values if invoked).  */
static YYRESULTTAG
yyresolveAction (yySemanticOption* yyopt, yyGLRStack* yystackp,
                 YYSTYPE* yyvalp, YYLTYPE *yylocp)
{
  yyGLRStackItem yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
  int yynrhs = yyrhsLength (yyopt->yyrule);
  YYRESULTTAG yyflag =
    yyresolveStates (yyopt->yystate, yynrhs, yystackp);
  if (yyflag != yyok)
    {
      yyGLRState *yys;
      for (yys = yyopt->yystate; yynrhs > 0; yys = yys->yypred, yynrhs -= 1)
        yydestroyGLRState ("Cleanup: popping", yys);
      return yyflag;
    }

  yyrhsVals[YYMAXRHS + YYMAXLEFT].yystate.yypred = yyopt->yystate;
  if (yynrhs == 0)
    /* Set default location.  */
    yyrhsVals[YYMAXRHS + YYMAXLEFT - 1].yystate.yyloc = yyopt->yystate->yyloc;
  {
    int yychar_current = yychar;
    YYSTYPE yylval_current = yylval;
    YYLTYPE yylloc_current = yylloc;
    yychar = yyopt->yyrawchar;
    yylval = yyopt->yyval;
    yylloc = yyopt->yyloc;
    yyflag = yyuserAction (yyopt->yyrule, yynrhs,
                           yyrhsVals + YYMAXRHS + YYMAXLEFT - 1,
                           yystackp, yyvalp, yylocp);
    yychar = yychar_current;
    yylval = yylval_current;
    yylloc = yylloc_current;
  }
  return yyflag;
}

#if YYDEBUG
static void
yyreportTree (yySemanticOption* yyx, int yyindent)
{
  int yynrhs = yyrhsLength (yyx->yyrule);
  int yyi;
  yyGLRState* yys;
  yyGLRState* yystates[1 + YYMAXRHS];
  yyGLRState yyleftmost_state;

  for (yyi = yynrhs, yys = yyx->yystate; 0 < yyi; yyi -= 1, yys = yys->yypred)
    yystates[yyi] = yys;
  if (yys == YY_NULLPTR)
    {
      yyleftmost_state.yyposn = 0;
      yystates[0] = &yyleftmost_state;
    }
  else
    yystates[0] = yys;

  if (yyx->yystate->yyposn < yys->yyposn + 1)
    YYFPRINTF (stderr, "%*s%s -> <Rule %d, empty>\n",
               yyindent, "", yytokenName (yylhsNonterm (yyx->yyrule)),
               yyx->yyrule - 1);
  else
    YYFPRINTF (stderr, "%*s%s -> <Rule %d, tokens %lu .. %lu>\n",
               yyindent, "", yytokenName (yylhsNonterm (yyx->yyrule)),
               yyx->yyrule - 1, (unsigned long int) (yys->yyposn + 1),
               (unsigned long int) yyx->yystate->yyposn);
  for (yyi = 1; yyi <= yynrhs; yyi += 1)
    {
      if (yystates[yyi]->yyresolved)
        {
          if (yystates[yyi-1]->yyposn+1 > yystates[yyi]->yyposn)
            YYFPRINTF (stderr, "%*s%s <empty>\n", yyindent+2, "",
                       yytokenName (yystos[yystates[yyi]->yylrState]));
          else
            YYFPRINTF (stderr, "%*s%s <tokens %lu .. %lu>\n", yyindent+2, "",
                       yytokenName (yystos[yystates[yyi]->yylrState]),
                       (unsigned long int) (yystates[yyi-1]->yyposn + 1),
                       (unsigned long int) yystates[yyi]->yyposn);
        }
      else
        yyreportTree (yystates[yyi]->yysemantics.yyfirstVal, yyindent+2);
    }
}
#endif

static YYRESULTTAG
yyreportAmbiguity (yySemanticOption* yyx0,
                   yySemanticOption* yyx1)
{
  YYUSE (yyx0);
  YYUSE (yyx1);

#if YYDEBUG
  YYFPRINTF (stderr, "Ambiguity detected.\n");
  YYFPRINTF (stderr, "Option 1,\n");
  yyreportTree (yyx0, 2);
  YYFPRINTF (stderr, "\nOption 2,\n");
  yyreportTree (yyx1, 2);
  YYFPRINTF (stderr, "\n");
#endif

  yyerror (YY_("syntax is ambiguous"));
  return yyabort;
}

/** Resolve the locations for each of the YYN1 states in *YYSTACKP,
 *  ending at YYS1.  Has no effect on previously resolved states.
 *  The first semantic option of a state is always chosen.  */
static void
yyresolveLocations (yyGLRState* yys1, int yyn1,
                    yyGLRStack *yystackp)
{
  if (0 < yyn1)
    {
      yyresolveLocations (yys1->yypred, yyn1 - 1, yystackp);
      if (!yys1->yyresolved)
        {
          yyGLRStackItem yyrhsloc[1 + YYMAXRHS];
          int yynrhs;
          yySemanticOption *yyoption = yys1->yysemantics.yyfirstVal;
          YYASSERT (yyoption != YY_NULLPTR);
          yynrhs = yyrhsLength (yyoption->yyrule);
          if (yynrhs > 0)
            {
              yyGLRState *yys;
              int yyn;
              yyresolveLocations (yyoption->yystate, yynrhs,
                                  yystackp);
              for (yys = yyoption->yystate, yyn = yynrhs;
                   yyn > 0;
                   yys = yys->yypred, yyn -= 1)
                yyrhsloc[yyn].yystate.yyloc = yys->yyloc;
            }
          else
            {
              /* Both yyresolveAction and yyresolveLocations traverse the GSS
                 in reverse rightmost order.  It is only necessary to invoke
                 yyresolveLocations on a subforest for which yyresolveAction
                 would have been invoked next had an ambiguity not been
                 detected.  Thus the location of the previous state (but not
                 necessarily the previous state itself) is guaranteed to be
                 resolved already.  */
              yyGLRState *yyprevious = yyoption->yystate;
              yyrhsloc[0].yystate.yyloc = yyprevious->yyloc;
            }
          {
            int yychar_current = yychar;
            YYSTYPE yylval_current = yylval;
            YYLTYPE yylloc_current = yylloc;
            yychar = yyoption->yyrawchar;
            yylval = yyoption->yyval;
            yylloc = yyoption->yyloc;
            YYLLOC_DEFAULT ((yys1->yyloc), yyrhsloc, yynrhs);
            yychar = yychar_current;
            yylval = yylval_current;
            yylloc = yylloc_current;
          }
        }
    }
}

/** Resolve the ambiguity represented in state YYS in *YYSTACKP,
 *  perform the indicated actions, and set the semantic value of YYS.
 *  If result != yyok, the chain of semantic options in YYS has been
 *  cleared instead or it has been left unmodified except that
 *  redundant options may have been removed.  Regardless of whether
 *  result = yyok, YYS has been left with consistent data so that
 *  yydestroyGLRState can be invoked if necessary.  */
static YYRESULTTAG
yyresolveValue (yyGLRState* yys, yyGLRStack* yystackp)
{
  yySemanticOption* yyoptionList = yys->yysemantics.yyfirstVal;
  yySemanticOption* yybest = yyoptionList;
  yySemanticOption** yypp;
  yybool yymerge = yyfalse;
  YYSTYPE yysval;
  YYRESULTTAG yyflag;
  YYLTYPE *yylocp = &yys->yyloc;

  for (yypp = &yyoptionList->yynext; *yypp != YY_NULLPTR; )
    {
      yySemanticOption* yyp = *yypp;

      if (yyidenticalOptions (yybest, yyp))
        {
          yymergeOptionSets (yybest, yyp);
          *yypp = yyp->yynext;
        }
      else
        {
          switch (yypreference (yybest, yyp))
            {
            case 0:
              yyresolveLocations (yys, 1, yystackp);
              return yyreportAmbiguity (yybest, yyp);
              break;
            case 1:
              yymerge = yytrue;
              break;
            case 2:
              break;
            case 3:
              yybest = yyp;
              yymerge = yyfalse;
              break;
            default:
              /* This cannot happen so it is not worth a YYASSERT (yyfalse),
                 but some compilers complain if the default case is
                 omitted.  */
              break;
            }
          yypp = &yyp->yynext;
        }
    }

  if (yymerge)
    {
      yySemanticOption* yyp;
      int yyprec = yydprec[yybest->yyrule];
      yyflag = yyresolveAction (yybest, yystackp, &yysval, yylocp);
      if (yyflag == yyok)
        for (yyp = yybest->yynext; yyp != YY_NULLPTR; yyp = yyp->yynext)
          {
            if (yyprec == yydprec[yyp->yyrule])
              {
                YYSTYPE yysval_other;
                YYLTYPE yydummy;
                yyflag = yyresolveAction (yyp, yystackp, &yysval_other, &yydummy);
                if (yyflag != yyok)
                  {
                    yydestruct ("Cleanup: discarding incompletely merged value for",
                                yystos[yys->yylrState],
                                &yysval, yylocp);
                    break;
                  }
                yyuserMerge (yymerger[yyp->yyrule], &yysval, &yysval_other);
              }
          }
    }
  else
    yyflag = yyresolveAction (yybest, yystackp, &yysval, yylocp);

  if (yyflag == yyok)
    {
      yys->yyresolved = yytrue;
      yys->yysemantics.yysval = yysval;
    }
  else
    yys->yysemantics.yyfirstVal = YY_NULLPTR;
  return yyflag;
}

static YYRESULTTAG
yyresolveStack (yyGLRStack* yystackp)
{
  if (yystackp->yysplitPoint != YY_NULLPTR)
    {
      yyGLRState* yys;
      int yyn;

      for (yyn = 0, yys = yystackp->yytops.yystates[0];
           yys != yystackp->yysplitPoint;
           yys = yys->yypred, yyn += 1)
        continue;
      YYCHK (yyresolveStates (yystackp->yytops.yystates[0], yyn, yystackp
                             ));
    }
  return yyok;
}

static void
yycompressStack (yyGLRStack* yystackp)
{
  yyGLRState* yyp, *yyq, *yyr;

  if (yystackp->yytops.yysize != 1 || yystackp->yysplitPoint == YY_NULLPTR)
    return;

  for (yyp = yystackp->yytops.yystates[0], yyq = yyp->yypred, yyr = YY_NULLPTR;
       yyp != yystackp->yysplitPoint;
       yyr = yyp, yyp = yyq, yyq = yyp->yypred)
    yyp->yypred = yyr;

  yystackp->yyspaceLeft += yystackp->yynextFree - yystackp->yyitems;
  yystackp->yynextFree = ((yyGLRStackItem*) yystackp->yysplitPoint) + 1;
  yystackp->yyspaceLeft -= yystackp->yynextFree - yystackp->yyitems;
  yystackp->yysplitPoint = YY_NULLPTR;
  yystackp->yylastDeleted = YY_NULLPTR;

  while (yyr != YY_NULLPTR)
    {
      yystackp->yynextFree->yystate = *yyr;
      yyr = yyr->yypred;
      yystackp->yynextFree->yystate.yypred = &yystackp->yynextFree[-1].yystate;
      yystackp->yytops.yystates[0] = &yystackp->yynextFree->yystate;
      yystackp->yynextFree += 1;
      yystackp->yyspaceLeft -= 1;
    }
}

static YYRESULTTAG
yyprocessOneStack (yyGLRStack* yystackp, size_t yyk,
                   size_t yyposn)
{
  while (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
    {
      yyStateNum yystate = yystackp->yytops.yystates[yyk]->yylrState;
      YYDPRINTF ((stderr, "Stack %lu Entering state %d\n",
                  (unsigned long int) yyk, yystate));

      YYASSERT (yystate != YYFINAL);

      if (yyisDefaultedState (yystate))
        {
          YYRESULTTAG yyflag;
          yyRuleNum yyrule = yydefaultAction (yystate);
          if (yyrule == 0)
            {
              YYDPRINTF ((stderr, "Stack %lu dies.\n",
                          (unsigned long int) yyk));
              yymarkStackDeleted (yystackp, yyk);
              return yyok;
            }
          yyflag = yyglrReduce (yystackp, yyk, yyrule, yyimmediate[yyrule]);
          if (yyflag == yyerr)
            {
              YYDPRINTF ((stderr,
                          "Stack %lu dies "
                          "(predicate failure or explicit user error).\n",
                          (unsigned long int) yyk));
              yymarkStackDeleted (yystackp, yyk);
              return yyok;
            }
          if (yyflag != yyok)
            return yyflag;
        }
      else
        {
          yySymbol yytoken;
          int yyaction;
          const short int* yyconflicts;

          yystackp->yytops.yylookaheadNeeds[yyk] = yytrue;
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

          yygetLRActions (yystate, yytoken, &yyaction, &yyconflicts);

          while (*yyconflicts != 0)
            {
              YYRESULTTAG yyflag;
              size_t yynewStack = yysplitStack (yystackp, yyk);
              YYDPRINTF ((stderr, "Splitting off stack %lu from %lu.\n",
                          (unsigned long int) yynewStack,
                          (unsigned long int) yyk));
              yyflag = yyglrReduce (yystackp, yynewStack,
                                    *yyconflicts,
                                    yyimmediate[*yyconflicts]);
              if (yyflag == yyok)
                YYCHK (yyprocessOneStack (yystackp, yynewStack,
                                          yyposn));
              else if (yyflag == yyerr)
                {
                  YYDPRINTF ((stderr, "Stack %lu dies.\n",
                              (unsigned long int) yynewStack));
                  yymarkStackDeleted (yystackp, yynewStack);
                }
              else
                return yyflag;
              yyconflicts += 1;
            }

          if (yyisShiftAction (yyaction))
            break;
          else if (yyisErrorAction (yyaction))
            {
              YYDPRINTF ((stderr, "Stack %lu dies.\n",
                          (unsigned long int) yyk));
              yymarkStackDeleted (yystackp, yyk);
              break;
            }
          else
            {
              YYRESULTTAG yyflag = yyglrReduce (yystackp, yyk, -yyaction,
                                                yyimmediate[-yyaction]);
              if (yyflag == yyerr)
                {
                  YYDPRINTF ((stderr,
                              "Stack %lu dies "
                              "(predicate failure or explicit user error).\n",
                              (unsigned long int) yyk));
                  yymarkStackDeleted (yystackp, yyk);
                  break;
                }
              else if (yyflag != yyok)
                return yyflag;
            }
        }
    }
  return yyok;
}

static void
yyreportSyntaxError (yyGLRStack* yystackp)
{
  if (yystackp->yyerrState != 0)
    return;
#if ! YYERROR_VERBOSE
  yyerror (YY_("syntax error"));
#else
  {
  yySymbol yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);
  size_t yysize0 = yytnamerr (YY_NULLPTR, yytokenName (yytoken));
  size_t yysize = yysize0;
  yybool yysize_overflow = yyfalse;
  char* yymsg = YY_NULLPTR;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected").  */
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
      int yyn = yypact[yystackp->yytops.yystates[0]->yylrState];
      yyarg[yycount++] = yytokenName (yytoken);
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for this
             state because they are default actions.  */
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
                yyarg[yycount++] = yytokenName (yyx);
                {
                  size_t yysz = yysize + yytnamerr (YY_NULLPTR, yytokenName (yyx));
                  yysize_overflow |= yysz < yysize;
                  yysize = yysz;
                }
              }
        }
    }

  switch (yycount)
    {
#define YYCASE_(N, S)                   \
      case N:                           \
        yyformat = S;                   \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  {
    size_t yysz = yysize + strlen (yyformat);
    yysize_overflow |= yysz < yysize;
    yysize = yysz;
  }

  if (!yysize_overflow)
    yymsg = (char *) YYMALLOC (yysize);

  if (yymsg)
    {
      char *yyp = yymsg;
      int yyi = 0;
      while ((*yyp = *yyformat))
        {
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
      yyerror (yymsg);
      YYFREE (yymsg);
    }
  else
    {
      yyerror (YY_("syntax error"));
      yyMemoryExhausted (yystackp);
    }
  }
#endif /* YYERROR_VERBOSE */
  yynerrs += 1;
}

/* Recover from a syntax error on *YYSTACKP, assuming that *YYSTACKP->YYTOKENP,
   yylval, and yylloc are the syntactic category, semantic value, and location
   of the lookahead.  */
static void
yyrecoverSyntaxError (yyGLRStack* yystackp)
{
  size_t yyk;
  int yyj;

  if (yystackp->yyerrState == 3)
    /* We just shifted the error token and (perhaps) took some
       reductions.  Skip tokens until we can proceed.  */
    while (yytrue)
      {
        yySymbol yytoken;
        if (yychar == YYEOF)
          yyFail (yystackp, YY_NULLPTR);
        if (yychar != YYEMPTY)
          {
            /* We throw away the lookahead, but the error range
               of the shifted error token must take it into account.  */
            yyGLRState *yys = yystackp->yytops.yystates[0];
            yyGLRStackItem yyerror_range[3];
            yyerror_range[1].yystate.yyloc = yys->yyloc;
            yyerror_range[2].yystate.yyloc = yylloc;
            YYLLOC_DEFAULT ((yys->yyloc), yyerror_range, 2);
            yytoken = YYTRANSLATE (yychar);
            yydestruct ("Error: discarding",
                        yytoken, &yylval, &yylloc);
          }
        YYDPRINTF ((stderr, "Reading a token: "));
        yychar = yylex ();
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
        yyj = yypact[yystackp->yytops.yystates[0]->yylrState];
        if (yypact_value_is_default (yyj))
          return;
        yyj += yytoken;
        if (yyj < 0 || YYLAST < yyj || yycheck[yyj] != yytoken)
          {
            if (yydefact[yystackp->yytops.yystates[0]->yylrState] != 0)
              return;
          }
        else if (! yytable_value_is_error (yytable[yyj]))
          return;
      }

  /* Reduce to one stack.  */
  for (yyk = 0; yyk < yystackp->yytops.yysize; yyk += 1)
    if (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
      break;
  if (yyk >= yystackp->yytops.yysize)
    yyFail (yystackp, YY_NULLPTR);
  for (yyk += 1; yyk < yystackp->yytops.yysize; yyk += 1)
    yymarkStackDeleted (yystackp, yyk);
  yyremoveDeletes (yystackp);
  yycompressStack (yystackp);

  /* Now pop stack until we find a state that shifts the error token.  */
  yystackp->yyerrState = 3;
  while (yystackp->yytops.yystates[0] != YY_NULLPTR)
    {
      yyGLRState *yys = yystackp->yytops.yystates[0];
      yyj = yypact[yys->yylrState];
      if (! yypact_value_is_default (yyj))
        {
          yyj += YYTERROR;
          if (0 <= yyj && yyj <= YYLAST && yycheck[yyj] == YYTERROR
              && yyisShiftAction (yytable[yyj]))
            {
              /* Shift the error token.  */
              /* First adjust its location.*/
              YYLTYPE yyerrloc;
              yystackp->yyerror_range[2].yystate.yyloc = yylloc;
              YYLLOC_DEFAULT (yyerrloc, (yystackp->yyerror_range), 2);
              YY_SYMBOL_PRINT ("Shifting", yystos[yytable[yyj]],
                               &yylval, &yyerrloc);
              yyglrShift (yystackp, 0, yytable[yyj],
                          yys->yyposn, &yylval, &yyerrloc);
              yys = yystackp->yytops.yystates[0];
              break;
            }
        }
      yystackp->yyerror_range[1].yystate.yyloc = yys->yyloc;
      if (yys->yypred != YY_NULLPTR)
        yydestroyGLRState ("Error: popping", yys);
      yystackp->yytops.yystates[0] = yys->yypred;
      yystackp->yynextFree -= 1;
      yystackp->yyspaceLeft += 1;
    }
  if (yystackp->yytops.yystates[0] == YY_NULLPTR)
    yyFail (yystackp, YY_NULLPTR);
}

#define YYCHK1(YYE)                                                          \
  do {                                                                       \
    switch (YYE) {                                                           \
    case yyok:                                                               \
      break;                                                                 \
    case yyabort:                                                            \
      goto yyabortlab;                                                       \
    case yyaccept:                                                           \
      goto yyacceptlab;                                                      \
    case yyerr:                                                              \
      goto yyuser_error;                                                     \
    default:                                                                 \
      goto yybuglab;                                                         \
    }                                                                        \
  } while (0)

/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
  int yyresult;
  yyGLRStack yystack;
  yyGLRStack* const yystackp = &yystack;
  size_t yyposn;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY;
  yylval = yyval_default;
  yylloc = yyloc_default;

  if (! yyinitGLRStack (yystackp, YYINITDEPTH))
    goto yyexhaustedlab;
  switch (YYSETJMP (yystack.yyexception_buffer))
    {
    case 0: break;
    case 1: goto yyabortlab;
    case 2: goto yyexhaustedlab;
    default: goto yybuglab;
    }
  yyglrShift (&yystack, 0, 0, 0, &yylval, &yylloc);
  yyposn = 0;

  while (yytrue)
    {
      /* For efficiency, we have two loops, the first of which is
         specialized to deterministic operation (single stack, no
         potential ambiguity).  */
      /* Standard mode */
      while (yytrue)
        {
          yyRuleNum yyrule;
          int yyaction;
          const short int* yyconflicts;

          yyStateNum yystate = yystack.yytops.yystates[0]->yylrState;
          YYDPRINTF ((stderr, "Entering state %d\n", yystate));
          if (yystate == YYFINAL)
            goto yyacceptlab;
          if (yyisDefaultedState (yystate))
            {
              yyrule = yydefaultAction (yystate);
              if (yyrule == 0)
                {
               yystack.yyerror_range[1].yystate.yyloc = yylloc;
                  yyreportSyntaxError (&yystack);
                  goto yyuser_error;
                }
              YYCHK1 (yyglrReduce (&yystack, 0, yyrule, yytrue));
            }
          else
            {
              yySymbol yytoken;
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

              yygetLRActions (yystate, yytoken, &yyaction, &yyconflicts);
              if (*yyconflicts != 0)
                break;
              if (yyisShiftAction (yyaction))
                {
                  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
                  yychar = YYEMPTY;
                  yyposn += 1;
                  yyglrShift (&yystack, 0, yyaction, yyposn, &yylval, &yylloc);
                  if (0 < yystack.yyerrState)
                    yystack.yyerrState -= 1;
                }
              else if (yyisErrorAction (yyaction))
                {
               yystack.yyerror_range[1].yystate.yyloc = yylloc;
                  yyreportSyntaxError (&yystack);
                  goto yyuser_error;
                }
              else
                YYCHK1 (yyglrReduce (&yystack, 0, -yyaction, yytrue));
            }
        }

      while (yytrue)
        {
          yySymbol yytoken_to_shift;
          size_t yys;

          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            yystackp->yytops.yylookaheadNeeds[yys] = yychar != YYEMPTY;

          /* yyprocessOneStack returns one of three things:

              - An error flag.  If the caller is yyprocessOneStack, it
                immediately returns as well.  When the caller is finally
                yyparse, it jumps to an error label via YYCHK1.

              - yyok, but yyprocessOneStack has invoked yymarkStackDeleted
                (&yystack, yys), which sets the top state of yys to NULL.  Thus,
                yyparse's following invocation of yyremoveDeletes will remove
                the stack.

              - yyok, when ready to shift a token.

             Except in the first case, yyparse will invoke yyremoveDeletes and
             then shift the next token onto all remaining stacks.  This
             synchronization of the shift (that is, after all preceding
             reductions on all stacks) helps prevent double destructor calls
             on yylval in the event of memory exhaustion.  */

          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            YYCHK1 (yyprocessOneStack (&yystack, yys, yyposn));
          yyremoveDeletes (&yystack);
          if (yystack.yytops.yysize == 0)
            {
              yyundeleteLastStack (&yystack);
              if (yystack.yytops.yysize == 0)
                yyFail (&yystack, YY_("syntax error"));
              YYCHK1 (yyresolveStack (&yystack));
              YYDPRINTF ((stderr, "Returning to deterministic operation.\n"));
           yystack.yyerror_range[1].yystate.yyloc = yylloc;
              yyreportSyntaxError (&yystack);
              goto yyuser_error;
            }

          /* If any yyglrShift call fails, it will fail after shifting.  Thus,
             a copy of yylval will already be on stack 0 in the event of a
             failure in the following loop.  Thus, yychar is set to YYEMPTY
             before the loop to make sure the user destructor for yylval isn't
             called twice.  */
          yytoken_to_shift = YYTRANSLATE (yychar);
          yychar = YYEMPTY;
          yyposn += 1;
          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            {
              int yyaction;
              const short int* yyconflicts;
              yyStateNum yystate = yystack.yytops.yystates[yys]->yylrState;
              yygetLRActions (yystate, yytoken_to_shift, &yyaction,
                              &yyconflicts);
              /* Note that yyconflicts were handled by yyprocessOneStack.  */
              YYDPRINTF ((stderr, "On stack %lu, ", (unsigned long int) yys));
              YY_SYMBOL_PRINT ("shifting", yytoken_to_shift, &yylval, &yylloc);
              yyglrShift (&yystack, yys, yyaction, yyposn,
                          &yylval, &yylloc);
              YYDPRINTF ((stderr, "Stack %lu now in state #%d\n",
                          (unsigned long int) yys,
                          yystack.yytops.yystates[yys]->yylrState));
            }

          if (yystack.yytops.yysize == 1)
            {
              YYCHK1 (yyresolveStack (&yystack));
              YYDPRINTF ((stderr, "Returning to deterministic operation.\n"));
              yycompressStack (&yystack);
              break;
            }
        }
      continue;
    yyuser_error:
      yyrecoverSyntaxError (&yystack);
      yyposn = yystack.yytops.yystates[0]->yyposn;
    }

 yyacceptlab:
  yyresult = 0;
  goto yyreturn;

 yybuglab:
  YYASSERT (yyfalse);
  goto yyabortlab;

 yyabortlab:
  yyresult = 1;
  goto yyreturn;

 yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;

 yyreturn:
  if (yychar != YYEMPTY)
    yydestruct ("Cleanup: discarding lookahead",
                YYTRANSLATE (yychar), &yylval, &yylloc);

  /* If the stack is well-formed, pop the stack until it is empty,
     destroying its entries as we go.  But free the stack regardless
     of whether it is well-formed.  */
  if (yystack.yyitems)
    {
      yyGLRState** yystates = yystack.yytops.yystates;
      if (yystates)
        {
          size_t yysize = yystack.yytops.yysize;
          size_t yyk;
          for (yyk = 0; yyk < yysize; yyk += 1)
            if (yystates[yyk])
              {
                while (yystates[yyk])
                  {
                    yyGLRState *yys = yystates[yyk];
                 yystack.yyerror_range[1].yystate.yyloc = yys->yyloc;
                  if (yys->yypred != YY_NULLPTR)
                      yydestroyGLRState ("Cleanup: popping", yys);
                    yystates[yyk] = yys->yypred;
                    yystack.yynextFree -= 1;
                    yystack.yyspaceLeft += 1;
                  }
                break;
              }
        }
      yyfreeGLRStack (&yystack);
    }

  return yyresult;
}

/* DEBUGGING ONLY */
#if YYDEBUG
static void
yy_yypstack (yyGLRState* yys)
{
  if (yys->yypred)
    {
      yy_yypstack (yys->yypred);
      YYFPRINTF (stderr, " -> ");
    }
  YYFPRINTF (stderr, "%d@%lu", yys->yylrState,
             (unsigned long int) yys->yyposn);
}

static void
yypstates (yyGLRState* yyst)
{
  if (yyst == YY_NULLPTR)
    YYFPRINTF (stderr, "<null>");
  else
    yy_yypstack (yyst);
  YYFPRINTF (stderr, "\n");
}

static void
yypstack (yyGLRStack* yystackp, size_t yyk)
{
  yypstates (yystackp->yytops.yystates[yyk]);
}

#define YYINDEX(YYX)                                                         \
    ((YYX) == YY_NULLPTR ? -1 : (yyGLRStackItem*) (YYX) - yystackp->yyitems)


static void
yypdumpstack (yyGLRStack* yystackp)
{
  yyGLRStackItem* yyp;
  size_t yyi;
  for (yyp = yystackp->yyitems; yyp < yystackp->yynextFree; yyp += 1)
    {
      YYFPRINTF (stderr, "%3lu. ",
                 (unsigned long int) (yyp - yystackp->yyitems));
      if (*(yybool *) yyp)
        {
          YYASSERT (yyp->yystate.yyisState);
          YYASSERT (yyp->yyoption.yyisState);
          YYFPRINTF (stderr, "Res: %d, LR State: %d, posn: %lu, pred: %ld",
                     yyp->yystate.yyresolved, yyp->yystate.yylrState,
                     (unsigned long int) yyp->yystate.yyposn,
                     (long int) YYINDEX (yyp->yystate.yypred));
          if (! yyp->yystate.yyresolved)
            YYFPRINTF (stderr, ", firstVal: %ld",
                       (long int) YYINDEX (yyp->yystate
                                             .yysemantics.yyfirstVal));
        }
      else
        {
          YYASSERT (!yyp->yystate.yyisState);
          YYASSERT (!yyp->yyoption.yyisState);
          YYFPRINTF (stderr, "Option. rule: %d, state: %ld, next: %ld",
                     yyp->yyoption.yyrule - 1,
                     (long int) YYINDEX (yyp->yyoption.yystate),
                     (long int) YYINDEX (yyp->yyoption.yynext));
        }
      YYFPRINTF (stderr, "\n");
    }
  YYFPRINTF (stderr, "Tops:");
  for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
    YYFPRINTF (stderr, "%lu: %ld; ", (unsigned long int) yyi,
               (long int) YYINDEX (yystackp->yytops.yystates[yyi]));
  YYFPRINTF (stderr, "\n");
}
#endif

#undef yylval
#undef yychar
#undef yynerrs
#undef yylloc



#line 685 "apyc-parser.y" /* glr.c:2584  */


bool debugParser;

#include "apyc-lexer.cc"

/** Make a new "unop" node with function name TOKEN, operand EXPR1, and
 *  location LOC. */
static AST_Ptr
makeUnopExpr (const char* token, AST_Ptr expr1, Location loc)
{
    return NODE (UNOP_AST, makeId(token, loc), expr1);
}

/** Make a new "binop" node with function name TOKEN, and operands EXPR1
 *  and EXPR2. */
static AST_Ptr
makeBinopExpr (const char* token, AST_Ptr expr1, AST_Ptr expr2)
{
    return NODE (BINOP_AST, makeId(token, expr1->location ()), expr1, expr2);
}

/* The following routines are used in a post-parse pass over the tree to detect
 * out-of-place constructs and to replace def nodes with method nodes
 * (for project 2) when appropriate. */

static AST_Ptr checkKids (AST_Ptr, bool, bool, bool, bool);
static AST_Ptr checkPlacement (AST_Ptr, bool, bool, bool, bool);
static void checkPlacement (AST_Ptr);


/** Apply checkPlacement (below) to each child of TREE, replacing the
 *  children's values, and returning TREE. */
static AST_Ptr
checkKids (AST_Ptr tree, bool inLoop, bool inFunc, bool inControl,
           bool inClass)
{
    for (auto& c : *tree) {
        c = checkPlacement (c, inLoop, inFunc, inControl, inClass);
    }
    return tree;
}

/** Helper for checkPlacement(TREE), which follows.  Performs the
 *  checks indicated there on TREE assuming that
 *  A. TREE is in a loop construct iff INLOOP.
 *  B. TREE is in a function definition iff INFUNC.
 *  C. TREE is in a compound control construct ('if', loop), iff INCONTROL.
 *  D. TREE is immediately within a class definition (and not in a compound
 *     statement nested within that class definition) iff INCLASS.
 *
 *  Returns TREE, suitably modified if needed. 
 */
static AST_Ptr
checkPlacement (AST_Ptr tree, bool inLoop, bool inFunc, bool inControl,
                bool inClass)
{
    assert (tree != NULL);
    switch (tree->typeIndex ()) {
    default:
        return checkKids (tree, inLoop, inFunc, inControl, inClass);
    case WHILE_AST: case FOR_AST:
        return checkKids (tree, true, inFunc, true, false);
    case IF_AST:
        return checkKids (tree, inLoop, inFunc, true, false);
    case DEF_AST: 
        if (inControl) {
            error (tree->location (), "illegally nested def statement");
        }
        checkKids (tree, false, true, false, false);
        if (inClass) {
            auto n = NODE (METHOD_AST, tree->children ());
            n->setLoc(tree->location());
            return n;
        } else {
            return tree;
        }
    case CLASS_AST:
        if (inClass || inControl || inFunc) {
            error (tree->location (), "illegally nested class definition");
        }
        return checkKids (tree, false, false, false, true);
    }
}

/** Check that constructs appear only in appropriate contexts in TREE.
 *
 *  1. Checks that
 *    A. break and continue occur only in loops.
 *    B. return occurs only in a functions.
 *    C. class definitions are not nested in functions, other class
 *       definitions, or compound statements.
 *    D. def statements may not be nested in compound control statements.
 *
 *  2. Converts DEF nodes to METHOD nodes in classes.
 *
 *  While these checks could be performed in the parser, it seems less
 *  obscure perform them as a post-pass over the tree.
 *
 *  Assumes that TREE is a module node.
 */
static void
checkPlacement (AST_Ptr tree)
{
    checkPlacement (tree, false, false, false, false);
}
    
AST_Ptr
parse (FILE* f, const string& name)
{
    if (debugParser)
        yydebug = 1;
    initLexer (name);
    theTree = NULL;
    yyparse ();
    if (theTree != NULL) {
        checkPlacement (theTree);
    }
    return theTree;
}

static void
yyerror (const char* s)
{
    error (currentLocation (), s);
}



