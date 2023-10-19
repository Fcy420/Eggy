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

unsigned int width = 1280, height = 720;

int main() {
	Window::Window window;
	
	Window::CreateWindow(&window, width, height, "Window");
	
	UI::Initialize(&window);
	

	while(window.open) {
		Window::ClearWindow(&window);
		UI::CreateFrame();
		UI::BeginWindow("Debugger");
		float ms;
		Window::GetFPS(&window, ms);
		UI::Text(std::string("Frame: " + std::to_string(ms) + " ms, FPS: " + std::to_string(roundf(1.0f / ms))).c_str());
		UI::Button("Button Testing!");
		UI::EndWindow();
		UI::Render();
		if(Window::GetKey(&window, GLFW_KEY_ESCAPE)) {
			Window::CloseWindow(&window);
		}
		Window::SwapWindowBuffers(&window);
	}
	
	Window::CloseWindow(&window);
	return 0;
}
