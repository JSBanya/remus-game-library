#include <remus/gfx/texture/font.h>

namespace remus {
	namespace gfx {
		namespace texture {

			Font::Font(std::string fontPath, GLint size) {
				std::filesystem::path p(fontPath);
				if(!std::filesystem::exists(p)) {
					throw std::runtime_error("Font not found at path: " + fontPath);
				}

				FT_Face face;
				if(FT_New_Face(Font::ft, p.c_str(), 0, &face)) {
					throw std::runtime_error("Failed to load font: " + fontPath);
				}

				FT_Set_Pixel_Sizes(face, 0, size); 

				GLint unpackAlignment;
				glGetIntegerv(GL_UNPACK_ALIGNMENT, &unpackAlignment);
				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

				for (unsigned char c = 0; c < 128; c++) {
					if(FT_Load_Char(face, c, FT_LOAD_RENDER)) {
						FT_Done_Face(face);
						throw std::runtime_error("Unable to load glyph " + std::to_string(c) + " from font " + fontPath);
					}

					// Generate texture
					auto tex = new Texture2D();
					tex->bind();
					tex->genTexture(GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, face->glyph->bitmap.buffer);

					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

					// Store character for later use
					auto character = new Character();
					character->texture = tex;
					character->size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
					character->bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
					character->advance = face->glyph->advance.x;
					this->characters[c] = character;
				}

				glPixelStorei(GL_UNPACK_ALIGNMENT, unpackAlignment);
				FT_Done_Face(face);
			}

			Font::~Font() {
				for(auto c : this->characters) {
					delete c.second->texture;
					delete c.second;
				}
			}

		}
	}
}