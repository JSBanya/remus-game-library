#include "testScene.h"

TestScene::TestScene(remus::engine::Context* context, remus::gfx::view::Camera* camera, remus::utils::Mouse* mouse, remus::utils::Keyboard* keyboard) 
	: remus::engine::scene::Scene("Test Scene", camera, context) 
{
	this->mouse = mouse;
	this->keyboard = keyboard;

	this->setup();
}

void TestScene::setup() {
	// Floor
	const int X_MIN = -10;
	const int X_MAX = 10;
	const int Z_MIN = -10;
	const int Z_MAX = 10;
	for(auto x = X_MIN; x < X_MAX; x+=2) {
		for(auto z = Z_MIN; z < Z_MAX; z+=2) {
			auto floorEntity = new remus::gfx::entity::Entity(
				context->getModel("floor"),
				context->getShaderProgram("test_shader"),
				{context->getMaterial("floor_material")},
				{"Plane"}
			);
			this->addEntity(floorEntity);
			floorEntity->getModelMatrix().setPos(x, 0.0f, z);
		}
	}

	// Cube
	this->cubeEntity = new remus::gfx::entity::Entity(
							context->getModel("cube"), 
							context->getShaderProgram("test_shader"), 
							{context->getMaterial("cube_material")}, 
							{"Cube"}
						);
	this->addEntity(this->cubeEntity);
	this->cubeEntity->getModelMatrix().setPos(3.0f, 1.0f, 0.0f);

	// Lighting
	this->ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	this->pointLights.add(glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, 0.0014, 0.000007);
	// this->directionaLights.add(glm::vec3(1.0, -0.5f, 1.0), glm::vec3(1.0, 1.0, 1.0));

	// Camera
	this->activeCamera->setPos(0, 1.0f, 0);
}

void TestScene::tick(GLint num) {
	this->cubeEntity->getModelMatrix().rotateY(1.5f);
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


	// Update lighting
	auto light = this->pointLights.get(0);
	glm::vec3 newColor = light->Color;

	const float COLOR_CHANGE_STEP = 2.0;
	this->pointLightColorClock += delta * COLOR_CHANGE_STEP;

	newColor.r = (cos(this->pointLightColorClock) + 1) / 2.0f;
	newColor.g = (cos(this->pointLightColorClock / 2) + 1) / 2.0f;
	newColor.b = (cos(this->pointLightColorClock / 3) + 1) / 2.0f;

	this->pointLights.updateColor(0, newColor);


	const float POSITION_CHANGE_STEP = 1.0f;
	this->pointLightPositionClock += delta * POSITION_CHANGE_STEP;

	glm::vec3 newPosition = light->Position;
	newPosition.x = sin(this->pointLightPositionClock) * 3;
	newPosition.z = cos(this->pointLightPositionClock) * 3;
	this->pointLights.updatePosition(0, newPosition);

	Scene::render(time, delta);
}

TestScene::~TestScene() {
	for(auto e : this->entities) {
		delete e;
	}
}