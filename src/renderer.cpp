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

void draw_line(Vector2 start_point, Vector2 end_point, TGAImage &framebuffer, TGAColor color)
{
  bool steep = std::abs(start_point.x - end_point.x) < std::abs(start_point.y - end_point.y);
  if (steep)
    {
      std::swap(start_point.x, start_point.y);
      std::swap(end_point.x, end_point.y); 
    }
  
  if (start_point.x > end_point.x)
    {
      std::swap(start_point.x, end_point.x);
      std::swap(start_point.y, end_point.y); 
    }

  int y = start_point.y;
  int ierror = 0; 
  for (int x = start_point.x; x < end_point.x; x++)
    {
      if (steep)
	framebuffer.set(y, x, color);
      else 
	framebuffer.set(x, y, color);

      ierror += 2 * std::abs(end_point.y - start_point.y); 
	
      y += (end_point.y > start_point.y ? 1 : -1) * (ierror > (end_point.x - start_point.x)); // Up or down ? 
      ierror -= 2 * (end_point.x - start_point.x) * (ierror > (end_point.x - start_point.x)); 
    }	
} 

void draw_line(Line line, TGAImage &framebuffer, TGAColor color)
{
  bool steep = std::abs(line.start_point.x - line.end_point.x) < std::abs(line.start_point.y - line.end_point.y);
  if (steep)
    {
      std::swap(line.start_point.x, line.start_point.y);
      std::swap(line.end_point.x,   line.end_point.y); 
    }
  
  if (line.start_point.x > line.end_point.x)
    {
      std::swap(line.start_point.x, line.end_point.x);
      std::swap(line.start_point.y, line.end_point.y); 
    }

  int y = line.start_point.y;
  int ierror = 0; 
  for (int x = line.start_point.x; x < line.end_point.x; x++)
    {
      if (steep)
	framebuffer.set(y, x, color);
      else 
	framebuffer.set(x, y, color);

      ierror += 2 * std::abs(line.end_point.y - line.start_point.y); 
	
      y += (line.end_point.y > line.start_point.y ? 1 : -1) * (ierror > (line.end_point.x - line.start_point.x)); // Up or down ? 
      ierror -= 2 * (line.end_point.x - line.start_point.x) * (ierror > (line.end_point.x - line.start_point.x)); 
    }	
}



void draw_triangle(Vector2 point1, Vector2 point2, Vector2 point3,
		   TGAImage &framebuffer, TGAColor color)
{  
  draw_line(point1, point2, framebuffer, color);
  draw_line(point2, point3, framebuffer, color);
  draw_line(point1, point3, framebuffer, color);
}



Vector2 screen(const Vector3f &point)
{
  // -1..1 => (after added 1) 0..2 => (divided 2) 0..1 => (multiplied width or height)0..w/h 

  return
    {
      static_cast<int>((point.x + 1.) / 2 * width),
      static_cast<int>((point.y + 1.) / 2 * height)
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

      Vector2 vertex0 = screen(buffer.vertices[face.x]);   
      Vector2 vertex1 = screen(buffer.vertices[face.y]);   
      Vector2 vertex2 =	screen(buffer.vertices[face.z]);   

      draw_triangle(vertex0, vertex1, vertex2, framebuffer, color); 
    }
}
