#ifndef DEFINES_H
#define DEFINES_H

#include <cmath>
#include "mathlib.h"
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

#endif
