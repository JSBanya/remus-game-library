#pragma once

#include <glad/glad.h>
#include <filesystem>
#include <vector>
#include <string>
#include <iostream>
#include <remus/logging/logger.h>

namespace remus {
	namespace gfx {
		namespace texture {

			class Texture2D {
			public:
				Texture2D();

				inline void bind() noexcept {
					glBindTexture(GL_TEXTURE_2D, this->ID);
				}

				inline void unbind() noexcept {
					glBindTexture(GL_TEXTURE_2D, 0);
				}

				void genColor(GLint width, GLint height, GLfloat r, GLfloat g, GLfloat b, GLfloat a);
				void genTexture(GLenum format, GLint width, GLint height, const void* data);
				void load(std::string filePath, bool genMipmaps = true);

				inline GLuint getID() noexcept { 
					return this->ID;
				};

				inline GLint getWidth() noexcept {
					return this->width;
				}

				inline GLint getHeight() noexcept {
					return this->height;
				}

				inline GLint getNumChannels() noexcept {
					return this->nChannels;
				}

				virtual ~Texture2D();
				
			protected:
				GLuint ID;
				GLint width;
				GLint height;
				GLint nChannels;
			};

		}
	}
}