#include "defines.h"

int main(int argc, char** argv)
{
  constexpr int width  = 64 * 8;			  
  constexpr int height = 64 * 8;			  
  TGAImage framebuffer(width, height, TGAImage::RGB);
  
  int ax =  7 * 8, ay =  3 * 8;
  int bx = 12 * 8, by = 37 * 8;
  int cx = 62 * 8, cy = 53 * 8;
  
  for (size_t i = 0; i < width; ++i)
    {
      for (size_t j = 0; j < height; ++j)
	{
	  framebuffer.set(i, j, navy); 
	}
    }
  
  Point start_point_1 = { ax, ay };
  Point end_point_1   = { bx, by };

  Point start_point_2 = { bx, by };
  Point end_point_2   = { cx, cy };

  Point start_point_3 = { ax, ay };
  Point end_point_3   = { cx, cy };

  draw_line(start_point_1, end_point_1, framebuffer, pink);
  draw_line(start_point_2, end_point_2, framebuffer, purple);
  draw_line(start_point_3, end_point_3, framebuffer, grey);
   
  framebuffer.write_tga_file("framebuffer.tga");
  return 0;
}
