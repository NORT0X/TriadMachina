/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "parser.y"

    #include <cstdint>
    #include <iostream>
    #include <memory>

    #include "../inc/assembler/Assembler.hpp"
    #include "../inc/common/Elf.hpp"

    using namespace std;

    extern int yylex(void);
    extern int lineNum;
    extern unique_ptr<Assembler> as;
    
    void yyerror(const char *);

/* Line 371 of yacc.c  */
#line 85 "parser.cpp"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
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
   by #include "parser.hpp".  */
#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     LITERAL = 258,
     SYMBOL = 259,
     STRING = 260,
     GPR = 261,
     CSR = 262,
     GLOBAL = 263,
     EXTERN = 264,
     SECTION = 265,
     WORD = 266,
     SKIP = 267,
     ASCII = 268,
     EQU = 269,
     END = 270,
     HALT = 271,
     INT = 272,
     IRET = 273,
     CALL = 274,
     RET = 275,
     JMP = 276,
     BEQ = 277,
     BNE = 278,
     BGT = 279,
     PUSH = 280,
     POP = 281,
     XCHG = 282,
     ADD = 283,
     SUB = 284,
     MUL = 285,
     DIV = 286,
     NOT = 287,
     AND = 288,
     OR = 289,
     XOR = 290,
     SHL = 291,
     SHR = 292,
     LD = 293,
     ST = 294,
     CSRRD = 295,
     CSRWR = 296,
     ENDL = 297,
     UMINUS = 298
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 21 "parser.y"

    uint32_t ival;
    uint8_t rval;
    char *sval;


/* Line 387 of yacc.c  */
#line 178 "parser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 206 "parser.cpp"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

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
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  83
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   219

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  11
/* YYNRULES -- Number of rules.  */
#define YYNRULES  76
/* YYNRULES -- Number of states.  */
#define YYNSTATES  187

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   298

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    48,     2,     2,     2,
      51,    52,     2,    43,    47,    44,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    46,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    49,     2,    50,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    45
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     6,     8,    11,    15,    19,    22,
      25,    28,    30,    33,    36,    39,    42,    45,    48,    51,
      56,    58,    60,    62,    64,    67,    70,    72,    75,    78,
      85,    92,    99,   106,   113,   120,   123,   126,   131,   136,
     141,   146,   151,   154,   159,   164,   169,   174,   179,   185,
     191,   196,   201,   206,   213,   222,   231,   236,   241,   248,
     257,   266,   271,   276,   278,   280,   284,   288,   290,   294,
     296,   300,   302,   304,   308,   312,   315
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      54,     0,    -1,    -1,    55,    -1,    56,    -1,    55,    56,
      -1,    57,    59,    42,    -1,    57,    58,    42,    -1,    57,
      42,    -1,    59,    42,    -1,    58,    42,    -1,    42,    -1,
       4,    46,    -1,     8,    61,    -1,     9,    62,    -1,    10,
       4,    -1,    11,    60,    -1,    12,     3,    -1,    13,     5,
      -1,    14,     4,    47,    63,    -1,    15,    -1,    16,    -1,
      17,    -1,    18,    -1,    19,     3,    -1,    19,     4,    -1,
      20,    -1,    21,     3,    -1,    21,     4,    -1,    22,     6,
      47,     6,    47,     3,    -1,    22,     6,    47,     6,    47,
       4,    -1,    23,     6,    47,     6,    47,     3,    -1,    23,
       6,    47,     6,    47,     4,    -1,    24,     6,    47,     6,
      47,     3,    -1,    24,     6,    47,     6,    47,     4,    -1,
      25,     6,    -1,    26,     6,    -1,    27,     6,    47,     6,
      -1,    28,     6,    47,     6,    -1,    29,     6,    47,     6,
      -1,    30,     6,    47,     6,    -1,    31,     6,    47,     6,
      -1,    32,     6,    -1,    33,     6,    47,     6,    -1,    34,
       6,    47,     6,    -1,    35,     6,    47,     6,    -1,    36,
       6,    47,     6,    -1,    37,     6,    47,     6,    -1,    38,
      48,     3,    47,     6,    -1,    38,    48,     4,    47,     6,
      -1,    38,     3,    47,     6,    -1,    38,     4,    47,     6,
      -1,    38,     6,    47,     6,    -1,    38,    49,     6,    50,
      47,     6,    -1,    38,    49,     6,    43,     3,    50,    47,
       6,    -1,    38,    49,     6,    43,     4,    50,    47,     6,
      -1,    39,     6,    47,     3,    -1,    39,     6,    47,     4,
      -1,    39,     6,    47,    49,     6,    50,    -1,    39,     6,
      47,    49,     6,    43,     3,    50,    -1,    39,     6,    47,
      49,     6,    43,     4,    50,    -1,    40,     7,    47,     6,
      -1,    41,     6,    47,     7,    -1,     4,    -1,     3,    -1,
      60,    47,     4,    -1,    60,    47,     3,    -1,     4,    -1,
      61,    47,     4,    -1,     4,    -1,    62,    47,     4,    -1,
       3,    -1,     4,    -1,    63,    43,    63,    -1,    63,    44,
      63,    -1,    44,    63,    -1,    51,    63,    52,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    45,    45,    47,    51,    52,    56,    57,    58,    59,
      60,    61,    65,    69,    70,    71,    72,    73,    74,    75,
      76,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   125,   126,   127,   128,   132,   133,   137,
     138,   142,   143,   144,   145,   146,   147
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "LITERAL", "SYMBOL", "STRING", "GPR",
  "CSR", "GLOBAL", "EXTERN", "SECTION", "WORD", "SKIP", "ASCII", "EQU",
  "END", "HALT", "INT", "IRET", "CALL", "RET", "JMP", "BEQ", "BNE", "BGT",
  "PUSH", "POP", "XCHG", "ADD", "SUB", "MUL", "DIV", "NOT", "AND", "OR",
  "XOR", "SHL", "SHR", "LD", "ST", "CSRRD", "CSRWR", "ENDL", "'+'", "'-'",
  "UMINUS", "':'", "','", "'$'", "'['", "']'", "'('", "')'", "$accept",
  "program", "statements", "statement", "label", "directive",
  "instruction", "init_list", "global_args", "extern_args", "ival_expr", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,    43,    45,   298,    58,    44,    36,    91,
      93,    40,    41
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    53,    54,    54,    55,    55,    56,    56,    56,    56,
      56,    56,    57,    58,    58,    58,    58,    58,    58,    58,
      58,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    60,    60,    60,    60,    61,    61,    62,
      62,    63,    63,    63,    63,    63,    63
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     1,     2,     3,     3,     2,     2,
       2,     1,     2,     2,     2,     2,     2,     2,     2,     4,
       1,     1,     1,     1,     2,     2,     1,     2,     2,     6,
       6,     6,     6,     6,     6,     2,     2,     4,     4,     4,
       4,     4,     2,     4,     4,     4,     4,     4,     5,     5,
       4,     4,     4,     6,     8,     8,     4,     4,     6,     8,
       8,     4,     4,     1,     1,     3,     3,     1,     3,     1,
       3,     1,     1,     3,     3,     2,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     0,     0,     0,     0,     0,     0,    20,
      21,    22,    23,     0,    26,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    11,     0,     3,     4,
       0,     0,     0,    12,    67,    13,    69,    14,    15,    64,
      63,    16,    17,    18,     0,    24,    25,    27,    28,     0,
       0,     0,    35,    36,     0,     0,     0,     0,     0,    42,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     1,     5,     8,     0,     0,    10,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     7,     6,    68,    70,
      66,    65,    71,    72,     0,     0,    19,     0,     0,     0,
      37,    38,    39,    40,    41,    43,    44,    45,    46,    47,
      50,    51,    52,     0,     0,     0,     0,    56,    57,     0,
      61,    62,    75,     0,     0,     0,     0,     0,     0,    48,
      49,     0,     0,     0,     0,    76,    73,    74,    29,    30,
      31,    32,    33,    34,     0,     0,    53,     0,    58,     0,
       0,     0,     0,    54,    55,    59,    60
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    37,    38,    39,    40,    41,    42,    51,    45,    47,
     126
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -123
static const yytype_int16 yypact[] =
{
      47,   -34,    16,    36,    40,    12,    42,    41,    43,  -123,
    -123,  -123,  -123,    14,  -123,    19,    46,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,     1,   134,   135,   137,  -123,    53,    47,  -123,
      82,    99,   102,  -123,  -123,    98,  -123,   100,  -123,  -123,
    -123,   101,  -123,  -123,   103,  -123,  -123,  -123,  -123,   104,
     105,   106,  -123,  -123,   107,   108,   109,   110,   111,  -123,
     112,   113,   114,   115,   116,   117,   118,   136,    21,   140,
     138,   139,   141,  -123,  -123,  -123,   142,   145,  -123,  -123,
     162,   163,    23,    -3,   143,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   183,   184,
     144,   146,   -37,     5,   186,   161,  -123,  -123,  -123,  -123,
    -123,  -123,  -123,  -123,    -3,    -3,   -15,   147,   148,   149,
    -123,  -123,  -123,  -123,  -123,  -123,  -123,  -123,  -123,  -123,
    -123,  -123,  -123,   191,   192,    27,   152,  -123,  -123,   194,
    -123,  -123,  -123,   -33,    -3,    -3,    31,    33,    35,  -123,
    -123,   151,   153,   196,   -29,  -123,  -123,  -123,  -123,  -123,
    -123,  -123,  -123,  -123,   157,   158,  -123,    39,  -123,   200,
     201,   159,   160,  -123,  -123,  -123,  -123
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -123,  -123,  -123,   177,  -123,   178,   179,  -123,  -123,  -123,
    -122
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
     122,   123,   152,   153,    75,    76,   145,    77,   147,   148,
     154,   155,    43,   146,   177,    49,    50,    55,    56,   165,
      44,   178,    57,    58,   110,   111,   120,   121,   154,   155,
     161,   162,   166,   167,   168,   169,   170,   171,   172,   173,
      46,   124,   181,   182,    48,    52,    53,    54,   125,    78,
      79,     1,    59,    83,   149,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    85,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      80,    88,    81,    82,    89,    90,   112,    91,    92,   127,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   118,   119,   151,     0,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   109,   116,   113,   114,   117,   115,   141,
     142,   143,   150,   144,   156,   157,   158,   159,   160,   163,
     164,   174,   176,   175,   179,   180,   183,   184,     0,   185,
     186,     0,     0,     0,     0,    84,     0,     0,    86,    87
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-123)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       3,     4,   124,   125,     3,     4,    43,     6,     3,     4,
      43,    44,    46,    50,    43,     3,     4,     3,     4,    52,
       4,    50,     3,     4,     3,     4,     3,     4,    43,    44,
       3,     4,   154,   155,     3,     4,     3,     4,     3,     4,
       4,    44,     3,     4,     4,     3,     5,     4,    51,    48,
      49,     4,     6,     0,    49,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       6,    42,     7,     6,    42,    47,     6,    47,    47,     6,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47,     4,     4,     7,    -1,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,    47,    42,    47,    47,    42,    47,     6,
       6,    47,     6,    47,    47,    47,    47,     6,     6,    47,
       6,    50,     6,    50,    47,    47,     6,     6,    -1,    50,
      50,    -1,    -1,    -1,    -1,    38,    -1,    -1,    40,    40
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    54,    55,    56,
      57,    58,    59,    46,     4,    61,     4,    62,     4,     3,
       4,    60,     3,     5,     4,     3,     4,     3,     4,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     3,     4,     6,    48,    49,
       6,     7,     6,     0,    56,    42,    58,    59,    42,    42,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    47,
       3,     4,     6,    47,    47,    47,    42,    42,     4,     4,
       3,     4,     3,     4,    44,    51,    63,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,    47,    47,    43,    50,     3,     4,    49,
       6,     7,    63,    63,    43,    44,    47,    47,    47,     6,
       6,     3,     4,    47,     6,    52,    63,    63,     3,     4,
       3,     4,     3,     4,    50,    50,     6,    43,    50,    47,
      47,     3,     4,     6,     6,    50,    50
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

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
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

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
      yychar = YYLEX;
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
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
/* Line 1792 of yacc.c  */
#line 47 "parser.y"
    { std::cout << "END\n"; }
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 65 "parser.y"
    { std::cout << (yyvsp[(1) - (2)].sval) << std::endl; as->label((yyvsp[(1) - (2)].sval)); }
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 71 "parser.y"
    { std::cout << "SECTION" << " " << (yyvsp[(2) - (2)].sval) << std::endl; as->sectionDirective((yyvsp[(2) - (2)].sval)); }
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 73 "parser.y"
    { std::cout << "LITERAL " << (yyvsp[(2) - (2)].ival) << std::endl; as->skipDirective((yyvsp[(2) - (2)].ival)); }
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 74 "parser.y"
    { std::cout << "ASCII " << "$2" << std::endl; }
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 75 "parser.y"
    { std::cout << "EQU " << (yyvsp[(2) - (4)].sval) << "=" << "IVAL" << std::endl; }
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 76 "parser.y"
    { as->end(); }
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 80 "parser.y"
    { MInstruction instr(OPCODE::HALT, 0, 0, 0, 0 ,0); as->insertInstruction(instr); }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 81 "parser.y"
    { MInstruction instr(OPCODE::INT, 0, 0, 0, 0, 0); as->insertInstruction(instr); }
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 82 "parser.y"
    { std::cout << "IRET\n"; as->iretInstruction();}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 83 "parser.y"
    { std::cout << "CALL " << (yyvsp[(2) - (2)].ival) << std::endl; as->callInstruction((yyvsp[(2) - (2)].ival)); }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 84 "parser.y"
    { std::cout << "CALL " << (yyvsp[(2) - (2)].sval) << std::endl; as->callInstruction((yyvsp[(2) - (2)].sval)); }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 85 "parser.y"
    { MInstruction instr(OPCODE::LOAD, 3, PC, SP, 0, 4); as->insertInstruction(instr); }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 86 "parser.y"
    { std::cout << "JMP " << (yyvsp[(2) - (2)].ival) << std::endl; as->jmpInstruction((yyvsp[(2) - (2)].ival)); }
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 87 "parser.y"
    { std::cout << "JMP " << (yyvsp[(2) - (2)].sval) << std::endl; as->jmpInstruction((yyvsp[(2) - (2)].sval)); }
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 88 "parser.y"
    { std::cout << "BEQ " << (yyvsp[(2) - (6)].rval) << " " << (yyvsp[(4) - (6)].rval) << " " << (yyvsp[(6) - (6)].ival) << std::endl; as->branch((yyvsp[(2) - (6)].rval), (yyvsp[(4) - (6)].rval), (yyvsp[(6) - (6)].ival), 0b0001); }
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 89 "parser.y"
    { std::cout << "BEQ " << (yyvsp[(2) - (6)].rval) << " " << (yyvsp[(4) - (6)].rval) << " " << (yyvsp[(6) - (6)].sval) << std::endl; as->branch((yyvsp[(2) - (6)].rval), (yyvsp[(4) - (6)].rval), (yyvsp[(6) - (6)].sval), 0b1001); }
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 90 "parser.y"
    { std::cout << "BNE " << (yyvsp[(2) - (6)].rval) << " " << (yyvsp[(4) - (6)].rval) << " " << (yyvsp[(6) - (6)].ival) << std::endl; as->branch((yyvsp[(2) - (6)].rval), (yyvsp[(4) - (6)].rval), (yyvsp[(6) - (6)].ival), 0b0010); }
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 91 "parser.y"
    { std::cout << "BNE " << (yyvsp[(2) - (6)].rval) << " " << (yyvsp[(4) - (6)].rval) << " " << (yyvsp[(6) - (6)].sval) << std::endl; as->branch((yyvsp[(2) - (6)].rval), (yyvsp[(4) - (6)].rval), (yyvsp[(6) - (6)].sval), 0b1010); }
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 92 "parser.y"
    { std::cout << "BGT " << (yyvsp[(2) - (6)].rval) << " " << (yyvsp[(4) - (6)].rval) << " " << (yyvsp[(6) - (6)].ival) << std::endl; as->branch((yyvsp[(2) - (6)].rval), (yyvsp[(4) - (6)].rval), (yyvsp[(6) - (6)].ival), 0b0011); }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 93 "parser.y"
    { std::cout << "BGT " << (yyvsp[(2) - (6)].rval) << " " << (yyvsp[(4) - (6)].rval) << " " << (yyvsp[(6) - (6)].sval) << std::endl; as->branch((yyvsp[(2) - (6)].rval), (yyvsp[(4) - (6)].rval), (yyvsp[(6) - (6)].sval), 0b1011); }
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 94 "parser.y"
    { MInstruction instr(OPCODE::STORE, 1, SP, 0, (yyvsp[(2) - (2)].rval), -4); as->insertInstruction(instr); }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 95 "parser.y"
    { MInstruction instr(OPCODE::LOAD, 3, (yyvsp[(2) - (2)].rval), 0x0E, 0, 4); as->insertInstruction(instr); }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 96 "parser.y"
    { MInstruction instr(OPCODE::XCHG, 0, 0, (yyvsp[(4) - (4)].rval), (yyvsp[(2) - (4)].rval), 0); as->insertInstruction(instr); }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 97 "parser.y"
    { MInstruction instr(OPCODE::ARITHMETIC, 0, (yyvsp[(4) - (4)].rval), (yyvsp[(4) - (4)].rval), (yyvsp[(2) - (4)].rval), 0); as->insertInstruction(instr); }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 98 "parser.y"
    { MInstruction instr(OPCODE::ARITHMETIC, 1, (yyvsp[(4) - (4)].rval), (yyvsp[(4) - (4)].rval), (yyvsp[(2) - (4)].rval), 0); as->insertInstruction(instr); }
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 99 "parser.y"
    { MInstruction instr(OPCODE::ARITHMETIC, 2, (yyvsp[(4) - (4)].rval), (yyvsp[(4) - (4)].rval), (yyvsp[(2) - (4)].rval), 0); as->insertInstruction(instr);  }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 100 "parser.y"
    { MInstruction instr(OPCODE::ARITHMETIC, 3, (yyvsp[(4) - (4)].rval), (yyvsp[(4) - (4)].rval), (yyvsp[(2) - (4)].rval), 0); as->insertInstruction(instr); }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 101 "parser.y"
    { MInstruction instr(OPCODE::LOGIC, 0, (yyvsp[(2) - (2)].rval), (yyvsp[(2) - (2)].rval), 0, 0); as->insertInstruction(instr); }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 102 "parser.y"
    { MInstruction instr(OPCODE::LOGIC, 1, (yyvsp[(4) - (4)].rval), (yyvsp[(4) - (4)].rval), (yyvsp[(2) - (4)].rval), 0); as->insertInstruction(instr); }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 103 "parser.y"
    { MInstruction instr(OPCODE::LOGIC, 2, (yyvsp[(4) - (4)].rval), (yyvsp[(4) - (4)].rval), (yyvsp[(2) - (4)].rval), 0); as->insertInstruction(instr); }
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 104 "parser.y"
    { MInstruction instr(OPCODE::LOGIC, 3, (yyvsp[(4) - (4)].rval), (yyvsp[(4) - (4)].rval), (yyvsp[(2) - (4)].rval), 0); as->insertInstruction(instr); }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 105 "parser.y"
    { MInstruction instr(OPCODE::SHIFT, 0, (yyvsp[(4) - (4)].rval), (yyvsp[(4) - (4)].rval), (yyvsp[(2) - (4)].rval), 0); as->insertInstruction(instr); }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 106 "parser.y"
    { MInstruction instr(OPCODE::SHIFT, 1, (yyvsp[(4) - (4)].rval), (yyvsp[(4) - (4)].rval), (yyvsp[(2) - (4)].rval), 0); as->insertInstruction(instr); }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 107 "parser.y"
    { std::cout << "LD " << (yyvsp[(3) - (5)].ival) << " " << (yyvsp[(5) - (5)].rval) << std::endl; as->loadLiteral((yyvsp[(3) - (5)].ival), (yyvsp[(5) - (5)].rval), LiteralMode::VALUE); }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 108 "parser.y"
    { std::cout << "LD " << (yyvsp[(3) - (5)].sval) << " " << (yyvsp[(5) - (5)].rval) << std::endl; as->loadSymbol((yyvsp[(3) - (5)].sval), (yyvsp[(5) - (5)].rval), SymbolMode::VALUE); }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 109 "parser.y"
    { std::cout << "LD " << (yyvsp[(2) - (4)].ival) << " " << (yyvsp[(4) - (4)].rval) << std::endl; as->loadLiteral((yyvsp[(2) - (4)].ival), (yyvsp[(4) - (4)].rval), LiteralMode::MEMORY); }
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 110 "parser.y"
    { std::cout << "LD " << (yyvsp[(2) - (4)].sval) << " " << (yyvsp[(4) - (4)].rval) << std::endl; as->loadSymbol((yyvsp[(2) - (4)].sval), (yyvsp[(4) - (4)].rval), SymbolMode::MEMORY); }
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 111 "parser.y"
    { std::cout << "LD " << (yyvsp[(2) - (4)].rval) << " " << (yyvsp[(4) - (4)].rval) << std::endl; as->loadReg((yyvsp[(2) - (4)].rval), (yyvsp[(4) - (4)].rval), RegMode::REG_DIR); }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 112 "parser.y"
    { std::cout << "LD " << (yyvsp[(3) - (6)].rval) << " " << (yyvsp[(6) - (6)].rval) << std::endl; as->loadReg((yyvsp[(3) - (6)].rval), (yyvsp[(6) - (6)].rval), RegMode::REG_IND); }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 113 "parser.y"
    { std::cout << "LD " << (yyvsp[(3) - (8)].rval) << "+" << (yyvsp[(5) - (8)].ival) << (yyvsp[(8) - (8)].rval) << std::endl; as->loadRegLiteral((yyvsp[(3) - (8)].rval), (yyvsp[(5) - (8)].ival), (yyvsp[(8) - (8)].rval)); }
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 114 "parser.y"
    { std::cout << "LD " << (yyvsp[(3) - (8)].rval) << "+" << (yyvsp[(5) - (8)].sval) << (yyvsp[(8) - (8)].rval) << std::endl; }
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 115 "parser.y"
    { std::cout << "ST " << (yyvsp[(2) - (4)].rval) << " " << (yyvsp[(4) - (4)].ival) << std::endl; as->storeLiteral((yyvsp[(2) - (4)].rval), (yyvsp[(4) - (4)].ival)); }
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 116 "parser.y"
    { std::cout << "ST " << (yyvsp[(2) - (4)].rval) << " " << (yyvsp[(4) - (4)].sval) << std::endl; as->storeSymbol((yyvsp[(2) - (4)].rval), (yyvsp[(4) - (4)].sval)); }
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 117 "parser.y"
    { std::cout << "ST " << (yyvsp[(2) - (6)].rval) << " " << (yyvsp[(5) - (6)].rval) << std::endl; as->storeReg((yyvsp[(2) - (6)].rval), (yyvsp[(5) - (6)].rval)); }
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 118 "parser.y"
    { std::cout << "ST " << (yyvsp[(2) - (8)].rval) << " " << (yyvsp[(5) - (8)].rval) << "+" << (yyvsp[(7) - (8)].ival) << std::endl; as->storeRegLiteral((yyvsp[(2) - (8)].rval), (yyvsp[(5) - (8)].rval), (yyvsp[(7) - (8)].ival)); }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 119 "parser.y"
    { std::cout << "ST " << (yyvsp[(2) - (8)].rval) << " " << (yyvsp[(5) - (8)].rval) << "+" << (yyvsp[(7) - (8)].sval) << std::endl; }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 120 "parser.y"
    { MInstruction instr(OPCODE::LOAD, 0, (yyvsp[(4) - (4)].rval), (yyvsp[(2) - (4)].rval), 0, 0); as->insertInstruction(instr); }
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 121 "parser.y"
    { MInstruction instr(OPCODE::LOAD, 4, (yyvsp[(4) - (4)].rval), (yyvsp[(2) - (4)].rval), 0, 0); as->insertInstruction(instr); }
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 125 "parser.y"
    { std::cout << "INIT_LIST " << (yyvsp[(1) - (1)].sval) << std::endl; as->wordDirectiveSymbol((yyvsp[(1) - (1)].sval)); }
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 126 "parser.y"
    { std::cout << "INIT_LIST " << (yyvsp[(1) - (1)].ival) << std::endl; as->wordDirectiveLiteral((yyvsp[(1) - (1)].ival)); }
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 127 "parser.y"
    { std::cout << "INIT_LIST " << (yyvsp[(3) - (3)].sval) << std::endl; as->wordDirectiveSymbol((yyvsp[(3) - (3)].sval)); }
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 128 "parser.y"
    { std::cout << "INIT_LIST " << (yyvsp[(3) - (3)].ival) << std::endl; as->wordDirectiveLiteral((yyvsp[(3) - (3)].ival)); }
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 132 "parser.y"
    { std::cout << "GLOBAL_ARGS " << (yyvsp[(1) - (1)].sval) << std::endl; as->globalDirective((yyvsp[(1) - (1)].sval)); }
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 133 "parser.y"
    { std::cout << "GLOBAL_ARGS " << (yyvsp[(3) - (3)].sval) << std::endl; as->globalDirective((yyvsp[(3) - (3)].sval)); }
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 137 "parser.y"
    { std::cout << "EXTERN_ARGS " << (yyvsp[(1) - (1)].sval) << std::endl; as->externDirective((yyvsp[(1) - (1)].sval)); }
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 138 "parser.y"
    { std::cout << "EXTERN_ARGS " << (yyvsp[(3) - (3)].sval) << std::endl; as->externDirective((yyvsp[(3) - (3)].sval)); }
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 142 "parser.y"
    { std::cout << "IVAL_EXPR " << (yyvsp[(1) - (1)].ival) << std::endl; }
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 143 "parser.y"
    { std::cout << "IVAL_EXPR " << (yyvsp[(1) - (1)].sval) << std::endl; }
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 144 "parser.y"
    { std::cout << "IVAL_EXPR +\n"; }
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 145 "parser.y"
    { std::cout << "IVAL_EXPR -\n"; }
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 146 "parser.y"
    { std::cout << "UMINUS\n"; }
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 147 "parser.y"
    { std::cout << "IVAL_EXPR ()\n"; }
    break;


/* Line 1792 of yacc.c  */
#line 1931 "parser.cpp"
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

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 150 "parser.y"


void yyerror(const char *s) {
    std::cout << "PARSER ERROR!\n"  << "Message: " << s << std::endl;
    exit(-1);
}
