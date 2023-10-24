#pragma once

#include "../libraries/glm/glm/glm.hpp"
#include "../libraries/glm/glm/gtx/vector_angle.hpp"
#include "Camera.hpp"
#include "Window.hpp"


namespace CameraMovement {

	inline void MoveCamera(Camera::Camera* camera, Window::Window* window, float speed, float sensetivity) {
		
		glm::vec3 moveVector;
		float delta; Window::GetFPS(window, delta);
		
		if(Window::GetKey(window, GLFW_KEY_W)) {
			moveVector += camera->orientation * speed * delta;
		}
		if(Window::GetKey(window, GLFW_KEY_S)) {
			moveVector -= camera->orientation * speed * delta;
		}
		if(Window::GetKey(window, GLFW_KEY_D)) {
			moveVector += glm::normalize(glm::cross(camera->orientation, glm::vec3(0,1,0))) * speed * delta;
		}
		if(Window::GetKey(window, GLFW_KEY_A)) {
			moveVector -= glm::normalize(glm::cross(camera->orientation, glm::vec3(0,1,0))) * speed * delta;
		}
		if(Window::GetKey(window, GLFW_KEY_SPACE)) {
			moveVector += glm::vec3(0,1,0) * speed * delta;
		}
		if(Window::GetKey(window, GLFW_KEY_LEFT_SHIFT)) {
			moveVector -= glm::vec3(0,1,0) * speed * delta;
		}
		camera->position += moveVector;

		double mouseX, mouseY;
		Window::GetCursorPos(window, &mouseX, &mouseY);

		int screenWidth, screenHeight;
		
		Window::GetWindowSize(window, &screenWidth, &screenHeight);
			
		float rotX = sensetivity * delta * (mouseY - (screenHeight/2.0f));
		float rotY = sensetivity * delta * (mouseX - (screenWidth/2.0f));
		
		glm::vec3 newRot = glm::rotate(camera->orientation, glm::radians(-rotX), glm::normalize(glm::cross(camera->orientation, glm::vec3(0,1,0))));
		if(std::abs(glm::angle(newRot, glm::vec3(0,1,0)) - glm::radians(90.0f) <= glm::radians(85.0f))) {
			camera->orientation = newRot;
		}
		camera->orientation = glm::rotate(camera->orientation, glm::radians(-rotY), glm::vec3(0,1,0));
		Window::SetCursorPos(window, screenWidth/2.0f, screenHeight/2.0f);
	}


}
