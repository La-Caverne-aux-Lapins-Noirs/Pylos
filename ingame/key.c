// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2024
// Hanged Bunny Studio 2014-2022
// EFRITS SAS 2022-2024
//
// Pylos

#include		"program.h"

t_bunny_response	ingame_key(t_bunny_event_state	state,
				   t_bunny_keysym	sym,
				   t_program		*prog)
{
  if (state == GO_DOWN)
    {
      if (sym == BKS_ESCAPE)
	{
	  if ((int)(prog->context -= 1) < 0)
	    return (EXIT_ON_SUCCESS);
	  return (SWITCH_CONTEXT);
	}

      if ((prog->ingame.turn == BLACKBALLS && prog->ingame.clients[1] == -1)
	  ||
	  (prog->ingame.turn == WHITEBALLS && prog->ingame.clients[0] == -1)
	  )
	{
	  if (sym == BKS_PAGEUP)
	    movement(prog, PYLOS_LEVEL_UP);
	  if (sym == BKS_PAGEDOWN)
	    movement(prog, PYLOS_LEVEL_DOWN);
	  
	  if (sym == BKS_LEFT)
	    movement(prog, PYLOS_GO_LEFT);
	  if (sym == BKS_RIGHT)
	    movement(prog, PYLOS_GO_RIGHT);
	 
	  if (sym == BKS_UP)
	    movement(prog, PYLOS_GO_UP);
	  if (sym == BKS_DOWN)
	    movement(prog, PYLOS_GO_DOWN);

	  if ((sym == BKS_LCONTROL || sym == BKS_RCONTROL))
	    movement(prog, PYLOS_TAKE);
	  if (sym == BKS_SPACE)
	    movement(prog, PYLOS_PUT);
	}
    }
  return (GO_ON);
}
