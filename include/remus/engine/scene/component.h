#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <remus/logging/logger.h>
#include <remus/gfx/entity/entity.h>
#include <remus/gfx/view/camera.h>
#include <remus/engine/context.h>

namespace remus {
	namespace engine {
		namespace scene {

			/*
			* A scene component is a collection of logically connected models
			*/
			class SceneComponent {
			public:
				SceneComponent(std::string name, Context* context = nullptr);

				virtual void tick(GLint num);
				virtual void render(gfx::view::Camera* camera, GLfloat time, GLfloat deltax);
				virtual std::vector<gfx::entity::Entity*> getEntities() noexcept;

				void addEntity(gfx::entity::Entity* e) noexcept;

				inline std::string getName() {
					return this->name;
				}

			protected:
				std::vector<gfx::entity::Entity*> entities;
				std::string name;
				Context* context;
			};

		}
	}
}
