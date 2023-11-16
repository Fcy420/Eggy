#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "window.h"
#include "scene.h"
#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "../libs/cimgui/cimgui.h"
#define CIMGUI_USE_GLFW
#define CIMGUI_USE_OPENGL3
#include "../libs/cimgui/cimgui_impl.h"

typedef struct {
	Window* window;
	struct Scene* scene;
	ImGuiContext* ctx;
	ImVec2 currentViewSize;
} EditorUI;

void init_ui(EditorUI* ui, Window* window);
void set_ui_scene(EditorUI* ui, struct Scene* scene);
void create_frame_ui(EditorUI* ui);
void render_frame_ui(EditorUI* ui);
void update_frame_ui(EditorUI* ui);
void start_dockspace(EditorUI* ui);
