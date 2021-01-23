#include <remus/gfx/buffers/vbo.h>

namespace remus {
	namespace gfx {
		namespace buffers {

			VBO::VBO() { 
				glGenBuffers(1, &this->ID); 
			};

			VBO::~VBO() {
				if(this->ID != 0) {
					glDeleteBuffers(1, &this->ID);
				}
			}

		}
	}
}