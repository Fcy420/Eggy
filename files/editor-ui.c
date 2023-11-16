#include "editor-ui.h"

void init_ui(EditorUI* ui, Window* window) {
	ui->window = window;
	ui->ctx = igCreateContext(NULL);
	ImGuiIO* ioptr = igGetIO();
	ioptr->ConfigFlags = ImGuiConfigFlags_DockingEnable;
	ImGui_ImplGlfw_InitForOpenGL(ui->window->window, true);
	const char* glsl = "#version 460";
	ImGui_ImplOpenGL3_Init(glsl);
	igStyleColorsDark(NULL);

}
void set_ui_scene(EditorUI* ui, struct Scene* scene) {
	ui->scene = scene;
}
void create_frame_ui(EditorUI *ui) {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	igNewFrame();
}

void render_frame_ui(EditorUI* ui) {
	igRender();
	ImGui_ImplOpenGL3_RenderDrawData(igGetDrawData());
}

void update_frame_ui(EditorUI* ui) {
	start_dockspace(ui);
	igBegin("Nodes", NULL, 0);
	for(int i = 0; i < ui->scene->node_size; i++) {
		if(igTreeNode_Str(ui->scene->nodes[i].tag)) {
			igTreePop();
		}
	}
	igEnd();
	igBegin("Scene View", NULL, 0);
		igGetWindowSize(&ui->currentViewSize);
		ui->currentViewSize.x -= 22;
		ui->currentViewSize.y -= 37;
		ImVec2 uv0 = {0,1};
		ImVec2 uv1 = {1,0};
		ImVec4 tint = {1,1,1,1};
		ImVec4 border = {1,1,1,1};
		igImage((ImTextureID)ui->scene->sceneView->tex, ui->currentViewSize, uv0, uv1, tint, border);
	igEnd();
	igBegin("Inspector", NULL, 0);
	igText("Dunno");	
	igEnd();
	igEnd();
}

void start_dockspace(EditorUI *ui) {
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
