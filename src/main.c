#include <stdio.h>
#include <stdint.h>
#include "raylib.h"
#include "display.h"

void draw_grid(int cellSize, Color color);

int main()
{
    SetTraceLogLevel(LOG_WARNING);
    SetConfigFlags(FLAG_FULLSCREEN_MODE);

    InitWindow(0, 0, "3D Renderer");
    SetTargetFPS(60);

    int monitor = GetCurrentMonitor();
    int width = GetMonitorWidth(monitor);
    int height = GetMonitorHeight(monitor);
    Color color = GetColor(0x00FFAAFF);

    while(!WindowShouldClose()) {
        BeginDrawing();
        
        draw_grid(5, color);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}