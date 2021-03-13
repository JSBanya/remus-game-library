#pragma once

#include <remus/gfx/lighting/lights.h>

namespace remus {
	namespace gfx {
		namespace lighting {

			struct PointLight {
				glm::vec4 Position;
				glm::vec4 Color;

				GLfloat AttenuationConstant;
				GLfloat AttenuationLinear;
				GLfloat AttenuationQuadratic;
			};

			class PointLights : public Lights<PointLight> {
			public:
				PointLights() : Lights(48) {}
				size_t newLight(glm::vec4 position, glm::vec4 color, GLfloat attentuationConstant, GLfloat attentuationLinear, GLfloat attentuationQuadratic) noexcept;

				void forceUpdate(size_t index);
				void updatePosition(size_t index, glm::vec4 position);
				void updateColor(size_t index, glm::vec4 color);
				void updateAttenuationConstant(size_t index, GLfloat attentuationConstant);
				void updateAttenuationLinear(size_t index, GLfloat attentuationLinear);
				void updateAttenuationQuadratic(size_t index, GLfloat attentuationQuadratic);

			private:
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