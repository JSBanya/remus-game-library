#include <remus/engine/scene/scene.h>

namespace remus {
	namespace engine {
		namespace scene {
			Scene::Scene(std::string name, gfx::view::Camera* c, Context* context) {
				this->name = name;
				this->activeCamera = c;
				this->context = context;
				logger::logNotice("Created new scene with name \"" + name + "\".");
			}

			void Scene::tick(GLint num) {
				
			}

			void Scene::render(GLfloat time, GLfloat delta) {
				
			}

			void Scene::draw() {
				for(auto &e : this->entities) {
					if(e->numInstances() == 0)
						continue;
					
					auto shader = e->getShader();

					shader->bind();

					// Bind entity instances
					e->bindInstanceData(0);

					// Bind camera uniforms
					shader->setUniform("viewMatrix", this->getCamera()->getViewMatrix());
					shader->setUniform("projectionMatrix", this->getCamera()->getProjection());
					shader->setUniform("cameraPosition", this->getCamera()->getPos());

					// Apply entity uniforms
					e->applyUniforms();

					// Apply lights
					shader->setUniform("ambient", this->ambient);
					this->pointLights.bind(1);
					this->directionaLights.bind(2);
					this->spotLights.bind(3);

					// Draw model mesh-by-mesh
					auto model = e->getModel();
					auto materials = e->getMaterials();
					for(auto &mesh : model->getMeshes()) {
						auto meshName = mesh.first;
						auto meshObj = mesh.second;

						bool hasMaterial = (materials.count(meshName) != 0);
						if(hasMaterial) {
							materials[meshName]->bind(shader);
						}
						
						meshObj->drawTrianglesInstanced(e->numInstances());

						if(hasMaterial) {
							materials[meshName]->unbind();
						}
					}

					shader->unbind();
				}
			}

			void Scene::addEntity(gfx::entity::Entity* e) noexcept {
				this->entities.push_back(e);
			}

			std::vector<gfx::entity::Entity*> Scene::getEntities() noexcept {
				return this->entities;
			}

		}
	}
}