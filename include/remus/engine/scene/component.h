#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <remus/logging/logger.h>
#include <remus/engine/entity/entity.h>
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
				virtual void render(GLfloat time, GLfloat delta, glm::mat4 projectionMatrix, glm::mat4 viewMatrix);
				virtual std::vector<entity::Entity*> getEntities() noexcept;

				inline std::string getName() {
					return this->name;
				}

				inline void setContext(Context* c) noexcept {
					this->context = c;
				}

			protected:
				std::vector<entity::Entity*> entities;
				std::string name;
				Context* context;
			};

		}
	}
}
