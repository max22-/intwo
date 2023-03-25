// -------------------------------------------------------------------------------
// utility.h
// This module handles cut elimination (Dec. 18. 1998)
// Last modified: Jan. 4. 1999
// -------------------------------------------------------------------------------


// INCLUDES ----------------------------------------------------------------------

#include "types.h"


// MACROS ------------------------------------------------------------------------


// EXTERN FUNCTION PROTOTYPES ----------------------------------------------------

gboolean are_cells_ordered(Cell *c1, Cell *c2);
Cut *create_cut(Cell *c1, Cell *c2);
void connect_cells(Cell *c1, Arity portN1, Cell *c2, Arity portN2);
void connect_ports(Port *port1, Port *port2);
void remove_cell(Cell *cell);



