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