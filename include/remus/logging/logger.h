#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <chrono>

namespace remus {
    namespace logger {
        
        extern std::ofstream logFile;

        inline void initLogger(std::string dir) {
            std::string now = std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
            logFile.open(dir + now + ".log");
        }

        inline void closeLogger() {
            logFile.close();
        }

        inline void logNotice(std::string s) {
            std::cout << s << std::endl;
            logFile << s << std::endl;
        } 

        inline void logWarning(std::string s) {
            std::cout << "\u001b[33m" << "[WARNING] " << s << "\u001b[0m" << std::endl;
            logFile << "[WARNING] " << s << std::endl;
        }

        inline void logError(std::string s) {
            std::cout << "\u001b[31m" << "[ERROR] " << s << "\u001b[0m" << std::endl;
            logFile << "[ERROR] " << s << std::endl;
        }
        
    }
}
