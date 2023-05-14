// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2024
// Hanged Bunny Studio 2014-2022
// EFRITS SAS 2022-2024
//
// Pylos

#include		"program.h"

bool			removes(t_program		*prog,
				int			x,
				int			y,
				int			z,
				t_slot			player)
{
  t_slot		*slot;

  if (can_removes(prog, x, y, z, player) == false)
    return (false);
  slot = get_slotp(prog, x, y, z);
  *slot = EMPTY;
  if (prog->ingame.turn == BLACKBALLS)
    prog->ingame.balls1 += 1;
  if (prog->ingame.turn == WHITEBALLS)
    prog->ingame.balls2 += 1;
  return (true);
}
