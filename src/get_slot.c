// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2024
// Hanged Bunny Studio 2014-2022
// EFRITS SAS 2022-2024
//
// Pylos

#include		"program.h"

t_slot			*get_slot(t_slot		*s,
				  int			siz,
				  int			x,
				  int			y,
				  int			z)
{
  if (x < 0 || y < 0 || z < 0)
    return (NULL);
  if (z >= siz)
    return (NULL);
  if (x >= (siz - z))
    return (NULL);
  if (y >= (siz - z))
    return (NULL);
  return (&s[z * siz * siz + y * siz + x]);
}

