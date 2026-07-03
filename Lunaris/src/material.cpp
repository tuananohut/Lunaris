#include "../include/material.h"

i32 load_material(TGAImage &material, const char *filepath)
{
  i32 read = material.read_tga_file(filepath);

  if (1 == read)
    {
      std::cout << "read_tga_file successful!\n";
    }
  else
    {
      std::cout << "read_tga_file unsuccessful!\n";
    }
  
  return read;
}

