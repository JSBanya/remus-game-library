#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>

namespace remus {
	namespace utils {

		class Mouse {
		public:
			Mouse(GLFWwindow* window);

			void setViewport(GLfloat minX, GLfloat maxX, GLfloat minY, GLfloat maxY) noexcept {
				this->minX = minX;
				this->maxX = maxX;
				this->minY = minY;
				this->maxY = maxY;
			}

			inline void setX(GLfloat x) noexcept {
				this->x = x;
			}

			inline void setY(GLfloat y) noexcept {
				this->y = y;
			}

			inline void setXY(GLfloat x, GLfloat y) noexcept {
				this->x = x;
				this->y = y;
			}

			inline GLfloat getX(bool clipped = false, bool normalized = false) noexcept {
				auto x = this->x;
				if(clipped) {
					if(x < this->minX) x = this->minX;
					if(x > this->maxY) x = this->maxX;
				}
				if(!normalized)
					return x;
				return 2 * ((x - this->minX) / (this->maxX - this->minX)) - 1.0f;
			}

			inline GLfloat getY(bool clipped = false, bool normalized = false, bool inversed = false) noexcept {
				auto y = this->y;
				if(clipped) {
					if(y < this->minY) y = this->minY;
					if(y > this->maxY) y = this->maxY;
				}
				if(inversed) 
					y = this->maxY - y;
				if(!normalized) 
					return y;
				return 2 * ((y - this->minY) / (this->maxY - this->minY)) - 1.0f;
			}

			~Mouse();
			
		private:
			GLFWwindow* window;
			GLfloat minX, maxX, minY, maxY;
			GLfloat x, y;
			
		private:
			static void posCallback(GLFWwindow* window, double xpos, double ypos);
			static inline std::unordered_map<GLFWwindow*, Mouse*> instances;
		};

	}
}