#pragma once

#include <glad/glad.h>
#include <vector>
#include <stdexcept>
#include <remus/gfx/buffers/fbo.h>
#include <remus/gfx/buffers/rbo.h>
#include <remus/gfx/shaders/shaderProgram.h>
#include <remus/gfx/models/rectangle.h>
#include <remus/gfx/models/mesh.h>
#include <remus/engine/scene/driver.h>
#include <remus/engine/window.h>
#include <remus/gfx/context.h>

namespace remus {
	namespace engine {
		namespace render {

			class Pipeline {
			public:
				Pipeline(GLint width, GLint height, GLint multisample = 0);

				virtual void draw(scene::Driver* driver) = 0;
				virtual void swapBuffers(scene::Driver* driver, Window* window);

				inline gfx::Context& context() noexcept { return this->openGLContext; };

				virtual ~Pipeline();

			protected:

			protected:
				gfx::Context openGLContext;

				GLint width, height, multisample;
				gfx::models::Rectangle* screenRectangle;
				gfx::models::Mesh* screenMesh;

				GLuint textureID;
				gfx::buffers::FBO fbo;
				gfx::buffers::RBO rbo;
			};

		}
	}
}