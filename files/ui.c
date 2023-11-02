#include "ui.h"

void init_ui(UI* ui, Window* window) {
	ui->window = window;
	ui->ctx = igCreateContext(NULL);
	ImGuiIO* ioptr = igGetIO();
	ioptr->ConfigFlags = ImGuiConfigFlags_DockingEnable;
	ImGui_ImplGlfw_InitForOpenGL(ui->window->window, true);
	const char* glsl = "#version 460";
	ImGui_ImplOpenGL3_Init(glsl);
	igStyleColorsDark(NULL);

}
void create_frame_ui(UI *ui) {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	igNewFrame();
}

void render_frame_ui(UI* ui) {
	igRender();
	ImGui_ImplOpenGL3_RenderDrawData(igGetDrawData());
}

void update_frame_ui(UI* ui) {
	start_dockspace(ui);
	igEnd();
}

void start_dockspace(UI *ui) {
	ImGuiViewport* viewport = igGetMainViewport();
	ImGuiWindowFlags window_flags = 0;
	window_flags = ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoDocking;
	igBegin("Dockspace", NULL, window_flags);
	ImGuiIO* io = igGetIO();
	ImGuiID dockId = igGetID_Str("Dockspace");
	ImVec2 dockSize;
	dockSize.x = 0;
	dockSize.y = 0;
	igDockSpace(dockId, dockSize, ImGuiDockNodeFlags_PassthruCentralNode, NULL);
	igSetWindowSize_Vec2(viewport->Size, ImGuiCond_None);
	igSetWindowPos_Vec2(viewport->Pos, ImGuiCond_None);
	if(igBeginMenuBar()) {
		if(igBeginMenu("File", true)) {
			if(igMenuItem_Bool("Information", NULL, false, true)) {
				
			}
			igEndMenu();	
		}
		igEndMenuBar();
	}
}
