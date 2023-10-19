#pragma once

#include <iostream>
#include "Shader.hpp"
#include "ShaderCollection.hpp"

#include "../libraries/glm/glm/gtc/matrix_transform.hpp"
namespace Camera {

	struct Camera {
		glm::vec3 position = glm::vec3(0);
		glm::vec3 orientation = glm::vec3(0,0,1);
		float near = 0.1f, far = 100.0f;
		float FOV = 45.0f;
		float aspect = 1.0f;
	};
	
	
	inline void UpdateCameraMatrix(Shader::Shader* shader, Camera* camera)  {
		glm::mat4 proj = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		view = glm::lookAt(camera->position, camera->position + camera->orientation, glm::vec3(0,1,0));
		proj = glm::perspective(glm::radians(camera->FOV), camera->aspect, camera->near, camera->far);
		glm::mat4 projectionMatrix = proj * view;
		Shader::Set(shader, projectionMatrix, "Projection");
	}
	inline void UpdateCameraMatrix(ShaderCollection::ShaderCollection* collection, Camera* camera)  {
		glm::mat4 proj = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		view = glm::lookAt(camera->position, camera->position + camera->orientation, glm::vec3(0,1,0));
		proj = glm::perspective(glm::radians(camera->FOV), camera->aspect, camera->near, camera->far);
		glm::mat4 projectionMatrix = proj * view;
		ShaderCollection::Set(collection, projectionMatrix, "Projection");
	}

}
