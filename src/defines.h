#ifndef DEFINES_H
#define DEFINES_H

#include <cmath>
#include "mathlib.h"
#include "model.h"
#include "tgaimage.h"

constexpr int width  = 1080;			  
constexpr int height = 1080;

constexpr TGAColor white   = {255, 255, 255, 255}; // attention, BGRA order
constexpr TGAColor green   = {  0, 255,   0, 255};
constexpr TGAColor red     = {  0,   0, 255, 255};
constexpr TGAColor blue    = {255, 128,  64, 255};
constexpr TGAColor yellow  = {  0, 200, 255, 255};
constexpr TGAColor pink    = {201, 145, 228, 255};
constexpr TGAColor navy    = { 61,  23,  21, 255};
constexpr TGAColor purple  = {152,  37, 152, 255};
constexpr TGAColor grey    = {233, 233, 241, 255};

void draw_line(int x1, int y1, int x2, int y2, TGAImage &framebuffer, TGAColor color);
void draw_line(Point start_point, Point end_point, TGAImage &framebuffer, TGAColor color);
void draw_line(Point2f start_point, Point2f end_point, TGAImage &framebuffer, TGAColor color);
void draw_line(Line line, TGAImage &framebuffer, TGAColor color);

void draw_triangle(Point point1, Point point2, Point point3, TGAImage &framebuffer, TGAColor color);

float point_ndc_x(float point);
float point_ndc_y(float point);

Point2f screen(const Point2f &point); 
Point2f project_screen(const Point3f &point3f);
Point3f translate_z(Point3f &point3f, float dz); 

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

void draw_line(Point start_point, Point end_point, TGAImage &framebuffer, TGAColor color)
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

void draw_line(Point2f start_point, Point2f end_point, TGAImage &framebuffer, TGAColor color)
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

  float y = start_point.y;
  float slope = (end_point.y - start_point.y) / (end_point.x - start_point.x); 
  for (float x = start_point.x; x < end_point.x; x++)
    {
      if (steep)
	framebuffer.set((int)std::round(y), (int)std::round(x), color);
      else 
	framebuffer.set((int)std::round(x), (int)std::round(y), color);
	
      y += slope; 
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

void draw_triangle(Point point1, Point point2, Point point3,
		   TGAImage &framebuffer, TGAColor color)
{  
  draw_line(point1, point2, framebuffer, color);
  draw_line(point2, point3, framebuffer, color);
  draw_line(point1, point3, framebuffer, color);
}

void draw_triangle(Point2f point1, Point2f point2, Point2f point3,
		   TGAImage &framebuffer, TGAColor color)
{  
  draw_line(point1, point2, framebuffer, color);
  draw_line(point2, point3, framebuffer, color);
  draw_line(point1, point3, framebuffer, color);
}

float point_ndc_x(float point)
{
  float ndc_x = point * 2 / width - 1;
  return ndc_x;
}

float point_ndc_y(float point)
{
  float ndc_y = 1 - 2 * point / height;
  return ndc_y;
}

Point2f screen(const Point2f &point)
{
  // -1..1 => (after added 1) 0..2 => (divided 2) 0..1 => (multiplied width or height)0..w/h 

  return
    {
      (point.x + 1) / 2 * width,
      ((point.y + 1) / 2) * height
    }; 
}

Point2f screen(const Point3f &point)
{
  // -1..1 => (after added 1) 0..2 => (divided 2) 0..1 => (multiplied width or height)0..w/h 

  return
    {
      (point.x + 1) / 2 * width,
      ((point.y + 1) / 2) * height
    }; 
}


Point3f vector_to_point(Vector3f &vector3f)
{
  Point3f point;
  point.x = vector3f.x;
  point.y = vector3f.y;
  point.z = vector3f.z;

  return point; 
}

Point2f vector_to_point(Vector2f &vector2f)
{
  Point2f point;
  point.x = vector2f.x;
  point.y = vector2f.y;

  return point; 
}
 
Vector2f project_screen(const Vector3f &vector3f)
{
  return
    {
      vector3f.x / vector3f.z,
      vector3f.y / vector3f.z
    }; 
}

Point2f project_screen(const Point3f &point3f)
{
  return
    {
      point3f.x / point3f.z,
      point3f.y / point3f.z
    }; 
}

Point3f translate_z(Point3f &point3f, float dz)
{
  point3f.z += dz;
  return point3f; 
}

// screen => project => translate_z

void render_model(ModelBuffer& buffer, TGAImage &framebuffer, TGAColor color)
{
  for (int i = 0; i < buffer.face_count; i++)
    {
      Vector3i face = buffer.faces[i];

      Point2f vertex0 = screen(vector_to_point(buffer.vertices[face.x]));   
      Point2f vertex1 = screen(vector_to_point(buffer.vertices[face.y]));   
      Point2f vertex2 =	screen(vector_to_point(buffer.vertices[face.z]));   
      
      draw_line(vertex0, vertex1, framebuffer, color);
      draw_line(vertex1, vertex2, framebuffer, color);
      draw_line(vertex2, vertex0, framebuffer, color);
    }
}

#endif
