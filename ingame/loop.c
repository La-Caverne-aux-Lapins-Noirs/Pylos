// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2024
// Hanged Bunny Studio 2014-2022
// EFRITS SAS 2022-2024
//
// Pylos

#include		"program.h"

t_bunny_response	ingame_loop(t_program		*prog)
{
  double		omega = 90 / 180.0;

  if (bunny_get_keyboard()[BKS_LSHIFT] || bunny_get_keyboard()[BKS_RSHIFT])
    omega *= 2;

  prog->ingame.cursor.x = bunny_clamp(prog->ingame.cursor.x, 0, prog->ingame.size - prog->ingame.cursor.z - 1);
  prog->ingame.cursor.y = bunny_clamp(prog->ingame.cursor.y, 0, prog->ingame.size - prog->ingame.cursor.z - 1);

  if (bunny_get_keyboard()[BKS_Z] || bunny_get_keyboard()[BKS_W])
    prog->ingame.rotation.x -= omega * M_PI * bunny_get_delay();
  if (bunny_get_keyboard()[BKS_S])
    prog->ingame.rotation.x += omega * M_PI * bunny_get_delay();
  if (prog->ingame.rotation.x < M_PI / 2)
    prog->ingame.rotation.x = M_PI / 2;
  if (prog->ingame.rotation.x > M_PI)
    prog->ingame.rotation.x = M_PI;

  if (bunny_get_keyboard()[BKS_Q] || bunny_get_keyboard()[BKS_A])
    prog->ingame.rotation.y -= omega * M_PI * bunny_get_delay();
  if (bunny_get_keyboard()[BKS_D])
    prog->ingame.rotation.y += omega * M_PI * bunny_get_delay();
  if (prog->ingame.rotation.y < -M_PI / 4)
    prog->ingame.rotation.y = -M_PI / 4;
  if (prog->ingame.rotation.y > +M_PI / 4)
    prog->ingame.rotation.y = +M_PI / 4;

  bool			dir[4];

  dir[0] = bunny_get_keyboard()[BKS_NUMPAD4] || bunny_get_keyboard()[BKS_NUMPAD7] || bunny_get_keyboard()[BKS_NUMPAD1];
  dir[1] = bunny_get_keyboard()[BKS_NUMPAD6] || bunny_get_keyboard()[BKS_NUMPAD3] || bunny_get_keyboard()[BKS_NUMPAD9];
  dir[2] = bunny_get_keyboard()[BKS_NUMPAD7] || bunny_get_keyboard()[BKS_NUMPAD8] || bunny_get_keyboard()[BKS_NUMPAD9];
  dir[3] = bunny_get_keyboard()[BKS_NUMPAD1] || bunny_get_keyboard()[BKS_NUMPAD2] || bunny_get_keyboard()[BKS_NUMPAD3];

  if (dir[0])
    {
      prog->ingame.translation.x = bunny_clamp(prog->ingame.translation.x - 1.0 * bunny_get_delay(), -2, +2);
      prog->ingame.translation.y = bunny_clamp(prog->ingame.translation.y + 1.0 * bunny_get_delay(), -2, +2);
    }
  if (dir[1])
    {
      prog->ingame.translation.x = bunny_clamp(prog->ingame.translation.x + 1.0 * bunny_get_delay(), -2, +2);
      prog->ingame.translation.y = bunny_clamp(prog->ingame.translation.y - 1.0 * bunny_get_delay(), -2, +2);
    }
  if (dir[2])
    {
      prog->ingame.translation.x = bunny_clamp(prog->ingame.translation.x - 1.0 * bunny_get_delay(), -2, +2);
      prog->ingame.translation.y = bunny_clamp(prog->ingame.translation.y - 1.0 * bunny_get_delay(), -2, +2);
    }
  if (dir[3])
    {
      prog->ingame.translation.x = bunny_clamp(prog->ingame.translation.x + 1.0 * bunny_get_delay(), -2, +2);
      prog->ingame.translation.y = bunny_clamp(prog->ingame.translation.y + 1.0 * bunny_get_delay(), -2, +2);
    }
  if (bunny_get_keyboard()[BKS_NUMPAD5])
    prog->ingame.translation.x = prog->ingame.translation.y = 0;

  return (GO_ON);
}
