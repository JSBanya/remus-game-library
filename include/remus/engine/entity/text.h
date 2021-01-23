#pragma once

#include <string>
#include <vector>
#include <remus/utils/definitions.h>
#include <remus/gfx/models/model.h>
#include <remus/gfx/models/mesh.h>
#include <remus/gfx/texture/font.h>
#include <remus/gfx/shaders/shaderProgram.h>
#include <remus/gfx/texture/writableTexture2d.h>
#include <remus/engine/entity/entity.h>
#include <remus/logging/logger.h>

namespace remus {
	namespace engine {
		namespace entity {

			enum TextModelType {
				TEXT_FIXED_HEIGHT,
				TEXT_FIXED_WIDTH,
				TEXT_SQUARE
			};
			
			class Text : public Entity {
			public:
				Text(gfx::texture::Font* font, std::string t, gfx::shaders::ShaderProgram* generationShader = utils::SHADER_PROG_GENERIC_TEXT_GEN, TextModelType modelType = TEXT_FIXED_HEIGHT);

				inline GLfloat getWidth() noexcept { return this->width; }
				inline GLfloat getHeight() noexcept { return this->height; }
				inline GLfloat getWHRatio() noexcept { return (this->width / this->height); }

				virtual ~Text();
			private:
				GLfloat width = 1.0f;
				GLfloat height = 1.0f;
				gfx::texture::WritableTexture2D* textTexture;
				std::string text;
			};

		}
	}
}