#include "renderer.h"


void init_material(Material* mat, const char* shader_path) {
	const char* vert_attachment = "/vert.glsl";
	const char* frag_attachment = "/frag.glsl";
	char* vert_path;
	vert_path = malloc(strlen(shader_path)+strlen(vert_attachment)+1);
	strcpy(vert_path, shader_path);
	strcat(vert_path, vert_attachment);
	char* frag_path;
	frag_path = malloc(strlen(shader_path)+strlen(frag_attachment)+1);
	strcpy(frag_path, shader_path);
	strcat(frag_path, frag_attachment);
	init_shader(&mat->shader, vert_path, frag_path);
	free(frag_path);
	free(vert_path);

	mat->components.float_components_size = 0;
	mat->components.vec4_components_size = 0;
}

void bind_material(Material* mat) {
	use_shader(&mat->shader);
	for(int i = 0; i < mat->components.float_components_size; i++) {
		set_shader_float(&mat->shader, mat->components.float_components[i].uniform, mat->components.float_components[i].val);
	}
	for(int i = 0; i < mat->components.vec4_components_size; i++) {
		set_shader_vec4(&mat->shader, mat->components.vec4_components[i].uniform, mat->components.vec4_components[i].val);
	}
}

void add_float_material_component(Material* mat, FloatComponent component) {
	if(mat->components.float_components_size == 0) {
		mat->components.float_components = (FloatComponent*) malloc(sizeof(FloatComponent)*15);
		mat->components.float_components[0] = component;
	} else if(mat->components.float_components_size % 15 == 0) {
		mat->components.float_components = (FloatComponent*) realloc(mat->components.float_components, (mat->components.float_components_size+15)*sizeof(FloatComponent));
		mat->components.float_components[mat->components.float_components_size] = component;
	} else {
		mat->components.float_components[mat->components.float_components_size] = component;
	}
	mat->components.float_components_size++;
}

void add_vec4_material_component(Material *mat, Vec4Component component) {
	if(mat->components.vec4_components_size == 0) {
		mat->components.vec4_components = (Vec4Component*) malloc(sizeof(Vec4Component)*15);
		mat->components.vec4_components[0] = component;
	} else if(mat->components.vec4_components_size % 15 == 0) {
		mat->components.vec4_components = (Vec4Component*) realloc(mat->components.vec4_components, (mat->components.vec4_components_size+15)*sizeof(Vec4Component));
		mat->components.vec4_components[mat->components.vec4_components_size] = component;
	} else {
		mat->components.vec4_components[mat->components.vec4_components_size] = component;
	}
	mat->components.vec4_components_size++;
}

void destroy_material(Material* mat) {
	if(mat->components.float_components_size > 0) free(mat->components.float_components);
	if(mat->components.vec4_components_size > 0) free(mat->components.vec4_components);
	destroy_shader(&mat->shader);
}
