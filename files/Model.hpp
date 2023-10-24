#pragma once
#include <vector>
#include "../libraries/assimp/include/assimp/Importer.hpp"
#include "../libraries/assimp/include/assimp/scene.h"
#include "../libraries/assimp/include/assimp/postprocess.h"

#include "Mesh.hpp"
#include "Shader.hpp"
#include "Material.hpp"

namespace Model {
	struct Model {
		std::vector<Mesh::Mesh> meshes;
		std::vector<Material::Material> materials; 	
	};

	inline void AssignMesh(Model* model, Mesh::Mesh mesh) {
		model->meshes.push_back(mesh);
	}
	inline void AssignMaterial(Model* model, Material::Material material) {
		model->materials.push_back(material);
	}

	inline bool Load(Model* model, const char* modelPath) {
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(modelPath, aiProcess_Triangulate);
		if(nullptr == scene) {
			std::cout << "Wrongful importation!\nError: " << importer.GetErrorString() << "\n";
			return false;
		}
		if(scene->HasMeshes()) {
			for(int i = 0; i < scene->mNumMeshes; i++) {
				std::vector<float> verts;
				std::vector<unsigned int> tris;
				aiMesh* mesh = scene->mMeshes[i];
				for(int k = 0; k < mesh->mNumVertices; k++) {
					aiVector3D vert = mesh->mVertices[k];
					verts.push_back(vert.x);
					verts.push_back(vert.y);
					verts.push_back(vert.z);
					if(mesh->HasNormals()) {
						aiVector3D normal = mesh->mNormals[k];
						verts.push_back(normal.x);
						verts.push_back(normal.y);
						verts.push_back(normal.z);
					} else {
						verts.push_back(0.0f);
						verts.push_back(0.0f);
						verts.push_back(0.0f);
					}
				}
				for(int k = 0; k < mesh->mNumFaces; k++) {
					aiFace face = mesh->mFaces[k];
					for(int l = 0; l < face.mNumIndices; l++) {
						tris.push_back(face.mIndices[l]);
					}
				}
				Mesh::Mesh aMesh;
				Mesh::CreateMesh(&aMesh);
				Mesh::MeshData(&aMesh, verts, tris);
				AssignMesh(model, aMesh);
			}

		}
		return true;
	}

	inline void Render(Model* model) {
		int index = 0;
		for(auto &mesh : model->meshes) {
			if(index < model->materials.size()) {
				Material::Bind(&model->materials[index]);
			}
			Mesh::RenderMesh(&mesh);
			index++;
		}


	}

}
