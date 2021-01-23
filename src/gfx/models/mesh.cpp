#include <remus/gfx/models/mesh.h>

namespace remus {
	namespace gfx {
		namespace models {
			
			Mesh* Mesh::addVBODataStatic(std::vector<GLfloat> v) noexcept {
				this->vao->bind();
				this->vbo->bind();
				this->vbo->addDataStatic(v);
				this->vao->unbind();
				this->vbo->unbind();
				return this;
			}

			Mesh* Mesh::addEBODataStatic(std::vector<GLuint> v) noexcept {
				this->vao->bind();
				this->ebo->bind();
				this->ebo->addDataStatic(v);
				this->vao->unbind();
				this->ebo->unbind();
				return this;
			}

			Mesh* Mesh::addAttribute(GLint i, GLint size, GLint stride, GLint offset) noexcept {
				this->vao->bind();
				this->vbo->bind();
				this->vao->addAttribute(i, size, stride, offset);
				this->vao->unbind();
				this->vbo->unbind();
				return this;
			}

			Mesh* Mesh::addAttributePacked(GLint i, GLint size) noexcept {
				this->addAttribute(i, size, size, 0);
				return this;
			}

			Mesh* Mesh::generateOBB(std::vector<GLfloat> vertices, GLint stride, GLint offset) {
				glm::vec3 minVec(0.0f);
				glm::vec3 maxVec(0.0f);

				for(int i = offset; i < (int) vertices.size(); i += stride) {
					glm::vec3 current;
					current.x = vertices[i];
					current.y = vertices[i+1];
					current.z = vertices[i+2];

					if(current.x <= minVec.x && current.y <= minVec.y && current.z <= minVec.z) {
						minVec = current;
					}
					
					if(current.x >= maxVec.x && current.y >= maxVec.y && current.z >= maxVec.z) {
						maxVec = current;
					} 
				}

				this->obb = new OBB();
				this->obb->min = minVec;
				this->obb->max = maxVec;

				this->obbIsSet = true;
				return this;
			}
			
			Mesh::~Mesh() {
				delete this->ebo;
				delete this->vbo;
				delete this->vao;
			}

		}
	}
}