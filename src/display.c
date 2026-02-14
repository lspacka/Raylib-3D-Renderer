#include "display.h"

void draw_grid(int cellSize, Color color)
{
    int width = GetScreenWidth();
    int height = GetScreenHeight();
    
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            if (row%cellSize==0 || col%cellSize==0 || row==height-1 || col==width-1)
                DrawPixel(col, row, color);
        }
    }
}

void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, Color color) 
{
    DrawLine(x0, y0, x1, y1, color);
    DrawLine(x1, y1, x2, y2, color);
    DrawLine(x2, y2, x0, y0, color);
}