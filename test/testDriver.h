#pragma once

#include <remus/engine/scene/driver.h>
#include <remus/engine/context.h>
#include <remus/utils/mouse.h>
#include "testScene.h"

class TestDriver : public remus::engine::scene::Driver {
public:
	TestDriver(remus::engine::Context* context, remus::utils::Mouse* mouse);

	~TestDriver();
};