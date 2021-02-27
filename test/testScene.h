#pragma once

#include <remus/engine/scene/scene.h>
#include <remus/engine/context.h>
#include <remus/gfx/view/perspectiveCamera.h>
#include <remus/utils/mouse.h>
#include "testComponent.h"
#include "settings.h"

#include <string>
#include <remus/logging/logger.h>

class TestScene : public remus::engine::scene::Scene {
public:
	TestScene(remus::engine::Context* context, remus::utils::Mouse* mouse);

	void render(GLfloat time, GLfloat delta);

	~TestScene();

private:
	remus::utils::Mouse* mouse;
	float sensitivity = 2.0f;
};