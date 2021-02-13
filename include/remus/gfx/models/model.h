#pragma once

#include <string>
#include <unordered_map>
#include <stdexcept>
#include <remus/gfx/models/mesh.h>
#include <remus/logging/logger.h>
#include <remus/gfx/shaders/shaderProgram.h>
#include <remus/gfx/texture/textureSet.h>

namespace remus {
	namespace gfx {
		namespace models {
			

			class Model {
			public:
				Model(std::unordered_map<std::string, Mesh*> meshes);
				Model(std::vector<Mesh*> meshes, std::vector<std::string> names);

				void addMesh(Mesh* m, std::string name);

				Mesh* getMesh(std::string name);
				inline std::unordered_map<std::string, Mesh*> getMeshes() {
					return this->meshes;
				}

				void draw(shaders::ShaderProgram* shader, std::unordered_map<std::string, texture::TextureSet*> textures = {});

				bool hasOBB() noexcept;

				virtual ~Model();

			protected:
				std::unordered_map<std::string, Mesh*> meshes;
			};
		}
	}
}