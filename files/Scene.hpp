#pragma once
#include <vector>
#include <string>
#include <iostream>

#include "../libraries/glad/glad.h"

#include "Camera.hpp"
#include "Material.hpp"
#include "Mesh.hpp"
#include "Model.hpp"
#include "Node.hpp"
#include "FileLoader.hpp"
#include "Shader.hpp"
#include "StringHelper.hpp"
#include "Texture.hpp"
#include "Window.hpp"

namespace Scene {
	struct Scene {
		std::vector<Node::Node> nodes;
		unsigned int fbo, rbo;
		GLuint tex;
		unsigned int resX = 1280, resY = 720;
	};
	inline void Initialize(Scene* scene) {
		glGenFramebuffers(1, &scene->fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, scene->fbo);
		glGenTextures(1, &scene->tex);
		glBindTexture(GL_TEXTURE_2D, scene->tex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, scene->resX, scene->resY, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, scene->tex, 0);

		glGenRenderbuffers(1, &scene->rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, scene->rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, scene->resX, scene->resY);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, scene->rbo);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n";
		
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	inline void AddNode(Scene* scene, Node::Node node) {
		scene->nodes.push_back(node);
	}
	
	inline void Update(Scene* scene, Camera::Camera* cam, Window::Window* window) {
		glEnable(GL_DEPTH_TEST);
		glViewport(0,0,scene->resX,scene->resY);
		glBindFramebuffer(GL_FRAMEBUFFER, scene->fbo);
		Window::ClearWindow(window);
		for(auto& node : scene->nodes) {
			Node::Update(&node, cam);
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		Window::ClearWindow(window);
		glDisable(GL_DEPTH_TEST);
	}

	inline Node::Node* GetNode(Scene* scene, std::string nodeTag) {
		for(int i = 0; i < scene->nodes.size(); i++) {
			if(scene->nodes[i].nodeTag == nodeTag) {
				return &scene->nodes[i];
			}
		}
		return nullptr;
	}

	inline void Load(Scene* scene, const char* path) {
		std::string sceneContents; FileLoader::Read(sceneContents, path);
		std::vector<std::string> lines; StringHelper::split(lines, sceneContents, "\n");
		int index = 0;
		for(auto& line : lines) {
			if(line == "CREATE") {
				std::vector<std::string> tagAttribute; StringHelper::split(tagAttribute, lines[index+1], "=");
				Node::Node node(tagAttribute[1]);
				std::vector<std::string> materialAttribute; StringHelper::split(materialAttribute, lines[index+2], "=");
				std::string materialPath = materialAttribute[1];
				Material::Material mat;
				Material::Load(&mat, materialPath.c_str());
				std::vector<std::string> meshAttribute; StringHelper::split(meshAttribute, lines[index+3], "=");
				std::string meshPath = meshAttribute[1];
				Model::Model model;
				Model::Load(&model, meshPath.c_str());
				Model::AssignMaterial(&model, mat);
				node.model = model;
				
				std::vector<std::string> positionAttribute; StringHelper::split(positionAttribute, lines[index+4], "=");
				std::vector<std::string> posRes; StringHelper::split(posRes, positionAttribute[1], ",");
				glm::vec3 posVec;
				posVec.x = std::stof(posRes[0]);
				posVec.y = std::stof(posRes[1]);
				posVec.z = std::stof(posRes[2]);
				node.position = posVec;	
				
				std::vector<std::string> rotationAttribute; StringHelper::split(rotationAttribute, lines[index+5], "=");
				std::vector<std::string> rotRes; StringHelper::split(rotRes, rotationAttribute[1], ",");
				glm::vec3 rotVec;
				rotVec.x = std::stof(rotRes[0]);
				rotVec.y = std::stof(rotRes[1]);
				rotVec.z = std::stof(rotRes[2]);
				node.rotation = rotVec;	
				

				AddNode(scene, node);
			}
			index++;

		}
	}
	
	inline void Destroy(Scene* scene) {
		glDeleteFramebuffers(1, &scene->fbo);
		glDeleteRenderbuffers(1, &scene->rbo);
		glDeleteTextures(1, &scene->tex);	
		for(auto& node : scene->nodes) {
			Node::Destroy(&node);
		}
		
		scene->nodes.clear();

	}
}
