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

void fill_flat_bottom_triangle(int x0 , int y0, int x1, int y1, int x2, int y2, Color color);
void fill_flat_top_triangle(int x0, int y0, int x1, int y1, int x2, int y2, Color color);
void draw_filled_triangle(int x0, int y0, int x1, int y1, int x2, int y2, Color color);

#endif