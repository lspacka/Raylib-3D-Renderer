#include "display.h"
#include <stdint.h>

Color* color_buffer = NULL;
Texture2D color_buffer_texture;

void draw_pixel(int x, int y, Color color)
{
    if (
        x<width && 
        x>0 &&
        y>0 &&
        y<height
    )
    color_buffer[(width*y) + x] = color;
}

void draw_grid(int cellSize, Color color)
{
    int width = GetScreenWidth();
    int height = GetScreenHeight();
    
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            if (row%cellSize==0 || col%cellSize==0 || row==height-1 || col==width-1)
                draw_pixel(col, row, color);
        }
    }
}

void draw_line(int x0, int y0, int x1, int y1, Color color)
{
    int delta_x = (x1 - x0);
    int delta_y = (y1 - y0);

    int side_length = abs(delta_x) >= abs(delta_y) ? abs(delta_x) : abs(delta_y);

    float x_inc = delta_x / (float)side_length;
    float y_inc = delta_y / (float)side_length;

    float current_x = x0;
    float current_y = y0;

    for (int i = 0; i <= side_length; i++) {
        // draw_pixel(round(current_x), round(current_y), color);
        draw_pixel(round(current_x), round(current_y), color);
        current_x += x_inc; 
        current_y += y_inc;
    }
}

void draw_rect(int x, int y, int width, int height, Color color)
{
    int rect_height = y + height;
    int rect_width = x + width;

    for (int recty = y; recty < rect_height; recty++) {
        for (int rectx = x; rectx < rect_width; rectx++) {
            draw_pixel(rectx, recty, color);
            // color_buffer[(window_width*ry) + rx] = color;
        }
    }
}

void clear_color_buffer(Color color) 
{
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            color_buffer[(width*y) + x] = color;
        }
    }
}


void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, Color color) 
{
    draw_line(x0, y0, x1, y1, color);
    draw_line(x1, y1, x2, y2, color);
    draw_line(x2, y2, x0, y0, color);
}