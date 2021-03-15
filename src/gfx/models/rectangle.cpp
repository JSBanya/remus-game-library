#include <remus/gfx/models/rectangle.h>

namespace remus {
	namespace gfx {
		namespace models {

			Rectangle::Rectangle(GLfloat width, GLfloat height, RectangleNormalized normalize, bool genOBB) : Model({}) {
				this->originalWidth = width;
				this->originalHeight = height;

				auto halfWidth = width / 2;
				auto halfHeight = height / 2;

				auto divisor = 1.0f;
				if(normalize == WIDTH) {
					divisor = width;
				} else if(normalize == HEIGHT) {
					divisor = height;
				}

				auto eWidth = halfWidth / divisor;
				auto eHeight = halfHeight / divisor;

				this->width = eWidth * 2;
				this->height = eHeight * 2;

				this->offsetWidth = eWidth;
				this->offsetHeight = eHeight;

				std::vector<GLfloat> vertices = {
					eWidth, eHeight, 0.0f,  // top right
					1.0f, 1.0f, 	// top right texture
					
					-eWidth, -eHeight, 0.0f,  // bottom left
					0.0f, 0.0f, 	// bottom left texture

					eWidth, -eHeight, 0.0f,  // bottom right
					1.0f, 0.0f,	 // bottom right texture

					-eWidth, eHeight, 0.0f,   // top left 
					0.0f, 1.0f		// top left texture
				};
				std::vector<GLuint> indices = {
					0, 1, 2,   // first triangle
					0, 3, 1    // second triangle
				};

				this->mesh = new Mesh();
				this->mesh
					->addVBODataStatic(vertices)
					->addEBODataStatic(indices)
					->addAttributeAsFloat(0, 3, 5, 0)
					->addAttributeAsFloat(1, 2, 5, 3);

				if(genOBB) {
					OBB* obb = new OBB();
					obb->min = glm::vec3(-eWidth, -eHeight, 0.0f);
					obb->max = glm::vec3(eWidth, eHeight, 0.0f);
					this->mesh->setOBB(obb);
				}

				this->addMesh(this->mesh, "rectangle");
			}

			Rectangle::~Rectangle() {
				delete this->mesh;
			}

		}
	}
}