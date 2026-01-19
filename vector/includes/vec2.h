#ifndef VEC2_H
#define VEC2_H

#include <math.h>

typedef struct s_vec2
{
    float x;
    float y;
} t_vec2;

t_vec2    init_v2(float x, float y);
t_vec2 add_v2(t_vec2 v1, t_vec2 v2);
t_vec2 subtract_v2(t_vec2 v1, t_vec2 v2);
t_vec2 rotate_v2(t_vec2 v1, float angle_radian);
t_vec2 normalize_vec2(t_vec2 v1);

#endif
