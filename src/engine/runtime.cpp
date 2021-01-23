#include <remus/engine/runtime.h>

namespace remus {
	namespace engine {

		Runtime::Runtime() {
			if(Runtime::openRuntimes == 0) {
				Runtime::initEnvironment();
				logger::logNotice("Performing first time runtime setup.");
			}

			this->context = new Context();
		}

		Runtime::Runtime(Window* mainWindow) : Runtime() {
			this->setMainWindow(mainWindow);
		}

		void Runtime::run(driver::Driver* driver) {
			if(this->mainWindow == NULL) {
				throw std::runtime_error("No main window set.");
			}

			logger::logNotice("Runtime started.");

			auto startTime = glfwGetTime();
			auto lastTick = startTime;
			auto lastFrame = startTime;
			auto lastSecond = startTime;

			auto tps = 0, fps = 0;
			auto totalTicks = 0;
			const GLfloat TICK_RATE = 1.0f / this->TPS;
			while(!glfwWindowShouldClose(this->mainWindow->getWindow())) {
				auto currentTime = glfwGetTime();
				auto timeSinceStart = currentTime - startTime;

				// Process inputs
				glfwPollEvents();

				// Set context
				driver->setContext(this->context);

				// Perform ticks
				while(timeSinceStart - lastTick >= TICK_RATE) {
					driver->tick(totalTicks);
					lastTick += TICK_RATE;
					tps++;
					totalTicks++;
				}

				// Perform renders
				this->mainWindow->clear();

				auto delta = currentTime - lastFrame;
				lastFrame = currentTime;
				driver->render(timeSinceStart, delta);

				this->mainWindow->update();
				fps++;

				if(timeSinceStart - lastSecond >= 1.0f) {
					logger::logNotice("FPS: " + std::to_string(fps) + " | TPS: " + std::to_string(tps));
					fps = 0;
					tps = 0;
					lastSecond += 1.0f;
				}
			}
		}

		Runtime* Runtime::setMainWindow(Window* win) noexcept { 
			if(win == NULL) {
				logger::logWarning("Attempted to set runtime window to NULL.");
				return this;
			}
			this->mainWindow = win; 
			return this;
		}

		Runtime* Runtime::setTPS(GLint tps) noexcept {
			this->TPS = tps;
			return this;
		}

		Context* Runtime::getContext() noexcept {
			return this->context;
		}


		Runtime::~Runtime() {
			Runtime::openRuntimes -= 1;
			if(Runtime::openRuntimes == 0) {
				logger::logNotice("Tearing down runtime environment (no more open runtimes).");
				Runtime::destroyEnvironment();
			}

			delete this->context;
		}

		void Runtime::initEnvironment() {
			logger::logNotice("Initializing GLFW - Core Profile " + std::to_string(Runtime::openGLMajor) + "." + std::to_string(Runtime::openGLMinor));
			glfwInit();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		}

		void Runtime::destroyEnvironment() {
			logger::logNotice("Destroying GLFW.");
			glfwTerminate();
		}

	}
}