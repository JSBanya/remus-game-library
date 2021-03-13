#include <remus/gfx/lighting/directionalLights.h>

namespace remus {
	namespace gfx {
		namespace lighting {

			size_t DirectionalLights::newLight(glm::vec4 direction, glm::vec4 color) noexcept {
				DirectionalLight light;
				light.Direction = direction;
				light.Color = color;
				return this->add(light);
			}

			void DirectionalLights::forceUpdate(size_t index) {
				auto pl = this->get(index);
				this->updateDirection(index, pl->Direction);
				this->updateColor(index, pl->Color);
			}

			void DirectionalLights::updateDirection(size_t index, glm::vec4 direction) {
				auto pl = this->get(index);
				pl->Direction = direction;
				this->ssbo.bind();
				this->ssbo.updateBufferData(glm::value_ptr(pl->Direction), this->DIRECTION_SIZE, this->DIRECTION_OFFSET + this->SIZE * index);
				this->ssbo.unbind();
			}

			void DirectionalLights::updateColor(size_t index, glm::vec4 color) {
				auto pl = this->get(index);
				pl->Color = color;
				this->ssbo.bind();
				this->ssbo.updateBufferData(glm::value_ptr(pl->Color), this->COLOR_SIZE, this->COLOR_OFFSET + this->SIZE * index);
				this->ssbo.unbind();
			}

		}
	}
}