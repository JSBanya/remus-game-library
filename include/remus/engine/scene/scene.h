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

namespace remus {
	namespace engine {
		namespace scene {


			/*
			* A scene is a collection of related components under a single projection and view matrix (i.e. camera)
			*/
			class Scene {
			public:
				Scene(std::string name);
				Scene(std::string name, gfx::view::Camera* c);

				// Operations
				virtual void tick(GLint num); // Happens every game tick
				virtual void render(GLfloat time, GLfloat delta); // Happens every frame (depends on fps)

				inline void addComponent(SceneComponent* c) noexcept {
					this->components.push_back(c);
				}

				// Setters
				inline void setCamera(gfx::view::Camera* c) noexcept {
					this->camera = c;
				}

				inline void setContext(Context* c) noexcept {
					this->context = c;
				}

				// Getters
				inline gfx::view::Camera* getCamera() noexcept {
					return this->camera;
				}

				virtual std::vector<SceneComponent*> getComponents() noexcept;

			protected:
				std::string name;
				gfx::view::Camera* camera;
				std::vector<SceneComponent*> components;
				Context* context;
			};

		}
	}
}