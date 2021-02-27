#include "testDriver.h"

TestDriver::TestDriver(remus::engine::Context* context) : remus::engine::scene::Driver(context) {
	// Setup scene
	this->addScene(new TestScene(context));
}

TestDriver::~TestDriver() {
	for(auto scene : this->activeScenes) {
		delete scene;
	}
}