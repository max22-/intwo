// -------------------------------------------------------------------------------
// engine.h
// This module handles cut elimination (October 15. 1998)
// Last modified: Dec. 17. 1998
// -------------------------------------------------------------------------------


// INCLUDES ----------------------------------------------------------------------

#include "types.h"
#include "utility.h"


// EXTERN FUNCTION PROTOTYPES ----------------------------------------------------

int eliminate_cut(System *s);
gboolean are_cuts_different(gconstpointer cut1, gconstpointer cut2);



