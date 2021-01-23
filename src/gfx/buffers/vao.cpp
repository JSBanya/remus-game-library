#include <remus/gfx/buffers/vao.h>

namespace remus {
	namespace gfx {
		namespace buffers {

			VAO::VAO() { 
				glGenVertexArrays(1, &this->ID); 
			};

			VAO::~VAO() {
				if(this->ID != 0) {
					glDeleteVertexArrays(1, &this->ID);
				}
			}

		}
	}
}
