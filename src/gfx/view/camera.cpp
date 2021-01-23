#include <remus/gfx/view/camera.h>

namespace remus {
	namespace gfx {
		namespace view {

			Camera::Camera(glm::vec3 position,  float yaw, float pitch) {
				this->position = position;
				this->yaw = yaw;
				this->pitch = pitch;
				this->update();
			}

			void Camera::update() noexcept {
				glm::vec3 forward;
				forward.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
				forward.y = sin(glm::radians(this->pitch));
				forward.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
				this->forward = glm::normalize(forward);

				this->right = glm::normalize(glm::cross(this->forward, glm::vec3(0.0f, 1.0f, 0.0f)));
				this->up = glm::normalize(glm::cross(this->right, this->forward));
			}

			Camera::~Camera() {
				
			}

		}
	}
}