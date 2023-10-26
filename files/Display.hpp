#pragma once
#include <vector>
#include "../libraries/glad/glad.h"
#include "Shader.hpp"
#include "Scene.hpp"

namespace Display {
	struct Display {
		Shader::Shader screenShader;
		unsigned int vao, vbo;
		std::vector<unsigned int> tris;
	};
	inline void Initialize(Display* display) {
		Shader::CreateShader(&display->screenShader, "Shaders/screen/vert.glsl", "Shaders/screen/frag.glsl");
		std::vector<float> verts = {
			-1,-1,0, 0,0,
			1,-1,0, 1,0,
			-1,1,0, 0,1,
			1,1,0, 1,1
		};
		std::vector<unsigned int> tris = {
			0,1,2,3,2,1
		};

		unsigned int VAO, VBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, verts.size()*sizeof(float), verts.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*5, (void*)0);
		glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(float)*5,(void*)(sizeof(float)*3));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		display->vao = VAO;
		display->vbo = VBO;
		display->tris = tris;
	}
	
	inline void Show(Display* display, Scene::Scene* scene) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, scene->tex);
		Shader::Set(&display->screenShader, 0, "tex0");
		glBindVertexArray(display->vao);
		glDrawElements(GL_TRIANGLES, display->tris.size(), GL_UNSIGNED_INT, display->tris.data());
		glBindVertexArray(0);
		Shader::Use(nullptr);
	}



	inline void Destroy(Display* display) {
		glDeleteBuffers(1, &display->vbo);
		glDeleteVertexArrays(1, &display->vao);
		Shader::DestroyShader(&display->screenShader);
	}


}
