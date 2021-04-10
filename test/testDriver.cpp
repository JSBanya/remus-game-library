#include "testDriver.h"

TestDriver::TestDriver(engine::Window* window, engine::Cache* cache) : engine::scene::Driver(cache) {
	this->camera = new gfx::view::PerspectiveCamera(70, Settings::width, Settings::height, 0.1, 100, gfx::view::CameraAxisType::FIXED_PITCH);

	// Setup scene
	this->addScene(new TestScene(cache, camera, window->getMouse(), window->getKeyboard()));
	this->window = window;
	this->keyboard = window->getKeyboard();
}

void TestDriver::render(GLfloat time, GLfloat delta) {
	if(this->keyboard->isPressed(GLFW_KEY_ESCAPE)) {
		this->window->close();
	}

	Driver::render(time, delta);
}

gfx::shaders::ShaderProgram* TestDriver::getPostProcessor() noexcept {
	return this->cache->getShaderProgram("postprocessing");
}

gfx::shaders::ShaderProgram* TestDriver::getPostProcessorMS() noexcept {
	return this->cache->getShaderProgram("postprocessing_ms");
}

TestDriver::~TestDriver() {
	for(auto scene : this->activeScenes) {
		delete scene;
	}
	delete this->camera;
}