#pragma once
#include <vector>
#include "Shader.hpp"
namespace ShaderCollection {
	struct ShaderCollection {
		std::vector<Shader::Shader*> shaders;
	};
	inline void AddShader(ShaderCollection& shaderCollection, Shader::Shader* shader) {
		shaderCollection.shaders.push_back(shader);
	}
}
