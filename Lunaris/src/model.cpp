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
      
      if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ')
        {
          f64 nx, ny, nz;
          i32 read = sscanf(line, "vn %lf %lf %lf", &nx, &ny, &nz);
          buffer.normals[normalCount++] = vec3f(nx, ny, nz);
        }

      /*
      if (line[0] == 'f' && line[1] == ' ')
        {
          i32 v0, v1, v2; 
          sscanf(line, "f %d%*[^ ] %d%*[^ ] %d%*[^ ]", &v0, &v1, &v2);
          buffer.faces[faceCount++] = vec3(v0 - 1, v1 - 1, v2 - 1);
        }
      */
      if (line[0] == 'f' && line[1] == ' ')
	{
	  i32 v[3], n[3];
	  int got = sscanf(line, "f %d/%*d/%d %d/%*d/%d %d/%*d/%d",
			   &v[0],&n[0], &v[1],&n[1], &v[2],&n[2]);
	  if (got != 6) 
	    got = sscanf(line, "f %d//%d %d//%d %d//%d",
			 &v[0],&n[0], &v[1],&n[1], &v[2],&n[2]);

	  buffer.faces[faceCount]        = vec3(v[0]-1, v[1]-1, v[2]-1);
	  buffer.normal_faces[faceCount] = vec3(n[0]-1, n[1]-1, n[2]-1);
	  faceCount++;
	}
    }

  fclose(file);

  buffer.vertex_count = posCount;
  buffer.normal_count = normalCount;  
  buffer.face_count   = faceCount;
  
  return true;
}
