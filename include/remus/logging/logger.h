#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <glad/glad.h>

namespace remus {
    namespace logging {
        
        class Logger {
        public:
            inline static std::string init(std::string dir, std::string name = "") {
                if(isInitialized) 
                    close();

                if(name.length() == 0)
                    name = std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
                
                logFile.open(dir + name + ".log");
                isInitialized = false;
                return name;
            }

            inline static void close() {
                logFile.close();
                isInitialized = false;
            }

            inline static void assertInitialized() {
                if(!isInitialized) {
                    init("./");
                }
            }

            inline static void logNotice(std::string s) {
                assertInitialized();
                std::cout << s << std::endl;
                logFile << s << std::endl;
            } 

            inline static void logWarning(std::string s) {
                assertInitialized();
                std::cout << "\u001b[33m" << "[WARNING] " << s << "\u001b[0m" << std::endl;
                logFile << "[WARNING] " << s << std::endl;
            }

            inline static void logError(std::string s) {
                assertInitialized();
                std::cout << "\u001b[31m" << "[ERROR] " << s << "\u001b[0m" << std::endl;
                logFile << "[ERROR] " << s << std::endl;
            }

            inline static void enableGLDebug() {
                glEnable(GL_DEBUG_OUTPUT);
                glDebugMessageCallback(GLDebugMessageCallback, 0);
            }

            static void GLDebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

        private:
            inline static std::ofstream logFile;
            inline static bool isInitialized = false;
        };
    }
}
