#include "../include/camera.h"

// -1..1 => (after added 1) 0..2 => (divided 2) 0..1 => (multiplied width or height)0..w/h 

Matrix4D viewport(const int width, const int height, const Vector2 v)
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
 
Matrix4D lookat(const Vector3f eye, const Vector3f center, const Vector3f up)
{
  Matrix4D model_view;

  Vector3f n = vec3f_normalize(vec3f_sub(eye, center));
  Vector3f l = vec3f_normalize(cross_product(up, n));
  Vector3f m = vec3f_normalize(cross_product(n, l));

  Matrix4D eye_up_center =
    {
      {
        l.c[X], l.c[Y], l.c[Z], 0.0,
        m.c[X], m.c[Y], m.c[Z], 0.0,
        n.c[X], n.c[Y], n.c[Z], 0.0,
        0.0,    0.0,    0.0,    1.0, 
      } 
    };

  Matrix4D center_matrix =
    {
      {
        1.0, 0.0, 0.0, -center.c[X],
        0.0, 1.0, 0.0, -center.c[Y],
        0.0, 0.0, 1.0, -center.c[Z],
        0.0, 0.0, 0.0, 1.0,
      }
    };
  
  model_view = matrix4d_multiply(eye_up_center, center_matrix);

  return model_view; 
}

std::vector<f64> init_zbuffer(const int width, const int height)
{
  return std::vector<f64>(width*height, -1000.0); 
}
