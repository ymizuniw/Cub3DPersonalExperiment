#include "includes/vec2.h"

t_vec2 normalize_vec2(t_vec2 v1)
{
    float len;
    len = sqrtf(v1.x * v1.x + v1.y*v1.y);
    if (len>0.0f)
    {
        v1.x /= len;
        v1.y /= len;
    }
    return (v1);
}
