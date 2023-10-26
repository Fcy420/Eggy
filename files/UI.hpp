#pragma once
#include <string>

#include "../libraries/imgui/imgui.h"
#include "../libraries/imgui/backends/imgui_impl_opengl3.h"
#include "../libraries/imgui/backends/imgui_impl_glfw.h"

#include "Material.hpp"
#include "Window.hpp"
#include "Scene.hpp"


namespace UI {
	
	struct UI {
		std::vector<std::string> logs;
		Scene::Scene* scene;
		Window::Window* window;
	};

	inline void Initialize(UI* ui, Scene::Scene* scene, Window::Window* window) {
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; 
		ImGui::StyleColorsDark();
		ui->scene = scene;
		ui->window = window;

		ImGui_ImplGlfw_InitForOpenGL(window->window, true);
		ImGui_ImplOpenGL3_Init("#version 430");
	}
	inline void CreateFrame(UI* ui) {
		Window::ClearWindow(ui->window);
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		
		ImGui::NewFrame();
		bool t = false;
		ImGuiViewport* viewport = ImGui::GetWindowViewport();
		ImGuiWindowFlags mainFlags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_MenuBar;
		ImGui::SetNextWindowPos(ImVec2(0,0));
		ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, viewport->Size.y));
		ImGui::Begin("DockSpace", &t, mainFlags);
		ImGui::DockSpace(ImGui::GetID("Dockspace"), ImVec2(0,0), ImGuiDockNodeFlags_PassthruCentralNode);
		if(ImGui::BeginMenuBar()) {
			if(ImGui::BeginMenu("File")) {
				if(ImGui::MenuItem("Load Model")) {
					ImGui::OpenPopup("Model_loading");	
				}
				if(ImGui::MenuItem("Close")) {
					Window::CloseWindow(ui->window);
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		if(ImGui::BeginPopupModal("Model_loading")) {
			ImGui::Text("Test");
			ImGui::EndPopup();
		}	
		
		ImGui::Begin("Scene Preview");
		ImVec2 size = ImGui::GetWindowSize();
		ImGui::Image(ImTextureID(ui->scene->tex), ImVec2(size.x-15,size.y-35), ImVec2(0,1), ImVec2(1,0));
		ImGui::End();
		
		ImGui::Begin("Scene");
		for(auto& node : ui->scene->nodes) {
			if(ImGui::TreeNode(node.nodeTag.c_str())) {
				ImGui::TreePop();
			}
		}

		ImGui::End();

		ImGui::Begin("Debugger");
		ImGui::BeginChild("DebugLogs");
		for(auto& log : ui->logs) {
			ImGui::TextUnformatted(log.c_str());
		}
		ImGui::EndChild();
		ImGui::End();

		ImGui::Begin("Inspector");

		ImGui::End();
		
		ImGui::End();
	}
	

	inline void Render() {
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	inline void Update(UI* ui) {
		CreateFrame(ui);
		Render();
	}
	
	inline void Log(UI* ui, std::string log) {
		ui->logs.push_back(log);
	}

};
