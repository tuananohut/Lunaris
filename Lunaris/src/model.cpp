#include "../include/model.h"

static int parse_face_token(const char* tok, i32* v, i32* vt, i32* vn)
{
  *v = *vt = *vn = 0;
  if (sscanf(tok, "%d/%d/%d", v, vt, vn) == 3) return 3; 
  if (sscanf(tok, "%d//%d",  v, vn)      == 2) return 3;  
  if (sscanf(tok, "%d/%d",   v, vt)      == 2) return 2;  
  if (sscanf(tok, "%d",      v)          == 1) return 1;  
  return 0;
}

static inline i32 resolve_index(i32 idx, i32 count)
{
  if (idx > 0) return idx - 1;
  if (idx < 0) return count + idx;
  return -1;
}

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
      if (line[0] == 'v' && line[1] == ' ' && posCount < 30000)
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

      if (line[0] == 'f' && line[1] == ' ')
	{
	  i32 vi[64], ni[64];
	  int n = 0;

	  char* p = line + 1;
	  char tok[64];
	  while (*p && n < 64)
	    {
	      while (*p == ' ' || *p == '\t') ++p;
	      if (*p == '\0' || *p == '\n' || *p == '\r') break;

	      int k = 0;
	      while (*p && *p != ' ' && *p != '\t' &&
		     *p != '\n' && *p != '\r' && k < 63)
		tok[k++] = *p++;
	      tok[k] = '\0';

	      i32 v, vt, vn;
	      if (parse_face_token(tok, &v, &vt, &vn) == 0) continue;

	      vi[n] = resolve_index(v,  posCount);     
	      ni[n] = resolve_index(vn, normalCount);
	      ++n;
	    }

	  for (int i = 1; i + 1 < n; ++i)
	    {
	      if (faceCount >= 40000) {  break; }

	      buffer.faces[faceCount]        = vec3(vi[0], vi[i], vi[i + 1]);
	      buffer.normal_faces[faceCount] = vec3(ni[0], ni[i], ni[i + 1]);
	      ++faceCount;
	    }
	}
    }

  fclose(file);

  buffer.vertex_count = posCount;
  buffer.normal_count = normalCount;  
  buffer.face_count   = faceCount;
  
  return true;
}
