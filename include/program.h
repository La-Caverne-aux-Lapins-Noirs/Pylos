// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2024
// Hanged Bunny Studio 2014-2022
// EFRITS SAS 2022-2024
//
// Pylos

#ifndef			__PROGRAM_H__
# define		__PROGRAM_H__
# include		<lapin.h>

typedef enum		e_game_action
  {
    PYLOS_LEVEL_UP,
    PYLOS_LEVEL_DOWN,
    PYLOS_GO_LEFT,
    PYLOS_GO_RIGHT,
    PYLOS_GO_UP,
    PYLOS_GO_DOWN,
    PYLOS_TAKE,
    PYLOS_PUT
  }			t_game_action;

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

typedef union		s_play
{
  struct {
    t_zposition		target; // ou mettre la balle
    t_zposition		origin; // d'ou on la prend? ou -1 si c'est la reserve
  };
  t_zposition		pickups[2];
  int			nbr_pickup; // on peut en prendre une ou deux
}			t_play;

typedef t_play		(*t_ai_play)(t_slot		*slot,
				     size_t		size,
				     int		quantity); // quantity est pour pickup

typedef struct		s_ball
{
  t_zposition		pos;
  t_slot		*slot;
}			t_ball;

typedef struct		s_ingame
{
  t_bunny_picture	*ball;
  t_bunny_picture	*normal_ball;
  t_slot		*slots;
  int			size;
  t_slot		turn;
  bool			remove;
  t_slot		last_game;
  t_bunny_accurate_position rotation; // rotate horizontaly or verticaly around 0, 0, 0, but not deeply
  t_bunny_accurate_position translation; // pour le plaisir
  t_zposition		cursor;

  int			clients[2]; // 0 est blanc, 1 est noir.
  int			nbr_clients;
  
  t_ai_play		play1;
  t_ai_play		play2;
  t_ai_play		pickup1;
  t_ai_play		pickup2;
  t_slot		*picked_up[2]; // la balle récupérée
  t_zposition		picked_up_pos[2];
  int			nbr_picked_up;
  int			balls1;
  int			balls2;
}			t_ingame;

typedef struct		s_program
{
  t_bunny_window	*win;
  t_bunny_picture	*screen;
  t_bunny_picture	*normal_screen;
  t_bunny_picture	*specular_screen;
  t_bunny_normal_map	normal_configuration;
  t_bunny_shader	*normal_shader;
  t_bunny_screen_tweak	screen_tweak_configuration;
  t_bunny_shader	*screen_tweak_shader;
  t_context		context;
  t_bunny_configuration	*cnf;
  t_bunny_font		*blacktext;
  t_bunny_font		*whitetext;

  t_bunny_server	*server;
  t_bunny_client	*client;

  // Contexts
  t_ingame		ingame;
}			t_program;

void			movement(t_program		*prog,
				 t_game_action		action);

t_slot			*get_slot(t_slot		*s,
				  int			siz,
				  int			x,
				  int			y,
				  int			z);

t_slot			*get_slotp(t_program		*prog,
				   int			x,
				   int			y,
				   int			z);

t_slot			*can_place(t_program		*prog,
				   int			x,
				   int			y,
				   int			z);
int			place(t_program			*prog,
			      int			x,
			      int			y,
			      int			z,
			      t_slot			s);
bool			detect_bonus(t_program		*prog,
				     int		x,
				     int		y,
				     int		z);
bool			can_removes(t_program		*prog,
				    int			x,
				    int			y,
				    int			z,
				    t_slot		player);
bool			removes(t_program		*prog,
				int			x,
				int			y,
				int			z,
				t_slot			player);

size_t			size_of_map(size_t		siz);

bool			alone_on_stage(t_program	*prog,
				       t_ball		*pos,
				       int		siz);

// Cette fonction sert seulement à déterminer une position aléatoire
void			all_places(t_program		*prog,
				   t_slot		*slot[static 4 * 4]);

#endif	//		__PROGRAM_H__
