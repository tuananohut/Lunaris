#include <cstdlib>
#include <ctime>

#include "defines.h"

void test_triangle(TGAImage &framebuffer)
{
  int ax =  7 * 8, ay =  3 * 8;
  int bx = 12 * 8, by = 37 * 8;
  int cx = 62 * 8, cy = 53 * 8;
  
  Point point_1 = { ax, ay };
  Point point_2 = { bx, by };
  Point point_3 = { cx, cy };

  draw_triangle(point_1, point_2, point_3,
		framebuffer, pink);
}

int main(int argc, char **argv)
{
  constexpr int width  = 64;
  constexpr int height = 64;
  TGAImage framebuffer(width, height, TGAImage::RGB);

  Point start_point;
  Point end_point;

  TGAColor color; 
  
  std::srand(static_cast<unsigned int>(std::time(0)));
  for (int i = 0; i < (1<<24); i++)
    {
      int ax = rand()%width, ay = rand()%height;
      int bx = rand()%width, by = rand()%height;

      start_point = { ax, ay };
      end_point = { bx, by };

      color = { static_cast<uint8_t>(rand()%255),
		static_cast<uint8_t>(rand()%255),
		static_cast<uint8_t>(rand()%255),
		static_cast<uint8_t>(rand()%255) };

      draw_line(start_point, end_point, framebuffer, color);
    }

  framebuffer.write_tga_file("test.tga");
  return 0;
}
