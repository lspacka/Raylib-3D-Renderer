#include <stdio.h>
#include <stdint.h>
#include "raylib.h"
#include "vector.h"
#include "display.h"

#define N_POINTS (9 * 9 * 9)

void setup();
void update();
void render();
Vector2 project(Vector3 point);

Vector2 projected_points[N_POINTS];
Vector3 cube_points[N_POINTS];
Vector3 camera_position = { .x=0, .y=0, .z=-5 };
Vector3 cube_rotation = { .x=0, .y=0, .z=0 };
Color color;

int monitor;
int width;
int height;
float fov_factor = 640;                                 // field of view factor

void setup()
{
    // start loading an array of vectors (video 26)
    // from -1 to 1 (in this 9*9*9 cube)
    int point_count = 0;
    for (float x = -1; x < 1; x += 0.25) {
        for (float y = -1; y < 1; y += 0.25) {
            for (float z = -1; z < 1; z += 0.25) {
                Vector3 new_point = { .x=x, .y=y, .z=z };
                cube_points[point_count++] = new_point;
            }
        }
    }
}

Vector2 project(Vector3 point)
{
    Vector2 projected_point = {
        .x = (point.x * fov_factor / point.z),
        .y = (point.y * fov_factor) / point.z,
    };

    return projected_point;
}

void update()
{
    cube_rotation.x += 0.01;
    cube_rotation.y += 0.01;
    cube_rotation.z += 0.01;
    
    for (int i = 0; i < N_POINTS; i++) {
        Vector3 point = cube_points[i];
        Vector3 transformed_point = vec3_rotate_x(point, cube_rotation.x);

        transformed_point = vec3_rotate_y(transformed_point, cube_rotation.y);
        transformed_point = vec3_rotate_z(transformed_point, cube_rotation.z);
        transformed_point.z -= camera_position.z;
        
        Vector2 projected_point = project(transformed_point);
        projected_points[i] = projected_point;
    }
}

void render()
{
    for (int i = 0; i < N_POINTS; i++) {
        Vector2 projected_point = projected_points[i];

        DrawRectangle(
            projected_point.x + (width/2),
            projected_point.y + (height/2),
            4,
            4,
            color
        );
    }

    ClearBackground(BLACK);
}

int main()
{
    SetTraceLogLevel(LOG_WARNING);
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    SetTargetFPS(60);

    InitWindow(0, 0, "3D Renderer");
    monitor = GetCurrentMonitor();
    width = GetMonitorWidth(monitor);
    height = GetMonitorHeight(monitor);
    color = GetColor(0x00FF09FF);
    
    setup();

    while(!WindowShouldClose()) {
        BeginDrawing();

        update();
        render();
        // draw_grid(5, color);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}