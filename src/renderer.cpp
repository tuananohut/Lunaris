#include "renderer.h"

void draw_line(Vector2 p0, Vector2 p1, TGAImage &framebuffer, TGAColor color)
{
  bool steep = std::abs(p0.c[X] - p1.c[X]) < std::abs(p0.c[Y] - p1.c[Y]);
  if (steep)
    {
      std::swap(p0.c[X], p0.c[Y]);
      std::swap(p1.c[X], p1.c[Y]); 
    }
   
  if (p0.c[X] > p1.c[X])
    {
      std::swap(p0.c[X], p1.c[X]);
      std::swap(p0.c[Y], p1.c[Y]); 
    }

  int y = p0.c[Y];
  int ierror = 0; 
  for (int x = p0.c[X]; x < p1.c[X]; x++)
    {
      if (steep)
        framebuffer.set(y, x, color);
      else 
        framebuffer.set(x, y, color);

      ierror += 2 * std::abs(p1.c[Y] - p0.c[Y]); 
	
      y += (p1.c[Y] > p0.c[Y] ? 1 : -1) * (ierror > (p1.c[X] - p0.c[X])); // Up or down ? 
      ierror -= 2 * (p1.c[X] - p0.c[X]) * (ierror > (p1.c[X] - p0.c[X])); 
    }	
} 

void draw_triangle(Vector2 point1, Vector2 point2, Vector2 point3,
                   TGAImage &framebuffer, TGAColor color)
{
  draw_line(point1, point2, framebuffer, color);
  draw_line(point2, point3, framebuffer, color);
  draw_line(point1, point3, framebuffer, color);
}

Vector3 screen(const Vector3f &point)
{
  // -1..1 => (after added 1) 0..2 => (divided 2) 0..1 => (multiplied width or height)0..w/h 

  return
    {
      static_cast<int>((point.c[X] + 1.) / 2 * width),
      static_cast<int>((point.c[Y] + 1.) / 2 * height),
      static_cast<int>((point.c[Z] + 1.) * 255./2)
    }; 
}

Vector3f translate_z(Vector3f &point3f, float dz)
{
  point3f.c[Z] += dz;
  return point3f; 
}

// screen => project => translate_z

void render_model(ModelBuffer& buffer, TGAImage &framebuffer, TGAColor color)
{
  for (int i = 0; i < buffer.face_count; i++)
    {
      Vector3 face = buffer.faces[i];

      Vector3 vertex0_ = screen(buffer.vertices[face.c[X]]);   
      Vector3 vertex1_ = screen(buffer.vertices[face.c[Y]]);   
      Vector3 vertex2_ = screen(buffer.vertices[face.c[Z]]);   

      Vector2 vertex0 = {vertex0_.c[X], vertex0_.c[Y]};
      Vector2 vertex1 = {vertex1_.c[X], vertex1_.c[Y]};
      Vector2 vertex2 = {vertex2_.c[X], vertex2_.c[Y]};

      draw_triangle(vertex0, vertex1, vertex2, framebuffer, color); 
    }
}

void scanline_rendering(Vector2 point1, Vector2 point2, Vector2 point3,
                        TGAImage &framebuffer, TGAColor color)
{
  if (point2.c[Y] > point3.c[Y])
    {
      std::swap(point2.c[Y], point3.c[Y]);
      std::swap(point2.c[X], point3.c[X]); 
    }

  if (point1.c[Y] > point3.c[Y])
    {
      std::swap(point1.c[Y], point3.c[Y]);
      std::swap(point1.c[X], point3.c[X]); 
    }

  if (point1.c[Y] > point2.c[Y])
    {
      std::swap(point1.c[Y], point2.c[Y]);
      std::swap(point1.c[X], point2.c[X]);
    }

  int total_height = point3.c[Y] - point1.c[Y];

  if (point1.c[Y] != point2.c[Y])
    {
      int segment_height = point2.c[Y] - point1.c[Y];
      for (int y = point1.c[Y]; y <= point2.c[Y]; y++)
        {
          int x1 = point1.c[X] + ((point3.c[X] - point1.c[X]) * (y - point1.c[Y])) / total_height; 
          int x2 = point1.c[X] + ((point2.c[X] - point1.c[X]) * (y - point1.c[Y])) / segment_height;
          for (int x = std::min(x1, x2); x < std::max(x1, x2); x++)
            {
              framebuffer.set(x, y, color);
            }
        }
    }

  if (point2.c[Y] != point3.c[Y])
    {
      int segment_height = point3.c[Y] - point2.c[Y];
      for (int y = point2.c[Y]; y <= point3.c[Y]; y++)
        {
          int x1 = point1.c[X] + ((point3.c[X] - point1.c[X]) * (y - point1.c[Y])) / total_height; 
          int x2 = point2.c[X] + ((point3.c[X] - point2.c[X]) * (y - point2.c[Y])) / segment_height;
          for (int x = std::min(x1, x2); x < std::max(x1, x2); x++)
            {
              framebuffer.set(x, y, color);
            }
        }
    }
}


void rasterize_model(ModelBuffer& buffer, TGAImage &framebuffer, TGAImage &zbuffer)
{
  for (int i = 0; i < buffer.face_count; i++)
    {
      Vector3 face = buffer.faces[i];

      Vector3 vertex0 = screen(buffer.vertices[face.c[X]]);   
      Vector3 vertex1 = screen(buffer.vertices[face.c[Y]]);   
      Vector3 vertex2 =	screen(buffer.vertices[face.c[Z]]);

      TGAColor rnd;
      for (int c = 0; c < 3; c++)
        rnd[c] = std::rand()%255;

      fill_triangle(vertex0, vertex1, vertex2, framebuffer, zbuffer, rnd); 
    }
}

void fill_triangle(Vector2 point1, Vector2 point2, Vector2 point3,
                   TGAImage &framebuffer, TGAColor color)
{
  int bbminx = std::min(std::min(point1.c[X], point2.c[X]), point3.c[X]); 
  int bbminy = std::min(std::min(point1.c[Y], point2.c[Y]), point3.c[Y]);
  int bbmaxx = std::max(std::max(point1.c[X], point2.c[X]), point3.c[X]);
  int bbmaxy = std::max(std::max(point1.c[Y], point2.c[Y]), point3.c[Y]); 
  double total_area = signed_triangle_area(point1, point2, point3);
  if (total_area < 1)
    return; // backface culling + discarding triangles that cover less than a pixel
  
#pragma omp parallel for
  for (int y = bbminy; y <= bbmaxy; y++)
    {
      for (int x = bbminx; x <= bbmaxx; x++)
        {
          Vector2 point = {x, y};
          double alpha = signed_triangle_area(point, point2, point3) / total_area; 
          double beta  = signed_triangle_area(point, point3, point1) / total_area; 
          double gamma = signed_triangle_area(point, point1, point2) / total_area; 

          if (alpha < 0 || beta < 0 || gamma < 0)
            continue; 

          framebuffer.set(x, y, color); 
        }
    }
}

void fill_triangle(Vector3 point1, Vector3 point2, Vector3 point3,
                   TGAImage &framebuffer, TGAImage &zbuffer, TGAColor color)
{
  int bbminx = std::min(std::min(point1.c[X], point2.c[X]), point3.c[X]); 
  int bbminy = std::min(std::min(point1.c[Y], point2.c[Y]), point3.c[Y]);
  int bbmaxx = std::max(std::max(point1.c[X], point2.c[X]), point3.c[X]);
  int bbmaxy = std::max(std::max(point1.c[Y], point2.c[Y]), point3.c[Y]);

  bbminx = std::max(0, bbminx);
  bbmaxx = std::min(width-1, bbmaxx);
  bbminy = std::max(0, bbminy);
  bbmaxy = std::min(height-1, bbmaxy);
  
  double total_area = signed_triangle_area(point1, point2, point3);
  if (total_area < 1)
    return; // backface culling + discarding triangles that cover less than a pixel

#pragma omp parallel for
  for (int y = bbminy; y <= bbmaxy; y++)
    {
      for (int x = bbminx; x <= bbmaxx; x++)
        {
          Vector3 point = {x, y, 0};
          double alpha = signed_triangle_area(point, point2, point3) / total_area; 
          double beta  = signed_triangle_area(point, point3, point1) / total_area; 
          double gamma = signed_triangle_area(point, point1, point2) / total_area;
          
          if (alpha < 0 || beta < 0 || gamma < 0)
            continue;

          unsigned char z = static_cast<unsigned char>(alpha * point1.c[Z] + beta * point2.c[Z] + gamma * point3.c[Z]);
          if (z <= zbuffer.get(x, y)[0])
            continue;
          
          zbuffer.set(x, y, {z});  
          framebuffer.set(x, y, color);
        }
    }
}
