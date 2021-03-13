#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <vector>
#include <string>
#include <remus/gfx/view/camera.h>
#include <remus/engine/scene/component.h>
#include <remus/logging/logger.h>
#include <remus/engine/entity/entity.h>
#include <remus/utils/mouse.h>
#include <remus/engine/context.h>
#include <remus/gfx/lighting/pointLights.h>
#include <remus/gfx/lighting/directionalLights.h>
#include <remus/gfx/lighting/spotLights.h>

namespace remus {
	namespace engine {
		namespace scene {

			class Scene {
			public:
				Scene(std::string name, gfx::view::Camera* c, Context* context = nullptr);

				virtual void tick(GLint num); // Happens every game tick
				virtual void render(GLfloat time, GLfloat delta); // Happens every frame (depends on fps)
				virtual void draw();

				virtual void addEntity(gfx::entity::Entity* e) noexcept;
				virtual std::vector<gfx::entity::Entity*> getEntities() noexcept;

				inline void setCamera(gfx::view::Camera* c) noexcept {
					this->activeCamera = c;
				}

				inline void setContext(Context* c) noexcept {
					this->context = c;
				}

				inline gfx::view::Camera* getCamera() noexcept {
					return this->activeCamera;
				}

			protected:
				std::string name;
				gfx::view::Camera* activeCamera;
				Context* context;

				gfx::lighting::PointLights pointLights;
				gfx::lighting::DirectionalLights directionaLights;
				gfx::lighting::SpotLights spotLights;
				glm::vec3 ambient = glm::vec3(1.0);

				std::vector<gfx::entity::Entity*> entities;
			};

		}
	}
}