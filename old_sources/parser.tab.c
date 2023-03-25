/* A Bison parser, made from parser.y
   by GNU bison 1.35.  */

#define YYBISON 1  /* Identify Bison output.  */

# define	SYMBOL	257
# define	RULE	258
# define	NET	259
# define	CUT	260
# define	LEFT_CUT	261
# define	ARITY_ID	262
# define	COLOR_ID	263
# define	ID	264

#line 7 "parser.y"


// INCLUDES ======================================================================

#include <gtk/gtk.h>
#include <glib.h>
#include "types.h"
#include "utility.h"


// STATIC FUNCTION PROTOTYPES ====================================================
	
static gboolean
are_symbol_labels_different(gconstpointer symbol, gconstpointer label);
static gboolean
are_cell_labels_different(gconstpointer cell, gconstpointer label);

static int yyerror(gchar *s);
static Symbol *create_void_symbol(gchar *label);
static Symbol *fill_in_symbol(Symbol *symbol, GdkColor *colorPtr, Arity arity);
static Cell *get_cell_or_variable(gchar *label);
static Cell *create_void_cell(Symbol *symbol);
static Cell *get_variable(gchar *l);
static Cell *create_void_variable(gchar *label);
static Cut *connect_principal_ports(Cell *cell1, Cell *cell2);
static gboolean isCutBetweenCells(Port *port1, Port *port2);
static GSList *remove_variable_list(GSList *list);
static void remove_one_variable(gpointer data, gpointer usr_data);
static Cell *allocate_and_connect_auxiliary_ports(Cell *cell, GSList *list);
static Cell *allocate_port_table(Cell *cell, Arity arity);
static Cell *connect_auxiliary_ports(Cell *root, GSList *subTreeList);
static Cell *create_interface_cell(void);
static gchar **create_free_port_label_table(void);
static Rule *create_rule(Cell *cell1, Cell *cell2);


// STATIC GLOBAL VARIABLES =======================================================

static GSList *freeVariableList = NULL;
static GSList *boundVariableList = NULL;


// EXTERN GLOBAL VARIABLES =======================================================

extern System *iSystem;



#line 58 "parser.y"
#ifndef YYSTYPE
typedef union
{
	gchar		*string;
	Arity		arity;
	Symbol		*symbolPtr;
	GdkColor	*colorPtr;
	Cell		*cellPtr;
	Cut			*cutPtr;
	Rule		*rulePtr;
	GSList		*list;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
#ifndef YYDEBUG
# define YYDEBUG 0
#endif



#define	YYFINAL		50
#define	YYFLAG		-32768
#define	YYNTBASE	16

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 264 ? yytranslate[x] : 35)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      11,    12,     2,     2,    13,     2,    15,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    14,     2,
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
       2,     2,     2,     2,     2,     2,     1,     3,     4,     5,
       6,     7,     8,     9,    10
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    24,    26,    31,    33,    37,    40,    41,    44,    50,
      54,    57,    58,    61,    65,    71,    75,    78,    79
};
static const short yyrhs[] =
{
      26,    29,    33,     0,     8,     0,     9,     0,    10,     0,
      17,     0,    17,     0,     9,     0,     8,     0,    17,     0,
      24,     6,    24,     0,    22,     0,    22,    11,    25,    12,
       0,    24,     0,    25,    13,    24,     0,     3,    27,     0,
       0,    27,    28,     0,    18,    13,    20,    14,    21,     0,
      18,    14,    21,     0,     4,    30,     0,     0,    31,    30,
       0,    32,    34,    15,     0,    32,    34,    13,    19,    15,
       0,    24,     7,    24,     0,     5,    34,     0,     0,    34,
      23,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   108,   114,   114,   114,   116,   118,   120,   122,   124,
     130,   132,   134,   140,   142,   148,   154,   156,   158,   160,
     166,   172,   174,   176,   186,   195,   204,   218,   220
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "SYMBOL", "RULE", "NET", "CUT", "LEFT_CUT", 
  "ARITY_ID", "COLOR_ID", "ID", "'('", "')'", "','", "':'", "'.'", 
  "system", "id", "symbol_id", "sound_id", "color_id", "arity_id", 
  "cell_id", "cut", "tree", "tree_seq1", "symbol_section", 
  "symbol_decl_seq", "symbol_decl", "rule_section", "rule_seq", "rule", 
  "rule_left_member", "net_section", "cut_seq", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    16,    17,    17,    17,    18,    19,    20,    21,    22,
      23,    24,    24,    25,    25,    26,    27,    27,    28,    28,
      29,    30,    30,    31,    31,    32,    33,    34,    34
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     4,     1,     3,     2,     0,     2,     5,     3,
       2,     0,     2,     3,     5,     3,     2,     0,     2
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       0,    16,     0,    15,    21,     0,     2,     3,     4,     5,
       0,    17,     9,    11,     0,    20,    21,    27,    27,     1,
       0,     0,     0,     0,    22,     0,    26,     7,     0,     8,
      19,    13,     0,    25,     0,    23,    28,     0,     0,    12,
       0,     6,     0,     0,    18,    14,    24,    10,     0,     0,
       0
};

static const short yydefgoto[] =
{
      48,    12,    10,    42,    28,    30,    13,    36,    14,    32,
       2,     3,    11,     5,    15,    16,    17,    19,    25
};

static const short yypact[] =
{
       0,-32768,     8,     6,     6,    15,-32768,-32768,-32768,-32768,
      -4,-32768,-32768,    10,    16,-32768,     6,-32768,-32768,-32768,
      17,    19,     6,     6,-32768,    -2,     6,-32768,    11,-32768,
  -32768,-32768,     5,-32768,     6,-32768,-32768,    18,    19,-32768,
       6,-32768,    13,     6,-32768,-32768,-32768,-32768,    29,    30,
  -32768
};

static const short yypgoto[] =
{
  -32768,    -3,-32768,-32768,-32768,    -6,-32768,-32768,   -21,-32768,
  -32768,-32768,-32768,-32768,    20,-32768,-32768,-32768,    21
};


#define	YYLAST		39


static const short yytable[] =
{
       9,    31,    33,     1,    37,    37,     6,     7,     8,    20,
      21,    34,     4,    35,     6,     7,     8,    39,    40,    45,
      18,    22,    47,    23,    43,    38,    27,    29,    46,    49,
      50,    41,    44,     0,     0,     0,    24,     0,     0,    26
};

static const short yycheck[] =
{
       3,    22,    23,     3,    25,    26,     8,     9,    10,    13,
      14,    13,     4,    15,     8,     9,    10,    12,    13,    40,
       5,    11,    43,     7,     6,    14,     9,     8,    15,     0,
       0,    34,    38,    -1,    -1,    -1,    16,    -1,    -1,    18
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/share/bison/bison.simple"

/* Skeleton output parser for bison,

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software
   Foundation, Inc.

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
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser when
   the %semantic_parser declaration is not specified in the grammar.
   It was written by Richard Stallman by simplifying the hairy parser
   used when %semantic_parser is specified.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

#if ! defined (yyoverflow) || defined (YYERROR_VERBOSE)

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || defined (YYERROR_VERBOSE) */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYLTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
# if YYLSP_NEEDED
  YYLTYPE yyls;
# endif
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAX (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# if YYLSP_NEEDED
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
      + 2 * YYSTACK_GAP_MAX)
# else
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAX)
# endif

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
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
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAX;	\
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif


#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
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
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");			\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).

   When YYLLOC_DEFAULT is run, CURRENT is set the location of the
   first token.  By default, to implement support for ranges, extend
   its range to the last symbol.  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)       	\
   Current.last_line   = Rhs[N].last_line;	\
   Current.last_column = Rhs[N].last_column;
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#if YYPURE
# if YYLSP_NEEDED
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, &yylloc, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval, &yylloc)
#  endif
# else /* !YYLSP_NEEDED */
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval)
#  endif
# endif /* !YYLSP_NEEDED */
#else /* !YYPURE */
# define YYLEX			yylex ()
#endif /* !YYPURE */


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
} while (0)
/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

#ifdef YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif
#endif

#line 315 "/usr/share/bison/bison.simple"


/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
#  define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL
# else
#  define YYPARSE_PARAM_ARG YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
# endif
#else /* !YYPARSE_PARAM */
# define YYPARSE_PARAM_ARG
# define YYPARSE_PARAM_DECL
#endif /* !YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
# ifdef YYPARSE_PARAM
int yyparse (void *);
# else
int yyparse (void);
# endif
#endif

/* YY_DECL_VARIABLES -- depending whether we use a pure parser,
   variables are global, or local to YYPARSE.  */

#define YY_DECL_NON_LSP_VARIABLES			\
/* The lookahead symbol.  */				\
int yychar;						\
							\
/* The semantic value of the lookahead symbol. */	\
YYSTYPE yylval;						\
							\
/* Number of parse errors so far.  */			\
int yynerrs;

#if YYLSP_NEEDED
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES			\
						\
/* Location data for the lookahead symbol.  */	\
YYLTYPE yylloc;
#else
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES
#endif


/* If nonreentrant, generate the variables here. */

#if !YYPURE
YY_DECL_VARIABLES
#endif  /* !YYPURE */

int
yyparse (YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  /* If reentrant, generate the variables here. */
#if YYPURE
  YY_DECL_VARIABLES
#endif  /* !YYPURE */

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yychar1 = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack. */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;

#if YYLSP_NEEDED
  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
#endif

#if YYLSP_NEEDED
# define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
# define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  YYSIZE_T yystacksize = YYINITDEPTH;


  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
#if YYLSP_NEEDED
  YYLTYPE yyloc;
#endif

  /* When reducing, the number of symbols on the RHS of the reduced
     rule. */
  int yylen;

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
#if YYLSP_NEEDED
  yylsp = yyls;
#endif
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  */
# if YYLSP_NEEDED
	YYLTYPE *yyls1 = yyls;
	/* This used to be a conditional around just the two extra args,
	   but that might be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
# else
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);
# endif
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
# if YYLSP_NEEDED
	YYSTACK_RELOCATE (yyls);
# endif
# undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
#if YYLSP_NEEDED
      yylsp = yyls + yysize - 1;
#endif

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yychar1 = YYTRANSLATE (yychar);

#if YYDEBUG
     /* We have to keep this `#if YYDEBUG', since we use variables
	which are defined only if `YYDEBUG' is set.  */
      if (yydebug)
	{
	  YYFPRINTF (stderr, "Next token is %d (%s",
		     yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise
	     meaning of a token, for further debugging info.  */
# ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
# endif
	  YYFPRINTF (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %d (%s), ",
	      yychar, yytname[yychar1]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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

     Otherwise, the following line sets YYVAL to the semantic value of
     the lookahead token.  This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

#if YYLSP_NEEDED
  /* Similarly for the default location.  Let the user run additional
     commands if for instance locations are ranges.  */
  yyloc = yylsp[1-yylen];
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
#endif

#if YYDEBUG
  /* We have to keep this `#if YYDEBUG', since we use variables which
     are defined only if `YYDEBUG' is set.  */
  if (yydebug)
    {
      int yyi;

      YYFPRINTF (stderr, "Reducing via rule %d (line %d), ",
		 yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (yyi = yyprhs[yyn]; yyrhs[yyi] > 0; yyi++)
	YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
      YYFPRINTF (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif

  switch (yyn) {

case 5:
#line 116 "parser.y"
{ yyval.symbolPtr = create_void_symbol(yyvsp[0].string); g_print("symbol_id : >%s<\n", yyvsp[0].string) ;
    break;}
case 6:
#line 118 "parser.y"
{ yyval.string = g_strdup(yyvsp[0].string); g_print("sound_id : >%s<\n", yyvsp[0].string) ;
    break;}
case 7:
#line 120 "parser.y"
{ yyval.colorPtr = g_malloc( sizeof(GdkColor) ); gdk_color_parse(yyvsp[0].string, yyval.colorPtr); ;
    break;}
case 8:
#line 122 "parser.y"
{ yyval.arity = atoi(yyvsp[0].string); ;
    break;}
case 9:
#line 124 "parser.y"
{ yyval.cellPtr = get_cell_or_variable(yyvsp[0].string); g_print("cell_id : %s\n", yyvsp[0].string); ;
    break;}
case 10:
#line 130 "parser.y"
{ yyval.cutPtr = connect_principal_ports(yyvsp[-2].cellPtr, yyvsp[0].cellPtr); ;
    break;}
case 11:
#line 132 "parser.y"
{ yyval.cellPtr = yyvsp[0].cellPtr->portTable ? yyvsp[0].cellPtr : allocate_port_table(yyvsp[0].cellPtr, 0); ;
    break;}
case 12:
#line 135 "parser.y"
{
	yyval.cellPtr = allocate_and_connect_auxiliary_ports(yyvsp[-3].cellPtr, yyvsp[-1].list);
	g_slist_free(yyvsp[-1].list);
;
    break;}
case 13:
#line 140 "parser.y"
{ yyval.list = g_slist_prepend(NULL, yyvsp[0].cellPtr); ;
    break;}
case 14:
#line 142 "parser.y"
{ yyval.list = g_slist_prepend(yyvsp[-2].list, yyvsp[0].cellPtr); ;
    break;}
case 15:
#line 149 "parser.y"
{
	iSystem->symbolList = yyvsp[0].list;
	g_print("--- SYMBOL SECTION PARSED ---\n");
;
    break;}
case 16:
#line 154 "parser.y"
{ yyval.list = NULL; ;
    break;}
case 17:
#line 156 "parser.y"
{ yyval.list = g_slist_prepend(yyvsp[-1].list, yyvsp[0].symbolPtr); ;
    break;}
case 18:
#line 158 "parser.y"
{ yyval.symbolPtr=fill_in_symbol(yyvsp[-4].symbolPtr,yyvsp[-2].colorPtr,yyvsp[0].arity); ;
    break;}
case 19:
#line 160 "parser.y"
{ yyval.symbolPtr = fill_in_symbol(yyvsp[-2].symbolPtr, NULL, yyvsp[0].arity); ;
    break;}
case 20:
#line 167 "parser.y"
{
	iSystem->ruleList = yyvsp[0].list;
	g_print("--- RULE SECTION PARSED ---\n");
;
    break;}
case 21:
#line 172 "parser.y"
{ yyval.list = NULL; ;
    break;}
case 22:
#line 174 "parser.y"
{ yyval.list = g_slist_prepend(yyvsp[0].list, yyvsp[-1].rulePtr); ;
    break;}
case 23:
#line 177 "parser.y"
{
	g_assert( !(yyvsp[-1].list) );				// no more than one cut
	g_assert( !freeVariableList );	// some variables are still free
	yyval.rulePtr = yyvsp[-2].rulePtr;
	boundVariableList = remove_variable_list(boundVariableList);
	yyval.rulePtr->sound = NULL;
	g_print("Default sound\n");
;
    break;}
case 24:
#line 187 "parser.y"
{
	g_assert( !(yyvsp[-3].list) );				// no more than one cut
	g_assert( !freeVariableList );	// some variables are still free
	yyval.rulePtr = yyvsp[-4].rulePtr;
	boundVariableList = remove_variable_list(boundVariableList);
	yyval.rulePtr->sound = yyvsp[-1].string;
;
    break;}
case 25:
#line 196 "parser.y"
{
	yyval.rulePtr = create_rule(yyvsp[-2].cellPtr, yyvsp[0].cellPtr);
;
    break;}
case 26:
#line 205 "parser.y"
{
	iSystem->net.cutList = yyvsp[0].list;
	iSystem->net.currentCut = g_slist_nth_data(yyvsp[0].list,0);
	INTERFACE(iSystem) = create_interface_cell();
	iSystem->net.freePortLabelTable = create_free_port_label_table();
	freeVariableList = remove_variable_list(freeVariableList);
	boundVariableList = remove_variable_list(boundVariableList);
;
    break;}
case 27:
#line 218 "parser.y"
{ yyval.list = NULL; ;
    break;}
case 28:
#line 220 "parser.y"
{ yyval.list = yyvsp[0].cutPtr ? g_slist_prepend(yyvsp[-1].list, yyvsp[0].cutPtr) : yyvsp[-1].list; ;
    break;}
}

#line 705 "/usr/share/bison/bison.simple"


  yyvsp -= yylen;
  yyssp -= yylen;
#if YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;
#if YYLSP_NEEDED
  *++yylsp = yyloc;
#endif

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("parse error, unexpected ") + 1;
	  yysize += yystrlen (yytname[YYTRANSLATE (yychar)]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "parse error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[YYTRANSLATE (yychar)]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exhausted");
	}
      else
#endif /* defined (YYERROR_VERBOSE) */
	yyerror ("parse error");
    }
  goto yyerrlab1;


/*--------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action |
`--------------------------------------------------*/
yyerrlab1:
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;
      YYDPRINTF ((stderr, "Discarding token %d (%s).\n",
		  yychar, yytname[yychar1]));
      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;


/*-------------------------------------------------------------------.
| yyerrdefault -- current state does not do anything special for the |
| error token.                                                       |
`-------------------------------------------------------------------*/
yyerrdefault:
#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */

  /* If its default is to accept any token, ok.  Otherwise pop it.  */
  yyn = yydefact[yystate];
  if (yyn)
    goto yydefault;
#endif


/*---------------------------------------------------------------.
| yyerrpop -- pop the current state because it cannot handle the |
| error token                                                    |
`---------------------------------------------------------------*/
yyerrpop:
  if (yyssp == yyss)
    YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#if YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "Error: state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

/*--------------.
| yyerrhandle.  |
`--------------*/
yyerrhandle:
  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

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

/*---------------------------------------------.
| yyoverflowab -- parser overflow comes here.  |
`---------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}
#line 224 "parser.y"



// STATIC FUNCTIONS ==============================================================


// symbol functions --------------------------------------------------------------

static Symbol *create_void_symbol(gchar *label)
{
	Symbol	*symbol;
	
	symbol = g_malloc( sizeof(Symbol) );
	symbol->label = g_strdup(label);
	return symbol;
}

static Symbol *fill_in_symbol(Symbol *symbol, GdkColor *colorPtr, Arity arity)
{
	symbol->color = colorPtr;
	symbol->arity = arity;
	return symbol;
}


// cell and variable functions ---------------------------------------------------

static Cell *get_cell_or_variable(gchar *label)
{
	GSList *ptr;
	GSList *symbolList = iSystem->symbolList;
	
	ptr = g_slist_find_custom(symbolList, label, are_symbol_labels_different);
	if ( ptr ) return create_void_cell( SYMBOL_PTR(ptr->data) );
	else return get_variable(label);
}

static Cell *create_void_cell(Symbol *symbol)
{
	Cell *cell;
	
	cell = g_malloc( sizeof(Cell) );
	cell->symbol = symbol;
	cell->portTable = NULL;
	return cell;
}

static Cell *get_variable(gchar *l)
{
	GSList *ptr;
	
	ptr = g_slist_find_custom(freeVariableList, l, are_cell_labels_different);
	if ( ptr )
	{
		freeVariableList = g_slist_remove_link(freeVariableList, ptr);
		boundVariableList = g_slist_concat(ptr, boundVariableList);
		return CELL_PTR(ptr->data);
	}
	else
	{
		Cell *variable;

		ptr=g_slist_find_custom(boundVariableList, l, are_cell_labels_different);
		g_assert ( !ptr ); // variable already used

		variable = create_void_variable(l);
		freeVariableList = g_slist_prepend(freeVariableList, variable);
		return variable;
	}
}

static Cell *create_void_variable(gchar *label)
{
	Symbol *symbol;
	
	symbol = fill_in_symbol(create_void_symbol(label), NULL, 0);
	return create_void_cell(symbol);
}


// tree, cut functions -----------------------------------------------------------

static Cut *connect_principal_ports(Cell *cell1, Cell *cell2)
{
	connect_ports(&PORT(cell1,0), &PORT(cell2,0));

	if ( !isCutBetweenCells(&PORT(cell1,0), &PORT(cell2,0)) ) return NULL;
	else return create_cut( PORT(cell1,0).cell, PORT(cell2,0).cell );
}

static Rule *create_rule(Cell *cell1, Cell *cell2)
{
	Rule *rule;
	
	connect_ports(&PORT(cell1,0), &PORT(cell2,0));

	g_assert( isCutBetweenCells(&PORT(cell1,0), &PORT(cell2,0)) );
	// left member must be a "real" cut

	rule = g_malloc( sizeof(Rule) );
	if ( !are_cells_ordered(cell1, cell2) ) EXCHANGE(cell1, cell2, Cell *);
	rule->cell1 = cell1;
	rule->cell2 = cell2;
	return rule;
}

static gboolean isCutBetweenCells(Port *port1, Port *port2)
{
	return (
			port1->num==0 &&
			port2->num==0 &&
			g_slist_find(iSystem->symbolList, port1->cell->symbol) &&
			g_slist_find(iSystem->symbolList, port2->cell->symbol)
		   );
}

static Cell *allocate_and_connect_auxiliary_ports(Cell *cell, GSList *list)
{
	cell = allocate_port_table(cell, g_slist_length(list));
	return connect_auxiliary_ports(cell, list);
}

static Cell *allocate_port_table(Cell *cell, Arity arity)
{
	Arity i;
	
	if (ARITY(cell) != arity)
	{
		GSList *ptr = g_slist_find_custom(iSystem->symbolList, LABEL(cell),
				are_symbol_labels_different);

		while ( ptr && SYMBOL_PTR(ptr->data)->arity != arity )
			ptr = g_slist_find_custom(ptr->next, LABEL(cell),
					are_symbol_labels_different);

		g_assert( ptr ); // symbol not found or bad number of arguments
		cell->symbol = SYMBOL_PTR(ptr->data);
	}
	cell->portTable = g_malloc( (arity+1)*sizeof(Port) );
	for (i=0; i<=arity; i++)
	{
		PORT(cell,i).cell = cell;
		PORT(cell,i).num = i;
		PORT(cell,i).ref = NULL;
	}
	return cell;
}

static Cell *connect_auxiliary_ports(Cell *root, GSList *subTreeList)
{
	GSList *ptr = subTreeList;
	Arity i;

	for (i=ARITY(root); i>=1; i--)
	{
		connect_ports( &PORT(root,i), &PORT(CELL_PTR(ptr->data),0) );
		ptr = ptr->next;
	}
	return root;
}


// variable functions ------------------------------------------------------------

static GSList *remove_variable_list(GSList *list)
{
	g_slist_foreach(list, remove_one_variable, NULL);
	g_slist_free(list);
	return NULL;
}

static void remove_one_variable(gpointer data, gpointer user_data)
{
	g_free( LABEL(CELL_PTR(data)) );
	g_free( CELL_PTR(data)->symbol );
	g_free( CELL_PTR(data)->portTable );
	g_free( data );
}


// net functions -----------------------------------------------------------------

static Cell *create_interface_cell(void)
{
	Arity	arity;
	Symbol	*symbol;
	Cell	*cell;

	arity = g_slist_length(freeVariableList);
	symbol = fill_in_symbol(create_void_symbol(NULL), NULL, arity);
	cell = create_void_cell(symbol);
	return allocate_and_connect_auxiliary_ports(cell, freeVariableList);
}

static gchar **create_free_port_label_table(void)
{
	gchar **freePortLabelTable;
	Arity arity = g_slist_length(freeVariableList);
	Arity i;
	GSList *ptr = freeVariableList;
	
	freePortLabelTable = g_malloc( arity*sizeof(gchar *) );
	for (i=1; i<=arity; i++)
	{
		freePortLabelTable[arity-i] = LABEL(CELL_PTR(ptr->data));
		LABEL(CELL_PTR(ptr->data)) = NULL; // this label must NOT be freed
		ptr = ptr->next;
	}
	return freePortLabelTable;
}


// comparison functions ----------------------------------------------------------

static gboolean
are_symbol_labels_different(gconstpointer symbol, gconstpointer label)
{
	return strcmp(SYMBOL_PTR(symbol)->label, (gchar *)label);
}

static gboolean
are_cell_labels_different(gconstpointer cell, gconstpointer label)
{
	return strcmp(LABEL(CELL_PTR(cell)), (gchar *)label);
}


// error function ----------------------------------------------------------------

static int yyerror(gchar *s)
{
	g_print("\n***** %s *****\n", s);
	freeVariableList = NULL;
	boundVariableList = NULL;
}


