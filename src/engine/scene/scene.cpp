#include <remus/engine/scene/scene.h>

namespace remus {
	namespace engine {
		namespace scene {
			Scene::Scene(std::string name) {
				this->name = name;
				logger::logNotice("Created new scene with name \"" + name + "\".");
			}
			
			Scene::Scene(std::string name, gfx::view::Camera* c) : Scene(name) {
				this->camera = c;
			}

			void Scene::tick(GLint num) {
				auto components = this->getComponents();
				for(auto c : components) {
					c->setContext(this->context);
					c->tick(num);
				}
			}

			void Scene::render(GLfloat time, GLfloat delta) {
				auto projectionMatrix = this->camera->getProjection();
				auto viewMatrix = this->camera->getViewMatrix();

				auto components = this->getComponents();
				for(auto c : components) {
					c->setContext(this->context);
					c->render(time, delta, projectionMatrix, viewMatrix);
				}
			}

			std::vector<SceneComponent*> Scene::getComponents() noexcept {
				return this->components;
			}

			// Sets the scene ray cast at the given screen x/y (normalized)
			GLfloat Scene::rayCastAt(entity::Entity* entity, GLfloat x, GLfloat y) noexcept {
				if(!entity->getModel()->hasOBB()) {
					logger::logWarning("Ray cast attempted at model with no-OBB.");
					return -1;
				}

				auto inverseVP = glm::inverse(this->camera->getProjection() * this->camera->getViewMatrix() * entity->getModel()->getModelMatrix());

				glm::vec4 screenPosStart = glm::vec4(x, y, -1.0, 1.0);
				glm::vec4 screenPosEnd = glm::vec4(x, y, 0.0, 1.0);

				glm::vec4 rayWorldStart = inverseVP * screenPosStart; 
				rayWorldStart /= rayWorldStart.w;

				glm::vec4 rayWorldEnd = inverseVP * screenPosEnd; 
				rayWorldEnd /= rayWorldEnd.w;

				glm::vec3 rayDir(rayWorldEnd - rayWorldStart);

				rayDir = glm::normalize(rayDir);
				glm::vec3 rayOrigin = glm::vec3(rayWorldStart);

				auto min = entity->getModel()->getOBB()->min;
				auto max = entity->getModel()->getOBB()->max;

				float tmin = (min.x - rayOrigin.x) / rayDir.x; 
				float tmax = (max.x - rayOrigin.x) / rayDir.x; 
			
				if (tmin > tmax) {
					auto temp = tmin;
					tmin = tmax;
					tmax = temp;
				}
			
				float tymin = (min.y - rayOrigin.y) / rayDir.y; 
				float tymax = (max.y - rayOrigin.y) / rayDir.y; 
			
				if (tymin > tymax) {
					auto temp = tymin;
					tymin = tymax;
					tymax = temp; 
				}
			
				if ((tmin > tymax) || (tymin > tmax)) 
					return -1; 
			
				if (tymin > tmin) 
					tmin = tymin; 
			
				if (tymax < tmax) 
					tmax = tymax; 
			
				float tzmin = (min.z - rayOrigin.z) / rayDir.z; 
				float tzmax = (max.z - rayOrigin.z) / rayDir.z; 
			
				if (tzmin > tzmax) {
					auto temp = tzmin;
					tzmin = tzmax;
					tzmax = temp; 
				} 
			
				if ((tmin > tzmax) || (tzmin > tmax)) 
					return -1; 
			
				if (tzmin > tmin) 
					tmin = tzmin; 
			
				if (tzmax < tmax) 
					tmax = tzmax; 
			
				return tmin; 
			}

			// Set the scene ray cast to the mouse coordinates
			GLfloat Scene::rayCastAtMouse(entity::Entity* entity) noexcept {
				return this->rayCastAt(entity, utils::Mouse::getX(true), utils::Mouse::getY(true, true));
			}

			// Gets the nearest model that is intersected with the scene ray cast at mouse
			entity::Entity* Scene::getRayCastMouseNearest() noexcept {
				entity::Entity* closestIntersection = nullptr;
				GLfloat closestIntersectionDistance = 1000000.0f;

				auto components = this->getComponents();
				for(auto c : components) {
					auto entities = c->getEntities();
					for(auto e : entities) {
						if(!e->getModel()->hasOBB())
							continue;
						GLfloat intersection = this->rayCastAtMouse(e);
						if(intersection >= 0.0f && intersection < closestIntersectionDistance) {
							closestIntersectionDistance = intersection;
							closestIntersection = e;
						}
					}
				}

				return closestIntersection;
			}

		}
	}
}