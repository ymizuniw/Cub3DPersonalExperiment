#ifndef PLAYER_H
# define PLAYER_H

# include "../../vector/includes/vec2.h"

typedef struct s_player
{
	t_vec2	pos;
	t_vec2	dir;
	t_vec2	plane;
}			t_player;

void		player_set_dir(t_player *player, char c);
void		rotate_player(t_player *player, float angle_radian);
void		player_init_plane_from_dir(t_player *player);
void		player_rotate_plane(t_player *player, float angle_radian);

#endif
