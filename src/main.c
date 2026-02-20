#include <stdio.h>
#include <stdint.h>
#include "raylib.h"
#include "vector.h"
#include "triangle.h"
#include "mesh.h"
#include "array.h"
#include "display.h"

Vector3 camera_position = { .x=0, .y=0, .z=-5 };
triangle_t* triangles_to_render = NULL;
Color color;

int monitor;
int width;
int height;
float fov_factor = 640;                                 // field of view factor

// Vector2 project(Vector3 point);
// void setup();
// void update();
// void render();

void setup()
{
    load_obj_file_data("./assets/spaceship.obj");
}

Vector2 project(Vector3 point)
{
    Vector2 projected_point = {
        .x = (point.x * fov_factor) / point.z,
        .y = (point.y * fov_factor) / point.z,
    };

    return projected_point;
}

void update()
{
    mesh.rotation.x += 0.01;
    mesh.rotation.y += 0.01;
    mesh.rotation.z += 0.01;
    
    triangles_to_render = NULL;
    int num_faces = array_length(mesh.faces);

    for (int i = 0; i < num_faces; i++) {
        face_t mesh_face = mesh.faces[i];
        Vector3 face_vertices[3];
        triangle_t projected_triangle;

        face_vertices[0] = mesh.vertices[mesh_face.a];
        face_vertices[1] = mesh.vertices[mesh_face.b];
        face_vertices[2] = mesh.vertices[mesh_face.c];

        for (int j = 0; j < 3; j++) {
            Vector3 transformed_vertex = face_vertices[j];
            transformed_vertex = vec3_rotate_x(transformed_vertex, mesh.rotation.x);
            transformed_vertex = vec3_rotate_y(transformed_vertex, mesh.rotation.y);
            transformed_vertex = vec3_rotate_z(transformed_vertex, mesh.rotation.z);
            
            transformed_vertex.z -= camera_position.z;

            Vector2 projected_point = project(transformed_vertex);

            projected_point.x += width / 2;
            projected_point.y += height / 2;

            projected_triangle.points[j] = projected_point;
        }
        array_push(triangles_to_render, projected_triangle);
    }
}

void render()
{
    int num_triangles = array_length(triangles_to_render);
    for (int i = 0; i < num_triangles; i++) {
        triangle_t triangle = triangles_to_render[i];

        draw_triangle(
            triangle.points[0].x,
            triangle.points[0].y,
            triangle.points[1].x,
            triangle.points[1].y,
            triangle.points[2].x,
            triangle.points[2].y,
            color
        );

        // vertices in counterclockwise order 
        // DrawTriangleLines (
        //     triangle.points[0],
        //     triangle.points[1],
        //     triangle.points[2],
        //     color
        // );
    }

    array_free(triangles_to_render);
}

void free_resources()
{
    array_free(mesh.faces);
    array_free(mesh.vertices);
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

        ClearBackground(BLACK);
        update();
        render();
        // draw_grid(5, color);

        EndDrawing();
    }

    CloseWindow();
    free_resources();

    return 0;
}