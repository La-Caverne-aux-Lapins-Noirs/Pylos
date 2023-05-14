// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2024
// Hanged Bunny Studio 2014-2022
// EFRITS SAS 2022-2024
//
// Pylos

#include		"program.h"

bool			detect_bonus(t_program		*prog,
				     int		x,
				     int		y,
				     int		z)
{
  t_slot		*ref = get_slotp(prog, x, y, z);
  t_slot		*tmp;
  bool			bonus;
  int			cnt;
  int			i;

  // Les lignes
  bonus = true;
  for (i = 0; i < y - z; ++i)
    if ((tmp = get_slotp(prog, x, i, z)) == NULL)
      bonus = false;
    else if (*tmp != *ref)
      bonus = false;
  if (bonus)
    return (true);
  for (i = 0; i < y - z; ++i)
    if ((tmp = get_slotp(prog, i, y, z)) == NULL)
      bonus = false;
    else if (*tmp != *ref)
      bonus = false;
  if (bonus)
    return (true);

  // Les carrés
  cnt = 0;
  tmp = get_slotp(prog, x + 1, y + 0, z);
  cnt += tmp == NULL ? 0 : *tmp == *ref ? 1 : 0;
  tmp = get_slotp(prog, x + 0, y + 1, z);
  cnt += tmp == NULL ? 0 : *tmp == *ref ? 1 : 0;
  tmp = get_slotp(prog, x + 1, y + 1, z);
  cnt += tmp == NULL ? 0 : *tmp == *ref ? 1 : 0;
  if (cnt == 3)
    return (true);

  cnt = 0;
  tmp = get_slotp(prog, x - 1, y + 0, z);
  cnt += tmp == NULL ? 0 : *tmp == *ref ? 1 : 0;
  tmp = get_slotp(prog, x + 0, y - 1, z);
  cnt += tmp == NULL ? 0 : *tmp == *ref ? 1 : 0;
  tmp = get_slotp(prog, x - 1, y - 1, z);
  cnt += tmp == NULL ? 0 : *tmp == *ref ? 1 : 0;
  if (cnt == 4)
    return (true);

  cnt = 0;
  tmp = get_slotp(prog, x + 1, y + 0, z);
  cnt += tmp == NULL ? 0 : *tmp == *ref ? 1 : 0;
  tmp = get_slotp(prog, x + 0, y - 1, z);
  cnt += tmp == NULL ? 0 : *tmp == *ref ? 1 : 0;
  tmp = get_slotp(prog, x + 1, y - 1, z);
  cnt += tmp == NULL ? 0 : *tmp == *ref ? 1 : 0;
  if (cnt == 3)
    return (true);

  cnt = 0;
  tmp = get_slotp(prog, x - 1, y + 0, z);
  cnt += tmp == NULL ? 0 : *tmp == *ref ? 1 : 0;
  tmp = get_slotp(prog, x + 0, y + 1, z);
  cnt += tmp == NULL ? 0 : *tmp == *ref ? 1 : 0;
  tmp = get_slotp(prog, x - 1, y + 1, z);
  cnt += tmp == NULL ? 0 : *tmp == *ref ? 1 : 0;
  if (cnt == 3)
    return (true);

  return (false);
}
