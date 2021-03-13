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

struct DirectionalLight {
	vec3 Direction;
	vec3 Color;
};

layout(std430, binding = 0) buffer PointLights
{
    PointLight lights[];
} pointLights;

layout(std430, binding = 1) buffer DirectionalLights
{
    DirectionalLight lights[];
} directionalLights;

uniform vec3 cameraPosition;
uniform vec3 ambient;
uniform Material material;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;  

out vec4 FragColor;

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir);
vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal);

void main() {
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(cameraPosition - FragPos);

	vec3 result = ambient * vec3(texture(material.diffuse, TexCoords));

	// Calculate point light contribution
	for(int i = 0; i < pointLights.lights.length(); i++) {
		result += CalcPointLight(pointLights.lights[i], norm, viewDir);
	}

	// Calculate directional light contribution
	for(int i = 0; i < directionalLights.lights.length(); i++) {
		result += CalcDirectionalLight(directionalLights.lights[i], norm);
	}

	FragColor = vec4(result, 1.0);   
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(light.Position - FragPos);
    float diff = max(dot(normal, lightDir), 0.0);

	float dist = length(light.Position - FragPos);
	float attenuation = 1.0 / (light.AttenuationConstant + light.AttenuationLinear * dist + light.AttenuationQuadratic * (dist * dist)); 

	// Diffuse shading
	vec3 diffuse = attenuation * light.Color * diff * vec3(texture(material.diffuse, TexCoords));

	// Specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = attenuation * light.Color * spec * vec3(texture(material.specular, TexCoords));

    return (diffuse + specular);
}

vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal) {
	vec3 lightDir = normalize(-light.Direction);
    float diff = max(dot(normal, lightDir), 0.0);

    // vec3 reflectDir = reflect(-lightDir, normal);
    // float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    
    vec3 diffuse = light.Color * diff * vec3(texture(material.diffuse, TexCoords));
    // vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    return diffuse;
}