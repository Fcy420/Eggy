#pragma once
#include "../libraries/glad/glad.h"
#include "../libraries/glfw/include/GLFW/glfw3.h"
#include <vector>
namespace Eggy {
	struct Mesh {
		unsigned int VBO, VAO, EBO, triCount;
	};
	inline void CreateMesh(Mesh* mesh) {
		glGenVertexArrays(1, &mesh->VAO);
		glGenBuffers(1, &mesh->VBO);
		glGenBuffers(1, &mesh->EBO);
	}
	inline void MeshData(Mesh* mesh, std::vector<float> vertices, std::vector<unsigned int> triangles) {
		glBindVertexArray(mesh->VAO);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), vertices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles.size()*sizeof(unsigned int), triangles.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, (void*)(sizeof(float)*3));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		mesh->triCount = triangles.size();
	}
	inline void RenderMesh(Mesh* mesh) {
		glBindVertexArray(mesh->VAO);
		glDrawElements(GL_TRIANGLES, mesh->triCount, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
	inline void DestroyMesh(Mesh* mesh) {
		glDeleteVertexArrays(1, &mesh->VAO);
		glDeleteBuffers(1, &mesh->VBO);
		glDeleteBuffers(1, &mesh->EBO);
	}
}
