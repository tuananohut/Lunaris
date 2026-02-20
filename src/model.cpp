#include "model.h"

bool object_to_render(char *filename, ModelBuffer &buffer)
{
  assert(filename);
  
  FILE* file = fopen(filename, "r");
  if (!file)
    return false;

  Vector3f vertices;
  Vector3i faces; 
  
  int posCount = 0;
  int faceCount = 0;
  
  char line[15000];

  while (fgets(line, sizeof(line), file))
    {
      if (line[0] == 'v' && line[1] == ' ')
	{
	  float x, y, z;
	  int read = sscanf(line, "v %f %f %f", &x, &y, &z);	
	  vertices[posCount++] = Vector3f(x, y, z);	    
	}
      if (line[0] == 'f' && line[1] == ' ')
	{
	  for (size_t i = 0; i < 3; ++i)
	    {
	      int x, y, z; 
	      int read = sscanf(line, "f %d/%d/%d", &x, &y, &z); 
	    }
	}
    }

  fclose(file);

  buffer.vertex_count = posCount;
  buffer.face_count  = buffer.vertex_count;

  vertices = new ModelBuffer[buffer.vertex_count];
  indices  = new int[buffer.face_count];

  for (int i = 0; i < posCount; ++i)
    {
      buffer.vertices[i].position = positions[i];

      buffer.faces[i] = i;
    }

  return true;
}
