#pragma once

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include <remus/gfx/buffers/vao.h>
#include <remus/gfx/buffers/vbo.h>
#include <remus/gfx/buffers/ebo.h>

namespace remus {
	namespace gfx {
		namespace models {

			enum DrawMode { TRIANGLES };

			struct OBB {
				// Oriented Bounding Box
				glm::vec3 min;
				glm::vec3 max;
			};

			class Mesh {
			public:
				Mesh(DrawMode m = TRIANGLES) : mode(m), vao(new buffers::VAO()), vbo(new buffers::VBO()), ebo(new buffers::EBO()) {};

				Mesh* addVBODataStatic(std::vector<GLfloat>) noexcept;
				Mesh* addEBODataStatic(std::vector<GLuint>) noexcept;
				Mesh* addAttribute(GLint, GLint, GLint, GLint) noexcept;
				Mesh* addAttributePacked(GLint, GLint) noexcept;

				Mesh* generateOBB(std::vector<GLfloat> vertices, GLint stride, GLint offset);
				
				inline Mesh* setOBB(OBB* obb) noexcept { 
					this->obbIsSet = true;
					this->obb = obb; 
					return this;
				}

				inline OBB* getOBB() noexcept { 
					return this->obb; 
				}

				inline bool hasOBB() noexcept { 
					return this->obbIsSet; 
				}

				inline void draw() noexcept {
					if(this->mode == TRIANGLES)
						this->drawTriangles();
				}

				inline void drawTriangles() noexcept {
					this->vao->bind();
					glDrawElements(GL_TRIANGLES, this->ebo->getNumIndices(), GL_UNSIGNED_INT, 0);
					this->vao->unbind();
				}

				virtual ~Mesh();

			private:
				DrawMode mode;
				buffers::VAO* vao;
				buffers::VBO* vbo;
				buffers::EBO* ebo;

				bool obbIsSet = false;
				OBB* obb;
			};

		}
	}
}