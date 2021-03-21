#pragma once

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdexcept>
#include <string>
#include <remus/gfx/buffers/ssbo.h>

namespace remus {
	namespace gfx {
		namespace lighting {

			template<class T>
			class Lights {
			public:
				Lights(size_t size) {
					this->size = size;
				}

				// Point Lights
				size_t add(T light) noexcept {
					this->lights.push_back(light);
					this->updateSSBO = true;
					return this->lights.size()-1;
				}

				size_t remove(size_t index) noexcept {
					this->lights.erase(this->lights.begin() + index);
					this->updateSSBO = true;
					return this->lights.size();
				}

				T* get(size_t index) {
					if(index < 0 || index >= this->lights.size()) {
						throw std::runtime_error("Light " + std::to_string(index) + " does not exist. Number of lights: " + std::to_string(this->lights.size()));
					}

					return &(this->lights[index]);
				}

				virtual void forceUpdate(size_t index) = 0;

				void bind(GLint binding) {
					this->ssbo.bind();
					if(this->updateSSBO) {
						// Update the contents of the SSBO
						this->updateSSBO = false;
						this->ssbo.addBufferDataDynamic(NULL, this->lights.size() * this->size);
						for(auto i = 0; i < this->lights.size(); i++) {
							// Set the data of each light
							this->forceUpdate(i);
						}
					}

					this->ssbo.bindBufferBase(binding);
				}

				void unbind() {
					this->ssbo.unbind();
				}

				~Lights() {

				}
			protected:
				size_t size = 0;
				std::vector<T> lights;
				buffers::SSBO ssbo;
				bool updateSSBO = true;
			};

		}
	}
}