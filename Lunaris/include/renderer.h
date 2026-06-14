#ifndef RENDERER_H
#define RENDERER_H

#include <cmath>
#include <algorithm>
#include <vector>
#include "model.h"
#include "tgaimage.h"
#include "mathlib.h"
#include "camera.h"

constexpr TGAColor white   = {255, 255, 255, 255}; // attention, BGRA order
constexpr TGAColor green   = {  0, 255,   0, 255};
constexpr TGAColor red     = {  0,   0, 255, 255};
constexpr TGAColor blue    = {255, 128,  64, 255};
constexpr TGAColor yellow  = {  0, 200, 255, 255};
constexpr TGAColor pink    = {201, 145, 228, 255};
constexpr TGAColor navy    = { 61,  23,  21, 255};
constexpr TGAColor purple  = {152,  37, 152, 255};
constexpr TGAColor grey    = {233, 233, 241, 255};

extern Matrix4D ModelView;
extern Matrix4D Perspective;
extern Matrix4D Viewport;

struct Shader
{
  TGAColor fragment(const Vector3f& bar) const
  {
    TGAColor color; 
    color[0] = 255; 
    color[1] = 255; 
    color[2] = 255; 
    color[3] = 255; 

    return color; 
  }
};

struct RandomShader
{
  const ModelBuffer& model;
  TGAColor color = {};
  Vector3f tri[3] = {};

  RandomShader(const ModelBuffer& m) : model(m) {}

  Vector4f vertex(int face, int vert);

  TGAColor fragment(const Vector3f& bar) const;
};

void draw_line(Vector3 start_point, Vector3 end_point, TGAImage &framebuffer, TGAColor color);

void draw_triangle(Vector3 point1, Vector3 point2, Vector3 point3, TGAImage &framebuffer, TGAColor color);

// void render_model(ModelBuffer& buffer, TGAImage &framebuffer, TGAColor color);
void rasterize_model(ModelBuffer& buffer, TGAImage &framebuffer, std::vector<f64> &zbuffer);

void fill_triangle(const int width, const int height,
                   const Vector4f clip[3], TGAImage &framebuffer,
                   const RandomShader &shader,
                   std::vector<f64>& zbuffer);

#endif
