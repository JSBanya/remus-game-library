#pragma once

#include <remus/engine/scene/component.h>
#include <remus/engine/context.h>
#include <remus/gfx/entity/entity.h>
#include <remus/logging/logger.h>

class TestComponent : public remus::engine::scene::SceneComponent {
public:
	TestComponent(remus::engine::Context* context);

	void tick(GLint num);

	~TestComponent();

private:
	remus::gfx::entity::Entity* cubeEntity;
};