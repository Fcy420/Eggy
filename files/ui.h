#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "window.h"
#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "../libs/cimgui/cimgui.h"
#define CIMGUI_USE_GLFW
#define CIMGUI_USE_OPENGL3
#include "../libs/cimgui/cimgui_impl.h"

typedef struct {
	Window* window;
	ImGuiContext* ctx;
} UI;

void init_ui(UI* ui, Window* window);
void create_frame_ui(UI* ui);
void render_frame_ui(UI* ui);
void update_frame_ui(UI* ui);
void start_dockspace(UI* ui);
