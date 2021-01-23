#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace remus {
	namespace gfx {
		namespace view {

			class Camera {
			public:
				Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);

				inline glm::mat4 getProjection() noexcept {
					return this->projection;
				}

				inline void setPos(glm::vec3 xyz) noexcept {
					this->position = xyz;
				}

				inline void setPos(GLfloat x, GLfloat y, GLfloat z) noexcept {
					this->position = glm::vec3(x, y, z);
				}

				inline void addPos(glm::vec3 xyz) noexcept {
					this->position += this->right * xyz.x;
					this->position += this->up * xyz.y;
					this->position += this->forward * xyz.z;
				}

				inline void addPos(GLfloat x, GLfloat y, GLfloat z) noexcept {
					this->addPos(glm::vec3(x, y, z));
				}

				inline void addPosX(GLfloat x) noexcept {
					this->addPos(x, 0, 0);
				}

				inline void addPosY(GLfloat y) noexcept {
					this->addPos(0, y, 0);
				}

				inline void addPosZ(GLfloat z) noexcept {
					this->addPos(0, 0, z);
				}

				inline void addYaw(GLfloat deg) noexcept {
					this->yaw += deg;
				}

				inline void addPitch(GLfloat deg) noexcept {
					this->pitch += deg;
				}

				inline glm::mat4 getViewMatrix() noexcept {
					return glm::lookAt(this->position, this->position + this->forward, this->up);
				}

				void update() noexcept;

				virtual ~Camera();

			protected:
				glm::mat4 projection;

				glm::vec3 position;
				glm::vec3 forward;
				glm::vec3 right;
				glm::vec3 up;

				GLfloat yaw;
				GLfloat pitch;
			};
			
		}
	}
}