#pragma once

#include <glad/glad.h>

#include <string>
#include <remus/gfx/texture/texture2d.h>
#include <remus/gfx/buffers/fbo.h>
#include <remus/gfx/buffers/rbo.h>
#include <remus/logging/logger.h>

namespace remus {
	namespace gfx {
		namespace texture {

			class WritableTexture2D : public Texture2D {
			public:
				WritableTexture2D(GLint width, GLint height);

				void startWrite() noexcept;
				void stopWrite() noexcept;

				virtual ~WritableTexture2D();

			private:
				void load(std::string); // No longer able to load

			private:
				buffers::FBO* fbo;
				buffers::RBO* rbo;

				GLint viewPortSize[4];
			};

		}
	}
}