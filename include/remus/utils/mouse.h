#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace remus {
	namespace utils {

		void __mouse_callback(GLFWwindow* window, double xpos, double ypos);

		class Mouse {
		public:
			static void attach(GLFWwindow* window) noexcept {
				glfwSetCursorPosCallback(window, __mouse_callback);
			}

			static void detach(GLFWwindow* window) noexcept {
				glfwSetCursorPosCallback(window, NULL);
			}

			static void setViewport(GLfloat minX, GLfloat maxX, GLfloat minY, GLfloat maxY) noexcept {
				Mouse::minX = minX;
				Mouse::maxX = maxX;
				Mouse::minY = minY;
				Mouse::maxY = maxY;
			}

			static void setX(GLfloat x) noexcept {
				Mouse::x = x;
				if(Mouse::x < minX) Mouse::x = Mouse::minX;
				if(Mouse::x > maxX) Mouse::x = Mouse::maxX;
			}

			static void setY(GLfloat y) noexcept {
				Mouse::y = y;
				if(Mouse::y < minY) Mouse::y = Mouse::minY;
				if(Mouse::y > maxY) Mouse::y = Mouse::maxY;
			}

			static void setXY(GLfloat x, GLfloat y) noexcept {
				Mouse::setX(x);
				Mouse::setY(y);
			}

			static GLfloat getX(bool normalized) noexcept {
				if(!normalized)
					return Mouse::x;
				return 2 * ((Mouse::x - Mouse::minX) / (Mouse::maxX - Mouse::minX)) - 1.0f;
			}

			static GLfloat getY(bool normalized, bool inversed) noexcept {
				auto y = Mouse::y;
				if(inversed) 
					y = Mouse::maxY - y;
				if(!normalized) 
					return y;
				return 2 * ((y - Mouse::minY) / (Mouse::maxY - Mouse::minY)) - 1.0f;
			}
			
		private:
			static inline GLfloat minX, maxX, minY, maxY;
			static inline GLfloat x, y;
		};

	}
}