#pragma once

#include <cstdlib>
#include <math.h>
#include <string>
#include <remus/engine/scene/scene.h>
#include <remus/engine/cache.h>
#include <remus/gfx/view/camera.h>
#include <remus/utils/mouse.h>
#include <remus/utils/keyboard.h>
#include "settings.h"

using namespace remus;

class TestScene : public engine::scene::Scene {
public:
	TestScene(engine::Cache* cache, gfx::view::Camera* camera, utils::Mouse* mouse, utils::Keyboard* keyboard);

	void setup();

	void tick(GLint num);
	void render(GLfloat time, GLfloat delta);

	~TestScene();

private:
	utils::Mouse* mouse;
	utils::Keyboard* keyboard;

	bool mouseCoordsInitialized = false;
	float lastX = 0.0f;
	float lastY = 0.0f;

	float sensitivity = 90.0f;
	float movementSpeed = 3.0f;

	float lastSpotlightToggle = 0;

	float pointLightColorClock = 0.0f;
	float pointLightPositionClock = 0.0f;

	gfx::entity::Entity* cubeEntity;
};