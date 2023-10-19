#pragma once
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <dlfcn.h>
#include <stdlib.h>

#include "files/Window.hpp"
#include "files/Mesh.hpp"
#include "files/Shader.hpp"
#include "files/ShaderCollection.hpp"
#include "files/Camera.hpp"
#include "files/UI.hpp"
#include "libraries/glfw/include/GLFW/glfw3.h"

namespace Eggy {

	inline void Run() {
		unsigned int width = 1280, height = 720;
		Window::Window window;
		Window::CreateWindow(&window, width, height, "Eggy - 1.0.0");
		
		while(window.open) {
			Window::ClearWindow(&window);
			
			if(Window::GetKey(&window, GLFW_KEY_ESCAPE)) {
				Window::CloseWindow(&window);
			}

			Window::SwapWindowBuffers(&window);
		}
		Window::CloseWindow(&window);
	}


}
