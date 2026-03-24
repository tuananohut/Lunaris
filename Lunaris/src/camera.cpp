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
 
Matrix4D lookat(const Vector3f eye, const Vector3f center, const Vector3f up)
{
  Matrix4D model_view; 

  Matrix4D eye_up_center =
    {
      {
        l.x, l.y, l.z, 0.0,
        m.x, m.y, m.z, 0.0,
        n.x, n.y, n.z, 0.0,
        0.0, 0.0, 0.0, 1.0, 
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
  
  vec3 n = vec3_normalize(eye-center);
  vec3 l = vec3_normalize(cross_product(up,n));
  vec3 m = vec3_normalize(cross_product(n, l));

  ModelView = matrix4d_multiply(eye_up_center, center_matrix);

  return ModelView; 
}
