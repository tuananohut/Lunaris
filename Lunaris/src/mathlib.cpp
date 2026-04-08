#include "../include/mathlib.h"

f64 cross_product(Vector2 a, Vector2 b)
{
  return (a.c[X] * b.c[Y]) - (a.c[Y] * b.c[X]);
}

///////////////////////////////////////////////////////////

Vector2 vec2(i32 x, i32 y)
{
  Vector2 v = {{ x, y }}; 
  return v;
}


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

Vector3 mul_vec3(Vector3 v)
{
  Matrix3D m = matrix3d_rotation_y(30); 
  Vector3 r;
  
  r.c[X] =  m.m[0]*v.c[X] + m.m[1]*v.c[Y] + m.m[2]*v.c[Z];
  r.c[Y] =  m.m[3]*v.c[X] + m.m[4]*v.c[Y] + m.m[5]*v.c[Z];
  r.c[Z] =  m.m[6]*v.c[X] + m.m[7]*v.c[Y] + m.m[8]*v.c[Z];

  return r;
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

Vector3f mul_vec3f(Matrix3D m, Vector3f v)
{
  Vector3f r;
  
  r.c[X] =  m.m[0]*v.c[X] + m.m[1]*v.c[Y] + m.m[2]*v.c[Z];
  r.c[Y] =  m.m[3]*v.c[X] + m.m[4]*v.c[Y] + m.m[5]*v.c[Z];
  r.c[Z] =  m.m[6]*v.c[X] + m.m[7]*v.c[Y] + m.m[8]*v.c[Z];

  return r;
}

Vector3f perspective(Vector3f v)
{
  constexpr f64 c = 3.0;
  return vec3f_div_scalar(v, (1 - v.c[Z] / c));
}

Vector3f cross_product(Vector3f a, Vector3f b)
{
  Vector3f result;

  result.c[X] = a.c[Y]*b.c[Z] - a.c[Z]*b.c[Y];  
  result.c[Y] = a.c[Z]*b.c[X] - a.c[X]*b.c[Z];
  result.c[Z] = a.c[X]*b.c[Y] - a.c[Y]*b.c[X]; 

  return result; 
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

Vector4 mul_vec4(Matrix4D m, Vector4 v)
{
  Vector4 r;
  
  r.c[X] =  m.m[0]*v.c[X]  +  m.m[1]*v.c[Y] +  m.m[2]*v.c[Z] +  m.m[3]*v.c[W];
  r.c[Y] =  m.m[4]*v.c[X]  +  m.m[5]*v.c[Y] +  m.m[6]*v.c[Z] +  m.m[7]*v.c[W];
  r.c[Z] =  m.m[8]*v.c[X]  +  m.m[9]*v.c[Y] + m.m[10]*v.c[Z] + m.m[11]*v.c[W];
  r.c[W] = m.m[12]*v.c[X]  + m.m[13]*v.c[Y] + m.m[14]*v.c[Z] + m.m[15]*v.c[W];

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

Matrix3D matrix3d(f32 n00, f32 n01, f32 n02, 
                  f32 n10, f32 n11, f32 n12, 
                  f32 n20, f32 n21, f32 n22)
{
  Matrix3D m
    {
      {
        n00, n01, n02,
        n10, n11, n12,
        n20, n21, n22,
      }
    };

  return m; 
}

Matrix3D matrix3d_identity()
{
  Matrix3D matrix
    {
      {
        1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0,
      }
    };
  
  return matrix; 
}

Matrix3D matrix3d_rotation_x(f64 t)
{
  f64 c = std::cos(t);
  f64 s = std::sin(t);

  Matrix3D matrix
    {
      {
        1.0, 0.0, 0.0,
        0.0,   c,  -s,
        0.0,   s,   c,
      }
    };

  return matrix; 
}

Matrix3D matrix3d_rotation_y(f64 t)
{
  // t = ; 
  f64 c = std::cos(t);
  f64 s = std::sin(t);

  Matrix3D matrix
    {
      {
          c, 0.0,   s,
        0.0, 1.0, 0.0,
         -s, 0.0,   c,
      }
    };

  return matrix; 
}

Matrix3D matrix3d_rotation_z(f64 t)
{
  f64 c = std::cos(t);
  f64 s = std::sin(t);

  Matrix3D matrix
    {
      {
          c,  -s, 0.0,
          s,   c, 0.0,
        0.0, 0.0, 1.0,
      }
    };

  return matrix; 
} 

Matrix3D matrix3d_multiply(const Matrix3D a, const Matrix3D b)
{
  Matrix3D result = Matrix3D{{0}};
  
  // Row 1
  result.m[0] = a.m[0]*b.m[0] + a.m[1]*b.m[3] + a.m[2]*b.m[6];
  result.m[1] = a.m[0]*b.m[1] + a.m[1]*b.m[4] + a.m[2]*b.m[7];
  result.m[2] = a.m[0]*b.m[2] + a.m[1]*b.m[5] + a.m[2]*b.m[8];

  // Row 2
  result.m[3] = a.m[3]*b.m[0] + a.m[4]*b.m[3] + a.m[5]*b.m[6];
  result.m[4] = a.m[3]*b.m[1] + a.m[4]*b.m[4] + a.m[5]*b.m[7];
  result.m[5] = a.m[3]*b.m[2] + a.m[4]*b.m[5] + a.m[5]*b.m[8];

  // Row 3
  result.m[6] = a.m[6]*b.m[0] + a.m[7]*b.m[3] + a.m[8]*b.m[6];
  result.m[7] = a.m[6]*b.m[1] + a.m[7]*b.m[4] + a.m[8]*b.m[7];
  result.m[8] = a.m[6]*b.m[2] + a.m[7]*b.m[5] + a.m[8]*b.m[8];

  return result; 
}


///////////////////////////////////////////////////////////

Matrix4D matrix4d(f32 n00, f32 n01, f32 n02, f32 n03, 
                  f32 n10, f32 n11, f32 n12, f32 n13, 
                  f32 n20, f32 n21, f32 n22, f32 n23, 
                  f32 n30, f32 n31, f32 n32, f32 n33)
{
  Matrix4D m
    {
      {
        n00, n01, n02, n03,
        n10, n11, n12, n13,
        n20, n21, n22, n23,
        n30, n31, n32, n33,
      }
    };

  return m; 
}

Matrix4D matrix4d_identity()
{
  Matrix4D matrix
    {
      {
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0,
      }
    };
  
  return matrix; 
}

Matrix4D matrix4d_rotation_x(f64 t)
{
  f64 c = std::cos(t);
  f64 s = std::sin(t);

  Matrix4D matrix
    {
      {
        1.0, 0.0, 0.0, 0.0,
        0.0,   c,  -s, 0.0,
        0.0,   s,   c, 0.0,
        0.0, 0.0, 0.0, 1.0,
      }
    };

  return matrix; 
}

Matrix4D matrix4d_rotation_y(f64 t)
{
  // t = ; 
  f64 c = std::cos(t);
  f64 s = std::sin(t);

  Matrix4D matrix
    {
      {
          c, 0.0,   s, 0.0,
        0.0, 1.0, 0.0, 0.0,
         -s, 0.0,   c, 0.0,
        0.0, 0.0, 0.0, 1.0,
      }
    };

  return matrix; 
}

Matrix4D matrix4d_rotation_z(f64 t)
{
  f64 c = std::cos(t);
  f64 s = std::sin(t);

  Matrix4D matrix
    {
      {
          c,  -s, 0.0, 0.0,
          s,   c, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0,
      }
    };

  return matrix; 
} 

Matrix4D matrix4d_multiply(const Matrix4D a, const Matrix4D b)
{
  Matrix4D result = Matrix4D{{0}};
  
  // Row 1
  result.m[0] = a.m[0]*b.m[0] + a.m[1]*b.m[4] + a.m[2]*b.m[8]  + a.m[3]*b.m[12];
  result.m[1] = a.m[0]*b.m[1] + a.m[1]*b.m[5] + a.m[2]*b.m[9]  + a.m[3]*b.m[13];
  result.m[2] = a.m[0]*b.m[2] + a.m[1]*b.m[6] + a.m[2]*b.m[10] + a.m[3]*b.m[14];
  result.m[3] = a.m[0]*b.m[3] + a.m[1]*b.m[7] + a.m[2]*b.m[11] + a.m[3]*b.m[15];

  // Row 2
  result.m[4] = a.m[4]*b.m[0] + a.m[5]*b.m[4] + a.m[6]*b.m[8]  + a.m[7]*b.m[12];
  result.m[5] = a.m[4]*b.m[1] + a.m[5]*b.m[5] + a.m[6]*b.m[9]  + a.m[7]*b.m[13];
  result.m[6] = a.m[4]*b.m[2] + a.m[5]*b.m[6] + a.m[6]*b.m[10] + a.m[7]*b.m[14];
  result.m[7] = a.m[4]*b.m[3] + a.m[5]*b.m[7] + a.m[6]*b.m[11] + a.m[7]*b.m[15];

  // Row 3
  result.m[8]  = a.m[8]*b.m[0] + a.m[9]*b.m[4] + a.m[10]*b.m[8]  + a.m[11]*b.m[12];
  result.m[9]  = a.m[8]*b.m[1] + a.m[9]*b.m[5] + a.m[10]*b.m[9]  + a.m[11]*b.m[13];
  result.m[10] = a.m[8]*b.m[2] + a.m[9]*b.m[6] + a.m[10]*b.m[10] + a.m[11]*b.m[14];
  result.m[11] = a.m[8]*b.m[3] + a.m[9]*b.m[7] + a.m[10]*b.m[11] + a.m[11]*b.m[15];

  // Row 4
  result.m[12] = a.m[12]*b.m[0] + a.m[13]*b.m[4] + a.m[14]*b.m[8]  + a.m[15]*b.m[12];
  result.m[13] = a.m[12]*b.m[1] + a.m[13]*b.m[5] + a.m[14]*b.m[9]  + a.m[15]*b.m[13];
  result.m[14] = a.m[12]*b.m[2] + a.m[13]*b.m[6] + a.m[14]*b.m[10] + a.m[15]*b.m[14];
  result.m[15] = a.m[12]*b.m[3] + a.m[13]*b.m[7] + a.m[14]*b.m[11] + a.m[15]*b.m[15];

  return result; 
}

Matrix4D matrix4d_translation(const Vector3f v)
{
  Matrix4D matrix =
    {
      {
        1.0, 0.0, 0.0, v.c[X],
        0.0, 1.0, 0.0, v.c[Y],
        0.0, 0.0, 1.0, v.c[Z],
        0.0, 0.0, 0.0, 1.0,
      }
    };

  return matrix; 
}
