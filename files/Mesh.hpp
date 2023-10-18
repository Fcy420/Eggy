#pragma once
#include "../libraries/glad/glad.h"
#include "../libraries/glfw/include/GLFW/glfw3.h"
#include <vector>
namespace Mesh {
	struct Mesh {
		unsigned int VBO, VAO;
		std::vector<unsigned int> triangles;
	};
	inline void CreateMesh(Mesh* mesh) {
		glGenVertexArrays(1, &mesh->VAO);
		glGenBuffers(1, &mesh->VBO);
	}
	inline void MeshData(Mesh* mesh, std::vector<float> vertices, std::vector<unsigned int> triangles) {
		glBindVertexArray(mesh->VAO);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), vertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		mesh->triangles = triangles;	
	}
	inline void RenderMesh(Mesh* mesh) {
		glBindVertexArray(mesh->VAO);
		glDrawElements(GL_TRIANGLES, mesh->triangles.size(), GL_UNSIGNED_INT, mesh->triangles.data());
		glBindVertexArray(0);
	}
	inline void DestroyMesh(Mesh* mesh) {
		glDeleteVertexArrays(1, &mesh->VAO);
		glDeleteBuffers(1, &mesh->VBO);
	}
}
