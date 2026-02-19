#ifndef MODEL_H
#define MODEL_H

#include <assert.h>
#include <fstream>

#include "mathlib.h"

struct ModelBuffer
{
  Vector3f *vertices;
  Vector3i *faces;

  int vertex_count;
  int face_count; 
};

#endif
