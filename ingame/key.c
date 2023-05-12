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
  if (state == GO_UP)
    {
      if (sym == BKS_ESCAPE)
	{
	  if ((prog->context -= 1) < 0)
	    return (EXIT_ON_SUCCESS);
	  return (SWITCH_CONTEXT);
	}
      if (sym == BKS_E)
	prog->ingame.cursor.z = bunny_clamp(prog->ingame.cursor.z + 1, 0, prog->ingame.size - 1);
      if (sym == BKS_A)
	prog->ingame.cursor.z = bunny_clamp(prog->ingame.cursor.z - 1, 0, prog->ingame.size - 1);

      if (sym == BKS_Q || sym == BKS_A)
	prog->ingame.cursor.x = bunny_clamp(prog->ingame.cursor.x - 1, 0, prog->ingame.size - 1);
      if (sym == BKS_D)
	prog->ingame.cursor.x = bunny_clamp(prog->ingame.cursor.x + 1, 0, prog->ingame.size - 1);

      if (sym == BKS_Z || sym == BKS_W)
	prog->ingame.cursor.y = bunny_clamp(prog->ingame.cursor.y - 1, 0, prog->ingame.size - 1);
      if (sym == BKS_S)
	prog->ingame.cursor.y = bunny_clamp(prog->ingame.cursor.y + 1, 0, prog->ingame.size - 1);
    }
  return (GO_ON);
}
