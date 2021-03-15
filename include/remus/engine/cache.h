#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <memory>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <remus/logging/logger.h>
#include <remus/gfx/texture/font.h>
#include <remus/gfx/shaders/shader.h>
#include <remus/gfx/shaders/shaderProgram.h>
#include <remus/gfx/models/model.h>
#include <remus/gfx/texture/texture2d.h>
#include <remus/gfx/texture/material.h>
#include <remus/engine/entity/entity.h>

namespace remus {
	namespace engine {

		class Cache {
		public:
			Cache();

			// Shaders
			Cache* loadShader(std::string name, gfx::shaders::Shader* shader);
			Cache* loadShader(std::string name, std::string pathToFile, std::string shaderType);
			Cache* loadShaderVertex(std::string name, std::string path);
			Cache* loadShaderFragment(std::string name, std::string path);
			gfx::shaders::Shader* getShader(std::string name);

			Cache* loadShaderProgram(std::string name, std::vector<std::string> s);
			gfx::shaders::ShaderProgram* getShaderProgram(std::string name);

			// Mesh
			Cache* loadMeshes(std::string prefix, std::string path, bool genOBB = true);
			Cache* loadMesh(std::string, gfx::models::Mesh*);

			gfx::models::Mesh* getMesh(std::string name);

			// Model
			Cache* loadModel(std::string name, std::string path, bool addMeshesToCache = true, bool genOBB = true);
			Cache* loadModel(std::string name, gfx::models::Model*);
			Cache* loadModel(std::string name, std::vector<std::string> meshNames);
			gfx::models::Model* getModel(std::string name);

			// Texture
			Cache* loadTexture2D(std::string name, std::string path, bool genMipmaps = true);
			Cache* loadTexture2D(std::string name, gfx::texture::Texture2D* tex);
			gfx::texture::Texture2D* getTexture2D(std::string name);

			// Material
			Cache* loadMaterial(std::string name, gfx::texture::Material* material);
			Cache* createMaterial(std::string name, std::string diffuse = "", std::string specular = "", GLfloat shininess = 1.0);
			gfx::texture::Material* getMaterial(std::string name);

			// Font
			Cache* loadFont(std::string name, std::string path, GLint size);
			gfx::texture::Font* getFont(std::string name);
		
			~Cache();

		private:
			std::string readContentsString(std::string pathToFile);
			std::unordered_map<std::string, gfx::models::Mesh*> getMeshesFromFile(std::string path, bool genOBB = true);
			std::unordered_map<std::string, gfx::models::Mesh*> createMeshes(aiNode *node, const aiScene *scene, bool genOBB = true);
			std::unordered_map<std::string, gfx::models::Mesh*> createMesh(aiMesh *mesh, const aiScene *scene, bool genOBB = true);

			void loadDefaults();

		private:
			std::unordered_map<std::string, gfx::shaders::Shader*> shaders;
			std::unordered_map<std::string, gfx::shaders::ShaderProgram*> shaderPrograms;
			std::unordered_map<std::string, gfx::models::Mesh*> meshes;
			std::unordered_map<std::string, gfx::models::Model*> models;
			std::unordered_map<std::string, gfx::texture::Texture2D*> texture2D;
			std::unordered_map<std::string, gfx::texture::Material*> materials;
			std::unordered_map<std::string, gfx::texture::Font*> fonts;
		};
			
	}
}