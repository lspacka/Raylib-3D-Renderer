#ifndef DISPLAY_H
#define DISPLAY_H

#include "raylib.h"
#include "raymath.h"

extern Color* color_buffer;
extern Texture2D color_buffer_texture;
extern int monitor;
extern int width;
extern int height;

void draw_grid(int cellSize, Color color);
void draw_line(int x0, int y0, int x1, int y1, Color color);
void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, Color color);
void clear_color_buffer(Color color);


#endif 