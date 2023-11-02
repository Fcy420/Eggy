#include "window.h"
#include <GLFW/glfw3.h>

void init_window(Window* window, int width, int height, const char* title) {
	if(!glfwInit()) {
		printf("GLFW Failed!\n");
		return;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window->window = glfwCreateWindow(width, height, title, NULL, NULL);
	glfwMakeContextCurrent(window->window);
	gladLoadGL();
	glViewport(0,0,width,height);
}
void destroy_window(Window *window) {
	glfwDestroyWindow(window->window);
	glfwTerminate();
}
void flush_window(Window *window) {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0,0,0,1);
}
void swap_window(Window *window) {
	glfwSwapBuffers(window->window);
}
void events_window() {
	glfwPollEvents();
}
bool get_window_key(Window* window, int key) {
	return glfwGetKey(window->window, key);
}
bool window_open(Window *window) {
	return !glfwWindowShouldClose(window->window);
}
