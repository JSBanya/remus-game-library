#include <remus/gfx/lighting/directionalLights.h>

namespace remus {
	namespace gfx {
		namespace lighting {

			size_t DirectionalLights::newLight(glm::vec4 direction, glm::vec4 color) noexcept {
				DirectionalLight light;
				light.Direction = direction;
				light.Color = color;
				light.Active = true;
				return this->add(light);
			}

			void DirectionalLights::forceUpdate(size_t index) {
				auto dl = this->get(index);
				this->updateDirection(index, dl->Direction);
				this->updateColor(index, dl->Color);
				this->updateActive(index, dl->Active);
			}

			void DirectionalLights::updateDirection(size_t index, glm::vec4 direction) {
				auto dl = this->get(index);
				dl->Direction = direction;

				if(this->updateSSBO) 
					return;
				this->ssbo.bind();
				this->ssbo.updateBufferData(glm::value_ptr(dl->Direction), this->DIRECTION_SIZE, this->DIRECTION_OFFSET + this->SIZE * index);
				this->ssbo.unbind();
			}

			void DirectionalLights::updateColor(size_t index, glm::vec4 color) {
				auto dl = this->get(index);
				dl->Color = color;

				if(this->updateSSBO) 
					return;
				this->ssbo.bind();
				this->ssbo.updateBufferData(glm::value_ptr(dl->Color), this->COLOR_SIZE, this->COLOR_OFFSET + this->SIZE * index);
				this->ssbo.unbind();
			}

			void DirectionalLights::updateActive(size_t index, bool active) {
				auto dl = this->get(index);
				dl->Active = active;

				if(this->updateSSBO) 
					return;
				this->ssbo.bind();
				this->ssbo.updateBufferData(&dl->Active, this->ACTIVE_SIZE, this->ACTIVE_OFFSET + this->SIZE * index);	
				this->ssbo.unbind();
			}

		}
	}
}