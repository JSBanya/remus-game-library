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
#include <remus/engine/cache.h>
#include <remus/gfx/lighting/pointLights.h>
#include <remus/gfx/lighting/directionalLights.h>
#include <remus/gfx/lighting/spotLights.h>

namespace remus {
	namespace engine {
		namespace scene {

			class Scene {
			public:
				Scene(std::string name, gfx::view::Camera* c, Cache* cache = nullptr);

				virtual void tick(GLint num); // Happens every game tick
				virtual void render(GLfloat time, GLfloat delta); // Happens every frame (depends on fps)

				virtual void addEntity(gfx::entity::Entity* e, bool transparency = false) noexcept;

				virtual std::vector<gfx::entity::Entity*> getOpaqueEntities() noexcept {
					return this->opaqueEntities;
				}

				virtual std::vector<gfx::entity::Entity*> getTransparentEntities() noexcept {
					return this->transparentEntities;
				}

				inline void setCamera(gfx::view::Camera* c) noexcept {
					this->activeCamera = c;
				}

				inline void setCache(Cache* c) noexcept {
					this->cache = c;
				}

				inline gfx::view::Camera* getCamera() noexcept {
					return this->activeCamera;
				}

				inline gfx::lighting::PointLights* getPointLights() {
					return &this->pointLights;
				}

				inline gfx::lighting::DirectionalLights* getDirectionalLights() {
					return &this->directionaLights;
				}

				inline gfx::lighting::SpotLights* getSpotLights() {
					return &this->spotLights;
				}

				inline glm::vec3 getAmbient() {
					return this->ambient;
				}

			protected:
				std::string name;
				gfx::view::Camera* activeCamera;
				Cache* cache;

				gfx::lighting::PointLights pointLights;
				gfx::lighting::DirectionalLights directionaLights;
				gfx::lighting::SpotLights spotLights;
				glm::vec3 ambient = glm::vec3(1.0);

				std::vector<gfx::entity::Entity*> opaqueEntities;
				std::vector<gfx::entity::Entity*> transparentEntities;
			};

		}
	}
}