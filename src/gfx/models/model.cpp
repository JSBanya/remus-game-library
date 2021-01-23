#include <remus/gfx/models/model.h>

namespace remus {
	namespace gfx {
		namespace models {

			Model::Model(Mesh* m, std::vector<texture::Texture2D*> t) {
				this->mesh = m;
				for(auto tex : t) 
					this->addTexture(tex);
				this->modelMatrixReset();
			}

			Model::~Model() {
				
			}
		}
	}
}