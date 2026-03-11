#ifndef MATHLIB_H
#define MATHLIB_H

struct Vector2 { int c[2]; };
struct Vector3 { int c[3]; };
struct Vector4 { int c[4]; };

struct Vector3f { double c[3]; };
struct Line { Vector2 p[2]; };

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

#endif
