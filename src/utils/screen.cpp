#include <remus/utils/screen.h>

namespace remus {
	namespace utils {

		Screen::Screen(GLint width, GLint height, bool multisample) {
			if(multisample)
				throw std::runtime_error("Multisample mode not implemented");

			this->width = width;
			this->height = height;

			this->screenRectangle = new gfx::models::Rectangle(2.0f, 2.0f, gfx::models::RectangleNormalized::NONE, false);
			this->screenMesh = this->screenRectangle->getMesh("rectangle");

			/* ***********************
			 Framebuffer configuration
			************************ */
			this->fbo.bind();

			// Add color attachment
			glGenTextures(1, &this->textureID); 
			glBindTexture(GL_TEXTURE_2D, this->textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->textureID, 0);

			// Add RBO depth/stencil attachment
			this->rbo.bind();
			this->rbo.createStorageDepth24Stencil8(width, height);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->rbo.getID());

			// Clear
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Check for completeness
			if(!this->fbo.complete()) {
				throw std::runtime_error("Screen framebuffer not complete.");
			}

			this->fbo.unbind();
		}

		Screen::~Screen() {
			glDeleteTextures(1, &this->textureID);
			delete this->screenRectangle;
		}

	}
}