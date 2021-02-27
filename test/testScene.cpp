#include "testScene.h"

TestScene::TestScene(remus::engine::Context* context, remus::utils::Mouse* mouse) : remus::engine::scene::Scene("Test Scene", context) {
	this->addComponent(new TestComponent(context));
	this->activeCamera = new remus::gfx::view::PerspectiveCamera(90, Settings::width, Settings::height, 0.1, 100);
	this->mouse = mouse;
}

void TestScene::render(GLfloat time, GLfloat delta) {
	auto x = mouse->getX(false, true);
	auto y = mouse->getY(false, true, true);

	auto yaw = (90.0f * x * this->sensitivity);
	auto pitch = (90.0f * y * this->sensitivity);
	this->activeCamera->setYaw(yaw);
	this->activeCamera->setPitch(pitch);

	Scene::render(time, delta);
}

TestScene::~TestScene() {
	for(auto c : this->getComponents()) {
		delete c;
	}
	delete this->activeCamera;
}