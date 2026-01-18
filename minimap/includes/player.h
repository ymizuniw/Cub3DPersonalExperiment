#ifndef PLAYER_H
#define PLAYER_H

#include "../../vector/includes/vec2.h"

typedef struct s_player
{
    t_vec2 pos;
    t_vec2 dir;
} t_player;

void player_set_dir(t_player *player, char c);

#endif
