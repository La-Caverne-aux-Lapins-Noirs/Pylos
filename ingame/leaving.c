// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2024
// Hanged Bunny Studio 2014-2022
// EFRITS SAS 2022-2024
//
// Pylos

#include		"program.h"

void			ingame_leaving(t_bunny_response	ret,
				       t_program	*prog)
{
  (void)ret;
  if (prog->ingame.ball)
    bunny_delete_clipable(prog->ingame.ball);
  if (prog->ingame.normal_ball)
    bunny_delete_clipable(prog->ingame.normal_ball);
  prog->ingame.ball = NULL;

  if (prog->ingame.slots)
    bunny_free(prog->ingame.slots);
}
