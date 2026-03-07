void fill_triangle(Vector3 point1, Vector3 point2, Vector3 point3,
                   Vector3 colorA, Vector3 colorB, Vector3 colorC, 
                   TGAImage &framebuffer, TGAColor color)
{
  int bbminx = std::min(std::min(point1.x, point2.x), point3.x); 
  int bbminy = std::min(std::min(point1.y, point2.y), point3.y);
  int bbmaxx = std::max(std::max(point1.x, point2.x), point3.x);
  int bbmaxy = std::max(std::max(point1.y, point2.y), point3.y);

  bbminx = std::max(0, bbminx);
  bbmaxx = std::min(width-1, bbmaxx);
  bbminy = std::max(0, bbminy);
  bbmaxy = std::min(height-1, bbmaxy);
  
  double total_area = signed_triangle_area(point1, point2, point3);
  if (total_area < 1)
    return; // backface culling + discarding triangles that cover less than a pixel
  
  int z = 0; 
#pragma omp parallel for
  for (int x = bbminx; x <= bbmaxx; x++)
    {
      for (int y = bbminy; y <= bbmaxy; y++)
        {
          Vector3 point = {x, y, z};
          double alpha = signed_triangle_area(point, point2, point3) / total_area; 
          double beta  = signed_triangle_area(point, point3, point1) / total_area; 
          double gamma = signed_triangle_area(point, point1, point2) / total_area; 

          if (alpha < 0 || beta < 0 || gamma < 0)
            continue;

          double t = 0.1;
          if (alpha > t && beta > t && gamma > t)
            {
              color[0] = 0;
              color[1] = 0;
              color[2] = 0;
            }
          else
            {
              color[0] = static_cast<unsigned char>(alpha * colorA.x + beta * colorB.x + gamma * colorC.x);
              color[1] = static_cast<unsigned char>(alpha * colorA.y + beta * colorB.y + gamma * colorC.y);
              color[2] = static_cast<unsigned char>(alpha * colorA.z + beta * colorB.z + gamma * colorC.z);
            }
          
          framebuffer.set(x, y, color);
        }
    }
}
