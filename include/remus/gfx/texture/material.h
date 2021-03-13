#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <stdexcept>
#include <remus/gfx/texture/texture2d.h>
#include <remus/gfx/shaders/shaderProgram.h>
#include <remus/logging/logger.h>

namespace remus {
	namespace gfx {
		namespace texture {

			class Material {
			public:
				Material(Texture2D* diffuse = nullptr, Texture2D* specular = nullptr, GLfloat shininess = 1.0);

				Material* setDiffuse(Texture2D* diffuse) noexcept;
				Material* setSpecular(Texture2D* specular) noexcept;
				Material* setShininess(GLfloat shininess) noexcept;

				void bind(shaders::ShaderProgram* shader);
				void unbind();

				~Material();
			private:
				Texture2D* diffuse;
				Texture2D* specular;
				GLfloat shininess = 1.0;
			
			private:
				static inline int MATERIAL_COUNT = 0;
				static inline Texture2D* DEFAULT_DIFFUSE = nullptr;
				static inline Texture2D* DEFAULT_SPECULAR = nullptr;
			};

		}
	}
}