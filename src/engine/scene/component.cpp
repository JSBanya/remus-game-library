#include <remus/engine/scene/component.h>

namespace remus {
	namespace engine {
		namespace scene {

			SceneComponent::SceneComponent(std::string name, Context* c) {
				this->name = name;
				this->context = context;
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

			void SceneComponent::addEntity(gfx::entity::Entity* e) noexcept {
				this->entities.push_back(e);
			}

			std::vector<gfx::entity::Entity*> SceneComponent::getEntities() noexcept {
				return this->entities;
			}

		}
	}
}