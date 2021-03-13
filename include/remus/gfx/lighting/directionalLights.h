#pragma once

#include <remus/gfx/lighting/lights.h>

namespace remus {
	namespace gfx {
		namespace lighting {

			struct DirectionalLight {
				glm::vec4 Direction;
				glm::vec4 Color;

				GLint Active;
			};

			class DirectionalLights : public Lights<DirectionalLight> {
			public:
				DirectionalLights() : Lights(48) {}
				size_t newLight(glm::vec4 direction, glm::vec4 color) noexcept;

				void forceUpdate(size_t index);
				void updateDirection(size_t index, glm::vec4 direction);
				void updateColor(size_t index, glm::vec4 color);
				void updateActive(size_t index, bool active);
			
			protected:
				const size_t SIZE = 48;
				const size_t DIRECTION_OFFSET = 0;
				const size_t DIRECTION_SIZE = 16;
				const size_t COLOR_OFFSET = 16;
				const size_t COLOR_SIZE = 16;
				const size_t ACTIVE_OFFSET = 32;
				const size_t ACTIVE_SIZE = 4;

			};

		}
	}
}