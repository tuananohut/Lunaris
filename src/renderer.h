#ifndef RENDERER_H
#define RENDERER_H

#include <cmath>
#include "model.h"
#include "tgaimage.h"
#include "mathlib.h"

constexpr int width  = 1080;			  
constexpr int height = 1080;

constexpr TGAColor white   = {255, 255, 255, 255}; // attention, BGRA order
constexpr TGAColor green   = {  0, 255,   0, 255};
constexpr TGAColor red     = {  0,   0, 255, 255};
constexpr TGAColor blue    = {255, 128,  64, 255};
constexpr TGAColor yellow  = {  0, 200, 255, 255};
constexpr TGAColor pink    = {201, 145, 228, 255};
constexpr TGAColor navy    = { 61,  23,  21, 255};
constexpr TGAColor purple  = {152,  37, 152, 255};
constexpr TGAColor grey    = {233, 233, 241, 255};

void draw_line(int x1, int y1, int x2, int y2, TGAImage &framebuffer, TGAColor color);
void draw_line(Vector2 start_point, Vector2 end_point, TGAImage &framebuffer, TGAColor color);

void draw_triangle(Vector2 point1, Vector2 point2, Vector2 point3, TGAImage &framebuffer, TGAColor color);

double signed_triangle_area(Vector2 point1, Vector2 point2, Vector2 point3);
double signed_triangle_area(Vector3 point1, Vector3 point2, Vector3 point3);

Vector3 screen(const Vector3f &point); 
Vector3f translate_z(Vector3f &point3f, float dz);

void render_model(ModelBuffer& buffer, TGAImage &framebuffer, TGAColor color);
void rasterize_model(ModelBuffer& buffer, TGAImage &framebuffer, TGAImage &zbuffer);

void scanline_rendering(Vector2 point1, Vector2 point2, Vector2 point3,
			TGAImage &framebuffer, TGAColor color);

void fill_triangle(Vector2 point1, Vector2 point2, Vector2 point3,
		   TGAImage &framebuffer, TGAColor color);
void fill_triangle(Vector3 point1, Vector3 point2, Vector3 point3,
                   TGAImage &framebuffer, TGAImage& zbuffer, TGAColor color);
void fill_triangle(Vector3 point1, Vector3 point2, Vector3 point3,
		   Vector3 colorA, Vector3 colorB, Vector3 colorC, 
		   TGAImage &framebuffer);

#endif
