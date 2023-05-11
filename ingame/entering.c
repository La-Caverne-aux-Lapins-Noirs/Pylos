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
	  t_bunny_size	pos = {15, 15};
	  t_bunny_size	siz = {10, 10};

	  if (!(prog->ingame.ball = bunny_new_picture(pos.x * 2, pos.y * 2)))
	    {
	      fprintf(stderr, "Cannot load res/ball.dab.\n");
	      return (EXIT_ON_ERROR);
	    }
	  bunny_set_disk(&prog->ingame.ball->buffer, pos, siz, GRAY(127), BLACK, 2);

	  for (int i = 1; i < 5; ++i)
	    {
	      if (i < 4)
		{
		  pos.x -= 1;
		  pos.y -= 1;
		}
	      siz.x = 10 - 2 * i;
	      siz.y = 10 - 2 * i;
	      bunny_set_disk(&prog->ingame.ball->buffer, pos, siz, GRAY(127 + i * 32), BLACK, 0);
	    }
	}
      prog->ingame.ball->origin.x = prog->ingame.ball->buffer.width / 2;
      prog->ingame.ball->origin.y = prog->ingame.ball->buffer.height / 2;
    }

  return (GO_ON);
}
