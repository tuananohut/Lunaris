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

void rasterize_model(ModelBuffer& buffer, TGAImage &framebuffer, TGAImage &zbuffer)
{
  constexpr Vector3f    eye = { -1.0, 0.0, 2.0 };
  constexpr Vector3f center = {  0.0, 0.0, 0.0 };
  constexpr Vector3f     up = {  0.0, 1.0, 0.0 };

  const i32 width  = 1080; 
  const i32 height = 1080;

  const Vector2 v = { width*7/8, height*7/8 }; 
  
  ModelView = lookat(eye, center, up);
  Perspective = perspective(vec3f_magnitude(vec3f_sub(eye, center)));
  Viewport = viewport(width/16, height/16, v);   
  
  f64 deg = 30.0;
  f64 rad = deg * DEG2RAD;
  
  const Matrix3D rotation_matrix_x = matrix3d_rotation_x(rad);
  const Matrix3D rotation_matrix_y = matrix3d_rotation_y(rad);
  const Matrix3D rotation_matrix_z = matrix3d_rotation_z(rad);

  Matrix3D rotate = matrix3d_multiply(rotation_matrix_x, rotation_matrix_z);  

  Vector4 clip[3];
  
  for (i32 i = 0; i < buffer.face_count; i++)
    {
      Vector3 face = buffer.faces[i];
      
      // Vector3 vertex0 = screen(mul_vec3f(rotate, buffer.vertices[face.c[X]]));  
      // Vector3 vertex1 = screen(mul_vec3f(rotate, buffer.vertices[face.c[Y]]));  
      // Vector3 vertex2 = screen(mul_vec3f(rotate, buffer.vertices[face.c[Z]]));

      Vector3f vertex0 = buffer.vertices[face.c[X]];
      Vector3f vertex1 = buffer.vertices[face.c[Y]];
      Vector3f vertex2 = buffer.vertices[face.c[Z]];
      
      Matrix4D view_matrix  = mul_vec4f(ModelView, model);
      Matrix4D world_matrix = matrix4d_multiply(Perspective, view_matrix); 
      
      
      
      TGAColor rnd;
      for (i32 c = 0; c < 3; c++)
        rnd[c] = std::rand()%255;

      
      fill_triangle(width, height, clip, framebuffer, zbuffer, rnd); 
    }
}

void fill_triangle(Vector3 point1, Vector3 point2, Vector3 point3,
                   TGAImage &framebuffer, TGAColor color)
{
  i32 bbminx = std::min(std::min(point1.c[X], point2.c[X]), point3.c[X]); 
  i32 bbminy = std::min(std::min(point1.c[Y], point2.c[Y]), point3.c[Y]);
  i32 bbmaxx = std::max(std::max(point1.c[X], point2.c[X]), point3.c[X]);
  i32 bbmaxy = std::max(std::max(point1.c[Y], point2.c[Y]), point3.c[Y]); 
  f64 total_area = signed_triangle_area(point1, point2, point3);
  if (total_area < 1)
    return; // backface culling + discarding triangles that cover less than a pixel
  
#pragma omp parallel for
  for (i32 y = bbminy; y <= bbmaxy; y++)
    {
      for (i32 x = bbminx; x <= bbmaxx; x++)
        {
          Vector3 point = {x, y, 0};
          f64 alpha = signed_triangle_area(point, point2, point3) / total_area; 
          f64 beta  = signed_triangle_area(point, point3, point1) / total_area; 
          f64 gamma = signed_triangle_area(point, point1, point2) / total_area; 

          if (alpha < 0 || beta < 0 || gamma < 0)
            continue; 

          framebuffer.set(x, y, color); 
        }
    }
}

void fill_triangle(const int width, const int height,
                   Vector3 point1, Vector3 point2, Vector3 point3,
                   TGAImage &framebuffer, TGAImage &zbuffer, TGAColor color)
{
  i32 bbminx = std::min(std::min(point1.c[X], point2.c[X]), point3.c[X]); 
  i32 bbminy = std::min(std::min(point1.c[Y], point2.c[Y]), point3.c[Y]);
  i32 bbmaxx = std::max(std::max(point1.c[X], point2.c[X]), point3.c[X]);
  i32 bbmaxy = std::max(std::max(point1.c[Y], point2.c[Y]), point3.c[Y]);

  bbminx = std::max(0, bbminx);
  bbmaxx = std::min(width-1, bbmaxx);
  bbminy = std::max(0, bbminy);
  bbmaxy = std::min(height-1, bbmaxy);
  
  f64 total_area = signed_triangle_area(point1, point2, point3);
  if (total_area < 1)
    return; // backface culling + discarding triangles that cover less than a pixel

#pragma omp parallel for
  for (i32 y = bbminy; y <= bbmaxy; y++)
    {
      for (i32 x = bbminx; x <= bbmaxx; x++)
        {
          Vector3 point = {x, y, 0};
          f64 alpha = signed_triangle_area(point, point2, point3) / total_area; 
          f64 beta  = signed_triangle_area(point, point3, point1) / total_area; 
          f64 gamma = signed_triangle_area(point, point1, point2) / total_area;
          
          if (alpha < 0 || beta < 0 || gamma < 0)
            continue;

          unsigned char z = static_cast<unsigned char>(alpha * point1.c[Z] + beta * point2.c[Z] + gamma * point3.c[Z]);
          if (z <= zbuffer.get(x, y)[0])
            continue;
          
          zbuffer.set(x, y, {z});  
          framebuffer.set(x, y, color);
        }
    }
}

void fill_triangle(const int width, const int height,
                   const Vector4 clip[3], TGAImage &framebuffer,
                   std::vector<f64> &zbuffer[], TGAColor color)
{
  Vector4 normalized_device_coordinates[3] =
  {
    vec4_div_scalar(clip[0], clip[0].c[W]),
    vec4_div_scalar(clip[1], clip[1].c[W]),
    vec4_div_scalar(clip[2], clip[2].c[W]),   
  };
    
  Vector2 screen[3] = {0}; 
  
  Vector4 A = mul_vec4(Viewport, normalized_device_coordinates[0]);
  Vector4 B = mul_vec4(Viewport, normalized_device_coordinates[1]);
  Vector4 C = mul_vec4(Viewport, normalized_device_coordinates[2]);

  Vector2 a = vec2(A.c[X], A.c[Y]); 
  Vector2 b = vec2(B.c[X], B.c[Y]); 
  Vector2 c = vec2(C.c[X], C.c[Y]);

  screen[0] = { A.c[X], A.c[Y] };
  screen[1] = { B.c[X], B.c[Y] };
  screen[2] = { C.c[X], C.c[Y] };
  
  Matrix3D ABC =
    {
      {
        static_cast<f64>(screen[0].c[X]), static_cast<f64>(screen[0].c[Y]), 1.,
        static_cast<f64>(screen[1].c[X]), static_cast<f64>(screen[1].c[Y]), 1.,
        static_cast<f64>(screen[2].c[X]), static_cast<f64>(screen[2].c[Y]), 1.,
      }
    }; 
  
  auto bbminx = std::min({ screen[0].c[X], screen[1].c[X], screen[2].c[X] }); 
  auto bbmaxx = std::max({ screen[0].c[X], screen[1].c[X], screen[2].c[X] }); 

  auto bbminy = std::min({ screen[0].c[Y], screen[1].c[Y], screen[2].c[Y] }); 
  auto bbmaxy = std::max({ screen[0].c[Y], screen[1].c[Y], screen[2].c[Y] }); 

  bbminx = std::max(0, bbminx);
  bbmaxx = std::min(width-1, bbmaxx);
  bbminy = std::max(0, bbminy);
  bbmaxy = std::min(height-1, bbmaxy);

#pragma omp parallel for
  for (i32 y = bbminy; y <= bbmaxy; y++)
    {
      for (i32 x = bbminx; x <= bbmaxx; x++)
        {
          Vector3f point = {static_cast<f64>(x), static_cast<f64>(y), 1.};
          Vector3f barycentric = mul_vec3f(ABC, point); 
                    
          if (barycentric.c[X] < 0 || barycentric.c[Y] < 0 || barycentric.c[Z] < 0)
            continue;

          f64 z = vec3f_dot(barycentric, vec3f(normalized_device_coordinates[0].c[Z],
                                               normalized_device_coordinates[1].c[Z],
                                               normalized_device_coordinates[2].c[Z])); 

          if (z <= zbuffer[x+y*framebuffer.width()])
            continue;
          
          zbuffer[x+y*framebuffer.width()] = z;
          framebuffer.set(x, y, color);
        }
    }
}
