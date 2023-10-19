#pragma once
#include "../libraries/glad/glad.h"
#include "../libraries/glfw/include/GLFW/glfw3.h"

namespace Window {
	struct Window {
		GLFWwindow* window = nullptr;
		bool open = false;
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
		glClearColor(1,1,1,1);
	}
	inline void SwapWindowBuffers(Window* window) {
		glfwSwapBuffers(window->window);
		glfwPollEvents();
	}
	inline void CloseWindow(Window* window) {
		window->open = false;
		glfwDestroyWindow(window->window);
		glfwTerminate();
	}
	inline double lastFrame = 0.0;
	inline void GetFPS(Window* window, float& delta) {
		double curTime = glfwGetTime();
		delta = curTime - lastFrame;
		lastFrame = curTime;
		
	}
}
