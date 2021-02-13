#pragma once

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include <string>
#include <remus/gfx/buffers/vao.h>
#include <remus/gfx/buffers/vbo.h>
#include <remus/gfx/buffers/ebo.h>

namespace remus {
	namespace gfx {
		namespace models {

			struct OBB {
				// Oriented Bounding Box
				glm::vec3 min;
				glm::vec3 max;
			};

			struct Vertex {
				glm::vec3 Position;
				glm::vec3 Normal;
				glm::vec2 TexCoords;
			};

			class Mesh {
			public:
				Mesh() : vao(new buffers::VAO()), vbo(new buffers::VBO()), ebo(new buffers::EBO()) {};
				Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, bool genOBB = true);

				Mesh* addVBODataStatic(void* data, size_t size) noexcept;
				Mesh* addVBODataStatic(std::vector<GLfloat> v) noexcept;
				Mesh* addEBODataStatic(std::vector<GLuint> v) noexcept;
				Mesh* addAttribute(GLint i, GLint size, GLint stride, GLint offset) noexcept;
				Mesh* addAttributeAsFloat(GLint i, GLint size, GLint stride, GLint offset) noexcept;

				Mesh* generateOBB(std::vector<Vertex> vertices);
				
				inline Mesh* setOBB(OBB* obb) noexcept {
					this->obb = obb;
					return this;
				}

				inline OBB* getOBB() noexcept { 
					return this->obb; 
				}

				inline bool hasOBB() noexcept { 
					return (this->obb != nullptr); 
				}

				inline void draw() noexcept {
					this->vao->bind();
					glDrawElements(GL_TRIANGLES, this->ebo->getNumIndices(), GL_UNSIGNED_INT, 0);
					this->vao->unbind();
				}

				virtual ~Mesh();

			private:
				buffers::VAO* vao;
				buffers::VBO* vbo;
				buffers::EBO* ebo;

				OBB* obb = nullptr;
			};

		}
	}
}