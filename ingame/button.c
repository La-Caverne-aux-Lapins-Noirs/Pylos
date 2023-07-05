// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2024
// Hanged Bunny Studio 2014-2022
// EFRITS SAS 2022-2024
//
// Pylos

#include		"program.h"

t_bunny_response	ingame_key(t_bunny_event_state		state,
				   t_bunny_keysym		sym,
				   t_program			*prog);

t_bunny_response	ingame_joy_button(t_bunny_event_state	state,
					  int			jid,
					  int			button,
					  t_program		*prog)
{
  (void)jid;
  if (button == 2 || button == 3)
    return (ingame_key(state, BKS_ESCAPE, prog));
  if (button == 1)
    return (ingame_key(state, BKS_SPACE, prog));

  if (button == 6)
    return (ingame_key(state, BKS_PAGEDOWN, prog));
  if (button == 7)
    return (ingame_key(state, BKS_PAGEUP, prog));
  
  if (button == 5)
    return (ingame_key(state, BKS_LCONTROL, prog));
  return (GO_ON);
}

