#include <remus/engine/scene/driver.h>

namespace remus {
	namespace engine {
		namespace scene {

			Driver::Driver(Context* context) {
				this->context = context;
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
					s->setContext(this->context);
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

			Driver::~Driver() {

			}

		}
	}
}