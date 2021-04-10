#include <remus/engine/render/pipeline.h>

namespace remus {
	namespace engine {
		namespace render {
			
			Pipeline::Pipeline(GLint width, GLint height, GLint multisample) {
				if(multisample < 0)
					throw std::invalid_argument("Cannot set multisample to a value less than 0.");

				this->width = width;
				this->height = height;
				this->multisample = multisample;

				this->screenRectangle = new gfx::models::Rectangle(2.0f, 2.0f, gfx::models::RectangleNormalized::NONE, false);
				this->screenMesh = this->screenRectangle->getMesh("rectangle");

				/* ***********************
				Framebuffer configuration
				************************ */
				this->fbo.bind();

				// Add color attachment
				glGenTextures(1, &this->textureID); 

				if(multisample) {
					glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, this->textureID);
					glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, this->multisample, GL_RGB, width, height, GL_TRUE);
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, this->textureID, 0);
				} else {
					glBindTexture(GL_TEXTURE_2D, this->textureID);
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->textureID, 0);
				}

				// Add RBO depth/stencil attachment
				this->rbo.bind();
				if(multisample) {
					this->rbo.createStorageDepth24Stencil8Multisample(width, height, multisample);
				} else {
					this->rbo.createStorageDepth24Stencil8(width, height);
				}
				
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->rbo.getID());

				// Clear
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				// Check for completeness
				if(!this->fbo.complete()) {
					throw std::runtime_error("Screen framebuffer not complete.");
				}

				this->fbo.unbind();

				/* ***********************
				Context configuration
				************************ */
				this->openGLContext.setViewport(this->width, this->height);
				this->openGLContext.setMSAA(this->multisample);
				this->openGLContext.apply();
			}

			void Pipeline::swapBuffers(scene::Driver* driver, Window* window) {
				window->assertAttached();

				gfx::shaders::ShaderProgram* postprocessor;
				if(this->multisample) {
					postprocessor = driver->getPostProcessorMS();
				} else {
					postprocessor = driver->getPostProcessor();
				}

				this->openGLContext.doClear(GL_COLOR_BUFFER_BIT);
				if(postprocessor == nullptr) {
					// No post processor specified
					// Simply blit color buffer
					glBindFramebuffer(GL_READ_FRAMEBUFFER, this->fbo.getID());
					glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
					glBlitFramebuffer(0, 0, this->width, this->height, 0, 0, window->getWidth(), window->getHeight(), GL_COLOR_BUFFER_BIT, GL_NEAREST);
					glfwSwapBuffers(window->getWindow());
					return;
				}

				// Has a postprocessor
				postprocessor->bind();

				// Setup for rendering screen quad
				auto wasDepthTestEnabled = this->openGLContext.isDepthTestEnabled();
				this->openGLContext.setDepthTest(false);

				// Set screen texture
				glActiveTexture(GL_TEXTURE0);
				postprocessor->setUniform("screen", 0);
				if(this->multisample) {
					postprocessor->setUniform("multisample", this->multisample);
					postprocessor->setUniform("vp_width", window->getWidth());
					postprocessor->setUniform("vp_height", window->getHeight());
					glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, this->textureID);
				} else {
					glBindTexture(GL_TEXTURE_2D, this->textureID);
				}

				// Render screen quad
				this->screenMesh->drawTriangles();
				postprocessor->unbind();
				glfwSwapBuffers(window->getWindow());

				// Set back old context state
				this->openGLContext.setDepthTest(wasDepthTestEnabled);
			}

			Pipeline::~Pipeline() {
				glDeleteTextures(1, &this->textureID);
				delete this->screenRectangle;
			}

		}
	}
}