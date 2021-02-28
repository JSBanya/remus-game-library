#pragma once

#include <remus/engine/scene/driver.h>
#include <remus/engine/context.h>
#include <remus/utils/mouse.h>
#include <remus/utils/keyboard.h>
#include <remus/engine/window.h>
#include "testScene.h"

class TestDriver : public remus::engine::scene::Driver {
public:
	TestDriver(remus::engine::Window* window, remus::engine::Context* context);

	void render(GLfloat time, GLfloat delta);

	~TestDriver();

private:
	remus::engine::Window* window;
	remus::utils::Keyboard* keyboard;
};