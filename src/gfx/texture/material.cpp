#include <remus/gfx/texture/material.h>

namespace remus {
	namespace gfx {
		namespace texture {


			Material* Material::setDiffuse(Texture2D* diffuse) noexcept {
				this->diffuse = diffuse;
				return this;
			}

			Material* Material::setSpecular(Texture2D* specular) noexcept {
				this->specular = specular;
				return this;
			}

			Material* Material::setShininess(GLfloat shininess) noexcept {
				this->shininess = shininess;
				return this;
			}

			void Material::bind(shaders::ShaderProgram* shader) {
				if(this->diffuse != nullptr) {
					glActiveTexture(GL_TEXTURE0);
					shader->setUniform("material.diffuse", 0);
					this->diffuse->bind();
				}

				if(this->specular != nullptr) {
					glActiveTexture(GL_TEXTURE1);
					shader->setUniform("material.specular", 1);
					this->specular->bind();
				}

				shader->setUniform("material.shininess", this->shininess);
			}

			void Material::unbind() {
				if(this->diffuse != nullptr) {
					glActiveTexture(GL_TEXTURE0);
					this->diffuse->unbind();
				}

				if(this->specular != nullptr) {
					glActiveTexture(GL_TEXTURE1);
					this->specular->unbind();
				}
			}

		}
	}
}