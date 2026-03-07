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
  // const char *model_filename = "../obj/african_head/african_head.obj";
  // const char *model_filename = "../obj/diablo3_pose/diablo3_pose.obj";
  const char *model_filename = "../obj/bunny.obj";
  // const char *model_filename = "../obj/penger.obj";
  // const char *model_filename = "../obj/teapot.obj";

  object_to_render(model_filename, *buffer);

  // rasterize_model(*buffer, framebuffer);  

  /*
    draw_triangle({7, 45}, {35, 100}, {45, 60}, framebuffer, pink);

    draw_triangle({120, 35}, {90, 5}, {45, 110}, framebuffer, purple);

    draw_triangle({115, 83}, {80, 90}, {85, 120}, framebuffer, grey);

    scanline_rendering({7, 45}, {35, 100}, {45, 60}, framebuffer, pink);
  
    scanline_rendering({120, 35}, {90, 5}, {45, 110}, framebuffer, purple);

    scanline_rendering({115, 83}, {80, 90}, {85, 120}, framebuffer, grey);
  
    fill_triangle({7, 45}, {35, 100}, {45, 60}, framebuffer, pink);

    fill_triangle({120, 35}, {90, 5}, {45, 110}, framebuffer, purple);

    fill_triangle({115, 83}, {80, 90}, {85, 120}, framebuffer, grey);
  */

  // fill_triangle({17, 4, 13}, {55, 39, 128}, {23, 59, 255}, framebuffer, grey);


  fill_triangle({17, 4, 13}, {55, 39, 128}, {23, 59, 255},
                {0, 0, 255}, {255, 255, 0}, {255, 0, 255},
                framebuffer);


  framebuffer.write_tga_file("framebuffer.tga");

  return 0;
}
