#include <remus/gfx/buffers/ssbo.h>

namespace remus {
	namespace gfx {
		namespace buffers {

			SSBO::SSBO() { 
				glGenBuffers(1, &this->ID);
			};

			SSBO::~SSBO() {
				if(this->ID != 0) {
					glDeleteBuffers(1, &this->ID);
				}
			}

		}
	}
}
