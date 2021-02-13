#pragma once

#include <glad/glad.h>
#include <cstddef>

namespace remus {
	namespace gfx {
		namespace buffers {

			class VAO {
			public:
				VAO();

				inline void bind() noexcept {
					glBindVertexArray(this->ID);
				};

				inline void addAttribute(GLint i, GLint size, GLint stride, size_t offset) noexcept {
					glVertexAttribPointer(i, size, GL_FLOAT, GL_FALSE, stride, (void*)offset);
					glEnableVertexAttribArray(i);
				};

				inline void addAttributeAsFloat(GLint i, GLint size, GLint stride, GLuint offset) noexcept {
					this->addAttribute(i, size, stride * sizeof(GLfloat), offset * sizeof(GLfloat));
				};

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