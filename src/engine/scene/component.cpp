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

			void SceneComponent::render(gfx::view::Camera* camera, GLfloat time, GLfloat delta) {
				auto entities = this->getEntities();
				for(auto e : entities) {
					e->draw(camera);
				}
			}

			std::vector<gfx::entity::Entity*> SceneComponent::getEntities() noexcept {
				return this->entities;
			}

		}
	}
}