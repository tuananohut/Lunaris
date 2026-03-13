#include "renderer.h"

void draw_line(int x1, int y1, int x2, int y2, TGAImage &framebuffer, TGAColor color)
{
  bool steep = std::abs(x1 - x2) < std::abs(y1 - y2);
  if (steep)
    {
      std::swap(x1, y1);
      std::swap(x2, y2); 
    }
  
  if (x1 > x2)
    {
      std::swap(x1, x2);
      std::swap(y1, y2); 
    }

  int y = y1;
  int ierror = 0; 
  for (int x = x1; x < x2; x++)
    {
      if (steep)
        framebuffer.set(y, x, color);
      else 
        framebuffer.set(x, y, color);

      ierror += 2 * std::abs(y2 - y1); 
      y += (y2 > y1 ? 1 : -1) * (ierror > (x2 - x1)); // Up or down ? 
      ierror -= 2 * (x2 - x1) * (ierror > (x2 - x1)); 
    }	
} 

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

void draw_line(Line line, TGAImage &framebuffer, TGAColor color)
{
  bool steep = std::abs(line.p.c[X] - line.p1.c[X]) < std::abs(line.p0.c[Y] - line.p1.c[Y]);
  if (steep)
    {
      std::swap(line.p0.c[X], line.p0.c[Y]);
      std::swap(line.p1.c[X], line.p1.c[Y]); 
    }
  
  if (line.p0.c[X] > line.p1.c[X])
    {
      std::swap(line.p0.c[X], line.p1.c[X]);
      std::swap(line.p0.c[Y], line.p1.c[Y]); 
    }

  int y = line.p0.c[Y];
  int ierror = 0; 
  for (int x = line.p0.c[X]; x < line.p1.c[X]; x++)
    {
      if (steep)
        framebuffer.set(y, x, color);
      else 
        framebuffer.set(x, y, color);

      ierror += 2 * std::abs(line.p1.c[Y] - line.p0.c[Y]); 
	
      y += (line.p1.c[Y] > line.p0.c[Y] ? 1 : -1) * (ierror > (line.p1.c[X] - line.p0.c[X])); // Up or down ? 
      ierror -= 2 * (line.p1.c[X] - line.p0.c[X]) * (ierror > (line.p1.c[X] - line.p0.c[X])); 
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
      static_cast<int>((point.x + 1.) / 2 * width),
      static_cast<int>((point.y + 1.) / 2 * height),
      static_cast<int>((point.z + 1.) * 255./2)
    }; 
}



Vector3f translate_z(Vector3f &point3f, float dz)
{
  point3f.z += dz;
  return point3f; 
}

// screen => project => translate_z



void render_model(ModelBuffer& buffer, TGAImage &framebuffer, TGAColor color)
{
  for (int i = 0; i < buffer.face_count; i++)
    {
      Vector3 face = buffer.faces[i];

      Vector3 vertex0_ = screen(buffer.vertices[face.x]);   
      Vector3 vertex1_ = screen(buffer.vertices[face.y]);   
      Vector3 vertex2_ = screen(buffer.vertices[face.z]);   

      Vector2 vertex0 = {vertex0_.x, vertex0_.y};
      Vector2 vertex1 = {vertex1_.x, vertex1_.y};
      Vector2 vertex2 = {vertex2_.x, vertex2_.y};

      draw_triangle(vertex0, vertex1, vertex2, framebuffer, color); 
    }
}


void scanline_rendering(Vector2 point1, Vector2 point2, Vector2 point3,
                        TGAImage &framebuffer, TGAColor color)
{
  if (point2.y > point3.y)
    {
      std::swap(point2.y, point3.y);
      std::swap(point2.x, point3.x); 
    }

  if (point1.y > point3.y)
    {
      std::swap(point1.y, point3.y);
      std::swap(point1.x, point3.x); 
    }

  if (point1.y > point2.y)
    {
      std::swap(point1.y, point2.y);
      std::swap(point1.x, point2.x);
    }

  int total_height = point3.y - point1.y;

  if (point1.y != point2.y)
    {
      int segment_height = point2.y - point1.y;
      for (int y = point1.y; y <= point2.y; y++)
        {
          int x1 = point1.x + ((point3.x - point1.x) * (y - point1.y)) / total_height; 
          int x2 = point1.x + ((point2.x - point1.x) * (y - point1.y)) / segment_height;
          for (int x = std::min(x1, x2); x < std::max(x1, x2); x++)
            {
              framebuffer.set(x, y, color);
            }
        }
    }

  if (point2.y != point3.y)
    {
      int segment_height = point3.y - point2.y;
      for (int y = point2.y; y <= point3.y; y++)
        {
          int x1 = point1.x + ((point3.x - point1.x) * (y - point1.y)) / total_height; 
          int x2 = point2.x + ((point3.x - point2.x) * (y - point2.y)) / segment_height;
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

      Vector3 vertex0 = screen(buffer.vertices[face.x]);   
      Vector3 vertex1 = screen(buffer.vertices[face.y]);   
      Vector3 vertex2 =	screen(buffer.vertices[face.z]);

      TGAColor rnd;
      for (int c = 0; c < 3; c++)
        rnd[c] = std::rand()%255;

      fill_triangle(vertex0, vertex1, vertex2, framebuffer, zbuffer, rnd); 
    }
}


double signed_triangle_area(Vector2 point1, Vector2 point2, Vector2 point3)
{
  return .5 * ((point2.y - point1.y)*(point2.x + point1.x) +
               (point3.y - point2.y)*(point3.x + point2.x) +
               (point1.y - point3.y)*(point1.x + point3.x));
}

double signed_triangle_area(Vector3 point1, Vector3 point2, Vector3 point3)
{
  return .5 * ((point2.y - point1.y)*(point2.x + point1.x) +
               (point3.y - point2.y)*(point3.x + point2.x) +
               (point1.y - point3.y)*(point1.x + point3.x));
}

void fill_triangle(Vector2 point1, Vector2 point2, Vector2 point3,
                   TGAImage &framebuffer, TGAColor color)
{
  int bbminx = std::min(std::min(point1.x, point2.x), point3.x); 
  int bbminy = std::min(std::min(point1.y, point2.y), point3.y);
  int bbmaxx = std::max(std::max(point1.x, point2.x), point3.x);
  int bbmaxy = std::max(std::max(point1.y, point2.y), point3.y); 
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
  int bbminx = std::min(std::min(point1.x, point2.x), point3.x); 
  int bbminy = std::min(std::min(point1.y, point2.y), point3.y);
  int bbmaxx = std::max(std::max(point1.x, point2.x), point3.x);
  int bbmaxy = std::max(std::max(point1.y, point2.y), point3.y);

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

          unsigned char z = static_cast<unsigned char>(alpha * point1.z + beta * point2.z + gamma * point3.z);
          if (z <= zbuffer.get(x, y)[0])
            continue;
          
          zbuffer.set(x, y, {z});  
          framebuffer.set(x, y, color);
        }
    }
}


void fill_triangle(Vector3 point1, Vector3 point2, Vector3 point3,
                   Vector3 colorA, Vector3 colorB, Vector3 colorC, 
                   TGAImage &framebuffer)
{
  TGAColor color; 
  
  int bbminx = std::min(std::min(point1.x, point2.x), point3.x); 
  int bbminy = std::min(std::min(point1.y, point2.y), point3.y);
  int bbmaxx = std::max(std::max(point1.x, point2.x), point3.x);
  int bbmaxy = std::max(std::max(point1.y, point2.y), point3.y);

  bbminx = std::max(0, bbminx);
  bbmaxx = std::min(width-1, bbmaxx);
  bbminy = std::max(0, bbminy);
  bbmaxy = std::min(height-1, bbmaxy);
  
  double total_area = signed_triangle_area(point1, point2, point3);
  if (total_area < 1)
    return; // backface culling + discarding triangles that cover less than a pixel
  
  int z = 0; 
#pragma omp parallel for
  for (int y = bbminy; y <= bbmaxy; y++)
    {
      for (int x = bbminx; x <= bbmaxx; x++)
        {
          Vector3 point = {x, y, z};
          double alpha = signed_triangle_area(point, point2, point3) / total_area; 
          double beta  = signed_triangle_area(point, point3, point1) / total_area; 
          double gamma = signed_triangle_area(point, point1, point2) / total_area; 

          if (alpha < 0 || beta < 0 || gamma < 0)
            continue;
          
          color[0] = static_cast<unsigned char>(alpha * colorA.x + beta * colorB.x + gamma * colorC.x);
          color[1] = static_cast<unsigned char>(alpha * colorA.y + beta * colorB.y + gamma * colorC.y);
          color[2] = static_cast<unsigned char>(alpha * colorA.z + beta * colorB.z + gamma * colorC.z);
            
          framebuffer.set(x, y, color);
        }
    }
}
