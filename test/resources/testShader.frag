#version 430 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct PointLight {
	vec3 Position;
	vec3 Color;

	float AttenuationConstant;
	float AttenuationLinear;
	float AttenuationQuadratic;
};

layout(std430, binding = 0) buffer PointLights
{
    PointLight lights[];
} pointLights;

uniform vec3 ambient;
uniform Material material;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;  

out vec4 FragColor;

vec3 CalcPointLight(PointLight light, vec3 normal);

void main() {
	vec3 norm = normalize(Normal);

	vec3 result = ambient * vec3(texture(material.diffuse, TexCoords));

	// Calculate diffuse contribution
	for(int i = 0; i < pointLights.lights.length(); i++) {
		result += CalcPointLight(pointLights.lights[i], norm);
	}

	FragColor = vec4(result, 1.0);   
}

vec3 CalcPointLight(PointLight light, vec3 normal) {
    vec3 lightDir = normalize(light.Position - FragPos);
    float diff = max(dot(normal, lightDir), 0.0);

    float dist = length(light.Position - FragPos);
    float attenuation = 1.0 / (light.AttenuationConstant + light.AttenuationLinear * dist + light.AttenuationQuadratic * (dist * dist));  

	vec3 diffuse = attenuation * light.Color * diff * vec3(texture(material.diffuse, TexCoords));
    return diffuse;
}
