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
  if (prog->ingame.rotation.x < M_PI / 2)
    prog->ingame.rotation.x = M_PI / 2;
  if (prog->ingame.rotation.x > M_PI)
    prog->ingame.rotation.x = M_PI;

  if (bunny_get_keyboard()[BKS_LEFT])
    prog->ingame.rotation.y -= (omega / 180.0) * M_PI * bunny_get_delay();
  if (bunny_get_keyboard()[BKS_RIGHT])
    prog->ingame.rotation.y += (omega / 180.0) * M_PI * bunny_get_delay();

  if (bunny_get_keyboard()[BKS_NUMPAD4])
    {
      prog->ingame.translation.x = bunny_clamp(prog->ingame.translation.x - 1.0 * bunny_get_delay(), -2, +2);
    }
  if (bunny_get_keyboard()[BKS_NUMPAD6])
    {
      prog->ingame.translation.x = bunny_clamp(prog->ingame.translation.x + 1.0 * bunny_get_delay(), -2, +2);
    }
  if (bunny_get_keyboard()[BKS_NUMPAD8])
    {
      prog->ingame.translation.y = bunny_clamp(prog->ingame.translation.y - 1.0 * bunny_get_delay(), -2, +2);
    }
  if (bunny_get_keyboard()[BKS_NUMPAD2])
    {
      prog->ingame.translation.y = bunny_clamp(prog->ingame.translation.y + 1.0 * bunny_get_delay(), -2, +2);
    }
  if (bunny_get_keyboard()[BKS_NUMPAD5])
    prog->ingame.translation.x = prog->ingame.translation.y = 0;
  return (GO_ON);
}
