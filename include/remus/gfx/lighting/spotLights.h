#pragma once

#include <remus/gfx/lighting/lights.h>

namespace remus {
	namespace gfx {
		namespace lighting {

			struct SpotLight {
				glm::vec4 Position;
				glm::vec4 Direction;
				glm::vec4 Color;

				GLfloat CutoffDegrees;
				GLfloat OuterCutoffDegrees;

				GLfloat AttenuationConstant;
				GLfloat AttenuationLinear;
				GLfloat AttenuationQuadratic;

				GLint Active;
			};

			class SpotLights : public Lights<SpotLight> {
			public:
				SpotLights() : Lights(80) {};

				size_t newLight(glm::vec4 position, glm::vec4 direction, glm::vec4 color, GLfloat cutoffDeg, GLfloat outerCutoffDeg, GLfloat attentuationConstant, GLfloat attentuationLinear, GLfloat attentuationQuadratic) noexcept;

				void forceUpdate(size_t index);
				void updatePosition(size_t index, glm::vec4 position);
				void updateDirection(size_t index, glm::vec4 direction);
				void updateColor(size_t index, glm::vec4 color);
				void updateCutoffDegrees(size_t index, GLfloat cutoffDegrees);
				void updateOuterCutoffDegrees(size_t index, GLfloat outerCutoffDegrees);
				void updateAttenuationConstant(size_t index, GLfloat attentuationConstant);
				void updateAttenuationLinear(size_t index, GLfloat attentuationLinear);
				void updateAttenuationQuadratic(size_t index, GLfloat attentuationQuadratic);
				void updateActive(size_t index, bool active);

			protected:
				const size_t SIZE = 80;
				const size_t POSITION_OFFSET = 0;
				const size_t POSITION_SIZE = 16;
				const size_t DIRECTION_OFFSET = 16;
				const size_t DIRECTION_SIZE = 16;
				const size_t COLOR_OFFSET = 32;
				const size_t COLOR_SIZE = 16;
				const size_t CUTOFF_OFFSET = 48;
				const size_t CUTOFF_SIZE = 4;
				const size_t OUTER_CUTOFF_OFFSET = 52;
				const size_t OUTER_CUTOFF_SIZE = 4;
				const size_t ATTENUATION_CONSTANT_OFFSET = 56;
				const size_t ATTENUATION_CONSTANT_SIZE = 4;
				const size_t ATTENUATION_LINEAR_OFFSET = 60;
				const size_t ATTENUATION_LINEAR_SIZE = 4;
				const size_t ATTENUATION_QUADRATIC_OFFSET = 64;
				const size_t ATTENUATION_QUADRATIC_SIZE = 4;
				const size_t ACTIVE_OFFSET = 68;
				const size_t ACTIVE_SIZE = 4;
			};

		}
	}
}