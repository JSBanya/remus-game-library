#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <remus/gfx/view/camera.h>
#include <remus/logging/logger.h>

namespace remus {
	namespace gfx {
		namespace view {

			class PerspectiveCamera : public Camera {
			public:
				PerspectiveCamera(GLfloat fov, GLint width, GLint height, GLfloat near, GLfloat far);
			};

		}
	}
}