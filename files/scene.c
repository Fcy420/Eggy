#include "scene.h"

void init_scene(struct Scene *scene) {
	scene->node_size = 0;
}

void set_display_scene(struct Scene *scene, Display *display) {
	scene->sceneView = display;
}

void update_scene(struct Scene *scene) {
	for(int i = 0; i < scene->node_size; i++) {
		update_node(&scene->nodes[i]);
	}
}

void render_scene(struct Scene *scene) {
	for(int i = 0; i < scene->node_size; i++) {
		if(scene->nodes[i].components.camera_renderer_components_size > 0) {
			
		}
	}
}

void destroy_scene(struct Scene *scene) {
	for(int i = 0; i < scene->node_size; i++) {
		destroy_node(&scene->nodes[i]);
	}
	if(scene->node_size > 0) free(scene->nodes);
}

void add_node_scene(struct Scene *scene, Node node) {
	node.scene = scene;
	if(scene->node_size == 0) {
		scene->nodes = (Node*) malloc(sizeof(Node)*15);
		scene->nodes[0] = node;
	} else if(scene->node_size % 15 == 0) {
		scene->nodes = (Node*) realloc(scene->nodes, scene->node_size*sizeof(Node)*15);
		scene->nodes[scene->node_size] = node;
	} else {
		scene->nodes[scene->node_size] = node;
	}
	scene->node_size++;
}

Node* get_node_scene(struct Scene* scene, const char* tag) {
	for(int i = 0; i < scene->node_size; i++) {
		if(scene->nodes[i].tag == tag) {
			return &scene->nodes[i];
		}
	}
	return NULL;
}
