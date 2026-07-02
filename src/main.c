#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "vector.h"
#include "triangle.h"
#include "mesh.h"
#include "array.h"
#include "display.h"

Vector3 camera_position = { 0, 0, 0 };
triangle_t* triangles_to_render = NULL;
Color color;
Color line_color;
// Color* color_buffer;
// Texture2D color_buffer_texture;

int monitor;
int width;
int height;
float fov_factor = 640;         // field of view factor

// Vector2 project(Vector3 point);
// void setup();
// void update();
// void render();

void setup()
{  
    color_buffer = malloc(sizeof(Color) * width * height);
    Image blank = GenImageColor(width, height, BLACK);
    color_buffer_texture = LoadTextureFromImage(blank);
    UnloadImage(blank);


    load_obj_file_data("./assets/sphere.obj");
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
        Vector3 transformed_vertices[3];
        triangle_t projected_triangle;

        face_vertices[0] = mesh.vertices[mesh_face.a];
        face_vertices[1] = mesh.vertices[mesh_face.b];
        face_vertices[2] = mesh.vertices[mesh_face.c];

        // transformation loop
        for (int j = 0; j < 3; j++) {
            Vector3 transformed_vertex = face_vertices[j];
            transformed_vertex = vec3_rotate_x(transformed_vertex, mesh.rotation.x);
            transformed_vertex = vec3_rotate_y(transformed_vertex, mesh.rotation.y);
            transformed_vertex = vec3_rotate_z(transformed_vertex, mesh.rotation.z);
            
            transformed_vertex.z += 5;
            transformed_vertices[j] = transformed_vertex;
        }

        // check backface culling
        Vector3 vec_a = transformed_vertices[0];
        Vector3 vec_b = transformed_vertices[1];
        Vector3 vec_c = transformed_vertices[2];

        Vector3 vec_ab = Vector3Subtract(vec_b, vec_a);
        Vector3 vec_ac = Vector3Subtract(vec_c, vec_a);

        Vector3 face_normal = Vector3CrossProduct(vec_ab, vec_ac);

        Vector3 camera_ray = Vector3Subtract(camera_position, vec_a);

        // check alignment between camera ray and face normal
        float alignment = Vector3DotProduct(camera_ray, face_normal);
        // if not aligned skip rendering loop
        if (alignment < 0)
            continue;

        // rendering loop
        for (int j = 0; j < 3; j++) {
            Vector2 projected_point = project(transformed_vertices[j]);
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

        // draw filled triangle
        // DrawTriangle(
        //     triangle.points[0],
        //     triangle.points[1],
        //     triangle.points[2],
        //     color
        // );
        // draw_filled_triangle(
        //     triangle.points[0].x, triangle.points[0].y,
        //     triangle.points[1].x, triangle.points[1].y,
        //     triangle.points[2].x, triangle.points[2].y,
        //     color
        // );

        // draw mesh
        draw_triangle(
            triangle.points[0].x, triangle.points[0].y,
            triangle.points[1].x, triangle.points[1].y,
            triangle.points[2].x, triangle.points[2].y,
            line_color
        );

        // vertices in counterclockwise order 
        // DrawTriangleLines (
        //     triangle.points[0],
        //     triangle.points[1],
        //     triangle.points[2],
        //     line_color
        // );
    }

    UpdateTexture(color_buffer_texture, color_buffer);
    DrawTexture(color_buffer_texture, 0, 0, WHITE);

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
    SetConfigFlags(FLAG_VSYNC_HINT);     // sync frame swap to monitor refresh, avoids tearing and timing jitter *
    InitWindow(0, 0, "3D Renderer");

    monitor = GetCurrentMonitor();
    width = GetMonitorWidth(monitor);
    height = GetMonitorHeight(monitor);
    color = GetColor(0x00FFFFFF);
    line_color = GetColor(0xFF6600FF);
    
    setup();

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);
        // draw_grid(15, color);
        clear_color_buffer(BLACK);
        update();
        render();

        EndDrawing();
    }

    CloseWindow();
    free_resources();

    return 0;
}



// * the monitor refreshes the image on screen at a fixed rate (60 times per second). 
// Without vsync, the program just renders frames as fast as it can 
// and pushes them to the screen whenever they're ready — 
// which can land in the middle of a monitor refresh, 
// causing a half-old half-new frame to show (tearing), 
// or irregular timing between frames (jitter/stutter).
// FLAG_VSYNC_HINT tells Raylib to wait for the monitor's refresh signal 
// before swapping the new frame in, so the renders always land cleanly between refreshes. 
// Much smoother than SetTargetFPS which just uses a timer that can drift.