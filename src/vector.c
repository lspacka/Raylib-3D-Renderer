#include <math.h>
#include "vector.h"

Vector3 vec3_rotate_x(Vector3 v, float angle)
{
    Vector3 rotated_vector = {
        .x = v.x,
        .y = v.y*cos(angle) - v.z*sin(angle),
        .z = v.y*sin(angle) + v.z*cos(angle)
    };

    return rotated_vector;
}

Vector3 vec3_rotate_y(Vector3 v, float angle)
{
    Vector3 rotated_vector = {
        .x = v.x*cos(angle) - v.z*sin(angle),
        .y = v.y,
        .z = v.x*sin(angle) + v.z*cos(angle)
    };
    
    return rotated_vector;
}

Vector3 vec3_rotate_z(Vector3 v, float angle)
{
    Vector3 rotated_vector = {
        .x = v.x*cos(angle) - v.y*sin(angle),
        .y = v.x*sin(angle) + v.y*cos(angle),
        .z = v.z
    };

    return rotated_vector;
}