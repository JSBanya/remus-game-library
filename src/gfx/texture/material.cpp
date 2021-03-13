#include <remus/gfx/texture/material.h>

namespace remus {
	namespace gfx {
		namespace texture {
			Material::Material(Texture2D* diffuse, Texture2D* specular, GLfloat shininess) 
			: diffuse(diffuse), specular(specular), shininess(shininess) 
			{
				if(Material::MATERIAL_COUNT == 0) {
					// Generate defaults
					Material::DEFAULT_DIFFUSE = new Texture2D();
					Material::DEFAULT_DIFFUSE->genColor(1, 1, 1.0, 0.0, 1.0, 1.0);

					Material::DEFAULT_SPECULAR = new Texture2D();
					Material::DEFAULT_SPECULAR->genColor(1, 1, 0.0, 0.0, 0.0, 1.0);
				}

				Material::MATERIAL_COUNT++;
			}

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
				
				glActiveTexture(GL_TEXTURE0);
				shader->setUniform("material.diffuse", 0);
				if(this->diffuse != nullptr) {
					this->diffuse->bind();
				} else {
					Material::DEFAULT_DIFFUSE->bind();
				}
				

				glActiveTexture(GL_TEXTURE1);
				shader->setUniform("material.specular", 1);
				if(this->specular != nullptr) {
					this->specular->bind();
				} else{
					Material::DEFAULT_SPECULAR->bind();
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

			Material::~Material() {
				Material::MATERIAL_COUNT--;
				if(Material::MATERIAL_COUNT == 0) {
					delete Material::DEFAULT_DIFFUSE;
					delete Material::DEFAULT_SPECULAR;
				}
			}

		}
	}
}