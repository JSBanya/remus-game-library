#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <remus/logging/logger.h>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>
#include <mutex>

namespace remus {
	namespace utils {

		class Keyboard {
		public:
			Keyboard(GLFWwindow* window);

			bool isPressed(int key);

			std::vector<unsigned int> getCodePoints();

			inline void saveCodePoints(bool shouldSave) {
				if(shouldSave) {
					glfwSetCharCallback(this->window, Keyboard::charCallback);
				} else {
					glfwSetCharCallback(this->window, NULL);
				}
			}

			~Keyboard();

		protected:
			GLFWwindow* window;
			bool keyPressed[GLFW_KEY_LAST+1];
			std::vector<unsigned int> codepoints;
			std::mutex mtx;

		protected:
			static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
			static void charCallback(GLFWwindow* window, unsigned int codepoint);
			static inline std::unordered_map<GLFWwindow*, Keyboard*> instances;
		};

	}
}