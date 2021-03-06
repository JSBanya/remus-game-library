#pragma once

#include <unordered_map>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <remus/gfx/models/model.h>
#include <remus/gfx/shaders/shaderProgram.h>
#include <remus/gfx/texture/material.h>
#include <remus/gfx/models/modelMatrix.h>
#include <remus/gfx/view/camera.h>
#include <remus/logging/logger.h>
#include <remus/gfx/buffers/ssbo.h>

namespace remus {
	namespace gfx {
		namespace entity {

			struct RayCastIntersection {
				std::string name;
				models::Mesh* mesh;
				GLfloat distance;
			};

			class Entity {
			public:
				Entity(models::Model* model, shaders::ShaderProgram* shader, std::unordered_map<std::string, texture::Material*> materials = {});
				Entity(models::Model* model, shaders::ShaderProgram* shader, std::vector<texture::Material*> materials, std::vector<std::string> names);

				models::ModelMatrix* newInstance() noexcept;
				size_t removeInstance(size_t instance);
				void updateInstance(size_t instance = 0);
				void bindInstanceData(GLint binding);
				void unbindInstanceData();

				inline std::vector<models::ModelMatrix>* getModelMatrices() noexcept {
					return &this->modelMatrices;
				}

				inline models::ModelMatrix* getModelMatrix(size_t instance = 0) { 
					return &this->modelMatrices[instance]; 
				}

				inline GLint numInstances() noexcept {
					return this->modelMatrices.size();
				}

				void addMaterial(std::string meshName, texture::Material* material);

				inline Entity* setShader(shaders::ShaderProgram* s) noexcept {
					this->shader = s;
					return this;
				}

				// std::vector<RayCastIntersection> raycast(GLfloat x, GLfloat y, view::Camera* camera = nullptr);

				inline Entity* setUniform(const std::string name, bool value) noexcept {
					this->shaderUniformBool[name] = value;
					return this;
				}

				inline Entity* setUniform(const std::string name, GLint value) noexcept { 
					this->shaderUniformInt[name] = value;
					return this;
				}

				inline Entity* setUniform(const std::string name, GLfloat value) noexcept { 
					this->shaderUniformFloat[name] = value;
					return this;
				}

				inline Entity* setUniform(const std::string name, glm::vec3 v3) noexcept { 
					this->shaderUniformVec3[name] = v3;
					return this;
				}

				inline Entity* setUniform(const std::string name, GLfloat x, GLfloat y, GLfloat z) noexcept { 
					this->setUniform(name, glm::vec3(x, y, z));
					return this;
				}

				inline Entity* setUniform(const std::string name, glm::vec4 v4) noexcept { 
					this->shaderUniformVec4[name] = v4;
					return this;
				}

				inline Entity* setUniform(const std::string name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) noexcept { 
					this->setUniform(name, glm::vec4(x, y, z, w));
					return this;
				}

				inline Entity* setUniform(const std::string name, glm::mat4 m4) noexcept { 
					this->shaderUniformMat4[name] = m4;
					return this;
				}

				void applyUniforms() noexcept;

				inline models::Model* getModel() noexcept { return this->model; }
				inline shaders::ShaderProgram* getShader() noexcept { return this->shader; }
				inline std::unordered_map<std::string, texture::Material*> getMaterials() { return this->materials; }
				inline texture::Material* getMaterial(std::string meshName) { return this->materials[meshName]; }

				inline std::unordered_map<std::string, bool> getUniformsBool() noexcept { return this->shaderUniformBool; }
				inline std::unordered_map<std::string, GLint> getUniformsInt() noexcept { return this->shaderUniformInt; }
				inline std::unordered_map<std::string, GLfloat> getUniformsFloat() noexcept { return this->shaderUniformFloat; }
				inline std::unordered_map<std::string, glm::vec3> getUniformsVec3() noexcept { return this->shaderUniformVec3; }
				inline std::unordered_map<std::string, glm::vec4> getUniformsVec4() noexcept { return this->shaderUniformVec4; }
				inline std::unordered_map<std::string, glm::mat4>  getUniformsMat4() noexcept { return this->shaderUniformMat4; }

				virtual ~Entity();

			protected:
				// Instancing
				std::vector<models::ModelMatrix> modelMatrices;
				buffers::SSBO instanceSSBO;
				bool updateSSBO = true;

				// Data
				models::Model* model;
				shaders::ShaderProgram* shader;
				std::unordered_map<std::string, texture::Material*> materials;

				// Uniforms
				std::unordered_map<std::string, bool> shaderUniformBool;
				std::unordered_map<std::string, GLint> shaderUniformInt;
				std::unordered_map<std::string, GLfloat> shaderUniformFloat;
				std::unordered_map<std::string, glm::vec3> shaderUniformVec3;
				std::unordered_map<std::string, glm::vec4> shaderUniformVec4;
				std::unordered_map<std::string, glm::mat4> shaderUniformMat4;				
			};

		}
	}
}