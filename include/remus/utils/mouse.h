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
				if(this->x < minX) this->x = this->minX;
				if(this->x > maxX) this->x = this->maxX;
			}

			inline void setY(GLfloat y) noexcept {
				this->y = y;
				if(this->y < minY) this->y = this->minY;
				if(this->y > maxY) this->y = this->maxY;
			}

			inline void setXY(GLfloat x, GLfloat y) noexcept {
				this->setX(x);
				this->setY(y);
			}

			inline GLfloat getX(bool normalized) noexcept {
				if(!normalized)
					return this->x;
				return 2 * ((this->x - this->minX) / (this->maxX - this->minX)) - 1.0f;
			}

			inline GLfloat getY(bool normalized, bool inversed) noexcept {
				auto y = this->y;
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