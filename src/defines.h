#ifndef DEFINES_H
#define DEFINES_H

#include <cmath>
#include "tgaimage.h"

constexpr TGAColor white   = {255, 255, 255, 255}; // attention, BGRA order
constexpr TGAColor green   = {  0, 255,   0, 255};
constexpr TGAColor red     = {  0,   0, 255, 255};
constexpr TGAColor blue    = {255, 128,  64, 255};
constexpr TGAColor yellow  = {  0, 200, 255, 255};
constexpr TGAColor pink    = {201, 145, 228, 255};
constexpr TGAColor navy    = { 61,  23,  21, 255};
constexpr TGAColor purple  = {152,  37, 152, 255};
constexpr TGAColor grey    = {233, 233, 241, 255};

struct Point
{
  int x;
  int y; 
};

struct Line
{
  Point start_point;
  Point end_point; 
}; 

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
  float error = 0.f;
  float slope = std::abs(end_point.y - start_point.y) / static_cast<float>(end_point.x - start_point.x);  
  for (int x = start_point.x; x < end_point.x; x++)
    {
      if (steep)
	framebuffer.set(y, x, color);
      else 
	framebuffer.set(x, y, color);

      error += slope;
      if (error > .5)
	{
	  y += end_point.y > start_point.y ? 1 : -1;
	  error -= 1.f; 
	}
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
  float error = 0.f;
  float slope = std::abs(line.end_point.y - line.start_point.y) / static_cast<float>(line.end_point.x - line.start_point.x);  
  for (int x = line.start_point.x; x < line.end_point.x; x++)
    {
      if (steep)
	framebuffer.set(y, x, color);
      else 
	framebuffer.set(x, y, color);

      error += slope;
      if (error > .5)
	{
	  y += line.end_point.y > line.start_point.y ? 1 : -1;
	  error -= 1.f; 
	}
    }

} 

#endif
