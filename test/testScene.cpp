#include "testScene.h"

TestScene::TestScene(remus::engine::Context* context) : remus::engine::scene::Scene("Test Scene", context) {
	this->addComponent(new TestComponent(context));
	this->activeCamera = new remus::gfx::view::PerspectiveCamera(90, Settings::width, Settings::height, 0.1, 100);
}

TestScene::~TestScene() {
	for(auto c : this->getComponents()) {
		delete c;
	}
	delete this->activeCamera;
}