#include <remus/engine/entity/entity.h>

namespace remus {
	namespace engine {
		namespace entity {

			Entity::Entity(gfx::models::Model* m, gfx::shaders::ShaderProgram* s, std::string name) {
				this->model = m;
				this->shader = s;
				this->name = name;

				logger::logNotice("Created entity: " + name);
			}

			void Entity::draw() noexcept {
				this->shader->bind();
				for(std::pair<std::string, bool> e : this->shaderUniformBool) this->shader->setUniform(e.first, e.second);
				for(std::pair<std::string, GLint> e : this->shaderUniformInt) this->shader->setUniform(e.first, e.second);
				for(std::pair<std::string, GLfloat> e : this->shaderUniformFloat) this->shader->setUniform(e.first, e.second);
				for(std::pair<std::string, glm::vec3> e : this->shaderUniformVec3) this->shader->setUniform(e.first, e.second);
				for(std::pair<std::string, glm::vec4> e : this->shaderUniformVec4) this->shader->setUniform(e.first, e.second);
				for(std::pair<std::string, glm::mat4> e : this->shaderUniformMat4) this->shader->setUniform(e.first, e.second);
				this->model->draw();
			}

			Entity::~Entity() {
				
			}

		}
	}
}