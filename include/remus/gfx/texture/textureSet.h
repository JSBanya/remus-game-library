#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <stdexcept>
#include <remus/gfx/texture/texture2d.h>
#include <remus/gfx/shaders/shaderProgram.h>
#include <remus/logging/logger.h>

namespace remus {
	namespace gfx {
		namespace texture {

			class TextureSet {
			public:
				TextureSet(std::unordered_map<std::string, Texture2D*> textures = {}, std::vector<Texture2D*> diffuseTextures = {}, std::vector<Texture2D*> specularTextures = {});
				TextureSet(std::vector<Texture2D*> textures, std::vector<Texture2D*> names, std::vector<Texture2D*> diffuseTextures = {}, std::vector<Texture2D*> specularTextures = {});

				void addDiffuse(Texture2D* diffuseTexture) noexcept;
				void addSpecular(Texture2D* specularTexture) noexcept;
				void addTexture(Texture2D* texture, std::string name) noexcept;

				void removeDiffuse(Texture2D* diffuseTexture, bool resize);
				void removeDiffuse(size_t index, bool resize);
				void removeSpecular(Texture2D* specularTexture, bool resize);
				void removeSpecular(size_t index, bool resize);
				void removeTexture(std::string name);

				void bind(shaders::ShaderProgram* shader);

				inline std::vector<Texture2D*> getDiffuse() noexcept {
					return this->diffuseTextures;
				}

				inline std::vector<Texture2D*> getSpecular() noexcept {
					return this->specularTextures;
				}

				inline std::unordered_map<std::string, Texture2D*> getTextures() noexcept {
					return this->textures;
				}

				inline Texture2D* getTexture(std::string name) noexcept {
					return this->textures[name];
				}

			private:
				void removeTextureFromVector(std::vector<Texture2D*>* vec_ptr, Texture2D* texture, bool resize);
				void removeTextureFromVector(std::vector<Texture2D*>* vec_ptr, size_t index, bool resize);

			private:
				std::vector<Texture2D*> diffuseTextures;
				std::vector<Texture2D*> specularTextures;
				std::unordered_map<std::string, Texture2D*> textures;
			};

		}
	}
}