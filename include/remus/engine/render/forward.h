#pragma once

#include <glad/glad.h>
#include <vector>
#include <remus/engine/render/pipeline.h>
#include <remus/engine/scene/driver.h>
#include <remus/gfx/entity/entity.h>
#include <remus/logging/logger.h>

namespace remus {
	namespace engine {
		namespace render {

			class Forward : public Pipeline {
			public:
				Forward(GLint width, GLint height, GLint multisample = 0);
				
				void draw(scene::Driver* driver);
				
			private:
				void renderEntity(
					gfx::entity::Entity* e, 
					gfx::view::Camera* camera,
					glm::vec3 ambient,
					gfx::lighting::PointLights* pointLights, 
					gfx::lighting::DirectionalLights* directionalLights,
					gfx::lighting::SpotLights* spotLights
				);
			};

		}
	}
}