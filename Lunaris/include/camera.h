#ifndef CAMERA_H
#define CAMERA_H

#include "mathlib.h"

const int width = 1080;
const int height = 1080;

Matrix4D ModelView, Viewport, Perspective; 

void viewport(const Vector4 vec4); 
Matrix4D perspective(const double f64);
Matrix4D lookat(const Vector3f eye, const Vector3f center, const Vector3f up);

#endif
