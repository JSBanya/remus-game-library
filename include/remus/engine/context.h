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
#include <remus/gfx/texture/textureSet.h>
#include <remus/engine/entity/entity.h>

namespace remus {
	namespace engine {

		class Context {
		public:
			Context(bool withDefaults = false);

			// Shaders
			Context* loadShader(std::string name, gfx::shaders::Shader* shader);
			Context* loadShader(std::string name, std::string pathToFile, std::string shaderType);
			Context* loadShaderVertex(std::string name, std::string path);
			Context* loadShaderFragment(std::string name, std::string path);
			gfx::shaders::Shader* getShader(std::string name);

			Context* loadShaderProgram(std::string name, std::vector<std::string> s);
			gfx::shaders::ShaderProgram* getShaderProgram(std::string name);

			// Mesh
			Context* loadMeshes(std::string prefix, std::string path, bool genOBB = true);
			Context* loadMesh(std::string, gfx::models::Mesh*);

			gfx::models::Mesh* getMesh(std::string name);

			// Model
			Context* loadModel(std::string name, std::string path, bool addMeshesToContext = true, bool genOBB = true);
			Context* loadModel(std::string name, gfx::models::Model*);
			Context* loadModel(std::string name, std::vector<std::string> meshNames);
			gfx::models::Model* getModel(std::string name);

			// Texture
			Context* loadTexture2D(std::string name, std::string path, bool genMipmaps = true);
			gfx::texture::Texture2D* getTexture2D(std::string name);

			// TextureSet
			Context* loadTextureSet(std::string name, gfx::texture::TextureSet* textureSet);
			Context* createTextureSet(std::string name);
			Context* addTextureSetGeneric(std::string name, std::vector<std::string> textureNames, std::vector<std::string> textureSetNames);
			Context* addTextureSetDiffuse(std::string name, std::vector<std::string> textureNames);
			Context* addTextureSetSpecular(std::string name, std::vector<std::string> textureNames);
			gfx::texture::TextureSet* getTextureSet(std::string name);

			// Font
			Context* loadFont(std::string name, std::string path, GLint size);
			gfx::texture::Font* getFont(std::string name);
		
			~Context();

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
			std::unordered_map<std::string, gfx::texture::TextureSet*> textureSets;
			std::unordered_map<std::string, gfx::texture::Font*> fonts;
		};
			
	}
}