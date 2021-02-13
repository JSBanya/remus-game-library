#include <remus/engine/scene/scene.h>

namespace remus {
	namespace engine {
		namespace scene {
			Scene::Scene(std::string name) {
				this->name = name;
				logger::logNotice("Created new scene with name \"" + name + "\".");
			}
			
			Scene::Scene(std::string name, gfx::view::Camera* c) : Scene(name) {
				this->camera = c;
			}

			void Scene::tick(GLint num) {
				auto components = this->getComponents();
				for(auto c : components) {
					c->setContext(this->context);
					c->tick(num);
				}
			}

			void Scene::render(GLfloat time, GLfloat delta) {
				auto components = this->getComponents();
				for(auto c : components) {
					c->setContext(this->context);
					c->render(this->camera, time, delta);
				}
			}

			std::vector<SceneComponent*> Scene::getComponents() noexcept {
				return this->components;
			}

		}
	}
}