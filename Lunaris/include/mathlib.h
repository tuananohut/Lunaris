#ifndef MATHLIB_H
#define MATHLIB_H

#include <cmath>

typedef float  f32;
typedef double f64;

typedef int    i32;

const f64 PI = 3.14159265358979323846;

const f64 DEG2RAD = PI / 180.0;
const f64 RAD2DEG = 180.0 / PI;

const i32 X = 0;
const i32 Y = 1;
const i32 Z = 2;
const i32 W = 3;

struct Vector2 { i32 c[2]; };
struct Vector3 { i32 c[3]; };
struct Vector4 { i32 c[4]; };
 
struct Vector3f { f64 c[3]; };

struct Matrix3D { f64 m[9]; };
struct Matrix4D { f64 m[16]; };

f64 cross_product(Vector2 a, Vector2 b);

///////////////////////////////////////////////////////////

Vector3 vec3(i32 x, i32 y, i32 z);
Vector3 vec3s(i32 x);
Vector3 vec3_add(Vector3 a, Vector3 b);
Vector3 vec3_sub(Vector3 a, Vector3 b);
Vector3 vec3_mul(Vector3 a, Vector3 b);
Vector3 vec3_mul_scalar(Vector3 a, i32 s);
Vector3 vec3_div(Vector3 a, Vector3 b);
Vector3 vec3_div_scalar(Vector3 a, i32 s);
Vector3 vec3_normalize(const Vector3 a);
Vector3 mul_vec3(Matrix3D m, Vector3 v);
i32 vec3_dot(Vector3 a, Vector3 b);
f64 vec3_magnitude(const Vector3 a);
f64 signed_triangle_area(Vector3 a, Vector3 b, Vector3 c);

///////////////////////////////////////////////////////////

Vector3f vec3f(f64 x, f64 y, f64 z);
Vector3f vec3fs(f64 x);
Vector3f vec3f_add(Vector3f a, Vector3f b);
Vector3f vec3f_sub(Vector3f a, Vector3f b);
Vector3f vec3f_mul(Vector3f a, Vector3f b);
Vector3f vec3f_mul_scalar(Vector3f a, f64 s);
Vector3f vec3f_div(Vector3f a, Vector3f b);
Vector3f vec3f_div_scalar(Vector3f a, f64 s);
Vector3f vec3f_normalize(const Vector3f a);
Vector3f mul_vec3f(Matrix3D m, Vector3f v);
Vector3f perspective(Vector3f v);
f64 vec3f_dot(Vector3f a, Vector3f b);
f64 vec3f_magnitude(const Vector3f a);

///////////////////////////////////////////////////////////

Vector4 vec4(i32 x, i32 y, i32 z, i32 w);
Vector4 vec4s(i32 x);
Vector4 vec4_add(Vector4 a, Vector4 b);
Vector4 vec4_sub(Vector4 a, Vector4 b);
Vector4 vec4_mul(Vector4 a, Vector4 b);
Vector4 vec4_mul_scalar(Vector4 a, i32 s);
Vector4 vec4_div(Vector4 a, Vector4 b);
Vector4 vec4_div_scalar(Vector4 a, i32 s);
Vector4 vec4_normalize(const Vector4 a);
Vector4 mul_vec4(Matrix4D m, Vector4 v);
i32 vec4_dot(Vector4 a, Vector4 b);
f64 vec4_magnitude(const Vector4 a);

///////////////////////////////////////////////////////////

Matrix3D matrix3d(f32 n00, f32 n01, f32 n02,
                  f32 n10, f32 n11, f32 n12,
                  f32 n20, f32 n21, f32 n22);
Matrix3D matrix3d_identity();
Matrix3D matrix3d_rotation_x(f64 t); 
Matrix3D matrix3d_rotation_y(f64 t); 
Matrix3D matrix3d_rotation_z(f64 t);
Matrix3D matrix3d_multiply(const Matrix3D a, const Matrix3D b); 

///////////////////////////////////////////////////////////

Matrix4D matrix4d(f32 n00, f32 n01, f32 n02, f32 n03,
                  f32 n10, f32 n11, f32 n12, f32 n13,
                  f32 n20, f32 n21, f32 n22, f32 n23,
                  f32 n30, f32 n31, f32 n32, f32 n33);
Matrix4D matrix4d_identity();
Matrix4D matrix4d_rotation_x(f64 t); 
Matrix4D matrix4d_rotation_y(f64 t); 
Matrix4D matrix4d_rotation_z(f64 t); 
Matrix4D matrix4d_multiply(const Matrix4D a, const Matrix4D b); 
Matrix4D matrix4d_translation(const Vector4 v); 
Matrix4D matrix4d_scale(const Vector4 v); 

#endif


