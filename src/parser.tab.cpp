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
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/parser.y"

#include <iostream>
#include <vector>
#include <string>
#include "../include/ast.hpp"

typedef void* yyscan_t;
extern int yylex(union YYSTYPE * yylval_param, struct YYLTYPE * yylloc_param, yyscan_t scanner);
void yyerror(const YYLTYPE* loc, yyscan_t scanner, Program** root, const char *s);

#line 82 "src/parser.tab.cpp"

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

#include "parser.tab.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT_LIT = 3,                    /* INT_LIT  */
  YYSYMBOL_BOOL_LIT = 4,                   /* BOOL_LIT  */
  YYSYMBOL_FLOAT_LIT = 5,                  /* FLOAT_LIT  */
  YYSYMBOL_IMAG_LIT = 6,                   /* IMAG_LIT  */
  YYSYMBOL_STRING_LIT = 7,                 /* STRING_LIT  */
  YYSYMBOL_ID = 8,                         /* ID  */
  YYSYMBOL_TIME_LIT = 9,                   /* TIME_LIT  */
  YYSYMBOL_KW_IMPORT = 10,                 /* KW_IMPORT  */
  YYSYMBOL_KW_CONST = 11,                  /* KW_CONST  */
  YYSYMBOL_KW_VAR = 12,                    /* KW_VAR  */
  YYSYMBOL_KW_LET = 13,                    /* KW_LET  */
  YYSYMBOL_KW_INT = 14,                    /* KW_INT  */
  YYSYMBOL_KW_FLOAT = 15,                  /* KW_FLOAT  */
  YYSYMBOL_KW_ANGLE = 16,                  /* KW_ANGLE  */
  YYSYMBOL_KW_BOOL = 17,                   /* KW_BOOL  */
  YYSYMBOL_KW_STRING = 18,                 /* KW_STRING  */
  YYSYMBOL_KW_COMPLEX = 19,                /* KW_COMPLEX  */
  YYSYMBOL_KW_MATRIX = 20,                 /* KW_MATRIX  */
  YYSYMBOL_KW_QUBIT = 21,                  /* KW_QUBIT  */
  YYSYMBOL_KW_BIT = 22,                    /* KW_BIT  */
  YYSYMBOL_KW_FUNC = 23,                   /* KW_FUNC  */
  YYSYMBOL_KW_CIRCUIT = 24,                /* KW_CIRCUIT  */
  YYSYMBOL_KW_RETURN = 25,                 /* KW_RETURN  */
  YYSYMBOL_KW_ALIAS = 26,                  /* KW_ALIAS  */
  YYSYMBOL_KW_IF = 27,                     /* KW_IF  */
  YYSYMBOL_KW_ELSE = 28,                   /* KW_ELSE  */
  YYSYMBOL_KW_WHILE = 29,                  /* KW_WHILE  */
  YYSYMBOL_KW_FOR = 30,                    /* KW_FOR  */
  YYSYMBOL_KW_FOREACH = 31,                /* KW_FOREACH  */
  YYSYMBOL_KW_IN = 32,                     /* KW_IN  */
  YYSYMBOL_KW_PARALLEL = 33,               /* KW_PARALLEL  */
  YYSYMBOL_KW_STRETCH = 34,                /* KW_STRETCH  */
  YYSYMBOL_KW_BOX = 35,                    /* KW_BOX  */
  YYSYMBOL_KW_DELAY = 36,                  /* KW_DELAY  */
  YYSYMBOL_KW_BARRIER = 37,                /* KW_BARRIER  */
  YYSYMBOL_ARROW = 38,                     /* ARROW  */
  YYSYMBOL_RANGE = 39,                     /* RANGE  */
  YYSYMBOL_DOT = 40,                       /* DOT  */
  YYSYMBOL_COMMA = 41,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 42,                 /* SEMICOLON  */
  YYSYMBOL_COLON = 43,                     /* COLON  */
  YYSYMBOL_AT = 44,                        /* AT  */
  YYSYMBOL_LPAREN = 45,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 46,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 47,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 48,                    /* RBRACE  */
  YYSYMBOL_LBRACKET = 49,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 50,                  /* RBRACKET  */
  YYSYMBOL_LOWER_THAN_ELSE = 51,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_ASSIGN = 52,                    /* ASSIGN  */
  YYSYMBOL_PLUS_ASSIGN = 53,               /* PLUS_ASSIGN  */
  YYSYMBOL_MINUS_ASSIGN = 54,              /* MINUS_ASSIGN  */
  YYSYMBOL_MUL_ASSIGN = 55,                /* MUL_ASSIGN  */
  YYSYMBOL_DIV_ASSIGN = 56,                /* DIV_ASSIGN  */
  YYSYMBOL_OR = 57,                        /* OR  */
  YYSYMBOL_AND = 58,                       /* AND  */
  YYSYMBOL_BIT_OR = 59,                    /* BIT_OR  */
  YYSYMBOL_BIT_XOR = 60,                   /* BIT_XOR  */
  YYSYMBOL_BIT_AND = 61,                   /* BIT_AND  */
  YYSYMBOL_EQ = 62,                        /* EQ  */
  YYSYMBOL_NEQ = 63,                       /* NEQ  */
  YYSYMBOL_LT = 64,                        /* LT  */
  YYSYMBOL_GT = 65,                        /* GT  */
  YYSYMBOL_LTE = 66,                       /* LTE  */
  YYSYMBOL_GTE = 67,                       /* GTE  */
  YYSYMBOL_LSHIFT = 68,                    /* LSHIFT  */
  YYSYMBOL_RSHIFT = 69,                    /* RSHIFT  */
  YYSYMBOL_PLUS = 70,                      /* PLUS  */
  YYSYMBOL_MINUS = 71,                     /* MINUS  */
  YYSYMBOL_STAR = 72,                      /* STAR  */
  YYSYMBOL_SLASH = 73,                     /* SLASH  */
  YYSYMBOL_PERCENT = 74,                   /* PERCENT  */
  YYSYMBOL_POWER = 75,                     /* POWER  */
  YYSYMBOL_NOT = 76,                       /* NOT  */
  YYSYMBOL_BIT_NOT = 77,                   /* BIT_NOT  */
  YYSYMBOL_UMINUS = 78,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 79,                  /* $accept  */
  YYSYMBOL_program = 80,                   /* program  */
  YYSYMBOL_declaration = 81,               /* declaration  */
  YYSYMBOL_import_path = 82,               /* import_path  */
  YYSYMBOL_block = 83,                     /* block  */
  YYSYMBOL_stmt_list = 84,                 /* stmt_list  */
  YYSYMBOL_statement = 85,                 /* statement  */
  YYSYMBOL_var_decl = 86,                  /* var_decl  */
  YYSYMBOL_primitive_type = 87,            /* primitive_type  */
  YYSYMBOL_param = 88,                     /* param  */
  YYSYMBOL_param_list = 89,                /* param_list  */
  YYSYMBOL_func_decl = 90,                 /* func_decl  */
  YYSYMBOL_circuit_decl = 91,              /* circuit_decl  */
  YYSYMBOL_expression = 92,                /* expression  */
  YYSYMBOL_assignment = 93,                /* assignment  */
  YYSYMBOL_range_expr = 94,                /* range_expr  */
  YYSYMBOL_logical_or = 95,                /* logical_or  */
  YYSYMBOL_logical_and = 96,               /* logical_and  */
  YYSYMBOL_bitwise = 97,                   /* bitwise  */
  YYSYMBOL_equality = 98,                  /* equality  */
  YYSYMBOL_relational = 99,                /* relational  */
  YYSYMBOL_shift_expr = 100,               /* shift_expr  */
  YYSYMBOL_additive = 101,                 /* additive  */
  YYSYMBOL_multiplicative = 102,           /* multiplicative  */
  YYSYMBOL_unary = 103,                    /* unary  */
  YYSYMBOL_postfix = 104,                  /* postfix  */
  YYSYMBOL_primary = 105,                  /* primary  */
  YYSYMBOL_elements = 106,                 /* elements  */
  YYSYMBOL_argument_list = 107             /* argument_list  */
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
typedef yytype_int16 yy_state_t;

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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   471

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  79
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  123
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  289

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   333


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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    87,    87,    88,    92,    93,    94,    95,   102,   103,
     110,   113,   123,   127,   134,   135,   136,   139,   142,   145,
     149,   152,   156,   159,   162,   166,   169,   172,   175,   179,
     182,   189,   193,   197,   203,   207,   211,   217,   221,   227,
     231,   237,   241,   247,   251,   257,   262,   267,   272,   277,
     281,   287,   291,   297,   304,   305,   306,   307,   308,   309,
     314,   319,   327,   330,   335,   343,   351,   358,   361,   364,
     367,   370,   374,   377,   381,   384,   388,   391,   395,   398,
     401,   404,   408,   411,   414,   418,   421,   424,   427,   430,
     434,   437,   440,   444,   447,   450,   454,   457,   460,   463,
     466,   470,   473,   476,   480,   481,   485,   489,   494,   508,
     520,   521,   522,   523,   524,   525,   526,   527,   528,   533,
     540,   541,   545,   549
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
  "\"end of file\"", "error", "\"invalid token\"", "INT_LIT", "BOOL_LIT",
  "FLOAT_LIT", "IMAG_LIT", "STRING_LIT", "ID", "TIME_LIT", "KW_IMPORT",
  "KW_CONST", "KW_VAR", "KW_LET", "KW_INT", "KW_FLOAT", "KW_ANGLE",
  "KW_BOOL", "KW_STRING", "KW_COMPLEX", "KW_MATRIX", "KW_QUBIT", "KW_BIT",
  "KW_FUNC", "KW_CIRCUIT", "KW_RETURN", "KW_ALIAS", "KW_IF", "KW_ELSE",
  "KW_WHILE", "KW_FOR", "KW_FOREACH", "KW_IN", "KW_PARALLEL", "KW_STRETCH",
  "KW_BOX", "KW_DELAY", "KW_BARRIER", "ARROW", "RANGE", "DOT", "COMMA",
  "SEMICOLON", "COLON", "AT", "LPAREN", "RPAREN", "LBRACE", "RBRACE",
  "LBRACKET", "RBRACKET", "LOWER_THAN_ELSE", "ASSIGN", "PLUS_ASSIGN",
  "MINUS_ASSIGN", "MUL_ASSIGN", "DIV_ASSIGN", "OR", "AND", "BIT_OR",
  "BIT_XOR", "BIT_AND", "EQ", "NEQ", "LT", "GT", "LTE", "GTE", "LSHIFT",
  "RSHIFT", "PLUS", "MINUS", "STAR", "SLASH", "PERCENT", "POWER", "NOT",
  "BIT_NOT", "UMINUS", "$accept", "program", "declaration", "import_path",
  "block", "stmt_list", "statement", "var_decl", "primitive_type", "param",
  "param_list", "func_decl", "circuit_decl", "expression", "assignment",
  "range_expr", "logical_or", "logical_and", "bitwise", "equality",
  "relational", "shift_expr", "additive", "multiplicative", "unary",
  "postfix", "primary", "elements", "argument_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-36)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -36,   138,   -36,   -36,   -36,   -36,   -36,   -36,   -36,   -36,
      25,    31,    42,    54,   125,   127,   129,   143,   158,   164,
     174,   178,   217,   218,    16,   219,   185,   186,   224,   225,
      58,   395,   192,   -36,   395,   238,   395,   395,   395,   -36,
     -36,   -36,   -36,   -36,   -36,   193,   -36,   -36,   -29,   179,
     151,    64,   112,   139,   130,   124,   -36,   -11,   -36,   -36,
     173,   -35,   -16,     8,    37,    41,    55,   121,   132,   184,
     190,   199,   206,   216,   -36,   395,   220,   -15,   395,   395,
     234,   240,    -3,   238,   -36,   226,   -36,   227,   -36,   286,
     -36,   193,     3,   -36,   228,   235,   -36,   -31,   -36,   -36,
     395,   395,   395,   395,   395,   395,   395,   395,   395,   395,
     395,   395,   395,   395,   395,   395,   395,   395,   395,   395,
     269,   381,   395,   395,   395,   395,   273,   -36,   -36,   395,
     -36,   395,   395,   395,   395,   395,   395,   395,   395,   395,
     395,   395,   395,   395,   395,   395,   395,   274,   274,   -36,
     -36,   395,   242,   250,   395,   395,   253,   264,   272,   395,
     -36,   -36,   -36,   395,   -36,   -36,   263,   179,   151,    64,
      64,    64,   112,   112,   139,   139,   139,   139,   130,   130,
     124,   124,   -36,   -36,   -36,   -36,   239,   -36,    18,   271,
     -36,   -36,   -36,   -36,   282,   283,   276,   285,   279,   288,
     294,   290,   297,   316,   318,   324,   319,   330,   331,   325,
     327,   293,   -36,    83,    84,   332,   333,   333,   333,   333,
     333,   333,   333,   336,   -36,   388,   -36,   -36,   -36,   -36,
     -12,   -36,    -7,   -36,   340,   -36,   364,   -36,   365,   -36,
     366,   -36,   -36,   367,   369,    32,   274,   333,   333,   -36,
     384,   -36,   -36,   -36,   -36,   -36,   -36,   -36,   -36,    93,
     -36,   395,   -36,   395,   -36,   -36,   -36,   -36,   -36,   -36,
     -36,   -36,   -36,   -36,   -36,   -36,   368,   -36,   -36,   -36,
     334,   -36,   371,   372,   370,   -36,   -36,   -36,   -36
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,   110,   112,   111,   114,   113,   116,   115,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    17,     0,     0,   120,     0,     0,     3,
      14,     6,    15,     4,     5,     0,    67,    71,    73,    75,
      77,    81,    84,    89,    92,    95,   100,   103,   104,     8,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    19,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    25,     0,    30,     0,    10,     0,
      12,   122,     0,   122,     0,   121,   102,   103,   101,    16,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     7,    48,     0,
      46,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    62,    62,    18,
      50,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     117,    11,    13,     0,   119,   118,    72,    74,    76,    78,
      79,    80,    82,    83,    85,    86,    87,    88,    90,    91,
      93,    94,    96,    97,    98,    99,     0,   109,     0,     0,
      68,    69,    70,     9,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    63,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   123,     0,   108,   107,    47,    45,
       0,    31,     0,    34,     0,    43,     0,    39,     0,    41,
       0,    37,    53,     0,     0,     0,     0,     0,     0,    49,
      20,    22,    23,    24,    26,    27,    28,    29,   106,     0,
      33,     0,    36,     0,    44,    40,    42,    38,    51,    52,
      54,    55,    56,    57,    58,    59,    60,    64,    65,    66,
       0,   105,     0,     0,     0,    21,    32,    35,    61
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -36,   -36,   -36,   -36,   -28,   -36,    -1,   -36,   -36,   169,
     268,   -36,   -36,   -23,   -36,   -36,   321,   317,   320,   113,
     115,    95,   111,   114,   -22,   -34,   -36,   -36,   -30
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,    39,    60,    40,    89,    90,    42,   276,   212,
     213,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    94,    92
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      41,    76,    84,    97,    97,   156,    95,   128,    85,   120,
     100,    87,    91,    93,   121,    96,    98,   129,   122,     3,
       4,     5,     6,     7,     8,     9,   130,   150,   101,   120,
     260,   157,   158,    59,   121,   262,   131,   151,   122,    61,
     261,   123,   124,   125,   163,   263,   270,   271,   272,   273,
      62,   164,    93,   274,   275,   152,   153,   132,    74,   163,
     133,    34,    63,    75,   226,    36,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,   134,    37,   162,   135,
     136,   188,    38,   137,   182,   183,   184,   185,    93,   189,
     190,   191,   192,    82,   138,    83,   194,   139,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   246,   246,   106,   107,   215,   247,
     248,   218,   219,    64,   163,    65,   223,    66,     2,   281,
     224,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    67,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    68,    27,    28,    29,
     140,    30,    69,   141,    31,    32,   108,   109,   110,   111,
      33,   142,    70,    34,   143,    35,    71,    36,   250,   251,
     252,   253,   254,   255,   256,   259,   116,   117,   118,   119,
     114,   115,    93,   174,   175,   176,   177,   112,   113,    37,
     103,   104,   105,   126,    38,   127,   169,   170,   171,   278,
     279,   172,   173,   178,   179,    72,    73,    77,   180,   181,
      78,    79,    80,    81,    86,    99,   144,   102,   282,   145,
     283,     3,     4,     5,     6,     7,     8,     9,   146,    11,
      12,   147,    13,    14,    15,    16,    17,    18,    19,    20,
      21,   148,   149,    24,    25,    26,   154,    27,    28,    29,
     159,    30,   155,   160,    31,    32,   163,   186,   165,   285,
      33,   193,   211,    34,   225,    35,    88,    36,   216,     3,
       4,     5,     6,     7,     8,     9,   217,    11,    12,   220,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    37,
     221,    24,    25,    26,    38,    27,    28,    29,   222,    30,
     101,   227,    31,    32,   228,   229,   230,   231,    33,   232,
     233,    34,   235,    35,   161,    36,   245,     3,     4,     5,
       6,     7,     8,     9,   234,    11,    12,   236,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    37,   237,    24,
      25,    26,    38,    27,    28,    29,   239,    30,   238,   240,
      31,    32,   241,   242,   249,   243,    33,   244,   257,    34,
      83,    35,   264,    36,     3,     4,     5,     6,     7,     8,
       9,     3,     4,     5,     6,     7,     8,     9,     3,     4,
       5,     6,     7,     8,     9,    37,   265,   266,   267,   268,
      38,   269,   280,   286,   287,   277,   214,   284,   167,     0,
     288,   166,   168,     0,     0,     0,    34,   187,    75,     0,
      36,     0,     0,    34,   258,    75,     0,    36,     0,     0,
      34,     0,    75,     0,    36,     0,     0,     0,     0,     0,
       0,     0,    37,     0,     0,     0,     0,    38,     0,    37,
       0,     0,     0,     0,    38,     0,    37,     0,     0,     0,
       0,    38
};

static const yytype_int16 yycheck[] =
{
       1,    24,    30,    37,    38,     8,    36,    42,    31,    40,
      39,    34,    35,    36,    45,    37,    38,    52,    49,     3,
       4,     5,     6,     7,     8,     9,    42,    42,    57,    40,
      42,    34,    35,     8,    45,    42,    52,    52,    49,     8,
      52,    52,    53,    54,    41,    52,    14,    15,    16,    17,
       8,    48,    75,    21,    22,    78,    79,    49,    42,    41,
      52,    45,     8,    47,    46,    49,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,    49,    71,    89,    52,
      49,   121,    76,    52,   116,   117,   118,   119,   121,   122,
     123,   124,   125,    45,    49,    47,   129,    52,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,    41,    41,    62,    63,   151,    46,
      46,   154,   155,     8,    41,     8,   159,     8,     0,    46,
     163,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,     8,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,     8,    29,    30,    31,
      49,    33,     8,    52,    36,    37,    64,    65,    66,    67,
      42,    49,     8,    45,    52,    47,     8,    49,   216,   217,
     218,   219,   220,   221,   222,   225,    72,    73,    74,    75,
      70,    71,   225,   108,   109,   110,   111,    68,    69,    71,
      59,    60,    61,    40,    76,    42,   103,   104,   105,   247,
     248,   106,   107,   112,   113,     8,     8,     8,   114,   115,
      45,    45,     8,     8,    42,    42,    52,    58,   261,    49,
     263,     3,     4,     5,     6,     7,     8,     9,    49,    11,
      12,    45,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    45,    42,    25,    26,    27,    32,    29,    30,    31,
      44,    33,    32,    46,    36,    37,    41,     8,    50,   280,
      42,     8,     8,    45,    45,    47,    48,    49,    46,     3,
       4,     5,     6,     7,     8,     9,    46,    11,    12,    46,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    71,
      46,    25,    26,    27,    76,    29,    30,    31,    46,    33,
      57,    50,    36,    37,    42,    42,    50,    42,    42,    50,
      42,    45,    42,    47,    48,    49,    43,     3,     4,     5,
       6,     7,     8,     9,    50,    11,    12,    50,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    71,    42,    25,
      26,    27,    76,    29,    30,    31,    42,    33,    50,    50,
      36,    37,    42,    42,    42,    50,    42,    50,    42,    45,
      47,    47,    42,    49,     3,     4,     5,     6,     7,     8,
       9,     3,     4,     5,     6,     7,     8,     9,     3,     4,
       5,     6,     7,     8,     9,    71,    42,    42,    42,    42,
      76,    42,    28,    42,    42,   246,   148,    49,   101,    -1,
      50,   100,   102,    -1,    -1,    -1,    45,    46,    47,    -1,
      49,    -1,    -1,    45,    46,    47,    -1,    49,    -1,    -1,
      45,    -1,    47,    -1,    49,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    71,    -1,    -1,    -1,    -1,    76,    -1,    71,
      -1,    -1,    -1,    -1,    76,    -1,    71,    -1,    -1,    -1,
      -1,    76
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    80,     0,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    29,    30,    31,
      33,    36,    37,    42,    45,    47,    49,    71,    76,    81,
      83,    85,    86,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,     8,
      82,     8,     8,     8,     8,     8,     8,     8,     8,     8,
       8,     8,     8,     8,    42,    47,    92,     8,    45,    45,
       8,     8,    45,    47,    83,    92,    42,    92,    48,    84,
      85,    92,   107,    92,   106,   107,   103,   104,   103,    42,
      39,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      40,    45,    49,    52,    53,    54,    40,    42,    42,    52,
      42,    52,    49,    52,    49,    52,    49,    52,    49,    52,
      49,    52,    49,    52,    52,    49,    49,    45,    45,    42,
      42,    52,    92,    92,    32,    32,     8,    34,    35,    44,
      46,    48,    85,    41,    48,    50,    95,    96,    97,    98,
      98,    98,    99,    99,   100,   100,   100,   100,   101,   101,
     102,   102,   103,   103,   103,   103,     8,    46,   107,    92,
      92,    92,    92,     8,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,     8,    88,    89,    89,    92,    46,    46,    92,    92,
      46,    46,    46,    92,    92,    45,    46,    50,    42,    42,
      50,    42,    50,    42,    50,    42,    50,    42,    50,    42,
      50,    42,    42,    50,    50,    43,    41,    46,    46,    42,
      83,    83,    83,    83,    83,    83,    83,    42,    46,   107,
      42,    52,    42,    52,    42,    42,    42,    42,    42,    42,
      14,    15,    16,    17,    21,    22,    87,    88,    83,    83,
      28,    46,    92,    92,    49,    85,    42,    42,    50
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    79,    80,    80,    81,    81,    81,    81,    82,    82,
      83,    83,    84,    84,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    87,    87,    87,    87,    87,    87,
      88,    88,    89,    89,    89,    90,    91,    92,    93,    93,
      93,    93,    94,    94,    95,    95,    96,    96,    97,    97,
      97,    97,    98,    98,    98,    99,    99,    99,    99,    99,
     100,   100,   100,   101,   101,   101,   102,   102,   102,   102,
     102,   103,   103,   103,   104,   104,   104,   104,   104,   104,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     106,   106,   107,   107
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     3,     1,     3,
       2,     3,     1,     2,     1,     1,     2,     1,     3,     2,
       5,     7,     5,     5,     5,     2,     5,     5,     5,     5,
       2,     5,     8,     6,     5,     8,     6,     5,     6,     5,
       6,     5,     6,     5,     6,     5,     3,     5,     3,     5,
       3,     6,     6,     5,     1,     1,     1,     1,     1,     1,
       3,     5,     0,     1,     3,     6,     6,     1,     3,     3,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     3,
       1,     2,     2,     1,     1,     6,     5,     4,     4,     3,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       0,     1,     1,     3
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
        yyerror (&yylloc, scanner, root, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

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

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
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

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, scanner, root); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, yyscan_t scanner, Program** root)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (scanner);
  YY_USE (root);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, yyscan_t scanner, Program** root)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, scanner, root);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, yyscan_t scanner, Program** root)
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
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), scanner, root);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, scanner, root); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, yyscan_t scanner, Program** root)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (scanner);
  YY_USE (root);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (yyscan_t scanner, Program** root)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

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

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yychar = yylex (&yylval, &yylloc, scanner);
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
      yyerror_range[1] = yylloc;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: %empty  */
#line 87 "src/parser.y"
                { *root = new Program(); }
#line 1532 "src/parser.tab.cpp"
    break;

  case 3: /* program: program declaration  */
#line 88 "src/parser.y"
                          { (*root)->add((yyvsp[0].node)); }
#line 1538 "src/parser.tab.cpp"
    break;

  case 4: /* declaration: func_decl  */
#line 92 "src/parser.y"
              { (yyval.node) = (yyvsp[0].stmt); }
#line 1544 "src/parser.tab.cpp"
    break;

  case 5: /* declaration: circuit_decl  */
#line 93 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].stmt); }
#line 1550 "src/parser.tab.cpp"
    break;

  case 6: /* declaration: statement  */
#line 94 "src/parser.y"
                { (yyval.node) = (yyvsp[0].stmt); }
#line 1556 "src/parser.tab.cpp"
    break;

  case 7: /* declaration: KW_IMPORT import_path SEMICOLON  */
#line 95 "src/parser.y"
                                      { 
        Expression* s = new StringLiteral(*(yyvsp[-1].sval)); s->loc((yylsp[-1]).first_line, (yylsp[-1]).first_column);
        (yyval.node) = (new ExprStmt(s))->loc((yylsp[-2]).first_line, (yylsp[-2]).first_column);
    }
#line 1565 "src/parser.tab.cpp"
    break;

  case 8: /* import_path: ID  */
#line 102 "src/parser.y"
       { (yyval.sval) = (yyvsp[0].sval); }
#line 1571 "src/parser.tab.cpp"
    break;

  case 9: /* import_path: import_path DOT ID  */
#line 103 "src/parser.y"
                         { 
        (yyval.sval) = new std::string(*(yyvsp[-2].sval) + "." + *(yyvsp[0].sval));
        delete (yyvsp[-2].sval); delete (yyvsp[0].sval); 
    }
#line 1580 "src/parser.tab.cpp"
    break;

  case 10: /* block: LBRACE RBRACE  */
#line 110 "src/parser.y"
                  { 
        (yyval.block) = (Block*)(new Block())->loc((yylsp[-1]).first_line, (yylsp[-1]).first_column); 
    }
#line 1588 "src/parser.tab.cpp"
    break;

  case 11: /* block: LBRACE stmt_list RBRACE  */
#line 113 "src/parser.y"
                              {
        Block* b = new Block();
        b->statements = *(yyvsp[-1].stmt_list);
        b->loc((yylsp[-2]).first_line, (yylsp[-2]).first_column);
        delete (yyvsp[-1].stmt_list);
        (yyval.block) = b;
    }
#line 1600 "src/parser.tab.cpp"
    break;

  case 12: /* stmt_list: statement  */
#line 123 "src/parser.y"
              { 
        (yyval.stmt_list) = new std::vector<Statement*>();
        (yyval.stmt_list)->push_back((yyvsp[0].stmt)); 
    }
#line 1609 "src/parser.tab.cpp"
    break;

  case 13: /* stmt_list: stmt_list statement  */
#line 127 "src/parser.y"
                          {
        (yyvsp[-1].stmt_list)->push_back((yyvsp[0].stmt));
        (yyval.stmt_list) = (yyvsp[-1].stmt_list);
    }
#line 1618 "src/parser.tab.cpp"
    break;

  case 14: /* statement: block  */
#line 134 "src/parser.y"
          { (yyval.stmt) = (yyvsp[0].block); }
#line 1624 "src/parser.tab.cpp"
    break;

  case 15: /* statement: var_decl  */
#line 135 "src/parser.y"
               { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1630 "src/parser.tab.cpp"
    break;

  case 16: /* statement: expression SEMICOLON  */
#line 136 "src/parser.y"
                           { 
        (yyval.stmt) = (Statement*)(new ExprStmt((yyvsp[-1].expr)))->loc((yylsp[-1]).first_line, (yylsp[-1]).first_column); 
    }
#line 1638 "src/parser.tab.cpp"
    break;

  case 17: /* statement: SEMICOLON  */
#line 139 "src/parser.y"
                { 
        (yyval.stmt) = (Statement*)(new Block())->loc((yylsp[0]).first_line, (yylsp[0]).first_column); 
    }
#line 1646 "src/parser.tab.cpp"
    break;

  case 18: /* statement: KW_RETURN expression SEMICOLON  */
#line 142 "src/parser.y"
                                     { 
        (yyval.stmt) = (Statement*)(new ReturnStmt((yyvsp[-1].expr)))->loc((yylsp[-2]).first_line, (yylsp[-2]).first_column); 
    }
#line 1654 "src/parser.tab.cpp"
    break;

  case 19: /* statement: KW_RETURN SEMICOLON  */
#line 145 "src/parser.y"
                          { 
        (yyval.stmt) = (Statement*)(new ReturnStmt(nullptr))->loc((yylsp[-1]).first_line, (yylsp[-1]).first_column); 
    }
#line 1662 "src/parser.tab.cpp"
    break;

  case 20: /* statement: KW_IF LPAREN expression RPAREN block  */
#line 149 "src/parser.y"
                                                                 { 
        (yyval.stmt) = (Statement*)(new IfStmt((yyvsp[-2].expr), (yyvsp[0].block)))->loc((yylsp[-4]).first_line, (yylsp[-4]).first_column); 
    }
#line 1670 "src/parser.tab.cpp"
    break;

  case 21: /* statement: KW_IF LPAREN expression RPAREN block KW_ELSE statement  */
#line 152 "src/parser.y"
                                                             { 
        (yyval.stmt) = (Statement*)(new IfStmt((yyvsp[-4].expr), (yyvsp[-2].block), (yyvsp[0].stmt)))->loc((yylsp[-6]).first_line, (yylsp[-6]).first_column); 
    }
#line 1678 "src/parser.tab.cpp"
    break;

  case 22: /* statement: KW_WHILE LPAREN expression RPAREN block  */
#line 156 "src/parser.y"
                                              {
        (yyval.stmt) = (Statement*)(new WhileStmt((yyvsp[-2].expr), (yyvsp[0].block)))->loc((yylsp[-4]).first_line, (yylsp[-4]).first_column);
    }
#line 1686 "src/parser.tab.cpp"
    break;

  case 23: /* statement: KW_FOR ID KW_IN expression block  */
#line 159 "src/parser.y"
                                       {
        (yyval.stmt) = (Statement*)(new ForStmt(*(yyvsp[-3].sval), (yyvsp[-1].expr), (yyvsp[0].block)))->loc((yylsp[-4]).first_line, (yylsp[-4]).first_column);
    }
#line 1694 "src/parser.tab.cpp"
    break;

  case 24: /* statement: KW_FOREACH ID KW_IN expression block  */
#line 162 "src/parser.y"
                                           {
        (yyval.stmt) = (Statement*)(new ForStmt(*(yyvsp[-3].sval), (yyvsp[-1].expr), (yyvsp[0].block)))->loc((yylsp[-4]).first_line, (yylsp[-4]).first_column);
    }
#line 1702 "src/parser.tab.cpp"
    break;

  case 25: /* statement: KW_PARALLEL block  */
#line 166 "src/parser.y"
                        {
        (yyval.stmt) = (Statement*)(new ParallelStmt("default", (yyvsp[0].block)))->loc((yylsp[-1]).first_line, (yylsp[-1]).first_column);
    }
#line 1710 "src/parser.tab.cpp"
    break;

  case 26: /* statement: KW_PARALLEL LPAREN ID RPAREN block  */
#line 169 "src/parser.y"
                                         {
        (yyval.stmt) = (Statement*)(new ParallelStmt(*(yyvsp[-2].sval), (yyvsp[0].block)))->loc((yylsp[-4]).first_line, (yylsp[-4]).first_column);
    }
#line 1718 "src/parser.tab.cpp"
    break;

  case 27: /* statement: KW_PARALLEL LPAREN KW_STRETCH RPAREN block  */
#line 172 "src/parser.y"
                                                 {
        (yyval.stmt) = (Statement*)(new ParallelStmt("stretch", (yyvsp[0].block)))->loc((yylsp[-4]).first_line, (yylsp[-4]).first_column);
    }
#line 1726 "src/parser.tab.cpp"
    break;

  case 28: /* statement: KW_PARALLEL LPAREN KW_BOX RPAREN block  */
#line 175 "src/parser.y"
                                             {
        (yyval.stmt) = (Statement*)(new ParallelStmt("box", (yyvsp[0].block)))->loc((yylsp[-4]).first_line, (yylsp[-4]).first_column);
    }
#line 1734 "src/parser.tab.cpp"
    break;

  case 29: /* statement: KW_DELAY expression AT expression SEMICOLON  */
#line 179 "src/parser.y"
                                                  {
        (yyval.stmt) = (Statement*)(new DelayStmt((yyvsp[-3].expr), (yyvsp[-1].expr)))->loc((yylsp[-4]).first_line, (yylsp[-4]).first_column);
    }
#line 1742 "src/parser.tab.cpp"
    break;

  case 30: /* statement: KW_BARRIER SEMICOLON  */
#line 182 "src/parser.y"
                           {
        (yyval.stmt) = (Statement*)(new BarrierStmt({}))->loc((yylsp[-1]).first_line, (yylsp[-1]).first_column);
    }
#line 1750 "src/parser.tab.cpp"
    break;

  case 31: /* var_decl: KW_INT ID ASSIGN expression SEMICOLON  */
#line 189 "src/parser.y"
                                          {
        TypeSpecifier t = { DataType::INT, false, {} };
        (yyval.stmt) = (Statement*)(new VarDecl(*(yyvsp[-3].sval), t, (yyvsp[-1].expr)))->loc((yylsp[-4]).first_line, (yylsp[-4]).first_column);
    }
#line 1759 "src/parser.tab.cpp"
    break;

  case 32: /* var_decl: KW_INT ID LBRACKET expression RBRACKET ASSIGN expression SEMICOLON  */
#line 193 "src/parser.y"
                                                                         {
        TypeSpecifier t = { DataType::INT, true, {} }; 
        (yyval.stmt) = (Statement*)(new VarDecl(*(yyvsp[-6].sval), t, (yyvsp[-1].expr), false, (yyvsp[-4].expr)))->loc((yylsp[-7]).first_line, (yylsp[-7]).first_column);
    }
#line 1768 "src/parser.tab.cpp"
    break;

  case 33: /* var_decl: KW_INT ID LBRACKET expression RBRACKET SEMICOLON  */
#line 197 "src/parser.y"
                                                       {
        TypeSpecifier t = { DataType::INT, true, {} }; 
        (yyval.stmt) = (Statement*)(new VarDecl(*(yyvsp[-4].sval), t, nullptr, false, (yyvsp[-2].expr)))->loc((yylsp[-5]).first_line, (yylsp[-5]).first_column);
    }
#line 1777 "src/parser.tab.cpp"
    break;

  case 34: /* var_decl: KW_FLOAT ID ASSIGN expression SEMICOLON  */
#line 203 "src/parser.y"
                                              {
        TypeSpecifier t = { DataType::FLOAT, false, {} };
        (yyval.stmt) = (Statement*)(new VarDecl(*(yyvsp[-3].sval), t, (yyvsp[-1].expr)))->loc((yylsp[-4]).first_line, (yylsp[-4]).first_column);
    }
#line 1786 "src/parser.tab.cpp"
    break;

  case 35: /* var_decl: KW_FLOAT ID LBRACKET expression RBRACKET ASSIGN expression SEMICOLON  */
#line 207 "src/parser.y"
                                                                           {
        TypeSpecifier t = { DataType::FLOAT, true, {} };
        (yyval.stmt) = (Statement*)(new VarDecl(*(yyvsp[-6].sval), t, (yyvsp[-1].expr), false, (yyvsp[-4].expr)))->loc((yylsp[-7]).first_line, (yylsp[-7]).first_column);
    }
#line 1795 "src/parser.tab.cpp"
    break;

  case 36: /* var_decl: KW_FLOAT ID LBRACKET expression RBRACKET SEMICOLON  */
#line 211 "src/parser.y"
                                                         {
        TypeSpecifier t = { DataType::FLOAT, true, {} };
        (yyval.stmt) = (Statement*)(new VarDecl(*(yyvsp[-4].sval), t, nullptr, false, (yyvsp[-2].expr)))->loc((yylsp[-5]).first_line, (yylsp[-5]).first_column);
    }
#line 1804 "src/parser.tab.cpp"
    break;

  case 37: /* var_decl: KW_COMPLEX ID ASSIGN expression SEMICOLON  */
#line 217 "src/parser.y"
                                                {
        TypeSpecifier t = { DataType::COMPLEX, false, {} };
        (yyval.stmt) = (Statement*)(new VarDecl(*(yyvsp[-3].sval), t, (yyvsp[-1].expr)))->loc((yylsp[-4]).first_line, (yylsp[-4]).first_column);
    }
#line 1813 "src/parser.tab.cpp"
    break;

  case 38: /* var_decl: KW_COMPLEX ID LBRACKET expression RBRACKET SEMICOLON  */
#line 221 "src/parser.y"
                                                           {
        TypeSpecifier t = { DataType::COMPLEX, true, {} };
        (yyval.stmt) = (Statement*)(new VarDecl(*(yyvsp[-4].sval), t, nullptr, false, (yyvsp[-2].expr)))->loc((yylsp[-5]).first_line, (yylsp[-5]).first_column);
    }
#line 1822 "src/parser.tab.cpp"
    break;

  case 39: /* var_decl: KW_BOOL ID ASSIGN expression SEMICOLON  */
#line 227 "src/parser.y"
                                             {
        TypeSpecifier t = { DataType::BOOL, false, {} };
        (yyval.stmt) = (Statement*)(new VarDecl(*(yyvsp[-3].sval), t, (yyvsp[-1].expr)))->loc((yylsp[-4]).first_line, (yylsp[-4]).first_column);
    }
#line 1831 "src/parser.tab.cpp"
    break;

  case 40: /* var_decl: KW_BOOL ID LBRACKET expression RBRACKET SEMICOLON  */
#line 231 "src/parser.y"
                                                        {
        TypeSpecifier t = { DataType::BOOL, true, {} };
        (yyval.stmt) = (Statement*)(new VarDecl(*(yyvsp[-4].sval), t, nullptr, false, (yyvsp[-2].expr)))->loc((yylsp[-5]).first_line, (yylsp[-5]).first_column);
    }
#line 1840 "src/parser.tab.cpp"
    break;

  case 41: /* var_decl: KW_STRING ID ASSIGN expression SEMICOLON  */
#line 237 "src/parser.y"
                                               {
        TypeSpecifier t = { DataType::STRING, false, {} };
        (yyval.stmt) = (Statement*)(new VarDecl(*(yyvsp[-3].sval), t, (yyvsp[-1].expr)))->loc((yylsp[-4]).first_line, (yylsp[-4]).first_column);
    }
#line 1849 "src/parser.tab.cpp"
    break;

  case 42: /* var_decl: KW_STRING ID LBRACKET expression RBRACKET SEMICOLON  */
#line 241 "src/parser.y"
                                                          { 
        TypeSpecifier t = { DataType::STRING, true, {} };
        (yyval.stmt) = (Statement*)(new VarDecl(*(yyvsp[-4].sval), t, nullptr, false, (yyvsp[-2].expr)))->loc((yylsp[-5]).first_line, (yylsp[-5]).first_column);
    }
#line 1858 "src/parser.tab.cpp"
    break;

  case 43: /* var_decl: KW_ANGLE ID ASSIGN expression SEMICOLON  */
#line 247 "src/parser.y"
                                              {
        TypeSpecifier t = { DataType::ANGLE, false, {} };
        (yyval.stmt) = (Statement*)(new VarDecl(*(yyvsp[-3].sval), t, (yyvsp[-1].expr)))->loc((yylsp[-4]).first_line, (yylsp[-4]).first_column);
    }
#line 1867 "src/parser.tab.cpp"
    break;

  case 44: /* var_decl: KW_ANGLE ID LBRACKET expression RBRACKET SEMICOLON  */
#line 251 "src/parser.y"
                                                         {
        TypeSpecifier t = { DataType::ANGLE, true, {} };
        (yyval.stmt) = (Statement*)(new VarDecl(*(yyvsp[-4].sval), t, nullptr, false, (yyvsp[-2].expr)))->loc((yylsp[-5]).first_line, (yylsp[-5]).first_column);
    }
#line 1876 "src/parser.tab.cpp"
    break;

  case 45: /* var_decl: KW_VAR ID ASSIGN expression SEMICOLON  */
#line 257 "src/parser.y"
                                            {
        TypeSpecifier t = { DataType::AUTO, false, {} };
        (yyval.stmt) = (Statement*)(new VarDecl(*(yyvsp[-3].sval), t, (yyvsp[-1].expr)))->loc((yylsp[-4]).first_line, (yylsp[-4]).first_column);
    }
#line 1885 "src/parser.tab.cpp"
    break;

  case 46: /* var_decl: KW_VAR ID SEMICOLON  */
#line 262 "src/parser.y"
                          {
        TypeSpecifier t = { DataType::AUTO, false, {} };
        (yyval.stmt) = (Statement*)(new VarDecl(*(yyvsp[-1].sval), t, nullptr))->loc((yylsp[-2]).first_line, (yylsp[-2]).first_column);
    }
#line 1894 "src/parser.tab.cpp"
    break;

  case 47: /* var_decl: KW_CONST ID ASSIGN expression SEMICOLON  */
#line 267 "src/parser.y"
                                              {
        TypeSpecifier t = { DataType::AUTO, false, {} };
        (yyval.stmt) = (Statement*)(new VarDecl(*(yyvsp[-3].sval), t, (yyvsp[-1].expr), true))->loc((yylsp[-4]).first_line, (yylsp[-4]).first_column);
    }
#line 1903 "src/parser.tab.cpp"
    break;

  case 48: /* var_decl: KW_CONST ID SEMICOLON  */
#line 272 "src/parser.y"
                            {
        TypeSpecifier t = { DataType::AUTO, false, {} };
        (yyval.stmt) = (Statement*)(new VarDecl(*(yyvsp[-1].sval), t, nullptr, true))->loc((yylsp[-2]).first_line, (yylsp[-2]).first_column);
    }
#line 1912 "src/parser.tab.cpp"
    break;

  case 49: /* var_decl: KW_ALIAS ID ASSIGN expression SEMICOLON  */
#line 277 "src/parser.y"
                                              {
        TypeSpecifier t = { DataType::AUTO, false, {} };
        (yyval.stmt) = (Statement*)(new VarDecl(*(yyvsp[-3].sval), t, (yyvsp[-1].expr)))->loc((yylsp[-4]).first_line, (yylsp[-4]).first_column);
    }
#line 1921 "src/parser.tab.cpp"
    break;

  case 50: /* var_decl: KW_ALIAS ID SEMICOLON  */
#line 281 "src/parser.y"
                            {
        TypeSpecifier t = { DataType::AUTO, false, {} };
        (yyval.stmt) = (Statement*)(new VarDecl(*(yyvsp[-1].sval), t, nullptr))->loc((yylsp[-2]).first_line, (yylsp[-2]).first_column);
    }
#line 1930 "src/parser.tab.cpp"
    break;

  case 51: /* var_decl: KW_QUBIT ID LBRACKET expression RBRACKET SEMICOLON  */
#line 287 "src/parser.y"
                                                         {
        TypeSpecifier t = { DataType::QUBIT, true, {1} };
        (yyval.stmt) = (Statement*)(new VarDecl(*(yyvsp[-4].sval), t, nullptr, false, (yyvsp[-2].expr)))->loc((yylsp[-5]).first_line, (yylsp[-5]).first_column);
    }
#line 1939 "src/parser.tab.cpp"
    break;

  case 52: /* var_decl: KW_BIT ID LBRACKET expression RBRACKET SEMICOLON  */
#line 291 "src/parser.y"
                                                       {
        TypeSpecifier t = { DataType::BIT, true, {1} };
        (yyval.stmt) = (Statement*)(new VarDecl(*(yyvsp[-4].sval), t, nullptr, false, (yyvsp[-2].expr)))->loc((yylsp[-5]).first_line, (yylsp[-5]).first_column);
    }
#line 1948 "src/parser.tab.cpp"
    break;

  case 53: /* var_decl: KW_MATRIX ID ASSIGN expression SEMICOLON  */
#line 297 "src/parser.y"
                                               {
        TypeSpecifier t = { DataType::MATRIX, false, {} };
        (yyval.stmt) = (Statement*)(new VarDecl(*(yyvsp[-3].sval), t, (yyvsp[-1].expr)))->loc((yylsp[-4]).first_line, (yylsp[-4]).first_column);
    }
#line 1957 "src/parser.tab.cpp"
    break;

  case 54: /* primitive_type: KW_INT  */
#line 304 "src/parser.y"
               { (yyval.type_enum) = (int)DataType::INT; }
#line 1963 "src/parser.tab.cpp"
    break;

  case 55: /* primitive_type: KW_FLOAT  */
#line 305 "src/parser.y"
               { (yyval.type_enum) = (int)DataType::FLOAT; }
#line 1969 "src/parser.tab.cpp"
    break;

  case 56: /* primitive_type: KW_ANGLE  */
#line 306 "src/parser.y"
               { (yyval.type_enum) = (int)DataType::ANGLE; }
#line 1975 "src/parser.tab.cpp"
    break;

  case 57: /* primitive_type: KW_BOOL  */
#line 307 "src/parser.y"
               { (yyval.type_enum) = (int)DataType::BOOL; }
#line 1981 "src/parser.tab.cpp"
    break;

  case 58: /* primitive_type: KW_QUBIT  */
#line 308 "src/parser.y"
               { (yyval.type_enum) = (int)DataType::QUBIT; }
#line 1987 "src/parser.tab.cpp"
    break;

  case 59: /* primitive_type: KW_BIT  */
#line 309 "src/parser.y"
               { (yyval.type_enum) = (int)DataType::BIT; }
#line 1993 "src/parser.tab.cpp"
    break;

  case 60: /* param: ID COLON primitive_type  */
#line 314 "src/parser.y"
                            {
        TypeSpecifier t = { (DataType)(yyvsp[0].type_enum), false, {} };
        (yyval.parameter) = new Parameter{*(yyvsp[-2].sval), t};
        delete (yyvsp[-2].sval);
    }
#line 2003 "src/parser.tab.cpp"
    break;

  case 61: /* param: ID COLON primitive_type LBRACKET RBRACKET  */
#line 319 "src/parser.y"
                                                {
        TypeSpecifier t = { (DataType)(yyvsp[-2].type_enum), true, {} };
        (yyval.parameter) = new Parameter{*(yyvsp[-4].sval), t};
        delete (yyvsp[-4].sval);
    }
#line 2013 "src/parser.tab.cpp"
    break;

  case 62: /* param_list: %empty  */
#line 327 "src/parser.y"
                { 
        (yyval.param_list) = new std::vector<Parameter>(); 
    }
#line 2021 "src/parser.tab.cpp"
    break;

  case 63: /* param_list: param  */
#line 330 "src/parser.y"
            {
        (yyval.param_list) = new std::vector<Parameter>();
        (yyval.param_list)->push_back(*(yyvsp[0].parameter));
        delete (yyvsp[0].parameter);
    }
#line 2031 "src/parser.tab.cpp"
    break;

  case 64: /* param_list: param_list COMMA param  */
#line 335 "src/parser.y"
                             {
        (yyvsp[-2].param_list)->push_back(*(yyvsp[0].parameter));
        delete (yyvsp[0].parameter);
        (yyval.param_list) = (yyvsp[-2].param_list);
    }
#line 2041 "src/parser.tab.cpp"
    break;

  case 65: /* func_decl: KW_FUNC ID LPAREN param_list RPAREN block  */
#line 343 "src/parser.y"
                                              {
        /* FIX: Pass *$4 (the vector) to constructor */
        (yyval.stmt) = (Statement*)(new FuncDecl(*(yyvsp[-4].sval), *(yyvsp[-2].param_list), (yyvsp[0].block), false))->loc((yylsp[-5]).first_line, (yylsp[-5]).first_column);
        delete (yyvsp[-4].sval); delete (yyvsp[-2].param_list);
    }
#line 2051 "src/parser.tab.cpp"
    break;

  case 66: /* circuit_decl: KW_CIRCUIT ID LPAREN param_list RPAREN block  */
#line 351 "src/parser.y"
                                                 {
        /* FIX: Pass *$4 to constructor */
        (yyval.stmt) = (Statement*)(new FuncDecl(*(yyvsp[-4].sval), *(yyvsp[-2].param_list), (yyvsp[0].block), true))->loc((yylsp[-5]).first_line, (yylsp[-5]).first_column);
        delete (yyvsp[-4].sval); delete (yyvsp[-2].param_list);
    }
#line 2061 "src/parser.tab.cpp"
    break;

  case 68: /* assignment: postfix ASSIGN expression  */
#line 361 "src/parser.y"
                              { 
        (yyval.expr) = (Expression*)(new BinaryExpr((yyvsp[-2].expr), OpType::ASSIGN, (yyvsp[0].expr)))->loc((yylsp[-1]).first_line, (yylsp[-1]).first_column); 
    }
#line 2069 "src/parser.tab.cpp"
    break;

  case 69: /* assignment: postfix PLUS_ASSIGN expression  */
#line 364 "src/parser.y"
                                     { 
        (yyval.expr) = (Expression*)(new BinaryExpr((yyvsp[-2].expr), OpType::PLUS_ASSIGN, (yyvsp[0].expr)))->loc((yylsp[-1]).first_line, (yylsp[-1]).first_column); 
    }
#line 2077 "src/parser.tab.cpp"
    break;

  case 70: /* assignment: postfix MINUS_ASSIGN expression  */
#line 367 "src/parser.y"
                                      { 
        (yyval.expr) = (Expression*)(new BinaryExpr((yyvsp[-2].expr), OpType::MINUS_ASSIGN, (yyvsp[0].expr)))->loc((yylsp[-1]).first_line, (yylsp[-1]).first_column); 
    }
#line 2085 "src/parser.tab.cpp"
    break;

  case 72: /* range_expr: logical_or RANGE logical_or  */
#line 374 "src/parser.y"
                                { 
        (yyval.expr) = (Expression*)(new RangeExpr((yyvsp[-2].expr), (yyvsp[0].expr)))->loc((yylsp[-1]).first_line, (yylsp[-1]).first_column); 
    }
#line 2093 "src/parser.tab.cpp"
    break;

  case 74: /* logical_or: logical_or OR logical_and  */
#line 381 "src/parser.y"
                              { 
        (yyval.expr) = (Expression*)(new BinaryExpr((yyvsp[-2].expr), OpType::OR, (yyvsp[0].expr)))->loc((yylsp[-1]).first_line, (yylsp[-1]).first_column); 
    }
#line 2101 "src/parser.tab.cpp"
    break;

  case 76: /* logical_and: logical_and AND bitwise  */
#line 388 "src/parser.y"
                            { 
        (yyval.expr) = (Expression*)(new BinaryExpr((yyvsp[-2].expr), OpType::AND, (yyvsp[0].expr)))->loc((yylsp[-1]).first_line, (yylsp[-1]).first_column); 
    }
#line 2109 "src/parser.tab.cpp"
    break;

  case 78: /* bitwise: bitwise BIT_OR equality  */
#line 395 "src/parser.y"
                            { 
        (yyval.expr) = (Expression*)(new BinaryExpr((yyvsp[-2].expr), OpType::BIT_OR, (yyvsp[0].expr)))->loc((yylsp[-1]).first_line, (yylsp[-1]).first_column); 
    }
#line 2117 "src/parser.tab.cpp"
    break;

  case 79: /* bitwise: bitwise BIT_XOR equality  */
#line 398 "src/parser.y"
                               { 
        (yyval.expr) = (Expression*)(new BinaryExpr((yyvsp[-2].expr), OpType::BIT_XOR, (yyvsp[0].expr)))->loc((yylsp[-1]).first_line, (yylsp[-1]).first_column); 
    }
#line 2125 "src/parser.tab.cpp"
    break;

  case 80: /* bitwise: bitwise BIT_AND equality  */
#line 401 "src/parser.y"
                               { 
        (yyval.expr) = (Expression*)(new BinaryExpr((yyvsp[-2].expr), OpType::BIT_AND, (yyvsp[0].expr)))->loc((yylsp[-1]).first_line, (yylsp[-1]).first_column); 
    }
#line 2133 "src/parser.tab.cpp"
    break;

  case 82: /* equality: equality EQ relational  */
#line 408 "src/parser.y"
                           { 
        (yyval.expr) = (Expression*)(new BinaryExpr((yyvsp[-2].expr), OpType::EQ, (yyvsp[0].expr)))->loc((yylsp[-1]).first_line, (yylsp[-1]).first_column); 
    }
#line 2141 "src/parser.tab.cpp"
    break;

  case 83: /* equality: equality NEQ relational  */
#line 411 "src/parser.y"
                              { 
        (yyval.expr) = (Expression*)(new BinaryExpr((yyvsp[-2].expr), OpType::NEQ, (yyvsp[0].expr)))->loc((yylsp[-1]).first_line, (yylsp[-1]).first_column); 
    }
#line 2149 "src/parser.tab.cpp"
    break;

  case 85: /* relational: relational LT shift_expr  */
#line 418 "src/parser.y"
                             { 
        (yyval.expr) = (Expression*)(new BinaryExpr((yyvsp[-2].expr), OpType::LT, (yyvsp[0].expr)))->loc((yylsp[-1]).first_line, (yylsp[-1]).first_column); 
    }
#line 2157 "src/parser.tab.cpp"
    break;

  case 86: /* relational: relational GT shift_expr  */
#line 421 "src/parser.y"
                               { 
        (yyval.expr) = (Expression*)(new BinaryExpr((yyvsp[-2].expr), OpType::GT, (yyvsp[0].expr)))->loc((yylsp[-1]).first_line, (yylsp[-1]).first_column); 
    }
#line 2165 "src/parser.tab.cpp"
    break;

  case 87: /* relational: relational LTE shift_expr  */
#line 424 "src/parser.y"
                                { 
        (yyval.expr) = (Expression*)(new BinaryExpr((yyvsp[-2].expr), OpType::LTE, (yyvsp[0].expr)))->loc((yylsp[-1]).first_line, (yylsp[-1]).first_column); 
    }
#line 2173 "src/parser.tab.cpp"
    break;

  case 88: /* relational: relational GTE shift_expr  */
#line 427 "src/parser.y"
                                { 
        (yyval.expr) = (Expression*)(new BinaryExpr((yyvsp[-2].expr), OpType::GTE, (yyvsp[0].expr)))->loc((yylsp[-1]).first_line, (yylsp[-1]).first_column); 
    }
#line 2181 "src/parser.tab.cpp"
    break;

  case 90: /* shift_expr: shift_expr LSHIFT additive  */
#line 434 "src/parser.y"
                               { 
        (yyval.expr) = (Expression*)(new BinaryExpr((yyvsp[-2].expr), OpType::LSHIFT, (yyvsp[0].expr)))->loc((yylsp[-1]).first_line, (yylsp[-1]).first_column); 
    }
#line 2189 "src/parser.tab.cpp"
    break;

  case 91: /* shift_expr: shift_expr RSHIFT additive  */
#line 437 "src/parser.y"
                                 { 
        (yyval.expr) = (Expression*)(new BinaryExpr((yyvsp[-2].expr), OpType::RSHIFT, (yyvsp[0].expr)))->loc((yylsp[-1]).first_line, (yylsp[-1]).first_column); 
    }
#line 2197 "src/parser.tab.cpp"
    break;

  case 93: /* additive: additive PLUS multiplicative  */
#line 444 "src/parser.y"
                                 { 
        (yyval.expr) = (Expression*)(new BinaryExpr((yyvsp[-2].expr), OpType::PLUS, (yyvsp[0].expr)))->loc((yylsp[-1]).first_line, (yylsp[-1]).first_column); 
    }
#line 2205 "src/parser.tab.cpp"
    break;

  case 94: /* additive: additive MINUS multiplicative  */
#line 447 "src/parser.y"
                                    { 
        (yyval.expr) = (Expression*)(new BinaryExpr((yyvsp[-2].expr), OpType::MINUS, (yyvsp[0].expr)))->loc((yylsp[-1]).first_line, (yylsp[-1]).first_column); 
    }
#line 2213 "src/parser.tab.cpp"
    break;

  case 96: /* multiplicative: multiplicative STAR unary  */
#line 454 "src/parser.y"
                              { 
        (yyval.expr) = (Expression*)(new BinaryExpr((yyvsp[-2].expr), OpType::MUL, (yyvsp[0].expr)))->loc((yylsp[-1]).first_line, (yylsp[-1]).first_column); 
    }
#line 2221 "src/parser.tab.cpp"
    break;

  case 97: /* multiplicative: multiplicative SLASH unary  */
#line 457 "src/parser.y"
                                 { 
        (yyval.expr) = (Expression*)(new BinaryExpr((yyvsp[-2].expr), OpType::DIV, (yyvsp[0].expr)))->loc((yylsp[-1]).first_line, (yylsp[-1]).first_column); 
    }
#line 2229 "src/parser.tab.cpp"
    break;

  case 98: /* multiplicative: multiplicative PERCENT unary  */
#line 460 "src/parser.y"
                                   { 
        (yyval.expr) = (Expression*)(new BinaryExpr((yyvsp[-2].expr), OpType::MOD, (yyvsp[0].expr)))->loc((yylsp[-1]).first_line, (yylsp[-1]).first_column); 
    }
#line 2237 "src/parser.tab.cpp"
    break;

  case 99: /* multiplicative: multiplicative POWER unary  */
#line 463 "src/parser.y"
                                 { 
        (yyval.expr) = (Expression*)(new BinaryExpr((yyvsp[-2].expr), OpType::POWER, (yyvsp[0].expr)))->loc((yylsp[-1]).first_line, (yylsp[-1]).first_column); 
    }
#line 2245 "src/parser.tab.cpp"
    break;

  case 101: /* unary: NOT unary  */
#line 470 "src/parser.y"
              { 
        (yyval.expr) = (Expression*)(new UnaryExpr(OpType::NOT, (yyvsp[0].expr)))->loc((yylsp[-1]).first_line, (yylsp[-1]).first_column); 
    }
#line 2253 "src/parser.tab.cpp"
    break;

  case 102: /* unary: MINUS unary  */
#line 473 "src/parser.y"
                               { 
        (yyval.expr) = (Expression*)(new UnaryExpr(OpType::MINUS, (yyvsp[0].expr)))->loc((yylsp[-1]).first_line, (yylsp[-1]).first_column); 
    }
#line 2261 "src/parser.tab.cpp"
    break;

  case 105: /* postfix: postfix DOT ID LPAREN argument_list RPAREN  */
#line 481 "src/parser.y"
                                                 {
        (yyval.expr) = (Expression*)(new MethodCallExpr((yyvsp[-5].expr), *(yyvsp[-3].sval), *(yyvsp[-1].expr_list)))->loc((yylsp[-4]).first_line, (yylsp[-4]).first_column);
        delete (yyvsp[-3].sval); delete (yyvsp[-1].expr_list);
    }
#line 2270 "src/parser.tab.cpp"
    break;

  case 106: /* postfix: postfix DOT ID LPAREN RPAREN  */
#line 485 "src/parser.y"
                                   {
        (yyval.expr) = (Expression*)(new MethodCallExpr((yyvsp[-4].expr), *(yyvsp[-2].sval), {}))->loc((yylsp[-3]).first_line, (yylsp[-3]).first_column);
        delete (yyvsp[-2].sval);
    }
#line 2279 "src/parser.tab.cpp"
    break;

  case 107: /* postfix: postfix LBRACKET expression RBRACKET  */
#line 489 "src/parser.y"
                                           {
        (yyval.expr) = (Expression*)(new IndexExpr((yyvsp[-3].expr), (yyvsp[-1].expr)))->loc((yylsp[-2]).first_line, (yylsp[-2]).first_column);
    }
#line 2287 "src/parser.tab.cpp"
    break;

  case 108: /* postfix: postfix LPAREN argument_list RPAREN  */
#line 494 "src/parser.y"
                                          {
        /* Check if the left side is an Identifier */
        if (auto id = dynamic_cast<Identifier*>((yyvsp[-3].expr))) {
            (yyval.expr) = (Expression*)(new CallExpr(id->name, *(yyvsp[-1].expr_list)))->loc((yylsp[-2]).first_line, (yylsp[-2]).first_column);
            /* We extracted the name, so we can delete the ID node */
            delete id;
        } else {
            /* Error case: Trying to call (1+2)(args) or similar */
            /* For resilience, create a call to "unknown" or handle error reporting here */
            (yyval.expr) = (yyvsp[-3].expr); // Fallback (or trigger yyerror)
            std::cerr << "Syntax Error: Call must be on an identifier." << std::endl;
        }
        delete (yyvsp[-1].expr_list); 
    }
#line 2306 "src/parser.tab.cpp"
    break;

  case 109: /* postfix: postfix LPAREN RPAREN  */
#line 508 "src/parser.y"
                            {
        if (auto id = dynamic_cast<Identifier*>((yyvsp[-2].expr))) {
            (yyval.expr) = (Expression*)(new CallExpr(id->name, {}))->loc((yylsp[-1]).first_line, (yylsp[-1]).first_column);
            delete id;
        } else {
            (yyval.expr) = (yyvsp[-2].expr); 
            std::cerr << "Syntax Error: Call must be on an identifier." << std::endl;
        }
    }
#line 2320 "src/parser.tab.cpp"
    break;

  case 110: /* primary: INT_LIT  */
#line 520 "src/parser.y"
            { (yyval.expr) = (Expression*)(new IntLiteral((yyvsp[0].ival)))->loc((yylsp[0]).first_line, (yylsp[0]).first_column); }
#line 2326 "src/parser.tab.cpp"
    break;

  case 111: /* primary: FLOAT_LIT  */
#line 521 "src/parser.y"
                { (yyval.expr) = (Expression*)(new FloatLiteral((yyvsp[0].fval)))->loc((yylsp[0]).first_line, (yylsp[0]).first_column); }
#line 2332 "src/parser.tab.cpp"
    break;

  case 112: /* primary: BOOL_LIT  */
#line 522 "src/parser.y"
               { (yyval.expr) = (Expression*)(new BoolLiteral((yyvsp[0].ival) != 0))->loc((yylsp[0]).first_line, (yylsp[0]).first_column); }
#line 2338 "src/parser.tab.cpp"
    break;

  case 113: /* primary: STRING_LIT  */
#line 523 "src/parser.y"
                 { (yyval.expr) = (Expression*)(new StringLiteral(*(yyvsp[0].sval)))->loc((yylsp[0]).first_line, (yylsp[0]).first_column); }
#line 2344 "src/parser.tab.cpp"
    break;

  case 114: /* primary: IMAG_LIT  */
#line 524 "src/parser.y"
               { (yyval.expr) = (Expression*)(new ImaginaryLiteral((yyvsp[0].fval)))->loc((yylsp[0]).first_line, (yylsp[0]).first_column); }
#line 2350 "src/parser.tab.cpp"
    break;

  case 115: /* primary: TIME_LIT  */
#line 525 "src/parser.y"
               { (yyval.expr) = (Expression*)(new Identifier(*(yyvsp[0].sval)))->loc((yylsp[0]).first_line, (yylsp[0]).first_column); }
#line 2356 "src/parser.tab.cpp"
    break;

  case 116: /* primary: ID  */
#line 526 "src/parser.y"
         { (yyval.expr) = (Expression*)(new Identifier(*(yyvsp[0].sval)))->loc((yylsp[0]).first_line, (yylsp[0]).first_column); }
#line 2362 "src/parser.tab.cpp"
    break;

  case 117: /* primary: LPAREN expression RPAREN  */
#line 527 "src/parser.y"
                               { (yyval.expr) = (yyvsp[-1].expr); }
#line 2368 "src/parser.tab.cpp"
    break;

  case 118: /* primary: LBRACKET elements RBRACKET  */
#line 528 "src/parser.y"
                                 {
        (yyval.expr) = (Expression*)(new ArrayLiteral(*(yyvsp[-1].expr_list)))->loc((yylsp[-2]).first_line, (yylsp[-2]).first_column);
        delete (yyvsp[-1].expr_list);
    }
#line 2377 "src/parser.tab.cpp"
    break;

  case 119: /* primary: LBRACE argument_list RBRACE  */
#line 533 "src/parser.y"
                                  {
        (yyval.expr) = (Expression*)(new ArrayLiteral(*(yyvsp[-1].expr_list)))->loc((yylsp[-2]).first_line, (yylsp[-2]).first_column);
        delete (yyvsp[-1].expr_list);
    }
#line 2386 "src/parser.tab.cpp"
    break;

  case 120: /* elements: %empty  */
#line 540 "src/parser.y"
                { (yyval.expr_list) = new std::vector<Expression*>(); }
#line 2392 "src/parser.tab.cpp"
    break;

  case 121: /* elements: argument_list  */
#line 541 "src/parser.y"
                    { (yyval.expr_list) = (yyvsp[0].expr_list); }
#line 2398 "src/parser.tab.cpp"
    break;

  case 122: /* argument_list: expression  */
#line 545 "src/parser.y"
               { 
        (yyval.expr_list) = new std::vector<Expression*>();
        (yyval.expr_list)->push_back((yyvsp[0].expr)); 
    }
#line 2407 "src/parser.tab.cpp"
    break;

  case 123: /* argument_list: argument_list COMMA expression  */
#line 549 "src/parser.y"
                                     {
        (yyvsp[-2].expr_list)->push_back((yyvsp[0].expr));
        (yyval.expr_list) = (yyvsp[-2].expr_list);
    }
#line 2416 "src/parser.tab.cpp"
    break;


#line 2420 "src/parser.tab.cpp"

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
  *++yylsp = yyloc;

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
      yyerror (&yylloc, scanner, root, YY_("syntax error"));
    }

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc, scanner, root);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, scanner, root);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

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
  yyerror (&yylloc, scanner, root, YY_("memory exhausted"));
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
                  yytoken, &yylval, &yylloc, scanner, root);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, scanner, root);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 555 "src/parser.y"


void yyerror(const YYLTYPE* loc, yyscan_t scanner, Program** root, const char *s) {
    std::cerr << "Parser Error at line " << loc->first_line << ", col " << loc->first_column 
              << ": " << s << std::endl;
}
