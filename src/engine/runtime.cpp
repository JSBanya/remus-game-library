#include <remus/engine/runtime.h>

namespace remus {
	namespace engine {

		Runtime::Runtime() {
			
		}

		void Runtime::run(Window* window, scene::Driver* driver, render::Pipeline* pipeline, GLint TPS) {
			Logger::logNotice("Runtime started.");

			auto startTime = glfwGetTime();
			auto lastTick = startTime;
			auto lastFrame = startTime;
			auto lastSecond = startTime;

			auto tps = 0, fps = 0;
			auto totalTicks = 0;
			const GLfloat TICK_RATE = 1.0f / TPS;
			while(!glfwWindowShouldClose(window->getWindow())) {
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
				auto delta = currentTime - lastFrame;
				lastFrame = currentTime;
				driver->render(timeSinceStart, delta);

				pipeline->draw(driver);
				pipeline->swapBuffers(driver, window);

				fps++;

				if(timeSinceStart - lastSecond >= 1.0f) {
					Logger::logNotice("FPS: " + std::to_string(fps) + " | TPS: " + std::to_string(tps));
					fps = 0;
					tps = 0;
					lastSecond += 1.0f;
				}
			}
		}

		Runtime::~Runtime() {

		}
	}
}