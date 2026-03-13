#include "model.h"

bool object_to_render(const char *filename, ModelBuffer &buffer)
{
  assert(filename);
  
  FILE* file = fopen(filename, "r");
  if (!file)
    return false;
  
  int posCount = 0;
  int faceCount = 0;
  
  char line[40000];

  while (fgets(line, sizeof(line), file))
    {
      if (line[0] == 'v' && line[1] == ' ')
        {
          double x, y, z;
          int read = sscanf(line, "v %lf %lf %lf", &x, &y, &z);
          buffer.vertices[posCount++] = vec3f(x, y, z);
        }
      if (line[0] == 'f' && line[1] == ' ')
        {
          int v0, v1, v2; 
          sscanf(line, "f %d%*[^ ] %d%*[^ ] %d%*[^ ]", &v0, &v1, &v2);
          buffer.faces[faceCount++] = vec3(v0 - 1, v1 - 1, v2 - 1);
        }
    }

  fclose(file);

  buffer.vertex_count = posCount;
  buffer.face_count   = faceCount;
  
  return true;
}
