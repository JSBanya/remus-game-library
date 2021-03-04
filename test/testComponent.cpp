#include "testComponent.h"

TestComponent::TestComponent(remus::engine::Context* context) : remus::engine::scene::SceneComponent("Test Component", context) {
	this->cubeEntity = new remus::gfx::entity::Entity(
							context->getModel("cube"), 
							context->getShaderProgram("test_shader"), 
							{context->getTextureSet("cube_textures")}, 
							{"Cube"}
						);
	this->addEntity(this->cubeEntity);
	this->cubeEntity->getModelMatrix().setPos(5.0f, 0.0f, 0.0f);
}

void TestComponent::tick(GLint num) {
	this->cubeEntity->getModelMatrix().rotateY(1.0f);
}

TestComponent::~TestComponent() {
	delete this->cubeEntity;
}