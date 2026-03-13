#ifndef MATHLIB_H
#define MATHLIB_H

#define X 0
#define Y 1
#define Z 2
#define W 3

struct Vector2 { int c[2]; };
struct Vector3 { int c[3]; };
struct Vector4 { int c[4]; };

struct Vector3f { double c[3]; };

Vector2 vec2(int x, int y);
Vector2 vec2s(int x);
Vector2 vec2_add(Vector2 a, Vector2 b);
Vector2 vec2_sub(Vector2 a, Vector2 b);
Vector2 vec2_mul(Vector2 a, Vector2 b);
Vector2 vec2_div(Vector2 a, Vector2 b);
int vec2_dot(Vector3f a, Vector3f b);

///////////////////////////////////////////////////////////

Vector3 vec3(int x, int y, int z);
Vector3 vec3s(int x);
Vector3 vec3_add(Vector3 a, Vector3 b);
Vector3 vec3_sub(Vector3 a, Vector3 b);
Vector3 vec3_mul(Vector3 a, Vector3 b);
Vector3 vec3_div(Vector3 a, Vector3 b);
int vec3_dot(Vector3f a, Vector3f b);

///////////////////////////////////////////////////////////

Vector3f vec3f(double x, double y, double z);
Vector3f vec3fs(double x);
Vector3f vec3f_add(Vector3f a, Vector3f b);
Vector3f vec3f_sub(Vector3f a, Vector3f b);
Vector3f vec3f_mul(Vector3f a, Vector3f b);
Vector3f vec3f_div(Vector3f a, Vector3f b);
double vec3f_dot(Vector3f a, Vector3f b);

///////////////////////////////////////////////////////////

Vector4 vec4(int x, int y, int z, int w);
Vector4 vec4s(int x);
Vector4 vec4_add(Vector4 a, Vector4 b);
Vector4 vec4_sub(Vector4 a, Vector4 b);
Vector4 vec4_mul(Vector4 a, Vector4 b);
Vector4 vec4_div(Vector4 a, Vector4 b);
int vec4_dot(Vector3f a, Vector3f b);

#endif
