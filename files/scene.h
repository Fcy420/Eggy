#pragma once
#include <glad/glad.h>
#include "renderer.h"

typedef struct {
	Mesh mesh;
} MeshFilterComponent;

typedef struct {
	Material material;
} MeshRendererComponent;

typedef struct {
	MeshFilterComponent* mesh_filter_components; unsigned int mesh_filter_components_size;
	MeshRendererComponent* mesh_renderer_components; unsigned int mesh_renderer_components_size;
} NodeComponents;

void init_components(NodeComponents* components);
void update_components(NodeComponents* components);
void destroy_components(NodeComponents* components);

typedef struct {
	const char* tag;
	vec3 position;
	vec3 rotation;
	NodeComponents components;
} Node;

void init_node(Node* node, const char* tag);
void update_node(Node* node);
void destroy_node(Node* node);

void add_mesh_filter_node_component(Node* node, MeshFilterComponent component);
void add_mesh_renderer_node_component(Node* node, MeshRendererComponent component);

typedef struct {
	unsigned int fbo, rbo;
	unsigned int texId;

	Node* nodes;
	unsigned int node_size;
} Scene;

void init_scene(Scene* scene);
void update_scene(Scene* scene);
void destroy_scene(Scene* scene);

void add_node_scene(Scene* scene, Node node);
Node* get_node_scene(Scene* scene, const char* tag);
