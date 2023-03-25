// -------------------------------------------------------------------------------
// layout.c
// Text interpreter for Interaction Nets (October 14. 1998)
// Last Modified: Jan. 8. 1999
// -------------------------------------------------------------------------------


// INCLUDES ----------------------------------------------------------------------

#include "layout.h"


// STATIC GLOBAL VARIABLES -------------------------------------------------------

gchar variableLabel[MAX_VARIABLE_LABEL];


// STATIC FUNCTIONS PROTOTYPES ---------------------------------------------------

static void print_symbol(gpointer symbol, gpointer data);
static void increment_label(char *l);
static gchar *get_new_variable_label(struct System *s);
static void reset_variable_label(void);
static void print_variable_label(System *s, Port *port);
static void print_tree(System *s, Cell *c);
static void print_one_cut(gpointer data, gpointer s);
static void print_one_rule(gpointer data, gpointer s);


// STATIC FUNCTIONS --------------------------------------------------------------

static void print_symbol(gpointer symbol, gpointer data)
{
	g_print("(%p) %-15s (r=%-5d g=%-5d b=%-5d) : %d\n",
			symbol,
			SYMBOL_PTR(symbol)->label,
			SYMBOL_PTR(symbol)->color ? SYMBOL_PTR(symbol)->color->red : 0,
			SYMBOL_PTR(symbol)->color ? SYMBOL_PTR(symbol)->color->green : 0,
			SYMBOL_PTR(symbol)->color ? SYMBOL_PTR(symbol)->color->blue : 0,
			SYMBOL_PTR(symbol)->arity);
}

static void increment_label(char *l) // A->B, B->C, ..., Z->AA, AA->AB, ...
{
	int right = strlen(l)-1;
	int i;

	i=right;
	while (l[i]=='Z' && i>0) l[i--]='A';
	if (l[i]<'Z') l[i]++;
	else
	{
		l[i]='A';
		l[right+1]='A';
		l[right+2]='\0';
	}
}

static gchar *get_new_variable_label(System *s)
{
	increment_label(variableLabel);
	return g_strdup(variableLabel);
}

static void reset_variable_label(void)
{
	variableLabel[0] = 64;
	variableLabel[1] = '\0';
}

static void print_variable_label(System *s, Port *port)
{
	if ( LABEL(port->cell)==NULL )
	{
		g_print("%s", FREE_PORT_LABEL(s,port->num));
	}
	else
	{
		if ( port->ref )
		{
			g_print("%s", (gchar *)port->ref);
			g_free(port->ref);
			port->ref = NULL;
		}
		else
		{
			PORT(port->cell, port->num).ref = (gpointer)get_new_variable_label(s);
			g_print("%s", (gchar *)PORT(port->cell, port->num).ref);
		}
	}
}

static void print_tree(System *s, Cell *c)
{
	Arity i;
	
	g_print("%s", LABEL(c));
	if (ARITY(c) >= 1)
	{
		g_print("(");
		if (PORT(c,1).num == 0) print_tree(s, PORT(c,1).cell);
		else print_variable_label(s, &PORT(c, 1));
		for (i=2; i<=ARITY(c); i++)
		{
			g_print(", ");
			if (PORT(c,i).num == 0) print_tree(s, PORT(c,i).cell);
			else print_variable_label(s, &PORT(c, i));
		}
		g_print(")");
	}
}

static void print_one_rule(gpointer data, gpointer s)
{
	reset_variable_label();
	print_tree((System *)s, RULE_PTR(data)->cell1);
	g_print(" >< ");
	print_tree((System *)s, RULE_PTR(data)->cell2);
	g_print("\n");
}

static void print_one_cut(gpointer data, gpointer s)
{
	print_tree((System *)s, CUT_PTR(data)->cell1);
	g_print(" -- ");
	print_tree((System *)s, CUT_PTR(data)->cell2);
	g_print("\n");
}


// EXTERN FUNCTIONS --------------------------------------------------------------

void print_symbol_list(System *s)
{
	g_print("\nSYMBOL LIST ------------------------------------------------\n\n");
	g_slist_foreach(s->symbolList, (GFunc)print_symbol, NULL);
}

void print_all_rules(System *s)
{
	g_print("\nRULES ------------------------------------------------------\n\n");
	g_slist_foreach(s->ruleList, (GFunc)print_one_rule, s);
}

void print_net(System *s)
{
	Arity	freePortNum;
	Arity	i;
	Cell	*cell;
	Arity	portNum;

	g_print("\nNET --------------------------------------------------------\n\n");
	reset_variable_label();
	g_slist_foreach(s->net.cutList, (GFunc)print_one_cut, s);
	freePortNum = ARITY(INTERFACE(s));
	for (i=1; i<=freePortNum; i++)
	{
		cell = PORT(INTERFACE(s),i).cell;
		portNum = PORT(INTERFACE(s),i).num;
		if (portNum == 0)
		{
			g_print("%s -- ", FREE_PORT_LABEL(s,i));
			print_tree(s, cell);
			g_print("\n");
		}
	}
}

void print_free_ports(System *s)
{
	Arity	i;
	Arity	freePortNum;

	g_print("\nFREE PORTS -------------------------------------------------\n\n");
	freePortNum = ARITY(INTERFACE(s));
	if ( freePortNum ) g_print("%s", FREE_PORT_LABEL(s,1));
	for (i=2; i<=freePortNum; i++) g_print(", %s", FREE_PORT_LABEL(s,i));
	g_print("\n");
}
