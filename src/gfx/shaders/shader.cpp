#include <remus/gfx/shaders/shader.h>

namespace remus {
    namespace gfx {
        namespace shaders {
        
            Shader::Shader() : ID(0) {

            }

            Shader::Shader(std::string src, GLenum shaderType) : Shader() {
                this->compile(src, shaderType);
            }

            void Shader::compile(std::string code, GLenum shaderType) {
                int success;
                char infoLog[512];
                const char* src = code.c_str();

                this->ID = glCreateShader(shaderType);
                glShaderSource(this->ID, 1, &src, NULL);
                glCompileShader(this->ID);
                glGetShaderiv(this->ID, GL_COMPILE_STATUS, &success);
                if(!success) {
                    glGetShaderInfoLog(this->ID, 512, NULL, infoLog);
                    std::string errorMessage = "Unable to compile shader file: " + this->path;
                    errorMessage += " | Message: " + std::string(infoLog);
                    throw std::runtime_error(errorMessage);
                };
            }

            Shader::~Shader() {
                if(this->ID != 0) {
                    glDeleteShader(this->ID);
                }
            }

        }
    }
}