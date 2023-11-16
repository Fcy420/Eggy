#pragma once
#include <glad/glad.h>
#include "renderer.h"

typedef struct {
	const char* out_uniform;
	float near, far, FOV;
} CameraRendererComponent;

typedef struct {
	Mesh mesh;
} MeshFilterComponent;

typedef struct {
	Material material;
} MeshRendererComponent;

typedef struct {
	MeshFilterComponent* mesh_filter_components; unsigned int mesh_filter_components_size;
	MeshRendererComponent* mesh_renderer_components; unsigned int mesh_renderer_components_size;
	CameraRendererComponent* camera_renderer_components; unsigned int camera_renderer_components_size;
} NodeComponents;

void init_components(NodeComponents* components);
void update_components(NodeComponents* components);
void update_render_components(NodeComponents* components);
void destroy_components(NodeComponents* components);

typedef struct {
	const char* tag;
	vec3 position;
	vec3 rotation;
	struct Scene* scene;
	NodeComponents components;
} Node;

void init_node(Node* node, const char* tag);
void update_node(Node* node);
void destroy_node(Node* node);

void add_mesh_filter_node_component(Node* node, MeshFilterComponent component);
void add_mesh_renderer_node_component(Node* node, MeshRendererComponent component);
void add_camera_node_component(Node* node, CameraRendererComponent component);

struct Scene {
	Node* nodes;
	unsigned int node_size;
	Display* sceneView;
};

void init_scene(struct Scene* scene);
void set_display_scene(struct Scene* scene, Display* display);
void update_scene(struct Scene* scene);
void render_scene(struct Scene* scene);
void destroy_scene(struct Scene* scene);

void add_node_scene(struct Scene* scene, Node node);
Node* get_node_scene(struct Scene* scene, const char* tag);
