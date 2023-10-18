cmake_minimum_required(VERSION 3.17)
project(Eggy)
add_subdirectory(libraries/glfw)
add_subdirectory(libraries/glm)
set(libIncludes 
	libraries/glad/glad.h
	libraries/glfw/include/GLFW/glfw3.h
	libraries/imgui/imconfig.h
	libraries/imgui/imgui.cpp
	libraries/imgui/imgui.h
	libraries/imgui/imgui_draw.cpp
	libraries/imgui/imgui_internal.h
	libraries/imgui/imgui_tables.cpp
	libraries/imgui/imgui_widgets.cpp
	libraries/imgui/imstb_rectpack.h
	libraries/imgui/imstb_textedit.h
	libraries/imgui/imstb_truetype.h
	libraries/imgui/imgui_impl_glfw.h
	libraries/imgui/imgui_impl_glfw.cpp
	libraries/imgui/imgui_impl_opengl3.h
	libraries/imgui/imgui_impl_opengl3.cpp
	libraries/imgui/imgui_impl_opengl3_loader.h
)
find_package(OpenGL REQUIRED)
add_executable(${PROJECT_NAME} ${libIncludes} glad.c main.cpp)
target_link_libraries(${PROJECT_NAME} OpenGL::GL dl glfw)
