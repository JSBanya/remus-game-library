#include <remus/engine/entity/text.h>

namespace remus {
	namespace engine {
		namespace entity {

			Text::Text(gfx::texture::Font* font, std::string t, gfx::shaders::ShaderProgram* generationShader, TextModelType modelType) 
			: text(t), Entity(new gfx::models::Model(new gfx::models::Mesh()), utils::SHADER_PROG_GENERIC_TEXT_DRAW, "text_entity(\""+t+"\")")
			{
				// Find width and height of final texture
				GLfloat width = 0.0f;
				GLfloat height = 0.0f;
				GLfloat origin = 0.0f;

				for(const char c : t) {
					auto ch = font->getCharacter(c);
					if(ch == nullptr) {
						logger::logWarning("Error in generating text: Character '" + std::string(1, c) + "' not found.");
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

				// Create character entity
				gfx::models::Model m(utils::MESH_SQUARE_CENTERED);
				
				// Fill texture
				this->textTexture = new gfx::texture::WritableTexture2D(width, height);
				this->textTexture->startWrite();
				
				GLfloat x = 0.0;
				for(const char c : t) {
					auto ch = font->getCharacter(c);
					if(ch == nullptr) {
						logger::logWarning("Error in generating text: Character '" + std::string(1, c) + "' not found.");
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
					
					m.modelMatrixReset(gfx::models::RELATIVE)
						->clearTextures()
						->addTexture(ch->texture)
						->translate(xpos, ypos, 0.0f)
						->scale(sizeX, sizeY, 1.0f);
					
					generationShader->bind();
					generationShader->setUniform("modelMatrix", m.getModelMatrix());
					m.draw();
					x += (ch->advance >> 6);
				}

				this->textTexture->stopWrite();

				// Create model
				if(modelType == TEXT_FIXED_WIDTH)
					this->height = height / width;
				else if(modelType == TEXT_FIXED_HEIGHT)
					this->width = width / height;
				else if(modelType == TEXT_SQUARE) {
					this->width = 1.0f;
					this->height = 1.0f;
				}
				
				std::vector<GLfloat> vertices = {
					this->getWidth(), this->getHeight(), 0.0f,  // top right
					1.0f, 1.0f, 	// top right texture
					
					this->getWidth(), -this->getHeight(), 0.0f,  // bottom right
					1.0f, 0.0f,	 // bottom right texture

					-this->getWidth(), -this->getHeight(), 0.0f,  // bottom left
					0.0f, 0.0f, 	// bottom left texture

					-this->getWidth(), this->getHeight(), 0.0f,   // top left 
					0.0f, 1.0f		// top left texture
				};
				std::vector<GLuint> indices = {
					0, 1, 3,   // first triangle
					1, 2, 3    // second triangle
				};

				this->getModel()->getMesh()
					->addVBODataStatic(vertices)
					->addEBODataStatic(indices)
					->addAttribute(0, 3, 5, 0)
					->addAttribute(1, 2, 5, 3); 

				this->model->addTexture(this->textTexture);
			}

			Text::~Text() {
				delete this->getModel()->getMesh();
				delete this->getModel();
				delete this->textTexture;
			}

		}
	}
}