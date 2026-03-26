#include "../include/renderer.h"

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
  f64 deg = 30.0;
  f64 rad = deg * DEG2RAD;

  Matrix4D ModelView, Viewport, Perspective;
  
  const Matrix3D rotation_matrix_x = matrix3d_rotation_x(rad);
  const Matrix3D rotation_matrix_y = matrix3d_rotation_y(rad);
  const Matrix3D rotation_matrix_z = matrix3d_rotation_z(rad);

  Matrix3D rotate = matrix3d_multiply(rotation_matrix_x, rotation_matrix_z);  
  
  for (i32 i = 0; i < buffer.face_count; i++)
    {
      Vector3 face = buffer.faces[i];

      Vector3 vertex0 = screen(mul_vec3f(rotate, buffer.vertices[face.c[X]]));  
      Vector3 vertex1 = screen(mul_vec3f(rotate, buffer.vertices[face.c[Y]]));  
      Vector3 vertex2 =	screen(mul_vec3f(rotate, buffer.vertices[face.c[Z]]));

      TGAColor rnd;
      for (i32 c = 0; c < 3; c++)
        rnd[c] = std::rand()%255;

      fill_triangle(vertex0, vertex1, vertex2, framebuffer, zbuffer, rnd); 
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

void fill_triangle(Vector3 point1, Vector3 point2, Vector3 point3,
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

void fill_triangle(const Vector4 clip[3], TGAImage &framebuffer,
                   TGAImage &zbuffer, TGAColor color)
{
  Vector4 normalized_device_coordinates[3] =
  {
    vec4_div_scalar(clip[0], clip[0].c[W]),
    vec4_div_scalar(clip[1], clip[1].c[W]),
    vec4_div_scalar(clip[2], clip[2].c[W]),   
  };
    
  Vector2 screen[3] = {0}; 
  
  for (size_t i = 0; i < 3; ++i)
    {
      Vector4 result4d = mul_vec4(Viewport, normalized_device_coordinates[i]); 
      Vector2 result2d;
      result2d.c[X] = result4d.c[X];
      result2d.c[Y] = result4d.c[Y]; 
      screen[i] = result2d; 
    }

  
  Matrix3D ABC =
    {
      {
        
      }
    }; 

  auto [bbminx, bbmaxx] = std::minmax({screen[0].c[X], screen[1].c[X], screen[2].c[X]});
  auto [bbminy, bbmaxy] = std::minmax({screen[0].c[Y], screen[1].c[Y], screen[2].c[Y]});

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
