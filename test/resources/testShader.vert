#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 texPos;

struct Instance {
	mat4 ModelMatrix;
	mat4 NormalMatrix;
};

layout(std430, binding = 0) buffer Instances
{
    Instance instance[];
} instances;


uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos; 

void main() {
	Instance instance = instances.instance[gl_InstanceID];
	mat4 modelMatrix = instance.ModelMatrix;
	mat3 normalMatrix = mat3(instance.NormalMatrix);

	// Output
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
	TexCoords = texPos;
	Normal = normalMatrix * normals;
	FragPos = vec3(modelMatrix * vec4(aPos, 1.0));
}