// ===============================================================================
// main.c (Dec. 17. 1998)
// Last modified: Dec. 17. 1998
// ===============================================================================


// INCLUDES ----------------------------------------------------------------------

#include "types.h"
#include "layout.h"
#include "drawing.h"
#include <gtk/gtk.h>
#include <stdio.h>


// EXTERN GLOBAL VARIABLES -------------------------------------------------------

System		*iSystem;
gchar		currentFilename[100] = "";
extern FILE	*yyin;

// MAIN FUNCTION -----------------------------------------------------------------

int main(int argc, char **argv)
{
	System *s;

    gtk_init (&argc, &argv);
	s = g_malloc( sizeof(System) );
	s->symbolList = NULL;
	s->ruleList = NULL;
	s->net.cutList = NULL;
	s->net.freePortLabelTable = NULL;
	s->net.interface = NULL;
	iSystem = s;

	if (argc>1)
	{
		strcpy(currentFilename, argv[1]);
		yyin=fopen(argv[1], "r");
		yyparse();
		//	print_symbol_list(s);
		//	print_all_rules(s);
		//	print_free_ports(s);
		//	print_net(s);
		fclose(yyin);
		open_window();
		draw_net(&iSystem->net);
		draw_next_rule( s );
	}
	else
	{
		open_window();
		open_callback(NULL, NULL);
	}
	gtk_main();
}
