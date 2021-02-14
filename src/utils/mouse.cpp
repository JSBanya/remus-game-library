#include <remus/utils/mouse.h>

namespace remus {
	namespace utils {

		Mouse::Mouse(GLFWwindow* window) : window(window) {
			Mouse::instances[window] = this;
			glfwSetCursorPosCallback(window, Mouse::posCallback);
		}

		void Mouse::posCallback(GLFWwindow* window, double xpos, double ypos) {
			auto instance = Mouse::instances[window];
			instance->setXY(xpos, ypos);
		}

		Mouse::~Mouse() {
			glfwSetCursorPosCallback(this->window, NULL);
			Mouse::instances.erase(this->window);
		}

	}
}