#include <remus/logging/logger.h>

namespace remus {
	void Logger::GLDebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
		assertInitialized();
		std::stringstream typestream;
		typestream << std::hex << type;
		std::string typeStr(typestream.str());

		std::stringstream severitystream;
		severitystream << std::hex << type;
		std::string severityStr(severitystream.str());

		std::string toPrint = "[type=0x" + typeStr + ", severity=0x" + severityStr + "] " + std::string(message);

		if(type == GL_DEBUG_TYPE_ERROR) {
			logError("GL ERROR: " + toPrint);
		} else {
			logWarning("GL MESSAGE: " + toPrint);
		}
	}
}
