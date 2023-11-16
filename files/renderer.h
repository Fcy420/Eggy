#pragma once
#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <cglm/vec3.h>
#include <cglm/vec3.h>
#include <cglm/mat4.h>
#include <cglm/types.h>

#include "window.h"

typedef struct {
	unsigned int vao, vbo, ebo;
	unsigned int triCount;
} Mesh;

void init_mesh(Mesh* mesh);
void create_mesh(Mesh* mesh, float vertices[], unsigned int vertexCount, unsigned int triangles[], unsigned int triCount);
void load_mesh(Mesh* mesh, const char* path);
void draw_mesh(Mesh* mesh);
void destroy_mesh(Mesh* mesh);


typedef struct {
	unsigned int program;
} Shader;

void init_shader(Shader* shader, const char* vert, const char* frag);
void use_shader(Shader* shader);
void set_shader_int(Shader* shader, const char* uniform, int val);
void set_shader_float(Shader* shader, const char* uniform, float val);
void set_shader_vec4(Shader* shader, const char* uniform, vec4 val);
void set_shader_mat4(Shader* shader, const char* uniform, mat4 val);
void destroy_shader(Shader* shader);

typedef struct {
	const char* uniform;
	float val;
} FloatComponent;

typedef struct {
	const char* uniform;
	vec4 val;
} Vec4Component;

typedef struct {
	FloatComponent* float_components;
	unsigned int float_components_size;
	Vec4Component* vec4_components;
	unsigned int vec4_components_size;
} MaterialComponents;

typedef struct {
	Shader shader;
	MaterialComponents components;
} Material;

void init_material(Material* mat, const char* shader_path);
void bind_material(Material* mat);
void add_float_material_component(Material* mat, FloatComponent component);
void add_vec4_material_component(Material* mat, Vec4Component component);
void destroy_material(Material* mat);

typedef struct {
	unsigned int fbo, rbo, tex;
	unsigned int width, height;
	Material material;
	Mesh mesh;
} Display;

void init_display(Display* display, int width, int height, const char* shader);
void bind_display(Display* display);
void unbind_displays();
void view_display(Display* display);
void destroy_display(Display* display);
