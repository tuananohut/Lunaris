#include "../Lunaris/include/renderer.h"
#include <iostream>

int main(int argc, char** argv)
{
  constexpr i32 width  = 1080;			  
  constexpr i32 height = 1080;
                           
  TGAImage framebuffer(width, height, TGAImage::RGB);
  std::vector<double> zbuffer(width*height, -std::numeric_limits<double>::max());
 
  for (size_t i = 0; i < width; ++i)
    {
      for (size_t j = 0; j < height; ++j)
        {
          framebuffer.set(i, j, navy); 
        }
    }
  
  ModelBuffer *buffer = new ModelBuffer();
  // const char *model_filename = "../obj/african_head/african_head.obj";
  // const char *model_filename = "../obj/diablo3_pose/diablo3_pose.obj";
  // const char *model_filename = "../obj/bunny.obj";
  // const char *model_filename = "../obj/penger.obj";
  const char *model_filename = "../obj/teapot.obj";

  object_to_render(model_filename, *buffer);

  printf("counts: V=%d  VN=%d  F=%d\n",
       buffer->vertex_count, buffer->normal_count, buffer->face_count);

  for (i32 f = 0; f < buffer->face_count; ++f)
    {
      Vector3 nf = buffer->normal_faces[f];  
      Vector3 vf = buffer->faces[f];         

      if (nf.c[X] < 0 || nf.c[X] >= buffer->normal_count ||
	  nf.c[Y] < 0 || nf.c[Y] >= buffer->normal_count ||
	  nf.c[Z] < 0 || nf.c[Z] >= buffer->normal_count)
	{
	  printf("BAD NORMAL INDEX at face %d: (%d,%d,%d) [normal_count=%d]\n",
		 f, nf.c[X], nf.c[Y], nf.c[Z], buffer->normal_count);
	  continue;
	}

      Vector3f n0 = buffer->normals[nf.c[X]];
      Vector3f n1 = buffer->normals[nf.c[Y]];
      Vector3f n2 = buffer->normals[nf.c[Z]];
      bool flat = (nf.c[X] == nf.c[Y] && nf.c[Y] == nf.c[Z]);

      if (f < 20)  
        printf("face %d | vi=(%d,%d,%d) ni=(%d,%d,%d) %s | "
               "n0=(%.2f,%.2f,%.2f)\n",
               f, vf.c[X], vf.c[Y], vf.c[Z], nf.c[X], nf.c[Y], nf.c[Z],
               flat ? "FLAT" : "smooth", n0.c[X], n0.c[Y], n0.c[Z]);
    }

  i32 flat = 0;
  for (i32 f = 0; f < buffer->face_count; ++f)
    {
      Vector3  nf = buffer->normal_faces[f];
      Vector3f A  = buffer->normals[nf.c[X]];
      Vector3f B  = buffer->normals[nf.c[Y]];
      Vector3f C  = buffer->normals[nf.c[Z]];

      f64 la = sqrt(A.c[X]*A.c[X] + A.c[Y]*A.c[Y] + A.c[Z]*A.c[Z]);
      f64 lb = sqrt(B.c[X]*B.c[X] + B.c[Y]*B.c[Y] + B.c[Z]*B.c[Z]);
      f64 lc = sqrt(C.c[X]*C.c[X] + C.c[Y]*C.c[Y] + C.c[Z]*C.c[Z]);
      f64 dab = (A.c[X]*B.c[X] + A.c[Y]*B.c[Y] + A.c[Z]*B.c[Z]) / (la*lb);   // cos(açý)
      f64 dbc = (B.c[X]*C.c[X] + B.c[Y]*C.c[Y] + B.c[Z]*C.c[Z]) / (lb*lc);

      if (dab > 0.9995 && dbc > 0.9995) ++flat;            // ~paralel = flat
    }
  printf("flat-by-vector faces: %d / %d\n", flat, buffer->face_count);
  
  rasterize_model(*buffer, framebuffer, zbuffer);  

  std::cout << "Writing file..." << std::endl;
  framebuffer.write_tga_file("framebuffer.tga");
  std::cout << "Done." << std::endl;
  
  return 0;
}
