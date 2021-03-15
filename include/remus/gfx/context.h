#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace remus {
	namespace gfx {

		class Context {
		public:
			inline void apply() {
				this->setBlend(this->isBlendEnabled(), this->getBlendSFactor(), this->getBlendDFactor());
				this->setDepthTest(this->isDepthTestEnabled());
				this->setViewport(this->getViewportWidth(), this->getViewportHeight());
				this->setClearColor(this->getClearColorR(), this->getClearColorG(), this->getClearColorB(), this->getClearColorA());
				this->setClearModeColor(this->getClearModeColor());
				this->setClearModeDepth(this->getClearModeDepth());
				this->setMSAA(this->getMSAA());
				this->setFaceCulling(this->isFaceCullingEnabled(), this->isFaceCullingCCW());
			}

			/***********
			* Blend
			***********/
			inline void setBlend(bool isEnabled, GLenum sfactor = GL_SRC_ALPHA, GLenum dfactor = GL_ONE_MINUS_SRC_ALPHA) {
				this->blend_isEnabled = isEnabled;
				this->blend_sfactor = sfactor;
				this->blend_dfactor = dfactor;

				if(isEnabled) {
					glEnable(GL_BLEND);
					glBlendFunc(sfactor, dfactor);
				} else {
					glDisable(GL_BLEND);
				}
			}

			inline bool isBlendEnabled() noexcept {
				return this->blend_isEnabled;
			}

			inline GLenum getBlendSFactor() noexcept {
				return this->blend_sfactor;
			}

			inline GLenum getBlendDFactor() noexcept {
				return this->blend_dfactor;
			}


			/***********
			* Depth Test
			***********/
			inline void setDepthTest(bool isEnabled) {
				this->depthTest_isEnabled = isEnabled;
				
				if(isEnabled) glEnable(GL_DEPTH_TEST);
				else glDisable(GL_DEPTH_TEST);
			}

			inline bool isDepthTestEnabled() noexcept {
				return this->depthTest_isEnabled;
			}


			/***********
			* Viewport
			***********/
			inline void setViewport(GLint width, GLint height) {
				this->viewport_width = width;
				this->viewport_height = height;
				glViewport(0, 0, width, height);
			}

			inline GLint getViewportWidth() noexcept {
				return this->viewport_width;
			}

			inline GLint getViewportHeight() noexcept {
				return this->viewport_height;
			}


			/***********
			* Clear
			***********/
			inline void setClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
				this->clearColor_r = r;
				this->clearColor_g = g;
				this->clearColor_b = b;
				this->clearColor_a = a;
				glClearColor(r, g, b, a);
			}

			inline GLfloat getClearColorR() noexcept {
				return this->clearColor_r;
			}

			inline GLfloat getClearColorG() noexcept {
				return this->clearColor_g;
			}

			inline GLfloat getClearColorB() noexcept {
				return this->clearColor_b;
			}

			inline GLfloat getClearColorA() noexcept {
				return this->clearColor_a;
			}

			inline void setClearModeColor(bool isEnabled) {
				this->clear_mode_color = isEnabled;
				this->recomputeClearMode();
			}

			inline bool getClearModeColor() noexcept {
				return this->clear_mode_color;
			}

			inline void setClearModeDepth(bool isEnabled) noexcept {
				this->clear_mode_depth = isEnabled;
				this->recomputeClearMode();
			}

			inline bool getClearModeDepth() noexcept {
				return this->clear_mode_depth;
			}

			void doClear(GLint clear_mode = -1) {
				if(clear_mode == -1)
					glClear(this->clear_mode);
				else
					glClear(clear_mode);
			}


			/***********
			* MSAA
			***********/
			inline void setMSAA(GLint value) {
				this->msaa = value;

				glfwWindowHint(GLFW_SAMPLES, value);
				if(value > 0) {
					glEnable(GL_MULTISAMPLE);
				} else {
					glDisable(GL_MULTISAMPLE);
				}
			}

			inline GLint getMSAA() {
				return this->msaa;
			}


			/***********
			* Face Culling
			***********/
			inline void setFaceCulling(bool isEnabled, bool ccw = true) {
				this->faceCulling_isEnabled = isEnabled;
				this->faceCulling_ccw = ccw;

				if(isEnabled) {
					glEnable(GL_CULL_FACE);
					glFrontFace((ccw ? GL_CCW : GL_CW));
				} else {
					glDisable(GL_CULL_FACE);
				}
			}

			inline bool isFaceCullingEnabled() noexcept {
				return this->faceCulling_isEnabled;
			}

			inline bool isFaceCullingCCW() noexcept {
				return this->faceCulling_ccw;
			}
			
		private:
			inline void recomputeClearMode() noexcept {
				this->clear_mode = 0;
				this->clear_mode |= (this->clear_mode_color ? GL_COLOR_BUFFER_BIT : 0);
				this->clear_mode |= (this->clear_mode_depth ? GL_DEPTH_BUFFER_BIT : 0);
			}

		private:
			bool blend_isEnabled = false;
			GLenum blend_sfactor = GL_SRC_ALPHA, blend_dfactor = GL_ONE_MINUS_SRC_ALPHA;

			bool depthTest_isEnabled = false;

			GLint viewport_width = 0, viewport_height = 0;

			GLint clear_mode = 0;
			bool clear_mode_color = false, clear_mode_depth = false;
			GLfloat clearColor_r = 1.0f, clearColor_g = 1.0f, clearColor_b = 1.0f, clearColor_a = 1.0f;

			GLint msaa = 0;

			bool faceCulling_isEnabled = false, faceCulling_ccw = true;
		};

	}
}