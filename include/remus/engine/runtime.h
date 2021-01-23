#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <remus/engine/window.h>
#include <remus/logging/logger.h>
#include <remus/engine/driver/driver.h>
#include <remus/engine/context.h>

namespace remus {
	namespace engine {

		class Runtime {
		public:
			Runtime();
			Runtime(Window* mainWindow);

			void run(driver::Driver* driver);

			Runtime* setMainWindow(Window* win) noexcept;
			Runtime* setTPS(GLint tps) noexcept;

			Context* getContext() noexcept;

			virtual ~Runtime();

		protected:
			Window* mainWindow = NULL;
			GLint TPS = 30;
			Context* context;

		protected:
			static void initEnvironment();
			static void destroyEnvironment();

		protected:
			inline static GLint openGLMajor = 3, openGLMinor = 3;
			inline static GLint openRuntimes = 0;
		};

	}
}