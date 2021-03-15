#pragma once

#include <remus/engine/scene/driver.h>
#include <remus/engine/cache.h>
#include <remus/utils/mouse.h>
#include <remus/utils/keyboard.h>
#include <remus/engine/window.h>
#include <remus/gfx/view/perspectiveCamera.h>
#include "testScene.h"

class TestDriver : public remus::engine::scene::Driver {
public:
	TestDriver(remus::engine::Window* window, remus::engine::Cache* cache);

	void render(GLfloat time, GLfloat delta);

	~TestDriver();

private:
	remus::engine::Window* window;
	remus::utils::Keyboard* keyboard;
	remus::gfx::view::PerspectiveCamera* camera;
};