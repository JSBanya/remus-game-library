#include <remus/gfx/view/orthographicCamera.h>

namespace remus {
	namespace gfx {
		namespace view {

			OrthographicCamera::OrthographicCamera(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far, CameraAxisType axisType) 
			: Camera(axisType) 
			{
				this->projection = glm::ortho(left, right, bottom, top, near, far);
			}
			
		}
	}
}