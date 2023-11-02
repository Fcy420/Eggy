#pragma once
#include <cglm/vec4-ext.h>
#include <stdio.h>
#include <stdlib.h>
#include "files/scene.h"
#include "files/window.h"
#include "files/ui.h"
#include "files/renderer.h"

void run_editor() {
	Window window;
	init_window(&window, 1280, 720, "Eggy - 0.0.1");
	
	UI ui;
	init_ui(&ui, &window);
	Material mat;
	init_material(&mat, "Shaders/standard");

	Mesh mesh;
	init_mesh(&mesh);
	float vertices[] = {
		0,0,0,
		1,0,0,
		0,1,0,
		1,1,0
	};
	unsigned int triangles[] = {
		0,1,2,3,2,1
	};
	create_mesh(&mesh, vertices, 12, triangles, 6);

	MeshFilterComponent filterComponent;
	filterComponent.mesh = mesh;
	MeshRendererComponent renderComponent;
	renderComponent.material = mat;
	Node node;
	init_node(&node, "Body");
	add_mesh_filter_node_component(&node, filterComponent);
	add_mesh_renderer_node_component(&node, renderComponent);

	Scene scene;
	init_scene(&scene);
	add_node_scene(&scene, node);

	while(window_open(&window)) {
		flush_window(&window);
		
		update_scene(&scene);

		create_frame_ui(&ui);
		update_frame_ui(&ui);
		render_frame_ui(&ui);

		swap_window(&window);
		events_window();
	}
	destroy_scene(&scene);
	destroy_window(&window);
}
