#pragma once

#include "../libraries/imgui/imgui.h"
#include "../libraries/imgui/imstb_rectpack.h"
#include "../libraries/imgui/imstb_textedit.h"
#include "../libraries/imgui/imstb_truetype.h"
#include "../libraries/imgui/imgui_impl_glfw.h"
#include "../libraries/imgui/imgui_impl_opengl3.h"
#include "Window.hpp"


namespace UI {

	inline void Initialize(Window::Window* window) {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(window->window, true);
		ImGui_ImplOpenGL3_Init("#version 460");
	}
	inline void CreateFrame() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		
		ImGui::NewFrame();
	}
	
	inline void BeginWindow(const char* title) {
		ImGui::Begin(title);	
	}
	
	inline void Text(const char* text) {
		ImGui::Text(text);
	}
	
	inline bool Button(const char* text) {
		return ImGui::Button(text);
	}
	
	inline void EndWindow() {
		ImGui::End();
	}

	inline void Render() {
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

};
