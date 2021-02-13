#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <stdexcept>
#include <string>
#include <vector>
#include <filesystem>
#include <unordered_map>
#include <remus/gfx/texture/texture2d.h>
#include <remus/gfx/models/model.h>
#include <remus/gfx/models/rectangle.h>
#include <remus/gfx/shaders/shaderProgram.h>
#include <remus/gfx/texture/writableTexture2d.h>
#include <remus/gfx/texture/textureSet.h>
#include <remus/gfx/entity/entity.h>
#include <remus/logging/logger.h>

namespace remus {
	namespace gfx {
		namespace texture {

			struct Character {
				Texture2D* texture;
				glm::ivec2 size;
				glm::ivec2 bearing;
				unsigned int advance;
			};

			class Font {
			public:
				Font(std::string fontPath, GLint size);

				inline Character* getCharacter(char c) {
					if(this->characters.count(c) == 0) return nullptr;
					return this->characters[c];
				}

				Texture2D* getText(std::string text, gfx::shaders::ShaderProgram* generationShader);

				virtual ~Font();

			private:
				std::unordered_map<char, Character*> characters;

				models::Model* characterModel;
				entity::Entity* characterEntity;
				TextureSet* characterTextureSet;
			};

		}
	}
}