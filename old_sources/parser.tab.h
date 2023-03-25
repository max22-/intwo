#ifndef BISON_PARSER_TAB_H
# define BISON_PARSER_TAB_H

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
# define	SYMBOL	257
# define	RULE	258
# define	NET	259
# define	CUT	260
# define	LEFT_CUT	261
# define	ARITY_ID	262
# define	COLOR_ID	263
# define	ID	264


extern YYSTYPE yylval;

#endif /* not BISON_PARSER_TAB_H */
