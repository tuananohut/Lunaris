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

void draw_line(Vector3 start_point, Vector3 end_point, TGAImage &framebuffer, TGAColor color);

void draw_triangle(Vector3 point1, Vector3 point2, Vector3 point3, TGAImage &framebuffer, TGAColor color);

void render_model(ModelBuffer& buffer, TGAImage &framebuffer, TGAColor color);
void rasterize_model(ModelBuffer& buffer, TGAImage &framebuffer, TGAImage &zbuffer);


void fill_triangle(const int width, const int height,
                   const Vector4 clip[3], TGAImage &framebuffer,
                   std::vector<f64> &zbuffer, TGAColor color);

/* void fill_triangle(Vector3 point1, Vector3 point2, Vector3 point3,
   TGAImage &framebuffer, TGAImage& zbuffer, TGAColor color); */

#endif
