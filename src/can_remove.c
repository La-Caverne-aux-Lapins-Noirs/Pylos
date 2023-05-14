// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2024
// Hanged Bunny Studio 2014-2022
// EFRITS SAS 2022-2024
//
// Pylos

#include		"program.h"

bool			can_removes(t_program		*prog,
				    int			x,
				    int			y,
				    int			z,
				    t_slot		player)
{
  t_slot		*slot[4];

  slot[0] = get_slotp(prog, x, y, z);
  if (slot[0] == NULL)
    return (false);
  if (*slot[0] != player)
    return (false);
  if (z == prog->ingame.size - 1)
    return (true); // Normalement ca n'arrive pas vu que le jeu s'arrete

  slot[0] = get_slotp(prog, x - 0, y - 0, z + 1);
  slot[1] = get_slotp(prog, x - 0, y - 1, z + 1);
  slot[2] = get_slotp(prog, x - 1, y - 0, z + 1);
  slot[3] = get_slotp(prog, x - 1, y - 1, z + 1);

  if (slot[0] && *slot[0] > EMPTY)
    return (false);
  if (slot[1] && *slot[1] > EMPTY)
    return (false);
  if (slot[2] && *slot[2] > EMPTY)
    return (false);
  if (slot[3] && *slot[3] > EMPTY)
    return (false);

  return (true);
}

