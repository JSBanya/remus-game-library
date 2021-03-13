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

			struct DirectionalLight {
				glm::vec3 Direction;
				glm::vec3 Color;
			};

			class DirectionalLights {
			public:
				DirectionalLights();

				// Point Lights
				size_t add(DirectionalLight light) noexcept;
				size_t add(glm::vec3 direction, glm::vec3 color) noexcept;
				DirectionalLight* get(size_t index);

				void forceUpdate(size_t index);
				void updateDirection(size_t index, glm::vec3 direction);
				void updateColor(size_t index, glm::vec3 color);

				void bind(GLint binding);
				void unbind();

				~DirectionalLights();
			protected:
				std::vector<DirectionalLight> lights;
				buffers::SSBO ssbo;
				bool updateSSBO = true;
			
			protected:
				// PointLight size/padding constants
				const size_t SIZE = 32;
				const size_t DIRECTION_OFFSET = 0;
				const size_t DIRECTION_SIZE = 16;
				const size_t COLOR_OFFSET = 16;
				const size_t COLOR_SIZE = 16;

			};

		}
	}
}