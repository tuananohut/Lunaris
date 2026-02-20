#ifndef MATHLIB_H
#define MATHLIB_H

struct Point
{
  int x;
  int y; 
};

struct Point2f
{
  float x;
  float y; 
};

struct Point3f
{
  float x;
  float y; 
  float z; 
};

struct Vector2f
{
  float x;
  float y;

  Vector2f() {}
  
Vector2f(float _x, float _y) :
  x(_x), y(_y) {} 
};

struct Vector3f
{
  float x;
  float y;
  float z;

  Vector3f() {}
  
Vector3f(float _x, float _y, float _z) :
  x(_x), y(_y), z(_z) {} 
};

struct Vector3i
{
  int x;
  int y;
  int z;

  Vector3i() {}

Vector3i(int _x, int _y, int _z) :
  x(_x), y(_y), z(_z) {} 
};

struct Line
{
  Point start_point;
  Point end_point; 
}; 

#endif
