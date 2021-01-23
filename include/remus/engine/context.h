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
#include <remus/logging/logger.h>
#include <remus/gfx/texture/font.h>
#include <remus/gfx/shaders/shader.h>
#include <remus/gfx/shaders/shaderProgram.h>
#include <remus/gfx/models/model.h>
#include <remus/gfx/texture/texture2d.h>
#include <remus/engine/entity/entity.h>

namespace remus {
	namespace engine {

		class Context {
		public:
			// Shaders
			Context* shaderLoad(std::string name, std::string pathToFile, std::string shaderType);
			Context* shaderLoadVertex(std::string path, std::string name);
			Context* shaderLoadFragment(std::string path, std::string name);
			gfx::shaders::Shader* shaderGet(std::string name);

			Context* shaderProgramLoad(std::string name, std::vector<std::string> s);
			gfx::shaders::ShaderProgram* shaderProgramGet(std::string name);

			// Mesh
			Context* meshLoad(std::string);
			Context* meshLoad(std::string, gfx::models::Mesh*);

			gfx::models::Mesh* meshGet(std::string name);

			// Texture
			Context* texture2DLoad(std::string name, std::string path, bool genMipmaps = true);
			gfx::texture::Texture2D* texture2DGet(std::string name);

			// Font
			Context* fontLoad(std::string name, std::string path, GLint size);
			gfx::texture::Font* fontGet(std::string name);
		
		private:
			std::string readContentsString(std::string pathToFile);

		private:
			std::unordered_map<std::string, gfx::shaders::Shader*> shaders;
			std::unordered_map<std::string, gfx::shaders::ShaderProgram*> shaderPrograms;
			std::unordered_map<std::string, gfx::models::Mesh*> meshes;
			std::unordered_map<std::string, gfx::texture::Texture2D*> texture2D;
			std::unordered_map<std::string, gfx::texture::Font*> fonts;
		};
			
	}
}