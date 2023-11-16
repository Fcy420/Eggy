#pragma once
#include <cglm/vec4-ext.h>
#include <stdio.h>
#include <stdlib.h>
#include "files/scene.h"
#include "files/window.h"
#include "files/renderer.h"

void run_editor() {
	Window window;
	init_window(&window, 1280, 720, "Eggy - 0.1.0");

	Display display;
	init_display(&display, 1280, 720, "Shaders/display");


	struct Scene scene;
	init_scene(&scene);

	Material mat;
	init_material(&mat, "Shaders/standard");

	Mesh mesh;
	init_mesh(&mesh);
	load_mesh(&mesh, "Models/block.obj");

	Node node;
	init_node(&node, "Node");
	MeshFilterComponent filter;
	filter.mesh = mesh;
	MeshRendererComponent renderer;
	renderer.material = mat;
	add_mesh_filter_node_component(&node, filter);
	add_mesh_renderer_node_component(&node, renderer);
	add_node_scene(&scene, node);

	while(window_open(&window)) {
		flush_window(&window);

		update_scene(&scene);
		
		render_scene(&scene);

		swap_window(&window);
		events_window();
	}
	destroy_window(&window);
}
