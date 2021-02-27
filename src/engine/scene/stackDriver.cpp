#include <remus/engine/driver/stackDriver.h>

namespace remus {
	namespace engine {
		namespace driver {

			void StackDriver::newState() noexcept {
				this->states.push(this->activeScenes);
				this->clearScenes();
			}

			void StackDriver::popState() noexcept {
				this->activeScenes = this->states.top();
				this->states.pop();
			}

			StackDriver::~StackDriver() {

			}

		}
	}
}