#include <remus/gfx/lighting/directionalLights.h>

namespace remus {
	namespace gfx {
		namespace lighting {

			DirectionalLights::DirectionalLights() {

			}

			size_t DirectionalLights::add(DirectionalLight light) noexcept {
				this->lights.push_back(light);
				this->updateSSBO = true;
				return this->lights.size()-1;
			}

			size_t DirectionalLights::add(glm::vec3 direction, glm::vec3 color) noexcept {
				DirectionalLight light;
				light.Direction = direction;
				light.Color = color;
				return this->add(light);
			}

			DirectionalLight* DirectionalLights::get(size_t index) {
				if(index < 0 || index >= this->lights.size()) {
					throw std::runtime_error("Directional Light " + std::to_string(index) + " does not exist. Number of directional lights: " + std::to_string(this->lights.size()));
				}

				return &(this->lights[index]);
			}

			void DirectionalLights::forceUpdate(size_t index) {
				auto pl = this->get(index);
				this->updateDirection(index, pl->Direction);
				this->updateColor(index, pl->Color);
			}

			void DirectionalLights::updateDirection(size_t index, glm::vec3 direction) {
				auto pl = this->get(index);
				pl->Direction = direction;
				this->ssbo.updateBufferData(glm::value_ptr(pl->Direction), this->DIRECTION_SIZE, this->DIRECTION_OFFSET);
			}

			void DirectionalLights::updateColor(size_t index, glm::vec3 color) {
				auto pl = this->get(index);
				pl->Color = color;
				this->ssbo.updateBufferData(glm::value_ptr(pl->Color), this->COLOR_SIZE, this->COLOR_OFFSET);
			}

			void DirectionalLights::bind(GLint binding) {
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

			void DirectionalLights::unbind() {
				this->ssbo.unbind();
			}

			DirectionalLights::~DirectionalLights() {
				
			}

		}
	}
}