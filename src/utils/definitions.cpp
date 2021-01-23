#include <remus/utils/definitions.h>

namespace remus {
	namespace utils {

		gfx::models::Mesh* MESH_SQUARE_CENTERED = nullptr;

		gfx::shaders::Shader* SHADER_VERT_GENERIC_TEXTURE = nullptr;
		gfx::shaders::Shader* SHADER_FRAG_GENERIC_TEXTURE = nullptr;
		gfx::shaders::ShaderProgram* SHADER_PROG_GENERIC_TEXTURE = nullptr;

		gfx::shaders::Shader* SHADER_VERT_GENERIC_TEXTURE_ONLYMODEL = nullptr;
		gfx::shaders::Shader* SHADER_FRAG_GENERIC_TEXTURE_ONLYMODEL = nullptr;
		gfx::shaders::ShaderProgram* SHADER_PROG_GENERIC_TEXTURE_ONLYMODEL = nullptr;

		gfx::shaders::Shader* SHADER_VERT_GENERIC_TEXT_GEN = nullptr;
		gfx::shaders::Shader* SHADER_FRAG_GENERIC_TEXT_GEN = nullptr;
		gfx::shaders::ShaderProgram* SHADER_PROG_GENERIC_TEXT_GEN = nullptr;

		gfx::shaders::Shader* SHADER_VERT_GENERIC_TEXT_DRAW = nullptr;
		gfx::shaders::Shader* SHADER_FRAG_GENERIC_TEXT_DRAW = nullptr;
		gfx::shaders::ShaderProgram* SHADER_PROG_GENERIC_TEXT_DRAW = nullptr;

		
		void initDefinitions() noexcept {
			// MESH_SQUARE_CENTERED
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
			MESH_SQUARE_CENTERED = new gfx::models::Mesh();
			MESH_SQUARE_CENTERED->addVBODataStatic(vertices)->addEBODataStatic(indices)->addAttribute(0, 3, 5, 0)->addAttribute(1, 2, 5, 3); 


			// SHADER_VERT_GENERIC_TEXTURE
			const std::string SHADER_VERT_GENERIC_TEXTURE_SOURCE = 
			R"(
				#version 330 core
				layout (location = 0) in vec3 aPos;
				layout (location = 1) in vec2 texPos;
				uniform mat4 modelMatrix;
				uniform mat4 viewMatrix;
				uniform mat4 projectionMatrix;
				out vec2 texCoord;
				void main() {
					gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
					texCoord = texPos;
				}
			)";
			SHADER_VERT_GENERIC_TEXTURE = new gfx::shaders::Shader(SHADER_VERT_GENERIC_TEXTURE_SOURCE, GL_VERTEX_SHADER);

			// SHADER_FRAG_GENERIC_TEXTURE
			const std::string SHADER_FRAG_GENERIC_TEXTURE_SOURCE = 
			R"(
			#version 330 core
			in vec2 texCoord;
			out vec4 FragColor;
			uniform sampler2D texture1;
			void main() {
				FragColor = texture(texture1, texCoord);
			}
			)";

			SHADER_FRAG_GENERIC_TEXTURE = new gfx::shaders::Shader(SHADER_FRAG_GENERIC_TEXTURE_SOURCE, GL_FRAGMENT_SHADER);

			// SHADER_PROG_GENERIC_TEXTURE
			SHADER_PROG_GENERIC_TEXTURE = new gfx::shaders::ShaderProgram({SHADER_VERT_GENERIC_TEXTURE, SHADER_FRAG_GENERIC_TEXTURE});


			// SHADER_VERT_GENERIC_TEXTURE_ONLYMODEL
			const std::string SHADER_VERT_GENERIC_TEXTURE_ONLYMODEL_SOURCE = 
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
			SHADER_VERT_GENERIC_TEXTURE_ONLYMODEL = new gfx::shaders::Shader(SHADER_VERT_GENERIC_TEXTURE_ONLYMODEL_SOURCE, GL_VERTEX_SHADER);

			// SHADER_FRAG_GENERIC_TEXTURE_ONLYMODEL
			const std::string SHADER_FRAG_GENERIC_TEXTURE_ONLYMODEL_SOURCE = 
			R"(
			#version 330 core
			in vec2 texCoord;
			out vec4 FragColor;
			uniform sampler2D texture1;
			void main() {
				FragColor = texture(texture1, texCoord);
			}
			)";

			SHADER_FRAG_GENERIC_TEXTURE_ONLYMODEL = new gfx::shaders::Shader(SHADER_FRAG_GENERIC_TEXTURE_ONLYMODEL_SOURCE, GL_FRAGMENT_SHADER);

			// SHADER_PROG_GENERIC_TEXTURE_ONLYMODEL
			SHADER_PROG_GENERIC_TEXTURE_ONLYMODEL = new gfx::shaders::ShaderProgram({SHADER_VERT_GENERIC_TEXTURE_ONLYMODEL, SHADER_FRAG_GENERIC_TEXTURE_ONLYMODEL});


			// SHADER_VERT_GENERIC_TEXT_GEN
			const std::string SHADER_VERT_GENERIC_TEXT_GEN_SOURCE = 
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
			SHADER_VERT_GENERIC_TEXT_GEN = new gfx::shaders::Shader(SHADER_VERT_GENERIC_TEXT_GEN_SOURCE, GL_VERTEX_SHADER);


			// SHADER_FRAG_GENERIC_TEXT_GEN
			const std::string SHADER_FRAG_GENERIC_TEXT_GEN_SOURCE = 
			R"(
			#version 330 core
			in vec2 texCoord;
			out vec4 FragColor;
			uniform sampler2D texture1;
			void main() {
				FragColor = texture(texture1, texCoord);
			}
			)";

			SHADER_FRAG_GENERIC_TEXT_GEN = new gfx::shaders::Shader(SHADER_FRAG_GENERIC_TEXT_GEN_SOURCE, GL_FRAGMENT_SHADER);


			// SHADER_PROG_GENERIC_TEXT_GEN
			SHADER_PROG_GENERIC_TEXT_GEN = new gfx::shaders::ShaderProgram({SHADER_VERT_GENERIC_TEXT_GEN, SHADER_FRAG_GENERIC_TEXT_GEN});


			// SHADER_VERT_GENERIC_TEXT_DRAW
			const std::string SHADER_VERT_GENERIC_TEXT_DRAW_SOURCE = 
			R"(
				#version 330 core
				layout (location = 0) in vec3 aPos;
				layout (location = 1) in vec2 texPos;
				uniform mat4 modelMatrix;
				uniform mat4 viewMatrix;
				uniform mat4 projectionMatrix;
				out vec2 texCoord;
				void main() {
					gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
					texCoord = texPos;
				}
			)";
			SHADER_VERT_GENERIC_TEXT_DRAW = new gfx::shaders::Shader(SHADER_VERT_GENERIC_TEXT_DRAW_SOURCE, GL_VERTEX_SHADER);


			// SHADER_FRAG_GENERIC_TEXT_DRAW
			const std::string SHADER_FRAG_GENERIC_TEXT_DRAW_SOURCE = 
			R"(
			#version 330 core
			in vec2 texCoord;
			out vec4 color;
			uniform vec4 textColor;
			uniform sampler2D texture1;
			void main() {    
				color = vec4(textColor.r, textColor.g, textColor.b, textColor.a * texture(texture1, texCoord).r);
			}  
			)";

			SHADER_FRAG_GENERIC_TEXT_DRAW = new gfx::shaders::Shader(SHADER_FRAG_GENERIC_TEXT_DRAW_SOURCE, GL_FRAGMENT_SHADER);


			// SHADER_PROG_GENERIC_TEXT_DRAW
			SHADER_PROG_GENERIC_TEXT_DRAW = new gfx::shaders::ShaderProgram({SHADER_VERT_GENERIC_TEXT_DRAW, SHADER_FRAG_GENERIC_TEXT_DRAW});
		}

		void destroyDefinitions() noexcept {
			delete MESH_SQUARE_CENTERED;

			delete SHADER_VERT_GENERIC_TEXTURE;
			delete SHADER_FRAG_GENERIC_TEXTURE;
			delete SHADER_PROG_GENERIC_TEXTURE;

			delete SHADER_VERT_GENERIC_TEXTURE_ONLYMODEL;
			delete SHADER_FRAG_GENERIC_TEXTURE_ONLYMODEL;
			delete SHADER_PROG_GENERIC_TEXTURE_ONLYMODEL;

			delete SHADER_VERT_GENERIC_TEXT_GEN;
			delete SHADER_FRAG_GENERIC_TEXT_GEN;
			delete SHADER_PROG_GENERIC_TEXT_GEN;

			delete SHADER_VERT_GENERIC_TEXT_DRAW;
			delete SHADER_FRAG_GENERIC_TEXT_DRAW;
			delete SHADER_PROG_GENERIC_TEXT_DRAW;
		}
	}
}