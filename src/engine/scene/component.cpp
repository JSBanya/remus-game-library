#include <remus/engine/scene/component.h>

namespace remus {
	namespace engine {
		namespace scene {

			SceneComponent::SceneComponent(std::string name) {
				this->name = name;
				logger::logNotice("Created new scene component \"" + this->name + "\".");
			}

			void SceneComponent::tick(GLint num) {
				(void) num;
			}

			void SceneComponent::render(GLfloat time, GLfloat delta, glm::mat4 projectionMatrix, glm::mat4 viewMatrix) {
				auto entities = this->getEntities();
				for(auto e : entities) {
					e->setUniform("projectionMatrix", projectionMatrix);
					e->setUniform("viewMatrix", viewMatrix);
					e->setUniform("modelMatrix", e->getModel()->getModelMatrix());
					e->draw();
				}
			}

			std::vector<entity::Entity*> SceneComponent::getEntities() noexcept {
				return this->entities;
			}

		}
	}
}