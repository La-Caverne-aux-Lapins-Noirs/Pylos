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
    .display = ingame_display,
    .move = ingame_move,
    .connect = ingame_joy_connect,
    .button = ingame_joy_button,
    .axis = ingame_joy_axis
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
  if (argc == 2)
    {
      if (strcmp(argv[1], "host") == 0)
	{
	  if ((prog.server = bunny_new_server(20601)) == NULL) // "Py" in big endian
	    fprintf(stderr, "%s: Cannot open server socket.\n", argv[0]);
	  else
	    {
	      gl_context[INGAME].netcom = prog.server;
	      gl_context[INGAME].netconnect = ingame_connect;
	      gl_context[INGAME].netmessage = ingame_message;
	      puts("Serveur ouvert.");
	    }
	}
      else if ((prog.client = bunny_new_client(argv[1], 20601)) == NULL)
	fprintf(stderr, "%s: Cannot open client socket.\n", argv[0]);
      else
	{
	  gl_context[INGAME].netcom = prog.client;
	  gl_context[INGAME].netmessage = ingame_message;
	  puts("Connexion établie.");
	}
    }
  if (!bunny_join_binary_directory(argv[0]))
    return (EXIT_FAILURE);
  prog.cnf = bunny_open_configuration("configuration.dab", NULL);

  siz.x = 800;
  siz.y = 600;
  tmp = false;

  prog.ingame.clients[0] = -1;
  prog.ingame.clients[1] = -1;
  prog.ingame.nbr_clients = 0;
  
  prog.cnf && bunny_configuration_getf(prog.cnf, &siz.x, "Window.Size[0]");
  prog.cnf && bunny_configuration_getf(prog.cnf, &siz.y, "Window.Size[1]");
  prog.cnf && bunny_configuration_getf(prog.cnf, &tmp, "Window.Fullscreen");
  if (!(prog.win = bunny_start(siz.x, siz.y, tmp, "Solyp")))
    {
      fprintf(stderr, "%s: Cannot open window (%d, %d, %s).\n",
	      argv[0], siz.x, siz.y, tmp ? "fullscreen" : "windowed"
	      );
      goto DeleteConf;
    }

  siz.x = 400;
  siz.y = 300;
  prog.cnf && bunny_configuration_getf(prog.cnf, &siz.x, "Screen.Size[0]");
  prog.cnf && bunny_configuration_getf(prog.cnf, &siz.y, "Screen.Size[1]");
  if (!(prog.screen = bunny_new_picture(siz.x, siz.y)))
    {
      fprintf(stderr, "%s: Cannot reserve screen picture (%d, %d).\n", argv[0], siz.x, siz.y);
      goto DeleteWindow;
    }

  prog.screen->scale.x = (double)prog.win->buffer.width / prog.screen->buffer.width;
  prog.screen->scale.y = (double)prog.win->buffer.height / prog.screen->buffer.height;

  fps = 50;
  prog.cnf && bunny_configuration_getf(prog.cnf, &fps, "FramePerSecond");

  if (!(prog.normal_screen = bunny_new_picture(prog.screen->buffer.width, prog.screen->buffer.height)))
    {
      fprintf(stderr, "%s: Cannot create normal screen (%zu, %zu).\n", argv[0], prog.screen->buffer.width, prog.screen->buffer.height);
      goto DeleteScreen;
    }

  prog.normal_screen->scale.x = (double)prog.win->buffer.width / prog.normal_screen->buffer.width;
  prog.normal_screen->scale.y = (double)prog.win->buffer.height / prog.normal_screen->buffer.height;
  if (prog.normal_screen->scale.x < prog.normal_screen->scale.y)
    prog.normal_screen->scale.y = prog.normal_screen->scale.x;
  else
    prog.normal_screen->scale.x = prog.normal_screen->scale.y;
  prog.normal_screen->origin.x = prog.normal_screen->buffer.width / 2.0;
  prog.normal_screen->origin.y = prog.normal_screen->buffer.height / 2.0;
  prog.normal_screen->position.x = prog.win->buffer.width / 2.0;
  prog.normal_screen->position.y = prog.win->buffer.height / 2.0;

  if (!(prog.specular_screen = bunny_new_picture(prog.screen->buffer.width, prog.screen->buffer.height)))
    {
      fprintf(stderr, "%s: Cannot create specular screen (%zu, %zu).\n", argv[0], prog.screen->buffer.width, prog.screen->buffer.height);
      goto DeleteNormalScreen;
    }
  bunny_clear(&prog.specular_screen->buffer, WHITE);
  prog.normal_configuration.window_size.x = prog.screen->buffer.width;
  prog.normal_configuration.window_size.y = prog.screen->buffer.height;
  prog.normal_configuration.normal_map = prog.normal_screen;
  prog.normal_configuration.specular_map = prog.specular_screen;

  for (size_t i = 0; i < sizeof(prog.normal_configuration.lights) / sizeof(prog.normal_configuration.lights[0]); ++i)
    {
      prog.normal_configuration.lights[i].x = 0;
      prog.normal_configuration.lights[i].y = 0;
      prog.normal_configuration.lights[i].z = 0.2;
      prog.normal_configuration.lights[i].ambient_color.full = WHITE;
      prog.normal_configuration.lights[i].specular_color.full = WHITE;
      prog.normal_configuration.lights[i].light_color.full = WHITE;

      prog.normal_configuration.lights[i].light_attenuation = 1;
      prog.normal_configuration.lights[i].ambient_depth = 0.1;
      prog.normal_configuration.lights[i].ambient_attenuation = 24;
      prog.normal_configuration.lights[i].specular_depth = 0.01;
      prog.normal_configuration.lights[i].specular_attenuation = 4.0;
    }
  prog.normal_configuration.lights[0].active = true;
  prog.normal_configuration.lights[1].active = true;
  prog.normal_configuration.lights[2].active = true;

  if (!(prog.normal_shader = bunny_normal_map_shader(&prog.normal_configuration)))
    {
      fprintf(stderr, "%s: Cannot initialize shader.\n", argv[0]);
      goto DeleteSpecularScreen;
    }

  bunny_default_screen_tweak(&prog.screen_tweak_configuration);
  prog.screen_tweak_configuration.blur_level = 3.0;
  prog.screen_tweak_shader = bunny_screen_tweak_shader(&prog.screen_tweak_configuration);

  if (!(prog.blacktext = bunny_load_text("./res/blackballs.dab")))
    {
      fprintf(stderr, "%s: Cannot load fonts.\n", argv[0]);
      goto DeleteSpecularScreen;
    }
  if (!(prog.whitetext = bunny_load_text("./res/whiteballs.dab")))
    {
      fprintf(stderr, "%s: Cannot load fonts.\n", argv[0]);
      goto DeleteBlackText;
    }

  puts(
       "Bienvenue dans Pylos.\n"
       "Utilisez espace pour placer une bille.\n"
       "Utilisez controle pour prendre une bille.\n"
       "\n"
       "Capacité réseau possible sur port 20601.\n"
       "Précisez 'host' pour établir un serveur, une IP pour un client."
       );
  
  prog.context = 0;
  bunny_set_joystick_threshold(prog.win, 70);
  do
    {
      bunny_set_context(&gl_context[prog.context]);
      res = bunny_loop(prog.win, fps, &prog);
    }
  while (res == SWITCH_CONTEXT && prog.context < LAST_CONTEXT);
  if (res == EXIT_ON_SUCCESS)
    ret = EXIT_SUCCESS;

 DeleteBlackText:
  bunny_delete_clipable(&prog.blacktext->clipable);
 DeleteSpecularScreen:
  bunny_delete_clipable(prog.specular_screen);
 DeleteNormalScreen:
  bunny_delete_clipable(prog.normal_screen);
 DeleteScreen:
  bunny_delete_clipable(prog.screen);
 DeleteWindow:
  bunny_stop(prog.win);
 DeleteConf:
  if (prog.cnf)
    bunny_delete_configuration(prog.cnf);
  if (prog.server)
    bunny_delete_server(prog.server);
  if (prog.client)
    bunny_delete_client(prog.client);
  return (ret);
}
