#ifndef MATHLIB_H
#define MATHLIB_H

#if !defined(ML_VECTOR2_TYPE)
struct Vector2
{
  int x;
  int y;

  Vector2() {}
  
Vector2(int _x, int _y) :
  x(_x), y(_y) {} 
};
#define ML_VECTOR2_TYPE
#endif

#if !defined(ML_VECTOR3_TYPE)
struct Vector3
{
  int x;
  int y;
  int z;

  Vector3() {}

Vector3(int _x, int _y, int _z) :
  x(_x), y(_y), z(_z) {} 
};
#define ML_VECTOR3_TYPE
#endif

#if !defined(ML_VECTOR3F_TYPE)
struct Vector3f
{
  double x;
  double y;
  double z;

  Vector3f() {}

Vector3f(double _x, double _y, double _z) :
  x(_x), y(_y), z(_z) {} 
};
#define ML_VECTOR3F_TYPE
#endif

#ifndef LINE_TYPE
#define LINE_TYPE
struct Line
{
  Vector2 start_point;
  Vector2 end_point; 
};
#endif

#endif
