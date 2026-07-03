#ifndef MATERIAL_H
#define MATERIAL_H

#include <iostream>

#include "tgaimage.h"
#include "mathlib.h"

struct MaterialBuffer
{
  TGAImage diffusemap; 
};

i32 load_material(TGAImage &material, const char *filepath); 

#endif
