#include <remus/gfx/texture/writableTexture2d.h>

namespace remus {
	namespace gfx {
		namespace texture {

			WritableTexture2D::WritableTexture2D(GLint width, GLint height) 
				: fbo(new buffers::FBO()), rbo(new buffers::RBO()) 
			{
				this->fbo->bind();
				this->rbo->bind();
				this->bind();

				this->genTexture(GL_RGBA, width, height, NULL);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->getID(), 0);

				this->rbo->createStorageDepth24Stencil8(width, height);
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->rbo->getID());

				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				if(!this->fbo->complete()) {
					logger::logError("WritableTexture2D: Framebuffer not complete.");
				}

				this->fbo->unbind();
				this->rbo->unbind();
				this->unbind();
			}

			void WritableTexture2D::startWrite() noexcept {
				glGetIntegerv(GL_VIEWPORT, this->viewPortSize); // Save current viewport size
				glBindFramebuffer(GL_FRAMEBUFFER, this->fbo->getID());
				glViewport(0, 0, this->width, this->height); // Set viewport to framebuffer size
			}
			
			void WritableTexture2D::stopWrite() noexcept {
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
				glViewport(this->viewPortSize[0], this->viewPortSize[1], this->viewPortSize[2], this->viewPortSize[3]); // Restore viewport size
			}

			WritableTexture2D::~WritableTexture2D() {
				delete this->fbo;
				delete this->rbo;
			}
		}
	}
}