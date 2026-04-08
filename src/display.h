#ifndef DISPLAY_H
#define DISPLAY_H

#include "raylib.h"
#include "raymath.h"

void draw_grid(int cellSize, Color color);
void draw_line(int x0, int y0, int x1, int y1, Color color);
void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, Color color);


#endif 