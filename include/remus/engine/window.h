#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stdexcept>
#include <string>
#include <remus/utils/mouse.h>
#include <remus/utils/keyboard.h>
#include <remus/gfx/shaders/shaderProgram.h>
#include <remus/logging/logger.h>

namespace remus {
	namespace engine {

		class Window {
		public:
			Window(GLint width, GLint height, std::string title, bool fullscreen = true, Window* share = NULL);
			
			Window* setMouseInputNormal() noexcept; // Makes the cursor visible and behaving normally
			Window* setMouseInputHidden() noexcept; // Makes the cursor invisible when it is over the content area of the window but does not restrict the cursor from leaving
			Window* setMouseInputBound() noexcept; // Hides and grabs the cursor, providing virtual and unlimited cursor movement

			Window* attach();
			Window* detach() noexcept;
			void close();

			inline utils::Mouse* getMouse() noexcept { return this->mouse; };
			inline utils::Keyboard* getKeyboard() noexcept { return this->keyboard; };
			inline GLFWwindow* getWindow() noexcept { return this->window; };
			inline GLFWmonitor* getMonitor() noexcept { return this->monitor; };
			inline GLint getWidth() noexcept { return this->width; };
			inline GLint getHeight() noexcept { return this->height; };
			inline std::string getTitle() noexcept { return this->title; };
			inline bool isFullscreen() noexcept { return this->fullscreen; };

			void assertAttached();

			virtual ~Window();

		protected:
			void loadGlPointers();

		protected:
			utils::Mouse* mouse;
			utils::Keyboard* keyboard;

			GLFWwindow* window;
			GLFWmonitor* monitor;

			GLint width, height;
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