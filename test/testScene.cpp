#include "testScene.h"

TestScene::TestScene(remus::engine::Context* context, remus::utils::Mouse* mouse, remus::utils::Keyboard* keyboard) : remus::engine::scene::Scene("Test Scene", context) {
	this->addComponent(new TestComponent(context));
	this->activeCamera = new remus::gfx::view::PerspectiveCamera(90, Settings::width, Settings::height, 0.1, 100, remus::gfx::view::CameraAxisType::FIXED_PITCH);
	this->mouse = mouse;
	this->keyboard = keyboard;
}

void TestScene::render(GLfloat time, GLfloat delta) {
	auto x = mouse->getX(false, true);
	auto y = mouse->getY(false, true, true);

	if(!this->mouseCoordsInitialized) {
		// First time mouse initialization
		this->mouseCoordsInitialized = true;
		this->lastX = x;
		this->lastY = y;
	}

	auto diffX = x - lastX;
	this->lastX = x;

	auto diffY = y - lastY;
	this->lastY = y;

	// Handle keyboard inputs
	if(this->keyboard->isPressed(GLFW_KEY_A)) {
		this->activeCamera->addPosX(-1.0f * this->movementSpeed * delta);
	}

	if(this->keyboard->isPressed(GLFW_KEY_D)) {
		this->activeCamera->addPosX(this->movementSpeed * delta);
	}

	if(this->keyboard->isPressed(GLFW_KEY_W)) {
		this->activeCamera->addPosZ(this->movementSpeed * delta);
	}

	if(this->keyboard->isPressed(GLFW_KEY_S)) {
		this->activeCamera->addPosZ(-1.0f * this->movementSpeed * delta);
	}

	// Handle mouse inputs
	auto yaw = (diffX * this->sensitivity);
	auto pitch = (diffY * this->sensitivity);
	this->activeCamera->addYaw(yaw);

	auto currentPitch = this->activeCamera->getPitch();
	if(currentPitch+pitch > 60.0f) 
		this->activeCamera->setPitch(60.0f);
	else if(currentPitch+pitch < -60.0f) 
		this->activeCamera->setPitch(-60.0f);
	else 
		this->activeCamera->setPitch(currentPitch+pitch);

	Scene::render(time, delta);
}

TestScene::~TestScene() {
	for(auto c : this->getComponents()) {
		delete c;
	}
	delete this->activeCamera;
}