#include <remus/engine/window.h>

namespace remus {
	namespace engine {

		Window::Window(GLint width, GLint height, GLint screenWidth, GLint screenHeight, std::string title, bool fullscreen, GLint multisample, Window* share) {
			logging::Logger::logNotice("Creating window (width=" + std::to_string(width) 
				+ ", height=" + std::to_string(height) 
				+ ", screenWidth=" + std::to_string(screenWidth)
				+ ", screenHeight=" + std::to_string(screenHeight)
				+ ", title=" + title
				+ ", fullscreen=" + (fullscreen ? "True": "False")
				+ ", multisample=" + std::to_string(multisample)
				+  (share == nullptr ? "" : ", shared=" + share->getTitle())
			);
			
			if(width <= 0) throw std::invalid_argument("Width less than or equal to 0");
			if(height <= 0) throw std::invalid_argument("Height less than or equal to 0");
			if(screenWidth <= 0) throw std::invalid_argument("Buffer Width less than or equal to 0");
			if(screenHeight <= 0) throw std::invalid_argument("Buffer Height less than or equal to 0");
			if(multisample < 0) throw std::invalid_argument("Multisample less than 0");

			// Init OpenGL as needed
			if(Window::openWindows == 0) {
				logging::Logger::logNotice("Performing first time graphics environment setup.");
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
			this->screenWidth = screenWidth;
			this->screenHeight = screenHeight;
			this->title = title;
			this->fullscreen = fullscreen;
			this->multisample = multisample;

			GLFWwindow* sharedWindow = NULL;
			if(share != NULL) {
				sharedWindow = share->getWindow();
				this->openGLContext = share->context();
			} else {
				this->openGLContext = new gfx::Context();
			}

			this->window = glfwCreateWindow(width, height, this->title.c_str(), this->monitor, sharedWindow);
			this->attach();
			this->loadGlPointers();

			// Setup context
			this->openGLContext->setViewport(this->width, this->height);
			this->openGLContext->setMSAA(this->multisample);
			this->openGLContext->apply();
				
			// Create utils
			this->screen = new utils::Screen(this->screenWidth, this->screenHeight, this->multisample);
			this->mouse = new utils::Mouse(this->window);
			this->mouse->setViewport(0, this->width, 0, this->height);
			this->keyboard = new utils::Keyboard(this->window);
		}

		void Window::beginDraw() noexcept {
			this->assertAttached();
			this->screen->getFBO().bind();
			this->openGLContext->setViewport(this->screenWidth, this->screenHeight);
			this->clear();
		}

		void Window::endDraw() noexcept {
			this->assertAttached();
			this->screen->getFBO().unbind();
			this->openGLContext->setViewport(this->width, this->height);
		}

		void Window::update(gfx::shaders::ShaderProgram* postprocessor) noexcept {
			this->openGLContext->doClear(GL_COLOR_BUFFER_BIT);
			if(postprocessor == nullptr) {
				// No post processor specified
				// Simply blit color buffer
				glBindFramebuffer(GL_READ_FRAMEBUFFER, this->screen->getFBO().getID());
				glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
				glBlitFramebuffer(0, 0, this->screenWidth, this->screenHeight, 0, 0, this->width, this->height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
				glfwSwapBuffers(this->window);
				return;
			}

			postprocessor->bind();

			// Setup for rendering screen quad
			auto wasDepthTestEnabled = this->openGLContext->isDepthTestEnabled();
			this->openGLContext->setDepthTest(false);

			// Set screen texture
			glActiveTexture(GL_TEXTURE0);
			postprocessor->setUniform("screen", 0);
			if(this->multisample != 0) {
				postprocessor->setUniform("multisample", this->multisample);
				postprocessor->setUniform("vp_width", this->screenWidth);
				postprocessor->setUniform("vp_height", this->screenHeight);
				glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, this->screen->getTexture());
			} else {
				glBindTexture(GL_TEXTURE_2D, this->screen->getTexture());
			}

			// Render screen quad
			this->screen->getMesh()->drawTriangles();

			postprocessor->unbind();
			glfwSwapBuffers(this->window);

			// Set back old context state
			this->openGLContext->setDepthTest(wasDepthTestEnabled);
		}

		void Window::clear() noexcept {
			this->openGLContext->doClear();
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
			if(this->screen) 
				delete this->screen;
			glfwDestroyWindow(this->window);

			Window::openWindows -= 1;
			if(Window::openWindows == 0) {
				logging::Logger::logNotice("Tearing down graphics environment (no more open windows).");
				Window::destroyEnvironment();
			}
		}

		void Window::assertAttached() {
			if(Window::currentWindow != this->window) 
				throw std::logic_error("Window is not attached.");
		}

		void Window::initEnvironment() {
			logging::Logger::logNotice("Initializing GLFW - Core Profile " + std::to_string(Window::openGLMajor) + "." + std::to_string(Window::openGLMinor));
			glfwInit();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		}

		void Window::destroyEnvironment() {
			logging::Logger::logNotice("Destroying GLFW.");
			glfwTerminate();
		}
	}
}