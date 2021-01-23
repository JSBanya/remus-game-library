#include <remus/gfx/buffers/fbo.h>

namespace remus {
	namespace gfx {
		namespace buffers {

			FBO::FBO() { 
				glGenFramebuffers(1, &this->ID);
			};

			FBO::~FBO() {
				if(this->ID != 0) {
					glDeleteFramebuffers(1, &this->ID);
				}
			}
		}
	}
}