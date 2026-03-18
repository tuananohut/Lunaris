#include "mathlib.h"

Vector2 vec2(i32 x, i32 y)
{
  Vector2 v = {{ x, y }}; 
  return v;
}

Vector2 vec2s(i32 x)
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

Vector2 vec2_mul_scalar(Vector2 a, i32 s)
{
  for (size_t i = 0; i < 2; ++i)
    a.c[i] *= s;
  
  return a;
}

Vector2 vec2_div(Vector2 a, Vector2 b)
{
  for (size_t i = 0; i < 2; ++i)
      a.c[i] /= b.c[i];
  
  return a;
} 

Vector2 vec2_div_scalar(Vector2 a, i32 s)
{
  s = 1.f / s; 
  for (size_t i = 0; i < 2; ++i)
    a.c[i] *= s;
  
  return a;
}

Vector2 vec2_normalize(const Vector2 a)
{
  return vec2_div_scalar(a, vec2_magnitude(a));
}

i32 vec2_dot(Vector2 a, Vector2 b)
{
    return a.c[X] * b.c[X] +
           a.c[Y] * b.c[Y];
}

f64 vec2_magnitude(const Vector2 a)
{
  return std::sqrt(a.c[X] * a.c[X] + a.c[Y] * a.c[Y]); 
}

f64 cross_product(Vector2 a, Vector2 b)
{
  return (a.c[X] * b.c[Y]) - (a.c[Y] * b.c[X]);
}

f64 signed_triangle_area(Vector2 a, Vector2 b, Vector2 c)
{
  Vector2 ab = { b.c[X] - a.c[X], b.c[Y] - a.c[Y] };
  Vector2 ac = { c.c[X] - a.c[X], c.c[Y] - a.c[Y] };
  return .5 * cross_product(ab, ac); 
};

///////////////////////////////////////////////////////////

Vector3 vec3(i32 x, i32 y, i32 z)
{
  Vector3 v = {{ x, y, z }}; 
  return v;
}

Vector3 vec3s(i32 x)
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

Vector3 vec3_mul_scalar(Vector3 a, i32 s)
{
  for (size_t i = 0; i < 3; ++i)
    a.c[i] *= s;
  
  return a;
}

Vector3 vec3_div(Vector3 a, Vector3 b)
{
  for (size_t i = 0; i < 3; ++i)
      a.c[i] /= b.c[i];
  
  return a;
}

Vector3 vec3_div_scalar(Vector3 a, i32 s)
{
  s = 1.f / s; 
  for (size_t i = 0; i < 3; ++i)
    a.c[i] *= s;
  
  return a;
}

Vector3 vec3_normalize(const Vector3 a)
{
  return vec3_div_scalar(a, vec3_magnitude(a));
}

i32 vec3_dot(Vector3 a, Vector3 b)
{
    return a.c[X] * b.c[X] +
           a.c[Y] * b.c[Y] +
           a.c[Z] * b.c[Z];
}

f64 vec3_magnitude(const Vector3 a)
{
  return std::sqrt(a.c[X] * a.c[X] +
                   a.c[Y] * a.c[Y] +
                   a.c[Z] * a.c[Z]); 
}

f64 signed_triangle_area(Vector3 a, Vector3 b, Vector3 c)
{
  Vector2 ab = { b.c[X] - a.c[X], b.c[Y] - a.c[Y] };
  Vector2 ac = { c.c[X] - a.c[X], c.c[Y] - a.c[Y] };
  return .5 * cross_product(ab, ac); 
}

///////////////////////////////////////////////////////////

Vector3f vec3f(f64 x, f64 y, f64 z)
{
  Vector3f v = {{ x, y, z }}; 
  return v;
}

Vector3f vec3fs(f64 x)
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

Vector3f vec3f_mul_scalar(Vector3f a, f64 s)
{
  for (size_t i = 0; i < 3; ++i)
    a.c[i] *= s;
  
  return a;
}

Vector3f vec3f_div(Vector3f a, Vector3f b)
{
  for (size_t i = 0; i < 3; ++i)
      a.c[i] /= b.c[i];
  
  return a;
}

Vector3f vec3f_div_scalar(Vector3f a,f64 s)
{
  s = 1.f / s; 
  for (size_t i = 0; i < 3; ++i)
    a.c[i] *= s;
  
  return a;
}

Vector3f vec3f_normalize(const Vector3f a)
{
  return vec3f_div_scalar(a, vec3f_magnitude(a));
}

f64 vec3f_dot(Vector3f a, Vector3f b)
{
    return a.c[X]*b.c[X] +
           a.c[Y]*b.c[Y] +
           a.c[Z]*b.c[Z];
}

f64 vec3f_magnitude(const Vector3f a)
{
  return std::sqrt(a.c[X] * a.c[X] +
                   a.c[Y] * a.c[Y] +
                   a.c[Z] * a.c[Z]); 
}

///////////////////////////////////////////////////////////

Vector4 vec4(i32 x, i32 y, i32 z, i32 w)
{
  Vector4 v = {{ x, y, z, w }}; 
  return v;
}

Vector4 vec4s(i32 x)
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

Vector4 vec4_mul_scalar(Vector4 a, i32 s)
{
  for (size_t i = 0; i < 4; ++i)
    a.c[i] *= s;
  
  return a;
}

Vector4 vec4_div(Vector4 a, Vector4 b)
{
  for (size_t i = 0; i < 4; ++i)
      a.c[i] /= b.c[i];
  
  return a;
}

Vector4 vec4_div_scalar(Vector4 a, i32 s)
{
  s = 1.f / s; 
  for (size_t i = 0; i < 4; ++i)
    a.c[i] *= s;
  
  return a;
}

Vector4 vec4_normalize(const Vector4 a)
{
  return vec4_div_scalar(a, vec4_magnitude(a));
}

Vector4 mul_vec4(Matrix m, Vector4 v)
{
  Vector4 r;

  r.c[X] = m.m[0][0]*v.c[X] + m.m[0][1]*v.c[Y] + m.m[0][2]*v.c[Z] + m.m[0][3]*v.c[W];
  r.c[Y] = m.m[1][0]*v.c[X] + m.m[1][1]*v.c[Y] + m.m[1][2]*v.c[Z] + m.m[1][3]*v.c[W];
  r.c[Z] = m.m[2][0]*v.c[X] + m.m[2][1]*v.c[Y] + m.m[2][2]*v.c[Z] + m.m[2][3]*v.c[W];
  r.c[W] = m.m[3][0]*v.c[X] + m.m[3][1]*v.c[Y] + m.m[3][2]*v.c[Z] + m.m[3][3]*v.c[W];

  return r;
}

i32 vec4_dot(Vector4 a, Vector4 b)
{
    return a.c[X] * b.c[X] +
           a.c[Y] * b.c[Y] +
           a.c[Z] * b.c[Z] +
           a.c[W] * b.c[W];
}

f64 vec4_magnitude(const Vector4 a)
{
  return std::sqrt(a.c[X] * a.c[X] +
                   a.c[Y] * a.c[Y] +
                   a.c[Z] * a.c[Z] +
                   a.c[W] * a.c[W]); 
}

///////////////////////////////////////////////////////////

Matrix matrix_identity()
{
  Matrix matrix
    {
      {
        { 1.0, 0.0, 0.0, 0.0 },
        { 0.0, 1.0, 0.0, 0.0 },
        { 0.0, 0.0, 1.0, 0.0 },
        { 0.0, 0.0, 0.0, 1.0 }
      }
    };
  
  return matrix; 
}

Matrix matrix_rotation_x(f64 t)
{
  f64 c = std::cos(t);
  f64 s = std::sin(t);

  Matrix matrix
    {
      {
        1.0, 0.0, 0.0,
        0.0,   c,  -s,
        0.0,   s,   c, 
      }
    };

  return matrix; 
}

Matrix matrix_rotation_y(f64 t)
{
  t = ; 
  f64 c = std::cos(t);
  f64 s = std::sin(t);

  Matrix matrix
    {
      {
          c, 0.0,   s,
        0.0, 1.0, 0.0,
         -s, 0.0,   c, 
      }
    };

  return matrix; 
}

Matrix matrix_rotation_z(f64 t)
{
  f64 c = std::cos(t);
  f64 s = std::sin(t);

  Matrix matrix
    {
      {
          c,  -s, 0.0,
          s,   c, 0.0,
        0.0, 0.0, 1.0, 
      }
    };

  return matrix; 
} 
