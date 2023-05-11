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
  if (state == GO_UP && sym == BKS_ESCAPE)
    {
      if ((prog->context -= 1) < 0)
	return (EXIT_ON_SUCCESS);
      return (SWITCH_CONTEXT);
    }
  return (GO_ON);
}
