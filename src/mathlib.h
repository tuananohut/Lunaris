#ifndef MATHLIB_H
#define MATHLIB_H

#include <cmath>

#define X 0
#define Y 1
#define Z 2
#define W 3

typedef float  f32;
typedef double f64;

typedef char   i8;
typedef char   i16; 
typedef int    i32;

struct Vector2 { i32 c[2]; };
struct Vector3 { i32 c[3]; };
struct Vector4 { i32 c[4]; };

struct Vector3f { f64 c[3]; };

struct Matrix { f64 m[4][4]; };


Vector2 vec2(i32 x, i32 y);
Vector2 vec2s(i32 x);
Vector2 vec2_add(Vector2 a, Vector2 b);
Vector2 vec2_sub(Vector2 a, Vector2 b);
Vector2 vec2_mul(Vector2 a, Vector2 b);
Vector2 vec2_div(Vector2 a, Vector2 b);
i32 vec2_dot(Vector2 a, Vector2 b);
f64 cross_product(Vector2 a, Vector2 b);
f64 signed_triangle_area(Vector2 a, Vector2 b, Vector2 c);

///////////////////////////////////////////////////////////

Vector3 vec3(i32 x, i32 y, i32 z);
Vector3 vec3s(i32 x);
Vector3 vec3_add(Vector3 a, Vector3 b);
Vector3 vec3_sub(Vector3 a, Vector3 b);
Vector3 vec3_mul(Vector3 a, Vector3 b);
Vector3 vec3_div(Vector3 a, Vector3 b);
i32 vec3_dot(Vector3 a, Vector3 b);
f64 signed_triangle_area(Vector3 a, Vector3 b, Vector3 c);

///////////////////////////////////////////////////////////

Vector3f vec3f(f64 x, f64 y, f64 z);
Vector3f vec3fs(f64 x);
Vector3f vec3f_add(Vector3f a, Vector3f b);
Vector3f vec3f_sub(Vector3f a, Vector3f b);
Vector3f vec3f_mul(Vector3f a, Vector3f b);
Vector3f vec3f_div(Vector3f a, Vector3f b);
f64 vec3f_dot(Vector3f a, Vector3f b);

///////////////////////////////////////////////////////////

Vector4 vec4(i32 x, i32 y, i32 z, i32 w);
Vector4 vec4s(i32 x);
Vector4 vec4_add(Vector4 a, Vector4 b);
Vector4 vec4_sub(Vector4 a, Vector4 b);
Vector4 vec4_mul(Vector4 a, Vector4 b);
Vector4 vec4_div(Vector4 a, Vector4 b);
Vector4 mul_vec4(Matrix m, Vector4 v);
i32 vec4_dot(Vector4 a, Vector4 b);

///////////////////////////////////////////////////////////

Matrix matrix_identity();
Matrix matrix_rotation_x(f64 t); 
Matrix matrix_rotation_y(f64 t); 
Matrix matrix_rotation_z(f64 t); 

#endif

