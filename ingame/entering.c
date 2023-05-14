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
  prog->ingame.balls1 = ceil(size_of_map(prog->ingame.size) / 2);
  prog->ingame.balls2 = ceil(size_of_map(prog->ingame.size) / 2);

  prog->cnf && bunny_configuration_getf(prog->cnf, &prog->ingame.size, "Game.Size");
  if (!(prog->ingame.slots = bunny_calloc(powf(prog->ingame.size, 3), sizeof(*prog->ingame.slots))))
    {
      fprintf(stderr, "Cannot allocate arena.\n");
      return (EXIT_ON_ERROR);
    }

  if (!prog->ingame.last_game)
    prog->ingame.turn = rand() % 2 + 1;
  else
    prog->ingame.turn = prog->ingame.last_game;

  if (!prog->ingame.ball)
    {
      if (!(prog->ingame.ball = bunny_load_picture("res/ball.png")))
	{
	  t_bunny_size	siz = {15, 15};
	  t_bunny_size	pos = {(siz.x * 2 + 4) / 2, (siz.y * 2 + 4) / 2};
	  int		col;

	  if (!(prog->ingame.ball = bunny_new_picture(siz.x * 2 + 4, siz.y * 2 + 4)))
	    {
	      fprintf(stderr, "Cannot load res/ball.png.\n");
	      return (EXIT_ON_ERROR);
	    }
	  bunny_clear(&prog->ingame.ball->buffer, 0);
	  bunny_set_disk(&prog->ingame.ball->buffer, pos, siz, GRAY(127), GRAY(127), 2);

	  for (int i = 1; i < 5 && 0; ++i)
	    {
	      if (i < 4)
		{
		  pos.x -= 1;
		  pos.y -= 1;
		  siz.x -= 2 * i;
		  siz.y -= 2 * i;
		}
	      else
		{
		  siz.x = 1;
		  siz.y = 1;
		}
	      col = 127 + i * 32;
	      bunny_set_disk(&prog->ingame.ball->buffer, pos, siz, GRAY(col), GRAY(col), 2);
	    }
	}
      prog->ingame.ball->origin.x = prog->ingame.ball->buffer.width / 2;
      prog->ingame.ball->origin.y = prog->ingame.ball->buffer.height / 2;
    }

  if (!prog->ingame.normal_ball)
    {
      if (!(prog->ingame.normal_ball = bunny_load_picture("res/normal_ball.png")))
	{
	  if (!(prog->ingame.normal_ball = bunny_new_picture(prog->ingame.ball->buffer.width, prog->ingame.ball->buffer.height)))
	    {
	      fprintf(stderr, "Cannot load res/normal_ball.png.\n");
	      return (EXIT_ON_ERROR);
	    }
	  t_bunny_size	siz = {15, 15};
	  t_bunny_size	pos = {(siz.x * 2 + 4) / 2, (siz.y * 2 + 4) / 2};

	  bunny_clear(&prog->ingame.normal_ball->buffer, 0);
	  bunny_set_disk(&prog->ingame.normal_ball->buffer, pos, siz, GRAY(127), GRAY(127), 2);
	}

      prog->ingame.normal_ball->origin.x = prog->ingame.normal_ball->buffer.width / 2;
      prog->ingame.normal_ball->origin.y = prog->ingame.normal_ball->buffer.height / 2;
      prog->ingame.normal_ball->scale.x = (double)prog->ingame.ball->buffer.width / prog->ingame.normal_ball->buffer.width;
      prog->ingame.normal_ball->scale.y = (double)prog->ingame.ball->buffer.height / prog->ingame.normal_ball->buffer.height;
    }

  if (prog->ingame.turn == BLACKBALLS)
    {
      prog->blacktext->string = "A toi de jouer!";
      prog->whitetext->string = "";
    }
  else
    {
      prog->blacktext->string = "";
      prog->whitetext->string = "A toi de jouer!";
    }
  return (GO_ON);
}
