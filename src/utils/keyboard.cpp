#include <remus/utils/keyboard.h>

namespace remus {
	namespace utils {

		Keyboard::Keyboard(GLFWwindow* window) {
			Keyboard::instances[window] = this;
			glfwSetKeyCallback(window, Keyboard::keyCallback);
			for(auto i = 0; i < GLFW_KEY_LAST+1; i++) {
				this->keyPressed[i] = false;
			}
		}

		bool Keyboard::isPressed(int key) {
			if(key < 0 || key > GLFW_KEY_LAST) {
				logger::logError("Invalid key isPressed requested: " + std::to_string(key));
				return false;
			}

			return this->keyPressed[key];
		}

		std::vector<unsigned int> Keyboard::getCodePoints() {
			this->mtx.lock();
			auto codepoints = this->codepoints;
			this->codepoints = {};
			this->mtx.unlock();
			return codepoints;
		}

		Keyboard::~Keyboard() {
			if(this->window) {
				this->saveCodePoints(false);
				glfwSetKeyCallback(this->window, NULL);
			}
			Keyboard::instances.erase(this->window);
		}

		void Keyboard::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
			auto instance = Keyboard::instances[window];
			if(key == GLFW_KEY_UNKNOWN) {
				logger::logNotice("Unknown key action for key=" + std::to_string(key));
				return;
			}

			if(action == GLFW_PRESS || action == GLFW_REPEAT) {
				instance->keyPressed[key] = true;
			} else {
				instance->keyPressed[key] = false;
			}
		}

		void Keyboard::charCallback(GLFWwindow* window, unsigned int codepoint) {
			auto instance = Keyboard::instances[window];
			instance->mtx.lock();
			instance->codepoints.push_back(codepoint);
			instance->mtx.unlock();
		}

	}
}