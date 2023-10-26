#pragma once
#include <vector>
#include <string>

#include "Model.hpp"
#include "Shader.hpp"
#include "Material.hpp"
#include "Camera.hpp"
#include "../libraries/glm/glm/glm.hpp"
#include "../libraries/glm/glm/gtx/vector_angle.hpp"

namespace Node {
	struct Node {
		Model::Model model;
		std::string nodeTag;
		glm::vec3 position;
		glm::vec3 rotation;
		Node(std::string tag) {
			nodeTag = tag;
		}
	};
	
	inline void Update(Node* node, Camera::Camera* cam) {
		if(node->model.meshes.size() > 0) {
			glm::mat4 matrix = glm::mat4(1.0f);
			matrix = glm::translate(matrix, node->position);
			matrix = glm::rotate(matrix, glm::radians(node->rotation.x), glm::vec3(1,0,0));
			matrix = glm::rotate(matrix, glm::radians(node->rotation.y), glm::vec3(0,1,0));
			matrix = glm::rotate(matrix, glm::radians(node->rotation.z), glm::vec3(0,0,1));
			glm::mat3 normalMatrix = glm::mat3(matrix);
			normalMatrix = glm::inverse(normalMatrix);
			normalMatrix = glm::transpose(normalMatrix);
			for(auto& material : node->model.materials) {
				Shader::Set(&material.shader, matrix, "Transform");
				Shader::Set(&material.shader, normalMatrix, "NormalTransform");
				Camera::UpdateCameraMatrix(&material.shader, cam);
			}
			Model::Render(&node->model);
		}
	}

	inline void Rotate(Node* node, glm::vec3 rotation) {
		node->rotation += rotation;	
	}
	
	inline void Destroy(Node* node) {
		Model::Destroy(&node->model);
	}
}
