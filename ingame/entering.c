// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2024
// Hanged Bunny Studio 2014-2022
// EFRITS SAS 2022-2024
//
// Pylos

#include		"program.h"

t_bunny_response	ingame_entering(t_program		*prog)
{
  prog->ingame.size = 4;
  prog->cnf && bunny_configuration_getf(prog->cnf, &prog->ingame.size, "Game.Size");
  if (!(prog->ingame.slots = bunny_calloc(powf(prog->ingame.size, 3), sizeof(*prog->ingame.slots))))
    {
      fprintf(stderr, "Cannot allocate arena.\n");
      return (EXIT_ON_ERROR);
    }

  *get_slotp(prog, 0, 0, 0) = BLACKBALLS;
  *get_slotp(prog, 1, 0, 0) = WHITEBALLS;

  if (!prog->ingame.last_game)
    prog->ingame.turn = rand() % 2;
  else
    prog->ingame.turn = prog->ingame.last_game;

  if (!prog->ingame.ball)
    {
      if (!(prog->ingame.ball = bunny_load_picture("res/ball.png")))
	{
	  t_bunny_size	siz = {10, 10};

	  if (!(prog->ingame.ball = bunny_new_picture(siz.x * 2, siz.y * 2)))
	    {
	      fprintf(stderr, "Cannot load res/ball.dab.\n");
	      return (EXIT_ON_ERROR);
	    }
	  bunny_set_disk(&prog->ingame.ball->buffer, siz, siz, WHITE, WHITE, 0);
	}
      prog->ingame.ball->origin.x = prog->ingame.ball->buffer.width / 2;
      prog->ingame.ball->origin.y = prog->ingame.ball->buffer.height / 2;
    }

  return (GO_ON);
}
