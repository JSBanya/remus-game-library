#include <remus/engine/context.h>

namespace remus {
	namespace engine {

		/****************
		* Shader
		****************/
		Context* Context::shaderLoad(std::string name, std::string pathToFile, std::string shaderType) {
			GLenum st = 0;
			if(shaderType == "vertex") {
				st = GL_VERTEX_SHADER;
			} else if(shaderType == "fragment") {
				st = GL_FRAGMENT_SHADER;
			} else {
				throw std::runtime_error("Unknown or unimplemented shader type: " + shaderType);
			}

			logger::logNotice("Loading " + shaderType + " shader \"" + name + "\" from " + pathToFile);

			auto src = this->readContentsString(pathToFile);
			this->shaders[name] = new gfx::shaders::Shader(src, st);

			if(this->shaders.count(name) > 0) {
				logger::logWarning("Duplicate shader \"" + name + "\" loaded from " + pathToFile);
			} else {
				logger::logNotice("Loaded shader \"" + name + "\" loaded from " + pathToFile);
			}
			
			return this;
		}

		Context* Context::shaderLoadVertex(std::string path, std::string name) {
			return this->shaderLoad(path, name, "vertex");
		}

		Context* Context::shaderLoadFragment(std::string path, std::string name) {
			return this->shaderLoad(path, name, "fragment");
		}

		gfx::shaders::Shader* Context::shaderGet(std::string name) {
			if(this->shaders.count(name) == 0) 
				throw std::runtime_error("No shader with name \"" + name + "\"");
			return this->shaders[name];
		}

		
		/****************
		* Shader Program
		****************/
		Context* Context::shaderProgramLoad(std::string programName, std::vector<std::string> shaderNames) {
			logger::logNotice("Loading shader program \"" + programName + "\"");

			std::vector<gfx::shaders::Shader*> shaders;
			std::string shaderNamesJoined = "";
			for(auto name : shaderNames) {
				if(this->shaders.count(name) == 0) {
					throw std::runtime_error("Error in creating shader program: no loaded shader found with name " + name);
				}

				logger::logNotice("Shader program \"" + programName + "\": Using shader " + name);
				shaders.push_back(this->shaders[name]);
			}

			this->shaderPrograms[programName] = new gfx::shaders::ShaderProgram(shaders);;
			logger::logNotice("Loaded shader program \"" + programName + "\"");

			return this;
		}

		gfx::shaders::ShaderProgram* Context::shaderProgramGet(std::string name) {
			if(this->shaderPrograms.count(name) == 0) 
				throw std::runtime_error("No shader program with name \"" + name + "\"");
			return this->shaderPrograms[name];
		}


		/****************
		* Mesh
		****************/
		Context* Context::meshLoad(std::string name) {
			logger::logNotice("Creating empty mesh \"" + name + "\"");

			if(this->meshes.count(name) > 0) {
				logger::logWarning("Duplicate mesh created with name \"" + name + "\"");
			}
			
			this->meshes[name] = new gfx::models::Mesh();
			logger::logNotice("Created empty mesh \"" + name + "\"");

			return this;
		}

		Context* Context::meshLoad(std::string name, gfx::models::Mesh* m) {
			logger::logNotice("Creating preloaded mesh \"" + name + "\"");
			if(this->meshes.count(name) > 0)
				logger::logWarning("Duplicate mesh created with name \"" + name + "\"");

			this->meshes[name] = m;
			logger::logNotice("Created preloaded mesh \"" + name + "\"");

			return this;
		}

		gfx::models::Mesh* Context::meshGet(std::string name) {
			if(this->meshes.count(name) == 0) 
				throw std::runtime_error("No model with name \"" + name + "\"");
			return this->meshes[name];
		}


		/****************
		* Texture2D
		****************/
		Context* Context::texture2DLoad(std::string name, std::string path, bool genMipmaps) {
			logger::logNotice("Creating texture2D \"" + name + "\" from " + path);
			if(this->texture2D.count(name) > 0) {
				logger::logWarning("Duplicate texture2D created with \"" + name + "\"");
			}

			auto t = new gfx::texture::Texture2D();
			t->load(path, genMipmaps);
			this->texture2D[name] = t;
			logger::logNotice("Created texture2D \"" + name + "\" from " + path);

			return this;
		}

		gfx::texture::Texture2D* Context::texture2DGet(std::string name) {
			if(this->texture2D.count(name) == 0) 
				throw std::runtime_error("No texture with name \"" + name + "\"");
			return this->texture2D[name];
		}


		/****************
		* Font
		****************/
		Context* Context::fontLoad(std::string name, std::string path, GLint size) {
			logger::logNotice("Creating font \"" + name + "\" from " + path + " with size " + std::to_string(size));
			if(this->fonts.count(name) > 0)
				logger::logWarning("Duplicate font created with \"" + name + "\"");

			this->fonts[name] = new gfx::texture::Font(path, size);
			logger::logNotice("Creating font \"" + name + "\" from " + path + " with size " + std::to_string(size));

			return this;
		}

		gfx::texture::Font* Context::fontGet(std::string name) {
			if(this->fonts.count(name) == 0) 
				throw std::runtime_error("No font with name \"" + name + "\"");
			return this->fonts[name];
		}


		std::string Context::readContentsString(std::string pathToFile) {
			std::filesystem::path p(pathToFile);
			if(!std::filesystem::exists(p)) {
				throw std::runtime_error("File " + pathToFile + " does not exist.");
			}			

			std::stringstream stream;
			std::ifstream file;
			file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			file.open(p);

			try {
				stream << file.rdbuf();
			} catch(const std::ifstream::failure* e) {
				file.close();
				throw *e;
			}
			
			file.close();

			return stream.str();
		}
	}
}