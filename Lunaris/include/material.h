#ifndef MATERIAL_H
#define MATERIAL_H

#include "mathlib.h"

struct MaterialBuffer
{
  TGAImage diffusemap; 
};

i32 load_material(MaterialBuffer *material); 

#endif
