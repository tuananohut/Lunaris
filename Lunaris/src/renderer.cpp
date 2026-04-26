#include "../include/renderer.h"

Matrix4D ModelView, Viewport, Perspective;

void draw_line(Vector3 p0, Vector3 p1, TGAImage &framebuffer, TGAColor color)
{
  bool steep = std::abs(p0.c[X] - p1.c[X]) < std::abs(p0.c[Y] - p1.c[Y]);
  if (steep)
    {
      std::swap(p0.c[X], p0.c[Y]);
      std::swap(p1.c[X], p1.c[Y]); 
    }
   
  if (p0.c[X] > p1.c[X])
    {
      std::swap(p0.c[X], p1.c[X]);
      std::swap(p0.c[Y], p1.c[Y]); 
    }

  i32 y = p0.c[Y];
  i32 ierror = 0; 
  for (i32 x = p0.c[X]; x < p1.c[X]; x++)
    {
      if (steep)
        framebuffer.set(y, x, color);
      else 
        framebuffer.set(x, y, color);

      ierror += 2 * std::abs(p1.c[Y] - p0.c[Y]); 
	
      y += (p1.c[Y] > p0.c[Y] ? 1 : -1) * (ierror > (p1.c[X] - p0.c[X])); // Up or down ? 
      ierror -= 2 * (p1.c[X] - p0.c[X]) * (ierror > (p1.c[X] - p0.c[X])); 
    }	
} 

void draw_triangle(Vector3 point1, Vector3 point2, Vector3 point3,
                   TGAImage &framebuffer, TGAColor color)
{
  draw_line(point1, point2, framebuffer, color);
  draw_line(point2, point3, framebuffer, color);
  draw_line(point1, point3, framebuffer, color);
}

/*
void render_model(ModelBuffer& buffer, TGAImage &framebuffer, TGAColor color)
{ 
  for (i32 i = 0; i < buffer.face_count; i++)
    {
      Vector3 face = buffer.faces[i];

      Vector3 vertex0_ = screen(buffer.vertices[face.c[X]]);   
      Vector3 vertex1_ = screen(buffer.vertices[face.c[Y]]);   
      Vector3 vertex2_ = screen(buffer.vertices[face.c[Z]]);   

      draw_triangle(vertex0_, vertex1_, vertex2_, framebuffer, color); 
    }
}
*/

void rasterize_model(ModelBuffer& buffer, TGAImage &framebuffer, std::vector<f64> &zbuffer)
{
  constexpr Vector3f    eye = {  0.0, 1.0, 2.0 };
  constexpr Vector3f center = {  0.0, 0.0, 0.0 };
  constexpr Vector3f     up = {  0.0, 1.0, 0.0 };

  const i32 width  = 1080; 
  const i32 height = 1080;

  const Vector2 v = { width/8, height/8 }; 

  ModelView = lookat(eye, center, up);
  Perspective = perspective(vec3f_magnitude(vec3f_sub(eye, center)));
  Viewport = viewport(width*3/4, height*3/4, v);   
  
  f64 deg = 30.0;
  f64 rad = deg * DEG2RAD;
  
  const Matrix3D rotation_matrix_x = matrix3d_rotation_x(rad);
  const Matrix3D rotation_matrix_y = matrix3d_rotation_y(rad);
  const Matrix3D rotation_matrix_z = matrix3d_rotation_z(rad);

  Matrix3D rotate = matrix3d_multiply(rotation_matrix_x, rotation_matrix_z);  

  Vector4f clip[3];

  for (i32 i = 0; i < buffer.face_count; i++)
    {
      Vector3 face = buffer.faces[i];
     
      for (i32 d = 0; d < 3; d++)
        {
          Vector3f vertex = buffer.vertices[buffer.faces[i].c[d]];
          Vector4f model = { vertex.c[X], vertex.c[Y], vertex.c[Z], 1.0 };

          Vector4f view  = mul_vec4f(ModelView, model);
          Vector4f world = mul_vec4f(Perspective, view);

          clip[d] = world;
        }

      TGAColor rnd;
      for (i32 c = 0; c < 3; c++)
        rnd[c] = std::rand()%255;
      
      fill_triangle(width, height, clip, framebuffer, zbuffer, rnd); 
    }
}

void fill_triangle(const int width, const int height,
                   const Vector4f clip[3], TGAImage &framebuffer,
                   std::vector<f64> &zbuffer, TGAColor color)
{
  Vector4f normalized_device_coordinates[3] =
  {
    vec4f_div_scalar(clip[0], clip[0].c[W]),
    vec4f_div_scalar(clip[1], clip[1].c[W]),
    vec4f_div_scalar(clip[2], clip[2].c[W]),   
  };
    
  Vector2 screen[3] = {0}; 
  
  Vector4f A = mul_vec4f(Viewport, normalized_device_coordinates[0]);
  Vector4f B = mul_vec4f(Viewport, normalized_device_coordinates[1]);
  Vector4f C = mul_vec4f(Viewport, normalized_device_coordinates[2]);

  screen[0] = { static_cast<i32>(A.c[X]), static_cast<i32>(A.c[Y]) };
  screen[1] = { static_cast<i32>(B.c[X]), static_cast<i32>(B.c[Y]) };
  screen[2] = { static_cast<i32>(C.c[X]), static_cast<i32>(C.c[Y]) };
  
  auto bbminx = std::min({ screen[0].c[X], screen[1].c[X], screen[2].c[X] }); 
  auto bbmaxx = std::max({ screen[0].c[X], screen[1].c[X], screen[2].c[X] }); 

  auto bbminy = std::min({ screen[0].c[Y], screen[1].c[Y], screen[2].c[Y] }); 
  auto bbmaxy = std::max({ screen[0].c[Y], screen[1].c[Y], screen[2].c[Y] }); 

  bbminx = std::max(0, bbminx);
  bbmaxx = std::min(width-1, bbmaxx);
  bbminy = std::max(0, bbminy);
  bbmaxy = std::min(height-1, bbmaxy);

  auto signed_area = [](Vector2 a, Vector2 b, Vector2 c)
  {
    return (b.c[X] - a.c[X]) * (c.c[Y] - a.c[Y]) - (b.c[Y] - a.c[Y]) * (c.c[X] - a.c[X]);
  };

  f64 total_area = signed_area(screen[0], screen[1], screen[2]);
  if (std::abs(total_area) < 1e-5)
    return;

#pragma omp parallel for
  for (i32 y = bbminy; y <= bbmaxy; y++)
    {
      for (i32 x = bbminx; x <= bbmaxx; x++)
        {
          Vector2 p = { static_cast<i32>(x), static_cast<i32>(y) };
          
          f64 alpha = signed_area(screen[1], screen[2], p) / total_area;
          f64 beta  = signed_area(screen[2], screen[0], p) / total_area;
          f64 gamma = signed_area(screen[0], screen[1], p) / total_area;

          if (alpha < 0 || beta < 0 || gamma < 0)
            continue;

          f64 z = alpha * normalized_device_coordinates[0].c[Z] + 
                  beta  * normalized_device_coordinates[1].c[Z] + 
                  gamma * normalized_device_coordinates[2].c[Z]; 

          if (z <= zbuffer[x + y * framebuffer.width()])
            continue;
          
          zbuffer[x + y * framebuffer.width()] = z;
          framebuffer.set(x, y, color);
        }
    }
}
