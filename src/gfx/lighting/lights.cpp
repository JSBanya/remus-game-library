#include <remus/gfx/lighting/lights.h>

namespace remus {
	namespace gfx {
		namespace lighting {
			Lights::Lights() {
				
			}

			size_t Lights::addPointLight(PointLight light) noexcept {
				this->pointLights.push_back(light);
				this->pointLightsUpdateSSBO = true;
				return this->pointLights.size()-1;
			}

			size_t Lights::addPointLight(glm::vec3 position, glm::vec3 color, GLfloat attentuationConstant, GLfloat attentuationLinear, GLfloat attentuationQuadratic) noexcept {
				PointLight light;
				light.Position = position;
				light.Color = color;
				light.AttenuationConstant = attentuationConstant;
				light.AttenuationLinear = attentuationLinear;
				light.AttenuationQuadratic = attentuationQuadratic;
				return this->addPointLight(light);
			}

			PointLight* Lights::getPointLight(size_t index) {
				if(index < 0 || index >= this->pointLights.size()) {
					throw std::runtime_error("Point Light " + std::to_string(index) + " does not exist. Number of point lights: " + std::to_string(this->pointLights.size()));
				}

				return &(this->pointLights[index]);
			}

			void Lights::forceUpdatePointLight(size_t index) {
				auto pl = this->getPointLight(index);
				this->updatePointLightPosition(index, pl->Position);
				this->updatePointLightColor(index, pl->Color);
				this->updatePointLightAttenuationConstant(index, pl->AttenuationConstant);
				this->updatePointLightAttenuationLinear(index, pl->AttenuationLinear);
				this->updatePointLightAttenuationQuadratic(index, pl->AttenuationQuadratic);
			}

			void Lights::updatePointLightPosition(size_t index, glm::vec3 position) {
				auto pl = this->getPointLight(index);
				pl->Position = position;
				this->pointLightsSSBO.updateBufferData(glm::value_ptr(pl->Position), this->POINT_LIGHT_POSITION_SIZE, this->POINT_LIGHT_POSITION_OFFSET);
			}

			void Lights::updatePointLightColor(size_t index, glm::vec3 color) {
				auto pl = this->getPointLight(index);
				pl->Color = color;
				this->pointLightsSSBO.updateBufferData(glm::value_ptr(pl->Color), this->POINT_LIGHT_COLOR_SIZE, this->POINT_LIGHT_COLOR_OFFSET);
			}

			void Lights::updatePointLightAttenuationConstant(size_t index, GLfloat attentuationConstant) {
				auto pl = this->getPointLight(index);
				pl->AttenuationConstant = attentuationConstant;
				this->pointLightsSSBO.updateBufferData(&pl->AttenuationConstant, this->POINT_LIGHT_ATTENUATION_CONSTANT_SIZE, this->POINT_LIGHT_ATTENUATION_CONSTANT_OFFSET);
			}

			void Lights::updatePointLightAttenuationLinear(size_t index, GLfloat attentuationLinear) {
				auto pl = this->getPointLight(index);
				pl->AttenuationLinear = attentuationLinear;
				this->pointLightsSSBO.updateBufferData(&pl->AttenuationLinear, this->POINT_LIGHT_ATTENUATION_LINEAR_SIZE, this->POINT_LIGHT_ATTENUATION_LINEAR_OFFSET);	
			}

			void Lights::updatePointLightAttenuationQuadratic(size_t index, GLfloat attentuationQuadratic) {
				auto pl = this->getPointLight(index);
				pl->AttenuationQuadratic = attentuationQuadratic;
				this->pointLightsSSBO.updateBufferData(&pl->AttenuationQuadratic, this->POINT_LIGHT_ATTENUATION_QUADRATIC_SIZE, this->POINT_LIGHT_ATTENUATION_QUADRATIC_OFFSET);	
			}

			void Lights::bindPointLights() {
				this->pointLightsSSBO.bind();
				if(this->pointLightsUpdateSSBO) {
					// Update the contents of the SSBO
					this->pointLightsSSBO.addBufferDataDynamic(&this->pointLights, this->pointLights.size() * this->POINT_LIGHT_SIZE);
					for(auto i = 0; i < this->pointLights.size(); i++) {
						// Set the data of each light
						this->forceUpdatePointLight(i);
					}
					this->pointLightsUpdateSSBO = false;
				}

				this->pointLightsSSBO.bindBufferBase(0);
			}

			void Lights::unbindPointLights() {
				this->pointLightsSSBO.unbind();
			}

			void Lights::bind() {
				this->bindPointLights();
			}

			void Lights::unbind() {
				this->unbindPointLights();
			}

			Lights::~Lights() {

			}
		}
	}
}