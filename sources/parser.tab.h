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
} YYSTYPE;
#define	SYMBOL	257
#define	RULE	258
#define	NET	259
#define	CUT	260
#define	LEFT_CUT	261
#define	ARITY_ID	262
#define	COLOR_ID	263
#define	ID	264


extern YYSTYPE yylval;
