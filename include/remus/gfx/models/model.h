#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <glm/glm.hpp>
#include <remus/gfx/shaders/shaderProgram.h>
#include <remus/gfx/models/mesh.h>
#include <remus/gfx/texture/texture2d.h>

namespace remus {
	namespace gfx {
		namespace models {
			enum ModelMode {
				ABSOLUTE,
				RELATIVE
			};

			class Model {
			public:
				Model(Mesh* m, std::vector<texture::Texture2D*> t = {});

				inline Model* addTexture(texture::Texture2D* t) noexcept {
					this->textures2D.push_back(t);
					return this;
				}

				inline Model* clearTextures() noexcept {
					this->textures2D.clear();
					return this;
				}

				// Model matrix operations
				inline Model* modelMatrixReset(ModelMode mode = ABSOLUTE) noexcept {
					this->pos = glm::vec3(0.0);
					this->size = glm::vec3(1.0);
					this->rotation = glm::mat4(1.0f);
					this->modelMatrix = glm::mat4(1.0f);
					this->modelUpdated = false;
					this->modelMode = mode;
					return this;
				}

				inline Model* resetRotation() {
					if(this->modelMode == RELATIVE)
						throw std::logic_error("resetRotation not supported under RELATIVE mode.");
					this->modelUpdated = true;
					this->rotation = glm::mat4(1.0f);
					return this;
				}

				inline Model* setRotation(glm::mat4 m) {
					if(this->modelMode == RELATIVE)
						throw std::logic_error("setRotation not supported under RELATIVE mode.");
					this->modelUpdated = true;
					this->rotation = m;
					return this;
				}

				inline Model* rotate(GLfloat deg, glm::vec3 axis) noexcept {
					if(this->modelMode == RELATIVE) {
						this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(deg), axis);
					} else {
						this->modelUpdated = true;
						this->rotation = glm::rotate(this->rotation, glm::radians(deg), axis);
					}
					
					return this;
				}

				inline Model* rotateX(GLfloat deg) noexcept {
					return this->rotate(deg, glm::vec3(1.0f, 0.0f, 0.0f)); 
				}

				inline Model* rotateY(GLfloat deg) noexcept {
					return this->rotate(deg, glm::vec3(0.0f, 1.0f, 0.0f)); 
				}

				inline Model* rotateZ(GLfloat deg) noexcept {
					return this->rotate(deg, glm::vec3(0.0f, 0.0f, 1.0f)); 
				}

				inline Model* setPos(glm::vec3 xyz) {
					if(this->modelMode == RELATIVE)
						throw std::logic_error("setPos not supported under RELATIVE mode.");
					this->modelUpdated = true;
					this->pos = xyz;
					return this;
				}

				inline Model* setPos(GLfloat x, GLfloat y, GLfloat z) noexcept {
					return this->setPos(glm::vec3(x, y, z));
				}

				inline Model* translate(glm::vec3 xyz) noexcept {
					if(this->modelMode == RELATIVE) {
						this->modelMatrix = glm::translate(this->modelMatrix, xyz);
					} else {
						this->modelUpdated = true;
						this->pos += xyz;
					}
					
					return this;
				}

				inline Model* translate(GLfloat x, GLfloat y, GLfloat z) noexcept {
					return this->translate(glm::vec3(x, y, z));
				}

				inline Model* setScale(glm::vec3 xyz) {
					if(this->modelMode == RELATIVE)
						throw std::logic_error("setScale not supported under RELATIVE mode.");
					this->modelUpdated = true;
					this->size = xyz;
					return this;
				}

				inline Model* setScale(GLfloat x, GLfloat y, GLfloat z) {
					return this->setScale(glm::vec3(x, y, z));
				}

				inline Model* addScale(glm::vec3 xyz) {
					if(this->modelMode == RELATIVE)
						throw std::logic_error("addScale not supported under RELATIVE mode.");
					this->modelUpdated = true;
					this->size += xyz;
					return this;
				}

				inline Model* addScale(GLfloat x, GLfloat y, GLfloat z) {
					return this->addScale(glm::vec3(x, y, z));
				}

				inline Model* scale(glm::vec3 xyz) noexcept {
					if(this->modelMode == RELATIVE) {
						this->modelMatrix = glm::scale(this->modelMatrix, xyz);
					} else {
						this->modelUpdated = true;
						this->size *= xyz;
					}
					
					return this;
				}

				inline Model* scale(GLfloat x, GLfloat y, GLfloat z) noexcept {
					return this->scale(glm::vec3(x, y, z));
				}

				// Rendering
				inline void draw() noexcept {
					for(std::size_t i = 0; i < this->textures2D.size(); i++) {
						glActiveTexture(GL_TEXTURE0 + i);
						this->textures2D[i]->bind();
					}
					this->mesh->draw();
				}

				inline glm::mat4 getModelMatrix() noexcept { 
					if(this->modelMode == RELATIVE)
						return this->modelMatrix;

					if(!this->modelUpdated)
						return this->modelMatrix; 

					this->modelMatrix = glm::mat4(1.0f);
					this->modelMatrix = glm::translate(this->modelMatrix, this->pos); 
					this->modelMatrix = glm::scale(this->modelMatrix, this->size);
					this->modelMatrix = this->modelMatrix * this->rotation;
					this->modelUpdated = false;
					return this->modelMatrix;
				}

				inline glm::vec3 getPos() { 
					if(this->modelMode == RELATIVE)
						throw std::logic_error("getPos not supported under RELATIVE mode.");
					return this->pos; 
				}

				inline glm::vec3 getScale() { 
					if(this->modelMode == RELATIVE)
						throw std::logic_error("getScale not supported under RELATIVE mode.");
					return this->size; 
				}

				inline glm::mat4 getRotation() { 
					if(this->modelMode == RELATIVE)
						throw std::logic_error("getRotation not supported under RELATIVE mode.");
					return this->rotation; 
				}

				inline bool hasOBB() noexcept { return this->mesh->hasOBB(); }
				inline OBB* getOBB() noexcept { return this->mesh->getOBB(); }

				inline Mesh* getMesh() noexcept { return this->mesh; }
				inline std::vector<texture::Texture2D*> getTextures2D() noexcept { return this->textures2D; }
				
				virtual ~Model();

			protected:
				bool modelUpdated = false;
				glm::vec3 pos;
				glm::mat4 rotation;
				glm::vec3 size;
				glm::mat4 modelMatrix;
				ModelMode modelMode = ABSOLUTE;
				
				Mesh* mesh;
				std::vector<texture::Texture2D*> textures2D;
			};
		}
	}
}