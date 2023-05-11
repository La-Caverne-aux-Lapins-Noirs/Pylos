// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2024
// Hanged Bunny Studio 2014-2022
// EFRITS SAS 2022-2024
//
// Pylos

#include		"program.h"

t_bunny_response	ingame_loop(t_program		*prog)
{
  const double		omega = 90;

  if (bunny_get_keyboard()[BKS_UP])
    prog->ingame.rotation.x -= (omega / 180.0) * M_PI * bunny_get_delay();
  if (bunny_get_keyboard()[BKS_DOWN])
    prog->ingame.rotation.x += (omega / 180.0) * M_PI * bunny_get_delay();
  if (prog->ingame.rotation.x < M_PI / 16)
    prog->ingame.rotation.x = M_PI / 16;
  if (prog->ingame.rotation.x > M_PI / 2)
    prog->ingame.rotation.x = M_PI / 2;

  if (bunny_get_keyboard()[BKS_LEFT])
    prog->ingame.rotation.y -= (omega / 180.0) * M_PI * bunny_get_delay();
  if (bunny_get_keyboard()[BKS_RIGHT])
    prog->ingame.rotation.y += (omega / 180.0) * M_PI * bunny_get_delay();
  return (GO_ON);
}
