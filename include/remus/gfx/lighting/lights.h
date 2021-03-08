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

			class Lights {
			public:
				Lights();

				size_t addPointLight(PointLight light) noexcept;
				size_t addPointLight(glm::vec3 position, glm::vec3 color, GLfloat attentuationConstant, GLfloat attentuationLinear, GLfloat attentuationQuadratic) noexcept;
				PointLight* getPointLight(size_t index);

				void forceUpdatePointLight(size_t index);
				void updatePointLightPosition(size_t index, glm::vec3 position);
				void updatePointLightColor(size_t index, glm::vec3 color);
				void updatePointLightAttenuationConstant(size_t index, GLfloat attentuationConstant);
				void updatePointLightAttenuationLinear(size_t index, GLfloat attentuationLinear);
				void updatePointLightAttenuationQuadratic(size_t index, GLfloat attentuationQuadratic);

				void bindPointLights();
				void unbindPointLights();

				void bind();
				void unbind();

				~Lights();
			protected:
				std::vector<PointLight> pointLights;
				buffers::SSBO pointLightsSSBO;
				bool pointLightsUpdateSSBO = true;
			
			protected:
				// PointLight size/padding constants
				const size_t POINT_LIGHT_SIZE = 48;
				const size_t POINT_LIGHT_POSITION_OFFSET = 0;
				const size_t POINT_LIGHT_POSITION_SIZE = 16;
				const size_t POINT_LIGHT_COLOR_OFFSET = 16;
				const size_t POINT_LIGHT_COLOR_SIZE = 16;
				const size_t POINT_LIGHT_ATTENUATION_CONSTANT_OFFSET = 32;
				const size_t POINT_LIGHT_ATTENUATION_CONSTANT_SIZE = 4;
				const size_t POINT_LIGHT_ATTENUATION_LINEAR_OFFSET = 36;
				const size_t POINT_LIGHT_ATTENUATION_LINEAR_SIZE = 4;
				const size_t POINT_LIGHT_ATTENUATION_QUADRATIC_OFFSET = 40;
				const size_t POINT_LIGHT_ATTENUATION_QUADRATIC_SIZE = 4;

			};

		}
	}
}