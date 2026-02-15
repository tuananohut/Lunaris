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

  float y = start_point.y; 
  for (int x = start_point.x; x < end_point.x; x++)
    {
      if (steep)
	framebuffer.set(y, x, color);
      else 
	framebuffer.set(x, y, color);

      y += (end_point.y - start_point.y) / float(end_point.x - start_point.x); 
    }
} 

#endif
