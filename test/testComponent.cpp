#include "testComponent.h"

TestComponent::TestComponent(remus::engine::Context* context) : remus::engine::scene::SceneComponent("Test Component", context) {
	this->cubeEntity = new remus::gfx::entity::Entity(context->getModel("cube"), context->getShaderProgram("test_shader"), {}, {});
	this->addEntity(this->cubeEntity);
	this->cubeEntity->getModelMatrix().setPos(0.0f, 0.0f, -5.0f);
}

void TestComponent::tick(GLint num) {
	// this->cubeEntity->getModelMatrix().translate(0.0f, 0.0f, -0.1f);
}

TestComponent::~TestComponent() {
	delete this->cubeEntity;
}