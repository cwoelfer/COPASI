// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

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

/* Substitute the variable and function names.  */
#define yyparse         yyparse
#define yyerror         CEvaluationParsererror
#define yydebug         CEvaluationParserdebug
#define yynerrs         CEvaluationParsernerrs

#define yylval          CEvaluationParserlval
#define yychar          CEvaluationParserchar

/* Copy the first part of user declarations.  */
#line 4 "CEvaluationParser.ypp" /* yacc.c:339  */

#define YYSTYPE CEvaluationNode *

#ifdef yylval
# undef yylval
#endif
#define yylval  mpNode

#ifdef yyerror
# undef yyerror
#endif
#define yyerror(__str) \
  if (yychar != YYERRCODE) correctErrorPosition(); \
  CCopasiMessage(CCopasiMessage::ERROR, MCFunction + 1, mPosition)

#include "copasi.h"
#include "CEvaluationNode.h"
#include "CEvaluationLexer.h"

#undef yyparse
#define yyparse CEvaluationParserBase::yyparse

#line 98 "CEvaluationParser_yacc.cpp" /* yacc.c:339  */

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
   by #include "CEvaluationParser.tab.hpp".  */
#ifndef YY_CEVALUATIONPARSER_CEVALUATIONPARSER_TAB_HPP_INCLUDED
# define YY_CEVALUATIONPARSER_CEVALUATIONPARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int CEvaluationParserdebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
enum yytokentype
{
  TOKEN_NUMBER = 258,
  TOKEN_VARIABLE = 259,
  TOKEN_UNIT = 260,
  TOKEN_CALL = 261,
  TOKEN_FUNCTION = 262,
  TOKEN_FUNCTION_2 = 263,
  TOKEN_SIGN = 264,
  TOKEN_OPERATOR_POWER = 265,
  TOKEN_OPERATOR_MULTIPLY = 266,
  TOKEN_OPERATOR_MODULUS = 267,
  TOKEN_OPERATOR_REMAINDER = 268,
  TOKEN_OPERATOR_PLUS = 269,
  TOKEN_LOGICAL_CHOICE = 270,
  TOKEN_LOGICAL_VALUE = 271,
  TOKEN_LOGICAL_NOT = 272,
  TOKEN_LOGICAL_OR = 273,
  TOKEN_LOGICAL_XOR = 274,
  TOKEN_LOGICAL_AND = 275,
  TOKEN_LOGICAL_EQ = 276,
  TOKEN_LOGICAL_NE = 277,
  TOKEN_LOGICAL_GT = 278,
  TOKEN_LOGICAL_GE = 279,
  TOKEN_LOGICAL_LT = 280,
  TOKEN_LOGICAL_LE = 281,
  TOKEN_STRUCTURE_OPEN = 282,
  TOKEN_STRUCTURE_VECTOR_OPEN = 283,
  TOKEN_STRUCTURE_COMMA = 284,
  TOKEN_STRUCTURE_CLOSE = 285,
  TOKEN_STRUCTURE_VECTOR_CLOSE = 286
};
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE CEvaluationParserlval;

#endif /* !YY_CEVALUATIONPARSER_CEVALUATIONPARSER_TAB_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 181 "CEvaluationParser_yacc.cpp" /* yacc.c:358  */

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
#  define YYSTACK_FREE(Ptr) do {/* empty */; } while (0)
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
void *malloc(YYSIZE_T);  /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free(void *);  /* INFRINGES ON USER NAME SPACE */
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
    {\
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
    {\
      YYSIZE_T yyi;                         \
      for (yyi = 0; yyi < (Count); yyi++)   \
        (Dst)[yyi] = (Src)[yyi];            \
    }                                       \
  while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  29
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   475

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  9
/* YYNRULES -- Number of rules.  */
#define YYNRULES  61
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  156

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   286

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
  25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
  0,    87,    87,    92,    98,   103,   108,   116,   126,   131,
  136,   143,   150,   157,   164,   171,   178,   183,   189,   196,
  202,   210,   220,   225,   233,   242,   251,   260,   270,   280,
  287,   294,   302,   310,   317,   324,   332,   340,   347,   354,
  361,   368,   375,   382,   389,   394,   401,   406,   412,   418,
  424,   428,   433,   437,   442,   447,   452,   458,   462,   467,
  472,   477
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOKEN_NUMBER", "TOKEN_VARIABLE",
  "TOKEN_UNIT", "TOKEN_CALL", "TOKEN_FUNCTION", "TOKEN_FUNCTION_2",
  "TOKEN_SIGN", "TOKEN_OPERATOR_POWER", "TOKEN_OPERATOR_MULTIPLY",
  "TOKEN_OPERATOR_MODULUS", "TOKEN_OPERATOR_REMAINDER",
  "TOKEN_OPERATOR_PLUS", "TOKEN_LOGICAL_CHOICE", "TOKEN_LOGICAL_VALUE",
  "TOKEN_LOGICAL_NOT", "TOKEN_LOGICAL_OR", "TOKEN_LOGICAL_XOR",
  "TOKEN_LOGICAL_AND", "TOKEN_LOGICAL_EQ", "TOKEN_LOGICAL_NE",
  "TOKEN_LOGICAL_GT", "TOKEN_LOGICAL_GE", "TOKEN_LOGICAL_LT",
  "TOKEN_LOGICAL_LE", "TOKEN_STRUCTURE_OPEN",
  "TOKEN_STRUCTURE_VECTOR_OPEN", "TOKEN_STRUCTURE_COMMA",
  "TOKEN_STRUCTURE_CLOSE", "TOKEN_STRUCTURE_VECTOR_CLOSE", "$accept",
  "result", "d_or_b", "exp", "bool", "vector", "vstart", "call", "cstart", YY_NULLPTR
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
  285,   286
};
# endif

#define YYPACT_NINF -45

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-45)))

#define YYTABLE_NINF -36

#define yytable_value_is_error(Yytable_value) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
  127,   -45,   -45,   -23,     9,    62,   250,    67,   -45,   127,
  127,    98,   -20,   374,   180,   -45,   188,   -45,   250,   250,
  82,   250,   -45,   107,   127,   374,    30,   279,   307,   -45,
  127,   127,   250,   217,   250,   250,   250,   250,   250,   250,
  250,   250,   250,   127,   127,   127,   127,   127,    84,   -16,
  258,    46,    49,   -14,    47,   223,   127,   159,   -10,   407,
  -45,   -45,    97,   -45,   107,   -45,   107,   137,   157,   116,
  461,   461,   461,   461,   461,   461,   241,    19,    30,     3,
  97,     8,   -45,   -45,   461,   -45,   -45,   -45,   -45,   -45,
  -45,   -45,   -45,   -45,   203,   -45,   -45,   250,    13,   419,
  127,   127,   461,   -45,   284,   250,   250,    52,   320,   424,
  75,   340,   436,   -45,   103,   345,   108,   365,   127,   250,
  127,   127,   250,   127,    14,    14,    32,   371,   305,    50,
  384,    86,   389,   310,    92,   402,   111,   126,   128,   -45,
  -45,   -45,   -45,   -45,   -45,   -45,   -45,   -45,   -45,   127,
  81,   441,    14,    14,   103,   108
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
  0,     8,     5,    57,     0,     0,     0,     0,    22,     0,
  0,     0,     9,     2,     3,     4,     0,    52,     0,     0,
  0,     0,     9,    19,     0,     0,    45,     0,     0,     1,
  0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
  0,     0,     0,     0,     0,     0,     0,     0,     0,     9,
  0,     0,     0,     0,     0,     0,     0,     0,     9,     0,
  16,    44,    32,    36,    15,    13,    14,    11,    12,    10,
  29,    33,    38,    37,    40,    39,    41,    42,    43,     9,
  30,     9,    34,    46,    48,    49,    58,    53,    59,    54,
  60,    55,    61,    56,     0,    47,    17,     0,     9,     0,
  0,     0,    50,    51,     0,     0,     0,     9,     0,     0,
  9,     0,     0,    18,     9,     0,     9,     0,     0,     0,
  0,     0,     0,     0,     0,     0,     9,     0,     0,     9,
  0,     9,     0,     0,     9,     0,     0,     0,     0,     7,
  27,    21,    28,    26,     6,    24,    20,    25,    23,     0,
  9,     0,     0,     0,     0,     0
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
  -45,   -45,     0,   145,    39,   -44,   -45,   -45,   -45
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
  -1,    11,    22,    25,    14,    52,    53,    15,    16
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
  12,    30,    31,   -31,    85,    30,    31,    17,   -35,    12,
  12,    30,    31,    86,    87,    94,    49,    95,     2,   100,
  3,   -31,   -31,   -31,    58,    31,   -35,   -35,   -35,   136,
  12,    12,   -31,   -31,    30,    31,    18,   -35,   -35,    45,
  46,    47,   105,    12,    12,    12,    79,    81,    26,    28,
  103,    46,    47,    30,    31,    51,    98,    32,    33,    34,
  35,    36,   139,    59,    43,    44,    45,    46,    47,    62,
  63,    30,    31,    30,    31,    90,    91,    96,    92,    93,
  142,   118,    76,    77,    78,    80,    82,     1,     2,    19,
  3,     4,     5,     6,    24,    99,    30,    31,    29,    20,
  107,   110,    30,    31,   121,   114,   116,    30,    31,    56,
  152,    21,    48,    30,    31,    83,   144,    32,   126,    47,
  129,   131,   147,   134,   137,   138,    32,    33,    34,    35,
  1,     2,   124,     3,     4,     5,     6,   125,   149,   109,
  112,     0,     7,     8,     9,    13,     0,    32,    33,   150,
  35,    23,   154,   155,    10,    27,   139,   127,   144,   130,
  132,    50,   135,    54,    55,     0,    57,    32,    33,    32,
  33,    34,    35,    36,     0,     0,     0,    64,    66,    67,
  68,    69,    70,    71,    72,    73,    74,    75,   151,    60,
  0,     1,     2,    84,     3,     4,     5,     6,    43,    44,
  45,    46,    47,     7,     8,     9,     1,     2,     0,     3,
  4,     5,     6,     0,     0,    10,    48,     0,    20,     0,
  1,     2,    65,     3,     4,     5,     6,     0,     0,     0,
  21,    48,    20,    32,    33,    34,    35,    36,     0,   102,
  0,     0,   104,     0,    21,   108,   111,     0,     0,     0,
  115,   117,    97,     1,     2,     0,     3,     4,     5,     6,
  44,    45,    46,    47,   128,    20,     0,   133,    32,    33,
  34,    35,    36,     0,     0,     0,     0,    21,     0,    37,
  38,    39,    40,    41,    42,     0,     0,    88,    89,    32,
  33,    34,    35,    36,    32,    33,    34,    35,    36,     0,
  37,    38,    39,    40,    41,    42,     0,     0,     0,    60,
  0,     0,     0,     0,   113,    32,    33,    34,    35,    36,
  32,    33,    34,    35,    36,    43,    44,    45,    46,    47,
  32,    33,    34,    35,    36,   141,     0,    61,     0,     0,
  146,    37,    38,    39,    40,    41,    42,     0,     0,   119,
  32,    33,    34,    35,    36,    32,    33,    34,    35,    36,
  0,    37,    38,    39,    40,    41,    42,     0,     0,   122,
  0,     0,     0,     0,   119,    32,    33,    34,    35,    36,
  0,     0,     0,     0,    32,    33,    34,    35,    36,    43,
  44,    45,    46,    47,   122,    37,    38,    39,    40,    41,
  42,   140,    43,    44,    45,    46,    47,    43,    44,    45,
  46,    47,     0,     0,   143,     0,     0,     0,     0,   145,
  43,    44,    45,    46,    47,    43,    44,    45,    46,    47,
  0,     0,   148,     0,     0,     0,   101,    43,    44,    45,
  46,    47,    43,    44,    45,    46,    47,     0,   106,     0,
  0,     0,     0,   120,    43,    44,    45,    46,    47,    43,
  44,    45,    46,    47,     0,   123,     0,     0,     0,     0,
  153,    32,    33,    34,    35,    36
};

static const yytype_int16 yycheck[] =
{
  0,    21,    22,     0,    48,    21,    22,    30,     0,     9,
  10,    21,    22,    29,    30,    29,    16,    31,     4,    29,
  6,    18,    19,    20,    24,    22,    18,    19,    20,    15,
  30,    31,    29,    30,    21,    22,    27,    29,    30,    20,
  21,    22,    29,    43,    44,    45,    46,    47,     9,    10,
  94,    21,    22,    21,    22,    16,    56,    10,    11,    12,
  13,    14,    30,    24,    18,    19,    20,    21,    22,    30,
  31,    21,    22,    21,    22,    29,    30,    30,    29,    30,
  30,    29,    43,    44,    45,    46,    47,     3,     4,    27,
  6,     7,     8,     9,    27,    56,    21,    22,     0,    15,
  100,   101,    21,    22,    29,   105,   106,    21,    22,    27,
  29,    27,    28,    21,    22,    31,    30,    10,   118,    22,
  120,   121,    30,   123,   124,   125,    10,    11,    12,    13,
  3,     4,    29,     6,     7,     8,     9,    29,    27,   100,
  101,    -1,    15,    16,    17,     0,    -1,    10,    11,   149,
  13,     6,   152,   153,    27,    10,    30,   118,    30,   120,
  121,    16,   123,    18,    19,    -1,    21,    10,    11,    10,
  11,    12,    13,    14,    -1,    -1,    -1,    32,    33,    34,
  35,    36,    37,    38,    39,    40,    41,    42,   149,    30,
  -1,     3,     4,    48,     6,     7,     8,     9,    18,    19,
  20,    21,    22,    15,    16,    17,     3,     4,    -1,     6,
  7,     8,     9,    -1,    -1,    27,    28,    -1,    15,    -1,
  3,     4,     5,     6,     7,     8,     9,    -1,    -1,    -1,
  27,    28,    15,    10,    11,    12,    13,    14,    -1,    94,
  -1,    -1,    97,    -1,    27,   100,   101,    -1,    -1,    -1,
  105,   106,    29,     3,     4,    -1,     6,     7,     8,     9,
  19,    20,    21,    22,   119,    15,    -1,   122,    10,    11,
  12,    13,    14,    -1,    -1,    -1,    -1,    27,    -1,    21,
  22,    23,    24,    25,    26,    -1,    -1,    29,    30,    10,
  11,    12,    13,    14,    10,    11,    12,    13,    14,    -1,
  21,    22,    23,    24,    25,    26,    -1,    -1,    -1,    30,
  -1,    -1,    -1,    -1,    30,    10,    11,    12,    13,    14,
  10,    11,    12,    13,    14,    18,    19,    20,    21,    22,
  10,    11,    12,    13,    14,    30,    -1,    30,    -1,    -1,
  30,    21,    22,    23,    24,    25,    26,    -1,    -1,    29,
  10,    11,    12,    13,    14,    10,    11,    12,    13,    14,
  -1,    21,    22,    23,    24,    25,    26,    -1,    -1,    29,
  -1,    -1,    -1,    -1,    29,    10,    11,    12,    13,    14,
  -1,    -1,    -1,    -1,    10,    11,    12,    13,    14,    18,
  19,    20,    21,    22,    29,    21,    22,    23,    24,    25,
  26,    30,    18,    19,    20,    21,    22,    18,    19,    20,
  21,    22,    -1,    -1,    30,    -1,    -1,    -1,    -1,    30,
  18,    19,    20,    21,    22,    18,    19,    20,    21,    22,
  -1,    -1,    30,    -1,    -1,    -1,    29,    18,    19,    20,
  21,    22,    18,    19,    20,    21,    22,    -1,    29,    -1,
  -1,    -1,    -1,    29,    18,    19,    20,    21,    22,    18,
  19,    20,    21,    22,    -1,    29,    -1,    -1,    -1,    -1,
  29,    10,    11,    12,    13,    14
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
  0,     3,     4,     6,     7,     8,     9,    15,    16,    17,
  27,    33,    34,    35,    36,    39,    40,    30,    27,    27,
  15,    27,    34,    35,    27,    35,    36,    35,    36,     0,
  21,    22,    10,    11,    12,    13,    14,    21,    22,    23,
  24,    25,    26,    18,    19,    20,    21,    22,    28,    34,
  35,    36,    37,    38,    35,    35,    27,    35,    34,    36,
  30,    30,    36,    36,    35,     5,    35,    35,    35,    35,
  35,    35,    35,    35,    35,    35,    36,    36,    36,    34,
  36,    34,    36,    31,    35,    37,    29,    30,    29,    30,
  29,    30,    29,    30,    29,    31,    30,    29,    34,    36,
  29,    29,    35,    37,    35,    29,    29,    34,    35,    36,
  34,    35,    36,    30,    34,    35,    34,    35,    29,    29,
  29,    29,    29,    29,    29,    29,    34,    36,    35,    34,
  36,    34,    36,    35,    34,    36,    15,    34,    34,    30,
  30,    30,    30,    30,    30,    30,    30,    30,    30,    27,
  34,    36,    29,    29,    34,    34
};

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
  0,    32,    33,    33,    34,    34,    34,    34,    35,    35,
  35,    35,    35,    35,    35,    35,    35,    35,    35,    35,
  35,    35,    36,    36,    36,    36,    36,    36,    36,    36,
  36,    36,    36,    36,    36,    36,    36,    36,    36,    36,
  36,    36,    36,    36,    36,    36,    37,    37,    38,    38,
  38,    38,    39,    39,    39,    39,    39,    40,    40,    40,
  40,    40
};

/* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
  0,     2,     1,     1,     1,     1,     8,     8,     1,     1,
  3,     3,     3,     3,     3,     3,     3,     4,     6,     2,
  8,     8,     1,     8,     8,     8,     8,     8,     8,     3,
  3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
  3,     3,     3,     3,     3,     2,     2,     2,     2,     2,
  3,     3,     2,     3,     3,     3,     3,     1,     3,     3,
  3,     3
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
      {\
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {\
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
  do {\
      if (yydebug)                                  \
        YYFPRINTF Args;                             \
    } while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
  do {\
      if (yydebug)                                                            \
        {\
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
yy_symbol_value_print(FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE(yyo);

  if (!yyvaluep)
    return;

# ifdef YYPRINT

  if (yytype < YYNTOKENS)
    YYPRINT(yyoutput, yytoknum[yytype], *yyvaluep);

# endif
  YYUSE(yytype);
}

/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print(FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF(yyoutput, "%s %s (",
            yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print(yyoutput, yytype, yyvaluep);
  YYFPRINTF(yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print(yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF(stderr, "Stack now");

  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF(stderr, " %d", yybot);
    }

  YYFPRINTF(stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
  do {\
      if (yydebug)                                                  \
        yy_stack_print ((Bottom), (Top));                           \
    } while (0)

/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print(yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF(stderr, "Reducing stack by rule %d (line %lu):\n",
            yyrule - 1, yylno);

  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF(stderr, "   $%d = ", yyi + 1);
      yy_symbol_print(stderr,
                      yystos[yyssp[yyi + 1 - yynrhs]],
                      &(yyvsp[(yyi + 1) - (yynrhs)])
                     );
      YYFPRINTF(stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
  do {\
      if (yydebug)                          \
        yy_reduce_print (yyssp, yyvsp, Rule); \
    } while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug = YYDEBUG;
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
yystrlen(const char *yystr)
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
yystpcpy(char *yydest, const char *yysrc)
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
yytnamerr(char *yyres, const char *yystr)
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

do_not_strip_quotes:;
    }

  if (! yyres)
    return yystrlen(yystr);

  return yystpcpy(yyres, yystr) - yyres;
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
yysyntax_error(YYSIZE_T *yymsg_alloc, char **yymsg,
               yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr(YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum {YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
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

      if (!yypact_value_is_default(yyn))
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
                && !yytable_value_is_error(yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }

                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr(YY_NULLPTR, yytname[yyx]);

                  if (!(yysize <= yysize1
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
    YYSIZE_T yysize1 = yysize + yystrlen(yyformat);

    if (!(yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;

    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;

      if (!(yysize <= *yymsg_alloc
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
          yyp += yytnamerr(yyp, yyarg[yyi++]);
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
yydestruct(const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE(yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";

  YY_SYMBOL_PRINT(yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE(yytype);
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
yyparse(void)
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

  YYDPRINTF((stderr, "Starting parse\n"));

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
        yyoverflow(YY_("memory exhausted"),
                   &yyss1, yysize * sizeof(*yyssp),
                   &yyvs1, yysize * sizeof(*yyvsp),
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
          (union yyalloc *) YYSTACK_ALLOC(YYSTACK_BYTES(yystacksize));

        if (! yyptr)
          goto yyexhaustedlab;

        YYSTACK_RELOCATE(yyss_alloc, yyss);
        YYSTACK_RELOCATE(yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE

        if (yyss1 != yyssa)
          YYSTACK_FREE(yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF((stderr, "Stack size increased to %lu\n",
                 (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF((stderr, "Entering state %d\n", yystate));

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

  if (yypact_value_is_default(yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF((stderr, "Reading a token: "));
      yychar = yylex();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE(yychar);
      YY_SYMBOL_PRINT("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;

  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;

  yyn = yytable[yyn];

  if (yyn <= 0)
    {
      if (yytable_value_is_error(yyn))
        goto yyerrlab;

      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT("Shifting", yytoken, &yylval, &yylloc);

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
  yyval = yyvsp[1 - yylen];

  YY_REDUCE_PRINT(yyn);

  switch (yyn)
    {
      case 2:
#line 88 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          mBoolean = false;
          mpRootNode = (yyval);
        }

#line 1422 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 3:
#line 93 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          mBoolean = true;
          mpRootNode = (yyval);
        }

#line 1431 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 4:
#line 99 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[0]);
          mpRootNode = (yyval);
        }

#line 1440 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 5:
#line 104 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[0]);
          mpRootNode = (yyval);
        }

#line 1449 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 6:
#line 109 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-7]);
          (yyval)->addChild((yyvsp[-5]));
          (yyval)->addChild((yyvsp[-3]));
          (yyval)->addChild((yyvsp[-1]));
          mpRootNode = (yyval);
        }

#line 1461 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 7:
#line 117 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyvsp[-7])->setValueType(CEvaluationNode::ValueType::Boolean);
          (yyval) = (yyvsp[-7]);
          (yyval)->addChild((yyvsp[-5]));
          (yyval)->addChild((yyvsp[-3]));
          (yyval)->addChild((yyvsp[-1]));
          mpRootNode = (yyval);
        }

#line 1474 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 8:
#line 127 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[0]);
          mpRootNode = (yyval);
        }

#line 1483 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 9:
#line 132 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[0]);
          mpRootNode = (yyval);
        }

#line 1492 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 10:
#line 137 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-1]);
          (yyval)->addChild((yyvsp[-2]));
          (yyval)->addChild((yyvsp[0]));
          mpRootNode = (yyval);
        }

#line 1503 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 11:
#line 144 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-1]);
          (yyval)->addChild((yyvsp[-2]));
          (yyval)->addChild((yyvsp[0]));
          mpRootNode = (yyval);
        }

#line 1514 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 12:
#line 151 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-1]);
          (yyval)->addChild((yyvsp[-2]));
          (yyval)->addChild((yyvsp[0]));
          mpRootNode = (yyval);
        }

#line 1525 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 13:
#line 158 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-1]);
          (yyval)->addChild((yyvsp[-2]));
          (yyval)->addChild((yyvsp[0]));
          mpRootNode = (yyval);
        }

#line 1536 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 14:
#line 165 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-1]);
          (yyval)->addChild((yyvsp[-2]));
          (yyval)->addChild((yyvsp[0]));
          mpRootNode = (yyval);
        }

#line 1547 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 15:
#line 172 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-1]);
          (yyval)->addChild((yyvsp[-2]));
          (yyval)->addChild((yyvsp[0]));
          mpRootNode = (yyval);
        }

#line 1558 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 16:
#line 179 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-1]);
          mpRootNode = (yyval);
        }

#line 1567 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 17:
#line 184 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-3]);
          (yyval)->addChild((yyvsp[-1]));
          mpRootNode = (yyval);
        }

#line 1577 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 18:
#line 190 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-5]);
          (yyval)->addChild((yyvsp[-3]));
          (yyval)->addChild((yyvsp[-1]));
          mpRootNode = (yyval);
        }

#line 1588 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 19:
#line 197 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-1]);
          (yyval)->addChild((yyvsp[0]));
          mpRootNode = (yyval);
        }

#line 1598 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 20:
#line 203 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-7]);
          (yyval)->addChild((yyvsp[-5]));
          (yyval)->addChild((yyvsp[-3]));
          (yyval)->addChild((yyvsp[-1]));
          mpRootNode = (yyval);
        }

#line 1610 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 21:
#line 211 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-7]);
          (yyvsp[-5])->setValueType(CEvaluationNode::ValueType::Boolean);
          (yyval)->addChild((yyvsp[-5]));
          (yyval)->addChild((yyvsp[-3]));
          (yyval)->addChild((yyvsp[-1]));
          mpRootNode = (yyval);
        }

#line 1623 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 22:
#line 221 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[0]);
          mpRootNode = (yyval);
        }

#line 1632 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 23:
#line 226 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-7]);
          (yyval)->addChild((yyvsp[-5]));
          (yyval)->addChild((yyvsp[-3]));
          (yyval)->addChild((yyvsp[-1]));
          mpRootNode = (yyval);
        }

#line 1644 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 24:
#line 234 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-7]);
          (yyval)->addChild((yyvsp[-5]));
          (yyval)->addChild((yyvsp[-3]));
          (yyvsp[-3])->setValueType(CEvaluationNode::ValueType::Boolean);
          (yyval)->addChild((yyvsp[-1]));
          mpRootNode = (yyval);
        }

#line 1657 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 25:
#line 243 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-7]);
          (yyval)->addChild((yyvsp[-5]));
          (yyval)->addChild((yyvsp[-3]));
          (yyvsp[-1])->setValueType(CEvaluationNode::ValueType::Boolean);
          (yyval)->addChild((yyvsp[-1]));
          mpRootNode = (yyval);
        }

#line 1670 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 26:
#line 252 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyvsp[-7])->setValueType(CEvaluationNode::ValueType::Boolean);
          (yyval) = (yyvsp[-7]);
          (yyval)->addChild((yyvsp[-5]));
          (yyval)->addChild((yyvsp[-3]));
          (yyval)->addChild((yyvsp[-1]));
          mpRootNode = (yyval);
        }

#line 1683 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 27:
#line 261 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyvsp[-7])->setValueType(CEvaluationNode::ValueType::Boolean);
          (yyval) = (yyvsp[-7]);
          (yyval)->addChild((yyvsp[-5]));
          (yyval)->addChild((yyvsp[-3]));
          (yyvsp[-3])->setValueType(CEvaluationNode::ValueType::Boolean);
          (yyval)->addChild((yyvsp[-1]));
          mpRootNode = (yyval);
        }

#line 1697 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 28:
#line 271 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyvsp[-7])->setValueType(CEvaluationNode::ValueType::Boolean);
          (yyval) = (yyvsp[-7]);
          (yyval)->addChild((yyvsp[-5]));
          (yyval)->addChild((yyvsp[-3]));
          (yyvsp[-1])->setValueType(CEvaluationNode::ValueType::Boolean);
          (yyval)->addChild((yyvsp[-1]));
          mpRootNode = (yyval);
        }

#line 1711 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 29:
#line 281 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-1]);
          (yyval)->addChild((yyvsp[-2]));
          (yyval)->addChild((yyvsp[0]));
          mpRootNode = (yyval);
        }

#line 1722 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 30:
#line 288 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-1]);
          (yyval)->addChild((yyvsp[-2]));
          (yyval)->addChild((yyvsp[0]));
          mpRootNode = (yyval);
        }

#line 1733 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 31:
#line 295 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyvsp[0])->setValueType(CEvaluationNode::ValueType::Boolean);
          (yyval) = (yyvsp[-1]);
          (yyval)->addChild((yyvsp[-2]));
          (yyval)->addChild((yyvsp[0]));
          mpRootNode = (yyval);
        }

#line 1745 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 32:
#line 303 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyvsp[-2])->setValueType(CEvaluationNode::ValueType::Boolean);
          (yyval) = (yyvsp[-1]);
          (yyval)->addChild((yyvsp[-2]));
          (yyval)->addChild((yyvsp[0]));
          mpRootNode = (yyval);
        }

#line 1757 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 33:
#line 311 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-1]);
          (yyval)->addChild((yyvsp[-2]));
          (yyval)->addChild((yyvsp[0]));
          mpRootNode = (yyval);
        }

#line 1768 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 34:
#line 318 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-1]);
          (yyval)->addChild((yyvsp[-2]));
          (yyval)->addChild((yyvsp[0]));
          mpRootNode = (yyval);
        }

#line 1779 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 35:
#line 325 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyvsp[0])->setValueType(CEvaluationNode::ValueType::Boolean);
          (yyval) = (yyvsp[-1]);
          (yyval)->addChild((yyvsp[-2]));
          (yyval)->addChild((yyvsp[0]));
          mpRootNode = (yyval);
        }

#line 1791 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 36:
#line 333 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyvsp[-2])->setValueType(CEvaluationNode::ValueType::Boolean);
          (yyval) = (yyvsp[-1]);
          (yyval)->addChild((yyvsp[-2]));
          (yyval)->addChild((yyvsp[0]));
          mpRootNode = (yyval);
        }

#line 1803 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 37:
#line 341 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-1]);
          (yyval)->addChild((yyvsp[-2]));
          (yyval)->addChild((yyvsp[0]));
          mpRootNode = (yyval);
        }

#line 1814 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 38:
#line 348 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-1]);
          (yyval)->addChild((yyvsp[-2]));
          (yyval)->addChild((yyvsp[0]));
          mpRootNode = (yyval);
        }

#line 1825 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 39:
#line 355 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-1]);
          (yyval)->addChild((yyvsp[-2]));
          (yyval)->addChild((yyvsp[0]));
          mpRootNode = (yyval);
        }

#line 1836 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 40:
#line 362 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-1]);
          (yyval)->addChild((yyvsp[-2]));
          (yyval)->addChild((yyvsp[0]));
          mpRootNode = (yyval);
        }

#line 1847 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 41:
#line 369 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-1]);
          (yyval)->addChild((yyvsp[-2]));
          (yyval)->addChild((yyvsp[0]));
          mpRootNode = (yyval);
        }

#line 1858 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 42:
#line 376 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-1]);
          (yyval)->addChild((yyvsp[-2]));
          (yyval)->addChild((yyvsp[0]));
          mpRootNode = (yyval);
        }

#line 1869 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 43:
#line 383 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-1]);
          (yyval)->addChild((yyvsp[-2]));
          (yyval)->addChild((yyvsp[0]));
          mpRootNode = (yyval);
        }

#line 1880 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 44:
#line 390 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-1]);
          mpRootNode = (yyval);
        }

#line 1889 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 45:
#line 395 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-1]);
          (yyval)->addChild((yyvsp[0]));
          mpRootNode = (yyval);
        }

#line 1899 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 46:
#line 402 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = new CEvaluationNodeVector();
          mpNodeList->push_back((yyval));
        }

#line 1908 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 47:
#line 407 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-1]);
        }

#line 1916 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 48:
#line 413 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = new CEvaluationNodeVector();
          mpNodeList->push_back((yyval));
          (yyval)->addChild((yyvsp[0]));
        }

#line 1926 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 49:
#line 419 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = new CEvaluationNodeVector();
          mpNodeList->push_back((yyval));
          (yyval)->addChild((yyvsp[0]));
        }

#line 1936 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 50:
#line 425 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval)->addChild((yyvsp[0]));
        }

#line 1944 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 51:
#line 429 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval)->addChild((yyvsp[0]));
        }

#line 1952 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 52:
#line 434 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-1]);
        }

#line 1960 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 53:
#line 438 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-2]);
          (yyval)->addChild((yyvsp[-1]));
        }

#line 1969 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 54:
#line 443 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-2]);
          (yyval)->addChild((yyvsp[-1]));
        }

#line 1978 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 55:
#line 448 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-2]);
          (yyval)->addChild((yyvsp[-1]));
        }

#line 1987 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 56:
#line 453 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-2]);
          (yyval)->addChild((yyvsp[-1]));
        }

#line 1996 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 57:
#line 459 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[0]);
        }

#line 2004 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 58:
#line 463 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-2]);
          (yyval)->addChild((yyvsp[-1]));
        }

#line 2013 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 59:
#line 468 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-2]);
          (yyval)->addChild((yyvsp[-1]));
        }

#line 2022 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 60:
#line 473 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-2]);
          (yyval)->addChild((yyvsp[-1]));
        }

#line 2031 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

      case 61:
#line 478 "CEvaluationParser.ypp" /* yacc.c:1646  */
        {
          (yyval) = (yyvsp[-2]);
          (yyval)->addChild((yyvsp[-1]));
        }

#line 2040 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */
        break;

#line 2044 "CEvaluationParser_yacc.cpp" /* yacc.c:1646  */

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
  YY_SYMBOL_PRINT("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK(yylen);
  yylen = 0;
  YY_STACK_PRINT(yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE(yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror(YY_("syntax error"));
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
              YYSTACK_FREE(yymsg);

            yymsg = (char *) YYSTACK_ALLOC(yymsg_alloc);

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

        yyerror(yymsgp);

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
          yydestruct("Error: discarding",
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
  YYPOPSTACK(yylen);
  yylen = 0;
  YY_STACK_PRINT(yyss, yyssp);
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

      if (!yypact_value_is_default(yyn))
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

      yydestruct("Error: popping",
                 yystos[yystate], yyvsp);
      YYPOPSTACK(1);
      yystate = *yyssp;
      YY_STACK_PRINT(yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Shift the error token.  */
  YY_SYMBOL_PRINT("Shifting", yystos[yyn], yyvsp, yylsp);

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
  yyerror(YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:

  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE(yychar);
      yydestruct("Cleanup: discarding lookahead",
                 yytoken, &yylval);
    }

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK(yylen);
  YY_STACK_PRINT(yyss, yyssp);

  while (yyssp != yyss)
    {
      yydestruct("Cleanup: popping",
                 yystos[*yyssp], yyvsp);
      YYPOPSTACK(1);
    }

#ifndef yyoverflow

  if (yyss != yyssa)
    YYSTACK_FREE(yyss);

#endif
#if YYERROR_VERBOSE

  if (yymsg != yymsgbuf)
    YYSTACK_FREE(yymsg);

#endif
  return yyresult;
}
#line 484 "CEvaluationParser.ypp" /* yacc.c:1906  */
