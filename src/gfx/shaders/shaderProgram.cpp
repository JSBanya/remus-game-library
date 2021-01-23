#include <remus/gfx/shaders/shaderProgram.h>

namespace remus {
    namespace gfx {
        namespace shaders {

            ShaderProgram::ShaderProgram() : ID(0) {

            }

            ShaderProgram::ShaderProgram(std::vector<Shader*> shaders) : ShaderProgram() {
                this->link(shaders);
            };

            void ShaderProgram::link(std::vector<Shader*> shaders) {
                int success;
                char infoLog[512];

                this->ID = glCreateProgram();
                for(auto s : shaders) {
                    glAttachShader(ID, s->getID());
                }
                glLinkProgram(this->ID);
                glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
                if(!success) {
                    glGetProgramInfoLog(this->ID, 512, NULL, infoLog);
                    std::string errorMessage = "Unable to link shader program with files: ";
                    for(auto s : shaders) {
                        errorMessage += s->getPath();
                        errorMessage += " ";
                    }
                    errorMessage += " | Message: " + std::string(infoLog);
                    throw std::runtime_error(errorMessage);
                }
            }

            ShaderProgram::~ShaderProgram() {
                if(this->ID != 0) {
                    glDeleteProgram(this->ID);
                }
            }

        }
    }
}