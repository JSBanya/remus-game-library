#include <remus/gfx/models/model.h>

namespace remus {
	namespace gfx {
		namespace models {
			Model::Model(std::unordered_map<std::string, Mesh*> meshes) {
				this->meshes = meshes;
			}

			Model::Model(std::vector<Mesh*> meshes, std::vector<std::string> names) {
				if(meshes.size() != names.size()) {
					throw std::logic_error("Meshes provided to model with unequal number of names.");
				}

				for(auto i = 0; i < meshes.size(); i++) {
					this->addMesh(meshes[i], names[i]);
				}
			}

			void Model::addMesh(Mesh* m, std::string name) {
				if(this->meshes.count(name) != 0) {
					logging::Logger::logWarning("Duplicate mesh added to model.");
				}

				this->meshes[name] = m;
			}

			Mesh* Model::getMesh(std::string name) {
				if(this->meshes.count(name) == 0) {
					logging::Logger::logWarning("Attempted to get non-existent mesh from model.");
					return nullptr;
				}

				return this->meshes[name];
			}

			bool Model::hasOBB() noexcept {
				for(auto &it : this->meshes) {
					if(it.second->hasOBB()) {
						return true;
					}
				}
				return false;
			}

			Model::~Model() {
				
			}
		}
	}
}