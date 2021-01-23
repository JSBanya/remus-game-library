#pragma once

#include <glad/glad.h>
#include <stdexcept>
#include <string>

namespace remus {
    namespace gfx {
        namespace shaders {

            class Shader {
            public:
                Shader();
                Shader(std::string src, GLenum shaderType);
            
                void compile(std::string, GLenum);
                
                inline GLuint getID() { return this->ID; };
                inline std::string getPath() { return this->path; };

                virtual ~Shader();
            protected:
                GLuint ID;
                std::string path;
            };
            
        }
    }
}