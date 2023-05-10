// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2024
// Hanged Bunny Studio 2014-2022
// EFRITS SAS 2022-2024
//
// Pylos

#include		"program.h"

void			qsort_r(void		*base,
				size_t		nmemb,
				size_t		size,
				int		(*compar)
				(const void	*a,
				 const void	*b,
				 void		*arg
				 ),
				void		*arg);

static void		rotate(t_zposition			*pos,
			       const t_zposition		*rot)
{
  double		x, y, z;
  double		xx, yy, zz;

  x = pos->x;
  y = pos->y;
  z = pos->z;

  xx = x * 1 + y * 0 + z * 0;
  yy = x * 0 + y * cos(rot->x) - z * sin(rot->x);
  zz = x * 0 + y * sin(rot->x) + z * cos(rot->x);

  x = xx * cos(rot->y) + yy * 0 + zz * sin(rot->y);
  y = xx * 0 + yy * 1 - zz * 0;
  z = -xx * sin(rot->y) + yy * 0 + zz * cos(rot->y);

  xx = x * cos(rot->z) - y * sin(rot->z) + z * 0;
  yy = x * sin(rot->z) + y * cos(rot->z) - z * 0;
  zz = x * 0 + y * 0 + z * 1;

  pos->x = xx;
  pos->y = yy;
  pos->z = zz;
}

static size_t		size_of_map(size_t			siz)
{
  return (siz * siz + (siz > 0 ? size_of_map(siz - 1) : 0));
}

static t_bunny_position	isoproject(const t_zposition		*a,
				   t_program			*prog)
{
  t_bunny_accurate_position	pos;

  (void)prog;
  pos.x = (a->x - a->y);
  pos.y = (a->x + a->y - a->z) / 2.0;
  pos.x *= prog->ingame.ball->buffer.width;
  pos.y *= prog->ingame.ball->buffer.height;
  t_bunny_position ppos = {round(pos.x), round(pos.y)};
  return (ppos);
}

static int		compare_ball(const void			*_a,
				     const void			*_b,
				     void			*prog)
{
  const t_zposition	*a = (const t_zposition*)_a;
  const t_zposition	*b = (const t_zposition*)_b;
  t_bunny_position	posa;
  t_bunny_position	posb;

  if (a->z > b->z)
    return (-1);
  if (a->z < b->z)
    return (+1);
  posa = isoproject(a, prog);
  posb = isoproject(a, prog);
  if (posa.y > posb.y)
    return (-1);
  if (posa.y < posb.y)
    return (+1);
  return (0);
}

t_bunny_response	ingame_display(t_program		*prog)
{
  unsigned int		coline[2] = {BLACK, BLACK};
  t_slot		*slot;
  t_bunny_position	p[2];
  size_t		len = size_of_map(prog->ingame.size);
  t_zposition		pos[len];
  t_zposition		rot;
  int			x, y, z, i;

  // Rotation en 3D
  rot.x = prog->ingame.rotation.x;
  rot.y = prog->ingame.rotation.y;
  rot.z = 0;

  bunny_clear(&prog->screen->buffer, WHITE);

  for (y = 0; y <= prog->ingame.size; ++y)
    {
      pos[0].x = -prog->ingame.size / 2.0;
      pos[0].y = y - prog->ingame.size / 2.0;
      pos[0].z = 0;
      p[0] = isoproject(&pos[0], prog);
      pos[0].x = +prog->ingame.size / 2.0;
      pos[0].y = y - prog->ingame.size / 2.0;
      pos[0].z = 0;
      p[1] = isoproject(&pos[0], prog);

      p[0].x += prog->screen->buffer.width / 2;
      p[0].y += prog->screen->buffer.height / 2;
      p[1].x += prog->screen->buffer.width / 2;
      p[1].y += prog->screen->buffer.height / 2;
      bunny_set_line(&prog->screen->buffer, &p[0], &coline[0]);
    }
  for (x = 0; x <= prog->ingame.size; ++x)
    {
      pos[0].x = x - prog->ingame.size / 2.0;
      pos[0].y = -prog->ingame.size / 2.0;
      pos[0].z = 0;
      p[0] = isoproject(&pos[0], prog);
      pos[0].x = x - prog->ingame.size / 2.0;
      pos[0].y = +prog->ingame.size / 2.0;
      pos[0].z = 0;
      p[1] = isoproject(&pos[0], prog);

      p[0].x += prog->screen->buffer.width / 2;
      p[0].y += prog->screen->buffer.height / 2;
      p[1].x += prog->screen->buffer.width / 2;
      p[1].y += prog->screen->buffer.height / 2;
      bunny_set_line(&prog->screen->buffer, &p[0], &coline[0]);
    }

  for (i = z = 0; z < prog->ingame.size; ++z)
    for (y = 0; y < prog->ingame.size - z; ++y)
      for (x = 0; x < prog->ingame.size - z; ++x)
	{
	  slot = get_slot(prog->ingame.slots, prog->ingame.size, x, y, z);
	  if (*slot <= EMPTY)
	    continue ;
	  if (*slot >= LAST_SLOT)
	    continue ;

	  if (*slot == BLACKBALLS)
	    prog->ingame.ball->color_mask.full = BLACK;
	  else if (*slot == WHITEBALLS)
	    prog->ingame.ball->color_mask.full = PINK2;

	  // Position en 3D
	  pos[i].x = x - prog->ingame.size / 2.0;
	  pos[i].y = y - prog->ingame.size / 2.0;
	  pos[i].z = z;

	  // On calcule
	  rotate(&pos[i], &rot);
	  i += 1;
	}
  qsort_r(&pos[0], sizeof(pos[0]), len, compare_ball, prog);
  for (x = 0; x < i; ++x)
    {
      p[0] = isoproject(&pos[x], prog);
      p[0].x += prog->screen->buffer.width / 2;
      p[0].y += prog->screen->buffer.height / 2;
      bunny_blit(&prog->screen->buffer, prog->ingame.ball, &p[0]);
    }

  bunny_blit(&prog->win->buffer, prog->screen, NULL);
  bunny_display(prog->win);
  return (GO_ON);
}
