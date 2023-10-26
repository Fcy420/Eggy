#pragma once
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <memory>

#include "files/Window.hpp"
#include "files/Mesh.hpp"
#include "files/Shader.hpp"
#include "files/ShaderCollection.hpp"
#include "files/Camera.hpp"
#include "files/UI.hpp"
#include "files/ScenePreview.hpp"
#include "files/Model.hpp"
#include "files/MaterialProperty.hpp"
#include "files/Material.hpp"
#include "files/Node.hpp"
#include "files/Scene.hpp"
#include "files/CameraMovement.hpp"

namespace Eggy {

	inline void Run() {
		unsigned int width = 1280, height = 720;
		Window::Window window;
		Window::CreateWindow(&window, width, height, "Eggy - 1.1.0");
		
		Camera::Camera camera;
		camera.aspect = (float)width/height;
		camera.position = glm::vec3(0,0,-15);

		Scene::Scene scene;
		Scene::Initialize(&scene);
		Scene::Load(&scene, "Scenes/main.scn");

		UI::UI ui;
		UI::Initialize(&ui, &scene, &window);
		
		
		bool firstClick = false, resetMouse = false;
		double mouseStartX, mouseStartY;
		while(window.open) {
			
			Scene::Update(&scene, &camera, &window);
			UI::Update(&ui);

			if(Window::GetMouse(&window, 1)) {
				if(firstClick) {
					Window::GetCursorPos(&window, &mouseStartX, &mouseStartY);
					Window::SetCursorPos(&window, width/2.0f, height/2.0f);
					firstClick = false;
					resetMouse = true;
				}
				Window::SetCursor(&window, GLFW_CURSOR_HIDDEN);
				CameraMovement::MoveCamera(&camera, &window, 12.0f, 5.0f);
			} else {
				firstClick = true;
				if(resetMouse) {
					Window::SetCursorPos(&window, mouseStartX, mouseStartY);
					resetMouse = false;
				}
				Window::SetCursor(&window, GLFW_CURSOR_NORMAL);
			}

			if(Window::GetKey(&window, GLFW_KEY_ESCAPE)) {
				Window::CloseWindow(&window);
			}
			Window::PollEvents();
			Window::SwapWindowBuffers(&window);
		}
		
		Window::DestroyWindow(&window);
	}


}
