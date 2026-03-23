#include "../include/camera.h"

// -1..1 => (after added 1) 0..2 => (divided 2) 0..1 => (multiplied width or height)0..w/h 

Matrix4D viewport(const Vector2 v)
{
  Matrix4D Viewport =
    {
      width/2., 0.0,        0.0, v.c[X] + width/2.0,
      0.0,      height/2.0, 0.0, v.c[Y] + height/2.0,
      0.0,      0.0,        1.0, 0.0,
      0.0,      0.0,        0.0, 1.0,
    };
  
  return Viewport; 
}

Matrix4D perspective(const f64 f) 
{
  Matrix4D Perspective =
    {
      1.0, 0.0,    0.0, 0.0,
      0.0, 1.0,    0.0, 0.0,
      0.0, 0.0,    1.0, 0.0,
      0.0, 0.0, -1.0/f, 1.0,
    };

  return Perspective; 
} 

// screen => project => translate_z
 
