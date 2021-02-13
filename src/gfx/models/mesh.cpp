#include <remus/gfx/models/mesh.h>

namespace remus {
	namespace gfx {
		namespace models {
			
			Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, bool genOBB) : Mesh() {
				this->addVBODataStatic(&vertices[0], vertices.size() * sizeof(Vertex));
				this->addEBODataStatic(indices);

				this->addAttribute(0, 3, sizeof(Vertex), 0);
				this->addAttribute(1, 3, sizeof(Vertex), offsetof(Vertex, Normal));
				this->addAttribute(2, 3, sizeof(Vertex), offsetof(Vertex, TexCoords));

				if(genOBB) {
					this->generateOBB(vertices);
				}
			}

			Mesh* Mesh::addVBODataStatic(void* data, size_t size) noexcept {
				this->vao->bind();
				this->vbo->bind();
				this->vbo->addDataStatic(data, size);
				this->vao->unbind();
				this->vbo->unbind();
				return this;
			}

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

			Mesh* Mesh::addAttributeAsFloat(GLint i, GLint size, GLint stride, GLint offset) noexcept {
				this->vao->bind();
				this->vbo->bind();
				this->vao->addAttributeAsFloat(i, size, stride, offset);
				this->vao->unbind();
				this->vbo->unbind();
				return this;
			}

			Mesh* Mesh::generateOBB(std::vector<Vertex> vertices) {
				glm::vec3 minVec(0.0f);
				glm::vec3 maxVec(0.0f);

				for(auto vertex : vertices) {
					if(vertex.Position.x <= minVec.x && vertex.Position.y <= minVec.y && vertex.Position.z <= minVec.z) {
						minVec = vertex.Position;
					}
					
					if(vertex.Position.x >= maxVec.x && vertex.Position.y >= maxVec.y && vertex.Position.z >= maxVec.z) {
						maxVec = vertex.Position;
					} 
				}

				if(this->hasOBB()) {
					delete this->obb;
				}

				this->obb = new OBB();
				this->obb->min = minVec;
				this->obb->max = maxVec;

				return this;
			}

			Mesh::~Mesh() {
				delete this->ebo;
				delete this->vbo;
				delete this->vao;
				if(this->hasOBB()) {
					delete this->obb;
				}
			}

		}
	}
}