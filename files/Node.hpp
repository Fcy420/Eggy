#pragma once
#include <vector>
#include <string>

#include "Model.hpp"
#include "Shader.hpp"
#include "Material.hpp"
#include "Camera.hpp"
#include "../libraries/glm/glm/glm.hpp"
#include "../libraries/glm/glm/gtx/vector_angle.hpp"

namespace Eggy {
	struct Node {
		Eggy::Model model;
		std::string nodeTag;
		glm::vec3 position;
		glm::vec3 rotation;
		Node(std::string tag) {
			nodeTag = tag;
		}
	};
	
	inline void UpdateNode(Node* node, Eggy::Camera* cam) {
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
				Eggy::SetUniform(&material.shader, matrix, "Transform");
				Eggy::SetUniform(&material.shader, normalMatrix, "NormalTransform");
				Eggy::UpdateCameraMatrix(&material.shader, cam);
			}
			Eggy::RenderModel(&node->model);
		}
	}

	inline void RotateNode(Node* node, glm::vec3 rotation) {
		node->rotation += rotation;	
	}
	
	inline void DestroyNode(Node* node) {
		Eggy::DestroyModel(&node->model);
	}
}
