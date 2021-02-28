#include <remus/gfx/view/camera.h>

namespace remus {
	namespace gfx {
		namespace view {

			Camera::Camera(CameraAxisType axisType) {
				this->axisType = axisType;
				this->update();
			}

			void Camera::update() noexcept {
				// Update view axis
				glm::vec3 forward;
				forward.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
				forward.y = sin(glm::radians(this->pitch));
				forward.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
				this->viewForward = glm::normalize(forward);

				this->viewRight = glm::normalize(glm::cross(this->viewForward, glm::vec3(0.0f, 1.0f, 0.0f)));
				this->viewUp = glm::normalize(glm::cross(this->viewRight, this->viewForward));

				// Update movement axis
				if(this->axisType == ALWAYS_LOCAL) {
					// Same as view axis (i.e. always local to current state)
					this->movementForward = this->viewForward;
					this->movementRight = this->viewRight;
					this->movementUp = this->viewUp;
				} else if(this->axisType == FIXED_PITCH) {
					// Axis changes with yaw only (not affected by pitch)
					this->movementForward = glm::normalize(glm::vec3(forward.x, this->movementForward.y, forward.z));
					this->movementRight = glm::normalize(glm::cross(this->movementForward, glm::vec3(0.0f, 1.0f, 0.0f)));
				} else if(this->axisType == ALWAYS_GLOBAL) {
					// No update to movement axis
				}
			}

			Camera::~Camera() {
				
			}

		}
	}
}