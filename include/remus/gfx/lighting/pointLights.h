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

			struct PointLight {
				glm::vec3 Position;
				glm::vec3 Color;

				GLfloat AttenuationConstant;
				GLfloat AttenuationLinear;
				GLfloat AttenuationQuadratic;
			};

			class PointLights {
			public:
				PointLights();

				// Point Lights
				size_t add(PointLight light) noexcept;
				size_t add(glm::vec3 position, glm::vec3 color, GLfloat attentuationConstant, GLfloat attentuationLinear, GLfloat attentuationQuadratic) noexcept;
				PointLight* get(size_t index);

				void forceUpdate(size_t index);
				void updatePosition(size_t index, glm::vec3 position);
				void updateColor(size_t index, glm::vec3 color);
				void updateAttenuationConstant(size_t index, GLfloat attentuationConstant);
				void updateAttenuationLinear(size_t index, GLfloat attentuationLinear);
				void updateAttenuationQuadratic(size_t index, GLfloat attentuationQuadratic);

				void bind(GLint binding);
				void unbind();

				~PointLights();
			protected:
				std::vector<PointLight> lights;
				buffers::SSBO ssbo;
				bool updateSSBO = true;
			
			protected:
				// PointLight size/padding constants
				const size_t SIZE = 48;
				const size_t POSITION_OFFSET = 0;
				const size_t POSITION_SIZE = 16;
				const size_t COLOR_OFFSET = 16;
				const size_t COLOR_SIZE = 16;
				const size_t ATTENUATION_CONSTANT_OFFSET = 32;
				const size_t ATTENUATION_CONSTANT_SIZE = 4;
				const size_t ATTENUATION_LINEAR_OFFSET = 36;
				const size_t ATTENUATION_LINEAR_SIZE = 4;
				const size_t ATTENUATION_QUADRATIC_OFFSET = 40;
				const size_t ATTENUATION_QUADRATIC_SIZE = 4;

			};

		}
	}
}