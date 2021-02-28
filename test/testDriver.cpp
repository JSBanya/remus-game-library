#include "testDriver.h"

TestDriver::TestDriver(remus::engine::Window* window, remus::engine::Context* context) : remus::engine::scene::Driver(context) {
	// Setup scene
	this->addScene(new TestScene(context, window->getMouse(), window->getKeyboard()));
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
}