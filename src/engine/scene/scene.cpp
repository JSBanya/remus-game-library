#include <remus/engine/scene/scene.h>

namespace remus {
	namespace engine {
		namespace scene {
			Scene::Scene(std::string name, gfx::view::Camera* c, Cache* cache) {
				this->name = name;
				this->activeCamera = c;
				this->cache = cache;
				Logger::logNotice("Created new scene with name \"" + name + "\".");
			}

			void Scene::tick(GLint num) {
				
			}

			void Scene::render(GLfloat time, GLfloat delta) {
				
			}

			void Scene::addEntity(gfx::entity::Entity* e, bool transparency) noexcept {
				if(transparency)
					this->transparentEntities.push_back(e);
				else
					this->opaqueEntities.push_back(e);
			}

		}
	}
}