#pragma once

#include <glad/glad.h>
#include <remus/gfx/buffers/fbo.h>
#include <remus/gfx/buffers/rbo.h>
#include <remus/gfx/shaders/shaderProgram.h>
#include <remus/gfx/models/rectangle.h>
#include <remus/gfx/models/mesh.h>
#include <stdexcept>

namespace remus {
	namespace utils {

		class Screen {
		public:
			Screen(GLint width, GLint height, GLint multisample = 0);

			inline gfx::buffers::FBO& getFBO() noexcept {
				return this->fbo;
			}

			inline GLuint getTexture() noexcept {
				return this->textureID;
			}

			inline gfx::models::Mesh* getMesh() noexcept {
				return this->screenMesh;
			}

			inline GLint getWidth() noexcept {
				return this->width;
			}

			inline GLint getHeight() noexcept {
				return this->height;
			}

			inline GLint getMultisample() noexcept {
				return this->multisample;
			}

			~Screen();
		private:
			GLint width, height, multisample;
			gfx::models::Rectangle* screenRectangle;
			gfx::models::Mesh* screenMesh;

			GLuint textureID;
			gfx::buffers::FBO fbo;
			gfx::buffers::RBO rbo;
		};

	}
}