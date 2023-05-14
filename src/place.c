// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2024
// Hanged Bunny Studio 2014-2022
// EFRITS SAS 2022-2024
//
// Pylos

#include		"program.h"

int			place(t_program		*program,
			      int		x,
			      int		y,
			      int		z,
			      t_slot		sl)
{
  t_slot		*slot = can_place(program, x, y, z);
  int			ret;

  if (!slot)
    {
      if (program->ingame.turn == BLACKBALLS)
	program->blacktext->string = "Impossible de placer la bille ici!";
      if (program->ingame.turn == WHITEBALLS)
	program->whitetext->string = "Impossible de placer la bille ici!";
      return (0);
    }
  if (program->ingame.turn == BLACKBALLS)
    program->ingame.balls1 -= 1;
  if (program->ingame.turn == WHITEBALLS)
    program->ingame.balls2 -= 1;
  *slot = sl;
  ret = detect_bonus(program, x, y, z) ? 2 : 1;
  if (ret == 2)
    {
      program->blacktext->string = "";
      program->whitetext->string = "";
      if (program->ingame.turn == BLACKBALLS)
	program->blacktext->string =
	  "Retire une a deux billes.\nUtilise controle pour choisir puis confirme avec espace.";
      if (program->ingame.turn == WHITEBALLS)
	program->whitetext->string =
	  "Retire une a deux billes.\nUtilise controle pour choisir puis confirme avec espace.";
    }
  return (ret);
}

