#pragma once

#include <glad/glad.h>
#include <vector>

namespace remus {
	namespace gfx {
		namespace buffers {

			class VBO {
			public:
				VBO();

				inline void bind() noexcept {
					glBindBuffer(GL_ARRAY_BUFFER, this->ID);
				}

				inline void addDataStatic(void* data, size_t size) noexcept {
					glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); 
				}

				inline void addDataStatic(std::vector<GLfloat> v) noexcept { 
					this->addDataStatic(&v[0], v.size()*sizeof(GLfloat));
				};

				inline void unbind() noexcept { 
					glBindBuffer(GL_ARRAY_BUFFER, 0); 
				};

				inline GLuint getID() noexcept { 
					return this->ID;
				};

				virtual ~VBO();
			private:
				GLuint ID;
			};

		}
	}
}