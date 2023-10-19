#pragma once	
#include "../libraries/glad/glad.h"
#include "../libraries/glm/glm/glm.hpp"
#include "../libraries/glm/glm/gtc/type_ptr.hpp"
#include "FileLoader.hpp"

#include <string>


namespace Shader {
	struct Shader {
		unsigned int ID;
	};
	inline void CreateShader(Shader* shader, const char* vertPath, const char* fragPath) {
		std::string vertSource;
		FileLoader::Read(vertSource, vertPath);
		const char* vertSourceS = vertSource.c_str();
		unsigned int vertShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertShader, 1, &vertSourceS, NULL);
		glCompileShader(vertShader);
		std::string fragSource;
		FileLoader::Read(fragSource, fragPath);
		const char* fragSourceS = fragSource.c_str();
		unsigned int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragShader, 1, &fragSourceS, NULL);
		glCompileShader(fragShader);
		shader->ID = glCreateProgram();
		glAttachShader(shader->ID, vertShader);
		glAttachShader(shader->ID, fragShader);
		glLinkProgram(shader->ID);
		glDeleteShader(vertShader);
		glDeleteShader(fragShader);
	}
	
	inline void Use(Shader* shader) {
		glUseProgram(shader->ID);
	}

	inline void Set(Shader* shader, float val, const char* uniform) {
		Use(shader);
		glUniform1f(glGetUniformLocation(shader->ID, uniform), val);
	}
	
	inline void Set(Shader* shader, glm::vec3 val, const char* uniform) {
		Use(shader);
		glUniform3fv(glGetUniformLocation(shader->ID, uniform), 1, glm::value_ptr(val));
	}

	inline void Set(Shader* shader, glm::mat4 val, const char* uniform) {
		Use(shader);
		glUniformMatrix4fv(glGetUniformLocation(shader->ID, uniform), 1, GL_FALSE, glm::value_ptr(val));
	}

	inline void DestroyShader(Shader* shader) {
		glDeleteProgram(shader->ID);
	}
}
