#include <iostream>
#include <vector>
#include "files/Window.hpp"
#include "files/Mesh.hpp"

int main() {
	Window::Window window;
	Window::CreateWindow(&window, 600, 600, "Window");
	Mesh::Mesh screenRect;
	Mesh::CreateMesh(&screenRect);
	std::vector<float> verts = {
		0,0,0,
		1,0,0,
		0,1,0,
		1,1,0,
	};
	std::vector<unsigned int> tris = {
		0,1,2,3,2,1
	};
	Mesh::MeshData(&screenRect, verts, tris);
	while(window.open) {
		Window::ClearWindow(&window);
		Mesh::RenderMesh(&screenRect);
		if(Window::GetKey(&window, GLFW_KEY_ESCAPE)) {
			Window::CloseWindow(&window);
		}
		Window::SwapWindowBuffers(&window);
	}
	Window::CloseWindow(&window);
	return 0;
}
