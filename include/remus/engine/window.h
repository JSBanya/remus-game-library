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

			Window* attachMouse() noexcept;
			Window* detachMouse() noexcept;
			Window* setMouseInputNormal() noexcept; // Makes the cursor visible and behaving normally
			Window* setMouseInputHidden() noexcept; // Makes the cursor invisible when it is over the content area of the window but does not restrict the cursor from leaving
			Window* setMouseInputBound() noexcept; // Hides and grabs the cursor, providing virtual and unlimited cursor movement

			Window* makeCurrent();
			Window* detach() noexcept;

			Window* refreshGLContext();

			Window* loadGlPointers();
			inline bool isGlPointersLoaded() noexcept { return this->glPointersLoaded; };
			
			Window* setGlDepthTest(bool value) noexcept;
			Window* setGlBlend(bool value) noexcept;
			Window* setMSAA(GLint value) noexcept;
			Window* setClearColor(glm::vec4 rgba) noexcept;
			Window* setClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) noexcept;

			inline GLFWwindow* getWindow() noexcept { return this->window; };
			inline GLFWmonitor* getMonitor() noexcept { return this->monitor; };
			inline GLint getWidth() noexcept { return this->width; };
			inline GLint getHeight() noexcept { return this->height; };
			inline std::string getTitle() noexcept { return this->title; };
			inline bool isFullscreen() noexcept { return this->fullscreen; };

			virtual ~Window();

		protected:
			GLFWwindow* window;

			bool isCurrent = false;
			GLFWmonitor* monitor;
			GLint width, height;
			std::string title;
			bool fullscreen;

			// OpenGL
			bool glPointersLoaded = false;
			bool depthTest = false;
			bool blend = false;
			GLint msaa = 0;
			glm::vec4 clearColor = glm::vec4(0, 0, 0, 1.0);
			GLint clearMode = GL_COLOR_BUFFER_BIT;
		};

	}
}