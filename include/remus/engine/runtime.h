#pragma once

#include <glad/glad.h>
#include <stdexcept>
#include <remus/engine/window.h>
#include <remus/logging/logger.h>
#include <remus/engine/scene/driver.h>
#include <remus/engine/cache.h>
#include <remus/gfx/texture/writableTexture2d.h>

namespace remus {
	namespace engine {

		class Runtime {
		public:
			Runtime();
			Runtime(Window* mainWindow);

			void run(scene::Driver* driver);

			Runtime* setMainWindow(Window* win) noexcept;
			Runtime* setTPS(GLint tps) noexcept;

			Cache* getCache() noexcept;

			virtual ~Runtime();

		protected:
			Window* mainWindow = NULL;
			GLint TPS = 30;
			Cache* cache;
		};

	}
}