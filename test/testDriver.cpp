#include "testDriver.h"

TestDriver::TestDriver(remus::engine::Window* window, remus::engine::Cache* cache) : remus::engine::scene::Driver(cache) {
	this->camera = new remus::gfx::view::PerspectiveCamera(70, Settings::width, Settings::height, 0.1, 100, remus::gfx::view::CameraAxisType::FIXED_PITCH);

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

TestDriver::~TestDriver() {
	for(auto scene : this->activeScenes) {
		delete scene;
	}
	delete this->camera;
}