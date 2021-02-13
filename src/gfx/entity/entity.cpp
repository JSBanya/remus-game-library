#include <remus/gfx/entity/entity.h>

namespace remus {
	namespace gfx {
		namespace entity {

			Entity::Entity(models::Model* model, shaders::ShaderProgram* shader, std::unordered_map<std::string, texture::TextureSet*> textureSets) {
				this->model = model;
				this->shader = shader;
				this->textureSets = textureSets;
			}

			Entity::Entity(models::Model* model, shaders::ShaderProgram* shader, std::vector<texture::TextureSet*> textureSets, std::vector<std::string> names) {
				if(textureSets.size() != names.size()) {
					throw std::logic_error("List of texture sets provided to entity with unequal number of names.");
				}
				
				this->model = model;
				this->shader = shader;
				for(auto i = 0; i < textureSets.size(); i++) {
					this->addTextureSet(names[i], textureSets[i]);
				}
			}

			void Entity::addTextureSet(std::string meshName, texture::TextureSet* textureSet) {
				if(this->textureSets.count(meshName) != 0) {
					logger::logWarning("Duplicate texture set added to entity with name \"" + meshName + "\"");
				}

				this->textureSets[meshName] = textureSet;
			}

			void Entity::draw(view::Camera* camera) noexcept {
				this->shader->bind();
				this->shader->setUniform("modelMatrix", this->modelMatrix.get());
				if(camera != nullptr) {
					this->shader->setUniform("viewMatrix", camera->getViewMatrix());
					this->shader->setUniform("projectionMatrix", camera->getProjection());
				}

				this->applyUniforms();

				this->model->draw(this->shader, this->textureSets);
				this->shader->unbind();
			}

			void Entity::applyUniforms() noexcept {
				for(std::pair<std::string, bool> e : this->shaderUniformBool) this->shader->setUniform(e.first, e.second);
				for(std::pair<std::string, GLint> e : this->shaderUniformInt) this->shader->setUniform(e.first, e.second);
				for(std::pair<std::string, GLfloat> e : this->shaderUniformFloat) this->shader->setUniform(e.first, e.second);
				for(std::pair<std::string, glm::vec3> e : this->shaderUniformVec3) this->shader->setUniform(e.first, e.second);
				for(std::pair<std::string, glm::vec4> e : this->shaderUniformVec4) this->shader->setUniform(e.first, e.second);
				for(std::pair<std::string, glm::mat4> e : this->shaderUniformMat4) this->shader->setUniform(e.first, e.second);
			}

			std::vector<RayCastIntersection> Entity::raycast(GLfloat x, GLfloat y, view::Camera* camera) {
				std::vector<RayCastIntersection> intersections;

				if(!this->getModel()->hasOBB()) {
					logger::logWarning("Ray cast attempted at entity with no-OBB.");
					return intersections;
				}

				glm::mat4 vp;
				if(camera != nullptr) {
					vp = camera->getProjection() * camera->getViewMatrix() * this->modelMatrix.get();
				} else {
					vp = this->modelMatrix.get(); 
				}

				auto inverseVP = glm::inverse(vp);

				glm::vec4 screenPosStart = glm::vec4(x, y, -1.0, 1.0);
				glm::vec4 screenPosEnd = glm::vec4(x, y, 0.0, 1.0);

				glm::vec4 rayWorldStart = inverseVP * screenPosStart; 
				rayWorldStart /= rayWorldStart.w;

				glm::vec4 rayWorldEnd = inverseVP * screenPosEnd; 
				rayWorldEnd /= rayWorldEnd.w;

				glm::vec3 rayDir(rayWorldEnd - rayWorldStart);

				rayDir = glm::normalize(rayDir);
				glm::vec3 rayOrigin = glm::vec3(rayWorldStart);

				for(auto &it : this->model->getMeshes()) {
					auto min = it.second->getOBB()->min;
					auto max = it.second->getOBB()->max;

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
						continue;
				
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
						continue;
				
					if (tzmin > tmin) 
						tmin = tzmin; 
				
					if (tzmax < tmax) 
						tmax = tzmax; 
				
					auto intersection = RayCastIntersection{
						name: it.first,
						mesh: it.second,
						distance: tmin
					};

					intersections.push_back(intersection);
				}

				return intersections;
			}

			Entity::~Entity() {
				
			}

		}
	}
}