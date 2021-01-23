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

				inline void addDataStatic(std::vector<GLfloat> v) noexcept { 
					glBufferData(GL_ARRAY_BUFFER, v.size()*sizeof(GLfloat), &v[0], GL_STATIC_DRAW); 
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