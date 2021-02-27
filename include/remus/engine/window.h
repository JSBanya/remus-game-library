#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stdexcept>
#include <string>
#include <remus/utils/mouse.h>
#include <remus/logging/logger.h>

namespace remus {
	namespace engine {

		class Window {
		public:
			Window(GLint width, GLint height, std::string title, bool fullscreen = true, Window* share = NULL);
			
			void clear() noexcept;
			void update() noexcept;

			
			Window* setMouseInputNormal() noexcept; // Makes the cursor visible and behaving normally
			Window* setMouseInputHidden() noexcept; // Makes the cursor invisible when it is over the content area of the window but does not restrict the cursor from leaving
			Window* setMouseInputBound() noexcept; // Hides and grabs the cursor, providing virtual and unlimited cursor movement

			Window* attach();
			Window* detach() noexcept;

			Window* setViewport(GLint width, GLint height);
			Window* setGlDepthTest(bool value);
			Window* setGlBlend(bool value);
			Window* setMSAA(GLint value);
			Window* setClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

			inline bool isPointersLoaded() noexcept { return this->pointersLoaded; };
			inline utils::Mouse* getMouse() noexcept { return this->mouse; };
			inline GLFWwindow* getWindow() noexcept { return this->window; };
			inline GLFWmonitor* getMonitor() noexcept { return this->monitor; };
			inline GLint getWidth() noexcept { return this->width; };
			inline GLint getHeight() noexcept { return this->height; };
			inline std::string getTitle() noexcept { return this->title; };
			inline bool isFullscreen() noexcept { return this->fullscreen; };

			virtual ~Window();

		protected:
			void assertAttached();
			void loadGlPointers();

		protected:
			GLFWwindow* window;
			utils::Mouse* mouse;

			bool pointersLoaded;
			bool viewportSet = false;
			bool isCurrent = false;
			GLFWmonitor* monitor;
			GLint width, height;
			std::string title;
			bool fullscreen;

			// OpenGL
			glm::vec4 clearColor = glm::vec4(0, 0, 0, 1.0);
			GLint clearMode = GL_COLOR_BUFFER_BIT;

		protected:
			inline static GLint openGLMajor = 3, openGLMinor = 3;
			inline static GLint openWindows = 0;

			static void initEnvironment();
			static void destroyEnvironment();
		};

	}
}