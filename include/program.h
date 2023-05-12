// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2024
// Hanged Bunny Studio 2014-2022
// EFRITS SAS 2022-2024
//
// Pylos

#ifndef			__PROGRAM_H__
# define		__PROGRAM_H__
# include		<lapin.h>

typedef union		s_zposition
{
  struct {
    double		x;
    double		y;
    double		z;
  };
  double		tab[3];
}			t_zposition;

typedef enum		e_slot
  {
   INVALID		= -1,
   EMPTY,
   BLACKBALLS,
   WHITEBALLS,
   LAST_SLOT
  }			t_slot;

typedef enum		e_context
  {
   INGAME,
   LAST_CONTEXT
  }			t_context;

typedef struct		s_ingame
{
  t_bunny_picture	*ball;
  t_slot		*slots;
  int			size;
  t_slot		turn;
  t_slot		last_game;
  t_bunny_accurate_position rotation; // rotate horizontaly or verticaly around 0, 0, 0, but not deeply
  t_bunny_accurate_position translation; // pour le plaisir
}			t_ingame;

typedef struct		s_program
{
  t_bunny_window	*win;
  t_bunny_picture	*screen;
  t_context		context;
  t_bunny_configuration	*cnf;

  // Contexts
  t_ingame		ingame;
}			t_program;

t_slot			*get_slot(t_slot		*s,
				  int			siz,
				  int			x,
				  int			y,
				  int			z);

t_slot			*get_slotp(t_program		*prog,
				   int			x,
				   int			y,
				   int			z);

#endif	//		__PROGRAM_H__
