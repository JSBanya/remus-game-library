#pragma once

#include <cstdlib>
#include <math.h>
#include <string>
#include <remus/engine/scene/scene.h>
#include <remus/engine/context.h>
#include <remus/gfx/view/camera.h>
#include <remus/utils/mouse.h>
#include <remus/utils/keyboard.h>
#include "settings.h"

class TestScene : public remus::engine::scene::Scene {
public:
	TestScene(remus::engine::Context* context, remus::gfx::view::Camera* camera, remus::utils::Mouse* mouse, remus::utils::Keyboard* keyboard);

	void setup();

	void tick(GLint num);
	void render(GLfloat time, GLfloat delta);

	~TestScene();

private:
	remus::utils::Mouse* mouse;
	remus::utils::Keyboard* keyboard;

	bool mouseCoordsInitialized = false;
	float lastX = 0.0f;
	float lastY = 0.0f;

	float sensitivity = 90.0f;
	float movementSpeed = 3.0f;

	float lastSpotlightToggle = 0;

	float pointLightColorClock = 0.0f;
	float pointLightPositionClock = 0.0f;

	remus::gfx::entity::Entity* cubeEntity;
};