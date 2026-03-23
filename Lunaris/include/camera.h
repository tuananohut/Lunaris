#ifndef CAMERA_H
#define CAMERA_H

#include "mathlib.h"

const int width = 1080;
const int height = 1080;

void viewport(const Vector4 vec4); 
Matrix4D perspective(const double f64);

#endif
