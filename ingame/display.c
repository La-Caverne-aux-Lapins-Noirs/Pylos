// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2024
// Hanged Bunny Studio 2014-2022
// EFRITS SAS 2022-2024
//
// Pylos

#include		"program.h"

void			bsl(t_bunny_buffer	*buf,
			    t_bunny_position	*pos,
			    unsigned int	*col)
{
  t_bunny_position	p[2] = {
    pos[0], pos[1]
  };

  bunny_set_line(buf, &p[0], col);
  p[0].y += 1;
  p[1].y += 1;
  bunny_set_line(buf, &p[0], col);
  p[0].y += 1;
  p[1].y += 1;
  bunny_set_line(buf, &p[0], col);
  p[0].y += 1;
  p[1].y += 1;
}

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
  pos.y = (a->x + a->y) / 2 * prog->ingame.rotation.x / (M_PI / 2) - a->z / 2;
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

  if (a->z < b->z)
    return (-1);
  if (a->z > b->z)
    return (+1);
  posa = isoproject(a, prog);
  posb = isoproject(b, prog);
  if (posa.y < posb.y)
    return (-1);
  if (posa.y > posb.y)
    return (+1);
  return (0);
}

typedef struct		s_ball
{
  t_zposition		pos;
  t_slot		slot;
}			t_ball;

t_bunny_response	ingame_display(t_program		*prog)
{
  unsigned int		coline[2] = {WHITE, WHITE};
  t_slot		*slot;
  t_bunny_position	p[2];
  size_t		len = size_of_map(prog->ingame.size);
  t_ball       		pos[len];
  t_ball       		lpos;
  t_zposition		rot;
  t_zposition		lig;
  int			x, y, z, i, iter;
  bool			grid;

  // Rotation en 3D
  rot.x = 0;
  rot.y = 0;
  rot.z = prog->ingame.rotation.y;

  bunny_clear(&prog->screen->buffer, WHITE);
  bunny_clear(&prog->normal_screen->buffer, COLOR(255, 128, 128, 255));

  for (i = z = 0; z < prog->ingame.size; ++z)
    for (y = 0; y < prog->ingame.size - z; ++y)
      for (x = 0; x < prog->ingame.size - z; ++x)
	{
	  slot = get_slot(prog->ingame.slots, prog->ingame.size, x, y, z);
	  if (*slot <= EMPTY)
	    continue ;
	  if (*slot >= LAST_SLOT)
	    continue ;
	  pos[i].slot = *slot;

	  // Position en 3D
	  pos[i].pos.x = x - prog->ingame.size / 2.0 + 0.5 + z * 0.5 + prog->ingame.translation.x;
	  pos[i].pos.y = y - prog->ingame.size / 2.0 + 0.5 + z * 0.5 + prog->ingame.translation.y;
	  pos[i].pos.z = z;

	  // On calcule
	  rotate(&pos[i].pos, &rot);
	  i += 1;
	}
  grid = false;
  qsort_r(&pos[0], i, sizeof(pos[0]), compare_ball, prog);
  for (iter = 0; iter < i; ++iter)
    {
      if (pos[iter].pos.z >= prog->ingame.cursor.z && grid == false)
	{
	  double gridsize = (prog->ingame.size - pos[iter].pos.z) / 2.0;
	  
	  grid = true;
	  for (y = 0; y <= prog->ingame.size - pos[iter].pos.z; ++y)
	    {
	      lpos.pos.x = -gridsize + prog->ingame.translation.x;
	      lpos.pos.y = y - gridsize + prog->ingame.translation.y;
	      lpos.pos.z = -prog->ingame.size / 8.0 + (int)prog->ingame.cursor.z;
	      rotate(&lpos.pos, &rot);
	      p[0] = isoproject(&lpos.pos, prog);
	      lpos.pos.x = +gridsize + prog->ingame.translation.x;
	      lpos.pos.y = y - gridsize + prog->ingame.translation.y;
	      lpos.pos.z = -prog->ingame.size / 8.0 + (int)prog->ingame.cursor.z;
	      rotate(&lpos.pos, &rot);
	      p[1] = isoproject(&lpos.pos, prog);

	      p[0].x += prog->screen->buffer.width / 2;
	      p[0].y += prog->screen->buffer.height / 2;
	      p[1].x += prog->screen->buffer.width / 2;
	      p[1].y += prog->screen->buffer.height / 2;
	      bsl(&prog->screen->buffer, &p[0], &coline[0]);
	      bsl(&prog->normal_screen->buffer, &p[0], &coline[0]);
	    }
	  for (x = 0; x <= prog->ingame.size - pos[iter].pos.z; ++x)
	    {
	      lpos.pos.x = x - gridsize + prog->ingame.translation.x;
	      lpos.pos.y = -gridsize + prog->ingame.translation.y;
	      lpos.pos.z = -prog->ingame.size / 8.0 + (int)prog->ingame.cursor.z;
	      rotate(&lpos.pos, &rot);
	      p[0] = isoproject(&lpos.pos, prog);
	      lpos.pos.x = x - gridsize + prog->ingame.translation.x;
	      lpos.pos.y = +gridsize + prog->ingame.translation.y;
	      lpos.pos.z = -prog->ingame.size / 8.0 + (int)prog->ingame.cursor.z;
	      rotate(&lpos.pos, &rot);
	      p[1] = isoproject(&lpos.pos, prog);

	      p[0].x += prog->screen->buffer.width / 2;
	      p[0].y += prog->screen->buffer.height / 2;
	      p[1].x += prog->screen->buffer.width / 2;
	      p[1].y += prog->screen->buffer.height / 2;
	      bsl(&prog->screen->buffer, &p[0], &coline[0]);
	      bsl(&prog->normal_screen->buffer, &p[0], &coline[0]);
	    }

	  // Position du curseur
	  lpos.pos.x = (prog->ingame.cursor.x + 0) - gridsize + prog->ingame.translation.x;
	  lpos.pos.y = (prog->ingame.cursor.y + 0) - gridsize + prog->ingame.translation.y;
	  lpos.pos.z = -prog->ingame.size / 8.0 + (int)prog->ingame.cursor.z;
	  rotate(&lpos.pos, &rot);
	  p[0] = isoproject(&lpos.pos, prog);
	  lpos.pos.x = (prog->ingame.cursor.x + 1) - gridsize + prog->ingame.translation.x;
	  lpos.pos.y = (prog->ingame.cursor.y + 1) - gridsize + prog->ingame.translation.y;
	  lpos.pos.z = -prog->ingame.size / 8.0 + (int)prog->ingame.cursor.z;
	  rotate(&lpos.pos, &rot);
	  p[1] = isoproject(&lpos.pos, prog);

	  p[0].x += prog->screen->buffer.width / 2;
	  p[0].y += prog->screen->buffer.height / 2;
	  p[1].x += prog->screen->buffer.width / 2;
	  p[1].y += prog->screen->buffer.height / 2;
	  bsl(&prog->screen->buffer, &p[0], &coline[0]);
	  bsl(&prog->normal_screen->buffer, &p[0], &coline[0]);


	  lpos.pos.x = (prog->ingame.cursor.x + 1) - gridsize + prog->ingame.translation.x;
	  lpos.pos.y = (prog->ingame.cursor.y + 0) - gridsize + prog->ingame.translation.y;
	  lpos.pos.z = -prog->ingame.size / 8.0 + (int)prog->ingame.cursor.z;
	  rotate(&lpos.pos, &rot);
	  p[0] = isoproject(&lpos.pos, prog);
	  lpos.pos.x = (prog->ingame.cursor.x + 0) - gridsize + prog->ingame.translation.x;
	  lpos.pos.y = (prog->ingame.cursor.y + 1) - gridsize + prog->ingame.translation.y;
	  lpos.pos.z = -prog->ingame.size / 8.0 + (int)prog->ingame.cursor.z;
	  rotate(&lpos.pos, &rot);
	  p[1] = isoproject(&lpos.pos, prog);

	  p[0].x += prog->screen->buffer.width / 2;
	  p[0].y += prog->screen->buffer.height / 2;
	  p[1].x += prog->screen->buffer.width / 2;
	  p[1].y += prog->screen->buffer.height / 2;
	  bsl(&prog->screen->buffer, &p[0], &coline[0]);
	  bsl(&prog->normal_screen->buffer, &p[0], &coline[0]);
	}
      
      p[0] = isoproject(&pos[iter].pos, prog);
      p[0].x += prog->screen->buffer.width / 2;
      p[0].y += prog->screen->buffer.height / 2;

      if (pos[iter].slot == BLACKBALLS)
	prog->ingame.ball->color_mask.full = COLOR(255, 0x6E, 0x33, 0x00);
      else if (pos[iter].slot == WHITEBALLS)
	prog->ingame.ball->color_mask.full = COLOR(255, 0xCA, 0xB2, 0xA3);

      bunny_blit(&prog->screen->buffer, prog->ingame.ball, &p[0]);
      bunny_blit(&prog->normal_screen->buffer, prog->ingame.normal_ball, &p[0]);
    }

  //const t_bunny_position *mpos = bunny_get_mouse_position();

  //bunny_normal_map_shader(&prog->normal_configuration);
  //prog->normal_configuration.lights[0].x = mpos->x;
  //prog->normal_configuration.lights[0].y = prog->win->buffer.height - mpos->y;

  t_bunny_position posa;

  lig.x = 2;
  lig.y = 0;
  lig.z = 1;
  rotate(&lig, &rot);
  posa = isoproject(&lig, prog);
  prog->normal_configuration.lights[0].x = posa.x + prog->screen->buffer.width / 2;
  prog->normal_configuration.lights[0].y = posa.y + prog->screen->buffer.height / 2;

  lig.x = 0;
  lig.y = 2;
  lig.z = 1;
  rotate(&lig, &rot);
  posa = isoproject(&lig, prog);
  prog->normal_configuration.lights[1].x = posa.x + prog->screen->buffer.width / 2;
  prog->normal_configuration.lights[1].y = posa.y + prog->screen->buffer.height / 2;

  lig.x = 0;
  lig.y = -2;
  lig.z = 1;
  rotate(&lig, &rot);
  posa = isoproject(&lig, prog);
  prog->normal_configuration.lights[2].x = posa.x + prog->screen->buffer.width / 2;
  prog->normal_configuration.lights[2].y = posa.y + prog->screen->buffer.height / 2;

  bunny_normal_map_shader(&prog->normal_configuration);
  bunny_blit_shader(&prog->win->buffer, prog->screen, NULL, prog->normal_shader);
  prog->screen->color_mask.full = ALPHA(32, WHITE);
  bunny_blit(&prog->win->buffer, prog->screen, NULL);
  prog->screen->color_mask.full = WHITE;
  bunny_display(prog->win);
  return (GO_ON);
}
