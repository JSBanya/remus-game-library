#include <remus/gfx/texture/texture2d.h>

#define STB_IMAGE_IMPLEMENTATION
#include <remus/stb_image.h>

namespace remus {
	namespace gfx {
		namespace texture {

			Texture2D::Texture2D() { 
				glGenTextures(1, &this->ID); 
			};

			void Texture2D::genColor(GLint width, GLint height, GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
				std::vector<GLfloat> data(4 * width * height);
				for(auto i = 0; i < data.size(); i += 4) {
					data[i] = r;
					data[i+1] = g;
					data[i+2] = b;
					data[i+3] = a;
				}

				this->width = width;
				this->height = height;

				this->bind();
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, &data[0]);
				this->unbind();
			}

			void Texture2D::genTexture(GLenum format, GLint width, GLint height, const void * data) {
				this->width = width;
				this->height = height;
				glTexImage2D(GL_TEXTURE_2D, 0, format, this->width, this->height, 0, format, GL_UNSIGNED_BYTE, data);
			}

			void Texture2D::load(std::string filePath, bool genMipmaps) {
				stbi_set_flip_vertically_on_load(true);

				std::filesystem::path p(filePath);
				if(!std::filesystem::exists(p)) {
					throw std::runtime_error("Image not found: " + filePath);
				}

				auto data = stbi_load(p.c_str(), &this->width, &this->height, &this->nChannels, 0);
				if(!data) {
					throw std::ios_base::failure("Error loading texture from " + filePath);
				}

				GLenum format;
				if(this->nChannels == 1)
					format = GL_RED;
				else if(this->nChannels == 3)
					format = GL_RGB;
				else if(this->nChannels == 4)
					format = GL_RGBA;

				this->bind();
				this->genTexture(format, this->width, this->height, data);

				if(genMipmaps) {
					glGenerateMipmap(GL_TEXTURE_2D);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				} else {
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				}
				
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				this->unbind();
				stbi_image_free(data);
				
				logger::logNotice("Loaded texture with width=" + std::to_string(this->width) + ", height=" + std::to_string(this->height) + ", channels=" + std::to_string(this->nChannels));
			}

			Texture2D::~Texture2D() {
				glDeleteTextures(1, &this->ID);
			}

		}
	}
}