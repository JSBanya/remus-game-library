#pragma once

#include <glad/glad.h>

namespace remus {
	namespace gfx {
		namespace buffers {

			class FBO {
			public:
				FBO();

				inline void bind() noexcept {
					glBindFramebuffer(GL_FRAMEBUFFER, this->ID);
				}

				static bool complete() noexcept {
					// Operates on the currently bound frame buffer
					return (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
				}

				inline void unbind() noexcept { 
					glBindFramebuffer(GL_FRAMEBUFFER, 0); 
				};

				inline GLuint getID() noexcept { 
					return this->ID;
				};

				virtual ~FBO();
			private:
				GLuint ID;
			};

		}
	}
}