#pragma once

#include <glad/glad.h>
#include <vector>

namespace remus {
	namespace gfx {
		namespace buffers {

			class EBO {
			public:
				EBO();

				inline void bind() noexcept {
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID);
				}

				inline void addDataStatic(std::vector<GLuint> v) noexcept { 
					this->numIndices = v.size();
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, v.size()*sizeof(GLuint), &v[0], GL_STATIC_DRAW); 
				};

				inline void unbind() noexcept { 
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); 
				};

				inline GLuint getID() noexcept { 
					return this->ID;
				};

				inline GLuint getNumIndices() noexcept {
					return this->numIndices;
				}
				
				virtual ~EBO();
			private:
				GLuint ID;
				GLuint numIndices;
			};

		}
	}
}