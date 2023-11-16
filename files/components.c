#include "scene.h"

void init_components(NodeComponents* components) {
	components->mesh_filter_components_size = 0;
	components->mesh_renderer_components_size = 0;
}

void update_components(NodeComponents* components) {

}

void update_render_components(NodeComponents* components) {
	for(int i = 0; i < components->mesh_renderer_components_size; i++) {
		bind_material(&components->mesh_renderer_components[i].material);
	}
	for(int i = 0; i < components->mesh_filter_components_size; i++) {
		draw_mesh(&components->mesh_filter_components[i].mesh);
	}

}

void destroy_components(NodeComponents* components) {
	for(int i = 0; i < components->mesh_filter_components_size; i++) {
		destroy_mesh(&components->mesh_filter_components[i].mesh);
	}
	for(int i = 0; i < components->mesh_renderer_components_size; i++) {
		destroy_material(&components->mesh_renderer_components[i].material);
	}
	if(components->mesh_filter_components_size > 0) free(components->mesh_filter_components);
	if(components->mesh_renderer_components_size > 0) free(components->mesh_renderer_components);
}
