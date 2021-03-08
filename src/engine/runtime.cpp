#include <remus/engine/runtime.h>

namespace remus {
	namespace engine {

		Runtime::Runtime() {
			this->context = new Context();
		}

		Runtime::Runtime(Window* mainWindow) : Runtime() {
			this->setMainWindow(mainWindow);
		}

		void Runtime::run(scene::Driver* driver) {
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
				driver->draw();

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
			delete this->context;
		}
	}
}