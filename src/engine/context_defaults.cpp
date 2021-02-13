#include <remus/engine/context.h>

namespace remus {
	namespace engine {

		void Context::loadDefaults() {

			// default_mesh_square_center
			std::vector<GLfloat> vertices = {
				1.0f, 1.0f, 0.0f,  // top right
				1.0f, 1.0f, 	// top right texture
				
				1.0f, -1.0f, 0.0f,  // bottom right
				1.0f, 0.0f,	 // bottom right texture

				-1.0f, -1.0f, 0.0f,  // bottom left
				0.0f, 0.0f, 	// bottom left texture

				-1.0f, 1.0f, 0.0f,   // top left 
				0.0f, 1.0f		// top left texture
			};
			std::vector<GLuint> indices = {
				0, 1, 3,   // first triangle
				1, 2, 3    // second triangle
			};

			auto default_mesh_square_center = new gfx::models::Mesh();
			default_mesh_square_center
				->addVBODataStatic(vertices)
				->addEBODataStatic(indices)
				->addAttributeAsFloat(0, 3, 5, 0)
				->addAttributeAsFloat(1, 2, 5, 3); 

			this->loadMesh("default_mesh_square_center", default_mesh_square_center);

			// default_vertex_shader
			const std::string default_vertex_shader_source = 
			R"(
				#version 330 core
				layout (location = 0) in vec3 aPos;
				uniform mat4 modelMatrix;
				uniform mat4 viewMatrix;
				uniform mat4 projectionMatrix;
				void main() {
					gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
				}
			)";
			this->loadShader("default_vertex_shader", new gfx::shaders::Shader(default_vertex_shader_source, GL_VERTEX_SHADER));

			// default_fragment_shader
			const std::string default_fragment_shader_source = 
			R"(
			#version 330 core
			in vec2 texCoord;
			out vec4 FragColor;
			uniform vec4 color;
			void main() {
				FragColor = color
			}
			)";

		 	this->loadShader("default_fragment_shader", new gfx::shaders::Shader(default_fragment_shader_source, GL_FRAGMENT_SHADER));

			// default_shader
			this->loadShaderProgram("default_shader", {"default_vertex_shader", "default_fragment_shader"});

			// default_vertex_shader_text_generation
			const std::string default_vertex_shader_text_generation_source = 
			R"(
				#version 330 core
				layout (location = 0) in vec3 aPos;
				layout (location = 1) in vec2 texPos;
				uniform mat4 modelMatrix;
				out vec2 texCoord;
				void main() {
					gl_Position = modelMatrix * vec4(aPos, 1.0);
					texCoord = texPos;
				}
			)";
			this->loadShader("default_vertex_shader_text_generation", new gfx::shaders::Shader(default_vertex_shader_text_generation_source, GL_VERTEX_SHADER));

			// default_fragment_shader_text_generation
			const std::string default_fragment_shader_text_generation_source = 
			R"(
			#version 330 core
			in vec2 texCoord;
			out vec4 FragColor;
			uniform sampler2D character;
			void main() {
				FragColor = texture(character, texCoord);
			}
			)";
			this->loadShader("default_fragment_shader_text_generation", new gfx::shaders::Shader(default_fragment_shader_text_generation_source, GL_FRAGMENT_SHADER));

			// default_shader_text_generation
			this->loadShaderProgram("default_shader_text_generation", {"default_vertex_shader_text_generation", "default_fragment_shader_text_generation"});
		}

	}
}