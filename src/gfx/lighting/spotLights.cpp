#include <remus/gfx/lighting/spotLights.h>

namespace remus {
	namespace gfx {
		namespace lighting {

			size_t SpotLights::newLight(glm::vec4 position, glm::vec4 direction, glm::vec4 color, GLfloat cutoffDeg, GLfloat outerCutoffDeg, GLfloat attentuationConstant, GLfloat attentuationLinear, GLfloat attentuationQuadratic) noexcept {
				SpotLight light;
				light.Position = position;
				light.Direction = direction;
				light.Color = color;
				light.CutoffDegrees = cutoffDeg;
				light.OuterCutoffDegrees = outerCutoffDeg;
				light.AttenuationConstant = attentuationConstant;
				light.AttenuationLinear = attentuationLinear;
				light.AttenuationQuadratic = attentuationQuadratic;
				light.Active = true;
				return this->add(light);
			}

			void SpotLights::forceUpdate(size_t index) {
				auto sl = this->get(index);
				this->updatePosition(index, sl->Position);
				this->updateDirection(index, sl->Direction);
				this->updateColor(index, sl->Color);
				this->updateCutoffDegrees(index, sl->CutoffDegrees);
				this->updateOuterCutoffDegrees(index, sl->OuterCutoffDegrees);
				this->updateAttenuationConstant(index, sl->AttenuationConstant);
				this->updateAttenuationLinear(index, sl->AttenuationLinear);
				this->updateAttenuationQuadratic(index, sl->AttenuationQuadratic);
				this->updateActive(index, sl->Active);
			}

			void SpotLights::updatePosition(size_t index, glm::vec4 position) {
				auto sl = this->get(index);
				sl->Position = position;
				this->ssbo.bind();
				this->ssbo.updateBufferData(glm::value_ptr(sl->Position), this->POSITION_SIZE, this->POSITION_OFFSET + this->SIZE * index);
				this->ssbo.unbind();
			}

			void SpotLights::updateDirection(size_t index, glm::vec4 direction) {
				auto sl = this->get(index);
				sl->Direction = direction;
				this->ssbo.bind();
				this->ssbo.updateBufferData(glm::value_ptr(sl->Direction), this->DIRECTION_SIZE, this->DIRECTION_OFFSET + this->SIZE * index);
				this->ssbo.unbind();
			}

			void SpotLights::updateColor(size_t index, glm::vec4 color) {
				auto sl = this->get(index);
				sl->Color = color;
				this->ssbo.bind();
				this->ssbo.updateBufferData(glm::value_ptr(sl->Color), this->COLOR_SIZE, this->COLOR_OFFSET + this->SIZE * index);
				this->ssbo.unbind();
			}

			void SpotLights::updateCutoffDegrees(size_t index, GLfloat cutoffDegrees) {
				auto sl = this->get(index);
				sl->CutoffDegrees = cutoffDegrees;
				GLfloat convertedCutoff = glm::cos(glm::radians(cutoffDegrees));
				this->ssbo.bind();
				this->ssbo.updateBufferData(&convertedCutoff, this->CUTOFF_SIZE, this->CUTOFF_OFFSET + this->SIZE * index);
				this->ssbo.unbind();
			}

			void SpotLights::updateOuterCutoffDegrees(size_t index, GLfloat outerCutoffDegrees) {
				auto sl = this->get(index);
				sl->OuterCutoffDegrees = outerCutoffDegrees;
				GLfloat convertedCutoff = glm::cos(glm::radians(outerCutoffDegrees));
				this->ssbo.bind();
				this->ssbo.updateBufferData(&convertedCutoff, this->OUTER_CUTOFF_SIZE, this->OUTER_CUTOFF_OFFSET + this->SIZE * index);
				this->ssbo.unbind();
			}

			void SpotLights::updateAttenuationConstant(size_t index, GLfloat attentuationConstant) {
				auto sl = this->get(index);
				sl->AttenuationConstant = attentuationConstant;
				this->ssbo.bind();
				this->ssbo.updateBufferData(&sl->AttenuationConstant, this->ATTENUATION_CONSTANT_SIZE, this->ATTENUATION_CONSTANT_OFFSET + this->SIZE * index);
				this->ssbo.unbind();
			}

			void SpotLights::updateAttenuationLinear(size_t index, GLfloat attentuationLinear) {
				auto sl = this->get(index);
				sl->AttenuationLinear = attentuationLinear;
				this->ssbo.bind();
				this->ssbo.updateBufferData(&sl->AttenuationLinear, this->ATTENUATION_LINEAR_SIZE, this->ATTENUATION_LINEAR_OFFSET + this->SIZE * index);
				this->ssbo.unbind();	
			}

			void SpotLights::updateAttenuationQuadratic(size_t index, GLfloat attentuationQuadratic) {
				auto sl = this->get(index);
				sl->AttenuationQuadratic = attentuationQuadratic;
				this->ssbo.bind();
				this->ssbo.updateBufferData(&sl->AttenuationQuadratic, this->ATTENUATION_QUADRATIC_SIZE, this->ATTENUATION_QUADRATIC_OFFSET + this->SIZE * index);	
				this->ssbo.unbind();
			}

			void SpotLights::updateActive(size_t index, bool active) {
				auto sl = this->get(index);
				sl->Active = active;
				this->ssbo.bind();
				this->ssbo.updateBufferData(&sl->Active, this->ACTIVE_SIZE, this->ACTIVE_OFFSET + this->SIZE * index);	
				this->ssbo.unbind();
			}
		}
	}
}