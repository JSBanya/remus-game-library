#include <remus/engine/driver/driver.h>

namespace remus {
	namespace engine {
		namespace driver {

			Driver::Driver() {

			}

			Driver::Driver(Context* c) {
				this->setContext(c);
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
				for(auto s : this->activeScenes) {
					s->setContext(this->context);
					s->tick(num);
				}
			}

			void Driver::render(GLfloat time, GLfloat delta) {
				for(auto s : this->activeScenes) {
					s->setContext(this->context);
					s->render(time, delta);
				}
			}

			void Driver::setContext(Context* c) {
				this->context = c;
			}

			Driver::~Driver() {

			}

		}
	}
}