#ifndef INPUT_H
# define INPUT_H

typedef struct s_game	t_game;

int						on_keypress(int keycode, t_game *game);
int						on_wsad(int keycode, t_game *game);
int						on_right_left(int keycode, t_game *game);
int						on_close(void *param);

#endif
