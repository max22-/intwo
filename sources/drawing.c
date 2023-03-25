// drawing.c
// graphical layout of interaction nets (November 16. 1998)
// Last modified : Jan. 12. 1999


// INCLUDES ----------------------------------------------------------------------

#include "drawing.h"
#include <stdio.h>
#include <string.h>


// EXTERN GLOBAL VARIABLES =======================================================

extern System *iSystem;
extern FILE	*yyin;
extern gchar currentFilename[100];


// STATIC GLOBALS ----------------------------------------------------------------

static GdkColor defaultCellColor;
static GdkPixmap *gdk_pixmap;
static GdkPixmap *net_gdk_pixmap;
static GdkPixmap *rule_gdk_pixmap;
static GdkGC *gc;
static GtkWidget *pixmap;
static GtkWidget *rulePixmap;
static GdkColor bgColor;
static GdkRectangle updateRect = {0, 0, PM_WIDTH, PM_HEIGHT};
static GdkColor blackPen = {0, 0x0000, 0x0000, 0x0000};
static GdkColor selectColor;
static struct AxiomHeightSeq
{
	int id;
	int height;
	GdkPoint left;
	struct AxiomHeightSeq *next;
} *axiomHeightSeq;
static guint RULE_WIDTH = 1500;
static guint RULE_HEIGHT = 1200;
static GtkWidget *filew;

// FUNCTIONS ---------------------------------------------------------------------

static void close_application(GtkWidget *widget, GdkEvent *event, gpointer *data);
static int draw_cut(int left, int bottom, Cut *c);
static int draw_free_link(int left, int bottom, gchar *var, Cell *misc);
static int draw_cut(int left, int bottom, Cut *c);
static int draw_tree(int left, int bottom, int *right, struct Cell *n);
static int draw_free_port(int left, int bottom, int *right, gchar *l);
static int draw_zero_cell(int left, int bottom, int *right, struct Cell *n);
static int draw_many_cell(int left, int bottom, struct Cell *n);
static int label_width(char *l);
static void draw_label(int left, int bottom, char *s);
static void handle_axiom_link(struct Port *port, int x, int y);
static void draw_connection(int origX, int origY, int destX, int destY);
static void draw_narrow_axiom_link(int lX, int lY, int rX, int rY, int h);
static void draw_large_axiom_link(int lX, int lY, int rX, int rY, int h);
static void draw_axiom_link(int lX, int lY, int rX, int rY, int h);
static void print_axiomHeightSeq(void);
static int calculate_subLeft(int left, struct Cell *n);
static int node_width(struct Port *p);
static void reduce_all_callback (GtkWidget *widget, gpointer data);
static void reduce_callback (GtkWidget *widget, gpointer data);
static void open_rule_window(void);
static int draw_rule_tree(int left, int bottom, int *right, struct Cell *n);
static int draw_rule_zero_cell(int left, int bottom, int *right, struct Cell *n);
static int draw_rule_many_cell(int left, int top, struct Cell *n);
static void handle_rule_axiom_link(struct Port *port, int x, int y);
static void draw_rule_axiom_link(int lX, int lY, int rX, int rY, int h);
static void draw_rule_narrow_axiom_link(int lX, int lY, int rX, int rY, int h);
static void draw_rule_large_axiom_link(int lX, int lY, int rX, int rY, int h);
static int calculate_tree_subLeft(int left, struct Cell *n);
static void file_ok_sel (GtkWidget *w, GtkFileSelection *fs);
static void destroy (GtkWidget *widget, gpointer data);
// static void change_cut(GtkWidget *widget, GtkSpinButton *spin);
static gint net_clicked(GtkWidget *widget, GdkEventButton *event, gpointer ref);
gboolean is_outside_cut(gconstpointer cut, gconstpointer x);
static void draw_normal_cut_link(int x1, int x2);
static void draw_current_cut_link(int x1, int x2);
static void reopen_callback (GtkWidget *widget, gpointer data);


static void draw_label(int left, int bottom, char *l)
{
	GdkFont* gdk_font;
	int right;

	gdk_font = gdk_font_load(LABEL_FONT);
	gdk_gc_set_foreground(gc, &blackPen);
	gdk_draw_string (gdk_pixmap, gdk_font, gc, left, bottom, l);
	right = left+strlen(l)*LABEL_FONT_WIDTH;

// for controlling the LABEL_FONT_WIDTH and LABEL_FONT_HEIGHT parameters
//	gdk_draw_rectangle (gdk_pixmap, gc, FALSE,
//			left, bottom-LABEL_FONT_HEIGHT, label_width(l), LABEL_FONT_HEIGHT);
			
}

static int draw_rule_tree(int left, int top, int *right, struct Cell *n)
{
	int rootAr, rootX, portX;		// root arity, root X and port X
	int *subX;						// tab of the X of the subtrees
	int subLeft, subTop, subRight; 	// left, bottom, right value for each subtree
	struct Port *port;				// the port being examined
	int i;
	
	rootAr = ARITY(n);
	if (rootAr==0) return draw_rule_zero_cell(left, top, right, n);
	
	// the root is a "many cell" (ie arity >= 1)
	subX = g_malloc( rootAr*sizeof(int) );
	subLeft = calculate_tree_subLeft(left, n);
	// Deux facons de centrer la racine : par rapport aux deux noeuds "extremes"
	// ou en faisant la moyenne des abscisses des sous arbres.
	// subBot = bottom-MANY_CELL_HEIGHT-rootAr*rootAr*VSPACE;
	subTop = top+MANY_CELL_HEIGHT+VSPACE;
	rootX=0;
	for (i=rootAr; i>=1; i--) // draw sub trees
	{
		port = &PORT(n,i);
		if (port->num != 0)
		{
			if ( LABEL(port->cell) == NULL ) // interface cell
			{
				g_assert( FALSE ); // no interface in a rule
			}
			else // axiom link
			{
				subRight = subLeft+AXIOM_WIDTH;
				subX[i-1] = subLeft+AXIOM_WIDTH/2;
				subLeft = subRight+HSPACE;
				handle_rule_axiom_link(port, subX[i-1], subTop);
			}
		}
		else // cell
		{
			subX[i-1]=draw_rule_tree(subLeft, subTop, &subRight,port->cell);
			subLeft = subRight+HSPACE;
		}
		rootX += subX[i-1];
	}
	// rootX = (subX[rootAr-1]+subX[0])/2;
	rootX = rootX/rootAr;
	g_assert(rootX >= left+MANY_CELL_WIDTH/2); // bad rootX
	for (i=rootAr-1; i>=0; i--) // draw connections
	{
		portX = rootX + MANY_CELL_WIDTH/2 - (i+1)*MANY_CELL_WIDTH/(rootAr+1);
		draw_connection(subX[i], subTop, portX, top+MANY_CELL_HEIGHT);
	}
	*right = MAX(subRight, rootX+MANY_CELL_WIDTH/2);
	g_free(subX);
	return draw_rule_many_cell(rootX-MANY_CELL_WIDTH/2, top, n);
}

static int draw_tree(int left, int bottom, int *right, struct Cell *n)
{
	int rootAr, rootX, portX;		// root arity, root X and port X
	int *subX;						// tab of the X of the subtrees
	int subLeft, subBot, subRight; 	// left, bottom, right value for each subtree
	struct Port *port;				// the port being examined
	int i;
	
	rootAr = ARITY(n);
	if (rootAr==0) return draw_zero_cell(left, bottom, right, n);
	
	// the root is a "many cell" (ie arity >= 1)
	subX = g_malloc( rootAr*sizeof(int) );
	subLeft = calculate_subLeft(left, n);
	// Deux facons de centrer la racine : par rapport aux deux noeuds "extremes"
	// ou en faisant la moyenne des abscisses des sous arbres.
	// subBot = bottom-MANY_CELL_HEIGHT-rootAr*rootAr*VSPACE;
	subBot = bottom-MANY_CELL_HEIGHT-VSPACE;
	rootX=0;
	for (i=1; i<=rootAr; i++) // draw sub trees
	{
		port = &PORT(n,i);
		if (port->num != 0)
		{
			if ( LABEL(port->cell) == NULL ) // interface cell
			{
				subX[i-1] = draw_free_port(subLeft, subBot, &subRight,
						FREE_PORT_LABEL(iSystem,port->num));
				subLeft = subRight+HSPACE;
			}
			else // axiom link
			{
				subRight = subLeft+AXIOM_WIDTH;
				subX[i-1] = subLeft+AXIOM_WIDTH/2;
				subLeft = subRight+HSPACE;
				handle_axiom_link(port, subX[i-1], subBot);
			}
		}
		else // free port or cell
		{
			subX[i-1]=draw_tree(subLeft, subBot, &subRight,port->cell);
			subLeft = subRight+HSPACE;
		}
		rootX += subX[i-1];
	}
	// rootX = (subX[rootAr-1]+subX[0])/2;
	rootX = rootX/rootAr;
	g_assert(rootX >= left+MANY_CELL_WIDTH/2); // bad rootX
	for (i=0; i<=rootAr-1; i++) // draw connections
	{
		portX = rootX - MANY_CELL_WIDTH/2 + (i+1)*MANY_CELL_WIDTH/(rootAr+1);
		draw_connection(portX, bottom-MANY_CELL_HEIGHT, subX[i], subBot);
	}
	*right = MAX(subRight, rootX+MANY_CELL_WIDTH/2);
	g_free(subX);
	return draw_many_cell(rootX-MANY_CELL_WIDTH/2, bottom, n);
}

static int calculate_tree_subLeft(int left, struct Cell *n)
{
	int subLeft = 0;
	int rootAr = ARITY(n);
	int i;
	int w;
	int rootX = 0;
	int *subX;

	subX = g_malloc( rootAr*sizeof(int) );
	for (i=rootAr; i>=1; i--)
	{
		w = node_width(&PORT(n,i));
		subX[i-1] = subLeft + w/2;
		subLeft += w + HSPACE;
		rootX += subX[i-1];
	}
	//rootX = (subX[0] + subX[rootAr-1])/2;
	rootX = rootX/rootAr;
	g_free(subX);
	if (rootX >= MANY_CELL_WIDTH/2) return left;
	else return (left + MANY_CELL_WIDTH/2 - rootX);
}

static int calculate_subLeft(int left, struct Cell *n)
{
	int subLeft = 0;
	int rootAr = ARITY(n);
	int i;
	int w;
	int rootX = 0;
	int *subX;

	subX = g_malloc( rootAr*sizeof(int) );
	for (i=1; i<=rootAr; i++)
	{
		w = node_width(&PORT(n,i));
		subX[i-1] = subLeft + w/2;
		subLeft += w + HSPACE;
		rootX += subX[i-1];
	}
	//rootX = (subX[0] + subX[rootAr-1])/2;
	rootX = rootX/rootAr;
	g_free(subX);
	if (rootX >= MANY_CELL_WIDTH/2) return left;
	else return (left + MANY_CELL_WIDTH/2 - rootX);
}

static int node_width(struct Port *p)
{
	if (p->num != 0)
		if ( LABEL(p->cell) ) return AXIOM_WIDTH;
		else return label_width(FREE_PORT_LABEL(iSystem,p->num));
		
	if (ARITY(p->cell) == 0) return ZERO_CELL_WIDTH;
	/* else */ return MANY_CELL_WIDTH;
}

static void handle_rule_axiom_link(struct Port *port, int x, int y)
{
	struct Port *rightPort;
	struct AxiomHeightSeq *current;
	struct AxiomHeightSeq *pred;
	struct AxiomHeightSeq *succ;
	int h;
	int id;
	int lX, lY;

	if (port->ref == NULL)	// left port
	{
		rightPort = &PORT(port->cell,port->num);
		rightPort->ref = g_malloc( sizeof(int) );
		current = g_malloc( sizeof(struct AxiomHeightSeq) );
		*(int *)(rightPort->ref) = current->id =
			axiomHeightSeq==NULL ? 0 : axiomHeightSeq->id + 1;
		current->height = y;
		current->left.x = x;
		current->left.y = y;
		current->next = axiomHeightSeq;
		axiomHeightSeq = current;
	}
	else					// right port
	{
		g_assert(axiomHeightSeq!=NULL); // invalid axiomHeightSeq
		id = *(int *)(port->ref);
		h = MAX(axiomHeightSeq->height, y);
		
		if (axiomHeightSeq->id == id)
		{
			succ = axiomHeightSeq->next;
			lX = axiomHeightSeq->left.x;
			lY = axiomHeightSeq->left.y;
			g_free(axiomHeightSeq);
			axiomHeightSeq = succ;
		}
		else
		{
			pred = axiomHeightSeq;
			current = pred->next;
			succ = current->next;
			g_assert(current!=NULL);
			while (current->id != id)
			{
				h = MAX(h, current->height);
				pred = current;
				current = succ;
				succ = current->next;
				g_assert(current!=NULL);
			}
			h = MAX(h, current->height);
			lX = current->left.x;
			lY = current->left.y;
			g_free(current);
			pred->next = succ;
		}
		g_free(port->ref);
		port->ref = NULL;
		draw_rule_axiom_link(lX, lY, x, y, h);
		if (axiomHeightSeq != NULL)
			axiomHeightSeq->height= MAX(axiomHeightSeq->height, h+AXIOM_CURVE+10);
	}
}

// If its the first time the axiom link occures we are at the left extremity
// else we are at the right extremity. If port is the left extremity port, store
// its coordinates in the right extremity port else draw the axiom link.

static void handle_axiom_link(struct Port *port, int x, int y)
{
	struct Port *rightPort;
	struct AxiomHeightSeq *current;
	struct AxiomHeightSeq *pred;
	struct AxiomHeightSeq *succ;
	int h;
	int id;
	int lX, lY;

	if (port->ref == NULL)	// left port
	{
		rightPort = &PORT(port->cell,port->num);
		rightPort->ref = g_malloc( sizeof(int) );
		current = g_malloc( sizeof(struct AxiomHeightSeq) );
		*(int *)(rightPort->ref) = current->id =
			axiomHeightSeq==NULL ? 0 : axiomHeightSeq->id + 1;
		current->height = y;
		current->left.x = x;
		current->left.y = y;
		current->next = axiomHeightSeq;
		axiomHeightSeq = current;
	}
	else					// right port
	{
		g_assert(axiomHeightSeq!=NULL); // invalid axiomHeightSeq
		id = *(int *)(port->ref);
		h = MIN(axiomHeightSeq->height, y);
		
		if (axiomHeightSeq->id == id)
		{
			succ = axiomHeightSeq->next;
			lX = axiomHeightSeq->left.x;
			lY = axiomHeightSeq->left.y;
			g_free(axiomHeightSeq);
			axiomHeightSeq = succ;
		}
		else
		{
			pred = axiomHeightSeq;
			current = pred->next;
			succ = current->next;
			g_assert(current!=NULL);
			while (current->id != id)
			{
				h = MIN(h, current->height);
				pred = current;
				current = succ;
				succ = current->next;
				g_assert(current!=NULL);
			}
			h = MIN(h, current->height);
			lX = current->left.x;
			lY = current->left.y;
			g_free(current);
			pred->next = succ;
		}
		g_free(port->ref);
		port->ref = NULL;
		draw_axiom_link(lX, lY, x, y, h);
		if (axiomHeightSeq != NULL)
			axiomHeightSeq->height= MIN(axiomHeightSeq->height, h-AXIOM_CURVE-10);
	}
}

static int draw_free_port(int left, int bottom, int *right, gchar *l)
{
	if (axiomHeightSeq != NULL) axiomHeightSeq->height =
		MIN(axiomHeightSeq->height, bottom-FREE_PORT_HEIGHT);
	draw_label(left, bottom-(FREE_PORT_HEIGHT-LABEL_FONT_HEIGHT), l);
	*right = left + label_width(l);
	return (left+*right)/2;
}

static int draw_rule_zero_cell(int left, int top, int *right, struct Cell *n)
{
	int labelX;
	char *l;
	GdkColor *color;
	
	if (axiomHeightSeq != NULL) axiomHeightSeq->height =
		MAX(axiomHeightSeq->height, top+ZERO_CELL_HEIGHT);
	l = LABEL(n);
	if ( n->symbol->color ) color = n->symbol->color;
	else
	{
		color = &defaultCellColor;
	}
	gdk_color_alloc(gdk_colormap_get_system(), color);
	gdk_gc_set_foreground(gc, color);

	gdk_draw_arc(gdk_pixmap, gc, TRUE,
			left, top,
			ZERO_CELL_WIDTH, ZERO_CELL_HEIGHT, 0, 360*64);

	gdk_gc_set_foreground(gc, &blackPen);

	gdk_draw_arc(gdk_pixmap, gc, FALSE,
			left, top,
			ZERO_CELL_WIDTH, ZERO_CELL_HEIGHT, 0, 360*64);

	labelX = left + (ZERO_CELL_WIDTH - label_width(l))/ 2;
	draw_label(labelX, top+ZERO_CELL_HEIGHT/2+LABEL_FONT_HEIGHT/2, l);
	*right = left+ZERO_CELL_WIDTH;

	return left+ZERO_CELL_WIDTH/2;
}

// draw a cell of arity 0
static int draw_zero_cell(int left, int bottom, int *right, struct Cell *n)
{
	int labelX;
	char *l;
	GdkColor *color;
	
	if (axiomHeightSeq != NULL) axiomHeightSeq->height =
		MIN(axiomHeightSeq->height, bottom-ZERO_CELL_HEIGHT);
	l = LABEL(n);
	if ( n->symbol->color ) color = n->symbol->color;
	else
	{
		color = &defaultCellColor;
	}
	gdk_color_alloc(gdk_colormap_get_system(), color);
	gdk_gc_set_foreground(gc, color);

	gdk_draw_arc(gdk_pixmap, gc, TRUE,
			left, bottom-ZERO_CELL_HEIGHT,
			ZERO_CELL_WIDTH, ZERO_CELL_HEIGHT, 0, 360*64);

	gdk_gc_set_foreground(gc, &blackPen);

	gdk_draw_arc(gdk_pixmap, gc, FALSE,
			left, bottom-ZERO_CELL_HEIGHT,
			ZERO_CELL_WIDTH, ZERO_CELL_HEIGHT, 0, 360*64);

	labelX = left + (ZERO_CELL_WIDTH - label_width(l))/ 2;
	draw_label(labelX, bottom-(ZERO_CELL_HEIGHT-LABEL_FONT_HEIGHT)/2, l);
	*right = left+ZERO_CELL_WIDTH;

	return left+ZERO_CELL_WIDTH/2;
}

static int draw_rule_many_cell(int left, int top, struct Cell *n)
{
	int labelX;
	char *l;
	GdkColor *color;
	GdkPoint points[3];

	l = LABEL(n);
	if ( n->symbol->color ) color = n->symbol->color;
	else
	{
		color = &defaultCellColor;
	}
	gdk_color_alloc(gdk_colormap_get_system(), color);
	gdk_gc_set_foreground(gc, color);
	points[0].x = left; points[0].y = top+MANY_CELL_HEIGHT;
	points[1].x = left+MANY_CELL_WIDTH; points[1].y = top+MANY_CELL_HEIGHT;
	points[2].x = left+MANY_CELL_WIDTH/2; points[2].y = top;
	gdk_draw_polygon (gdk_pixmap, gc, TRUE, points, 3);
	gdk_gc_set_foreground(gc, &blackPen);
	gdk_draw_polygon (gdk_pixmap, gc, FALSE, points, 3);
	labelX = left + (MANY_CELL_WIDTH - label_width(l))/2;
	draw_label(labelX, top+MANY_CELL_HEIGHT-3, l);
	
	return left+MANY_CELL_WIDTH/2;
}

// draw a cell of arity >= 1
static int draw_many_cell(int left, int bottom, struct Cell *n)
{
	int labelX;
	char *l;
	GdkColor *color;
	GdkPoint points[3];

	l = LABEL(n);
	if ( n->symbol->color ) color = n->symbol->color;
	else
	{
		color = &defaultCellColor;
	}
	gdk_color_alloc(gdk_colormap_get_system(), color);
	gdk_gc_set_foreground(gc, color);
	points[0].x = left; points[0].y = bottom-MANY_CELL_HEIGHT;
	points[1].x = left+MANY_CELL_WIDTH; points[1].y = bottom-MANY_CELL_HEIGHT;
	points[2].x = left+MANY_CELL_WIDTH/2; points[2].y = bottom;
	gdk_draw_polygon (gdk_pixmap, gc, TRUE, points, 3);
	gdk_gc_set_foreground(gc, &blackPen);
	gdk_draw_polygon (gdk_pixmap, gc, FALSE, points, 3);
	labelX = left + (MANY_CELL_WIDTH - label_width(l))/2;
	draw_label(labelX, bottom-MANY_CELL_HEIGHT+LABEL_FONT_HEIGHT+4, l);
	
	return left+MANY_CELL_WIDTH/2;
}

static int label_width(char *l)
{
	return strlen(l)*LABEL_FONT_WIDTH;
}

static void draw_rule_axiom_link(int lX, int lY, int rX, int rY, int h)
{
	/*
	g_print("(%d,%d) -> (%d,%d) cah=%d\n\n", lX, lY, rX, rY, h);
	*/

	g_assert(lX<rX); // axiom link extremities permuted
	g_assert(MAX(lY,rY)<=h); // bad axiom height value

	//gdk_draw_rectangle(gdk_pixmap,gc,FALSE,lX,MIN(lY,rY),rX-lX, h-MIN(lY, rY));

	gdk_draw_line(gdk_pixmap, gc, lX, lY, lX, h);
	gdk_draw_line(gdk_pixmap, gc, rX, rY, rX, h);
	if ( (rX-lX) < (2*AXIOM_CURVE) )
		draw_rule_narrow_axiom_link(lX, lY, rX, rY, h);
	else
		draw_rule_large_axiom_link(lX, lY, rX, rY, h);
}

static void draw_axiom_link(int lX, int lY, int rX, int rY, int h)
{
	/*
	g_print("(%d,%d) -> (%d,%d) cah=%d\n\n", lX, lY, rX, rY, h);
	*/

	g_assert(lX<rX); // axiom link extremities permuted
	g_assert(MIN(lY,rY)>=h); // bad axiom height value

	//gdk_draw_rectangle (gdk_pixmap, gc, FALSE, lX, h, rX-lX, MAX(lY, rY)-h);

	gdk_draw_line(gdk_pixmap, gc, lX, lY, lX, h);
	gdk_draw_line(gdk_pixmap, gc, rX, rY, rX, h);
	if ( (rX-lX) < (2*AXIOM_CURVE) ) draw_narrow_axiom_link(lX, lY, rX, rY, h);
	else draw_large_axiom_link(lX, lY, rX, rY, h);
}

static void draw_rule_narrow_axiom_link(int lX, int lY, int rX, int rY, int h)
{
	int w;
	
	w = rX-lX;
	gdk_draw_arc(gdk_pixmap, gc, FALSE, lX, h-w/2, w, w, 180*64, 180*64);
}

static void draw_narrow_axiom_link(int lX, int lY, int rX, int rY, int h)
{
	int w;
	
	w = rX-lX;
	gdk_draw_arc(gdk_pixmap, gc, FALSE, lX, h-w/2, w, w, 0, 180*64);
}

static void draw_rule_large_axiom_link(int lX, int lY, int rX, int rY, int h)
{
		gdk_draw_arc(gdk_pixmap, gc, FALSE,
				lX, h-AXIOM_CURVE, 2*AXIOM_CURVE, 2*AXIOM_CURVE, 180*64, 90*64);

		gdk_draw_line(gdk_pixmap, gc,
				lX+AXIOM_CURVE, h+AXIOM_CURVE, rX-AXIOM_CURVE, h+AXIOM_CURVE);

		gdk_draw_arc(gdk_pixmap, gc, FALSE,
				rX-2*AXIOM_CURVE, h-AXIOM_CURVE, 2*AXIOM_CURVE, 2*AXIOM_CURVE,
				270*64, 90*64);
}

static void draw_large_axiom_link(int lX, int lY, int rX, int rY, int h)
{

		gdk_draw_arc(gdk_pixmap, gc, FALSE,
				lX, h-AXIOM_CURVE, 2*AXIOM_CURVE, 2*AXIOM_CURVE, 90*64, 90*64);

		gdk_draw_line(gdk_pixmap, gc,
				lX+AXIOM_CURVE, h-AXIOM_CURVE, rX-AXIOM_CURVE, h-AXIOM_CURVE);

		gdk_draw_arc(gdk_pixmap, gc, FALSE,
				rX-2*AXIOM_CURVE, h-AXIOM_CURVE, 2*AXIOM_CURVE, 2*AXIOM_CURVE,
				0, 90*64);
}

static int draw_free_link(int left, int bottom, gchar *var, Cell *misc)
{
	int r;
	int x1, x2;
	
	x1 = draw_tree(left, bottom, &r, misc);
	left = r+HSPACE;

	gdk_draw_line(gdk_pixmap, gc, x1, bottom, x1, bottom+CUT_HEIGHT-20);
	
	x1 -= (strlen(var)*LABEL_FONT_WIDTH)/2;
	draw_free_port(x1, bottom+CUT_HEIGHT, &r, var);

	return left;
}

static int draw_cut(int left, int bottom, Cut *c)
{
	int r;
	int x1, x2;
	

	x1 = draw_tree(left, bottom, &r, c->cell1);
	left = r+HSPACE;
	x2 = draw_tree(left, bottom, &r, c->cell2);
	left = r+HSPACE;

	c->left = x1;
	c->right = x2;

	if (c==iSystem->net.currentCut)
	{
		gdk_gc_set_foreground(gc, &selectColor);
		draw_current_cut_link(x1,x2);
		gdk_gc_set_foreground(gc, &blackPen);
	}
	else
	{
		draw_normal_cut_link(x1,x2);
	}
	return left;
}

static void draw_normal_cut_link(int x1, int x2)
{
	gdk_draw_arc(gdk_pixmap, gc, FALSE,
				x1, PM_HEIGHT-MANY_CELL_HEIGHT-3*CUT_HEIGHT/2, x2-x1, 2*CUT_HEIGHT, 180*64, 180*64);
}

static void draw_current_cut_link(int x1, int x2)
{
	gdk_draw_arc(gdk_pixmap, gc, FALSE,
				x1-1, PM_HEIGHT-MANY_CELL_HEIGHT-3*CUT_HEIGHT/2,
				x2-x1+2, 2*CUT_HEIGHT+1, 180*64, 180*64);
	gdk_draw_arc(gdk_pixmap, gc, FALSE,
				x1, PM_HEIGHT-MANY_CELL_HEIGHT-3*CUT_HEIGHT/2,
				x2-x1, 2*CUT_HEIGHT, 180*64, 180*64);
	gdk_draw_arc(gdk_pixmap, gc, FALSE,
				x1+1, PM_HEIGHT-MANY_CELL_HEIGHT-3*CUT_HEIGHT/2,
				x2-x1-2, 2*CUT_HEIGHT-1, 180*64, 180*64);
}

static void draw_connection(int origX, int origY, int destX, int destY)
{
	int w = abs(origX-destX);
	int h = origY-destY;
	GdkPoint orig, dest;
	
	orig.x = origX; orig.y = origY;
	dest.x = destX; dest.y = destY;
	
	if (abs(dest.x-orig.x) <= 1)
	{
		gdk_draw_line(gdk_pixmap, gc, dest.x, orig.y, dest.x, dest.y);
	}
	else
		if (dest.x < orig.x)
		{
			gdk_draw_arc(gdk_pixmap, gc, FALSE,
					orig.x-w, orig.y-h/2,
					w, h,
					0, 90*64);

			gdk_draw_arc(gdk_pixmap, gc, FALSE,
					dest.x, dest.y-h/2, w, h, 180*64, 90*64);
		}
		else
		{
			gdk_draw_arc(gdk_pixmap, gc, FALSE,
					orig.x, orig.y-h/2, w, h, 90*64, 90*64);
			gdk_draw_arc(gdk_pixmap, gc, FALSE,
					dest.x-w, dest.y-h/2, w, h, 270*64, 90*64);
		}

}

static void close_application(GtkWidget *widget, GdkEvent *event, gpointer *data)
{
    gtk_main_quit();
}

void draw_rule(Rule *rule)
{
	int rootAr, rootX, portX;		// root arity, root X and port X
	int *subX;						// tab of the X of the subtrees
	int subLeft, subTop, subRight; 	// left, top, right value for each subtree
	struct Port *port;				// the port being examined
	int i;
	Cell *n;
	
	int x1, x2;
	GdkRectangle updateRect = {0, 0, RULE_WIDTH, RULE_HEIGHT};
	int left = HSPACE;
	int top = 0;
	int right;
	int bottom = top+VSPACE+2*MANY_CELL_HEIGHT;
	GdkPoint arrow[3];
	gchar label[2] = {96, 0};
	
	gdk_color_alloc(gdk_colormap_get_system(), &blackPen);
	gdk_gc_set_foreground(gc, &bgColor);
	gdk_draw_rectangle (rule_gdk_pixmap, gc, TRUE, 0, 0, RULE_WIDTH, RULE_HEIGHT);
	gdk_gc_set_foreground(gc, &blackPen);

	gdk_pixmap = rule_gdk_pixmap;
	
	if (ARITY(rule->cell1)==0)
		x1 = draw_zero_cell(left, bottom, &right, rule->cell1);
	else
	{
		x1 = draw_many_cell(left, bottom, rule->cell1);
		right = left+MANY_CELL_WIDTH;
		rootAr = ARITY(rule->cell1);
		for (i=0; i<=rootAr-1; i++) // draw connections
		{
			portX = x1 - MANY_CELL_WIDTH/2 + (i+1)*MANY_CELL_WIDTH/(rootAr+1);
			draw_connection(portX, bottom-MANY_CELL_HEIGHT, portX,
					bottom-MANY_CELL_HEIGHT-VSPACE);
			label[0]++;
			draw_label(portX-2, bottom-MANY_CELL_HEIGHT-VSPACE-5, label);
		}
	}

	left = right+HSPACE;

	if (ARITY(rule->cell2)==0)
		x2 = draw_zero_cell(left, bottom, &right, rule->cell2);
	else
	{
		x2 = draw_many_cell(left, bottom, rule->cell2);
		right = left+MANY_CELL_WIDTH;
		rootAr = ARITY(rule->cell2);
		for (i=0; i<=rootAr-1; i++) // draw connections
		{
			portX = x2 - MANY_CELL_WIDTH/2 + (i+1)*MANY_CELL_WIDTH/(rootAr+1);
			draw_connection(portX, bottom-MANY_CELL_HEIGHT, portX,
					bottom-MANY_CELL_HEIGHT-VSPACE);
			label[0]++;
			draw_label(portX-2, bottom-MANY_CELL_HEIGHT-VSPACE-5, label);
		}
	}

	gdk_draw_arc(gdk_pixmap, gc, FALSE,
				x1, bottom-CUT_HEIGHT, x2-x1, 2*CUT_HEIGHT, 180*64, 180*64);
	
	left = right;
	
	gdk_draw_line(gdk_pixmap, gc, left+30, bottom-MANY_CELL_HEIGHT, left+80,
			bottom-MANY_CELL_HEIGHT);
	arrow[0].x = left+85; arrow[0].y = bottom-MANY_CELL_HEIGHT;
	arrow[1].x = left+80; arrow[1].y = bottom-MANY_CELL_HEIGHT-5;
	arrow[2].x = left+80; arrow[2].y = bottom-MANY_CELL_HEIGHT+5;
	gdk_draw_polygon(gdk_pixmap, gc, TRUE, arrow, 3);
	
	left += 110;


	axiomHeightSeq = NULL;
	label[0] = 96;
	
	
	
	n=rule->cell1; rootAr = ARITY(n);
	if ( rootAr )
	{
	subX = g_malloc( rootAr*sizeof(int) );
	subLeft = calculate_subLeft(left, n);
	// Deux facons de centrer la racine : par rapport aux deux noeuds "extremes"
	// ou en faisant la moyenne des abscisses des sous arbres.
	subTop = top+MANY_CELL_HEIGHT+VSPACE;
	rootX=0;
	for (i=1; i<=rootAr; i++) // draw sub trees
	{
		port = &PORT(n,i);
		if (port->num != 0)
		{
			if ( LABEL(port->cell) == NULL ) // interface cell
			{
				g_assert( FALSE ); // no interface in a rule
			}
			else // axiom link
			{
				subRight = subLeft+AXIOM_WIDTH;
				subX[i-1] = subLeft+AXIOM_WIDTH/2;
				subLeft = subRight+HSPACE;
				handle_rule_axiom_link(port, subX[i-1], subTop);
			}
		}
		else // cell
		{
			subX[i-1]=draw_rule_tree(subLeft, subTop, &subRight,port->cell);
			subLeft = subRight+HSPACE;
		}
		rootX += subX[i-1];
	}
	// rootX = (subX[rootAr-1]+subX[0])/2;
	rootX = rootX/rootAr;
	g_assert(rootX >= left+MANY_CELL_WIDTH/2); // bad rootX
	for (i=0; i<=rootAr-1; i++) // draw connections
	{
		portX = rootX - MANY_CELL_WIDTH/2 + (i+1)*MANY_CELL_WIDTH/(rootAr+1);
		//draw_connection(subX[i], subTop, portX, top+MANY_CELL_HEIGHT);
		draw_connection(subX[i], subTop, subX[i], top+MANY_CELL_HEIGHT);
		label[0]++;
		draw_label(subX[i]-2, top+MANY_CELL_HEIGHT-5, label);
	}
	right = MAX(subRight, rootX+MANY_CELL_WIDTH/2);
	g_free(subX);
	left = right + HSPACE;
	}
	
	
	n=rule->cell2; rootAr = ARITY(n);
	if ( rootAr )
	{
	subX = g_malloc( rootAr*sizeof(int) );
	subLeft = calculate_subLeft(left, n);
	// Deux facons de centrer la racine : par rapport aux deux noeuds "extremes"
	// ou en faisant la moyenne des abscisses des sous arbres.
	subTop = top+MANY_CELL_HEIGHT+VSPACE;
	rootX=0;
	for (i=1; i<=rootAr; i++) // draw sub trees
	{
		port = &PORT(n,i);
		if (port->num != 0)
		{
			if ( LABEL(port->cell) == NULL ) // interface cell
			{
				g_assert( FALSE ); // no interface in a rule
			}
			else // axiom link
			{
				subRight = subLeft+AXIOM_WIDTH;
				subX[i-1] = subLeft+AXIOM_WIDTH/2;
				subLeft = subRight+HSPACE;
				handle_rule_axiom_link(port, subX[i-1], subTop);
			}
		}
		else // cell
		{
			subX[i-1]=draw_rule_tree(subLeft, subTop, &subRight,port->cell);
			subLeft = subRight+HSPACE;
		}
		rootX += subX[i-1];
	}
	// rootX = (subX[rootAr-1]+subX[0])/2;
	rootX = rootX/rootAr;
	g_assert(rootX >= left+MANY_CELL_WIDTH/2); // bad rootX
	for (i=0; i<=rootAr-1; i++) // draw connections
	{
		portX = rootX - MANY_CELL_WIDTH/2 + (i+1)*MANY_CELL_WIDTH/(rootAr+1);
		//draw_connection(subX[i], subTop, portX, top+MANY_CELL_HEIGHT);
		draw_connection(subX[i], subTop, subX[i], top+MANY_CELL_HEIGHT);
		label[0]++;
		draw_label(subX[i]-2, top+MANY_CELL_HEIGHT-5, label);
	}
	right = MAX(subRight, rootX+MANY_CELL_WIDTH/2);
	g_free(subX);
	}

	
	


	gtk_widget_draw(rulePixmap, &updateRect);
	gdk_pixmap = net_gdk_pixmap;
}

static void open_rule_window(void)
{
	GtkWidget *window;
    GtkWidget *scrolled_window;

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_signal_connect (GTK_OBJECT (window), "delete_event",
                        GTK_SIGNAL_FUNC (close_application), NULL);
    gtk_signal_connect (GTK_OBJECT (window), "destroy",
                        GTK_SIGNAL_FUNC (close_application), NULL);
    gtk_window_set_title (GTK_WINDOW (window), "next rule");
    gtk_container_border_width (GTK_CONTAINER (window), 0);
    gtk_widget_set_usize(window, 100, 100);
    gtk_widget_realize (window);

    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_container_border_width (GTK_CONTAINER (scrolled_window), 10);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
                                    GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_widget_show (scrolled_window);
	
	gtk_container_add (GTK_CONTAINER (window), scrolled_window);

	rule_gdk_pixmap= gdk_pixmap_new (window->window, RULE_WIDTH, RULE_HEIGHT, -1);
	rulePixmap = gtk_pixmap_new( rule_gdk_pixmap, NULL );
	//gtk_container_add (GTK_CONTAINER (window), rulePixmap);
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window),
			rulePixmap);
	gdk_gc_set_foreground(gc, &bgColor);
	gdk_draw_rectangle (rule_gdk_pixmap, gc, TRUE, 0, 0, RULE_WIDTH, RULE_HEIGHT);
	gdk_gc_set_foreground(gc, &blackPen);
	gtk_widget_show(rulePixmap);
	gtk_widget_show(window);
}

void open_window(void)
{
	GtkWidget *window;
    GtkWidget *scrolled_window;
	GtkWidget *button;
	GtkWidget *hbox;
	GtkWidget *hbox1;
	GtkWidget *vbox;
	GtkWidget *vscrollbar;

	// GtkAdjustment *adj;
	// GtkWidget *spinner;

    window = gtk_dialog_new ();

	gtk_signal_connect (GTK_OBJECT (window), "button_press_event",
			  GTK_SIGNAL_FUNC (net_clicked), (gpointer) NULL);


    gtk_signal_connect (GTK_OBJECT (window), "delete_event",
                        GTK_SIGNAL_FUNC (close_application), NULL);

    gtk_signal_connect (GTK_OBJECT (window), "destroy",
                        GTK_SIGNAL_FUNC (close_application), NULL);

    gtk_window_set_title (GTK_WINDOW (window), "net");
    gtk_container_border_width (GTK_CONTAINER (window), 0);
    gtk_widget_set_usize(window, 400, 300);
    gtk_widget_realize (window);
	gc = window->style->black_gc;

    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_container_border_width (GTK_CONTAINER (scrolled_window), 10);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
                                    GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start (GTK_BOX (GTK_DIALOG(window)->vbox), scrolled_window, 
			TRUE, TRUE, 0);
    gtk_widget_show (scrolled_window);
	gdk_pixmap = gdk_pixmap_new (window->window, PM_WIDTH, PM_HEIGHT, -1);
	pixmap = gtk_pixmap_new( gdk_pixmap, NULL );

	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window),
			pixmap);
	gtk_widget_show(pixmap);

    hbox = gtk_hbox_new (FALSE, 0);
    hbox1 = gtk_hbox_new (TRUE, 0);

	// adj = (GtkAdjustment *) gtk_adjustment_new (1.0, 1.0, 31.0, 1.0, 5.0, 0.0);
	// spinner = gtk_spin_button_new (adj, 0, 0);
	// gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner), TRUE);
	// gtk_spin_button_set_shadow_type(GTK_SPIN_BUTTON (spinner), GTK_SHADOW_OUT);
    // gtk_widget_show(spinner);
    // gtk_box_pack_start (GTK_BOX (hbox), spinner, FALSE, TRUE, 0);
	// gtk_signal_connect (GTK_OBJECT (adj), "value_changed",
	// GTK_SIGNAL_FUNC (change_cut), (gpointer) spinner);

    button = gtk_button_new_with_label("Reduce");
    gtk_signal_connect (GTK_OBJECT (button), "clicked",
			GTK_SIGNAL_FUNC (reduce_callback), NULL);
    gtk_widget_show(button);
    gtk_box_pack_start (GTK_BOX (hbox1), button, TRUE, TRUE, 0);

    button = gtk_button_new_with_label("Reduce all");
    gtk_signal_connect (GTK_OBJECT (button), "clicked",
			GTK_SIGNAL_FUNC (reduce_all_callback), NULL);
    gtk_widget_show(button);
    gtk_box_pack_start (GTK_BOX (hbox1), button, TRUE, TRUE, 0);

    button = gtk_button_new_with_label("Reopen");
    gtk_signal_connect (GTK_OBJECT (button), "clicked",
			GTK_SIGNAL_FUNC (reopen_callback), NULL);
    gtk_widget_show(button);
    gtk_box_pack_start (GTK_BOX (hbox1), button, TRUE, TRUE, 0);

    button = gtk_button_new_with_label("Open...");
    gtk_signal_connect (GTK_OBJECT (button), "clicked",
			GTK_SIGNAL_FUNC (open_callback), NULL);
    gtk_widget_show(button);
    gtk_box_pack_start (GTK_BOX (hbox1), button, TRUE, TRUE, 0);

    gtk_widget_show(hbox1);
    gtk_widget_show(hbox);
    button = gtk_button_new_with_label("Quit");
    gtk_signal_connect_object (GTK_OBJECT (button), "clicked",
			GTK_SIGNAL_FUNC (gtk_widget_destroy),
			GTK_OBJECT (window));
    gtk_widget_show(button);
    gtk_box_pack_start (GTK_BOX (hbox1), button, TRUE, TRUE, 0);


    gtk_box_pack_start (GTK_BOX (hbox), hbox1, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(window)->action_area),hbox,TRUE,TRUE,0);

	gdk_color_parse(BACKGROUND_COLOR, &bgColor);
	gdk_color_alloc(gdk_colormap_get_system(), &bgColor);
	gdk_gc_set_foreground(gc, &bgColor);
	gdk_draw_rectangle (gdk_pixmap, gc, TRUE, 0, 0, PM_WIDTH, PM_HEIGHT);

	gdk_color_parse(SELECT_COLOR, &selectColor);
	gdk_color_alloc(gdk_colormap_get_system(), &selectColor);

	//vscrollbar = GTK_SCROLLED_WINDOW (scrolled_window)->vscrollbar;

	gdk_color_parse(DEFAULT_CELL_COLOR, &defaultCellColor);

	gdk_gc_set_foreground(gc, &blackPen);
	gtk_widget_show(window);
	open_rule_window();
	net_gdk_pixmap = gdk_pixmap;
}

void draw_net (struct Net *net)
{
	int left = HSPACE;
	GSList *ptr;
	Arity i;
	Cell *interface = INTERFACE(iSystem);
	int r;
	int x1, x2;
	int bottom = PM_HEIGHT-MANY_CELL_HEIGHT - CUT_HEIGHT/2;
	
	gdk_color_alloc(gdk_colormap_get_system(), &blackPen);
	gdk_gc_set_foreground(gc, &bgColor);
	gdk_draw_rectangle (gdk_pixmap, gc, TRUE, 0, 0, PM_WIDTH, PM_HEIGHT);
	gdk_gc_set_foreground(gc, &blackPen);
	axiomHeightSeq = NULL;
	ptr = net->cutList;
	while ( ptr!=NULL )
	{
		left=draw_cut(left,PM_HEIGHT-MANY_CELL_HEIGHT - CUT_HEIGHT/2,
				CUT_PTR(ptr->data));
		ptr = ptr->next;
	}
	
	// les "liens libres"
	for (i=1; i<=ARITY(interface); i++)
	{
		if (PORT(interface,i).num == 0)
		{
			x1 = draw_tree(left, bottom, &r, PORT(interface,i).cell);
			left = r+HSPACE;
			gdk_draw_line(gdk_pixmap, gc, x1, bottom, x1, bottom+CUT_HEIGHT-20);
			x1 -= (strlen(FREE_PORT_LABEL(iSystem,i))*LABEL_FONT_WIDTH)/2;
			draw_free_port(x1, bottom+CUT_HEIGHT, &r, FREE_PORT_LABEL(iSystem,i));
		}
		else
			if (LABEL(PORT(interface,i).cell)==NULL && PORT(interface,i).num>i)
			{
				x1 = draw_free_port(left, bottom, &r,
						FREE_PORT_LABEL(iSystem,PORT(interface,i).num));
				left = r+HSPACE;
				gdk_draw_line(gdk_pixmap, gc, x1, bottom, x1,
						bottom+CUT_HEIGHT-20);
				x1 -= (strlen(FREE_PORT_LABEL(iSystem,i))*LABEL_FONT_WIDTH)/2;
				draw_free_port(x1, bottom+CUT_HEIGHT, &r,
						FREE_PORT_LABEL(iSystem,i));
			}
			else
			{
				// nothing to do
			}
	}

	gtk_widget_draw(pixmap, &updateRect);
}

static void print_axiomHeightSeq(void)
{
	struct AxiomHeightSeq *ptr;
	
	ptr = axiomHeightSeq;
	g_print("------------ BEGIN print_axiomHeightSeq ------------\n");
	while (ptr !=NULL)
	{
		g_print("%d - height=%d\n", ptr->id, ptr->height);
		ptr=ptr->next;
	}
	g_print("------------ END   print_axiomHeightSeq ------------\n");
}

static void reduce_all_callback (GtkWidget *widget, gpointer data)
{
	guint32 count = 0;

	while ( eliminate_cut(iSystem) ) count++;

	// while ( iSystem->net.cutList )
	// {
	// eliminate_cut(iSystem);
	// count++;
	// }

	g_print("--------- %10d cut elimination(s)            ---------\n", count);
	print_net(iSystem);
	if ( count ) draw_net(&iSystem->net);
	draw_next_rule( iSystem );
}

static void reduce_callback (GtkWidget *widget, gpointer data)
{
	GSList *ruleList;
	GSList *cutList = iSystem->net.cutList;
	Rule *rule;
	Cut *cut;

	if ( eliminate_cut(iSystem) )
	{
		print_net(iSystem);
		draw_net(&iSystem->net);
		draw_next_rule(iSystem);
	}
}

void draw_next_rule(System *s)
{
	GSList *ruleList;
	Cut *cut = s->net.currentCut;
	Rule *rule;
	GdkRectangle updateRect = {0, 0, RULE_WIDTH, RULE_HEIGHT};
	
	if ( cut )
	{
		ruleList = g_slist_find_custom(s->ruleList, cut, are_cuts_different);
		if ( ruleList )
		{
			rule = RULE_PTR(ruleList->data);
			draw_rule( rule );
		}
		else 
		{
			gdk_pixmap = rule_gdk_pixmap;
			gdk_gc_set_foreground(gc, &bgColor);
			gdk_draw_rectangle (rule_gdk_pixmap, gc, TRUE, 0, 0, RULE_WIDTH,
					RULE_HEIGHT);
			gdk_gc_set_foreground(gc, &blackPen);
			draw_label(20, 20, "Rule not found.");
			gtk_widget_draw(rulePixmap, &updateRect);
			gdk_pixmap = net_gdk_pixmap;
		}
	}
	else
	{
		gdk_pixmap = rule_gdk_pixmap;
		gdk_gc_set_foreground(gc, &bgColor);
		gdk_draw_rectangle (rule_gdk_pixmap, gc, TRUE, 0, 0, RULE_WIDTH,
				RULE_HEIGHT);
		gdk_gc_set_foreground(gc, &blackPen);
		draw_label(20, 20, "Net reduced.");
		gtk_widget_draw(rulePixmap, &updateRect);
		gdk_pixmap = net_gdk_pixmap;
	}
}


/* Get the selected filename and print it to the console */
static void file_ok_sel (GtkWidget *w, GtkFileSelection *fs)
{
	gchar *filename;
	
	filename = gtk_file_selection_get_filename (GTK_FILE_SELECTION (fs));
	strcpy(currentFilename, filename);
	g_print("filename = %s\n", filename);
	yyin = fopen(currentFilename, "r");
	yyparse();
	close(yyin);
	draw_net(&iSystem->net);
	draw_next_rule( iSystem );
	gtk_widget_destroy(filew);
}

static void destroy (GtkWidget *widget, gpointer data)
{
    gtk_main_quit ();
}

static void reopen_callback (GtkWidget *widget, gpointer data)
{
	if ( currentFilename[0] == '\0' ) g_print("no current file.\n");
	else
	{
		g_print("reopen ... %s\n",currentFilename);
		yyin = fopen(currentFilename, "r");
		yyparse();
		close(yyin);
		draw_net(&iSystem->net);
		draw_next_rule( iSystem );
	}
}

void open_callback (GtkWidget *widget, gpointer data)
{
    
    /* Create a new file selection widget */
    filew = gtk_file_selection_new ("File selection");
    
    gtk_signal_connect (GTK_OBJECT (filew), "destroy",
			  GTK_SIGNAL_FUNC (gtk_widget_destroy), &filew);
    /* Connect the ok_button to file_ok_sel function */
    gtk_signal_connect (GTK_OBJECT (GTK_FILE_SELECTION (filew)->ok_button),
			"clicked", (GtkSignalFunc) file_ok_sel, filew );
    
    /* Connect the cancel_button to destroy the widget */
    gtk_signal_connect_object (
			GTK_OBJECT (GTK_FILE_SELECTION (filew)->cancel_button), "clicked",
			GTK_SIGNAL_FUNC (gtk_widget_destroy),
			GTK_OBJECT (filew));
    
    /* Lets set the filename, as if this were a save dialog, and we are giving
     a default filename */
    //gtk_file_selection_set_filename (GTK_FILE_SELECTION(filew), "penguin.png");
    
    gtk_widget_show(filew);
}

// static void change_cut(GtkWidget *widget, GtkSpinButton *spin)
// {
//	cutNumber = gtk_spin_button_get_value_as_int (spin);
//	g_print("cutNumber = %d\n", cutNumber);
// }

static gint net_clicked(GtkWidget *widget, GdkEventButton *event, gpointer ref)
{
	GSList	*ptr;
	Cut		*oldCut;
	Cut		*newCut;
	int		x;

	x = (int)event->x;


	ptr = g_slist_find_custom(iSystem->net.cutList, GINT_TO_POINTER(x),
					is_outside_cut);
	if ( ptr )
	{
		if (event->type == GDK_2BUTTON_PRESS) // the cut is already selected
		{
			eliminate_cut(iSystem);
			print_net(iSystem);
			draw_net(&iSystem->net);
			draw_next_rule(iSystem);
		}
		else
		{
			oldCut = iSystem->net.currentCut;
			newCut = CUT_PTR(ptr->data);
			iSystem->net.currentCut = newCut;
			// deselect the old current cut
			gdk_gc_set_foreground(gc, &bgColor);
			draw_current_cut_link(oldCut->left,oldCut->right);
			gdk_gc_set_foreground(gc, &blackPen);
			draw_normal_cut_link(oldCut->left,oldCut->right);
			// select the new current cut
			gdk_gc_set_foreground(gc, &selectColor);
			draw_current_cut_link(newCut->left,newCut->right);
			gdk_gc_set_foreground(gc, &blackPen);
			gtk_widget_draw(pixmap, &updateRect);
			draw_next_rule(iSystem);
		}
	}
	else
			g_print("You missed it !\n");
}

gboolean is_outside_cut(gconstpointer cut, gconstpointer x)
{
		return ((GPOINTER_TO_INT(x) < CUT_PTR(cut)->left) ||
						(GPOINTER_TO_INT(x) > CUT_PTR(cut)->right));
}
