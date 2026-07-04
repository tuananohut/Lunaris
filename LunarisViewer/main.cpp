#include "../Lunaris/include/renderer.h"
#include <iostream>

int main(int argc, char** argv)
{
  constexpr i32 width  = 1080;			  
  constexpr i32 height = 1080;
                           
  TGAImage framebuffer(width, height, TGAImage::RGB);
  std::vector<double> zbuffer(width*height, -std::numeric_limits<double>::max());
 
  for (size_t i = 0; i < width; ++i)
    {
      for (size_t j = 0; j < height; ++j)
        {
          framebuffer.set(i, j, navy); 
        }
    }
  
  ModelBuffer *buffer = new ModelBuffer();
  const char *model_filename = "../obj/african_head/african_head.obj";
  // const char *model_filename = "../obj/diablo3_pose/diablo3_pose.obj";
  // const char *model_filename = "../obj/boggie/boggie_full.obj";
  // const char *model_filename = "../obj/bunny.obj";
  // const char *model_filename = "../obj/penger.obj";
  // const char *model_filename = "../obj/teapot.obj";

  MaterialBuffer *material = new MaterialBuffer();;
  const char *diffuse_texture = "../obj/african_head/african_head_diffuse.tga";
  load_material(material->diffusemap, diffuse_texture);

  object_to_render(model_filename, *buffer);

  std::cout << "Tex count: " << std::endl;
  std::cout << buffer->tex_count << std::endl;
  
  rasterize_model(*buffer, material, framebuffer, zbuffer);

  std::cout << "Writing file..." << std::endl;
  framebuffer.write_tga_file("framebuffer.tga");
  std::cout << "Done." << std::endl;

  delete buffer;
  delete material;
  
  return 0;
}
