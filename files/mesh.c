#include "renderer.h"

void init_mesh(Mesh* mesh) {
	glGenVertexArrays(1, &mesh->vao);
	glGenBuffers(1, &mesh->vbo);
	glGenBuffers(1, &mesh->ebo);
}

void create_mesh(Mesh* mesh, float vertices[], unsigned int vertexCount, unsigned int triangles[], unsigned int triCount) {
	glBindVertexArray(mesh->vao);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertexCount, vertices, GL_STATIC_READ);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*triCount, triangles, GL_STATIC_READ);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	mesh->triCount = triCount;
}

void draw_mesh(Mesh* mesh) {
	glBindVertexArray(mesh->vao);
	glDrawElements(GL_TRIANGLES, mesh->triCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void destroy_mesh(Mesh* mesh) {
	glDeleteBuffers(1, &mesh->vbo);
	glDeleteBuffers(1, &mesh->ebo);
	glDeleteVertexArrays(1, &mesh->vao);
}
