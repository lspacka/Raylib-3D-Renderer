#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "raylib.h"

typedef struct {
    int a;
    int b;
    int c;
} face_t;

typedef struct {
    Vector2 points[3];
} triangle_t;

#endif