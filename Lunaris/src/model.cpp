#include "../include/model.h"

bool object_to_render(const char *filename, ModelBuffer &buffer)
{
  assert(filename);
  
  FILE* file = fopen(filename, "r");
  if (!file)
    return false;
  
  i32 posCount = 0;
  i32 normalCount = 0; 
  i32 faceCount = 0;
  
  char line[40000];

  while (fgets(line, sizeof(line), file))
    {
      if (line[0] == 'v' && line[1] == ' ')
        {
          f64 x, y, z;
          i32 read = sscanf(line, "v %lf %lf %lf", &x, &y, &z);
          buffer.vertices[posCount++] = vec3f(x, y, z);
        }
      if (line[0] == 'f' && line[1] == ' ')
        {
          i32 v0, v1, v2; 
          sscanf(line, "f %d%*[^ ] %d%*[^ ] %d%*[^ ]", &v0, &v1, &v2);
          buffer.faces[faceCount++] = vec3(v0 - 1, v1 - 1, v2 - 1);
        }
      if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ')
        {
          f64 nx, ny, nz;
          i32 read = sscanf(line, "vn %lf %lf %lf", &nx, &ny, &nz);
          buffer.vertices[normalCount++] = vec3f(nx, ny, nz);
        } 
    }

  fclose(file);

  buffer.vertex_count = posCount;
  buffer.normal_count = normalCount;  
  buffer.face_count   = faceCount;
  
  return true;
}
