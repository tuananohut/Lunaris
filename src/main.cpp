#include "renderer.h"

int main(int argc, char** argv)
{  
  TGAImage framebuffer(width, height, TGAImage::RGB);
  
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
  // const char *model_filename = "../obj/bunny.obj";
  // const char *model_filename = "../obj/penger.obj";
  // const char *model_filename = "../obj/teapot.obj";

  object_to_render(model_filename, *buffer);

  render_model(*buffer, framebuffer, grey);
   
  framebuffer.write_tga_file("framebuffer.tga");

  delete buffer;
  
  return 0;
}
