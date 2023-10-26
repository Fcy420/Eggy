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
#include "files/Display.hpp"

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
	
		Display::Display display;
		Display::Initialize(&display);
				

		bool firstClick = false, resetMouse = false;
		double mouseStartX, mouseStartY;
		while(window.open) {
			
			Scene::Update(&scene, &camera, &window);
		
			Display::Show(&display, &scene);
			
			if(Window::GetKey(&window, GLFW_KEY_ESCAPE)) {
				Window::CloseWindow(&window);
			}
			Window::PollEvents();
			Window::SwapWindowBuffers(&window);
		}
		
		Display::Destroy(&display);
		Scene::Destroy(&scene);
		Window::DestroyWindow(&window);
	}


}
