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

bool object_to_render(char *filename)
{
  assert(filename);
  
  FILE* file = fopen(filename, "r");
  if (!file)
    return false;

  XMFLOAT3 positions[14700];
  XMFLOAT3 normals[14700];
  XMFLOAT2 texcoords[14700];
  
  int posCount = 0;
  int normalCount = 0;
  int texCount = 0;

  char line[15000];

  while (fgets(line, sizeof(line), file))
    {
      if (line[0] == 'v' && line[1] == ' ')
	{
	  float x, y, z;
	  float tx, ty; 
	  float nx, ny, nz;
	  int read = sscanf(line, "v %f %f %f %f %f %f %f %f",
			    &x, &y, &z, &tx, &ty, &nx, &ny, &nz);
	  
	  if (read == 8)
	    {
	      positions[posCount++] = XMFLOAT3(x, y, z);	    
	      normals[normalCount++] = XMFLOAT3(nx, ny, nz); 
	      texcoords[texCount++] = XMFLOAT2(tx, ty); 	    
	    }
	}
    }

  fclose(file);

  if (posCount == 0 || posCount != normalCount)
    return false;

  vertexCount = posCount;
  indexCount  = Buffer->vertexCount;

  vertices = new HemisphericVertex[Buffer->vertexCount];
  indices  = new uint32_t[Buffer->indexCount];

  for (int i = 0; i < posCount; ++i)
    {
      Buffer->vertices[i].position = positions[i];
      Buffer->vertices[i].normal   = normals[i];
      Buffer->vertices[i].texture  = texcoords[i];

      Buffer->indices[i] = i;
    }

  return true;

}

#endif
