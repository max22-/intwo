// -------------------------------------------------------------------------------
// utility.c
// This module handles cut elimination (Dec. 18. 1998)
// Last modified: Jan. 4. 1999
// -------------------------------------------------------------------------------


// INCLUDES ----------------------------------------------------------------------

#include "utility.h"


// EXTERN FUNCTIONS --------------------------------------------------------------

gboolean are_cells_ordered(Cell *c1, Cell *c2)
{
	return
		(ARITY(c1) < ARITY(c2))										||
		(ARITY(c1) == ARITY(c2) && strcmp(LABEL(c1), LABEL(c2))<=0)	;
}

Cut *create_cut(Cell *c1, Cell *c2)
{
	Cut *cut;

	cut = g_malloc( sizeof(Cut) );
	if ( !are_cells_ordered(c1, c2) ) EXCHANGE(c1, c2, Cell *);
	cut->cell1 = c1;
	cut->cell2 = c2;
	return cut;
}

void connect_cells(Cell *c1, Arity portN1, Cell *c2, Arity portN2)
{
	PORT(c1, portN1).cell = c2;
	PORT(c1, portN1).num = portN2;
	PORT(c2, portN2).cell = c1;
	PORT(c2, portN2).num = portN1;
}

void connect_ports(Port *port1, Port *port2)
{
	connect_cells(port1->cell, port1->num, port2->cell, port2->num);
}

void remove_cell(Cell *cell)
{
	g_free(cell->portTable);
	g_free(cell);
}

