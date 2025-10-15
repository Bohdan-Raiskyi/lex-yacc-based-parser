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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Value type for evaluation
typedef struct Value {
    int type; // 0 = int, 1 = float, 2 = undefined, 3 = bool
    union {
        int int_val;
        float float_val;
        int bool_val;
    };
} Value;

// AST Node Types
typedef enum {
    NODE_PROGRAM,
    NODE_DECLARATION,
    NODE_ASSIGNMENT,
    NODE_RETURN,
    NODE_BINARY_OP,
    NODE_IDENTIFIER,
    NODE_INT_CONSTANT,
    NODE_FLOAT_CONSTANT,
    NODE_COMPOUND_STMT,
    NODE_IF,
    NODE_EQ,
    NODE_NE,
    NODE_GT,
    NODE_LT,
    NODE_GE,
    NODE_LE,
    NODE_AND,
    NODE_OR,
    NODE_NOT
} NodeType;

// AST Node Structure
typedef struct ASTNode {
    NodeType type;
    char* name;  // For identifiers
    union {
        int int_value;
        float float_value;
        int bool_value;
    };
    struct ASTNode* left;
    struct ASTNode* right;
    struct ASTNode* next; // For linked lists (statements)
    struct ASTNode* else_branch; // For if-else statements
} ASTNode;

// Symbol table for evaluation
typedef struct Symbol {
    char* name;
    Value value;
    int initialized;
} Symbol;

#define MAX_SYMBOLS 100
Symbol symbol_table[MAX_SYMBOLS];
int symbol_count = 0;

// Global root of AST
ASTNode* root = NULL;

// Function declarations
ASTNode* create_node(NodeType type);
ASTNode* create_int_node(int value);
ASTNode* create_float_node(float value);
ASTNode* create_identifier_node(char* name);
ASTNode* create_binary_op_node(NodeType op, ASTNode* left, ASTNode* right);
ASTNode* create_unary_op_node(NodeType op, ASTNode* operand);
ASTNode* create_if_node(ASTNode* condition, ASTNode* then_branch, ASTNode* else_branch);
void free_ast(ASTNode* node);
void print_ast(ASTNode* node, int depth);
void generate_code(ASTNode* node, FILE* output);
Value evaluate_expression(ASTNode* node);

extern int line_num;
extern FILE *yyin;
void yyerror(const char *s);
int yylex(void);


#line 159 "parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT_CONSTANT = 3,               /* INT_CONSTANT  */
  YYSYMBOL_FLOAT_CONSTANT = 4,             /* FLOAT_CONSTANT  */
  YYSYMBOL_IDENTIFIER = 5,                 /* IDENTIFIER  */
  YYSYMBOL_INT = 6,                        /* INT  */
  YYSYMBOL_FLOAT = 7,                      /* FLOAT  */
  YYSYMBOL_RETURN = 8,                     /* RETURN  */
  YYSYMBOL_IF = 9,                         /* IF  */
  YYSYMBOL_ELSE = 10,                      /* ELSE  */
  YYSYMBOL_LBRACE = 11,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 12,                    /* RBRACE  */
  YYSYMBOL_LPAREN = 13,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 14,                    /* RPAREN  */
  YYSYMBOL_SEMICOLON = 15,                 /* SEMICOLON  */
  YYSYMBOL_ASSIGN = 16,                    /* ASSIGN  */
  YYSYMBOL_PLUS = 17,                      /* PLUS  */
  YYSYMBOL_MINUS = 18,                     /* MINUS  */
  YYSYMBOL_MULTIPLY = 19,                  /* MULTIPLY  */
  YYSYMBOL_DIVIDE = 20,                    /* DIVIDE  */
  YYSYMBOL_EQ = 21,                        /* EQ  */
  YYSYMBOL_NE = 22,                        /* NE  */
  YYSYMBOL_GT = 23,                        /* GT  */
  YYSYMBOL_LT = 24,                        /* LT  */
  YYSYMBOL_GE = 25,                        /* GE  */
  YYSYMBOL_LE = 26,                        /* LE  */
  YYSYMBOL_AND = 27,                       /* AND  */
  YYSYMBOL_OR = 28,                        /* OR  */
  YYSYMBOL_NOT = 29,                       /* NOT  */
  YYSYMBOL_ERROR = 30,                     /* ERROR  */
  YYSYMBOL_YYACCEPT = 31,                  /* $accept  */
  YYSYMBOL_program = 32,                   /* program  */
  YYSYMBOL_statement_list = 33,            /* statement_list  */
  YYSYMBOL_statement = 34,                 /* statement  */
  YYSYMBOL_declaration = 35,               /* declaration  */
  YYSYMBOL_assignment = 36,                /* assignment  */
  YYSYMBOL_if_statement = 37,              /* if_statement  */
  YYSYMBOL_compound_statement = 38,        /* compound_statement  */
  YYSYMBOL_expression = 39,                /* expression  */
  YYSYMBOL_logical_or_expression = 40,     /* logical_or_expression  */
  YYSYMBOL_logical_and_expression = 41,    /* logical_and_expression  */
  YYSYMBOL_equality_expression = 42,       /* equality_expression  */
  YYSYMBOL_relational_expression = 43,     /* relational_expression  */
  YYSYMBOL_additive_expression = 44,       /* additive_expression  */
  YYSYMBOL_multiplicative_expression = 45, /* multiplicative_expression  */
  YYSYMBOL_primary_expression = 46         /* primary_expression  */
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
typedef yytype_int8 yy_state_t;

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
#define YYFINAL  19
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   76

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  16
/* YYNRULES -- Number of rules.  */
#define YYNRULES  41
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  76

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   285


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
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   124,   124,   132,   135,   146,   149,   152,   155,   161,
     165,   169,   174,   182,   190,   193,   199,   203,   209,   213,
     214,   220,   221,   227,   228,   231,   237,   238,   241,   244,
     247,   253,   254,   257,   263,   264,   267,   273,   276,   279,
     282,   285
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
  "\"end of file\"", "error", "\"invalid token\"", "INT_CONSTANT",
  "FLOAT_CONSTANT", "IDENTIFIER", "INT", "FLOAT", "RETURN", "IF", "ELSE",
  "LBRACE", "RBRACE", "LPAREN", "RPAREN", "SEMICOLON", "ASSIGN", "PLUS",
  "MINUS", "MULTIPLY", "DIVIDE", "EQ", "NE", "GT", "LT", "GE", "LE", "AND",
  "OR", "NOT", "ERROR", "$accept", "program", "statement_list",
  "statement", "declaration", "assignment", "if_statement",
  "compound_statement", "expression", "logical_or_expression",
  "logical_and_expression", "equality_expression", "relational_expression",
  "additive_expression", "multiplicative_expression", "primary_expression", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-25)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      34,    -6,    12,    14,    21,     9,    25,    34,   -25,   -25,
     -25,   -25,   -25,    -1,     7,    31,    -1,   -25,    26,   -25,
     -25,   -25,   -25,   -25,    -1,    -1,    29,     8,     0,    27,
     -17,    38,    39,   -25,   -25,    -1,   -25,    -1,    28,   -25,
      43,   -25,   -25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    49,    50,    34,   -25,     0,
      27,   -17,   -17,    38,    38,    38,    38,    39,    39,   -25,
     -25,   -25,   -25,    56,    34,   -25
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     2,     3,     5,
       6,     7,     8,     0,     0,     0,     0,    17,     0,     1,
       4,    38,    39,    37,     0,     0,     0,    18,    19,    21,
      23,    26,    31,    34,     9,     0,    10,     0,     0,    16,
       0,    41,    13,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    40,    20,
      22,    24,    25,    27,    28,    29,    30,    32,    33,    35,
      36,    11,    12,    14,     0,    15
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -25,   -25,    63,    -7,   -25,   -25,   -25,   -25,   -11,   -25,
      30,    32,    15,     4,    11,   -24
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     6,     7,     8,     9,    10,    11,    12,    26,    27,
      28,    29,    30,    31,    32,    33
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      20,    41,    21,    22,    23,    38,    47,    48,    49,    50,
      13,    20,    24,    40,     1,     2,     3,    14,     4,    15,
       5,    17,    34,    35,    55,    19,    56,    44,    25,    69,
      70,     1,     2,     3,    16,     4,    43,     5,    39,     1,
       2,     3,    57,     4,    42,     5,    36,    37,    45,    46,
      73,    63,    64,    65,    66,    51,    52,    58,    53,    54,
      61,    62,    67,    68,    71,    72,    74,    75,    18,     0,
       0,     0,     0,    59,     0,     0,    60
};

static const yytype_int8 yycheck[] =
{
       7,    25,     3,     4,     5,    16,    23,    24,    25,    26,
      16,    18,    13,    24,     5,     6,     7,     5,     9,     5,
      11,    12,    15,    16,    35,     0,    37,    27,    29,    53,
      54,     5,     6,     7,    13,     9,    28,    11,    12,     5,
       6,     7,    14,     9,    15,    11,    15,    16,    21,    22,
      57,    47,    48,    49,    50,    17,    18,    14,    19,    20,
      45,    46,    51,    52,    15,    15,    10,    74,     5,    -1,
      -1,    -1,    -1,    43,    -1,    -1,    44
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     5,     6,     7,     9,    11,    32,    33,    34,    35,
      36,    37,    38,    16,     5,     5,    13,    12,    33,     0,
      34,     3,     4,     5,    13,    29,    39,    40,    41,    42,
      43,    44,    45,    46,    15,    16,    15,    16,    39,    12,
      39,    46,    15,    28,    27,    21,    22,    23,    24,    25,
      26,    17,    18,    19,    20,    39,    39,    14,    14,    41,
      42,    43,    43,    44,    44,    44,    44,    45,    45,    46,
      46,    15,    15,    34,    10,    34
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    31,    32,    33,    33,    34,    34,    34,    34,    35,
      35,    35,    35,    36,    37,    37,    38,    38,    39,    40,
      40,    41,    41,    42,    42,    42,    43,    43,    43,    43,
      43,    44,    44,    44,    45,    45,    45,    46,    46,    46,
      46,    46
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     3,
       3,     5,     5,     4,     5,     7,     3,     2,     1,     1,
       3,     1,     3,     1,     3,     3,     1,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     1,     1,     1,
       3,     2
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
  case 2: /* program: statement_list  */
#line 124 "parser.y"
                   {
        (yyval.node) = create_node(NODE_PROGRAM);
        (yyval.node)->left = (yyvsp[0].node);
        root = (yyval.node);
    }
#line 1241 "parser.tab.c"
    break;

  case 3: /* statement_list: statement  */
#line 132 "parser.y"
              {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1249 "parser.tab.c"
    break;

  case 4: /* statement_list: statement_list statement  */
#line 135 "parser.y"
                               {
        struct ASTNode* current = (yyvsp[-1].node);
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = (yyvsp[0].node);
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1262 "parser.tab.c"
    break;

  case 5: /* statement: declaration  */
#line 146 "parser.y"
                {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1270 "parser.tab.c"
    break;

  case 6: /* statement: assignment  */
#line 149 "parser.y"
                 {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1278 "parser.tab.c"
    break;

  case 7: /* statement: if_statement  */
#line 152 "parser.y"
                   {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1286 "parser.tab.c"
    break;

  case 8: /* statement: compound_statement  */
#line 155 "parser.y"
                         {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1294 "parser.tab.c"
    break;

  case 9: /* declaration: INT IDENTIFIER SEMICOLON  */
#line 161 "parser.y"
                             {
        (yyval.node) = create_node(NODE_DECLARATION);
        (yyval.node)->name = (yyvsp[-1].string_val);
    }
#line 1303 "parser.tab.c"
    break;

  case 10: /* declaration: FLOAT IDENTIFIER SEMICOLON  */
#line 165 "parser.y"
                                 {
        (yyval.node) = create_node(NODE_DECLARATION);
        (yyval.node)->name = (yyvsp[-1].string_val);
    }
#line 1312 "parser.tab.c"
    break;

  case 11: /* declaration: INT IDENTIFIER ASSIGN expression SEMICOLON  */
#line 169 "parser.y"
                                                 {
        (yyval.node) = create_node(NODE_DECLARATION);
        (yyval.node)->name = (yyvsp[-3].string_val);
        (yyval.node)->left = (yyvsp[-1].node);
    }
#line 1322 "parser.tab.c"
    break;

  case 12: /* declaration: FLOAT IDENTIFIER ASSIGN expression SEMICOLON  */
#line 174 "parser.y"
                                                   {
        (yyval.node) = create_node(NODE_DECLARATION);
        (yyval.node)->name = (yyvsp[-3].string_val);
        (yyval.node)->left = (yyvsp[-1].node);
    }
#line 1332 "parser.tab.c"
    break;

  case 13: /* assignment: IDENTIFIER ASSIGN expression SEMICOLON  */
#line 182 "parser.y"
                                           {
        (yyval.node) = create_node(NODE_ASSIGNMENT);
        (yyval.node)->name = (yyvsp[-3].string_val);
        (yyval.node)->left = (yyvsp[-1].node);
    }
#line 1342 "parser.tab.c"
    break;

  case 14: /* if_statement: IF LPAREN expression RPAREN statement  */
#line 190 "parser.y"
                                          {
        (yyval.node) = create_if_node((yyvsp[-2].node), (yyvsp[0].node), NULL);
    }
#line 1350 "parser.tab.c"
    break;

  case 15: /* if_statement: IF LPAREN expression RPAREN statement ELSE statement  */
#line 193 "parser.y"
                                                           {
        (yyval.node) = create_if_node((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1358 "parser.tab.c"
    break;

  case 16: /* compound_statement: LBRACE statement_list RBRACE  */
#line 199 "parser.y"
                                 {
        (yyval.node) = create_node(NODE_COMPOUND_STMT);
        (yyval.node)->left = (yyvsp[-1].node);
    }
#line 1367 "parser.tab.c"
    break;

  case 17: /* compound_statement: LBRACE RBRACE  */
#line 203 "parser.y"
                    {
        (yyval.node) = create_node(NODE_COMPOUND_STMT);
    }
#line 1375 "parser.tab.c"
    break;

  case 20: /* logical_or_expression: logical_or_expression OR logical_and_expression  */
#line 214 "parser.y"
                                                      {
        (yyval.node) = create_binary_op_node(NODE_OR, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1383 "parser.tab.c"
    break;

  case 22: /* logical_and_expression: logical_and_expression AND equality_expression  */
#line 221 "parser.y"
                                                     {
        (yyval.node) = create_binary_op_node(NODE_AND, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1391 "parser.tab.c"
    break;

  case 24: /* equality_expression: equality_expression EQ relational_expression  */
#line 228 "parser.y"
                                                   {
        (yyval.node) = create_binary_op_node(NODE_EQ, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1399 "parser.tab.c"
    break;

  case 25: /* equality_expression: equality_expression NE relational_expression  */
#line 231 "parser.y"
                                                   {
        (yyval.node) = create_binary_op_node(NODE_NE, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1407 "parser.tab.c"
    break;

  case 27: /* relational_expression: relational_expression GT additive_expression  */
#line 238 "parser.y"
                                                   {
        (yyval.node) = create_binary_op_node(NODE_GT, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1415 "parser.tab.c"
    break;

  case 28: /* relational_expression: relational_expression LT additive_expression  */
#line 241 "parser.y"
                                                   {
        (yyval.node) = create_binary_op_node(NODE_LT, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1423 "parser.tab.c"
    break;

  case 29: /* relational_expression: relational_expression GE additive_expression  */
#line 244 "parser.y"
                                                   {
        (yyval.node) = create_binary_op_node(NODE_GE, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1431 "parser.tab.c"
    break;

  case 30: /* relational_expression: relational_expression LE additive_expression  */
#line 247 "parser.y"
                                                   {
        (yyval.node) = create_binary_op_node(NODE_LE, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1439 "parser.tab.c"
    break;

  case 32: /* additive_expression: additive_expression PLUS multiplicative_expression  */
#line 254 "parser.y"
                                                         {
        (yyval.node) = create_binary_op_node(NODE_BINARY_OP, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1447 "parser.tab.c"
    break;

  case 33: /* additive_expression: additive_expression MINUS multiplicative_expression  */
#line 257 "parser.y"
                                                          {
        (yyval.node) = create_binary_op_node(NODE_BINARY_OP, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1455 "parser.tab.c"
    break;

  case 35: /* multiplicative_expression: multiplicative_expression MULTIPLY primary_expression  */
#line 264 "parser.y"
                                                            {
        (yyval.node) = create_binary_op_node(NODE_BINARY_OP, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1463 "parser.tab.c"
    break;

  case 36: /* multiplicative_expression: multiplicative_expression DIVIDE primary_expression  */
#line 267 "parser.y"
                                                          {
        (yyval.node) = create_binary_op_node(NODE_BINARY_OP, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1471 "parser.tab.c"
    break;

  case 37: /* primary_expression: IDENTIFIER  */
#line 273 "parser.y"
               {
        (yyval.node) = create_identifier_node((yyvsp[0].string_val));
    }
#line 1479 "parser.tab.c"
    break;

  case 38: /* primary_expression: INT_CONSTANT  */
#line 276 "parser.y"
                   {
        (yyval.node) = create_int_node((yyvsp[0].int_val));
    }
#line 1487 "parser.tab.c"
    break;

  case 39: /* primary_expression: FLOAT_CONSTANT  */
#line 279 "parser.y"
                     {
        (yyval.node) = create_float_node((yyvsp[0].float_val));
    }
#line 1495 "parser.tab.c"
    break;

  case 40: /* primary_expression: LPAREN expression RPAREN  */
#line 282 "parser.y"
                               {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1503 "parser.tab.c"
    break;

  case 41: /* primary_expression: NOT primary_expression  */
#line 285 "parser.y"
                             {
        (yyval.node) = create_unary_op_node(NODE_NOT, (yyvsp[0].node));
    }
#line 1511 "parser.tab.c"
    break;


#line 1515 "parser.tab.c"

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

#line 290 "parser.y"


// AST Creation Functions
ASTNode* create_node(NodeType type) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = type;
    node->name = NULL;
    node->int_value = 0;
    node->float_value = 0.0f;
    node->bool_value = 0;
    node->left = node->right = node->next = node->else_branch = NULL;
    return node;
}

ASTNode* create_int_node(int value) {
    ASTNode* node = create_node(NODE_INT_CONSTANT);
    node->int_value = value;
    return node;
}

ASTNode* create_float_node(float value) {
    ASTNode* node = create_node(NODE_FLOAT_CONSTANT);
    node->float_value = value;
    return node;
}

ASTNode* create_identifier_node(char* name) {
    ASTNode* node = create_node(NODE_IDENTIFIER);
    node->name = strdup(name);
    return node;
}

ASTNode* create_binary_op_node(NodeType op, ASTNode* left, ASTNode* right) {
    ASTNode* node = create_node(op);
    node->left = left;
    node->right = right;
    return node;
}

ASTNode* create_unary_op_node(NodeType op, ASTNode* operand) {
    ASTNode* node = create_node(op);
    node->left = operand;
    return node;
}

ASTNode* create_if_node(ASTNode* condition, ASTNode* then_branch, ASTNode* else_branch) {
    ASTNode* node = create_node(NODE_IF);
    node->left = condition;
    node->right = then_branch;
    node->else_branch = else_branch;
    return node;
}

void free_ast(ASTNode* node) {
    if (node == NULL) return;
    
    free_ast(node->left);
    free_ast(node->right);
    free_ast(node->next);
    free_ast(node->else_branch);
    
    if (node->name != NULL) {
        free(node->name);
    }
    
    free(node);
}

// AST Printing Function
void print_ast(ASTNode* node, int depth) {
    if (node == NULL) {
        return;
    }
    
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    
    switch (node->type) {
        case NODE_PROGRAM:
            printf("PROGRAM\n");
            print_ast(node->left, depth + 1);
            break;
        case NODE_DECLARATION:
            printf("DECLARATION: %s\n", node->name);
            if (node->left != NULL) {
                print_ast(node->left, depth + 1);
            }
            break;
        case NODE_ASSIGNMENT:
            printf("ASSIGNMENT: %s\n", node->name);
            print_ast(node->left, depth + 1);
            break;
        case NODE_RETURN:
            printf("RETURN\n");
            print_ast(node->left, depth + 1);
            break;
        case NODE_BINARY_OP:
            printf("BINARY_OP\n");
            print_ast(node->left, depth + 1);
            print_ast(node->right, depth + 1);
            break;
        case NODE_IDENTIFIER:
            printf("IDENTIFIER: %s\n", node->name);
            break;
        case NODE_INT_CONSTANT:
            printf("INT: %d\n", node->int_value);
            break;
        case NODE_FLOAT_CONSTANT:
            printf("FLOAT: %f\n", node->float_value);
            break;
        case NODE_COMPOUND_STMT:
            printf("COMPOUND_STMT\n");
            print_ast(node->left, depth + 1);
            break;
        case NODE_IF:
            printf("IF\n");
            print_ast(node->left, depth + 1);
            print_ast(node->right, depth + 1);
            if (node->else_branch != NULL) {
                for (int i = 0; i < depth; i++) printf("  ");
                printf("ELSE\n");
                print_ast(node->else_branch, depth + 1);
            }
            break;
        case NODE_EQ:
            printf("EQ (==)\n");
            print_ast(node->left, depth + 1);
            print_ast(node->right, depth + 1);
            break;
        case NODE_NE:
            printf("NE (!=)\n");
            print_ast(node->left, depth + 1);
            print_ast(node->right, depth + 1);
            break;
        case NODE_GT:
            printf("GT (>)\n");
            print_ast(node->left, depth + 1);
            print_ast(node->right, depth + 1);
            break;
        case NODE_LT:
            printf("LT (<)\n");
            print_ast(node->left, depth + 1);
            print_ast(node->right, depth + 1);
            break;
        case NODE_GE:
            printf("GE (>=)\n");
            print_ast(node->left, depth + 1);
            print_ast(node->right, depth + 1);
            break;
        case NODE_LE:
            printf("LE (<=)\n");
            print_ast(node->left, depth + 1);
            print_ast(node->right, depth + 1);
            break;
        case NODE_AND:
            printf("AND (&&)\n");
            print_ast(node->left, depth + 1);
            print_ast(node->right, depth + 1);
            break;
        case NODE_OR:
            printf("OR (||)\n");
            print_ast(node->left, depth + 1);
            print_ast(node->right, depth + 1);
            break;
        case NODE_NOT:
            printf("NOT (!)\n");
            print_ast(node->left, depth + 1);
            break;
    }
    
    if (node->next != NULL) {
        print_ast(node->next, depth);
    }
}

// Symbol Table Functions
int find_symbol(char* name) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int add_symbol(char* name, Value value) {
    if (find_symbol(name) != -1) return 0;
    
    if (symbol_count < MAX_SYMBOLS) {
        symbol_table[symbol_count].name = strdup(name);
        symbol_table[symbol_count].value = value;
        symbol_table[symbol_count].initialized = 1;
        symbol_count++;
        return 1;
    }
    return 0;
}

// Expression Evaluation
Value evaluate_expression(ASTNode* node) {
    Value result = {0};
    
    if (node == NULL) return result;
    
    switch (node->type) {
        case NODE_INT_CONSTANT:
            result.type = 0;
            result.int_val = node->int_value;
            break;
            
        case NODE_FLOAT_CONSTANT:
            result.type = 1;
            result.float_val = node->float_value;
            break;
            
        case NODE_IDENTIFIER: {
            int idx = find_symbol(node->name);
            if (idx != -1 && symbol_table[idx].initialized) {
                return symbol_table[idx].value;
            } else {
                fprintf(stderr, "Error: Variable '%s' not initialized\n", node->name);
                result.type = 2; // undefined
            }
            break;
        }
            
        case NODE_BINARY_OP: {
            Value left = evaluate_expression(node->left);
            Value right = evaluate_expression(node->right);
            
            if (left.type == 0 && right.type == 0) {
                result.type = 0;
                result.int_val = left.int_val + right.int_val; // Default to addition
            } else if ((left.type == 0 || left.type == 1) && (right.type == 0 || right.type == 1)) {
                result.type = 1;
                float lval = (left.type == 0) ? (float)left.int_val : left.float_val;
                float rval = (right.type == 0) ? (float)right.int_val : right.float_val;
                result.float_val = lval + rval; // Default to addition
            }
            break;
        }
            
        case NODE_EQ:
        case NODE_NE:
        case NODE_GT:
        case NODE_LT:
        case NODE_GE:
        case NODE_LE:
        case NODE_AND:
        case NODE_OR:
        case NODE_NOT: {
            // Simplified evaluation - in real implementation would need proper comparison
            Value left = evaluate_expression(node->left);
            Value right = evaluate_expression(node->right);
            result.type = 3; // bool
            result.bool_val = 1; // placeholder
            break;
        }
            
        default:
            result.type = 2; // undefined
            break;
    }
    
    return result;
}

// Code Generation
void generate_code(ASTNode* node, FILE* output) {
    if (node == NULL) {
        return;
    }
    
    switch (node->type) {
        case NODE_PROGRAM:
            fprintf(output, "#include <stdio.h>\n\n");
            fprintf(output, "int main() {\n");
            generate_code(node->left, output);
            fprintf(output, "    return 0;\n");
            fprintf(output, "}\n");
            break;
            
        case NODE_DECLARATION:
            if (node->name != NULL) {
                fprintf(output, "    int %s", node->name);
                if (node->left != NULL) {
                    fprintf(output, " = ");
                    generate_code(node->left, output);
                }
                fprintf(output, ";\n");
            }
            break;
            
        case NODE_ASSIGNMENT:
            if (node->name != NULL) {
                fprintf(output, "    %s = ", node->name);
                generate_code(node->left, output);
                fprintf(output, ";\n");
            }
            break;
            
        case NODE_INT_CONSTANT:
            fprintf(output, "%d", node->int_value);
            break;
            
        case NODE_FLOAT_CONSTANT:
            fprintf(output, "%f", node->float_value);
            break;
            
        case NODE_IDENTIFIER:
            fprintf(output, "%s", node->name);
            break;
            
        case NODE_BINARY_OP:
            fprintf(output, "(");
            generate_code(node->left, output);
            fprintf(output, " + "); // Simplified - should check actual operator
            generate_code(node->right, output);
            fprintf(output, ")");
            break;
            
        case NODE_COMPOUND_STMT:
            fprintf(output, "{\n");
            generate_code(node->left, output);
            fprintf(output, "}\n");
            break;
            
        case NODE_IF:
            fprintf(output, "if (");
            generate_code(node->left, output);
            fprintf(output, ") ");
            generate_code(node->right, output);
            if (node->else_branch != NULL) {
                fprintf(output, " else ");
                generate_code(node->else_branch, output);
            }
            break;
            
        case NODE_EQ:
            fprintf(output, "(");
            generate_code(node->left, output);
            fprintf(output, " == ");
            generate_code(node->right, output);
            fprintf(output, ")");
            break;
            
        case NODE_NE:
            fprintf(output, "(");
            generate_code(node->left, output);
            fprintf(output, " != ");
            generate_code(node->right, output);
            fprintf(output, ")");
            break;
            
        case NODE_GT:
            fprintf(output, "(");
            generate_code(node->left, output);
            fprintf(output, " > ");
            generate_code(node->right, output);
            fprintf(output, ")");
            break;
            
        case NODE_LT:
            fprintf(output, "(");
            generate_code(node->left, output);
            fprintf(output, " < ");
            generate_code(node->right, output);
            fprintf(output, ")");
            break;
            
        case NODE_GE:
            fprintf(output, "(");
            generate_code(node->left, output);
            fprintf(output, " >= ");
            generate_code(node->right, output);
            fprintf(output, ")");
            break;
            
        case NODE_LE:
            fprintf(output, "(");
            generate_code(node->left, output);
            fprintf(output, " <= ");
            generate_code(node->right, output);
            fprintf(output, ")");
            break;
            
        case NODE_AND:
            fprintf(output, "(");
            generate_code(node->left, output);
            fprintf(output, " && ");
            generate_code(node->right, output);
            fprintf(output, ")");
            break;
            
        case NODE_OR:
            fprintf(output, "(");
            generate_code(node->left, output);
            fprintf(output, " || ");
            generate_code(node->right, output);
            fprintf(output, ")");
            break;
            
        case NODE_NOT:
            fprintf(output, "(!");
            generate_code(node->left, output);
            fprintf(output, ")");
            break;
            
        default:
            fprintf(stderr, "CODEGEN: Unknown node type: %d\n", node->type);
            break;
    }
    
    if (node->next != NULL) {
        generate_code(node->next, output);
    }
}

void yyerror(const char *s) {
    fprintf(stderr, "PARSER ERROR at line %d: %s\n", line_num, s);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file> [output_file]\n", argv[0]);
        return 1;
    }
    
    FILE* input = fopen(argv[1], "r");
    if (!input) {
        fprintf(stderr, "ERROR: Cannot open input file: %s\n", argv[1]);
        return 1;
    }
    
    fseek(input, 0, SEEK_END);
    long size = ftell(input);
    fseek(input, 0, SEEK_SET);
    
    if (size == 0) {
        fprintf(stderr, "ERROR: File is empty\n");
        fclose(input);
        return 1;
    }
    
    yyin = input;
    
    printf("Parsing file: %s\n", argv[1]);
    
    root = NULL;
    int parse_result = yyparse();
    
    fclose(input);
    
    if (parse_result == 0) {
        if (root == NULL) {
            printf("WARNING: Parsing succeeded but root is NULL!\n");
        } else {
            printf("\n=== AST STRUCTURE ===\n");
            print_ast(root, 0);
            
            FILE* output = stdout;
            if (argc > 2) {
                output = fopen(argv[2], "w");
                if (!output) {
                    fprintf(stderr, "Cannot open output file: %s\n", argv[2]);
                    output = stdout;
                }
            }
            
            printf("\n=== GENERATED C CODE ===\n");
            generate_code(root, output);
            
            if (output != stdout) {
                fclose(output);
                printf("Code written to: %s\n", argv[2]);
            }
            
            free_ast(root);
            root = NULL;
        }
    } else {
        fprintf(stderr, "Parsing failed!\n");
    }
    
    return parse_result;
}
