#pragma once

#include <glad/glad.h>

namespace remus {
	namespace gfx {
		namespace buffers {

			class RBO {
			public:
				RBO();

				inline void bind() noexcept {
					glBindRenderbuffer(GL_RENDERBUFFER, this->ID);
				}

				static void createStorage(GLenum storageType, GLsizei width, GLsizei height) noexcept {
					glRenderbufferStorage(GL_RENDERBUFFER, storageType, width, height);
				}

				static void createStorageMultisample(GLenum storageType, GLsizei width, GLsizei height, GLint multisample) noexcept {
					glRenderbufferStorageMultisample(GL_RENDERBUFFER, multisample, storageType, width, height);
				}

				static void createStorageDepth24Stencil8(GLsizei width, GLsizei height) noexcept {
					RBO::createStorage(GL_DEPTH24_STENCIL8, width, height);
				}

				static void createStorageDepth24Stencil8Multisample(GLsizei width, GLsizei height, GLint multisample) noexcept {
					RBO::createStorageMultisample(GL_DEPTH24_STENCIL8, width, height, multisample);
				}

				inline void unbind() noexcept { 
					glBindRenderbuffer(GL_RENDERBUFFER, 0); 
				};

				inline GLuint getID() noexcept { 
					return this->ID;
				};

				virtual ~RBO();
			private:
				GLuint ID;
			};

		}
	}
}