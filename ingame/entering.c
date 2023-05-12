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

  for (int z = 0; z < prog->ingame.size; ++z)
    for (int i = 0; i < prog->ingame.size - z; ++i)
      for (int j = 0; j < prog->ingame.size - z; ++j)
	*get_slotp(prog, i, j, z) = rand() % 2 ? BLACKBALLS : WHITEBALLS;

  if (!prog->ingame.last_game)
    prog->ingame.turn = rand() % 2;
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
		  siz.x -= 2 * i;
		  siz.y -= 2 * i;
		}
	      else
		{
		  siz.x = 1;
		  siz.y = 1;
		}
	      col = 127 + i * 32;
	      printf("%d %d\n", col, siz.x);
	      bunny_set_disk(&prog->ingame.ball->buffer, pos, siz, GRAY(col), BLACK, 0);
	    }
	}
      prog->ingame.ball->origin.x = prog->ingame.ball->buffer.width / 2;
      prog->ingame.ball->origin.y = prog->ingame.ball->buffer.height / 2;
    }

  return (GO_ON);
}
