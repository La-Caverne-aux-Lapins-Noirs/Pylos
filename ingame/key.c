// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2024
// Hanged Bunny Studio 2014-2022
// EFRITS SAS 2022-2024
//
// Pylos

#include		"program.h"

t_bunny_response	ingame_key(t_bunny_event_state	state,
				   t_bunny_keysym	sym,
				   t_program		*prog)
{
  if (state == GO_DOWN)
    {
      if (sym == BKS_ESCAPE)
	{
	  if ((int)(prog->context -= 1) < 0)
	    return (EXIT_ON_SUCCESS);
	  return (SWITCH_CONTEXT);
	}

      if ((prog->ingame.turn == BLACKBALLS && prog->ingame.play1 == NULL)
	  ||
	  (prog->ingame.turn == WHITEBALLS && prog->ingame.play2 == NULL)
	  )
	{
	  if (sym == BKS_PAGEUP)
	    prog->ingame.cursor.z = bunny_clamp(prog->ingame.cursor.z + 1, 0, prog->ingame.size - 1);
	  if (sym == BKS_PAGEDOWN)
	    prog->ingame.cursor.z = bunny_clamp(prog->ingame.cursor.z - 1, 0, prog->ingame.size - 1);

	  if (sym == BKS_LEFT)
	    prog->ingame.cursor.x = bunny_clamp(prog->ingame.cursor.x - 1, 0, prog->ingame.size - 1);
	  if (sym == BKS_RIGHT)
	    prog->ingame.cursor.x = bunny_clamp(prog->ingame.cursor.x + 1, 0, prog->ingame.size - 1);

	  if (sym == BKS_UP)
	    prog->ingame.cursor.y = bunny_clamp(prog->ingame.cursor.y - 1, 0, prog->ingame.size - 1);
	  if (sym == BKS_DOWN)
	    prog->ingame.cursor.y = bunny_clamp(prog->ingame.cursor.y + 1, 0, prog->ingame.size - 1);

	  if ((sym == BKS_LCONTROL || sym == BKS_RCONTROL))
	    {
	      t_slot	*tmp = get_slotp(prog, prog->ingame.cursor.x, prog->ingame.cursor.y, prog->ingame.cursor.z);

	      if (can_removes(prog, prog->ingame.cursor.x, prog->ingame.cursor.y, prog->ingame.cursor.z, prog->ingame.turn))
		{
		  if (tmp != NULL && tmp != prog->ingame.picked_up[0] && tmp != prog->ingame.picked_up[1])
		    {
		      if (*tmp == prog->ingame.turn)
			{
			  if (!prog->ingame.picked_up[0])
			    {
			      prog->ingame.picked_up[0] = tmp;
			      prog->ingame.picked_up_pos[0] = prog->ingame.cursor;
			    }
			  else
			    {
			      prog->ingame.picked_up[1] = tmp;
			      prog->ingame.picked_up_pos[1] = prog->ingame.cursor;
			    }
			}
		    }
		  else
		    {
		      if (prog->ingame.picked_up[0] == tmp)
			prog->ingame.picked_up[0] = NULL;
		      if (prog->ingame.picked_up[1] == tmp)
			prog->ingame.picked_up[1] = NULL;
		    }
		}
	      else
		{
		  if (tmp == NULL || *tmp <= EMPTY)
		    {
		      if (prog->ingame.turn == BLACKBALLS)
			prog->blacktext->string = "Aucune bille a retirer.";
		      else
			prog->whitetext->string = "Aucune bille a retirer.";
		    }
		  else
		    {
		      if (prog->ingame.turn == BLACKBALLS)
			prog->blacktext->string = "Impossible de retirer cette bille!";
		      else
			prog->whitetext->string = "Impossible de retirer cette bille!";
		    }
		}
	    }
	  if (sym == BKS_SPACE)
	    {
	      // Retrait de deux billes suites à un bonus ligne/carré
	      //
	      //
	      //

	      // Est ce que le montage d'une bille d'un étage est possible?
	      if (prog->ingame.picked_up[0] && prog->ingame.picked_up_pos[0].z >= prog->ingame.cursor.z - 0.9)
		{
		  if (prog->ingame.turn == BLACKBALLS)
		    prog->blacktext->string = "Le deplacement ne peut s'effectuer qu'en hauteur!";
		  else
		    prog->whitetext->string = "Le deplacement ne peut s'effectuer qu'en hauteur!";
		  return (GO_ON);
		}

	      if (place(prog, prog->ingame.cursor.x, prog->ingame.cursor.y, prog->ingame.cursor.z, prog->ingame.turn))
		{
		  if (prog->ingame.picked_up[0])
		    {
		      // Retrait de la bille montée
		      if (removes(prog, prog->ingame.picked_up_pos[0].x, prog->ingame.picked_up_pos[0].y,
				  prog->ingame.picked_up_pos[0].z, prog->ingame.turn) == false)
			{
			  removes(prog, prog->ingame.cursor.x, prog->ingame.cursor.y, prog->ingame.cursor.z, prog->ingame.turn);
			  if (prog->ingame.turn == BLACKBALLS)
			    prog->blacktext->string = "Impossible de deplacer la bille ici!";
			  else
			    prog->whitetext->string = "Impossible de deplacer la bille ici!";
			  return (GO_ON);
			}
		      else
			prog->ingame.picked_up[0] = NULL;
		    }

		  if (prog->ingame.turn == BLACKBALLS)
		    prog->ingame.turn = WHITEBALLS;
		  else
		    prog->ingame.turn = BLACKBALLS;

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
		}
	    }
	}
    }
  return (GO_ON);
}
