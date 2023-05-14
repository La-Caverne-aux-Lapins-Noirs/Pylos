// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2024
// Hanged Bunny Studio 2014-2022
// EFRITS SAS 2022-2024
//
// Pylos

#include		"program.h"

void			all_places(t_program		*prog,
				   t_slot		*slot[static 4 * 4])
{
  t_slot		*sl;
  int			i;
  int			x;
  int			y;
  int			z;

  i = 0;
  for (z = 0; z < prog->ingame.size; ++z)
    for (y = 0; y < prog->ingame.size; ++y)
      for (x = 0; x < prog->ingame.size; ++x)
	if ((sl = can_place(prog, x, y, z)) != NULL)
	  slot[i++] = sl;
}

