// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2024
// Hanged Bunny Studio 2014-2022
// EFRITS SAS 2022-2024
//
// Pylos

#include		"program.h"

t_slot			*can_place(t_program		*program,
				   int			x,
				   int			y,
				   int			z)
{
  t_slot		*slot[4];

  if ((slot[0] = get_slotp(program, x, y, z)) == NULL)
    return (NULL);
  if (*slot[0] > EMPTY)
    return (NULL);
  if (z == 0)
    return (slot[0]);

  slot[0] = get_slotp(program, x + 0, y + 0, z - 1);
  slot[1] = get_slotp(program, x + 0, y + 1, z - 1);
  slot[2] = get_slotp(program, x + 1, y + 0, z - 1);
  slot[3] = get_slotp(program, x + 1, y + 1, z - 1);
  if (*slot[0] <= EMPTY)
    return (NULL);
  if (*slot[1] <= EMPTY)
    return (NULL);
  if (*slot[2] <= EMPTY)
    return (NULL);
  if (*slot[3] <= EMPTY)
    return (NULL);
  return (get_slotp(program, x, y, z));
}


