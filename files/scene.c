#include "scene.h"

void init_scene(Scene *scene) {
	scene->node_size = 0;	
}

void update_scene(Scene *scene) {
	for(int i = 0; i < scene->node_size; i++) {
		update_node(&scene->nodes[i]);
	}
}

void destroy_scene(Scene *scene) {
	for(int i = 0; i < scene->node_size; i++) {
		destroy_node(&scene->nodes[i]);
	}
	if(scene->node_size > 0) free(scene->nodes);
}

void add_node_scene(Scene *scene, Node node) {
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

Node* get_node_scene(Scene* scene, const char* tag) {
	for(int i = 0; i < scene->node_size; i++) {
		if(scene->nodes[i].tag == tag) {
			return &scene->nodes[i];
		}
	}
	return NULL;
}
