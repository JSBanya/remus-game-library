#include <remus/engine/window.h>

namespace remus {
	namespace engine {

		Window::Window(GLint width, GLint height, std::string title, bool fullscreen, Window* share) {
			Logger::logNotice("Creating window (width=" + std::to_string(width) 
				+ ", height=" + std::to_string(height) 
				+ ", title=" + title
				+ ", fullscreen=" + (fullscreen ? "True": "False")
				+  (share == nullptr ? "" : ", shared=" + share->getTitle())
			);
			
			if(width <= 0) throw std::invalid_argument("Width less than or equal to 0");
			if(height <= 0) throw std::invalid_argument("Height less than or equal to 0");

			// Init OpenGL as needed
			if(Window::openWindows == 0) {
				Logger::logNotice("Performing first time graphics environment setup.");
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
			}

			this->window = glfwCreateWindow(width, height, this->title.c_str(), this->monitor, sharedWindow);
			this->attach();
			this->loadGlPointers();

			// Create utils
			this->mouse = new utils::Mouse(this->window);
			this->mouse->setViewport(0, this->width, 0, this->height);
			this->keyboard = new utils::Keyboard(this->window);
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
			Window::currentWindow = this->window;
			glfwMakeContextCurrent(this->window);
			return this;
		}

		Window* Window::detach() noexcept {
			this->assertAttached();
			glfwMakeContextCurrent(NULL);
			Window::currentWindow = nullptr;
			return this;
		}

		void Window::close() {
			glfwSetWindowShouldClose(this->window, true);
		}

		void Window::loadGlPointers() {
			if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
				throw std::runtime_error("Failed to initialize GLAD");
			}
		}

		Window::~Window() {
			delete this->mouse;
			delete this->keyboard;
			glfwDestroyWindow(this->window);

			Window::openWindows -= 1;
			if(Window::openWindows == 0) {
				Logger::logNotice("Tearing down graphics environment (no more open windows).");
				Window::destroyEnvironment();
			}
		}

		void Window::assertAttached() {
			if(Window::currentWindow != this->window) 
				throw std::logic_error("Window is not attached.");
		}

		void Window::initEnvironment() {
			Logger::logNotice("Initializing GLFW - Core Profile " + std::to_string(Window::openGLMajor) + "." + std::to_string(Window::openGLMinor));
			glfwInit();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		}

		void Window::destroyEnvironment() {
			Logger::logNotice("Destroying GLFW.");
			glfwTerminate();
		}
	}
}