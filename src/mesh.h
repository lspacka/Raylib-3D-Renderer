#ifndef MESH_H
#define MESH_H

#include "raylib.h"
#include "triangle.h"

typedef struct {
    Vector3* vertices;
    Vector3 rotation;
    face_t* faces;
} mesh_t;

extern mesh_t mesh;

void load_obj_file_data(char* filename);

#endif