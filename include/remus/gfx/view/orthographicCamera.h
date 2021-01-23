#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <remus/gfx/view/camera.h>

namespace remus {
	namespace gfx {
		namespace view {

			class OrthographicCamera : public Camera {
			public:
				OrthographicCamera(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far);
			};

		}
	}
}