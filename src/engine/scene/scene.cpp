#include <remus/engine/scene/scene.h>

namespace remus {
	namespace engine {
		namespace scene {
			Scene::Scene(std::string name, Context* context) {
				this->name = name;
				this->context = context;
				logger::logNotice("Created new scene with name \"" + name + "\".");
			}
			
			Scene::Scene(std::string name, gfx::view::Camera* c, Context* context) : Scene(name, context) {
				this->activeCamera = c;
			}

			void Scene::tick(GLint num) {
				auto components = this->getComponents();
				for(auto c : components) {
					c->tick(num);
				}
			}

			void Scene::render(GLfloat time, GLfloat delta) {
				auto components = this->getComponents();
				for(auto c : components) {
					c->render(this->activeCamera, time, delta);
				}
			}

			std::vector<SceneComponent*> Scene::getComponents() noexcept {
				return this->components;
			}

		}
	}
}