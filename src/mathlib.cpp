#include "mathlib.h"

Vector2 vec2(int x, int y)
{
  Vector2 v = {{ x, y }}; 
  return v;
}

Vector2 vec2s(int x)
{
  return vec2(x, x); 
}

Vector2 vec2_add(Vector2 a, Vector2 b)
{
  for (size_t i = 0; i < 2; ++i)
      a.c[i] += b.c[i];
  
  return a;
}

Vector2 vec2_sub(Vector2 a, Vector2 b)
{
  for (size_t i = 0; i < 2; ++i)
      a.c[i] -= b.c[i];
  
  return a;
}

Vector2 vec2_mul(Vector2 a, Vector2 b)
{
  for (size_t i = 0; i < 2; ++i)
      a.c[i] *= b.c[i];
  
  return a;
}

Vector2 vec2_div(Vector2 a, Vector2 b)
{
  for (size_t i = 0; i < 2; ++i)
      a.c[i] /= b.c[i];
  
  return a;
}

int vec2_dot(Vector2 a, Vector2 b)
{
    return a.c[X] * b.c[X] +
           a.c[Y] * b.c[Y];
}

double cross_product(Vector2 a, Vector2 b)
{
  return (a.c[X] * b.c[Y]) - (a.c[Y] * b.c[X]);
}

double signed_triangle_area(Vector2 a, Vector2 b, Vector2 c)
{
  Vector2 ab = { b.c[X] - a.c[X], b.c[Y] - a.c[Y] };
  Vector2 ac = { c.c[X] - a.c[X], c.c[Y] - a.c[Y] };
  return .5 * cross_product(ab, ac); 
};

///////////////////////////////////////////////////////////

Vector3 vec3(int x, int y, int z)
{
  Vector3 v = {{ x, y, z }}; 
  return v;
}

Vector3 vec3s(int x)
{
  return vec3(x, x, x); 
}

Vector3 vec3_add(Vector3 a, Vector3 b)
{
  for (size_t i = 0; i < 3; ++i)
      a.c[i] += b.c[i];
  
  return a;
}

Vector3 vec3_sub(Vector3 a, Vector3 b)
{
  for (size_t i = 0; i < 3; ++i)
      a.c[i] -= b.c[i];
  
  return a;
}

Vector3 vec3_mul(Vector3 a, Vector3 b)
{
  for (size_t i = 0; i < 3; ++i)
      a.c[i] *= b.c[i];
  
  return a;
}

Vector3 vec3_div(Vector3 a, Vector3 b)
{
  for (size_t i = 0; i < 3; ++i)
      a.c[i] /= b.c[i];
  
  return a;
}

int vec3_dot(Vector3 a, Vector3 b)
{
    return a.c[X] * b.c[X] +
           a.c[Y] * b.c[Y] +
           a.c[Z] * b.c[Z];
}

double signed_triangle_area(Vector3 a, Vector3 b, Vector3 c)
{
  Vector2 ab = { b.c[X] - a.c[X], b.c[Y] - a.c[Y] };
  Vector2 ac = { c.c[X] - a.c[X], c.c[Y] - a.c[Y] };
  return .5 * cross_product(ab, ac); 
}

///////////////////////////////////////////////////////////

Vector3f vec3f(double x, double y, double z)
{
  Vector3f v = {{ x, y, z }}; 
  return v;
}

Vector3f vec3fs(double x)
{
  return vec3f(x, x, x); 
}

Vector3f vec3f_add(Vector3f a, Vector3f b)
{
  for (size_t i = 0; i < 3; ++i)
      a.c[i] += b.c[i];
  
  return a;
}

Vector3f vec3f_sub(Vector3f a, Vector3f b)
{
  for (size_t i = 0; i < 3; ++i)
      a.c[i] -= b.c[i];
  
  return a;
}

Vector3f vec3f_mul(Vector3f a, Vector3f b)
{
  for (size_t i = 0; i < 3; ++i)
      a.c[i] *= b.c[i];
  
  return a;
}

Vector3f vec3f_div(Vector3f a, Vector3f b)
{
  for (size_t i = 0; i < 3; ++i)
      a.c[i] /= b.c[i];
  
  return a;
}

double vec3f_dot(Vector3f a, Vector3f b)
{
    return a.c[X]*b.c[X] +
           a.c[Y]*b.c[Y] +
           a.c[Z]*b.c[Z];
}

///////////////////////////////////////////////////////////


Vector4 vec4(int x, int y, int z, int w)
{
  Vector4 v = {{ x, y, z, w }}; 
  return v;
}

Vector4 vec4s(int x)
{
  return vec4(x, x, x, x); 
}

Vector4 vec4_add(Vector4 a, Vector4 b)
{
  for (size_t i = 0; i < 4; ++i)
      a.c[i] += b.c[i];
  
  return a;
}

Vector4 vec4_sub(Vector4 a, Vector4 b)
{
  for (size_t i = 0; i < 4; ++i)
      a.c[i] -= b.c[i];
  
  return a;
}

Vector4 vec4_mul(Vector4 a, Vector4 b)
{
  for (size_t i = 0; i < 4; ++i)
      a.c[i] *= b.c[i];
  
  return a;
}

Vector4 vec4_div(Vector4 a, Vector4 b)
{
  for (size_t i = 0; i < 4; ++i)
      a.c[i] /= b.c[i];
  
  return a;
}

int vec4_dot(Vector4 a, Vector4 b)
{
    return a.c[X] * b.c[X] +
           a.c[Y] * b.c[Y] +
           a.c[Z] * b.c[Z] +
           a.c[W] * b.c[W];
}
