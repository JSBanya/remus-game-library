#pragma once

#include <unordered_map>
#include <glm/glm.hpp>
#include <remus/gfx/models/model.h>
#include <remus/gfx/shaders/shaderProgram.h>
#include <remus/logging/logger.h>

namespace remus {
	namespace engine {
		namespace entity {

			class Entity {
			public:
				Entity(gfx::models::Model* m, gfx::shaders::ShaderProgram* s, std::string name = "e_unknown");

				void draw() noexcept;

				inline Entity* setShader(gfx::shaders::ShaderProgram* s) noexcept {
					this->shader = s;
					return this;
				}

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

				inline gfx::models::Model* getModel() noexcept { return this->model; }
				inline gfx::shaders::ShaderProgram* getShader() noexcept { return this->shader; }
				inline std::unordered_map<std::string, bool> getUniformsBool() noexcept { return this->shaderUniformBool; }
				inline std::unordered_map<std::string, GLint> getUniformsInt() noexcept { return this->shaderUniformInt; }
				inline std::unordered_map<std::string, GLfloat> getUniformsFloat() noexcept { return this->shaderUniformFloat; }
				inline std::unordered_map<std::string, glm::vec3> getUniformsVec3() noexcept { return this->shaderUniformVec3; }
				inline std::unordered_map<std::string, glm::vec4> getUniformsVec4() noexcept { return this->shaderUniformVec4; }
				inline std::unordered_map<std::string, glm::mat4>  getUniformsMat4() noexcept { return this->shaderUniformMat4; }

				virtual ~Entity();

			protected:
				std::string name;
				gfx::models::Model* model;
				gfx::shaders::ShaderProgram* shader;

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