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
				SceneComponent(std::string name);

				virtual void tick(GLint num);
				virtual void render(gfx::view::Camera* camera, GLfloat time, GLfloat deltax);
				virtual std::vector<gfx::entity::Entity*> getEntities() noexcept;

				inline std::string getName() {
					return this->name;
				}

				inline void setContext(Context* c) noexcept {
					this->context = c;
				}

			protected:
				std::vector<gfx::entity::Entity*> entities;
				std::string name;
				Context* context;
			};

		}
	}
}
