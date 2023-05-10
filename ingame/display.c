// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2024
// Hanged Bunny Studio 2014-2022
// EFRITS SAS 2022-2024
//
// Pylos

#include		"program.h"

static void		tekpixel(t_bunny_pixelarray	*pix,
				 t_bunny_position	pos,
				 unsigned int		color)
{
  t_color		res;
  t_color		ori;
  t_color		lay;
  double		under_ratio;
  double		upper_ratio;
  int			i;

  if (pos.x >= pix->clipable.buffer.width ||
      pos.y >= pix->clipable.buffer.height ||
      pos.x < 0 || pos.y < 0)
    return ;
  lay.full = color;
  if (lay.argb[ALPHA_CMP] == 255)
    ((unsigned int*)pix->pixels)[pos.x + pos.y * pix->clipable.buffer.width] |= color;
  else
    {
      res.full = 0;
      ori.full = ((unsigned int*)pix->pixels)[pos.x + pos.y * pix->clipable.buffer.width];

      upper_ratio = (double)lay.argb[ALPHA_CMP] / 255.0;
      under_ratio = (double)(255 - lay.argb[ALPHA_CMP]) / 255.0;

      res.argb[ALPHA_CMP] = 255;
      for (i = RED_CMP; i < ALPHA_CMP; ++i)
	res.argb[i] = ori.argb[i] * under_ratio + lay.argb[i] * upper_ratio;

      ((unsigned int*)pix->pixels)[pos.x + pos.y * pix->clipable.buffer.width] |= res.full;
    }
}

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
  return (siz + siz > 0 ? size_of_map(siz - 1) : 0);
}

static t_bunny_position	isoproject(const t_zposition		*a,
				   t_program			*prog)
{
  t_bunny_position	pos;

  (void)prog;
  pos.x = (a->x - a->y);
  pos.y = a->x + a->y - a->z;
  pos.x *= prog->ingame.ball->buffer.width;
  pos.y *= prog->ingame.ball->buffer.height;
  return (pos);
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
  t_slot		*slot;
  size_t		len = size_of_map(prog->ingame.size);
  t_zposition		pos[len];
  t_zposition		rot;
  int			x, y, z, i;

  // Rotation en 3D
  rot.x = prog->rotation.x;
  rot.y = prog->rotation.y;
  rot.z = 0;

  bunny_clear(&prog->screen->buffer, WHITE);
  for (i = z = 0; z < prog->ingame.size; ++z)
    for (y = 0; y < prog->ingame.size - z; ++y)
      for (x = 0; x < prog->ingame.size - z; ++x)
	{
	  slot = get_slot(prog->ingame.slots, prog->ingame.size, x, y, z);
	  if (*slot <= EMPTY)
	    continue ;
	  if (*slot == BLACK)
	    prog->ingame.ball.color_mask.full = BLACK;
	  else if (*slot == WHITE)
	    prog->ingame.ball.color_mask.full = PINK2;
	  else
	    continue ;

	  // Position en 3D
	  pos[i].x = x - prog->ingame.size / 2.0;
	  pos[i).y = y - prog->ingame.size / 2.0;
	  pos[i].z = z;

	  // On calcule
	  rotate(&pos[i], &rot);
	  i += 1;
	}
  qsort_r(&pos[0], sizeof(pos[0]), len, compare_ball, prog);
  for (x = 0; x < i; ++x)
    {
      t_bunny_position p = isoproject(pos[i], prog);

      bunny_blit(&prog->screen, prog->ingame.ball, &p);
    }

  bunny_blit(&prog->win->buffer, prog->screen, NULL);
  bunny_display(prog->win);
  return (GO_ON);
}
