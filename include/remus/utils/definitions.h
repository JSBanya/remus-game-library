#pragma once

#include <vector>
#include <string>
#include <glad/glad.h>
#include <remus/gfx/models/mesh.h>
#include <remus/gfx/shaders/shader.h>
#include <remus/gfx/shaders/shaderProgram.h>


namespace remus {
	namespace utils {
		
		// Standard 2D square using coord range [-1,1]
		extern gfx::models::Mesh* MESH_SQUARE_CENTERED; 
		
		// Generic shader with model, view, and projection matrix, plus texture
		extern gfx::shaders::Shader* SHADER_VERT_GENERIC_TEXTURE;
		extern gfx::shaders::Shader* SHADER_FRAG_GENERIC_TEXTURE;
		extern gfx::shaders::ShaderProgram* SHADER_PROG_GENERIC_TEXTURE;

		// Generic shader with only model matrix, plus texture
		extern gfx::shaders::Shader* SHADER_VERT_GENERIC_TEXTURE_ONLYMODEL;
		extern gfx::shaders::Shader* SHADER_FRAG_GENERIC_TEXTURE_ONLYMODEL;
		extern gfx::shaders::ShaderProgram* SHADER_PROG_GENERIC_TEXTURE_ONLYMODEL;
		
		// Generic shader for generating text
		extern gfx::shaders::Shader* SHADER_VERT_GENERIC_TEXT_GEN;
		extern gfx::shaders::Shader* SHADER_FRAG_GENERIC_TEXT_GEN;
		extern gfx::shaders::ShaderProgram* SHADER_PROG_GENERIC_TEXT_GEN;

		// Generic shader for drawing text
		extern gfx::shaders::Shader* SHADER_VERT_GENERIC_TEXT_DRAW;
		extern gfx::shaders::Shader* SHADER_FRAG_GENERIC_TEXT_DRAW;
		extern gfx::shaders::ShaderProgram* SHADER_PROG_GENERIC_TEXT_DRAW;


		void initDefinitions() noexcept; 
		void destroyDefinitions() noexcept;
	}
}