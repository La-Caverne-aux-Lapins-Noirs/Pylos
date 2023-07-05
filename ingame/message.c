// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2024
// Hanged Bunny Studio 2014-2022
// EFRITS SAS 2022-2024
//
// Pylos

#include		<string.h>
#include		"program.h"

t_bunny_response	ingame_message(int		fd,
				       const void	*_buffer,
				       size_t		size,
				       t_program	*prog)
{
  char			buffer[size];
  bool			res;

  // C'est une connexion surnuméraire bannie par le connecteur
  if (prog->ingame.clients[0] != fd && prog->ingame.clients[1] != fd)
    return (GO_ON);

  if ((prog->ingame.turn == WHITEBALLS && prog->ingame.clients[0] != fd) ||
      (prog->ingame.turn == BLACKBALLS && prog->ingame.clients[1] != fd))
    {
      bunny_server_write(prog->server, "not ur turn, dumbass\n", 21, fd);
      return (GO_ON);
    }
  
  (void)fd;
  memcpy(buffer, _buffer, size);
  if (size > 1)
    buffer[size - 1] = '\0';
  else
    buffer[size] = '\0';
  if (strncmp(buffer, "levelup", size) == 0)
    res = movement(prog, PYLOS_LEVEL_UP);
  else if (strncmp(buffer, "leveldown", size) == 0)
    res = movement(prog, PYLOS_LEVEL_DOWN);
  else if (strncmp(buffer, "left", size) == 0)
    res = movement(prog, PYLOS_GO_LEFT);
  else if (strncmp(buffer, "right", size) == 0)
    res = movement(prog, PYLOS_GO_RIGHT);
  else if (strncmp(buffer, "up", size) == 0)
    res = movement(prog, PYLOS_GO_UP);
  else if (strncmp(buffer, "down", size) == 0)
    res = movement(prog, PYLOS_GO_DOWN);
  else if (strncmp(buffer, "take", size) == 0)
    res = movement(prog, PYLOS_TAKE);
  else if (strncmp(buffer, "put", size) == 0)
    res = movement(prog, PYLOS_PUT);
  else if (strncmp(buffer, "map", size) == 0)
    {
      size_t		max = (int)powf(prog->ingame.size, 3);
      char		map[max + 1];
      size_t		i;

      for (i = 0; i < max; ++i)
	map[i] = prog->ingame.slots[i] + '0';
      map[max] = '\n';
      bunny_server_write(prog->server, map, max, fd);
    }
  if (strncmp(buffer, "pos", size) == 0)
    {
      char		coords[256];
      int		len;
      
      len = snprintf(coords, sizeof(coords), "%d %d %d\n", (int)prog->ingame.cursor.x, (int)prog->ingame.cursor.y, (int)prog->ingame.cursor.z);
      bunny_server_write(prog->server, coords, len, fd);
    }
  if (strncmp(buffer, "go ", 3) == 0)
    {
      int		a, b, c;

      if (sscanf(buffer, "go %d %d %d", &a, &b, &c) == 3)
	{
	  prog->ingame.cursor.x = a;
	  prog->ingame.cursor.y = b;
	  prog->ingame.cursor.z = c;
	  res = true;
	}
    }
  bunny_server_write(prog->server, res ? "ok\n" : "ko\n", 3, fd);
  return (GO_ON);
}

