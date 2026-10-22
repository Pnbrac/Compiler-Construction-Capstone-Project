/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     INTCONST = 259,
     CHARCONST = 260,
     KWD_INT = 261,
     KWD_CHAR = 262,
     KWD_VOID = 263,
     KWD_WHILE = 264,
     KWD_RETURN = 265,
     KWD_IF = 266,
     KWD_ELSE = 267,
     KWD_FOR = 268,
     LSQ_BRKT = 269,
     RSQ_BRKT = 270,
     LCRLY_BRKT = 271,
     RCRLY_BRKT = 272,
     LPAREN = 273,
     RPAREN = 274,
     COMMA = 275,
     SEMICLN = 276,
     OPER_LTE = 277,
     OPER_LT = 278,
     OPER_DIV = 279,
     OPER_GT = 280,
     OPER_GTE = 281,
     OPER_EQ = 282,
     OPER_ASGN = 283,
     OPER_NEQ = 284,
     OPER_ADD = 285,
     OPER_SUB = 286,
     OPER_MUL = 287,
     ERROR = 288,
     ILLEGAL_TOK = 289,
     LOWER_THAN_ELSE = 290
   };
#endif
/* Tokens.  */
#define ID 258
#define INTCONST 259
#define CHARCONST 260
#define KWD_INT 261
#define KWD_CHAR 262
#define KWD_VOID 263
#define KWD_WHILE 264
#define KWD_RETURN 265
#define KWD_IF 266
#define KWD_ELSE 267
#define KWD_FOR 268
#define LSQ_BRKT 269
#define RSQ_BRKT 270
#define LCRLY_BRKT 271
#define RCRLY_BRKT 272
#define LPAREN 273
#define RPAREN 274
#define COMMA 275
#define SEMICLN 276
#define OPER_LTE 277
#define OPER_LT 278
#define OPER_DIV 279
#define OPER_GT 280
#define OPER_GTE 281
#define OPER_EQ 282
#define OPER_ASGN 283
#define OPER_NEQ 284
#define OPER_ADD 285
#define OPER_SUB 286
#define OPER_MUL 287
#define ERROR 288
#define ILLEGAL_TOK 289
#define LOWER_THAN_ELSE 290




/* Copy the first part of user declarations.  */
#line 2 "src/parser.y"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<../src/tree.h>
#include<../src/strtab.h>

extern char currFunction[256];

extern int yylineno;
extern int yylex(void);

int yywarning(char *msg);
int yyerror(char *msg);

int callArgDepth = 0;

extern tree *ast;

/* nodeTypes refer to different types of internal and external nodes
  that can be part of the abstract syntax tree.
  */
enum nodeTypes {PROGRAM, DECLLIST, DECL, VARDECL, TYPESPEC, FUNDECL,
                FORMALDECLLIST, FORMALDECL, FUNBODY, LOCALDECLLIST,
                STATEMENTLIST, STATEMENT, COMPOUNDSTMT, ASSIGNSTMT,
                CONDSTMT, LOOPSTMT, RETURNSTMT, EXPRESSION, RELOP,
                ADDEXPR, ADDOP, TERM, MULOP, FACTOR, FUNCCALLEXPR,
                ARGLIST, INTEGER, IDENTIFIER, VAR, ARRAYDECL, CHAR,
                FUNCTYPENAME};

enum opType {ADD, SUB, MUL, DIV, LT, LTE, EQ, GTE, GT, NEQ};

/* NOTE: mC has two kinds of scopes for variables : local and global.
  Variables declared outside any function are considered globals,
    whereas variables (and parameters) declared inside a function foo
    are local to foo.
  You should update the scope variable whenever you are inside a production
    that matches function definition (funDecl production).
  The rationale is that you are entering that function, so all variables,
    arrays, and other functions should be within this scope.
  You should pass this variable whenever you are
    calling the ST_insert or ST_lookup functions.
  This variable should be updated to scope = ""
    to indicate global scope whenever funDecl finishes.
  Treat these hints as helpful directions only.
  You may implement all of the functions as you like
    and not adhere to my instructions.
  As long as the directory structure is correct and the file names are correct,
    we are okay with it.
  */
char* scope = "";

#define TYPE_ERROR (-1)

static char current_function[256] = "";
static int pending_func_index = -1;
static int pending_param_count = 0;

static int in_local_scope(void){
    return current_function[0] != '\0';
}

static int is_same_scope_entry(symEntry *entry){
    if (!entry) { return 0; }
    if (!in_local_scope()) { return (entry->scope == NULL || entry->scope[0] == '\0'); }
    return (entry->scope != NULL && strcmp(entry->scope, current_function) == 0);
}

static int insert_decl(char *id, int data_type, int symbol_type){
  int scope_flag = in_local_scope() ? 1 : 0;
  symEntry *existing = ST_lookup(id);

  if(existing && strcmp(existing->id, id) == 0 && is_same_scope_entry(existing)){
    yyerror("Symbol declared multiple times.");
    return -1;
  }

  return ST_insert(id, data_type, symbol_type, &scope_flag);
}

static symEntry* lookup_var(char *id){
  symEntry *entry = ST_lookup(id);
  if (!entry){
    if(callArgDepth == 0){ yyerror("Undeclared variable."); } // editted from prev version due to extra undeclared variable calls when testing.
    return NULL;
  }
  return entry;
}

static symEntry* lookup_func(char *id){
  symEntry *entry = ST_lookup(id);
  if (!entry || entry->symbol_type != FUNCTION){
    yyerror("Undefined function.");
    return NULL;
  }
  return entry;
}

static int id_for_ast(symEntry *entry){
    return get_symbol_index(entry);
}

static int combine_arithmetic_type(int lhs, int rhs){
  if(lhs == TYPE_ERROR || rhs == TYPE_ERROR){ return TYPE_ERROR; }
  if(lhs == rhs && lhs != VOID_TYPE) { return lhs; }
  return TYPE_ERROR;
}
static void set_expr(tree *n, int type, int scope, int val){
  n->type = type;
  n->scope = scope;
  n->val = val;
}

static int validate_func_call(symEntry *fn, tree *args){
  if (!fn) { return TYPE_ERROR; }

  int numArgsGiven = (args == NULL) ? 0 : args->numChildren;
  
  if(numArgsGiven < fn->size){
    yyerror("Too few arguments provided in function call.");
    return fn->data_type;
  }
  if(numArgsGiven > fn->size){
    yyerror("Too many arguments provided in function call.");
    return fn->data_type;
  }

  param *parameters = fn->params;
  for(int i = 0; i < numArgsGiven && parameters != NULL; i++){
    tree *arg = getChild(args, i);
    if (arg->type == TYPE_ERROR || arg->type != parameters->data_type){
      yyerror("Argument type mismatch in function call.");
      break;
    }
    parameters = parameters->next;
  }
  return fn->data_type;
  
}



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 147 "src/parser.y"
{
    int value;
    struct treenode *node;
    char *strval;
}
/* Line 193 of yacc.c.  */
#line 314 "obj/y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 327 "obj/y.tab.c"

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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   159

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  68
/* YYNRULES -- Number of states.  */
#define YYNSTATES  125

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
      35
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    12,    14,    18,    23,
      26,    28,    30,    32,    37,    43,    45,    49,    52,    57,
      61,    66,    67,    70,    71,    74,    76,    78,    80,    82,
      84,    87,    91,    96,   100,   106,   114,   120,   130,   133,
     137,   139,   144,   146,   150,   152,   154,   156,   158,   160,
     162,   164,   168,   170,   172,   174,   178,   180,   182,   186,
     188,   190,   192,   194,   195,   201,   202,   207,   209
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      37,     0,    -1,    38,    -1,    39,    -1,    38,    39,    -1,
      40,    -1,    43,    -1,    42,     3,    21,    -1,    42,     3,
      46,    21,    -1,    42,     3,    -1,     6,    -1,     7,    -1,
       8,    -1,    41,    18,    19,    47,    -1,    41,    18,    44,
      19,    47,    -1,    45,    -1,    44,    20,    45,    -1,    42,
       3,    -1,    42,     3,    14,    15,    -1,    14,     4,    15,
      -1,    16,    48,    49,    17,    -1,    -1,    40,    48,    -1,
      -1,    50,    49,    -1,    51,    -1,    52,    -1,    54,    -1,
      55,    -1,    56,    -1,    58,    21,    -1,    16,    49,    17,
      -1,    57,    28,    58,    21,    -1,    57,    28,    58,    -1,
      11,    18,    58,    19,    50,    -1,    11,    18,    58,    19,
      50,    12,    50,    -1,     9,    18,    58,    19,    50,    -1,
      13,    18,    53,    21,    58,    21,    53,    19,    50,    -1,
      10,    21,    -1,    10,    58,    21,    -1,     3,    -1,     3,
      14,    60,    15,    -1,    60,    -1,    58,    59,    60,    -1,
      22,    -1,    23,    -1,    25,    -1,    26,    -1,    27,    -1,
      29,    -1,    62,    -1,    60,    61,    62,    -1,    30,    -1,
      31,    -1,    64,    -1,    62,    63,    64,    -1,    32,    -1,
      24,    -1,    18,    58,    19,    -1,    57,    -1,    65,    -1,
       4,    -1,     5,    -1,    -1,     3,    18,    66,    68,    19,
      -1,    -1,     3,    18,    67,    19,    -1,    58,    -1,    68,
      20,    58,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   185,   185,   194,   200,   209,   214,   221,   229,   248,
     271,   275,   279,   285,   301,   319,   324,   332,   342,   354,
     362,   371,   374,   383,   386,   394,   399,   404,   409,   414,
     419,   426,   433,   443,   455,   461,   470,   476,   486,   490,
     497,   513,   534,   540,   556,   560,   564,   568,   572,   576,
     582,   588,   605,   609,   615,   621,   641,   645,   651,   657,
     663,   669,   675,   683,   683,   695,   695,   707,   712
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "INTCONST", "CHARCONST", "KWD_INT",
  "KWD_CHAR", "KWD_VOID", "KWD_WHILE", "KWD_RETURN", "KWD_IF", "KWD_ELSE",
  "KWD_FOR", "LSQ_BRKT", "RSQ_BRKT", "LCRLY_BRKT", "RCRLY_BRKT", "LPAREN",
  "RPAREN", "COMMA", "SEMICLN", "OPER_LTE", "OPER_LT", "OPER_DIV",
  "OPER_GT", "OPER_GTE", "OPER_EQ", "OPER_ASGN", "OPER_NEQ", "OPER_ADD",
  "OPER_SUB", "OPER_MUL", "ERROR", "ILLEGAL_TOK", "LOWER_THAN_ELSE",
  "$accept", "program", "declList", "decl", "varDecl", "funcTypeName",
  "typeSpecifier", "funDecl", "formalDeclList", "formalDecl", "arrayDecl",
  "funBody", "localDeclList", "statementList", "statement", "compoundStmt",
  "assignStmt", "forAssign", "condStmt", "loopStmt", "returnStmt", "var",
  "expression", "relop", "addExpr", "addop", "term", "mulop", "factor",
  "funCallExpr", "@1", "@2", "argList", 0
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
     285,   286,   287,   288,   289,   290
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    36,    37,    38,    38,    39,    39,    40,    40,    41,
      42,    42,    42,    43,    43,    44,    44,    45,    45,    46,
      47,    48,    48,    49,    49,    50,    50,    50,    50,    50,
      50,    51,    52,    53,    54,    54,    55,    55,    56,    56,
      57,    57,    58,    58,    59,    59,    59,    59,    59,    59,
      60,    60,    61,    61,    62,    62,    63,    63,    64,    64,
      64,    64,    64,    66,    65,    67,    65,    68,    68
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     3,     4,     2,
       1,     1,     1,     4,     5,     1,     3,     2,     4,     3,
       4,     0,     2,     0,     2,     1,     1,     1,     1,     1,
       2,     3,     4,     3,     5,     7,     5,     9,     2,     3,
       1,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     3,     1,     1,     3,     1,
       1,     1,     1,     0,     5,     0,     4,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    10,    11,    12,     0,     2,     3,     5,     0,     0,
       6,     1,     4,     0,     9,     0,     0,     0,    15,     0,
       7,     0,    21,    13,    17,     0,     0,     0,     8,    21,
       0,    23,     0,    14,    16,    19,    22,     0,    40,    61,
      62,     0,     0,     0,     0,    23,     0,     0,    23,    25,
      26,    27,    28,    29,    59,     0,    42,    50,    54,    60,
      18,     0,    63,     0,    38,    59,     0,     0,     0,     0,
       0,    20,    24,     0,    30,    44,    45,    46,    47,    48,
      49,     0,    52,    53,     0,    57,    56,     0,     0,     0,
       0,     0,    39,     0,    40,     0,     0,    31,    58,     0,
      43,    51,    55,    41,    67,     0,    66,     0,     0,     0,
       0,    32,    64,     0,    36,    34,     0,    33,    68,     0,
       0,    35,     0,     0,    37
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,     7,     8,     9,    10,    17,    18,
      21,    23,    31,    47,    48,    49,    50,    95,    51,    52,
      53,    65,    55,    81,    56,    84,    57,    87,    58,    59,
      89,    90,   105
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -89
static const yytype_int16 yypact[] =
{
      55,   -89,   -89,   -89,     4,    55,   -89,   -89,    20,    50,
     -89,   -89,   -89,    52,    -5,    51,    63,    31,   -89,    66,
     -89,    53,    55,   -89,    59,    51,    55,    65,   -89,    55,
      81,    36,    71,   -89,   -89,   -89,   -89,    -5,    16,   -89,
     -89,    80,     3,    83,    87,    36,    39,    93,    36,   -89,
     -89,   -89,   -89,   -89,    91,    86,    25,     1,   -89,   -89,
     -89,    39,   109,    39,   -89,   -89,    95,    39,   111,   106,
      56,   -89,   -89,    39,   -89,   -89,   -89,   -89,   -89,   -89,
     -89,    39,   -89,   -89,    39,   -89,   -89,    39,    -3,    39,
     118,    68,   -89,    77,   127,   124,   123,   -89,   -89,   104,
      25,     1,   -89,   -89,   121,    45,   -89,    36,    36,    39,
      39,   -89,   -89,    39,   -89,   120,   113,   121,   121,    36,
     111,   -89,   130,    36,   -89
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -89,   -89,   -89,   147,     7,   -89,   -11,   -89,   -89,   128,
     -89,   131,   126,   -35,   -88,   -89,   -89,    33,   -89,   -89,
     -89,   -31,   -41,   -89,   -58,   -89,    73,   -89,    72,   -89,
     -89,   -89,   -89
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -66
static const yytype_int8 yytable[] =
{
      54,    66,    16,    88,    11,    70,    38,    39,    40,    19,
      69,    30,   103,    72,    54,    16,    20,    54,    30,   114,
     115,    46,    91,   100,    64,    85,    93,    82,    83,    29,
      61,   121,    99,    86,    62,   124,    29,    96,    13,    38,
      39,    40,    38,    39,    40,    41,    42,    43,   104,    44,
      25,    26,    45,    14,    46,    82,    83,    46,     1,     2,
       3,     1,     2,     3,   112,   113,    24,    22,   116,   117,
      27,    15,   118,    32,    28,    98,    54,    54,    75,    76,
      35,    77,    78,    79,    37,    80,    60,   107,    54,    96,
      75,    76,    54,    77,    78,    79,   108,    80,    63,    75,
      76,    67,    77,    78,    79,    68,    80,    74,    75,    76,
      71,    77,    78,    79,    94,    80,    92,    75,    76,    73,
      77,    78,    79,    97,    80,   111,    75,    76,   -65,    77,
      78,    79,   119,    80,   120,    75,    76,   106,    77,    78,
      79,    61,    80,    75,    76,   109,    77,    78,    79,   123,
      80,   110,    12,   122,    34,    36,    33,   101,     0,   102
};

static const yytype_int8 yycheck[] =
{
      31,    42,    13,    61,     0,    46,     3,     4,     5,    14,
      45,    22,    15,    48,    45,    26,    21,    48,    29,   107,
     108,    18,    63,    81,    21,    24,    67,    30,    31,    22,
      14,   119,    73,    32,    18,   123,    29,    68,    18,     3,
       4,     5,     3,     4,     5,     9,    10,    11,    89,    13,
      19,    20,    16,     3,    18,    30,    31,    18,     6,     7,
       8,     6,     7,     8,    19,    20,     3,    16,   109,   110,
       4,    19,   113,    14,    21,    19,   107,   108,    22,    23,
      15,    25,    26,    27,     3,    29,    15,    19,   119,   120,
      22,    23,   123,    25,    26,    27,    19,    29,    18,    22,
      23,    18,    25,    26,    27,    18,    29,    21,    22,    23,
      17,    25,    26,    27,     3,    29,    21,    22,    23,    28,
      25,    26,    27,    17,    29,    21,    22,    23,    19,    25,
      26,    27,    12,    29,    21,    22,    23,    19,    25,    26,
      27,    14,    29,    22,    23,    21,    25,    26,    27,    19,
      29,    28,     5,   120,    26,    29,    25,    84,    -1,    87
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,     7,     8,    37,    38,    39,    40,    41,    42,
      43,     0,    39,    18,     3,    19,    42,    44,    45,    14,
      21,    46,    16,    47,     3,    19,    20,     4,    21,    40,
      42,    48,    14,    47,    45,    15,    48,     3,     3,     4,
       5,     9,    10,    11,    13,    16,    18,    49,    50,    51,
      52,    54,    55,    56,    57,    58,    60,    62,    64,    65,
      15,    14,    18,    18,    21,    57,    58,    18,    18,    49,
      58,    17,    49,    28,    21,    22,    23,    25,    26,    27,
      29,    59,    30,    31,    61,    24,    32,    63,    60,    66,
      67,    58,    21,    58,     3,    53,    57,    17,    19,    58,
      60,    62,    64,    15,    58,    68,    19,    19,    19,    21,
      28,    21,    19,    20,    50,    50,    58,    58,    58,    12,
      21,    50,    53,    19,    50
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
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
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
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
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


/* Prevent warnings from -Wmissing-prototypes.  */

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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

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
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
        case 2:
#line 186 "src/parser.y"
    {
                    tree *progNode = maketree(PROGRAM);
                    addChild(progNode, (yyvsp[(1) - (1)].node));
                    (yyval.node) = progNode;
                    ast = progNode;
                 }
    break;

  case 3:
#line 195 "src/parser.y"
    {
                    tree* declListNode = maketree(DECLLIST);
                    addChild(declListNode, (yyvsp[(1) - (1)].node));
                    (yyval.node) = declListNode;
                 }
    break;

  case 4:
#line 201 "src/parser.y"
    {
                    tree* declListNode = maketree(DECLLIST);
                    addChild(declListNode, (yyvsp[(1) - (2)].node));
                    addChild(declListNode, (yyvsp[(2) - (2)].node));
                    (yyval.node) = declListNode;
                 }
    break;

  case 5:
#line 210 "src/parser.y"
    {
                    (yyval.node) = maketree(DECL);
                    addChild((yyval.node), (yyvsp[(1) - (1)].node));
                 }
    break;

  case 6:
#line 215 "src/parser.y"
    {
                    (yyval.node) = maketree(DECL);
                    addChild((yyval.node), (yyvsp[(1) - (1)].node));
                 }
    break;

  case 7:
#line 222 "src/parser.y"
    {
                    tree *varDeclNode = maketree(VARDECL);
                    int idx = insert_decl((yyvsp[(2) - (3)].strval), (yyvsp[(1) - (3)].node)->val, SCALAR);
                    addChild(varDeclNode, (yyvsp[(1) - (3)].node));
                    addChild(varDeclNode, maketreeWithVal(IDENTIFIER, idx));
                    (yyval.node) = varDeclNode;
                 }
    break;

  case 8:
#line 230 "src/parser.y"
    {
                    tree *varDeclNode = maketree(VARDECL);
                    int idx = insert_decl((yyvsp[(2) - (4)].strval), (yyvsp[(1) - (4)].node)->val, ARRAY);

                    if((yyvsp[(3) - (4)].node)->val == 0){ yyerror("Array variable declared with size of zero."); }

                    addChild(varDeclNode, (yyvsp[(1) - (4)].node));
                    addChild(varDeclNode, maketreeWithVal(IDENTIFIER, idx));
                    addChild(varDeclNode, (yyvsp[(3) - (4)].node));
                    (yyval.node) = varDeclNode;

                    symEntry *arr = ST_lookup((yyvsp[(2) - (4)].strval));
                    if (arr && arr->symbol_type == ARRAY && is_same_scope_entry(arr)){
                      arr->size = (yyvsp[(3) - (4)].node)->val;
                    }
                 }
    break;

  case 9:
#line 249 "src/parser.y"
    {
                    int idx = insert_decl((yyvsp[(2) - (2)].strval), (yyvsp[(1) - (2)].node)->val, FUNCTION);

                    strncpy(current_function, (yyvsp[(2) - (2)].strval), sizeof(current_function)-1);
                    current_function[sizeof(current_function)-1] = '\0';
                    strncpy(currFunction, current_function, sizeof(currFunction)-1);
                    currFunction[sizeof(currFunction)-1] = '\0';
                    scope = current_function;

                    pending_func_index = idx;
                    pending_param_count = 0;
                    working_list_head = NULL;
                    working_list_end = NULL;

                    new_scope();

                    (yyval.node) = maketree(FUNCTYPENAME);
                    addChild((yyval.node), (yyvsp[(1) - (2)].node));
                    addChild((yyval.node), maketreeWithVal(IDENTIFIER, idx));
                 }
    break;

  case 10:
#line 272 "src/parser.y"
    {
                    (yyval.node) = maketreeWithVal(TYPESPEC, INT_TYPE);
                 }
    break;

  case 11:
#line 276 "src/parser.y"
    {
                    (yyval.node) = maketreeWithVal(TYPESPEC, CHAR_TYPE);
                 }
    break;

  case 12:
#line 280 "src/parser.y"
    {
                    (yyval.node) = maketreeWithVal(TYPESPEC, VOID_TYPE);
                 }
    break;

  case 13:
#line 286 "src/parser.y"
    {
                    tree *funDeclNode = maketree(FUNDECL);
                    
                    addChild(funDeclNode, (yyvsp[(1) - (4)].node));
                    addChild(funDeclNode, (yyvsp[(4) - (4)].node));

                    connect_params(pending_func_index, 0);
                    up_scope();

                    current_function[0] = '\0';
                    currFunction[0] = '\0';
                    scope = "";

                    (yyval.node) = funDeclNode;
                 }
    break;

  case 14:
#line 302 "src/parser.y"
    {
                    tree *funDeclNode = maketree(FUNDECL);
                    addChild(funDeclNode, (yyvsp[(1) - (5)].node));
                    addChild(funDeclNode, (yyvsp[(3) - (5)].node));
                    addChild(funDeclNode, (yyvsp[(5) - (5)].node));

                    connect_params(pending_func_index, pending_param_count);
                    up_scope();

                    current_function[0] = '\0';
                    currFunction[0] = '\0';
                    scope = "";

                    (yyval.node) = funDeclNode;
                 }
    break;

  case 15:
#line 320 "src/parser.y"
    {
                    (yyval.node) = maketree(FORMALDECLLIST);
                    addChild((yyval.node), (yyvsp[(1) - (1)].node));
                 }
    break;

  case 16:
#line 325 "src/parser.y"
    {
                    (yyval.node) = maketree(FORMALDECLLIST);
                    addChild((yyval.node), (yyvsp[(1) - (3)].node));
                    addChild((yyval.node), (yyvsp[(3) - (3)].node));
                 }
    break;

  case 17:
#line 333 "src/parser.y"
    {
                    int idx = insert_decl((yyvsp[(2) - (2)].strval), (yyvsp[(1) - (2)].node)->val, SCALAR);
                    pending_param_count++;
                    add_param((yyvsp[(1) - (2)].node)->val, SCALAR);

                    (yyval.node) = maketree(FORMALDECL);
                    addChild((yyval.node), (yyvsp[(1) - (2)].node));
                    addChild((yyval.node), maketreeWithVal(IDENTIFIER, idx));
                 }
    break;

  case 18:
#line 343 "src/parser.y"
    {
                    int idx = insert_decl((yyvsp[(2) - (4)].strval), (yyvsp[(1) - (4)].node)->val, ARRAY);
                    pending_param_count++;
                    add_param((yyvsp[(1) - (4)].node)->val, ARRAY);

                    (yyval.node) = maketree(FORMALDECL);
                    addChild((yyval.node), (yyvsp[(1) - (4)].node));
                    addChild((yyval.node), maketreeWithVal(IDENTIFIER, idx));
                 }
    break;

  case 19:
#line 355 "src/parser.y"
    {
                    (yyval.node) = maketree(ARRAYDECL);
                    (yyval.node)->val = (yyvsp[(2) - (3)].value);
                    addChild((yyval.node), maketreeWithVal(INTEGER, (yyvsp[(2) - (3)].value)));
                 }
    break;

  case 20:
#line 363 "src/parser.y"
    {
                    (yyval.node) = maketree(FUNBODY);
                    addChild((yyval.node), (yyvsp[(2) - (4)].node));
                    addChild((yyval.node), (yyvsp[(3) - (4)].node));
                 }
    break;

  case 21:
#line 371 "src/parser.y"
    {
                    (yyval.node) = maketree(LOCALDECLLIST);
                  }
    break;

  case 22:
#line 375 "src/parser.y"
    {
                    (yyval.node) = maketree(LOCALDECLLIST);
                    addChild((yyval.node), (yyvsp[(1) - (2)].node));
                    addChild((yyval.node), (yyvsp[(2) - (2)].node));
                  }
    break;

  case 23:
#line 383 "src/parser.y"
    {
                    (yyval.node) = maketree(STATEMENTLIST);
                  }
    break;

  case 24:
#line 387 "src/parser.y"
    {
                    (yyval.node) = maketree(STATEMENTLIST);
                    addChild((yyval.node), (yyvsp[(1) - (2)].node));
                    addChild((yyval.node), (yyvsp[(2) - (2)].node));
                  }
    break;

  case 25:
#line 395 "src/parser.y"
    {
                    (yyval.node) = maketree(STATEMENT);
                    addChild((yyval.node), (yyvsp[(1) - (1)].node));
                  }
    break;

  case 26:
#line 400 "src/parser.y"
    {
                    (yyval.node) = maketree(STATEMENT);
                    addChild((yyval.node), (yyvsp[(1) - (1)].node));
                  }
    break;

  case 27:
#line 405 "src/parser.y"
    {
                    (yyval.node) = maketree(STATEMENT);
                    addChild((yyval.node), (yyvsp[(1) - (1)].node));
                  }
    break;

  case 28:
#line 410 "src/parser.y"
    {
                    (yyval.node) = maketree(STATEMENT);
                    addChild((yyval.node), (yyvsp[(1) - (1)].node));
                  }
    break;

  case 29:
#line 415 "src/parser.y"
    {
                    (yyval.node) = maketree(STATEMENT);
                    addChild((yyval.node), (yyvsp[(1) - (1)].node));
                  }
    break;

  case 30:
#line 420 "src/parser.y"
    {
                    (yyval.node) = maketree(STATEMENT);
                    addChild((yyval.node), (yyvsp[(1) - (2)].node));
                  }
    break;

  case 31:
#line 427 "src/parser.y"
    {
                    (yyval.node) = maketree(COMPOUNDSTMT);
                    addChild((yyval.node), (yyvsp[(2) - (3)].node));
                  }
    break;

  case 32:
#line 434 "src/parser.y"
    {
                    (yyval.node) = maketree(ASSIGNSTMT);
                    addChild((yyval.node), (yyvsp[(1) - (4)].node));
                    addChild((yyval.node), (yyvsp[(3) - (4)].node));

                    if((yyvsp[(1) - (4)].node)->type == TYPE_ERROR || (yyvsp[(3) - (4)].node)->type == TYPE_ERROR || (yyvsp[(1) - (4)].node)->type != (yyvsp[(3) - (4)].node)->type){ yyerror("Type mismatch in assignment."); }
                  }
    break;

  case 33:
#line 444 "src/parser.y"
    {
                    (yyval.node) = maketree(ASSIGNSTMT);
                    addChild((yyval.node), (yyvsp[(1) - (3)].node));
                    addChild((yyval.node), (yyvsp[(3) - (3)].node));

                    if((yyvsp[(1) - (3)].node)->type == TYPE_ERROR || (yyvsp[(3) - (3)].node)->type == TYPE_ERROR || (yyvsp[(1) - (3)].node)->type != (yyvsp[(3) - (3)].node)->type){
                      yyerror("Type Mismatch in assignment.");
                    }
                  }
    break;

  case 34:
#line 456 "src/parser.y"
    {
                    (yyval.node) = maketree(CONDSTMT);
                    addChild((yyval.node), (yyvsp[(3) - (5)].node));
                    addChild((yyval.node), (yyvsp[(5) - (5)].node));
                  }
    break;

  case 35:
#line 462 "src/parser.y"
    {
                    (yyval.node) = maketree(CONDSTMT);
                    addChild((yyval.node), (yyvsp[(3) - (7)].node));
                    addChild((yyval.node), (yyvsp[(5) - (7)].node));
                    addChild((yyval.node), (yyvsp[(7) - (7)].node));
                  }
    break;

  case 36:
#line 471 "src/parser.y"
    {
                    (yyval.node) = maketree(LOOPSTMT);
                    addChild((yyval.node), (yyvsp[(3) - (5)].node));
                    addChild((yyval.node), (yyvsp[(5) - (5)].node));
                  }
    break;

  case 37:
#line 477 "src/parser.y"
    {
                    (yyval.node) = maketree(LOOPSTMT);
                    addChild((yyval.node), (yyvsp[(3) - (9)].node));
                    addChild((yyval.node), (yyvsp[(5) - (9)].node));
                    addChild((yyval.node), (yyvsp[(7) - (9)].node));
                    addChild((yyval.node), (yyvsp[(9) - (9)].node));
                  }
    break;

  case 38:
#line 487 "src/parser.y"
    {
                    (yyval.node) = maketree(RETURNSTMT);
                  }
    break;

  case 39:
#line 491 "src/parser.y"
    {
                    (yyval.node) = maketree(RETURNSTMT);
                    addChild((yyval.node), (yyvsp[(2) - (3)].node));
                  }
    break;

  case 40:
#line 498 "src/parser.y"
    {
                    symEntry *entry = lookup_var((yyvsp[(1) - (1)].strval));

                    (yyval.node) = maketree(VAR);
                    addChild((yyval.node), maketreeWithVal(IDENTIFIER, id_for_ast(entry)));

                    if(entry){
                      (yyval.node)->type = entry->data_type;
                      (yyval.node)->sym_type = entry->symbol_type;
                    }
                    else{
                      (yyval.node)->type = TYPE_ERROR;
                      (yyval.node)->sym_type = SCALAR;
                    }
                  }
    break;

  case 41:
#line 514 "src/parser.y"
    {
                    symEntry *entry = lookup_var((yyvsp[(1) - (4)].strval));

                    (yyval.node) = maketree(VAR);
                    addChild((yyval.node), maketreeWithVal(IDENTIFIER, id_for_ast(entry)));
                    addChild((yyval.node), (yyvsp[(3) - (4)].node));

                    if(!entry){ (yyval.node)->type = TYPE_ERROR; (yyval.node)->sym_type = SCALAR; }
                    else{
                      if(entry->symbol_type != ARRAY){ yyerror("Non-array identifier used as an array."); }
                      if((yyvsp[(3) - (4)].node)->type != INT_TYPE){ yyerror("Array indexed using non-integer expression."); }
                      if(entry->symbol_type == ARRAY && entry->size > 0 && (yyvsp[(3) - (4)].node)->scope == 1){
                        if((yyvsp[(3) - (4)].node)->val < 0 || (yyvsp[(3) - (4)].node)->val >= entry->size){ yyerror("Statically sized array indexed with constant, out-of-bounds expression."); }
                      }
                      (yyval.node)->type = entry->data_type;
                      (yyval.node)->sym_type = SCALAR;
                    }
                  }
    break;

  case 42:
#line 535 "src/parser.y"
    {
                    (yyval.node) = maketree(EXPRESSION);
                    addChild((yyval.node), (yyvsp[(1) - (1)].node));
                    set_expr((yyval.node), (yyvsp[(1) - (1)].node)->type, (yyvsp[(1) - (1)].node)->scope, (yyvsp[(1) - (1)].node)->val);
                  }
    break;

  case 43:
#line 541 "src/parser.y"
    {
                    (yyval.node) = maketree(EXPRESSION);
                    addChild((yyval.node), (yyvsp[(1) - (3)].node));
                    addChild((yyval.node), (yyvsp[(2) - (3)].node));
                    addChild((yyval.node), (yyvsp[(3) - (3)].node));

                    if((yyvsp[(1) - (3)].node)->type == TYPE_ERROR || (yyvsp[(3) - (3)].node)->type == TYPE_ERROR || (yyvsp[(1) - (3)].node)->type == VOID_TYPE || (yyvsp[(3) - (3)].node)->type == VOID_TYPE || (yyvsp[(1) - (3)].node)->type != (yyvsp[(3) - (3)].node)->type){
                      set_expr((yyval.node), TYPE_ERROR, 0, 0);
                    }
                    else{
                      set_expr((yyval.node), INT_TYPE, 0 ,0);
                    }
                  }
    break;

  case 44:
#line 557 "src/parser.y"
    {
                    (yyval.node) = maketreeWithVal(RELOP, LTE);
                  }
    break;

  case 45:
#line 561 "src/parser.y"
    {
                    (yyval.node) = maketreeWithVal(RELOP, LT);
                  }
    break;

  case 46:
#line 565 "src/parser.y"
    {
                    (yyval.node) = maketreeWithVal(RELOP, GT);
                  }
    break;

  case 47:
#line 569 "src/parser.y"
    {
                    (yyval.node) = maketreeWithVal(RELOP, GTE);
                  }
    break;

  case 48:
#line 573 "src/parser.y"
    {
                    (yyval.node) = maketreeWithVal(RELOP, EQ);
                  }
    break;

  case 49:
#line 577 "src/parser.y"
    {
                    (yyval.node) = maketreeWithVal(RELOP, NEQ);
                  }
    break;

  case 50:
#line 583 "src/parser.y"
    {
                    (yyval.node) = maketree(ADDEXPR);
                    addChild((yyval.node), (yyvsp[(1) - (1)].node));
                    set_expr((yyval.node), (yyvsp[(1) - (1)].node)->type, (yyvsp[(1) - (1)].node)->scope, (yyvsp[(1) - (1)].node)->val);
                  }
    break;

  case 51:
#line 589 "src/parser.y"
    { 
                    (yyval.node) = maketree(ADDEXPR);
                    addChild((yyval.node), (yyvsp[(1) - (3)].node));
                    addChild((yyval.node), (yyvsp[(2) - (3)].node));
                    addChild((yyval.node), (yyvsp[(3) - (3)].node));

                    int typ = combine_arithmetic_type((yyvsp[(1) - (3)].node)->type, (yyvsp[(3) - (3)].node)->type);
                    if(typ == TYPE_ERROR){ set_expr((yyval.node), TYPE_ERROR, 0, 0); }
                    else if((yyvsp[(1) - (3)].node)->scope == 1 && (yyvsp[(3) - (3)].node)->scope == 1){ 
                      int vl = ((yyvsp[(2) - (3)].node)->val == ADD) ? ((yyvsp[(1) - (3)].node)->val + (yyvsp[(3) - (3)].node)->val) : ((yyvsp[(1) - (3)].node)->val - (yyvsp[(3) - (3)].node)->val); 
                      set_expr((yyval.node), typ, 1, vl);
                    }
                    else{ set_expr((yyval.node), typ, 0, 0); }
                  }
    break;

  case 52:
#line 606 "src/parser.y"
    {
                    (yyval.node) = maketreeWithVal(ADDOP, ADD);
                  }
    break;

  case 53:
#line 610 "src/parser.y"
    {
                    (yyval.node) = maketreeWithVal(ADDOP, SUB);
                  }
    break;

  case 54:
#line 616 "src/parser.y"
    {
                    (yyval.node) = maketree(TERM);
                    addChild((yyval.node), (yyvsp[(1) - (1)].node));
                    set_expr((yyval.node), (yyvsp[(1) - (1)].node)->type, (yyvsp[(1) - (1)].node)->scope, (yyvsp[(1) - (1)].node)->val);
                  }
    break;

  case 55:
#line 622 "src/parser.y"
    {
                    (yyval.node) = maketree(TERM);
                    addChild((yyval.node), (yyvsp[(1) - (3)].node));
                    addChild((yyval.node), (yyvsp[(2) - (3)].node));
                    addChild((yyval.node), (yyvsp[(3) - (3)].node));

                    int typ = combine_arithmetic_type((yyvsp[(1) - (3)].node)->type, (yyvsp[(3) - (3)].node)->type);
                    if(typ == TYPE_ERROR){ set_expr((yyval.node), TYPE_ERROR, 0, 0); }
                    else if((yyvsp[(1) - (3)].node)->scope == 1 && (yyvsp[(3) - (3)].node)->scope == 1){
                      if((yyvsp[(2) - (3)].node)->val == MUL){ set_expr((yyval.node), typ, 1, (yyvsp[(1) - (3)].node)->val * (yyvsp[(3) - (3)].node)->val); }
                      else{
                        if((yyvsp[(3) - (3)].node)->val == 0){ set_expr((yyval.node), typ, 0, 0); }
                        else { set_expr((yyval.node), typ, 1, (yyvsp[(1) - (3)].node)->val / (yyvsp[(3) - (3)].node)->val); }
                      }
                    }
                    else{ set_expr((yyval.node), typ, 0, 0);}
                  }
    break;

  case 56:
#line 642 "src/parser.y"
    {
                    (yyval.node) = maketreeWithVal(MULOP, MUL);
                  }
    break;

  case 57:
#line 646 "src/parser.y"
    {
                    (yyval.node) = maketreeWithVal(MULOP, DIV);
                  }
    break;

  case 58:
#line 652 "src/parser.y"
    {
                    (yyval.node) = maketree(FACTOR);
                    addChild((yyval.node), (yyvsp[(2) - (3)].node));
                    set_expr((yyval.node), (yyvsp[(2) - (3)].node)->type, (yyvsp[(2) - (3)].node)->scope, (yyvsp[(2) - (3)].node)->val);
                  }
    break;

  case 59:
#line 658 "src/parser.y"
    {
                    (yyval.node) = maketree(FACTOR);
                    addChild((yyval.node), (yyvsp[(1) - (1)].node));
                    set_expr((yyval.node), (yyvsp[(1) - (1)].node)->type, 0, 0);
                  }
    break;

  case 60:
#line 664 "src/parser.y"
    {
                    (yyval.node) = maketree(FACTOR);
                    addChild((yyval.node), (yyvsp[(1) - (1)].node));
                    set_expr((yyval.node), (yyvsp[(1) - (1)].node)->type, 0, 0);
                  }
    break;

  case 61:
#line 670 "src/parser.y"
    {
                    (yyval.node) = maketree(FACTOR);
                    addChild((yyval.node), maketreeWithVal(INTEGER, (yyvsp[(1) - (1)].value)));
                    set_expr((yyval.node), INT_TYPE, 1, (yyvsp[(1) - (1)].value));
                  }
    break;

  case 62:
#line 676 "src/parser.y"
    {
                    (yyval.node) = maketree(FACTOR);
                    addChild((yyval.node), maketreeWithVal(CHAR, (yyvsp[(1) - (1)].value)));
                    set_expr((yyval.node), CHAR_TYPE, 1, (yyvsp[(1) - (1)].value));
                  }
    break;

  case 63:
#line 683 "src/parser.y"
    { callArgDepth++; }
    break;

  case 64:
#line 684 "src/parser.y"
    {
                    callArgDepth--;

                    symEntry *fn = lookup_func((yyvsp[(1) - (5)].strval));

                    (yyval.node) = maketree(FUNCCALLEXPR);
                    addChild((yyval.node), maketreeWithVal(IDENTIFIER, id_for_ast(fn)));
                    addChild((yyval.node), (yyvsp[(4) - (5)].node));

                    (yyval.node)->type = validate_func_call(fn, (yyvsp[(4) - (5)].node));
                  }
    break;

  case 65:
#line 695 "src/parser.y"
    { callArgDepth++; }
    break;

  case 66:
#line 696 "src/parser.y"
    {
                    callArgDepth--;
                    symEntry *fn = lookup_func((yyvsp[(1) - (4)].strval));

                    (yyval.node) = maketree(FUNCCALLEXPR);
                    addChild((yyval.node), maketreeWithVal(IDENTIFIER, id_for_ast(fn)));

                    (yyval.node)->type = validate_func_call(fn, NULL);
                  }
    break;

  case 67:
#line 708 "src/parser.y"
    {
                    (yyval.node) = maketree(ARGLIST);
                    addChild((yyval.node), (yyvsp[(1) - (1)].node));
                  }
    break;

  case 68:
#line 713 "src/parser.y"
    {
                    (yyval.node) = (yyvsp[(1) - (3)].node);
                    addChild((yyval.node), (yyvsp[(3) - (3)].node));
                  }
    break;


/* Line 1267 of yacc.c.  */
#line 2319 "obj/y.tab.c"
      default: break;
    }
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
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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
      if (yyn != YYPACT_NINF)
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

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
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


#line 719 "src/parser.y"
 
int yywarning(char *msg){
  printf("warning: line %d: %s\n", yylineno, msg);
  return 0;
}

int yyerror(char * msg){
  printf("error: line %d: %s\n", yylineno, msg);
  return 0;
}

