#include "../include/material.h"

i32 load_material(MaterialBuffer *material)
{
  material->diffusemap = read_tga_file("obj/african_head/african_head_diffuse.tga");
  return 1;
}

