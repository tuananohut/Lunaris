#include "defines.h"

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
  
  int ax =  7 * 8, ay =  3 * 8;
  int bx = 12 * 8, by = 37 * 8;
  int cx = 62 * 8, cy = 53 * 8;
  
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
  
  /*
  float ax =  7 * 8, ay =  3 * 8;
  float bx = 12 * 8, by = 37 * 8;
  float cx = 62 * 8, cy = 53 * 8;
    
  float n_ax = point_ndc_x(ax);
  float n_bx = point_ndc_x(bx);
  float n_cx = point_ndc_x(cx);

  float n_ay = point_ndc_y(ay);
  float n_by = point_ndc_y(by);
  float n_cy = point_ndc_y(cy);
  
  Point2f start_point_1 = { n_ax, n_ay };
  Point2f end_point_1   = { n_bx, n_by };
			    	  
  Point2f start_point_2 = { n_bx, n_by };
  Point2f end_point_2   = { n_cx, n_cy };
			    	  
  Point2f start_point_3 = { n_ax, n_ay };
  Point2f end_point_3   = { n_cx, n_cy };

  draw_line(screen(start_point_1), screen(end_point_1), framebuffer, pink);
  draw_line(screen(start_point_2), screen(end_point_2), framebuffer, purple);
  draw_line(screen(start_point_3), screen(end_point_3), framebuffer, grey);
  
  framebuffer.write_tga_file("framebuffer_float.tga");
  */
  
  return 0;
}
