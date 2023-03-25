// -------------------------------------------------------------------------------
// engine.c
// This module handles cut elimination (October 15. 1998)
// Last modified: Jan. 4. 1999
// -------------------------------------------------------------------------------


// INCLUDES ----------------------------------------------------------------------

#include "engine.h"


// STATIC FUNCTION PROTOTYPES ----------------------------------------------------

static Cell *create_cell(Symbol *symbol);
static Cut *copy_rule(Rule *rule);
static Cell *copy_tree(Cell *root);
static void copy_axiom_link(Cell *cell1, Cell *cell1Copy, Arity portNum1);
static void connect_trees(System *s, Cell *root1, Cell *root2);
static void connect_cuts(System *s, Cut *cut1, Cut *cut2);


// STATIC FUNCTIONS --------------------------------------------------------------

static Cell *create_cell(Symbol *symbol)
{
	Cell	*cell;
	Arity	i;
	
	cell = g_malloc( sizeof(Cell) );
	cell->symbol = symbol;
	cell->portTable = g_malloc( (ARITY(cell)+1)*sizeof(Port) );
	PORT(cell,0).cell = NULL;
	for (i=0; i<=ARITY(cell); i++) PORT(cell,i).ref = NULL;
	return cell;
}

static Cut *copy_rule(Rule *rule)
{
	return create_cut(copy_tree(rule->cell1), copy_tree(rule->cell2));
}

static Cell *copy_tree(Cell *root)
{
	Arity i;
	Cell *rootCopy;
	
	rootCopy = create_cell(root->symbol);
	for (i=1; i<=ARITY(root); i++)
	{
		if (PORT(root,i).num != 0) copy_axiom_link(root, rootCopy, i);
		else connect_cells(rootCopy, i, copy_tree(PORT(root,i).cell), 0);
	}
	return rootCopy;
}

static void copy_axiom_link(Cell *cell1, Cell *cell1Copy, Arity portNum1)
{
	Cell	*cell2 = PORT(cell1,portNum1).cell;
	Arity	portNum2 = PORT(cell1,portNum1).num;
	
	if ( PORT(cell2,portNum2).ref )
	{
		connect_cells(cell1Copy, portNum1, PORT(cell2,portNum2).ref, portNum2);
		PORT(cell2,portNum2).ref = NULL;
	}
	else
		PORT(cell1,portNum1).ref = cell1Copy;
}

static void connect_trees(System *s, Cell *root1, Cell *root2)
{
	Arity i;
	
	g_assert( ARITY(root1) == ARITY(root2) ); // roots don't match
	for (i=ARITY(root1); i>=1; i--)
	{
		connect_ports(&PORT(root1,i), &PORT(root2,i));
		if (PORT(root1,i).num==0 && PORT(root2,i).num==0)
		{
			s->net.cutList = g_slist_prepend(
					s->net.cutList,
					create_cut(PORT(root1,i).cell, PORT(root2,i).cell)
											);
		}
	}
}

static void connect_cuts(System *s, Cut *cut1, Cut *cut2)
{
	connect_trees(s, cut1->cell2, cut2->cell2);
	connect_trees(s, cut1->cell1, cut2->cell1);
}


// EXTERN FUNCTIONS --------------------------------------------------------------

void eliminate_cut(System *s)
{
	GSList	*ruleList;
	Cut		*cut;
	Rule	*rule;
	Cut		*ruleCopy;
	gchar	sound[100] = SOUND_DIR;

	
	cut = s->net.currentCut;
	if ( cut )
	{
		ruleList = g_slist_find_custom(s->ruleList, cut, are_cuts_different);
		g_assert( ruleList ); // rule not found
		rule = RULE_PTR(ruleList->data);

		if ( rule->sound )
		{
			strcat(sound,rule->sound);
			g_print("Sound is >%s<\n",sound);
			system(sound);
		}

		ruleCopy = copy_rule(rule);
		connect_cuts(s, cut, ruleCopy);
		remove_cell(cut->cell1); remove_cell(cut->cell2);
		remove_cell(ruleCopy->cell1); remove_cell(ruleCopy->cell2);
		s->net.cutList = g_slist_remove(s->net.cutList, cut);
	}
	s->net.currentCut = g_slist_nth_data(s->net.cutList, 0);
}

gboolean are_cuts_different(gconstpointer cut1, gconstpointer cut2)
{
	return
		ARITY(CUT_PTR(cut1)->cell1) != ARITY(CUT_PTR(cut2)->cell1)				||
		ARITY(CUT_PTR(cut1)->cell2) != ARITY(CUT_PTR(cut2)->cell2)				||
		strcmp(LABEL(CUT_PTR(cut1)->cell1), LABEL(CUT_PTR(cut2)->cell1)) != 0	||
		strcmp(LABEL(CUT_PTR(cut1)->cell2), LABEL(CUT_PTR(cut2)->cell2)) != 0	;

}


