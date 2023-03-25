/* ===============================================================================
	parser.y
	Text interpreter for Interaction Nets (October 12.)
	Modified: Jan. 8. 1999
=============================================================================== */

%{

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


%}

// BISON DEFINITIONS =============================================================

%union
{
	gchar		*string;
	Arity		arity;
	Symbol		*symbolPtr;
	GdkColor	*colorPtr;
	Cell		*cellPtr;
	Cut			*cutPtr;
	Rule		*rulePtr;
	GSList		*list;
}

%token					SYMBOL
%token					RULE
%token					NET
%token					CUT
%token					LEFT_CUT
%token	<string>		ARITY_ID
%token	<string>		COLOR_ID
%token	<string>		ID

%type	<string>		id

%type	<string>		sound_id

%type	<symbolPtr>		symbol_id
%type	<colorPtr>		color_id
%type	<arity>			arity_id
%type	<cellPtr>		cell_id

%type	<list>			symbol_decl_seq
%type	<symbolPtr>		symbol_decl

%type	<list>			rule_seq
%type	<rulePtr>		rule
%type	<list>			cut_seq
%type	<cutPtr>		cut
%type	<rulePtr>		rule_left_member

%type	<cellPtr>		tree
%type	<list>			tree_seq1

%%


// BISON RULES ===================================================================


// initial symbol ----------------------------------------------------------------

system: symbol_section rule_section net_section
;


// IDs ---------------------------------------------------------------------------

id: ARITY_ID | COLOR_ID | ID
;
symbol_id: id { $$ = create_void_symbol($1); g_print("symbol_id : >%s<\n", $1) }
;
sound_id: id { $$ = g_strdup($1); g_print("sound_id : >%s<\n", $1) }
;
color_id: COLOR_ID { $$ = g_malloc( sizeof(GdkColor) ); gdk_color_parse($1, $$); }
;
arity_id: ARITY_ID { $$ = atoi($1); }
;
cell_id: id { $$ = get_cell_or_variable($1); g_print("cell_id : %s\n", $1); }
;


// cut, tree ---------------------------------------------------------------------

cut: tree CUT tree { $$ = connect_principal_ports($1, $3); }
;
tree: cell_id { $$ = $1->portTable ? $1 : allocate_port_table($1, 0); }
;
tree: cell_id '(' tree_seq1 ')'
{
	$$ = allocate_and_connect_auxiliary_ports($1, $3);
	g_slist_free($3);
}
;
tree_seq1: tree { $$ = g_slist_prepend(NULL, $1); }
;
tree_seq1: tree_seq1 ',' tree { $$ = g_slist_prepend($1, $3); }
;


// symbol section ----------------------------------------------------------------

symbol_section: SYMBOL symbol_decl_seq
{
	iSystem->symbolList = $2;
	g_print("--- SYMBOL SECTION PARSED ---\n");
}
;
symbol_decl_seq: /* empty */ { $$ = NULL; }
;
symbol_decl_seq: symbol_decl_seq symbol_decl { $$ = g_slist_prepend($1, $2); }
;
symbol_decl: symbol_id ',' color_id ':' arity_id { $$=fill_in_symbol($1,$3,$5); }
;
symbol_decl: symbol_id ':' arity_id { $$ = fill_in_symbol($1, NULL, $3); }
;


// rule section ------------------------------------------------------------------

rule_section: RULE rule_seq
{
	iSystem->ruleList = $2;
	g_print("--- RULE SECTION PARSED ---\n");
}
;
rule_seq: /* empty */ { $$ = NULL; }
;
rule_seq: rule rule_seq { $$ = g_slist_prepend($2, $1); }
;
rule: rule_left_member cut_seq '.'
{
	g_assert( !($2) );				// no more than one cut
	g_assert( !freeVariableList );	// some variables are still free
	$$ = $1;
	boundVariableList = remove_variable_list(boundVariableList);
	$$->sound = NULL;
	g_print("Default sound\n");
}
;
rule: rule_left_member cut_seq ',' sound_id '.'
{
	g_assert( !($2) );				// no more than one cut
	g_assert( !freeVariableList );	// some variables are still free
	$$ = $1;
	boundVariableList = remove_variable_list(boundVariableList);
	$$->sound = $4;
}
;
rule_left_member: tree LEFT_CUT tree
{
	$$ = create_rule($1, $3);
}
;


// net section -------------------------------------------------------------------

net_section: NET cut_seq
{
	iSystem->net.cutList = $2;
	iSystem->net.currentCut = g_slist_nth_data($2,0);
	INTERFACE(iSystem) = create_interface_cell();
	iSystem->net.freePortLabelTable = create_free_port_label_table();
	freeVariableList = remove_variable_list(freeVariableList);
	boundVariableList = remove_variable_list(boundVariableList);
}
;


// cut_seq -----------------------------------------------------------------------

cut_seq: /* empty */ { $$ = NULL; }
;
cut_seq: cut_seq cut { $$ = $2 ? g_slist_prepend($1, $2) : $1; }
;


%%


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


