#pragma once

#include <glad/glad.h>
#include <stdexcept>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <remus/gfx/shaders/shader.h>

namespace remus {
    namespace gfx {
        namespace shaders {

            class ShaderProgram {
            public:
                ShaderProgram();
                ShaderProgram(std::vector<Shader*> shaders);

                void link(std::vector<Shader*>);

                inline void bind() noexcept { 
                    glUseProgram(this->ID); 
                };

                inline void unbind() noexcept {
                    glUseProgram(0); 
                }

                inline GLuint getID() noexcept { 
                    return this->ID; 
                };

                // Set uniform: bool
                inline void setUniform(const std::string name, bool value) noexcept {
                    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), (int)value); 
                }

                // Set uniform: int
                inline void setUniform(const std::string name, GLint value) noexcept { 
                    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value); 
                }

                // Set uniform: float
                inline void setUniform(const std::string name, GLfloat value) noexcept { 
                    glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
                }

                // Set uniform: vec3
                inline void setUniform(const std::string name, GLfloat x, GLfloat y, GLfloat z) noexcept {
                    glUniform3f(glGetUniformLocation(this->ID, name.c_str()), x, y, z);
                }

                inline void setUniform(const std::string name, glm::vec3 v3) noexcept {
                    glUniform3fv(glGetUniformLocation(this->ID, name.c_str()), 1, glm::value_ptr(v3));
                }

                // Set uniform: vec4
                inline void setUniform(const std::string name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) noexcept {
                    glUniform4f(glGetUniformLocation(this->ID, name.c_str()), x, y, z, w);
                }

                inline void setUniform(const std::string name, glm::vec4 v4) noexcept {
                    glUniform4fv(glGetUniformLocation(this->ID, name.c_str()), 1, glm::value_ptr(v4));
                }

                // Set uniform: mat4
                inline void setUniform(const std::string name, glm::mat4 m) noexcept {
                    glUniformMatrix4fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(m));
                }

                virtual ~ShaderProgram();
            private:
                GLuint ID;
            };
            
        }
    }
}