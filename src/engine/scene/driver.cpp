#include <remus/engine/scene/driver.h>

namespace remus {
	namespace engine {
		namespace scene {

			Driver::Driver(Cache* cache) {
				this->cache = cache;
			}

			void Driver::addScene(scene::Scene* s) noexcept {
				this->activeScenes.push_back(s);
			}

			void Driver::removeScene(scene::Scene* s) noexcept {
				this->activeScenes.erase(std::remove(this->activeScenes.begin(), this->activeScenes.end(), s), this->activeScenes.end());
			}

			void Driver::clearScenes() noexcept {
				this->activeScenes.clear();
			}

			void Driver::tick(GLint num) {
				for(auto &s : this->activeScenes) {
					s->setCache(this->cache);
					s->tick(num);
				}
			}

			void Driver::render(GLfloat time, GLfloat delta) {
				for(auto &s : this->activeScenes) {
					s->render(time, delta);
				}
			}

			void Driver::draw() {
				for(auto &s : this->activeScenes) {
					s->draw();
				}
			}

			gfx::shaders::ShaderProgram* Driver::getPostProcessor() noexcept {
				return nullptr;
			}

			gfx::shaders::ShaderProgram* Driver::getPostProcessorMS() noexcept {
				return nullptr;
			}

			Driver::~Driver() {

			}

		}
	}
}