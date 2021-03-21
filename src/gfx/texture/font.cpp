#include <remus/gfx/texture/font.h>

namespace remus {
	namespace gfx {
		namespace texture {

			Font::Font(std::string fontPath, GLint size) {
				std::filesystem::path p(fontPath);
				if(!std::filesystem::exists(p)) {
					throw std::runtime_error("Font not found at path: " + fontPath);
				}

				FT_Library ft;
				if(FT_Init_FreeType(&ft)) {
					throw std::runtime_error("Unable to init FreeType Library.");
				}

				FT_Face face;
				if(FT_New_Face(ft, p.c_str(), 0, &face)) {
					FT_Done_FreeType(ft);
					throw std::runtime_error("Failed to load font: " + fontPath);
				}

				FT_Set_Pixel_Sizes(face, 0, size); 

				GLint unpackAlignment;
				glGetIntegerv(GL_UNPACK_ALIGNMENT, &unpackAlignment);
				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

				for (unsigned char c = 0; c < 128; c++) {
					if(FT_Load_Char(face, c, FT_LOAD_RENDER)) {
						FT_Done_Face(face);
						FT_Done_FreeType(ft);
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
				FT_Done_FreeType(ft);

				// Initialize objects for text generation
				characterModel = new models::Rectangle(2.0f, 2.0f);
			}

			Texture2D* Font::getText(std::string text, shaders::ShaderProgram* generationShader) {
				// Find width and height of final texture
				GLfloat width = 0.0f;
				GLfloat height = 0.0f;
				GLfloat origin = 0.0f;

				for(const char c : text) {
					auto ch = this->getCharacter(c);
					if(ch == nullptr) {
						logging::Logger::logWarning("Error in generating text: Character '" + std::string(1, c) + "' not found.");
						continue;
					}
					width += (ch->advance >> 6);
					
					auto ypos = ch->size.y - ch->bearing.y;
					if(ypos > origin)
						origin = ypos;

					auto h = ch->size.y + ypos;
					if(h > height)
						height = h;
				}

				// Fill texture
				auto textTexture = new gfx::texture::WritableTexture2D(width, height);
				textTexture->startWrite();
				
				GLfloat x = 0.0;
				for(const char c : text) {
					auto ch = this->getCharacter(c);
					if(ch == nullptr) {
						logging::Logger::logWarning("Error in generating text: Character '" + std::string(1, c) + "' not found.");
						continue;
					}
					
					GLfloat xpos = x + ch->bearing.x;
					xpos /= width;
					xpos = -1.0f + 2.0f * xpos;

					GLfloat ypos = origin - (ch->size.y - ch->bearing.y);
					ypos /= height;
					ypos = -1.0f + 2.0f * ypos;

					GLfloat sizeX = 2.0 * (ch->size.x / width);
					GLfloat sizeY = 2.0 * (ch->size.y / height);
					

					models::ModelMatrix modelMatrix(models::LOCAL);
					modelMatrix.translate(xpos, ypos, 0.0f);
					modelMatrix.scale(sizeX, sizeY, 1.0f);

					generationShader->bind();
					glActiveTexture(GL_TEXTURE0);
					generationShader->setUniform("character", 0);
					ch->texture->bind();
					generationShader->setUniform("modelMatrix", modelMatrix.get());
					this->characterModel->getMesh("rectangle")->drawTriangles();
					
					x += (ch->advance >> 6);
				}

				textTexture->stopWrite();

				generationShader->unbind();
				return textTexture;
			}

			Font::~Font() {
				for(auto c : this->characters) {
					delete c.second->texture;
					delete c.second;
				}

				delete this->characterModel;
			}

		}
	}
}