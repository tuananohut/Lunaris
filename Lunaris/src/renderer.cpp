#include "../include/renderer.h"

Matrix4D ModelView, Viewport, Perspective;

Vector4f RandomShader::vertex(int face, int vert, int norm)
{
  Vector3f v = model.vertices[model.faces[face].c[vert]];
  Vector3f vn = model.normals[model.faces[face].c[norm]];

  Matrix4D normal_matrix = matrix4d_transpose(ModelView); 
  
  Vector4f model_pos =
    {
      v.c[X],
      v.c[Y],
      v.c[Z],
      1.0
    };

  Vector4f normal_pos =
    {
      vn.c[X],
      vn.c[Y],
      vn.c[Z],
      1.0
    };
  
  Vector4f view = mul_vec4f(ModelView, model_pos);

  Vector4f view_normal = mul_vec4f(normal_matrix, normal_pos); 
  
  tri[vert] = { view.c[X], view.c[Y], view.c[Z] };

  tri[norm] = { view_normal.c[X], view_normal.c[Y], view_normal.c[Z] }; 

  Vector4f perspective = mul_vec4f(Perspective, view);
  // perspective = mul_vec4f(Perspective, view_normal);
  
  return perspective;
}

TGAColor RandomShader::fragment(const Vector3f& bar) const
{
  Vector3f n = vec3f_normalize(tri[X]);
  
  Vector3f light_dir = vec3f_normalize(Vector3f{ 1.0, 1.0, -1.0 });

  Vector3f centroid = vec3f_mul_scalar(vec3f_add(vec3f_add(tri[0], tri[1]), tri[2]), 1.0 / 3.0);
  Vector3f v = vec3f_normalize(vec3f_mul_scalar(centroid, -1.0));

  f64 e = 32.0;  

  Vector3f r = vec3f_sub(vec3f_mul_scalar(n, 2.0 * vec3f_dot(n, light_dir)), light_dir); 
  f64 spec   = std::pow(std::max(0.0, vec3f_dot(r, v)), e);
  f64 diff   = std::abs(vec3f_dot(n, light_dir));
  f64 ambient = 0.4;
  f64 intensity = std::min(1.0, ambient + 0.6 * diff + 0.4 * spec);

  // Vector3f base_color = { 255.0, 112.0, 191.0 };
  Vector3f base_color = { 245.0, 245.0, 245.0 };

  TGAColor out;
  out[0] = static_cast<uint8_t>(base_color.c[0] * intensity);
  out[1] = static_cast<uint8_t>(base_color.c[1] * intensity);
  out[2] = static_cast<uint8_t>(base_color.c[2] * intensity);
  out[3] = 255;
  return out;
}

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

void rasterize_model(ModelBuffer& buffer, TGAImage &framebuffer, std::vector<f64> &zbuffer)
{
  constexpr Vector3f    eye = {  0.0, 0.0, 2.0 };
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

  for (int y = 0; y < framebuffer.height(); y++)
    {
      for (int x = 0; x < framebuffer.width(); x++)
        {
          framebuffer.set(x, y, navy);
        }
    }

  for (i32 i = 0; i < buffer.face_count; i++)
    {
      RandomShader shader(buffer);
	  
      for (i32 d = 0; d < 3; d++)
	clip[d] = shader.vertex(i, d, d);   
	  
      fill_triangle(width, height, clip, framebuffer, shader, zbuffer);
    }
}


void fill_triangle(const int width, const int height,
                   const Vector4f clip[3], TGAImage &framebuffer,
                   const RandomShader &shader,
                   std::vector<f64>& zbuffer)
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

          Vector3f bar = { alpha, beta, gamma };

          TGAColor color = shader.fragment(bar); 
          
          zbuffer[x + y * framebuffer.width()] = z;
          framebuffer.set(x, y, color);
        }
    }
}
