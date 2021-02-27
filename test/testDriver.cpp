#include "testDriver.h"

TestDriver::TestDriver(remus::engine::Context* context, remus::utils::Mouse* mouse) : remus::engine::scene::Driver(context) {
	// Setup scene
	this->addScene(new TestScene(context, mouse));
}

TestDriver::~TestDriver() {
	for(auto scene : this->activeScenes) {
		delete scene;
	}
}