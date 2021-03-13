#include <remus/gfx/lighting/pointLights.h>

namespace remus {
	namespace gfx {
		namespace lighting {

			PointLights::PointLights() {

			}

			size_t PointLights::add(PointLight light) noexcept {
				this->lights.push_back(light);
				this->updateSSBO = true;
				return this->lights.size()-1;
			}

			size_t PointLights::add(glm::vec3 position, glm::vec3 color, GLfloat attentuationConstant, GLfloat attentuationLinear, GLfloat attentuationQuadratic) noexcept {
				PointLight light;
				light.Position = position;
				light.Color = color;
				light.AttenuationConstant = attentuationConstant;
				light.AttenuationLinear = attentuationLinear;
				light.AttenuationQuadratic = attentuationQuadratic;
				return this->add(light);
			}

			PointLight* PointLights::get(size_t index) {
				if(index < 0 || index >= this->lights.size()) {
					throw std::runtime_error("Point Light " + std::to_string(index) + " does not exist. Number of point lights: " + std::to_string(this->lights.size()));
				}

				return &(this->lights[index]);
			}

			void PointLights::forceUpdate(size_t index) {
				auto pl = this->get(index);
				this->updatePosition(index, pl->Position);
				this->updateColor(index, pl->Color);
				this->updateAttenuationConstant(index, pl->AttenuationConstant);
				this->updateAttenuationLinear(index, pl->AttenuationLinear);
				this->updateAttenuationQuadratic(index, pl->AttenuationQuadratic);
			}

			void PointLights::updatePosition(size_t index, glm::vec3 position) {
				auto pl = this->get(index);
				pl->Position = position;
				this->ssbo.bind();
				this->ssbo.updateBufferData(glm::value_ptr(pl->Position), this->POSITION_SIZE, this->POSITION_OFFSET * (index+1));
				this->ssbo.unbind();
			}

			void PointLights::updateColor(size_t index, glm::vec3 color) {
				auto pl = this->get(index);
				pl->Color = color;
				this->ssbo.bind();
				this->ssbo.updateBufferData(glm::value_ptr(pl->Color), this->COLOR_SIZE, this->COLOR_OFFSET * (index+1));
				this->ssbo.unbind();
			}

			void PointLights::updateAttenuationConstant(size_t index, GLfloat attentuationConstant) {
				auto pl = this->get(index);
				pl->AttenuationConstant = attentuationConstant;
				this->ssbo.bind();
				this->ssbo.updateBufferData(&pl->AttenuationConstant, this->ATTENUATION_CONSTANT_SIZE, this->ATTENUATION_CONSTANT_OFFSET * (index+1));
				this->ssbo.unbind();
			}

			void PointLights::updateAttenuationLinear(size_t index, GLfloat attentuationLinear) {
				auto pl = this->get(index);
				pl->AttenuationLinear = attentuationLinear;
				this->ssbo.bind();
				this->ssbo.updateBufferData(&pl->AttenuationLinear, this->ATTENUATION_LINEAR_SIZE, this->ATTENUATION_LINEAR_OFFSET * (index+1));
				this->ssbo.unbind();	
			}

			void PointLights::updateAttenuationQuadratic(size_t index, GLfloat attentuationQuadratic) {
				auto pl = this->get(index);
				pl->AttenuationQuadratic = attentuationQuadratic;
				this->ssbo.bind();
				this->ssbo.updateBufferData(&pl->AttenuationQuadratic, this->ATTENUATION_QUADRATIC_SIZE, this->ATTENUATION_QUADRATIC_OFFSET * (index+1));	
				this->ssbo.unbind();
			}

			void PointLights::bind(GLint binding) {
				this->ssbo.bind();
				if(this->updateSSBO) {
					// Update the contents of the SSBO
					this->ssbo.addBufferDataDynamic(&this->lights, this->lights.size() * this->SIZE);
					for(auto i = 0; i < this->lights.size(); i++) {
						// Set the data of each light
						this->forceUpdate(i);
					}
					this->updateSSBO = false;
				}

				this->ssbo.bindBufferBase(binding);
			}

			void PointLights::unbind() {
				this->ssbo.unbind();
			}

			PointLights::~PointLights() {

			}

		}
	}
}