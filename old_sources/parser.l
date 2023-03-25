/* -------------------------------------------------------------------------------
	parser.l
	Text interpreter for Interaction Nets (October 13.)
	Modified: Jan. 8. 1999
------------------------------------------------------------------------------- */


%{

// INCLUDES ----------------------------------------------------------------------

#include <glib.h>
#include "types.h"
#include "parser.tab.h"
#include "layout.h"


// STATIC FUNCTION PROTOTYPES ----------------------------------------------------

static void handle_quoted_id(void);



%}

%{
// FLEX DEFINITIONS --------------------------------------------------------------
%}

%option noyywrap

ARITY_ID	[0-9]+
COLOR_ID	[a-zA-Z][a-zA-Z0-9]*
UNQUOTED_ID	[^()\.:,\-"/ \t\n]+
QUOTED_ID	\"([^"]|(\"\"))*\"

%%


%{
// FLEX RULES --------------------------------------------------------------------
%}

"symbol"			{ return(SYMBOL); }
"rule"				{ return(RULE); }
"net"				{ return(NET); }
{ARITY_ID}			{ yylval.string = yytext; return(ARITY_ID); }
{COLOR_ID}			{ yylval.string = yytext; return(COLOR_ID); }
"("					{ return('('); }
")"					{ return(')'); }
":"					{ return(':'); }
"."					{ return('.'); }
","					{ return(','); }
"><"				{ return(LEFT_CUT); }
"--"				{ return(CUT); }
{UNQUOTED_ID}		{ yylval.string = yytext; return(ID); }
{QUOTED_ID}			{ handle_quoted_id(); return(ID); }
"//"[^\n]*\n		/* COMMENTS */
[ \t\n]+			/* WHITESPACE */
.					{ g_print("unknown char : >%s<\n", yytext); }

%%


// STATIC FUNCTIONS --------------------------------------------------------------

// yytext = >"abc""d""ef"""< translated into yytext = >abc"d"ef"<
//
static void handle_quoted_id(void)
{
	int oldIdx = 1;
	int newIdx = 0;

	while (oldIdx<=yyleng-2)
	{
		yytext[newIdx++] = yytext[oldIdx];
		if (yytext[oldIdx]=='"') {g_assert(oldIdx<yyleng-2); oldIdx+=2; }
		else oldIdx+=1;
	}
	yytext[newIdx] = '\0';
	yylval.string = yytext;
}


