#include <remus/gfx/view/perspectiveCamera.h>

namespace remus {
	namespace gfx {
		namespace view {

			PerspectiveCamera::PerspectiveCamera(GLfloat fov, GLint width, GLint height, GLfloat near, GLfloat far, CameraAxisType axisType)
			: Camera(axisType)
			{
				if(near <= 0.0f)
					logger::logWarning("Perspective camera 'near' less than or equal to to 0.");
				this->projection = glm::perspective(glm::radians(fov), (GLfloat)width / (GLfloat)height, near, far);
			}

		}
	}
}