#ifndef MODEL_H
#define MODEL_H

#include <assert.h>
#include <fstream>

#include "mathlib.h"

struct ModelBuffer
{
  Vector3f vertices[10000];
  Vector3 faces[30000];
  Vector3f normals[30000];
  Vector3 normal_faces[30000];
  Vector2f tex_coords[30000];
  Vector3 tex_faces[30000];
  
  i32 vertex_count;
  i32 normal_count; 
  i32 face_count;
  i32 tex_count; 
};

bool object_to_render(const char *filename, ModelBuffer &buffer);

#endif
