/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
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

#line 88 "parser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_LITERAL = 3,                    /* LITERAL  */
  YYSYMBOL_SYMBOL = 4,                     /* SYMBOL  */
  YYSYMBOL_STRING = 5,                     /* STRING  */
  YYSYMBOL_GPR = 6,                        /* GPR  */
  YYSYMBOL_CSR = 7,                        /* CSR  */
  YYSYMBOL_GLOBAL = 8,                     /* GLOBAL  */
  YYSYMBOL_EXTERN = 9,                     /* EXTERN  */
  YYSYMBOL_SECTION = 10,                   /* SECTION  */
  YYSYMBOL_WORD = 11,                      /* WORD  */
  YYSYMBOL_SKIP = 12,                      /* SKIP  */
  YYSYMBOL_ASCII = 13,                     /* ASCII  */
  YYSYMBOL_EQU = 14,                       /* EQU  */
  YYSYMBOL_END = 15,                       /* END  */
  YYSYMBOL_HALT = 16,                      /* HALT  */
  YYSYMBOL_INT = 17,                       /* INT  */
  YYSYMBOL_IRET = 18,                      /* IRET  */
  YYSYMBOL_CALL = 19,                      /* CALL  */
  YYSYMBOL_RET = 20,                       /* RET  */
  YYSYMBOL_JMP = 21,                       /* JMP  */
  YYSYMBOL_BEQ = 22,                       /* BEQ  */
  YYSYMBOL_BNE = 23,                       /* BNE  */
  YYSYMBOL_BGT = 24,                       /* BGT  */
  YYSYMBOL_PUSH = 25,                      /* PUSH  */
  YYSYMBOL_POP = 26,                       /* POP  */
  YYSYMBOL_XCHG = 27,                      /* XCHG  */
  YYSYMBOL_ADD = 28,                       /* ADD  */
  YYSYMBOL_SUB = 29,                       /* SUB  */
  YYSYMBOL_MUL = 30,                       /* MUL  */
  YYSYMBOL_DIV = 31,                       /* DIV  */
  YYSYMBOL_NOT = 32,                       /* NOT  */
  YYSYMBOL_AND = 33,                       /* AND  */
  YYSYMBOL_OR = 34,                        /* OR  */
  YYSYMBOL_XOR = 35,                       /* XOR  */
  YYSYMBOL_SHL = 36,                       /* SHL  */
  YYSYMBOL_SHR = 37,                       /* SHR  */
  YYSYMBOL_LD = 38,                        /* LD  */
  YYSYMBOL_ST = 39,                        /* ST  */
  YYSYMBOL_CSRRD = 40,                     /* CSRRD  */
  YYSYMBOL_CSRWR = 41,                     /* CSRWR  */
  YYSYMBOL_ENDL = 42,                      /* ENDL  */
  YYSYMBOL_43_ = 43,                       /* '+'  */
  YYSYMBOL_44_ = 44,                       /* '-'  */
  YYSYMBOL_UMINUS = 45,                    /* UMINUS  */
  YYSYMBOL_46_ = 46,                       /* ':'  */
  YYSYMBOL_47_ = 47,                       /* ','  */
  YYSYMBOL_48_ = 48,                       /* '$'  */
  YYSYMBOL_49_ = 49,                       /* '['  */
  YYSYMBOL_50_ = 50,                       /* ']'  */
  YYSYMBOL_51_ = 51,                       /* '('  */
  YYSYMBOL_52_ = 52,                       /* ')'  */
  YYSYMBOL_YYACCEPT = 53,                  /* $accept  */
  YYSYMBOL_program = 54,                   /* program  */
  YYSYMBOL_statements = 55,                /* statements  */
  YYSYMBOL_statement = 56,                 /* statement  */
  YYSYMBOL_label = 57,                     /* label  */
  YYSYMBOL_directive = 58,                 /* directive  */
  YYSYMBOL_instruction = 59,               /* instruction  */
  YYSYMBOL_init_list = 60,                 /* init_list  */
  YYSYMBOL_global_args = 61,               /* global_args  */
  YYSYMBOL_extern_args = 62,               /* extern_args  */
  YYSYMBOL_ival_expr = 63                  /* ival_expr  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
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
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  187

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   298


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
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

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "LITERAL", "SYMBOL",
  "STRING", "GPR", "CSR", "GLOBAL", "EXTERN", "SECTION", "WORD", "SKIP",
  "ASCII", "EQU", "END", "HALT", "INT", "IRET", "CALL", "RET", "JMP",
  "BEQ", "BNE", "BGT", "PUSH", "POP", "XCHG", "ADD", "SUB", "MUL", "DIV",
  "NOT", "AND", "OR", "XOR", "SHL", "SHR", "LD", "ST", "CSRRD", "CSRWR",
  "ENDL", "'+'", "'-'", "UMINUS", "':'", "','", "'$'", "'['", "']'", "'('",
  "')'", "$accept", "program", "statements", "statement", "label",
  "directive", "instruction", "init_list", "global_args", "extern_args",
  "ival_expr", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-123)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
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

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
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

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -123,  -123,  -123,   177,  -123,   178,   179,  -123,  -123,  -123,
    -122
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    37,    38,    39,    40,    41,    42,    51,    45,    47,
     126
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
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

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
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

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
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

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
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


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 3: /* program: statements  */
#line 47 "parser.y"
                   { std::cout << "END\n"; }
#line 1254 "parser.cpp"
    break;

  case 12: /* label: SYMBOL ':'  */
#line 65 "parser.y"
                   { as->label((yyvsp[-1].sval)); }
#line 1260 "parser.cpp"
    break;

  case 15: /* directive: SECTION SYMBOL  */
#line 71 "parser.y"
                                                { as->sectionDirective((yyvsp[0].sval)); }
#line 1266 "parser.cpp"
    break;

  case 17: /* directive: SKIP LITERAL  */
#line 73 "parser.y"
                                                { as->skipDirective((yyvsp[0].ival)); }
#line 1272 "parser.cpp"
    break;

  case 18: /* directive: ASCII STRING  */
#line 74 "parser.y"
                                                { std::cout << "ASCII " << "$2" << std::endl; }
#line 1278 "parser.cpp"
    break;

  case 19: /* directive: EQU SYMBOL ',' ival_expr  */
#line 75 "parser.y"
                                                { std::cout << "EQU " << (yyvsp[-2].sval) << "=" << "IVAL" << std::endl; }
#line 1284 "parser.cpp"
    break;

  case 20: /* directive: END  */
#line 76 "parser.y"
                                                { as->end(); }
#line 1290 "parser.cpp"
    break;

  case 21: /* instruction: HALT  */
#line 80 "parser.y"
                                                { MInstruction instr(OPCODE::HALT, 0, 0, 0, 0 ,0); as->insertInstruction(instr); }
#line 1296 "parser.cpp"
    break;

  case 22: /* instruction: INT  */
#line 81 "parser.y"
                                                { MInstruction instr(OPCODE::INT, 0, 0, 0, 0, 0); as->insertInstruction(instr); }
#line 1302 "parser.cpp"
    break;

  case 23: /* instruction: IRET  */
#line 82 "parser.y"
                                                { as->iretInstruction();}
#line 1308 "parser.cpp"
    break;

  case 24: /* instruction: CALL LITERAL  */
#line 83 "parser.y"
                                                { as->callInstruction((yyvsp[0].ival)); }
#line 1314 "parser.cpp"
    break;

  case 25: /* instruction: CALL SYMBOL  */
#line 84 "parser.y"
                                                { as->callInstruction((yyvsp[0].sval)); }
#line 1320 "parser.cpp"
    break;

  case 26: /* instruction: RET  */
#line 85 "parser.y"
                                                { MInstruction instr(OPCODE::LOAD, 3, PC, SP, 0, 4); as->insertInstruction(instr); }
#line 1326 "parser.cpp"
    break;

  case 27: /* instruction: JMP LITERAL  */
#line 86 "parser.y"
                                                { as->jmpInstruction((yyvsp[0].ival)); }
#line 1332 "parser.cpp"
    break;

  case 28: /* instruction: JMP SYMBOL  */
#line 87 "parser.y"
                                                { as->jmpInstruction((yyvsp[0].sval)); }
#line 1338 "parser.cpp"
    break;

  case 29: /* instruction: BEQ GPR ',' GPR ',' LITERAL  */
#line 88 "parser.y"
                                                { as->branch((yyvsp[-4].rval), (yyvsp[-2].rval), (yyvsp[0].ival), 0b0001); }
#line 1344 "parser.cpp"
    break;

  case 30: /* instruction: BEQ GPR ',' GPR ',' SYMBOL  */
#line 89 "parser.y"
                                                { as->branch((yyvsp[-4].rval), (yyvsp[-2].rval), (yyvsp[0].sval), 0b0001); }
#line 1350 "parser.cpp"
    break;

  case 31: /* instruction: BNE GPR ',' GPR ',' LITERAL  */
#line 90 "parser.y"
                                                { as->branch((yyvsp[-4].rval), (yyvsp[-2].rval), (yyvsp[0].ival), 0b0010); }
#line 1356 "parser.cpp"
    break;

  case 32: /* instruction: BNE GPR ',' GPR ',' SYMBOL  */
#line 91 "parser.y"
                                                { as->branch((yyvsp[-4].rval), (yyvsp[-2].rval), (yyvsp[0].sval), 0b0010); }
#line 1362 "parser.cpp"
    break;

  case 33: /* instruction: BGT GPR ',' GPR ',' LITERAL  */
#line 92 "parser.y"
                                                { as->branch((yyvsp[-4].rval), (yyvsp[-2].rval), (yyvsp[0].ival), 0b0011); }
#line 1368 "parser.cpp"
    break;

  case 34: /* instruction: BGT GPR ',' GPR ',' SYMBOL  */
#line 93 "parser.y"
                                                { as->branch((yyvsp[-4].rval), (yyvsp[-2].rval), (yyvsp[0].sval), 0b0011); }
#line 1374 "parser.cpp"
    break;

  case 35: /* instruction: PUSH GPR  */
#line 94 "parser.y"
                                                { MInstruction instr(OPCODE::STORE, 1, SP, 0, (yyvsp[0].rval), -4); as->insertInstruction(instr); }
#line 1380 "parser.cpp"
    break;

  case 36: /* instruction: POP GPR  */
#line 95 "parser.y"
                                                { MInstruction instr(OPCODE::LOAD, 3, (yyvsp[0].rval), 0x0E, 0, 4); as->insertInstruction(instr); }
#line 1386 "parser.cpp"
    break;

  case 37: /* instruction: XCHG GPR ',' GPR  */
#line 96 "parser.y"
                                                { MInstruction instr(OPCODE::XCHG, 0, 0, (yyvsp[0].rval), (yyvsp[-2].rval), 0); as->insertInstruction(instr); }
#line 1392 "parser.cpp"
    break;

  case 38: /* instruction: ADD GPR ',' GPR  */
#line 97 "parser.y"
                                                { MInstruction instr(OPCODE::ARITHMETIC, 0, (yyvsp[0].rval), (yyvsp[0].rval), (yyvsp[-2].rval), 0); as->insertInstruction(instr); }
#line 1398 "parser.cpp"
    break;

  case 39: /* instruction: SUB GPR ',' GPR  */
#line 98 "parser.y"
                                                { MInstruction instr(OPCODE::ARITHMETIC, 1, (yyvsp[0].rval), (yyvsp[0].rval), (yyvsp[-2].rval), 0); as->insertInstruction(instr); }
#line 1404 "parser.cpp"
    break;

  case 40: /* instruction: MUL GPR ',' GPR  */
#line 99 "parser.y"
                                                { MInstruction instr(OPCODE::ARITHMETIC, 2, (yyvsp[0].rval), (yyvsp[0].rval), (yyvsp[-2].rval), 0); as->insertInstruction(instr);  }
#line 1410 "parser.cpp"
    break;

  case 41: /* instruction: DIV GPR ',' GPR  */
#line 100 "parser.y"
                                                { MInstruction instr(OPCODE::ARITHMETIC, 3, (yyvsp[0].rval), (yyvsp[0].rval), (yyvsp[-2].rval), 0); as->insertInstruction(instr); }
#line 1416 "parser.cpp"
    break;

  case 42: /* instruction: NOT GPR  */
#line 101 "parser.y"
                                                { MInstruction instr(OPCODE::LOGIC, 0, (yyvsp[0].rval), (yyvsp[0].rval), 0, 0); as->insertInstruction(instr); }
#line 1422 "parser.cpp"
    break;

  case 43: /* instruction: AND GPR ',' GPR  */
#line 102 "parser.y"
                                                { MInstruction instr(OPCODE::LOGIC, 1, (yyvsp[0].rval), (yyvsp[0].rval), (yyvsp[-2].rval), 0); as->insertInstruction(instr); }
#line 1428 "parser.cpp"
    break;

  case 44: /* instruction: OR GPR ',' GPR  */
#line 103 "parser.y"
                                                { MInstruction instr(OPCODE::LOGIC, 2, (yyvsp[0].rval), (yyvsp[0].rval), (yyvsp[-2].rval), 0); as->insertInstruction(instr); }
#line 1434 "parser.cpp"
    break;

  case 45: /* instruction: XOR GPR ',' GPR  */
#line 104 "parser.y"
                                                { MInstruction instr(OPCODE::LOGIC, 3, (yyvsp[0].rval), (yyvsp[0].rval), (yyvsp[-2].rval), 0); as->insertInstruction(instr); }
#line 1440 "parser.cpp"
    break;

  case 46: /* instruction: SHL GPR ',' GPR  */
#line 105 "parser.y"
                                                { MInstruction instr(OPCODE::SHIFT, 0, (yyvsp[0].rval), (yyvsp[0].rval), (yyvsp[-2].rval), 0); as->insertInstruction(instr); }
#line 1446 "parser.cpp"
    break;

  case 47: /* instruction: SHR GPR ',' GPR  */
#line 106 "parser.y"
                                                { MInstruction instr(OPCODE::SHIFT, 1, (yyvsp[0].rval), (yyvsp[0].rval), (yyvsp[-2].rval), 0); as->insertInstruction(instr); }
#line 1452 "parser.cpp"
    break;

  case 48: /* instruction: LD '$' LITERAL ',' GPR  */
#line 107 "parser.y"
                                                { as->loadLiteral((yyvsp[-2].ival), (yyvsp[0].rval), LiteralMode::VALUE); }
#line 1458 "parser.cpp"
    break;

  case 49: /* instruction: LD '$' SYMBOL ',' GPR  */
#line 108 "parser.y"
                                                { as->loadSymbol((yyvsp[-2].sval), (yyvsp[0].rval), SymbolMode::VALUE); }
#line 1464 "parser.cpp"
    break;

  case 50: /* instruction: LD LITERAL ',' GPR  */
#line 109 "parser.y"
                                                { as->loadLiteral((yyvsp[-2].ival), (yyvsp[0].rval), LiteralMode::MEMORY); }
#line 1470 "parser.cpp"
    break;

  case 51: /* instruction: LD SYMBOL ',' GPR  */
#line 110 "parser.y"
                                                { as->loadSymbol((yyvsp[-2].sval), (yyvsp[0].rval), SymbolMode::MEMORY); }
#line 1476 "parser.cpp"
    break;

  case 52: /* instruction: LD GPR ',' GPR  */
#line 111 "parser.y"
                                                { as->loadReg((yyvsp[-2].rval), (yyvsp[0].rval), RegMode::REG_DIR); }
#line 1482 "parser.cpp"
    break;

  case 53: /* instruction: LD '[' GPR ']' ',' GPR  */
#line 112 "parser.y"
                                                { as->loadReg((yyvsp[-3].rval), (yyvsp[0].rval), RegMode::REG_IND); }
#line 1488 "parser.cpp"
    break;

  case 54: /* instruction: LD '[' GPR '+' LITERAL ']' ',' GPR  */
#line 113 "parser.y"
                                                { as->loadRegLiteral((yyvsp[-5].rval), (yyvsp[-3].ival), (yyvsp[0].rval)); }
#line 1494 "parser.cpp"
    break;

  case 55: /* instruction: LD '[' GPR '+' SYMBOL ']' ',' GPR  */
#line 114 "parser.y"
                                                { std::cout << "LD " << (yyvsp[-5].rval) << "+" << (yyvsp[-3].sval) << (yyvsp[0].rval) << std::endl; }
#line 1500 "parser.cpp"
    break;

  case 56: /* instruction: ST GPR ',' LITERAL  */
#line 115 "parser.y"
                                                { as->storeLiteral((yyvsp[-2].rval), (yyvsp[0].ival)); }
#line 1506 "parser.cpp"
    break;

  case 57: /* instruction: ST GPR ',' SYMBOL  */
#line 116 "parser.y"
                                                { as->storeSymbol((yyvsp[-2].rval), (yyvsp[0].sval)); }
#line 1512 "parser.cpp"
    break;

  case 58: /* instruction: ST GPR ',' '[' GPR ']'  */
#line 117 "parser.y"
                                                { as->storeReg((yyvsp[-4].rval), (yyvsp[-1].rval)); }
#line 1518 "parser.cpp"
    break;

  case 59: /* instruction: ST GPR ',' '[' GPR '+' LITERAL ']'  */
#line 118 "parser.y"
                                                { as->storeRegLiteral((yyvsp[-6].rval), (yyvsp[-3].rval), (yyvsp[-1].ival)); }
#line 1524 "parser.cpp"
    break;

  case 60: /* instruction: ST GPR ',' '[' GPR '+' SYMBOL ']'  */
#line 119 "parser.y"
                                                { std::cout << "ST " << (yyvsp[-6].rval) << " " << (yyvsp[-3].rval) << "+" << (yyvsp[-1].sval) << std::endl; }
#line 1530 "parser.cpp"
    break;

  case 61: /* instruction: CSRRD CSR ',' GPR  */
#line 120 "parser.y"
                                                { MInstruction instr(OPCODE::LOAD, 0, (yyvsp[0].rval), (yyvsp[-2].rval), 0, 0); as->insertInstruction(instr); }
#line 1536 "parser.cpp"
    break;

  case 62: /* instruction: CSRWR GPR ',' CSR  */
#line 121 "parser.y"
                                                { MInstruction instr(OPCODE::LOAD, 4, (yyvsp[0].rval), (yyvsp[-2].rval), 0, 0); as->insertInstruction(instr); }
#line 1542 "parser.cpp"
    break;

  case 63: /* init_list: SYMBOL  */
#line 125 "parser.y"
                                                { as->wordDirectiveSymbol((yyvsp[0].sval)); }
#line 1548 "parser.cpp"
    break;

  case 64: /* init_list: LITERAL  */
#line 126 "parser.y"
                                                { as->wordDirectiveLiteral((yyvsp[0].ival)); }
#line 1554 "parser.cpp"
    break;

  case 65: /* init_list: init_list ',' SYMBOL  */
#line 127 "parser.y"
                                                { as->wordDirectiveSymbol((yyvsp[0].sval)); }
#line 1560 "parser.cpp"
    break;

  case 66: /* init_list: init_list ',' LITERAL  */
#line 128 "parser.y"
                                                { as->wordDirectiveLiteral((yyvsp[0].ival)); }
#line 1566 "parser.cpp"
    break;

  case 67: /* global_args: SYMBOL  */
#line 132 "parser.y"
                                                { as->globalDirective((yyvsp[0].sval)); }
#line 1572 "parser.cpp"
    break;

  case 68: /* global_args: global_args ',' SYMBOL  */
#line 133 "parser.y"
                                                { as->globalDirective((yyvsp[0].sval)); }
#line 1578 "parser.cpp"
    break;

  case 69: /* extern_args: SYMBOL  */
#line 137 "parser.y"
                                                { as->externDirective((yyvsp[0].sval)); }
#line 1584 "parser.cpp"
    break;

  case 70: /* extern_args: extern_args ',' SYMBOL  */
#line 138 "parser.y"
                                                { as->externDirective((yyvsp[0].sval)); }
#line 1590 "parser.cpp"
    break;

  case 71: /* ival_expr: LITERAL  */
#line 142 "parser.y"
                                                { std::cout << "IVAL_EXPR " << (yyvsp[0].ival) << std::endl; }
#line 1596 "parser.cpp"
    break;

  case 72: /* ival_expr: SYMBOL  */
#line 143 "parser.y"
                                                { std::cout << "IVAL_EXPR " << (yyvsp[0].sval) << std::endl; }
#line 1602 "parser.cpp"
    break;

  case 73: /* ival_expr: ival_expr '+' ival_expr  */
#line 144 "parser.y"
                                                { std::cout << "IVAL_EXPR +\n"; }
#line 1608 "parser.cpp"
    break;

  case 74: /* ival_expr: ival_expr '-' ival_expr  */
#line 145 "parser.y"
                                                { std::cout << "IVAL_EXPR -\n"; }
#line 1614 "parser.cpp"
    break;

  case 75: /* ival_expr: '-' ival_expr  */
#line 146 "parser.y"
                                                { std::cout << "UMINUS\n"; }
#line 1620 "parser.cpp"
    break;

  case 76: /* ival_expr: '(' ival_expr ')'  */
#line 147 "parser.y"
                                                { std::cout << "IVAL_EXPR ()\n"; }
#line 1626 "parser.cpp"
    break;


#line 1630 "parser.cpp"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 150 "parser.y"


void yyerror(const char *s) {
    std::cout << "PARSER ERROR!\n"  << "Message: " << s << std::endl;
    exit(-1);
}
