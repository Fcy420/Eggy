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
#include "files/Camera.hpp"
#include "files/UI.hpp"
#include "files/Model.hpp"
#include "files/MaterialProperty.hpp"
#include "files/Material.hpp"
#include "files/Node.hpp"
#include "files/Scene.hpp"
#include "files/Display.hpp"

namespace Eggy {

	inline void RunEditor() {
		unsigned int width = 1280, height = 720;
		Eggy::Window window;
		Eggy::CreateWindow(&window, width, height, "Eggy - 1.1.0");
		
		Eggy::Camera camera;
		camera.aspect = (float)width/height;
		camera.position = glm::vec3(0,0,-15);

		Eggy::Scene scene;
		Eggy::InitializeScene(&scene);
		Eggy::LoadScene(&scene, "Scenes/main.scn");

		Eggy::UI ui;
		Eggy::InitializeUI(&ui, &scene, &window);

		bool firstClick = false, resetMouse = false;
		double mouseStartX, mouseStartY;
		while(window.open) {
			
			Eggy::UpdateScene(&scene, &camera, &window);
			Eggy::UpdateUI(&ui);
			
			if(Eggy::GetKey(&window, GLFW_KEY_ESCAPE)) {
				Eggy::CloseWindow(&window);
			}
			Eggy::PollEvents();
			Eggy::SwapWindowBuffers(&window);
		}
		
		Eggy::DestroyScene(&scene);
		Eggy::DestroyWindow(&window);
	}


}
