#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 texPos;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos; 

void main() {
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
	TexCoords = texPos;
	Normal = normalMatrix * normals;
	FragPos = vec3(modelMatrix * vec4(aPos, 1.0));
}