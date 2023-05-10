// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2024
// Hanged Bunny Studio 2014-2022
// EFRITS SAS 2022-2024
//
// Pylos

#include		"program.h"

bunny_declare_context(ingame);

t_bunny_context		gl_context[LAST_CONTEXT] =
  {
   [INGAME] =
   {
    .entering_context = ingame_entering,
    .leaving_context = ingame_leaving,
    .key = ingame_key,
    .loop = ingame_loop,
    .display = ingame_display
   }
  };

int			main(int		argc,
			     char		**argv)
{
  static t_program	prog;
  t_bunny_size		siz;
  t_bunny_response	res;
  bool			tmp;
  int			fps;
  int			ret;

  bunny_enable_full_blit(true);
  ret = EXIT_FAILURE;
  if (argc > 2)
    prog.cnf = bunny_open_configuration(argv[1], NULL);
  else
    {
      if (!bunny_join_binary_directory(argv[0]))
	return (EXIT_FAILURE);
      prog.cnf = bunny_open_configuration("default_configuration.dab", NULL);
    }
  if (!prog.cnf)
    {
      fprintf(stderr, "%s: Cannot load configuration.\n", argv[0]);
      return (EXIT_FAILURE);
    }

  siz.x = 800;
  siz.y = 600;
  tmp = false;
  bunny_configuration_getf(prog.cnf, &siz.x, "Window.Size[0]");
  bunny_configuration_getf(prog.cnf, &siz.y, "Window.Size[1]");
  bunny_configuration_getf(prog.cnf, &tmp, "Window.Fullscreen");
  if (!(prog.win = bunny_start(siz.x, siz.y, tmp, "Solyp")))
    {
      fprintf(stderr, "%s: Cannot open window (%d, %d, %s).\n",
	      argv[0], siz.x, siz.y, tmp ? "fullscreen" : "windowed"
	      );
      goto DeleteConf;
    }

  siz.x = 320;
  siz.y = 240;
  bunny_configuration_getf(prog.cnf, &siz.x, "Screen.Size[0]");
  bunny_configuration_getf(prog.cnf, &siz.y, "Screen.Size[1]");
  if (!(prog.screen = bunny_new_picture(siz.x, siz.y)))
    {
      fprintf(stderr, "%s: Cannot reserve screen picture (%d, %d).\n", argv[0], siz.x, siz.y);
      goto DeleteWindow;
    }

  prog.screen->scale.x = (double)prog.win->buffer.width / prog.screen->buffer.width;
  prog.screen->scale.y = (double)prog.win->buffer.height / prog.screen->buffer.height;
  if (prog.screen->scale.x < prog.screen->scale.y)
    prog.screen->scale.y = prog.screen->scale.x;
  else
    prog.screen->scale.x = prog.screen->scale.y;
  prog.screen->origin.x = prog.screen->buffer.width / 2.0;
  prog.screen->origin.y = prog.screen->buffer.height / 2.0;
  prog.screen->position.x = prog.win->buffer.width / 2.0;
  prog.screen->position.y = prog.win->buffer.height / 2.0;

  fps = 50;
  bunny_configuration_getf(prog.cnf, &fps, "FramePerSecond");

  prog.context = 0;
  do
    {
      bunny_set_context(&gl_context[prog.context]);
      res = bunny_loop(prog.win, fps, &prog);
    }
  while (res == SWITCH_CONTEXT);
  if (res == EXIT_ON_SUCCESS)
    ret = EXIT_SUCCESS;

  // DeleteScreen:
  bunny_delete_clipable(prog.screen);
 DeleteWindow:
  bunny_stop(prog.win);
 DeleteConf:
  bunny_delete_configuration(prog.cnf);
  return (ret);
}

