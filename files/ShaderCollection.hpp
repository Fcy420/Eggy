#pragma once
#include <vector>
#include "Shader.hpp"
namespace ShaderCollection {
	struct ShaderCollection {
		std::vector<Shader::Shader*> shaders;
	};
	inline void AddShader(ShaderCollection* shaderCollection, Shader::Shader* shader) {
		shaderCollection->shaders.push_back(shader);
	}
	inline void Set(ShaderCollection* shaderCollection, float val, const char* uniform) {
		for(auto &s : shaderCollection->shaders) {
			Shader::Set(s, val, uniform);
		}
	}
	inline void Set(ShaderCollection* shaderCollection, glm::vec3 val, const char* uniform) {
		for(auto &s : shaderCollection->shaders) {
			Shader::Set(s, val, uniform);
		}
	}
	inline void Set(ShaderCollection* shaderCollection, glm::mat4 val, const char* uniform) {
		for(auto &s : shaderCollection->shaders) {
			Shader::Set(s, val, uniform);
		}
	}

}
