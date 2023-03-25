// drawing.h
// graphical layout of interaction nets (November 16. 1998)
// Last modified : Jan. 5. 1999



#ifndef __DRAWING__
#define __DRAWING__


// INCLUDES ----------------------------------------------------------------------


#include "layout.h"
#include "types.h"
#include "engine.h"
#include <gtk/gtk.h>


// CONSTANTS ---------------------------------------------------------------------

#define LABEL_FONT_WIDTH 5.8
#define LABEL_FONT_HEIGHT 9
#define LABEL_FONT "fixed"

#define ZERO_CELL_WIDTH		40	// width of an arity ZERO cell
#define ZERO_CELL_HEIGHT	40	// height of an arity ZERO cell
#define MANY_CELL_WIDTH		60	// width of cell of arity >= 1
#define MANY_CELL_HEIGHT	30	// height of cell of arity >= 1
#define FREE_PORT_HEIGHT	(LABEL_FONT_HEIGHT+4)
#define VSPACE			40
#define HSPACE			6
#define CUT_HEIGHT		40
#define AXIOM_WIDTH		10
#define AXIOM_CURVE		8

#define BACKGROUND_COLOR	"wheat1"
// #define BACKGROUND_COLOR	"white"
#define SELECT_COLOR		"red"
#define DEFAULT_CELL_COLOR	"RoyalBlue"

#define PM_HEIGHT	1500
#define PM_WIDTH	3000




// FUNCTIONS ---------------------------------------------------------------------

void draw_net(struct Net *net);
void draw_rule(Rule *rule);
void open_window(void);
void draw_next_rule(System *s);
void open_callback (GtkWidget *widget, gpointer data);


#endif // __DRAWING__

