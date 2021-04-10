#include <remus/engine/cache.h>

namespace remus {
	namespace engine {

		Cache::Cache() {
			Logger::logNotice("Creating new cache...");
			this->loadDefaults();
			Logger::logNotice("Created new cache.");
		}

		void Cache::loadDefaults() {
			Logger::logNotice("Loading cache defaults...");

			// default_vertex_shader_postprocessing
			const std::string default_vertex_shader_postprocessing_source = 
			R"(
			#version 430 core
			layout (location = 0) in vec3 aPos;
			layout (location = 1) in vec2 texPos;

			out vec2 TexCoords;

			void main() {
				gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0); 
				TexCoords = texPos;
			}
			)";
			this->loadShader(Cache::DEFAULT_POSTPROCESSING_VERTEX_SHADER,  new gfx::shaders::Shader(default_vertex_shader_postprocessing_source, GL_VERTEX_SHADER));

			// default_fragment_shader_postprocessing
			const std::string default_fragment_shader_postprocessing_source = 
			R"(
			#version 430 core

			in vec2 TexCoords;
			out vec4 FragColor;

			uniform sampler2D screen;

			void main() {
				FragColor = texture(screen, TexCoords);
			}
			)";

		 	this->loadShader(Cache::DEFAULT_POSTPROCESSING_FRAGMENT_SHADER, new gfx::shaders::Shader(default_fragment_shader_postprocessing_source, GL_FRAGMENT_SHADER));

			// default_shader
			this->loadShaderProgram(Cache::DEFAULT_POSTPROCESSING_SHADER, {Cache::DEFAULT_POSTPROCESSING_VERTEX_SHADER, Cache::DEFAULT_POSTPROCESSING_FRAGMENT_SHADER});

			// default_vertex_shader_text_generation
			const std::string default_vertex_shader_text_generation_source = 
			R"(
				#version 330 core
				layout (location = 0) in vec3 aPos;
				layout (location = 1) in vec2 texPos;
				uniform mat4 modelMatrix;
				out vec2 texCoord;
				void main() {
					gl_Position = modelMatrix * vec4(aPos, 1.0);
					texCoord = texPos;
				}
			)";
			this->loadShader(Cache::DEFAULT_TEXT_GENERATION_VERTEX_SHADER, new gfx::shaders::Shader(default_vertex_shader_text_generation_source, GL_VERTEX_SHADER));

			// default_fragment_shader_text_generation
			const std::string default_fragment_shader_text_generation_source = 
			R"(
			#version 330 core
			in vec2 texCoord;
			out vec4 FragColor;
			uniform sampler2D character;
			void main() {
				FragColor = texture(character, texCoord);
			}
			)";
			this->loadShader(Cache::DEFAULT_TEXT_GENERATION_FRAGMENT_SHADER, new gfx::shaders::Shader(default_fragment_shader_text_generation_source, GL_FRAGMENT_SHADER));

			// default_shader_text_generation
			this->loadShaderProgram(Cache::DEFAULT_TEXT_GENERATION_SHADER, {Cache::DEFAULT_TEXT_GENERATION_VERTEX_SHADER, Cache::DEFAULT_TEXT_GENERATION_FRAGMENT_SHADER});
		}

		/****************
		* Shader
		****************/
		Cache* Cache::loadShader(std::string name, gfx::shaders::Shader* shader) {
			Logger::logNotice("Loading shader with name \"" + name + "\"");

			if(this->shaders.count(name) > 0) {
				Logger::logWarning("Shader already exists with name \"" + name + "\"");
			}

			this->shaders[name] = shader;
			Logger::logNotice("Loaded shader with name \"" + name + "\"");
			return this;
		}

		Cache* Cache::loadShader(std::string name, std::string pathToFile, std::string shaderType) {
			GLenum st = 0;
			if(shaderType == "vertex") {
				st = GL_VERTEX_SHADER;
			} else if(shaderType == "fragment") {
				st = GL_FRAGMENT_SHADER;
			} else {
				throw std::runtime_error("Unknown or unimplemented shader type: " + shaderType);
			}

			Logger::logNotice("Reading " + shaderType + " shader \"" + name + "\" from " + pathToFile);

			auto src = this->readContentsString(pathToFile);
			this->loadShader(name, new gfx::shaders::Shader(src, st));
			
			return this;
		}

		Cache* Cache::loadShaderVertex(std::string name, std::string path) {
			return this->loadShader(name, path, "vertex");
		}

		Cache* Cache::loadShaderFragment(std::string name, std::string path) {
			return this->loadShader(name, path, "fragment");
		}

		gfx::shaders::Shader* Cache::getShader(std::string name) {
			if(this->shaders.count(name) == 0) 
				throw std::runtime_error("No shader with name \"" + name + "\"");
			return this->shaders[name];
		}

		
		/****************
		* Shader Program
		****************/
		Cache* Cache::loadShaderProgram(std::string programName, std::vector<std::string> shaderNames) {
			std::string names = "";
			for(auto sn : shaderNames) {
				names += sn + ",";
			}

			Logger::logNotice("Loading shader program \"" + programName + "\" from shaders: " + names);

			std::vector<gfx::shaders::Shader*> shaders;
			for(auto name : shaderNames) {
				if(this->shaders.count(name) == 0) {
					throw std::runtime_error("Error in creating shader program: no loaded shader found with name " + name);
				}
				shaders.push_back(this->shaders[name]);
			}

			this->shaderPrograms[programName] = new gfx::shaders::ShaderProgram(shaders);;
			Logger::logNotice("Loaded shader program \"" + programName + "\" from shaders: " + names);
			return this;
		}

		gfx::shaders::ShaderProgram* Cache::getShaderProgram(std::string name) {
			if(this->shaderPrograms.count(name) == 0) 
				throw std::runtime_error("No shader program with name \"" + name + "\"");
			return this->shaderPrograms[name];
		}


		/****************
		* Mesh
		****************/
		Cache* Cache::loadMeshes(std::string prefix, std::string path, bool genOBB) {
			Logger::logNotice("Loading meshes from file \"" + path + "\" with prefix \"" + prefix + "\"");

			auto meshes = this->getMeshesFromFile(path, genOBB);
			for(auto &it : meshes) {
				this->loadMesh(prefix + it.first, it.second);
			}

			Logger::logNotice("Loaded all meshes from file \"" + path + "\" with prefix \"" + prefix + "\"");
			return this;
		}

		std::unordered_map<std::string, gfx::models::Mesh*> Cache::getMeshesFromFile(std::string path, bool genOBB) {
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

		std::unordered_map<std::string, gfx::models::Mesh*> Cache::createMeshes(aiNode *node, const aiScene *scene, bool genOBB) {
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

		std::unordered_map<std::string, gfx::models::Mesh*> Cache::createMesh(aiMesh *mesh, const aiScene *scene, bool genOBB) {
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

		Cache* Cache::loadMesh(std::string name, gfx::models::Mesh* m) {
			Logger::logNotice("Creating mesh \"" + name + "\"");
			if(this->meshes.count(name) > 0)
				Logger::logWarning("Mesh already exists with name \"" + name + "\"");

			this->meshes[name] = m;
			Logger::logNotice("Created mesh \"" + name + "\"");

			return this;
		}

		gfx::models::Mesh* Cache::getMesh(std::string name) {
			if(this->meshes.count(name) == 0) 
				throw std::runtime_error("No mesh with name \"" + name + "\"");
			return this->meshes[name];
		}


		/****************
		* Model
		****************/
		Cache* Cache::loadModel(std::string name, std::string path, bool addMeshesToCache, bool genOBB) {
			Logger::logNotice("Loading model \"" + name + "\" from file \"" + path + "\"");

			auto meshes = this->getMeshesFromFile(path, genOBB);

			std::string meshNames = "";
			for(auto &it : meshes) {
				meshNames += it.first + ", ";
				if(addMeshesToCache) {
					this->loadMesh(name + "_" + it.first, it.second);
				}
			}

			this->loadModel(name, new gfx::models::Model(meshes));

			Logger::logNotice("Loaded model \"" + name + "\" (meshes: " + meshNames + ") from file \"" + path + "\"");
			return this;
		}

		Cache* Cache::loadModel(std::string name, gfx::models::Model* model) {
			Logger::logNotice("Creating model \"" + name + "\"");
			if(this->models.count(name) > 0) {
				Logger::logWarning("Model already exists with name \"" + name + "\"");
			}

			this->models[name] = model;
			Logger::logNotice("Created model \"" + name + "\"");
			return this;
		}

		Cache* Cache::loadModel(std::string name, std::vector<std::string> meshNames) {
			std::string names = "";
			for(auto mn : meshNames) {
				names += mn + ",";
			}
			Logger::logNotice("Creating model \"" + name + "\" from existing meshes: " + names);

			std::unordered_map<std::string, gfx::models::Mesh*> meshes;
			for(auto mn : meshNames) {
				meshes[mn] = this->getMesh(mn);
			}

			this->loadModel(name, new gfx::models::Model(meshes));
			Logger::logNotice("Created model \"" + name + "\" from existing meshes: " + names);
			return this;
		}

		gfx::models::Model* Cache::getModel(std::string name) {
			if(this->models.count(name) == 0) 
				throw std::runtime_error("No model with name \"" + name + "\"");
			return this->models[name];
		}


		/****************
		* Texture2D
		****************/
		Cache* Cache::loadTexture2D(std::string name, std::string path, bool genMipmaps) {
			Logger::logNotice("Creating texture2D \"" + name + "\" from " + path);
			if(this->texture2D.count(name) > 0) {
				Logger::logWarning("Texture2D already exists with name \"" + name + "\"");
			}

			auto t = new gfx::texture::Texture2D();
			t->load(path, genMipmaps);
			this->texture2D[name] = t;
			Logger::logNotice("Created texture2D \"" + name + "\" from " + path);

			return this;
		}

		Cache* Cache::loadTexture2D(std::string name, gfx::texture::Texture2D* tex) {
			Logger::logNotice("Creating texture2D \"" + name + "\" from preload.");
			if(this->texture2D.count(name) > 0) {
				Logger::logWarning("Texture2D already exists with name \"" + name + "\"");
			}

			this->texture2D[name] = tex;
			Logger::logNotice("Created texture2D \"" + name + "\" from preload.");
			return this;
		}

		gfx::texture::Texture2D* Cache::getTexture2D(std::string name) {
			if(this->texture2D.count(name) == 0) 
				throw std::runtime_error("No texture with name \"" + name + "\"");
			return this->texture2D[name];
		}


		/****************
		* Material
		****************/
		Cache* Cache::loadMaterial(std::string name, gfx::texture::Material* material) {
			Logger::logNotice("Loading material \"" + name + "\"");
			if(this->materials.count(name) > 0) {
				Logger::logWarning("Material already exists with name \"" + name + "\"");
			}

			this->materials[name] = material;
			Logger::logNotice("Loading material \"" + name + "\"");
			return this;
		}

		Cache* Cache::createMaterial(std::string name, std::string diffuse, std::string specular, GLfloat shininess) {
			Logger::logNotice("Creating new material \"" + name + "\" with diffuse=" + diffuse + ", specular=" + specular + ", shininess=" + std::to_string(shininess));
			if(this->materials.count(name) > 0) {
				Logger::logWarning("Material already exists with name \"" + name + "\"");
			}

			auto diffuseTex = (diffuse.size() == 0 ? nullptr : this->getTexture2D(diffuse));
			auto specularTex = (specular.size() == 0 ? nullptr : this->getTexture2D(specular));

			this->materials[name] = new gfx::texture::Material(diffuseTex, specularTex, shininess);
			Logger::logNotice("Created new material \"" + name + "\"");
			return this;
		}

		gfx::texture::Material* Cache::getMaterial(std::string name) {
			if(this->materials.count(name) == 0) 
				throw std::runtime_error("No material with name \"" + name + "\"");
			return this->materials[name];
		}


		/****************
		* Font
		****************/
		Cache* Cache::loadFont(std::string name, std::string path, GLint size) {
			Logger::logNotice("Creating font \"" + name + "\" from " + path + " with size " + std::to_string(size));
			if(this->fonts.count(name) > 0)
				Logger::logWarning("Font already exists with name \"" + name + "\"");

			this->fonts[name] = new gfx::texture::Font(path, size);
			Logger::logNotice("Creating font \"" + name + "\" from " + path + " with size " + std::to_string(size));

			return this;
		}

		gfx::texture::Font* Cache::getFont(std::string name) {
			if(this->fonts.count(name) == 0) 
				throw std::runtime_error("No font with name \"" + name + "\"");
			return this->fonts[name];
		}


		std::string Cache::readContentsString(std::string pathToFile) {
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

		Cache::~Cache() {
			Logger::logNotice("Destroying cache...");
			for(auto &it : this->shaders) delete it.second;
			for(auto &it : this->shaderPrograms) delete it.second;
			for(auto &it : this->meshes) delete it.second;
			for(auto &it : this->models) delete it.second;
			for(auto &it : this->texture2D) delete it.second;
			for(auto &it : this->materials) delete it.second;
			for(auto &it : this->fonts) delete it.second;
			Logger::logNotice("Destroyed cache.");
		}
	}
}