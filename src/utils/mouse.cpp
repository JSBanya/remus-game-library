#include <remus/utils/mouse.h>

namespace remus {
	namespace utils {

		void __mouse_callback(GLFWwindow* window, double xpos, double ypos) {
			Mouse::setXY(xpos, ypos);
			// glfwSetCursorPos(window, Mouse::getX(false), Mouse::getY(false, false));
		}

	}
}