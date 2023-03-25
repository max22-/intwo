// -------------------------------------------------------------------------------
// types.h
// Text interpreter for Interaction Nets (Dec. 9. 1998)
// Last modified: Jan. 4. 1999
// -------------------------------------------------------------------------------

#ifndef __TYPES__
#define __TYPES__


// INCLUDES ----------------------------------------------------------------------

#include <gtk/gtk.h>


// MACROS ------------------------------------------------------------------------

#define MACINTOSH
#define SOUND_DIR "launch -b -c hook $HOME/sons/"


#define INTERFACE(s)			((s)->net.interface)
#define FREE_PORT_LABEL(s,n)	((s)->net.freePortLabelTable[(n)-1])
#define PORT(cell,n)			(cell->portTable[n])
#define ARITY(cell)				(cell->symbol->arity)
#define LABEL(cell)				(cell->symbol->label)
#define EXCHANGE(a,b,type)		{type ptr_; ptr_=a; a=b; b=ptr_;}
#define SYMBOL_PTR(ptr)			((Symbol *)(ptr))
#define CELL_PTR(ptr)			((Cell *)(ptr))
#define RULE_PTR(ptr)			((Rule *)(ptr))
#define CUT_PTR(ptr)			((Cut *)(ptr))


// CONSTANTS ---------------------------------------------------------------------

#define MAX_VARIABLE_LABEL	20


// DATA STRUCTURES ---------------------------------------------------------------

typedef guint8 Arity;

typedef struct Symbol
{
	gchar					*label;
	Arity					arity;
	GdkColor				*color;
} Symbol;

typedef struct Cell
{
	Symbol		*symbol;
	struct Port	*portTable;
} Cell;

typedef struct Port
{
	Cell		*cell;
	Arity		num;
	gpointer	ref;	// for layout and copy
} Port;

typedef struct Cut
{
	Cell	*cell1;
	Cell	*cell2;
	int		left;
	int		right;
} Cut;

#ifdef MACINTOSH
typedef struct Rule
{
	Cell	*cell1;
	Cell	*cell2;
	gchar	*sound;
} Rule;
#else

typedef struct Rule
{
	Cell	*cell1;
	Cell	*cell2;
} Rule;

#endif

typedef struct Net
{
	GSList	*cutList;
	gchar	**freePortLabelTable;
	Cell	*interface;
	Cut		*currentCut;
} Net;

typedef struct System
{
	GSList		*symbolList;
	GSList		*ruleList;
	Net			net;
} System;


#endif // __TYPES__
