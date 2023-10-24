#pragma once
#include <string>
#include <iostream>

#include "../libraries/glm/glm/glm.hpp"
#include "Shader.hpp"


class MaterialProperty {
	public:
		std::string uniform;
		MaterialProperty() { }
		virtual void BindValue(Shader::Shader* shader) {}
};

class VectorProperty : public MaterialProperty {
	public:
		glm::vec3 val;
		virtual void BindValue(Shader::Shader* shader) {
			Shader::Set(shader, val, uniform.c_str());
		}
};

class FloatProperty : public MaterialProperty {
	public:
		float val;
		virtual void BindValue(Shader::Shader* shader) {
			Shader::Set(shader, val, uniform.c_str());
		}
};
