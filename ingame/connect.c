// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2024
// Hanged Bunny Studio 2014-2022
// EFRITS SAS 2022-2024
//
// Pylos

#include		"program.h"

t_bunny_response	ingame_joy_connect(t_bunny_event_state	state,
					   int			joyid,
					   const t_bunny_joystick *j,
					   t_program		*prog)
{
  (void)joyid;
  (void)prog;
  if (state == CONNECTED)
    printf("Nouvelle manette (%d) détectée: %s.\n", joyid, j->name);
  else
    printf("Manette perdue (%d): %s.\n", joyid, j->name);
  return (GO_ON);
} 

t_bunny_response	ingame_connect(int			fd,
				       t_bunny_event_state	state,
				       t_program		*prog)
{
  (void)prog;
  if (state == CONNECTED)
    {
      printf("Nouvelle connexion, numéroté %d.\n", fd);
      if (prog->ingame.clients[0] == -1)
	{
	  prog->ingame.clients[0] = fd;
	  prog->ingame.nbr_clients += 1;
	}
      else if (prog->ingame.clients[1] == -1)
	{
	  prog->ingame.clients[1] = fd;
	  prog->ingame.nbr_clients += 1;
	}
      else
	{
	  printf("Connexion rejetée: serveur plein.\n");
	  bunny_server_doom_client(prog->server, fd);
	}
    }
  else
    {
      printf("Déconnexion du numéro %d.\n", fd);
      if (prog ->ingame.clients[0] == fd)
	{
	  prog->ingame.clients[0] = -1;
	  prog->ingame.nbr_clients -= 1;
	}
      else if (prog ->ingame.clients[1] == fd)
	{
	  prog->ingame.clients[1] = -1;
	  prog->ingame.nbr_clients -= 1;
	}
    }
  return (GO_ON);
}
