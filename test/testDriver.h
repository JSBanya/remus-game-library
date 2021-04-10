#pragma once

#include <remus/engine/scene/driver.h>
#include <remus/engine/cache.h>
#include <remus/utils/mouse.h>
#include <remus/utils/keyboard.h>
#include <remus/engine/window.h>
#include <remus/gfx/view/perspectiveCamera.h>
#include "testScene.h"

using namespace remus;

class TestDriver : public engine::scene::Driver {
public:
	TestDriver(engine::Window* window, engine::Cache* cache);

	void render(GLfloat time, GLfloat delta);

	gfx::shaders::ShaderProgram* getPostProcessor() noexcept;
	gfx::shaders::ShaderProgram* getPostProcessorMS() noexcept;

	~TestDriver();

private:
	engine::Window* window;
	utils::Keyboard* keyboard;
	gfx::view::PerspectiveCamera* camera;
};