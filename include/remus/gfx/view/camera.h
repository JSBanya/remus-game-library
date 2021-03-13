#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace remus {
	namespace gfx {
		namespace view {

			enum CameraAxisType {
				ALWAYS_LOCAL,
				ALWAYS_GLOBAL,
				FIXED_PITCH
			};

			class Camera {
			public:
				Camera(CameraAxisType axisType);

				inline glm::mat4 getProjection() noexcept {
					return this->projection;
				}

				inline void setPos(glm::vec3 xyz) noexcept {
					this->position = xyz;
				}

				inline void setPos(GLfloat x, GLfloat y, GLfloat z) noexcept {
					this->position = glm::vec3(x, y, z);
				}

				inline glm::vec3 getPos() noexcept {
					return this->position;
				}

				inline void addPos(glm::vec3 xyz) noexcept {
					this->position += this->movementRight * xyz.x;
					this->position += this->movementUp * xyz.y;
					this->position += this->movementForward * xyz.z;
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
					this->update();
				}

				inline void setYaw(GLfloat deg) noexcept {
					this->yaw = deg;
					this->update();
				}

				inline GLfloat getYaw() noexcept {
					return this->yaw;
				}

				inline void addPitch(GLfloat deg) noexcept {
					this->pitch += deg;
					this->update();
				}

				inline void setPitch(GLfloat deg) noexcept {
					this->pitch = deg;
					this->update();
				}

				inline GLfloat getPitch() noexcept {
					return this->pitch;
				}

				inline glm::mat4 getViewMatrix() noexcept {
					return glm::lookAt(this->position, this->position + this->viewForward, this->viewUp);
				}

				inline glm::vec3 getMovementForward() noexcept {
					return this->movementForward;
				}

				inline glm::vec3 getViewForward() noexcept {
					return this->viewForward;
				}

				virtual ~Camera();

			protected:
				void update() noexcept;

			protected:
				CameraAxisType axisType;
				
				glm::mat4 projection = glm::mat4(1.0f);
				GLfloat yaw = 0.0f;
				GLfloat pitch = 0.0f;

				glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);

				glm::vec3 movementForward = glm::vec3(0.0f, 0.0f, -1.0f);
				glm::vec3 viewForward = glm::vec3(0.0f, 0.0f, -1.0f);

				glm::vec3 movementRight = glm::vec3(1.0f, 0.0f, 0.0f);
				glm::vec3 viewRight = glm::vec3(1.0f, 0.0f, 0.0f);

				glm::vec3 movementUp = glm::vec3(0.0f, 1.0f, 0.0f);
				glm::vec3 viewUp = glm::vec3(0.0f, 1.0f, 0.0f);
			};
			
		}
	}
}