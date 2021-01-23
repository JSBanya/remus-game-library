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
				static inline void initLibrary() {
					if(FT_Init_FreeType(&Font::ft)) throw std::runtime_error("Unable to init FreeType Library.");
				}

				static inline void destroyLibrary() {
					FT_Done_FreeType(Font::ft);
				}

				Font(std::string fontPath, GLint size);

				inline Character* getCharacter(char c) {
					if(this->characters.count(c) == 0) return nullptr;
					return this->characters[c];
				}

				virtual ~Font();

			private:
				static inline FT_Library ft;
				std::unordered_map<char, Character*> characters;
			};

		}
	}
}