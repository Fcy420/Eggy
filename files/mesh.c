#include "renderer.h"

void init_mesh(Mesh* mesh) {
	glGenVertexArrays(1, &mesh->vao);
	glGenBuffers(1, &mesh->vbo);
	glGenBuffers(1, &mesh->ebo);
}

void create_mesh(Mesh* mesh, float vertices[], unsigned int vertexCount, unsigned int triangles[], unsigned int triCount) {
	glBindVertexArray(mesh->vao);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertexCount*8, vertices, GL_STATIC_READ);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*triCount, triangles, GL_STATIC_READ);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*8, (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	mesh->triCount = triCount;
}

void load_mesh(Mesh *mesh, const char *path) {
	FILE* file = fopen(path, "r");
	if(file == NULL) {
		printf("File not found!\n");
		return;
	}
	float* vertices = (float*)malloc(0);
	unsigned int vertex_length = 0;
	float* uvs = (float*)malloc(0);
	unsigned int uvs_length = 0;
	float* normals = (float*)malloc(0);
	unsigned int normal_length = 0;

	unsigned int* vertex_indices = (unsigned int*)malloc(0);
	unsigned int* uv_indices = (unsigned int*)malloc(0);
	unsigned int* normal_indices = (unsigned int*)malloc(0);
	unsigned int added_indices = 0;
	while(1) {
		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		if(res == EOF)
			break;
		if(strcmp(lineHeader, "v") == 0) {
			vec3 vert;
			fscanf(file, "%f %f %f\n", &vert[0], &vert[1], &vert[2]);
			vertices = (float*)realloc(vertices, sizeof(float)*(vertex_length+3));
			for(int i = 0; i < 3; i++) {
				vertices[vertex_length+i] = vert[i];
			}
			vertex_length += 3;
		} else if(strcmp(lineHeader, "vt") == 0) {
			vec2 uv;
			fscanf(file, "%f %f\n", &uv[0], &uv[1]);
			uvs = (float*)realloc(uvs, sizeof(float)*(uvs_length+2));
			for(int i = 0; i < 2; i++) {
				uvs[uvs_length+i] = uv[i];
			}
			uvs_length += 2;
		} else if(strcmp(lineHeader, "vn") == 0) {
			vec3 normal;
			fscanf(file, "%f %f %f\n", &normal[0], &normal[1], &normal[2]);
			normals = (float*)realloc(normals, sizeof(float)*(normal_length+3));
			for(int i = 0; i < 3; i++) {
				normals[normal_length+i] = normal[i];
			}
			normal_length += 3;
		} else if(strcmp(lineHeader, "f") == 0) {
			unsigned int vertex_index[3], uv_index[3], normal_index[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertex_index[0], &uv_index[0], &normal_index[0], &vertex_index[1], &uv_index[1], &normal_index[1], &vertex_index[2], &uv_index[2], &normal_index[2]);
			if(matches != 9) {
				printf("Boooo, Not good triangles!\n");
				return;
			}
			vertex_indices = (unsigned int*)realloc(vertex_indices, (added_indices+3)*sizeof(unsigned int));	
			uv_indices = (unsigned int*)realloc(uv_indices, (added_indices+3)*sizeof(unsigned int));
			normal_indices = (unsigned int*)realloc(normal_indices, (added_indices+3)*sizeof(unsigned int));
			for(int i = 0; i < 3; i++) {
				vertex_indices[added_indices+i] = vertex_index[i];
				normal_indices[added_indices+i] = normal_index[i];
				uv_indices[added_indices+i] = uv_index[i];
			}
			added_indices += 3;
		}
	}

	float* out_vertices = (float*)malloc(sizeof(float)*((vertex_length/3)*8));
	unsigned int length = (vertex_length/3)*8;
	unsigned int* out_triangles = (unsigned int*)malloc(sizeof(unsigned int)*(added_indices));
	int stride = 0;
	for(int i = 0; i < added_indices; i += 3) {
		vec3 vert = {vertices[vertex_indices[i]-1], vertices[vertex_indices[i]], vertices[vertex_indices[i]+1]};
		vec3 norm = {normals[normal_indices[i]-1], normals[normal_indices[i]], normals[normal_indices[i]+1]};
		vec2 uv = {uvs[uv_indices[i]-1], uvs[uv_indices[i]]};
		out_vertices[stride] = vert[0];
		out_vertices[stride+1] = vert[1];
		out_vertices[stride+2] = vert[2];
		out_vertices[stride+3] = norm[0];
		out_vertices[stride+4] = norm[1];
		out_vertices[stride+5] = norm[2];
		out_vertices[stride+6] = uv[0];
		out_vertices[stride+7] = uv[1];
		printf("%f,%f,%f,%f,%f,%f,%f,%f\n", out_vertices[stride], out_vertices[stride+1], out_vertices[stride+2], out_vertices[stride+3], out_vertices[stride+4], out_vertices[stride+5], out_vertices[stride+6], out_vertices[stride+7]);

		stride += 8;
		out_triangles[i] = vertex_indices[i]-1;
		out_triangles[i+1] = vertex_indices[i+1]-1;
		out_triangles[i+2] = vertex_indices[i+2]-1;
		printf("%d,%d,%d\n", vertex_indices[i]-1, vertex_indices[i+1]-1,vertex_indices[i+2]-1);
	}
	create_mesh(mesh, out_vertices, length, out_triangles, added_indices);
	free(out_vertices);
	free(out_triangles);
	free(vertex_indices);
	free(normal_indices);
	free(uv_indices);
	free(vertices);
	free(normals);
	free(uvs);
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
