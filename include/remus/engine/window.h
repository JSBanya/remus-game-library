#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stdexcept>
#include <string>
#include <remus/gfx/context.h>
#include <remus/utils/mouse.h>
#include <remus/utils/keyboard.h>
#include <remus/utils/screen.h>
#include <remus/gfx/shaders/shaderProgram.h>
#include <remus/logging/logger.h>

namespace remus {
	namespace engine {

		class Window {
		public:
			Window(GLint width, GLint height, GLint screenWidth, GLint screenHeight, std::string title, bool fullscreen = true, GLint multisample = 0, Window* share = NULL);
			
			void beginDraw() noexcept;
			void endDraw() noexcept;
			void update(gfx::shaders::ShaderProgram* postprocessor = nullptr) noexcept;
			void clear() noexcept;
			
			Window* setMouseInputNormal() noexcept; // Makes the cursor visible and behaving normally
			Window* setMouseInputHidden() noexcept; // Makes the cursor invisible when it is over the content area of the window but does not restrict the cursor from leaving
			Window* setMouseInputBound() noexcept; // Hides and grabs the cursor, providing virtual and unlimited cursor movement

			Window* attach();
			Window* detach() noexcept;
			void close();

			inline gfx::Context* context() noexcept { return this->openGLContext; };

			inline utils::Mouse* getMouse() noexcept { return this->mouse; };
			inline utils::Keyboard* getKeyboard() noexcept { return this->keyboard; };
			inline GLFWwindow* getWindow() noexcept { return this->window; };
			inline GLFWmonitor* getMonitor() noexcept { return this->monitor; };
			inline GLint getWidth() noexcept { return this->width; };
			inline GLint getHeight() noexcept { return this->height; };
			inline GLint getMultisample() noexcept { return this->multisample; };
			inline std::string getTitle() noexcept { return this->title; };
			inline bool isFullscreen() noexcept { return this->fullscreen; };

			virtual ~Window();

		protected:
			void assertAttached();
			void loadGlPointers();

		protected:
			gfx::Context* openGLContext;
			utils::Screen* screen;
			utils::Mouse* mouse;
			utils::Keyboard* keyboard;

			GLFWwindow* window;
			GLFWmonitor* monitor;

			GLint width, height;
			GLint screenWidth, screenHeight;
			GLint multisample;
			std::string title;
			bool fullscreen;

		protected:
			inline static GLFWwindow* currentWindow = nullptr;
			inline static GLint openGLMajor = 4, openGLMinor = 3;
			inline static GLint openWindows = 0;

			static void initEnvironment();
			static void destroyEnvironment();
		};

	}
}