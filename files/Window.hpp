#pragma once
#include "../libraries/glad/glad.h"
#include "../libraries/glfw/include/GLFW/glfw3.h"

namespace Eggy {
	struct Window {
		GLFWwindow* window = nullptr;
		bool open = false;
		double lastFrame = 0.0;
	};
	
	inline void CreateWindow(Window* window, int width, int height, const char* name) {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		window->window = glfwCreateWindow(width, height, name, NULL, NULL);
		window->open = true;
		glfwMakeContextCurrent(window->window);
		gladLoadGL();
		glViewport(0,0,width,height);
		glEnable(GL_DEPTH_TEST);
	}
	inline bool GetKey(Window* window, int key) {
		return glfwGetKey(window->window, key);
	}
	inline void ClearWindow(Window* window) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1,0.1,0.1,1);
	}
	inline void SwapWindowBuffers(Window* window) {
		window->open = !glfwWindowShouldClose(window->window);
		glfwSwapBuffers(window->window);
	}
	inline void PollEvents() {
		glfwPollEvents();
	}
	inline void CloseWindow(Window* window) {
		glfwSetWindowShouldClose(window->window, 1);
	}
	inline void DestroyWindow(Window* window) {
		glfwDestroyWindow(window->window);
		glfwTerminate();
	}
	inline void GetFPS(Window* window, float& delta) {
		double curTime = glfwGetTime();
		delta = curTime - window->lastFrame;
		window->lastFrame = curTime;
	}
	inline void SetCursorPos(Window* window, float x, float y) {
		glfwSetCursorPos(window->window, x, y);
	}
	inline void GetCursorPos(Window* window, double* x, double* y) {
		glfwGetCursorPos(window->window, x, y);	
	}
	inline void GetWindowSize(Window* window, int* width, int* height) {
		glfwGetWindowSize(window->window, width, height);
	}
	inline void SetCursor(Window* window, int cursorMode) {
		glfwSetInputMode(window->window, GLFW_CURSOR, cursorMode);
	}
	inline bool GetMouse(Window* window, int button) {
		return glfwGetMouseButton(window->window, button);
	}
}
