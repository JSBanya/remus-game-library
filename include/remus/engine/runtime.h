#pragma once

#include <glad/glad.h>
#include <stdexcept>
#include <remus/engine/window.h>
#include <remus/logging/logger.h>
#include <remus/engine/scene/driver.h>
#include <remus/engine/cache.h>
#include <remus/gfx/texture/writableTexture2d.h>
#include <remus/engine/render/pipeline.h>

namespace remus {
	namespace engine {

		class Runtime {
		public:
			Runtime();

			void run(Window* window, scene::Driver* driver, render::Pipeline* pipeline, GLint TPS = 30);

			virtual ~Runtime();
		};

	}
}