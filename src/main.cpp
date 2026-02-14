#include "defines.h"

void draw_line(Point start_point, Point end_point, TGAImage &framebuffer, TGAColor color)
{    
  for (float t = 0; t < 1; t += .02)
    {
      int xx = std::round((1 - t) * start_point.x + t * end_point.x);
      int yy = std::round((1 - t) * start_point.y + t * end_point.y);

      framebuffer.set(xx, yy, color);
    }
} 

int main(int argc, char** argv)
{
  constexpr int width  = 64;			  
  constexpr int height = 64;			  
  TGAImage framebuffer(width, height, TGAImage::RGB);
  
  int ax =  7, ay =  3;
  int bx = 12, by = 37;
  int cx = 62, cy = 53;
  
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
