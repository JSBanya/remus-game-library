#pragma once

#include <remus/engine/scene/scene.h>
#include <remus/engine/context.h>
#include <remus/gfx/view/perspectiveCamera.h>
#include "testComponent.h"
#include "settings.h"

class TestScene : public remus::engine::scene::Scene {
public:
	TestScene(remus::engine::Context* context);

	~TestScene();

private:

};