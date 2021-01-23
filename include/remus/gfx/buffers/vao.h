#pragma once

#include <glad/glad.h>

namespace remus {
	namespace gfx {
		namespace buffers {

			class VAO {
			public:
				VAO();

				inline void bind() noexcept {
					glBindVertexArray(this->ID);
				}

				inline void addAttribute(GLint i, GLint size, GLint stride, GLint offset) noexcept {
					glVertexAttribPointer(i, size, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*) (offset * sizeof(GLfloat)) );
					glEnableVertexAttribArray(i);
				}

				inline void addAttributePacked(GLint i, GLint size) noexcept {
					this->addAttribute(i, size, size, 0);
				}

				inline void unbind() noexcept { 
					glBindVertexArray(0); 
				};

				inline GLuint getID() noexcept { 
					return this->ID;
				};

				virtual ~VAO();
			private:
				GLuint ID;
			};

		}
	}
}