cmake_minimum_required(VERSION 3.17)
project(Eggy)
set(BUILD_SHARED_LIBS ON)
add_subdirectory(libs/cimgui)
add_subdirectory(libs/cglm)

set(SOURCES
	files/window.c
	files/mesh.c
	files/shader.c
	files/editor-ui.c
	files/material.c
	files/node.c
	files/scene.c
	files/components.c
	files/display.c
)
set(HEADERS 
	libs/tinyobj/tinyobj_loader_c.h
)

#GLFW
set(GLFW_VERSION 3.3.8)
include(FetchContent)
	FetchContent_Declare(
    glfw
    URL https://github.com/glfw/glfw/archive/refs/tags/${GLFW_VERSION}.tar.gz)

FetchContent_GetProperties(glfw)
if (NOT glfw_POPULATED)
	set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(glfw)
	set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
	set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
	add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()

#cimgui for backends
set(cimgui_backend_sources
	libs/cimgui/imgui/backends/imgui_impl_glfw.cpp
	libs/cimgui/imgui/backends/imgui_impl_opengl3.cpp
)




find_package(OpenGL REQUIRED)
add_executable(${PROJECT_NAME} ${SOURCES} ${cimgui_backend_sources} glad.c main.c)
target_link_libraries(${PROJECT_NAME} OpenGL::GL glfw cimgui cglm)
