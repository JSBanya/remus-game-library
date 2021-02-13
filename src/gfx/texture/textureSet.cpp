#include <remus/gfx/texture/textureSet.h>

namespace remus {
	namespace gfx {
		namespace texture {

			TextureSet::TextureSet(std::unordered_map<std::string, Texture2D*> textures = {}, std::vector<Texture2D*> diffuseTextures = {}, std::vector<Texture2D*> specularTextures = {}) {
				this->diffuseTextures = diffuseTextures;
				this->specularTextures = specularTextures;
				this->textures = textures;
			}

			TextureSet::TextureSet(std::vector<Texture2D*> textures, std::vector<Texture2D*> names, std::vector<Texture2D*> diffuseTextures = {}, std::vector<Texture2D*> specularTextures = {}) {
				if(textures.size() != names.size()) {
					throw std::logic_error("List of textures provided to texture set with unequal number of names.");
				}

				for(auto i = 0; i < textures.size(); i++) {
					this->addTexture(textures[i], names[i]);
				}
				
				this->diffuseTextures = diffuseTextures;
				this->specularTextures = specularTextures;
			}

			void TextureSet::addDiffuse(Texture2D* diffuseTexture) noexcept {
				this->diffuseTextures.push_back(diffuseTexture);
			}

			void TextureSet::addSpecular(Texture2D* specularTexture) noexcept {
				this->specularTextures.push_back(specularTexture);
			}

			void TextureSet::addTexture(Texture2D* texture, std::string name) noexcept {
				this->textures[name] = texture;
			}

			void TextureSet::removeDiffuse(Texture2D* diffuseTexture, bool resize) {
				this->removeTextureFromVector(&this->diffuseTextures, diffuseTexture, resize);
			}

			void TextureSet::removeDiffuse(size_t index, bool resize) {
				this->removeTextureFromVector(&this->diffuseTextures, index, resize);
			}

			void TextureSet::removeSpecular(Texture2D* specularTexture, bool resize) {
				this->removeTextureFromVector(&this->specularTextures, specularTexture, resize);
			}

			void TextureSet::removeSpecular(size_t index, bool resize) {
				this->removeTextureFromVector(&this->specularTextures, index, resize);
			}

			void TextureSet::removeTexture(std::string name) {
				auto it = this->textures.find(name);
				if(it != this->textures.end()) {
					this->textures.erase(it);
				}
			}

			void TextureSet::bind(shaders::ShaderProgram* shader) {
				auto texNum = 0;
				for(auto i = 0; i < this->diffuseTextures.size(); i++) {
					glActiveTexture(GL_TEXTURE0 + texNum);
					shader->setUniform("diffuse_" + std::to_string(i), texNum);
					this->diffuseTextures[i]->bind();
					texNum++;
				}

				for(auto i = 0; i < this->specularTextures.size(); i++) {
					glActiveTexture(GL_TEXTURE0 + texNum);
					shader->setUniform("specular_" + std::to_string(i), texNum);
					this->specularTextures[i]->bind();
					texNum++;
				}

				for(auto &it : this->textures) {
					glActiveTexture(GL_TEXTURE0 + texNum);
					shader->setUniform(it.first, texNum);
					it.second->bind();
					texNum++;
				}
			}

			void TextureSet::removeTextureFromVector(std::vector<Texture2D*>* vec_ptr, Texture2D* texture, bool resize) {
				auto vec = *vec_ptr;
				size_t index = 0;
				while(index < vec.size() && vec[index] != texture) {
					index++;
				}

				this->removeTextureFromVector(vec_ptr, index, resize);
				return;
			}

			void TextureSet::removeTextureFromVector(std::vector<Texture2D*>* vec_ptr, size_t index, bool resize) {
				auto vec = *vec_ptr;
				if(index >= vec.size()) {
					return;
				}

				if(!resize) {
					vec[index] = nullptr;
					return;
				}

				// Resize vector
				vec.erase(vec.begin() + index);
				return;
			}
		}
	}
}