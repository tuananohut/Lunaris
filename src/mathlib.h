#ifndef MATHLIB_H
#define MATHLIB_H

struct Vector2
{
  int x;
  int y;

  Vector2() {}
  
Vector2(int _x, int _y) :
  x(_x), y(_y) {} 
};

struct Vector3
{
  int x;
  int y;
  int z;

  Vector3() {}

Vector3(int _x, int _y, int _z) :
  x(_x), y(_y), z(_z) {} 
};

struct Vector3f
{
  double x;
  double y;
  double z;

  Vector3f() {}

Vector3f(double _x, double _y, double _z) :
  x(_x), y(_y), z(_z) {} 
};

struct Line
{
  Vector2 start_point;
  Vector2 end_point; 
}; 

#endif
