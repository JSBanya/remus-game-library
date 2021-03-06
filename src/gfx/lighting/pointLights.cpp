#include <remus/gfx/lighting/pointLights.h>

namespace remus {
	namespace gfx {
		namespace lighting {

			size_t PointLights::newLight(glm::vec4 position, glm::vec4 color, GLfloat attentuationConstant, GLfloat attentuationLinear, GLfloat attentuationQuadratic) noexcept {
				PointLight light;
				light.Position = position;
				light.Color = color;
				light.AttenuationConstant = attentuationConstant;
				light.AttenuationLinear = attentuationLinear;
				light.AttenuationQuadratic = attentuationQuadratic;
				light.Active = true;
				return this->add(light);
			}

			void PointLights::forceUpdate(size_t index) {
				auto pl = this->get(index);
				this->updatePosition(index, pl->Position);
				this->updateColor(index, pl->Color);
				this->updateAttenuationConstant(index, pl->AttenuationConstant);
				this->updateAttenuationLinear(index, pl->AttenuationLinear);
				this->updateAttenuationQuadratic(index, pl->AttenuationQuadratic);
				this->updateActive(index, pl->Active);
			}

			void PointLights::updatePosition(size_t index, glm::vec4 position) {
				auto pl = this->get(index);
				pl->Position = position;

				if(this->updateSSBO) 
					return;
				this->ssbo.bind();
				this->ssbo.updateBufferData(glm::value_ptr(pl->Position), this->POSITION_SIZE, this->POSITION_OFFSET + this->SIZE * index);
				this->ssbo.unbind();
			}

			void PointLights::updateColor(size_t index, glm::vec4 color) {
				auto pl = this->get(index);
				pl->Color = color;

				if(this->updateSSBO) 
					return;
				this->ssbo.bind();
				this->ssbo.updateBufferData(glm::value_ptr(pl->Color), this->COLOR_SIZE, this->COLOR_OFFSET + this->SIZE * index);
				this->ssbo.unbind();
			}

			void PointLights::updateAttenuationConstant(size_t index, GLfloat attentuationConstant) {
				auto pl = this->get(index);
				pl->AttenuationConstant = attentuationConstant;

				if(this->updateSSBO) 
					return;
				this->ssbo.bind();
				this->ssbo.updateBufferData(&pl->AttenuationConstant, this->ATTENUATION_CONSTANT_SIZE, this->ATTENUATION_CONSTANT_OFFSET + this->SIZE * index);
				this->ssbo.unbind();
			}

			void PointLights::updateAttenuationLinear(size_t index, GLfloat attentuationLinear) {
				auto pl = this->get(index);
				pl->AttenuationLinear = attentuationLinear;

				if(this->updateSSBO) 
					return;
				this->ssbo.bind();
				this->ssbo.updateBufferData(&pl->AttenuationLinear, this->ATTENUATION_LINEAR_SIZE, this->ATTENUATION_LINEAR_OFFSET + this->SIZE * index);
				this->ssbo.unbind();	
			}

			void PointLights::updateAttenuationQuadratic(size_t index, GLfloat attentuationQuadratic) {
				auto pl = this->get(index);
				pl->AttenuationQuadratic = attentuationQuadratic;

				if(this->updateSSBO) 
					return;
				this->ssbo.bind();
				this->ssbo.updateBufferData(&pl->AttenuationQuadratic, this->ATTENUATION_QUADRATIC_SIZE, this->ATTENUATION_QUADRATIC_OFFSET + this->SIZE * index);	
				this->ssbo.unbind();
			}

			void PointLights::updateActive(size_t index, bool active) {
				auto pl = this->get(index);
				pl->Active = active;

				if(this->updateSSBO) 
					return;
				this->ssbo.bind();
				this->ssbo.updateBufferData(&pl->Active, this->ACTIVE_SIZE, this->ACTIVE_OFFSET + this->SIZE * index);	
				this->ssbo.unbind();
			}

		}
	}
}