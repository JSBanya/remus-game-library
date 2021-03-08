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
					auto shader = e->getShader();
					auto modelMatrix = e->getModelMatrix();

					shader->bind();

					shader->setUniform("modelMatrix", modelMatrix.get());
					shader->setUniform("viewMatrix", this->getCamera()->getViewMatrix());
					shader->setUniform("projectionMatrix", this->getCamera()->getProjection());
					shader->setUniform("normalMatrix", modelMatrix.getNormalMatrix());

					// Apply entity uniforms
					e->applyUniforms();

					// Apply lights
					shader->setUniform("ambient", this->ambient);
					this->lights.bind();

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
						
						meshObj->drawTriangles();

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