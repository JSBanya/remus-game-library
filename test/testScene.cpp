#include "testScene.h"

TestScene::TestScene(remus::engine::Context* context, remus::gfx::view::Camera* camera, remus::utils::Mouse* mouse, remus::utils::Keyboard* keyboard) 
	: remus::engine::scene::Scene("Test Scene", camera, context) 
{
	this->mouse = mouse;
	this->keyboard = keyboard;

	this->cubeEntity = new remus::gfx::entity::Entity(
							context->getModel("cube"), 
							context->getShaderProgram("test_shader"), 
							{context->getMaterial("cube_material")}, 
							{"Cube"}
						);
	this->addEntity(this->cubeEntity);
	this->cubeEntity->getModelMatrix().setPos(5.0f, 0.0f, 0.0f);

	this->ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	this->lights.addPointLight(glm::vec3(3.5f, 0.0f, 0.0f), glm::vec3(1.0, 1.0, 1.0), 1.0f, 0.0014, 0.000007);
}

void TestScene::tick(GLint num) {
	this->cubeEntity->getModelMatrix().rotateY(1.0f);
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
	delete this->cubeEntity;
}