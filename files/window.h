#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef struct {
	GLFWwindow* window;
} Window;
void init_window(Window* window, int width, int height, const char* title);
void destroy_window(Window* window);
void flush_window(Window* window);
void swap_window(Window* window);
bool get_window_key(Window* window, int key);
void events_window();
bool window_open(Window* window);
