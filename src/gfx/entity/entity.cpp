#include <remus/gfx/entity/entity.h>

namespace remus {
	namespace gfx {
		namespace entity {

			Entity::Entity(models::Model* model, shaders::ShaderProgram* shader, std::unordered_map<std::string, texture::Material*> materials) {
				this->model = model;
				this->shader = shader;
				this->materials = materials;
				this->newInstance();
			}

			Entity::Entity(models::Model* model, shaders::ShaderProgram* shader, std::vector<texture::Material*> materials, std::vector<std::string> names) {
				if(materials.size() != names.size()) {
					throw std::logic_error("List of texture sets provided to entity with unequal number of names.");
				}
				
				this->model = model;
				this->shader = shader;
				for(auto i = 0; i < materials.size(); i++) {
					this->addMaterial(names[i], materials[i]);
				}
				this->newInstance();
			}

			models::ModelMatrix* Entity::newInstance() noexcept {
				models::ModelMatrix m;
				this->modelMatrices.push_back(m);
				this->updateSSBO = true;
				return &this->modelMatrices[this->modelMatrices.size() - 1];
			}

			size_t Entity::removeInstance(size_t instance) {
				this->modelMatrices.erase(this->modelMatrices.begin() + instance);
				this->updateSSBO = true;
				return this->modelMatrices.size();
			}

			void Entity::updateInstance(size_t instance) {
				if(this->updateSSBO)
					return; // No need to update if the memory will be reallocated on next bind

				this->instanceSSBO.bind();

				// Model matrix (16 elements of 4 bytes each)
				this->instanceSSBO.updateBufferData((void*)glm::value_ptr(this->modelMatrices[instance].get()), 16*4, 32*4 * instance);

				// Normal matrix (16 elements of 4 bytes each)
				this->instanceSSBO.updateBufferData((void*)glm::value_ptr(this->modelMatrices[instance].getNormalMatrix()), 16*4, 16*4 + 32*4 * instance);

				this->instanceSSBO.unbind();
			}

			void Entity::bindInstanceData(GLint binding) {
				this->instanceSSBO.bind();
				if(this->updateSSBO) {
					// Reallocate empty memory for model matrices
					this->instanceSSBO.addBufferDataDynamic(nullptr, this->modelMatrices.size() * 2 * 16 * 4);
					this->updateSSBO = false;

					// Update each instance
					for(auto i = 0; i < this->modelMatrices.size(); i++) {
						this->updateInstance(i);
					}
				}

				this->instanceSSBO.bindBufferBase(binding);
			}

			void Entity::unbindInstanceData() {
				this->instanceSSBO.unbind();
			}

			void Entity::addMaterial(std::string meshName, texture::Material* material) {
				if(this->materials.count(meshName) != 0) {
					logger::logWarning("Duplicate texture set added to entity with name \"" + meshName + "\"");
				}

				this->materials[meshName] = material;
			}
			
			void Entity::applyUniforms() noexcept {
				for(std::pair<std::string, bool> e : this->shaderUniformBool) this->shader->setUniform(e.first, e.second);
				for(std::pair<std::string, GLint> e : this->shaderUniformInt) this->shader->setUniform(e.first, e.second);
				for(std::pair<std::string, GLfloat> e : this->shaderUniformFloat) this->shader->setUniform(e.first, e.second);
				for(std::pair<std::string, glm::vec3> e : this->shaderUniformVec3) this->shader->setUniform(e.first, e.second);
				for(std::pair<std::string, glm::vec4> e : this->shaderUniformVec4) this->shader->setUniform(e.first, e.second);
				for(std::pair<std::string, glm::mat4> e : this->shaderUniformMat4) this->shader->setUniform(e.first, e.second);
			}

			// std::vector<RayCastIntersection> Entity::raycast(GLfloat x, GLfloat y, view::Camera* camera) {
			// 	std::vector<RayCastIntersection> intersections;

			// 	if(!this->getModel()->hasOBB()) {
			// 		logger::logWarning("Ray cast attempted at entity with no-OBB.");
			// 		return intersections;
			// 	}

			// 	glm::mat4 vp;
			// 	if(camera != nullptr) {
			// 		vp = camera->getProjection() * camera->getViewMatrix() * this->modelMatrix.get();
			// 	} else {
			// 		vp = this->modelMatrix.get(); 
			// 	}

			// 	auto inverseVP = glm::inverse(vp);

			// 	glm::vec4 screenPosStart = glm::vec4(x, y, -1.0, 1.0);
			// 	glm::vec4 screenPosEnd = glm::vec4(x, y, 0.0, 1.0);

			// 	glm::vec4 rayWorldStart = inverseVP * screenPosStart; 
			// 	rayWorldStart /= rayWorldStart.w;

			// 	glm::vec4 rayWorldEnd = inverseVP * screenPosEnd; 
			// 	rayWorldEnd /= rayWorldEnd.w;

			// 	glm::vec3 rayDir(rayWorldEnd - rayWorldStart);

			// 	rayDir = glm::normalize(rayDir);
			// 	glm::vec3 rayOrigin = glm::vec3(rayWorldStart);

			// 	for(auto &it : this->model->getMeshes()) {
			// 		auto min = it.second->getOBB()->min;
			// 		auto max = it.second->getOBB()->max;

			// 		float tmin = (min.x - rayOrigin.x) / rayDir.x; 
			// 		float tmax = (max.x - rayOrigin.x) / rayDir.x; 
				
			// 		if (tmin > tmax) {
			// 			auto temp = tmin;
			// 			tmin = tmax;
			// 			tmax = temp;
			// 		}
				
			// 		float tymin = (min.y - rayOrigin.y) / rayDir.y; 
			// 		float tymax = (max.y - rayOrigin.y) / rayDir.y; 
				
			// 		if (tymin > tymax) {
			// 			auto temp = tymin;
			// 			tymin = tymax;
			// 			tymax = temp; 
			// 		}
				
			// 		if ((tmin > tymax) || (tymin > tmax)) 
			// 			continue;
				
			// 		if (tymin > tmin) 
			// 			tmin = tymin; 
				
			// 		if (tymax < tmax) 
			// 			tmax = tymax; 
				
			// 		float tzmin = (min.z - rayOrigin.z) / rayDir.z; 
			// 		float tzmax = (max.z - rayOrigin.z) / rayDir.z; 
				
			// 		if (tzmin > tzmax) {
			// 			auto temp = tzmin;
			// 			tzmin = tzmax;
			// 			tzmax = temp; 
			// 		} 
				
			// 		if ((tmin > tzmax) || (tzmin > tmax)) 
			// 			continue;
				
			// 		if (tzmin > tmin) 
			// 			tmin = tzmin; 
				
			// 		if (tzmax < tmax) 
			// 			tmax = tzmax; 
				
			// 		auto intersection = RayCastIntersection{
			// 			name: it.first,
			// 			mesh: it.second,
			// 			distance: tmin
			// 		};

			// 		intersections.push_back(intersection);
			// 	}

			// 	return intersections;
			// }

			Entity::~Entity() {
				
			}

		}
	}
}