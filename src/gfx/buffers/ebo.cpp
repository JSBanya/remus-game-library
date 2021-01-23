#include <remus/gfx/buffers/ebo.h>

namespace remus {
	namespace gfx {
		namespace buffers {

			EBO::EBO() { 
				glGenBuffers(1, &this->ID); 
			};

			EBO::~EBO() {
				if(this->ID != 0) {
					glDeleteBuffers(1, &this->ID);
				}
			}

		}
	}
}
