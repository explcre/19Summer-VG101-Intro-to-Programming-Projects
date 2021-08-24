
#include "head.h"
//Find the minimum
float min(float x, float y)
{
    if (x < y)
        return x;
    else
        return y;
}
//Find the maximum
float max(float x, float y)
{
    if (x > y)
        return x;
    else
        return y;
}
//Find the dot product
float mult(float x1, float y1, float x2, float y2, float xx, float yy)
{
    return ((xx - x1) * (yy - y1) - (xx - x2) * (yy - y2));
}
//Find the cross product
float cross(float x1, float y1, float x2, float y2, float xx, float yy)
{
    return (x2 - x1) * (yy - y1) - (xx - x1) * (y2 - y1);
}


