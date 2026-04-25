#ifndef CAMERA_H
#define CAMERA_H

#include "mathlib.h"

Matrix4D viewport(const int width, const int height, const Vector2 v);
Matrix4D perspective(const f64 f);
Matrix4D lookat(const Vector3f eye, const Vector3f center, const Vector3f up);

Vector3 screen(Vector3f); 

#endif
