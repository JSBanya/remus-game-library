#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <stdexcept>

namespace remus {
	namespace gfx {
		namespace models {

			enum ModelMode {
				WORLD,
				LOCAL
			};

			class ModelMatrix {
			public:
				ModelMatrix(ModelMode mode = WORLD);

				inline glm::mat4 get() noexcept { 
					if(this->modelMode == LOCAL)
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
					if(this->modelMode == LOCAL)
						throw std::logic_error("getPos not supported under LOCAL mode.");
					return this->pos; 
				}

				inline glm::vec3 getScale() { 
					if(this->modelMode == LOCAL)
						throw std::logic_error("getScale not supported under LOCAL mode.");
					return this->size; 
				}

				inline glm::mat4 getRotation() { 
					if(this->modelMode == LOCAL)
						throw std::logic_error("getRotation not supported under LOCAL mode.");
					return this->rotation; 
				}

				inline ModelMatrix* reset(ModelMode mode = WORLD) noexcept {
					this->pos = glm::vec3(0.0);
					this->size = glm::vec3(1.0);
					this->rotation = glm::mat4(1.0f);
					this->modelMatrix = glm::mat4(1.0f);
					this->modelUpdated = false;
					this->modelMode = mode;
					return this;
				}

				inline ModelMatrix* resetRotation() {
					if(this->modelMode == LOCAL)
						throw std::logic_error("resetRotation not supported under LOCAL mode.");
					this->modelUpdated = true;
					this->rotation = glm::mat4(1.0f);
					return this;
				}

				inline ModelMatrix* setRotation(glm::mat4 m) {
					if(this->modelMode == LOCAL)
						throw std::logic_error("setRotation not supported under LOCAL mode.");
					this->modelUpdated = true;
					this->rotation = m;
					return this;
				}

				inline ModelMatrix* rotate(GLfloat deg, glm::vec3 axis) noexcept {
					if(this->modelMode == LOCAL) {
						this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(deg), axis);
					} else {
						this->modelUpdated = true;
						this->rotation = glm::rotate(this->rotation, glm::radians(deg), axis);
					}
					
					return this;
				}

				inline ModelMatrix* rotateX(GLfloat deg) noexcept {
					return this->rotate(deg, glm::vec3(1.0f, 0.0f, 0.0f)); 
				}

				inline ModelMatrix* rotateY(GLfloat deg) noexcept {
					return this->rotate(deg, glm::vec3(0.0f, 1.0f, 0.0f)); 
				}

				inline ModelMatrix* rotateZ(GLfloat deg) noexcept {
					return this->rotate(deg, glm::vec3(0.0f, 0.0f, 1.0f)); 
				}

				inline ModelMatrix* setPos(glm::vec3 xyz) {
					if(this->modelMode == LOCAL)
						throw std::logic_error("setPos not supported under LOCAL mode.");
					this->modelUpdated = true;
					this->pos = xyz;
					return this;
				}

				inline ModelMatrix* setPos(GLfloat x, GLfloat y, GLfloat z) noexcept {
					return this->setPos(glm::vec3(x, y, z));
				}

				inline ModelMatrix* translate(glm::vec3 xyz) noexcept {
					if(this->modelMode == LOCAL) {
						this->modelMatrix = glm::translate(this->modelMatrix, xyz);
					} else {
						this->modelUpdated = true;
						this->pos += xyz;
					}
					
					return this;
				}

				inline ModelMatrix* translate(GLfloat x, GLfloat y, GLfloat z) noexcept {
					return this->translate(glm::vec3(x, y, z));
				}

				inline ModelMatrix* setScale(glm::vec3 xyz) {
					if(this->modelMode == LOCAL)
						throw std::logic_error("setScale not supported under LOCAL mode.");
					this->modelUpdated = true;
					this->size = xyz;
					return this;
				}

				inline ModelMatrix* setScale(GLfloat x, GLfloat y, GLfloat z) {
					return this->setScale(glm::vec3(x, y, z));
				}

				inline ModelMatrix* addScale(glm::vec3 xyz) {
					if(this->modelMode == LOCAL)
						throw std::logic_error("addScale not supported under LOCAL mode.");
					this->modelUpdated = true;
					this->size += xyz;
					return this;
				}

				inline ModelMatrix* addScale(GLfloat x, GLfloat y, GLfloat z) {
					return this->addScale(glm::vec3(x, y, z));
				}

				inline ModelMatrix* scale(glm::vec3 xyz) noexcept {
					if(this->modelMode == LOCAL) {
						this->modelMatrix = glm::scale(this->modelMatrix, xyz);
					} else {
						this->modelUpdated = true;
						this->size *= xyz;
					}
					
					return this;
				}

				inline ModelMatrix* scale(GLfloat x, GLfloat y, GLfloat z) noexcept {
					return this->scale(glm::vec3(x, y, z));
				}
			
			private:
				bool modelUpdated = false;
				glm::vec3 pos;
				glm::mat4 rotation;
				glm::vec3 size;
				glm::mat4 modelMatrix;
				ModelMode modelMode = WORLD;
			};

		}
	}
}