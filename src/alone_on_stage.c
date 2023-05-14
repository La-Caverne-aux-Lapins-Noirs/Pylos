// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2024
// Hanged Bunny Studio 2014-2022
// EFRITS SAS 2022-2024
//
// Pylos

#include		"program.h"

bool			alone_on_stage(t_program	*prog,
				       t_ball		*pos,
				       int		siz)
{
  int			i;

  for (i = 0; i < siz; ++i)
    if (fabs(pos[i].pos.z - prog->ingame.cursor.z) < 0.1)
      return (false);
  return (true);
}
