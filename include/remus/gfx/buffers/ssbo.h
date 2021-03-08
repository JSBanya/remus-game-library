#pragma once

#include <glad/glad.h>
#include <cstddef>

namespace remus {
	namespace gfx {
		namespace buffers {

			class SSBO {
			public:
				SSBO();

				inline void bind() noexcept {
					glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->ID);
				};

				inline void bindBufferBase(GLint index) {
					glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, this->ID);
				}

				inline void addBufferData(void *data, size_t size, GLenum usage) {
					glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, usage);
				}

				inline void addBufferDataStatic(void *data, size_t size) {
					this->addBufferData(data, size, GL_STATIC_DRAW);
				}

				inline void addBufferDataDynamic(void *data, size_t size) {
					this->addBufferData(data, size, GL_DYNAMIC_DRAW);
				}

				inline void updateBufferData(void *data, size_t size, size_t offset) {
					glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, size, data);
				}

				inline void unbind() noexcept {
					glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
				}

				inline GLuint getID() noexcept { 
					return this->ID;
				};

				virtual ~SSBO();
			private:
				GLuint ID;
			};

		}
	}
}