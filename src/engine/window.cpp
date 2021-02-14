#include <remus/engine/window.h>

namespace remus {
	namespace engine {

		Window::Window(GLint width, GLint height, std::string title, bool fullscreen, Window* share) {
			if(width <= 0) throw std::invalid_argument("Width less than or equal to 0");
			if(height <= 0) throw std::invalid_argument("Height less than or equal to 0");

			this->monitor = NULL;
			if(fullscreen) {
				this->monitor = glfwGetPrimaryMonitor();
				if(this->monitor == NULL) {
					throw std::runtime_error("GLFW: Unable to get primary monitor.");
				}
			}

			this->width = width;
			this->height = height;
			this->title = title;
			this->fullscreen = fullscreen;

			GLFWwindow* sharedWindow = NULL;
			if(share != NULL) {
				sharedWindow = share->getWindow();
			}

			this->window = glfwCreateWindow(width, height, this->title.c_str(), this->monitor, sharedWindow);
			if(share != NULL) {
				this->glPointersLoaded = share->isGlPointersLoaded();
			}

			// Create utils
			this->mouse = new utils::Mouse(this->window);
			this->mouse->setViewport(0, this->width, 0, this->height);
		}

		void Window::clear() noexcept {
			glClear(this->clearMode); // No check for isCurrent for performance
		}

		void Window::update() noexcept {
			glfwSwapBuffers(this->window);
		}

		Window* Window::setMouseInputNormal() noexcept {
			glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			return this;
		}

		Window* Window::setMouseInputHidden() noexcept {
			glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			return this;
		}

		Window* Window::setMouseInputBound() noexcept {
			glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			return this;
		}

		Window* Window::makeCurrent() {
			this->isCurrent = true;
			glfwMakeContextCurrent(this->window);
			return this;
		}

		Window* Window::detach() noexcept {
			if(this->isCurrent) {
				glfwMakeContextCurrent(NULL);
				this->isCurrent = false;
			}
			return this;
		}

		Window* Window::refreshGLContext() {
			if(!this->isCurrent) {
				throw std::logic_error("Cannot refresh GL context on non-current window");
			}

			if(!this->glPointersLoaded) {
				this->loadGlPointers();
			}

			// Reset states
			this->clearMode = GL_COLOR_BUFFER_BIT;

			// Depth Test
			if(this->depthTest) {
				glEnable(GL_DEPTH_TEST);
				this->clearMode |= GL_DEPTH_BUFFER_BIT;
			} else {
				glDisable(GL_DEPTH_TEST);
			}

			// Blend
			if(this->blend) {
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			} else {
				glDisable(GL_BLEND);
			}

			// MSAA
			glfwWindowHint(GLFW_SAMPLES, this->msaa);
			if(this->msaa > 0) {
				glEnable(GL_MULTISAMPLE);
			} else {
				glDisable(GL_MULTISAMPLE);
			}

			// Clear color
			glClearColor(this->clearColor.r, this->clearColor.g, this->clearColor.b, this->clearColor.a);

			// Viewport
			glViewport(0, 0, this->width, this->height);

			return this;
		}

		Window* Window::loadGlPointers() {
			if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
				throw std::runtime_error("Failed to initialize GLAD");
			}
			this->glPointersLoaded = true;
			return this;
		}

		Window* Window::setGlDepthTest(bool value) noexcept {
			this->depthTest = value;
			return this;
		}

		Window* Window::setGlBlend(bool value) noexcept {
			this->blend = value;
			return this;
		}

		Window* Window::setMSAA(GLint value) noexcept {
			if(value < 0) {
				logger::logWarning("Unable to set MSAA to a negative value.");
				return this;
			}

			this->msaa = value;
			return this;
		}

		Window* Window::setClearColor(glm::vec4 rgba) noexcept {
			this->clearColor = rgba;
			return this;
		}

		Window* Window::setClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) noexcept {
			return this->setClearColor(glm::vec4(r, g, b, a));
		}	

		Window::~Window() {
			delete this->mouse;
			glfwDestroyWindow(this->window);
		}
	}
}