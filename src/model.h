#ifndef MODEL_H
#define MODEL_H

#include <assert.h>
#include <fstream>

#include "mathlib.h"

struct ModelBuffer
{
  Vector3f vertices[10000];
  Vector3i faces[30000];

  int vertex_count;
  int face_count; 
};

bool object_to_render(const char *filename, ModelBuffer &buffer);

#endif
