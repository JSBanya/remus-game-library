#include <remus/engine/window.h>

namespace remus {
	namespace engine {

		Window::Window(GLint width, GLint height, std::string title, bool fullscreen, Window* share) {
			if(width <= 0) throw std::invalid_argument("Width less than or equal to 0");
			if(height <= 0) throw std::invalid_argument("Height less than or equal to 0");

			// Init OpenGL as needed
			if(Window::openWindows == 0) {
				logger::logNotice("Performing first time graphics environment setup.");
				Window::initEnvironment();
			}
			Window::openWindows += 1;

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
				this->pointersLoaded = share->isPointersLoaded();
			}

			this->window = glfwCreateWindow(width, height, this->title.c_str(), this->monitor, sharedWindow);

			// Create utils
			this->mouse = new utils::Mouse(this->window);
			this->mouse->setViewport(0, this->width, 0, this->height);
		}

		void Window::clear() noexcept {
			glClear(this->clearMode);
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

		Window* Window::attach() {
			this->isCurrent = true;
			glfwMakeContextCurrent(this->window);
			if(!this->isPointersLoaded()) {
				this->loadGlPointers();
			}
			if(!this->viewportSet) {
				this->setViewport(this->width, this->height);
			}
			return this;
		}

		Window* Window::detach() noexcept {
			if(this->isCurrent) {
				glfwMakeContextCurrent(NULL);
				this->isCurrent = false;
			}
			return this;
		}

		void Window::loadGlPointers() {
			if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
				throw std::runtime_error("Failed to initialize GLAD");
			}
			this->pointersLoaded = true;
		}

		Window* Window::setViewport(GLint width, GLint height) {
			this->assertAttached();

			glViewport(0, 0, this->width, this->height);
			this->viewportSet = true;
			return this;
		}

		Window* Window::setGlDepthTest(bool value) {
			this->assertAttached();

			if(value) {
				glEnable(GL_DEPTH_TEST);
				this->clearMode |= GL_DEPTH_BUFFER_BIT;
			} else {
				glDisable(GL_DEPTH_TEST);
				this->clearMode &= ~GL_DEPTH_BUFFER_BIT;
			}

			return this;
		}

		Window* Window::setGlBlend(bool value) {
			this->assertAttached();

			if(value) {
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			} else {
				glDisable(GL_BLEND);
			}
			return this;
		}

		Window* Window::setMSAA(GLint value) {
			this->assertAttached();

			if(value < 0) {
				logger::logWarning("Unable to set MSAA to a negative value.");
				return this;
			}

			glfwWindowHint(GLFW_SAMPLES, value);
			if(value > 0) {
				glEnable(GL_MULTISAMPLE);
			} else {
				glDisable(GL_MULTISAMPLE);
			}

			return this;
		}

		Window* Window::setClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
			glClearColor(r, g, b, a);
			this->clearMode |= GL_COLOR_BUFFER_BIT;
			return this;
		}	

		Window::~Window() {
			delete this->mouse;
			glfwDestroyWindow(this->window);

			Window::openWindows -= 1;
			if(Window::openWindows == 0) {
				logger::logNotice("Tearing down graphics environment (no more open windows).");
				Window::destroyEnvironment();
			}
		}

		void Window::assertAttached() {
			if(!this->isCurrent) 
				throw std::logic_error("Window is not attached.");
		}

		void Window::initEnvironment() {
			logger::logNotice("Initializing GLFW - Core Profile " + std::to_string(Window::openGLMajor) + "." + std::to_string(Window::openGLMinor));
			glfwInit();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		}

		void Window::destroyEnvironment() {
			logger::logNotice("Destroying GLFW.");
			glfwTerminate();
		}
	}
}