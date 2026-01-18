#include "includes/vec2.h"

void wrap_radian(float *angle_radian)
{
    *angle_radian = fmod(*angle_radian, 2.0f * M_PI);
    if (*angle_radian<0)
        *angle_radian += 2.0f * M_PI;
}

t_vec2 rotate_v2(t_vec2 v1, float angle_radian)
{
    float old_x;
    float old_y;

    old_x = v1.x;
    old_y = v1.y;
    v1.x = old_x * cosf(angle_radian) - old_y * sinf(angle_radian);
    v1.y = old_x * sinf(angle_radian) + old_y * cosf(angle_radian);
    return (v1);
}
