#include <stdio.h>
#include "mesh.h"
#include "array.h"

mesh_t mesh = {
    .vertices = NULL,
    .rotation = { 0, 0, 0 },
    .faces = NULL
};

void load_obj_file_data(char* filename)
{
    FILE* file;
    Vector3 vertex;
    face_t face;
    char line[1024];

    file = fopen(filename, "r");
    if (file == NULL) 
        printf("couldn\'t open file %s\n", filename);

    while (fgets(line, sizeof(line), file)) {
        if (line[0]=='v' && line[1]==' ') 
            if (sscanf(line, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z) == 3)
                array_push(mesh.vertices, vertex);

        if (line[0] == 'f')
            if (sscanf(line, "f %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &face.a, &face.b, &face.c) == 3) {
                face.a--;
                face.b--;
                face.c--;
                array_push(mesh.faces, face);
            }
    }
}