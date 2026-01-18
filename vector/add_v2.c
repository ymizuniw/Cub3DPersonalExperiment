#include "includes/vec2.h"

t_vec2 add_v2(t_vec2 v1, t_vec2 v2)
{
    t_vec2 ret;
    ret.x = v1.x + v2.x;
    ret.y = v1.y + v2.y;
    return (ret);
}
