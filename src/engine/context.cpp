#include <remus/engine/context.h>

namespace remus {
	namespace engine {

		Context::Context(bool withDefaults) {
			if(withDefaults)
				logger::logNotice("Creating new context with defaults...");
			else
				logger::logNotice("Creating new context...");

			if(withDefaults) {
				this->loadDefaults();
			}

			if(withDefaults)
				logger::logNotice("Created new context with defaults.");
			else
				logger::logNotice("Created new context.");

		}

		/****************
		* Shader
		****************/
		Context* Context::loadShader(std::string name, gfx::shaders::Shader* shader) {
			logger::logNotice("Loading shader with name \"" + name + "\"");

			if(this->shaders.count(name) > 0) {
				logger::logWarning("Shader already exists with name \"" + name + "\"");
			}

			this->shaders[name] = shader;
			logger::logNotice("Loaded shader with name \"" + name + "\"");
			return this;
		}

		Context* Context::loadShader(std::string name, std::string pathToFile, std::string shaderType) {
			GLenum st = 0;
			if(shaderType == "vertex") {
				st = GL_VERTEX_SHADER;
			} else if(shaderType == "fragment") {
				st = GL_FRAGMENT_SHADER;
			} else {
				throw std::runtime_error("Unknown or unimplemented shader type: " + shaderType);
			}

			logger::logNotice("Reading " + shaderType + " shader \"" + name + "\" from " + pathToFile);

			auto src = this->readContentsString(pathToFile);
			this->loadShader(name, new gfx::shaders::Shader(src, st));
			
			return this;
		}

		Context* Context::loadShaderVertex(std::string name, std::string path) {
			return this->loadShader(name, path, "vertex");
		}

		Context* Context::loadShaderFragment(std::string name, std::string path) {
			return this->loadShader(name, path, "fragment");
		}

		gfx::shaders::Shader* Context::getShader(std::string name) {
			if(this->shaders.count(name) == 0) 
				throw std::runtime_error("No shader with name \"" + name + "\"");
			return this->shaders[name];
		}

		
		/****************
		* Shader Program
		****************/
		Context* Context::loadShaderProgram(std::string programName, std::vector<std::string> shaderNames) {
			std::string names = "";
			for(auto sn : shaderNames) {
				names += sn + ",";
			}

			logger::logNotice("Loading shader program \"" + programName + "\" from shaders: " + names);

			std::vector<gfx::shaders::Shader*> shaders;
			for(auto name : shaderNames) {
				if(this->shaders.count(name) == 0) {
					throw std::runtime_error("Error in creating shader program: no loaded shader found with name " + name);
				}
				shaders.push_back(this->shaders[name]);
			}

			this->shaderPrograms[programName] = new gfx::shaders::ShaderProgram(shaders);;
			logger::logNotice("Loaded shader program \"" + programName + "\" from shaders: " + names);
			return this;
		}

		gfx::shaders::ShaderProgram* Context::getShaderProgram(std::string name) {
			if(this->shaderPrograms.count(name) == 0) 
				throw std::runtime_error("No shader program with name \"" + name + "\"");
			return this->shaderPrograms[name];
		}


		/****************
		* Mesh
		****************/
		Context* Context::loadMeshes(std::string prefix, std::string path, bool genOBB) {
			logger::logNotice("Loading meshes from file \"" + path + "\" with prefix \"" + prefix + "\"");

			auto meshes = this->getMeshesFromFile(path, genOBB);
			for(auto &it : meshes) {
				this->loadMesh(prefix + it.first, it.second);
			}

			logger::logNotice("Loaded all meshes from file \"" + path + "\" with prefix \"" + prefix + "\"");
			return this;
		}

		std::unordered_map<std::string, gfx::models::Mesh*> Context::getMeshesFromFile(std::string path, bool genOBB) {
			std::filesystem::path p(path);
			if(!std::filesystem::exists(p)) {
				throw std::runtime_error("File " + path + " does not exist.");
			}

			Assimp::Importer importer;
			const aiScene* scene = importer.ReadFile(p, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
			if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
				throw std::runtime_error("Unable to load meshes from file \"" + path + "\": " + importer.GetErrorString());
			}

			return this->createMeshes(scene->mRootNode, scene, genOBB);
		}

		std::unordered_map<std::string, gfx::models::Mesh*> Context::createMeshes(aiNode *node, const aiScene *scene, bool genOBB) {
			std::unordered_map<std::string, gfx::models::Mesh*> meshes;

			for(unsigned int i = 0; i < node->mNumMeshes; i++) {
				aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
				for(auto &it : this->createMesh(mesh, scene, genOBB)) {
					meshes[it.first] = it.second;
				}
			}
			
			for(unsigned int i = 0; i < node->mNumChildren; i++) {
				for(auto &it : this->createMeshes(node->mChildren[i], scene, genOBB)) {
					meshes[it.first] = it.second;
				}
			}

			return meshes;
		}

		std::unordered_map<std::string, gfx::models::Mesh*> Context::createMesh(aiMesh *mesh, const aiScene *scene, bool genOBB) {
			std::vector<gfx::models::Vertex> vertices;
			std::vector<GLuint> indices;

			// Vertices
			for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
				gfx::models::Vertex vertex;
				vertex.Position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
				
				// Normals
				if(mesh->HasNormals()) {
					vertex.Normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
				}

				// UV Coordinates
				if(mesh->mTextureCoords[0]) {
					vertex.TexCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
				}

				vertices.push_back(vertex);
			}

			// Indices
			for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
				aiFace face = mesh->mFaces[i];
				for(unsigned int j = 0; j < face.mNumIndices; j++)
					indices.push_back(face.mIndices[j]);        
			}
			
			std::unordered_map<std::string, gfx::models::Mesh*> meshes;
			if(!mesh->mName.C_Str()) {
				throw std::runtime_error("Mesh requires a name.");
			}

			auto meshName = std::string(mesh->mName.C_Str());
			if(meshName.length() == 0) {
				throw std::runtime_error("Mesh name cannot be empty");
			}

			meshes[meshName] = new gfx::models::Mesh(vertices, indices, genOBB);
			return meshes;
		}

		Context* Context::loadMesh(std::string name, gfx::models::Mesh* m) {
			logger::logNotice("Creating mesh \"" + name + "\"");
			if(this->meshes.count(name) > 0)
				logger::logWarning("Mesh already exists with name \"" + name + "\"");

			this->meshes[name] = m;
			logger::logNotice("Created mesh \"" + name + "\"");

			return this;
		}

		gfx::models::Mesh* Context::getMesh(std::string name) {
			if(this->meshes.count(name) == 0) 
				throw std::runtime_error("No mesh with name \"" + name + "\"");
			return this->meshes[name];
		}


		/****************
		* Model
		****************/
		Context* Context::loadModel(std::string name, std::string path, bool addMeshesToContext, bool genOBB) {
			logger::logNotice("Loading model \"" + name + "\" from file \"" + path + "\"");

			auto meshes = this->getMeshesFromFile(path, genOBB);

			std::string meshNames = "";
			for(auto &it : meshes) {
				meshNames += it.first + ", ";
				if(addMeshesToContext) {
					this->loadMesh(name + "_" + it.first, it.second);
				}
			}

			this->loadModel(name, new gfx::models::Model(meshes));

			logger::logNotice("Loaded model \"" + name + "\" (meshes: " + meshNames + ") from file \"" + path + "\"");
			return this;
		}

		Context* Context::loadModel(std::string name, gfx::models::Model* model) {
			logger::logNotice("Creating model \"" + name + "\"");
			if(this->models.count(name) > 0) {
				logger::logWarning("Model already exists with name \"" + name + "\"");
			}

			this->models[name] = model;
			logger::logNotice("Created model \"" + name + "\"");
			return this;
		}

		Context* Context::loadModel(std::string name, std::vector<std::string> meshNames) {
			std::string names = "";
			for(auto mn : meshNames) {
				names += mn + ",";
			}
			logger::logNotice("Creating model \"" + name + "\" from existing meshes: " + names);

			std::unordered_map<std::string, gfx::models::Mesh*> meshes;
			for(auto mn : meshNames) {
				meshes[mn] = this->getMesh(mn);
			}

			this->loadModel(name, new gfx::models::Model(meshes));
			logger::logNotice("Created model \"" + name + "\" from existing meshes: " + names);
			return this;
		}

		gfx::models::Model* Context::getModel(std::string name) {
			if(this->models.count(name) == 0) 
				throw std::runtime_error("No model with name \"" + name + "\"");
			return this->models[name];
		}


		/****************
		* Texture2D
		****************/
		Context* Context::loadTexture2D(std::string name, std::string path, bool genMipmaps) {
			logger::logNotice("Creating texture2D \"" + name + "\" from " + path);
			if(this->texture2D.count(name) > 0) {
				logger::logWarning("Texture2D already exists with name \"" + name + "\"");
			}

			auto t = new gfx::texture::Texture2D();
			t->load(path, genMipmaps);
			this->texture2D[name] = t;
			logger::logNotice("Created texture2D \"" + name + "\" from " + path);

			return this;
		}

		Context* Context::loadTexture2D(std::string name, gfx::texture::Texture2D* tex) {
			logger::logNotice("Creating texture2D \"" + name + "\" from preload.");
			if(this->texture2D.count(name) > 0) {
				logger::logWarning("Texture2D already exists with name \"" + name + "\"");
			}

			this->texture2D[name] = tex;
			logger::logNotice("Created texture2D \"" + name + "\" from preload.");
			return this;
		}

		gfx::texture::Texture2D* Context::getTexture2D(std::string name) {
			if(this->texture2D.count(name) == 0) 
				throw std::runtime_error("No texture with name \"" + name + "\"");
			return this->texture2D[name];
		}


		/****************
		* Material
		****************/
		Context* Context::loadMaterial(std::string name, gfx::texture::Material* material) {
			logger::logNotice("Loading material \"" + name + "\"");
			if(this->materials.count(name) > 0) {
				logger::logWarning("Material already exists with name \"" + name + "\"");
			}

			this->materials[name] = material;
			logger::logNotice("Loading material \"" + name + "\"");
			return this;
		}

		Context* Context::createMaterial(std::string name, std::string diffuse, std::string specular, GLfloat shininess) {
			logger::logNotice("Creating new material \"" + name + "\" with diffuse=" + diffuse + ", specular=" + specular + ", shininess=" + std::to_string(shininess));
			if(this->materials.count(name) > 0) {
				logger::logWarning("Material already exists with name \"" + name + "\"");
			}

			auto diffuseTex = (diffuse.size() == 0 ? nullptr : this->getTexture2D(diffuse));
			auto specularTex = (specular.size() == 0 ? nullptr : this->getTexture2D(specular));

			this->materials[name] = new gfx::texture::Material(diffuseTex, specularTex, shininess);
			logger::logNotice("Created new material \"" + name + "\"");
			return this;
		}

		gfx::texture::Material* Context::getMaterial(std::string name) {
			if(this->materials.count(name) == 0) 
				throw std::runtime_error("No material with name \"" + name + "\"");
			return this->materials[name];
		}


		/****************
		* Font
		****************/
		Context* Context::loadFont(std::string name, std::string path, GLint size) {
			logger::logNotice("Creating font \"" + name + "\" from " + path + " with size " + std::to_string(size));
			if(this->fonts.count(name) > 0)
				logger::logWarning("Font already exists with name \"" + name + "\"");

			this->fonts[name] = new gfx::texture::Font(path, size);
			logger::logNotice("Creating font \"" + name + "\" from " + path + " with size " + std::to_string(size));

			return this;
		}

		gfx::texture::Font* Context::getFont(std::string name) {
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

		Context::~Context() {
			logger::logNotice("Destroying context...");
			for(auto &it : this->shaders) delete it.second;
			for(auto &it : this->shaderPrograms) delete it.second;
			for(auto &it : this->meshes) delete it.second;
			for(auto &it : this->models) delete it.second;
			for(auto &it : this->texture2D) delete it.second;
			for(auto &it : this->materials) delete it.second;
			for(auto &it : this->fonts) delete it.second;
			logger::logNotice("Destroyed context.");
		}
	}
}