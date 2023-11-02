#include "scene.h"

void init_node(Node *node, const char* tag) {
	node->tag = tag;
	init_components(&node->components);
}

void update_node(Node *node) {


	update_components(&node->components);
}

void destroy_node(Node* node) {
	destroy_components(&node->components);
}

void add_mesh_filter_node_component(Node *node, MeshFilterComponent component) {
	if(node->components.mesh_filter_components_size == 0) {
		node->components.mesh_filter_components = (MeshFilterComponent*) malloc(sizeof(MeshFilterComponent));
		node->components.mesh_filter_components[0] = component;
		node->components.mesh_filter_components_size++;
	} else {
		printf("Cannot have more than one mesh filter per node!\n");	
	}
}

void add_mesh_renderer_node_component(Node *node, MeshRendererComponent component) {
	if(node->components.mesh_renderer_components_size == 0) {
		node->components.mesh_renderer_components = (MeshRendererComponent*) malloc(sizeof(MeshRendererComponent));
		node->components.mesh_renderer_components[0] = component;
		node->components.mesh_renderer_components_size++;
	} else {
		printf("Cannot have more than one mesh renderer per node!\n");
	}
}
