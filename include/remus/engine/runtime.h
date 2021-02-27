#pragma once

#include <glad/glad.h>
#include <stdexcept>
#include <remus/engine/window.h>
#include <remus/logging/logger.h>
#include <remus/engine/scene/driver.h>
#include <remus/engine/context.h>

namespace remus {
	namespace engine {

		class Runtime {
		public:
			Runtime();
			Runtime(Window* mainWindow);

			void run(scene::Driver* driver);

			Runtime* setMainWindow(Window* win) noexcept;
			Runtime* setTPS(GLint tps) noexcept;

			Context* getContext() noexcept;

			virtual ~Runtime();

		protected:
			Window* mainWindow = NULL;
			GLint TPS = 30;
			Context* context;
		};

	}
}