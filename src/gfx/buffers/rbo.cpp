#include <remus/gfx/buffers/rbo.h>

namespace remus {
	namespace gfx {
		namespace buffers {

			RBO::RBO() { 
				glGenRenderbuffers(1, &this->ID);
			};

			RBO::~RBO() {
				if(this->ID != 0) {
					glDeleteRenderbuffers(1, &this->ID);
				}
			}
		}
	}
}