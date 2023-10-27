#pragma once
#include <vector>

#include "FileLoader.hpp"

#include "Mesh.hpp"
#include "Shader.hpp"
#include "Material.hpp"

namespace Eggy {
	struct Model {
		std::vector<Eggy::Mesh> meshes;
		std::vector<Eggy::Material> materials; 	
	};

	inline void AssignModelMesh(Model* model, Eggy::Mesh mesh) {
		model->meshes.push_back(mesh);
	}
	inline void AssignModelMaterial(Model* model, Eggy::Material material) {
		model->materials.push_back(material);
	}

	bool LoadModel(Model* model, std::string path) {
		
		return true;		
	}

	inline void RenderModel(Model* model) {
		int index = 0;
		for(auto& mesh : model->meshes) {
			if(index < model->materials.size()) {
				Eggy::BindMaterial(&model->materials[index]);
			}
			Eggy::RenderMesh(&mesh);
			index++;
		}
	}
	
	inline void DestroyModel(Model* model) {
		for(auto& mesh : model->meshes) {
			Eggy::DestroyMesh(&mesh);
		}
		for(auto& material : model->materials) {
			Eggy::DestroyMaterial(&material);
		}
		model->meshes.clear();
		model->materials.clear();
	}

}
