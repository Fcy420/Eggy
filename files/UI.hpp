#pragma once

#include "../libraries/imgui/imgui.h"
#include "../libraries/imgui/backends/imgui_impl_opengl3.h"
#include "../libraries/imgui/backends/imgui_impl_glfw.h"

#include "Window.hpp"
#include "Scene.hpp"


namespace UI {

	inline void Initialize(Window::Window* window) {
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; 
		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(window->window, true);
		ImGui_ImplOpenGL3_Init("#version 430");
	}
	inline void CreateFrame(Scene::Scene* scene, Window::Window* window) {
		Window::ClearWindow(window);
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		
		ImGui::NewFrame();
		bool t = false;
		ImGuiViewport* viewport = ImGui::GetWindowViewport();
		ImGui::Begin("Docker", &t, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking);
		ImGui::SetWindowSize(ImVec2(viewport->Size.x, viewport->Size.y));
		ImGui::SetWindowPos(ImVec2(0,0));
		if(ImGui::BeginMenuBar()) {
			if(ImGui::BeginMenu("File")) {
				if(ImGui::MenuItem("Open")) {
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		ImGui::BeginChild("Game Render");
		ImGui::Image(ImTextureID(scene->tex), ImVec2(800,500), ImVec2(0,1), ImVec2(1,0));
		ImGui::EndChild();
		ImGui::End();
	}
	

	inline void Render() {
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	inline void Update(Scene::Scene* scene, Window::Window* window) {
		CreateFrame(scene, window);
		Render();
	}

};
