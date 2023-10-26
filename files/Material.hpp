#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <string>

#include "Shader.hpp"
#include "MaterialProperty.hpp"
#include "FileLoader.hpp"
#include "StringHelper.hpp"

namespace Material {
	struct Material {
		Shader::Shader shader;
		std::vector<std::shared_ptr<MaterialProperty>> properties;
	};


	inline void AddProperty(Material* mat, MaterialProperty* prop) {
		mat->properties.emplace_back(prop);
	}

	inline void Shader(Material* mat, Shader::Shader shader) {
		mat->shader = shader;
	}	

	inline void Bind(Material* mat) {
		Shader::Use(&mat->shader);
		for(auto& prop : mat->properties) {
			prop.get()->BindValue(&mat->shader);
		}
	}

	inline bool Load(Material* mat, const char* path) {
		std::string fileContent;
		FileLoader::Read(fileContent, path);
		std::vector<std::string> lines; StringHelper::split(lines, fileContent, "\n");
		for(auto &line : lines) {
			std::vector<std::string> attribs; StringHelper::split(attribs, line, "=");
			if(attribs.size() != 2) {
				continue;
			}
			if(attribs[0] == "shader") {
				Shader::Shader shader;
				std::string shaderPath = attribs[1];
				Shader::CreateShader(&shader, (shaderPath + "/vert.glsl").c_str(), (shaderPath + "/frag.glsl").c_str());
				mat->shader = shader;
			} else {
				std::string uniform = attribs[0];
				std::vector<std::string> vec; StringHelper::split(vec, attribs[1], ",");
				if(vec.size() != 1 && vec.size() != 3) {
					std::cout << "Garbage material detected!\nLine: " << line << "\n";
					return false;
				}
				if(vec.size() > 1) {
					glm::vec3 res;
					float x = std::stof(vec[0]);
					float y = std::stof(vec[1]);
					float z = std::stof(vec[2]);
					res.x = x; res.y = y; res.z = z;
					VectorProperty* prop = new VectorProperty();
					prop->uniform = uniform;
					prop->val = res;
					AddProperty(mat, prop);
				} else {
					float val = std::stof(vec[0]);
					FloatProperty* prop = new FloatProperty();
					prop->uniform = uniform;
					prop->val = val;
					AddProperty(mat, prop);
				}
			}
		}
		return true;
	}
	inline void Destroy(Material* mat) {
		mat->properties.clear();
		Shader::DestroyShader(&mat->shader);	
	}
}
