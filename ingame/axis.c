// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2024
// Hanged Bunny Studio 2014-2022
// EFRITS SAS 2022-2024
//
// Pylos

#include		<math.h>
#include		"program.h"

t_bunny_response	ingame_key(t_bunny_event_state		state,
				   t_bunny_keysym		sym,
				   t_program			*prog);

t_bunny_response	ingame_joy_axis(int			jid,
					t_bunny_axis		axis,
					float			value,
					t_program		*prog)
{
  (void)jid;
  if (axis == 0)
    return (ingame_key(fabs(value) > 50 ? GO_DOWN : GO_UP, value < 0 ? BKS_LEFT : BKS_RIGHT, prog));
  if (axis == 1)
    return (ingame_key(fabs(value) > 50 ? GO_DOWN : GO_UP, value < 0 ? BKS_UP : BKS_DOWN, prog));
  return (GO_ON);
}
