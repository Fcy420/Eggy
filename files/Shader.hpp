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
	inline void CompileError(unsigned int ID, const char* type) {
		GLint hasCompiled;
		char infoLog[1024];
		if(type != "PROGRAM") {
			glGetShaderiv(ID, GL_COMPILE_STATUS, &hasCompiled);
			if(hasCompiled == GL_FALSE) {
				glGetShaderInfoLog(ID, 1024, NULL, infoLog);
				std::cout << "SHADER: " << type << " ERROR: " << infoLog << "\n";
			}
		} else {
			glGetProgramiv(ID, GL_LINK_STATUS, &hasCompiled);
			if(hasCompiled == GL_FALSE) {
				glGetProgramInfoLog(ID, 1024, NULL, infoLog);
				std::cout << "PROGRAM LINK ERROR: " << infoLog << "\n";
			}
			
		}

	}

	inline void CreateShader(Shader* shader, const char* vertPath, const char* fragPath) {
		std::string vertSource;
		FileLoader::Read(vertSource, vertPath);
		const char* vertSourceS = vertSource.c_str();
		unsigned int vertShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertShader, 1, &vertSourceS, NULL);
		glCompileShader(vertShader);
		CompileError(vertShader, "VERTEX");
		std::string fragSource;
		FileLoader::Read(fragSource, fragPath);
		const char* fragSourceS = fragSource.c_str();
		unsigned int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragShader, 1, &fragSourceS, NULL);
		glCompileShader(fragShader);
		CompileError(fragShader, "FRAGMENT");
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
	
	inline void Set(Shader* shader, int val, const char* uniform) {
		Use(shader);
		glUniform1i(glGetUniformLocation(shader->ID, uniform), val);
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
	
	inline void Set(Shader* shader, glm::mat3 val, const char* uniform) {
		Use(shader);
		glUniformMatrix3fv(glGetUniformLocation(shader->ID, uniform), 1, GL_FALSE, glm::value_ptr(val));
	}

	inline void DestroyShader(Shader* shader) {
		glDeleteProgram(shader->ID);
	}
}
