#pragma once

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include <remus/gfx/models/model.h>

namespace remus {
	namespace gfx {
		namespace models {

			enum RectangleNormalized {
				NONE,
				WIDTH,
				HEIGHT
			};

			class Rectangle : public Model {
			public:
				Rectangle(GLfloat width, GLfloat height, RectangleNormalized normalize = NONE, bool genOBB = true);

				inline GLfloat getOriginalWidth() noexcept { return this->originalWidth; }
				inline GLfloat getOriginalHeight() noexcept { return this->originalHeight; }

				inline GLfloat getWidth() noexcept { return this->width; }
				inline GLfloat getHeight() noexcept { return this->height; }

				inline GLfloat getOffsetWidth() noexcept { return this->offsetWidth; }
				inline GLfloat getOffsetHeight() noexcept { return this->offsetHeight; }

				virtual ~Rectangle();
			protected:
				GLfloat originalWidth;
				GLfloat originalHeight;

				GLfloat width;
				GLfloat height;

				GLfloat offsetWidth;
				GLfloat offsetHeight;

				Mesh* mesh;
			};
		
		}
	}
}