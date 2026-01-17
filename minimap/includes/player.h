#ifndef PLAYER_H
#define PLAYER_H

typedef struct s_player
{
    float x;
    float y;
    float dir_x;
    float dir_y;
} t_player;

void player_set_dir(t_player *player, char c);

#endif
